/* ==========================================================================
 * $File: //dwh/usb_iip/dev/software/otg/linux/drivers/dwc_otg_driver.c $
 * $Revision: #87 $
 * $Date: 2010/11/29 $
 * $Change: 1636033 $
 *
 * Synopsys HS OTG Linux Software Driver and documentation (hereinafter,
 * "Software") is an Unsupported proprietary work of Synopsys, Inc. unless
 * otherwise expressly agreed to in writing between Synopsys and you.
 *
 * The Software IS NOT an item of Licensed Software or Licensed Product under
 * any End User Software License Agreement or Agreement for Licensed Product
 * with Synopsys or any supplement thereto. You are permitted to use and
 * redistribute this Software in source and binary forms, with or without
 * modification, provided that redistributions of source code must retain this
 * notice. You may not view, use, disclose, copy or distribute this file or
 * any information contained herein except pursuant to this license grant from
 * Synopsys. If you do not agree with this notice, including the disclaimer
 * below, then you are not authorized to use the Software.
 *
 * THIS SOFTWARE IS BEING DISTRIBUTED BY SYNOPSYS SOLELY ON AN "AS IS" BASIS
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE HEREBY DISCLAIMED. IN NO EVENT SHALL SYNOPSYS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * ========================================================================== */

/** @file
 * The dwc_otg_driver module provides the initialization and cleanup entry
 * points for the DWC_otg driver. This module will be dynamically installed
 * after Linux is booted using the insmod command. When the module is
 * installed, the dwc_otg_driver_init function is called. When the module is
 * removed (using rmmod), the dwc_otg_driver_cleanup function is called.
 *
 * This module also defines a data structure for the dwc_otg_driver, which is
 * used in conjunction with the standard ARM lm_device structure. These
 * structures allow the OTG driver to comply with the standard Linux driver
 * model in which devices and drivers are registered with a bus driver. This
 * has the benefit that Linux can expose attributes of the driver and device
 * in its special sysfs file system. Users can then read or write files in
 * this file system to perform diagnostics on the driver components or the
 * device.
 */

#include "dwc_otg_os_dep.h"
#include "dwc_otg_dbg.h"
#include "dwc_otg_driver.h"
#include "dwc_otg_attr.h"
#include "dwc_otg_core_if.h"
#include "dwc_otg_pcd_if.h"
#include "dwc_otg_hcd_if.h"
#include "dwc_otg_cil.h"
#include "dwc_otg_pcd.h"
#include "dwc_otg_hcd.h"

#include "dwc_os.h"
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/kthread.h>
#include <linux/freezer.h>
#include <linux/gpio.h>
#include <mach/usb-phy.h>
#include <mach/pad.h>
#include <mach/hw_cfg.h>

#include <linux/debugfs.h> /*for debugfs */

#define DWC_DRIVER_VERSION	"2.92a 15-NOV-2010"
#define DWC_DRIVER_DESC		"HS OTG USB Controller driver"

static const char dwc_driver_name[] = "dwc_otg";
static dwc_otg_device_t *g_otgdev;
int dwc_otg_driver_reinit(void);

struct otg_monitor {
	int pin_id, pin_vbus;
	int pin_id_host, pin_vbus_host;
	int is_host;
	int is_enumerated;
	struct task_struct *task;
	struct delayed_work	work;
};
static struct otg_monitor om;
static int otg_attr_is_host = 0;

extern int pcd_init(struct platform_device *_dev);
extern int hcd_init(struct platform_device *_dev);

extern int pcd_remove(struct platform_device *_dev);

extern void hcd_remove(struct platform_device *_dev);

extern void dwc_otg_adp_start(dwc_otg_core_if_t * core_if);
extern void dwc_otg_core_dev_init(dwc_otg_core_if_t * _core_if);

void otg_monitor_switch(const char *func);
/*-------------------------------------------------------------------------*/
/* Encapsulate the module parameter settings */

struct dwc_otg_driver_module_params {
	int32_t opt;
	int32_t otg_cap;
	int32_t dma_enable;
	int32_t dma_desc_enable;
	int32_t dma_burst_size;
	int32_t speed;
	int32_t host_support_fs_ls_low_power;
	int32_t host_ls_low_power_phy_clk;
	int32_t enable_dynamic_fifo;
	int32_t data_fifo_size;
	int32_t dev_rx_fifo_size;
	int32_t dev_nperio_tx_fifo_size;
	uint32_t dev_perio_tx_fifo_size[MAX_PERIO_FIFOS];
	int32_t host_rx_fifo_size;
	int32_t host_nperio_tx_fifo_size;
	int32_t host_perio_tx_fifo_size;
	int32_t max_transfer_size;
	int32_t max_packet_count;
	int32_t host_channels;
	int32_t dev_endpoints;
	int32_t phy_type;
	int32_t phy_utmi_width;
	int32_t phy_ulpi_ddr;
	int32_t phy_ulpi_ext_vbus;
	int32_t i2c_enable;
	int32_t ulpi_fs_ls;
	int32_t ts_dline;
	int32_t en_multiple_tx_fifo;
	uint32_t dev_tx_fifo_size[MAX_TX_FIFOS];
	uint32_t thr_ctl;
	uint32_t tx_thr_length;
	uint32_t rx_thr_length;
	int32_t pti_enable;
	int32_t mpi_enable;
	int32_t lpm_enable;
	int32_t ic_usb_cap;
	int32_t ahb_thr_ratio;
	int32_t power_down;
	int32_t reload_ctl;
	int32_t otg_ver;
	int32_t adp_enable;
};

static struct dwc_otg_driver_module_params dwc_otg_module_params = {
	.opt = -1,
	.otg_cap = -1,
	.dma_enable = -1,
	.dma_desc_enable = -1,
	.dma_burst_size = -1,
	.speed = -1,
	.host_support_fs_ls_low_power = -1,
	.host_ls_low_power_phy_clk = -1,
	.enable_dynamic_fifo = -1,
	.data_fifo_size = -1,
	.dev_rx_fifo_size = -1,
	.dev_nperio_tx_fifo_size = -1,
	.dev_perio_tx_fifo_size = {
				   /* dev_perio_tx_fifo_size_1 */
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1,
				   -1
				   /* 15 */
				   },
	.host_rx_fifo_size = -1,
	.host_nperio_tx_fifo_size = -1,
	.host_perio_tx_fifo_size = -1,
	.max_transfer_size = -1,
	.max_packet_count = -1,
	.host_channels = -1,
	.dev_endpoints = -1,
	.phy_type = -1,
	.phy_utmi_width = -1,
	.phy_ulpi_ddr = -1,
	.phy_ulpi_ext_vbus = -1,
	.i2c_enable = -1,
	.ulpi_fs_ls = -1,
	.ts_dline = -1,
	.en_multiple_tx_fifo = -1,
	.dev_tx_fifo_size = {
			     /* dev_tx_fifo_size */
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1,
			     -1
			     /* 15 */
			     },
	.thr_ctl = -1,
	.tx_thr_length = -1,
	.rx_thr_length = -1,
	.pti_enable = -1,
	.mpi_enable = -1,
	.lpm_enable = -1,
	.ic_usb_cap = -1,
	.ahb_thr_ratio = -1,
	.power_down = -1,
	.reload_ctl = -1,
	.otg_ver = -1,
	.adp_enable = -1,
};

/**
 * This function shows the Driver Version.
 */
static ssize_t version_show(struct device_driver *dev, char *buf)
{
	return snprintf(buf, sizeof(DWC_DRIVER_VERSION) + 2, "%s\n",
			DWC_DRIVER_VERSION);
}

static DRIVER_ATTR(version, S_IRUGO, version_show, NULL);

#if defined(CONFIG_DWC_OTG_DOUBLE_MANUAL)
static ssize_t g_is_host_show(struct device_driver *dev, char *buf)
{
	return sprintf(buf, "%d\n", otg_attr_is_host);
}

static ssize_t g_is_host_store(struct device_driver *dev, const char *buf,
			       size_t count)
{
	otg_attr_is_host = (int)simple_strtoul(buf, NULL, 16);
	if(otg_attr_is_host == 0)
		otg_monitor_switch("device");
	else
		otg_monitor_switch("host");

	return count;
}

static DRIVER_ATTR(is_host, S_IRUGO | S_IWUSR, g_is_host_show,
		   g_is_host_store);
#endif//CONFIG_DWC_OTG_DOUBLE_MANUAL
/**
 * Global Debug Level Mask.
 */
uint32_t g_dbg_lvl = 0xff;		/* OFF */

/**
 * This function shows the driver Debug Level.
 */
static ssize_t dbg_level_show(struct device_driver *drv, char *buf)
{
	return sprintf(buf, "0x%0x\n", g_dbg_lvl);
}

/**
 * This function stores the driver Debug Level.
 */
static ssize_t dbg_level_store(struct device_driver *drv, const char *buf,
			       size_t count)
{
	g_dbg_lvl = simple_strtoul(buf, NULL, 16);
	return count;
}

static DRIVER_ATTR(debuglevel, S_IRUGO | S_IWUSR, dbg_level_show,
		   dbg_level_store);

/*This function return dwc_otg_device pointer*/
dwc_otg_device_t * dwc_get_otg_device(void) 
{
	return g_otgdev;
}

/**
 * This function is called during module intialization
 * to pass module parameters to the DWC_OTG CORE.
 */
static int set_parameters(dwc_otg_core_if_t * core_if)
{
	int retval = 0;
	int i;

	if (dwc_otg_module_params.otg_cap != -1) {
		retval +=
		    dwc_otg_set_param_otg_cap(core_if,
					      dwc_otg_module_params.otg_cap);
	}
	if (dwc_otg_module_params.dma_enable != -1) {
		retval +=
		    dwc_otg_set_param_dma_enable(core_if,
						 dwc_otg_module_params.
						 dma_enable);
	}
	if (dwc_otg_module_params.dma_desc_enable != -1) {
		retval +=
		    dwc_otg_set_param_dma_desc_enable(core_if,
						      dwc_otg_module_params.
						      dma_desc_enable);
	}
	if (dwc_otg_module_params.opt != -1) {
		retval +=
		    dwc_otg_set_param_opt(core_if, dwc_otg_module_params.opt);
	}
	if (dwc_otg_module_params.dma_burst_size != -1) {
		retval +=
		    dwc_otg_set_param_dma_burst_size(core_if,
						     dwc_otg_module_params.
						     dma_burst_size);
	}
	if (dwc_otg_module_params.host_support_fs_ls_low_power != -1) {
		retval +=
		    dwc_otg_set_param_host_support_fs_ls_low_power(core_if,
								   dwc_otg_module_params.
								   host_support_fs_ls_low_power);
	}
	if (dwc_otg_module_params.enable_dynamic_fifo != -1) {
		retval +=
		    dwc_otg_set_param_enable_dynamic_fifo(core_if,
							  dwc_otg_module_params.
							  enable_dynamic_fifo);
	}
	if (dwc_otg_module_params.data_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_data_fifo_size(core_if,
						     dwc_otg_module_params.
						     data_fifo_size);
	}
	if (dwc_otg_module_params.dev_rx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_dev_rx_fifo_size(core_if,
						       dwc_otg_module_params.
						       dev_rx_fifo_size);
	}
	if (dwc_otg_module_params.dev_nperio_tx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_dev_nperio_tx_fifo_size(core_if,
							      dwc_otg_module_params.
							      dev_nperio_tx_fifo_size);
	}
	if (dwc_otg_module_params.host_rx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_host_rx_fifo_size(core_if,
							dwc_otg_module_params.host_rx_fifo_size);
	}
	if (dwc_otg_module_params.host_nperio_tx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_host_nperio_tx_fifo_size(core_if,
							       dwc_otg_module_params.
							       host_nperio_tx_fifo_size);
	}
	if (dwc_otg_module_params.host_perio_tx_fifo_size != -1) {
		retval +=
		    dwc_otg_set_param_host_perio_tx_fifo_size(core_if,
							      dwc_otg_module_params.
							      host_perio_tx_fifo_size);
	}
	if (dwc_otg_module_params.max_transfer_size != -1) {
		retval +=
		    dwc_otg_set_param_max_transfer_size(core_if,
							dwc_otg_module_params.
							max_transfer_size);
	}
	if (dwc_otg_module_params.max_packet_count != -1) {
		retval +=
		    dwc_otg_set_param_max_packet_count(core_if,
						       dwc_otg_module_params.
						       max_packet_count);
	}
	if (dwc_otg_module_params.host_channels != -1) {
		retval +=
		    dwc_otg_set_param_host_channels(core_if,
						    dwc_otg_module_params.
						    host_channels);
	}
	if (dwc_otg_module_params.dev_endpoints != -1) {
		retval +=
		    dwc_otg_set_param_dev_endpoints(core_if,
						    dwc_otg_module_params.
						    dev_endpoints);
	}
	if (dwc_otg_module_params.phy_type != -1) {
		retval +=
		    dwc_otg_set_param_phy_type(core_if,
					       dwc_otg_module_params.phy_type);
	}
	if (dwc_otg_module_params.speed != -1) {
		retval +=
		    dwc_otg_set_param_speed(core_if,
					    dwc_otg_module_params.speed);
	}
	if (dwc_otg_module_params.host_ls_low_power_phy_clk != -1) {
		retval +=
		    dwc_otg_set_param_host_ls_low_power_phy_clk(core_if,
								dwc_otg_module_params.
								host_ls_low_power_phy_clk);
	}
	if (dwc_otg_module_params.phy_ulpi_ddr != -1) {
		retval +=
		    dwc_otg_set_param_phy_ulpi_ddr(core_if,
						   dwc_otg_module_params.
						   phy_ulpi_ddr);
	}
	if (dwc_otg_module_params.phy_ulpi_ext_vbus != -1) {
		retval +=
		    dwc_otg_set_param_phy_ulpi_ext_vbus(core_if,
							dwc_otg_module_params.
							phy_ulpi_ext_vbus);
	}
	if (dwc_otg_module_params.phy_utmi_width != -1) {
		retval +=
		    dwc_otg_set_param_phy_utmi_width(core_if,
						     dwc_otg_module_params.
						     phy_utmi_width);
	}
	if (dwc_otg_module_params.ulpi_fs_ls != -1) {
		retval +=
		    dwc_otg_set_param_ulpi_fs_ls(core_if,
						 dwc_otg_module_params.ulpi_fs_ls);
	}
	if (dwc_otg_module_params.ts_dline != -1) {
		retval +=
		    dwc_otg_set_param_ts_dline(core_if,
					       dwc_otg_module_params.ts_dline);
	}
	if (dwc_otg_module_params.i2c_enable != -1) {
		retval +=
		    dwc_otg_set_param_i2c_enable(core_if,
						 dwc_otg_module_params.
						 i2c_enable);
	}
	if (dwc_otg_module_params.en_multiple_tx_fifo != -1) {
		retval +=
		    dwc_otg_set_param_en_multiple_tx_fifo(core_if,
							  dwc_otg_module_params.
							  en_multiple_tx_fifo);
	}
	for (i = 0; i < 15; i++) {
		if (dwc_otg_module_params.dev_perio_tx_fifo_size[i] != -1) {
			retval +=
			    dwc_otg_set_param_dev_perio_tx_fifo_size(core_if,
								     dwc_otg_module_params.
								     dev_perio_tx_fifo_size
								     [i], i);
		}
	}

	for (i = 0; i < 15; i++) {
		if (dwc_otg_module_params.dev_tx_fifo_size[i] != -1) {
			retval += dwc_otg_set_param_dev_tx_fifo_size(core_if,
								     dwc_otg_module_params.
								     dev_tx_fifo_size
								     [i], i);
		}
	}
	if (dwc_otg_module_params.thr_ctl != -1) {
		retval +=
		    dwc_otg_set_param_thr_ctl(core_if,
					      dwc_otg_module_params.thr_ctl);
	}
	if (dwc_otg_module_params.mpi_enable != -1) {
		retval +=
		    dwc_otg_set_param_mpi_enable(core_if,
						 dwc_otg_module_params.
						 mpi_enable);
	}
	if (dwc_otg_module_params.pti_enable != -1) {
		retval +=
		    dwc_otg_set_param_pti_enable(core_if,
						 dwc_otg_module_params.
						 pti_enable);
	}
	if (dwc_otg_module_params.lpm_enable != -1) {
		retval +=
		    dwc_otg_set_param_lpm_enable(core_if,
						 dwc_otg_module_params.
						 lpm_enable);
	}
	if (dwc_otg_module_params.ic_usb_cap != -1) {
		retval +=
		    dwc_otg_set_param_ic_usb_cap(core_if,
						 dwc_otg_module_params.
						 ic_usb_cap);
	}
	if (dwc_otg_module_params.tx_thr_length != -1) {
		retval +=
		    dwc_otg_set_param_tx_thr_length(core_if,
						    dwc_otg_module_params.tx_thr_length);
	}
	if (dwc_otg_module_params.rx_thr_length != -1) {
		retval +=
		    dwc_otg_set_param_rx_thr_length(core_if,
						    dwc_otg_module_params.
						    rx_thr_length);
	}
	if (dwc_otg_module_params.ahb_thr_ratio != -1) {
		retval +=
		    dwc_otg_set_param_ahb_thr_ratio(core_if,
						    dwc_otg_module_params.ahb_thr_ratio);
	}
	if (dwc_otg_module_params.power_down != -1) {
		retval +=
		    dwc_otg_set_param_power_down(core_if,
						 dwc_otg_module_params.power_down);
	}
	if (dwc_otg_module_params.reload_ctl != -1) {
		retval +=
		    dwc_otg_set_param_reload_ctl(core_if,
						 dwc_otg_module_params.reload_ctl);
	}
	if (dwc_otg_module_params.otg_ver != -1) {
		retval +=
		    dwc_otg_set_param_otg_ver(core_if,
					      dwc_otg_module_params.otg_ver);
	}
	if (dwc_otg_module_params.adp_enable != -1) {
		retval +=
		    dwc_otg_set_param_adp_enable(core_if,
						 dwc_otg_module_params.
						 adp_enable);
	}
	return retval;
}

/**
 * This function is the top level interrupt handler for the Common
 * (Device and host modes) interrupts.
 */
static irqreturn_t dwc_otg_common_irq(int irq, void *dev)
{
	dwc_otg_device_t *otg_dev = dev;
	int32_t retval = IRQ_NONE;

	retval = dwc_otg_handle_common_intr(otg_dev->core_if);
	if (retval != 0) {
	}
	return IRQ_RETVAL(retval);
}

/**
 * This function is called when a lm_device is unregistered with the
 * dwc_otg_driver. This happens, for example, when the rmmod command is
 * executed. The device may or may not be electrically present. If it is
 * present, the driver stops device processing. Any resources used on behalf
 * of this device are freed.
 *
 * @param _dev
 */
static int dwc_otg_driver_remove(struct platform_device *_dev)
{
   //drvdata has been replaced by usb_hcd data when hcd_init
    //dwc_otg_device_t *otg_dev = platform_get_drvdata(_dev);
    dwc_otg_device_t *otg_dev = dwc_get_otg_device();

	DWC_DEBUGPL(DBG_ANY, "%s(%p)\n", __func__, _dev);

	if (!otg_dev) {
		/* Memory allocation for the dwc_otg_device failed. */
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev NULL!\n", __func__);
		return -1;
	}
	if (om.task) {
		kthread_stop(om.task);
		om.task = NULL;
	}
#ifndef DWC_DEVICE_ONLY
	if (otg_dev->hcd) {
		hcd_remove(_dev);
	} else {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev->hcd NULL!\n", __func__);
		return -1;
	}
#endif

#ifndef DWC_HOST_ONLY
	if (otg_dev->pcd) {
		pcd_remove(_dev);
	} else {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev->pcd NULL!\n", __func__);
		return -1;
	}
#endif
	if (otg_dev->core_if) {
		dwc_otg_cil_remove(otg_dev->core_if);
	} else {
		DWC_DEBUGPL(DBG_ANY, "%s: otg_dev->core_if NULL!\n", __func__);
		return -1;
	}

	/*
	 * Remove the device attributes
	 */
	dwc_otg_attr_remove(_dev);

	/*
	 * Return the memory.
	 */
	if (otg_dev->os_dep.base) {
		iounmap(otg_dev->os_dep.base);
	}
	DWC_FREE(otg_dev);

	/*
	 * Clear the drvdata pointer.
	 */
	platform_set_drvdata(_dev, 0);
        return 0;
}

void otg_monitor_switch(const char *func)
{
	if(strncmp(func, "host", 5) == 0) {
#if defined(CONFIG_DWC_OTG_DOUBLE_EXTRAID)
		printk(KERN_ERR "OTG monitor: checking state om.pin_id(%d): %d\n",
					om.pin_id, gpio_get_value(om.pin_id));
#endif
		otg_phy_reconfig(1, 0);
		if(om.pin_vbus) {
			gpio_direction_output(om.pin_vbus, om.pin_vbus_host);
			printk(KERN_ERR "OTG monitor: set vbus_pin(%s) to %d\n",
						om.pin_vbus_host? "normal": "reversed", om.pin_vbus_host);
		}
		om.is_host = 1;
		om.is_enumerated = 0;
		printk(KERN_ERR "OTG monitor: switched to host!\n");
	}
	else if(strncmp(func, "device", 7) == 0) {
#if defined(CONFIG_DWC_OTG_DOUBLE_EXTRAID)
		printk(KERN_ERR "OTG monitor: checking state om.pin_id(%d): %d\n",
					om.pin_id, gpio_get_value(om.pin_id));
#endif
		if(om.pin_vbus) {
			gpio_direction_output(om.pin_vbus, !om.pin_vbus_host);
			printk(KERN_ERR "OTG monitor: set vbus_pin(%s) to %d\n",
						om.pin_vbus_host? "normal": "reversed", !om.pin_vbus_host);
		}
		otg_phy_reconfig(1, 1);
		dwc_otg_driver_reinit();
		om.is_host = 0;
		printk(KERN_ERR "OTG monitor: switched to device (temporary)!\n");
#if defined(CONFIG_DWC_OTG_DOUBLE_EXTRAID)
		schedule_delayed_work(&om.work, msecs_to_jiffies(2000));
#endif
	}
	else {
		printk(KERN_ERR "OTG monitor: unknown switch command: %s\n", func);
	}
}

void otg_monitor_double_check(struct work_struct *work)
{
	if(om.is_enumerated) {
		printk(KERN_ERR "OTG monitor: enumerated, stay on device\n");
		return ;
	}

	printk(KERN_ERR "OTG monitor: no enumeration detected, switch back to host\n");
	otg_monitor_switch("host");
}

void otg_monitor_set_enumerated(void)
{
	om.is_enumerated = 1;
}
EXPORT_SYMBOL(otg_monitor_set_enumerated);

int otg_monitor_thread(void *x)
{
	printk(KERN_ERR "OTG monitor: vbus_pin %d (%s)\n",
		om.pin_vbus, om.pin_vbus_host? "normal": "reversed");

#if defined(CONFIG_DWC_OTG_DOUBLE) && defined(CONFIG_DWC_OTG_DOUBLE_EXTRAID)
	int pid = -1, tmp;
	if(!om.pin_id) {
		printk(KERN_ERR "OTG monitor: no om.pin_id specified, cannot start monitor\n");
		return -1;
	} else {
		printk(KERN_ERR "OTG monitor: id_pin %d (%s)\n",
		 om.pin_id, om.pin_id_host ? "reversed": "normal");
	}

	while(1) {
		if((tmp = gpio_get_value(om.pin_id)) == pid) goto done;
		else pid = tmp;

		if(pid == om.pin_id_host && om.is_host != 1) {
#endif//CONFIG_DWC_OTG_DOUBLE
#if defined(CONFIG_DWC_OTG_DOUBLE) || defined(CONFIG_DWC_OTG_HOST_ONLY)
			/* switch to host */
			otg_monitor_switch("host");
#endif

#if defined(CONFIG_DWC_OTG_DOUBLE) && defined(CONFIG_DWC_OTG_DOUBLE_EXTRAID)
		} else if (pid != om.pin_id_host
			 && om.is_host != 0) {
#endif//CONFIG_DWC_OTG_DOUBLE
#if defined(CONFIG_DWC_OTG_DOUBLE) || defined(CONFIG_DWC_OTG_DEVICE_ONLY)
			/* switch to device */
			otg_monitor_switch("device");
#endif
#if defined(CONFIG_DWC_OTG_DOUBLE) && defined(CONFIG_DWC_OTG_DOUBLE_EXTRAID)
		}

done:
		msleep(200);
		if (kthread_should_stop()) {
			printk(KERN_ERR "OTG monitor: stop\n");
			break;
		}
	}
#endif

	return 0;
}

/*-------------------------------------------------------------------------*/
/*add dugfs for otg*/
/* atomic operations from debugfs */

typedef struct {
	struct dentry *dir;
	/* atomic ops */
	struct dentry *addr_set;
	struct dentry *reg;
	struct dentry *link;
	unsigned int addr;
} otg_dbgfs_t;

static otg_dbgfs_t otg_dbgfs;

enum otg_dbgfs_type { OTG_REG_ADDR, OTG_REG_VAL, OTG_LINK};
/* reading operations */
static ssize_t otg_dbgfs_read(char __user *, size_t , loff_t *, enum otg_dbgfs_type);
static ssize_t otg_dbgfs_addr_read(struct file *, char __user *, size_t , loff_t *);
static ssize_t otg_dbgfs_get_reg_read(struct file *, char __user *, size_t , loff_t *);

/* writting operations */
static int otg_dbgfs_write(const char __user *buff, size_t , enum otg_dbgfs_type);
static ssize_t otg_dbgfs_addr_write(struct file *, const char __user *, size_t , loff_t *);
static ssize_t otg_dbgfs_set_reg_write(struct file *, const char __user *, size_t , loff_t *);
static ssize_t otg_dbgfs_set_link_write(struct file *, const char __user *, size_t , loff_t *);

/* ops for atomic operations */
static const struct file_operations otg_dbgfs_addr_ops = {
	.open		= nonseekable_open,
	.read		= otg_dbgfs_addr_read,
	.write		= otg_dbgfs_addr_write,
	.llseek		= no_llseek,
};

static const struct file_operations otg_dbgfs_reg_ops = {
	.open		= nonseekable_open,
	.write		= otg_dbgfs_set_reg_write,
	.read		= otg_dbgfs_get_reg_read,
	.llseek		= no_llseek,
};

static const struct file_operations otg_dbgfs_link_ops = {
	.open		= nonseekable_open,
	.write		= otg_dbgfs_set_link_write,
	.llseek		= no_llseek,
};

static inline int dwc_otg_reg_read(uint32_t addr)
{
	if (!g_otgdev || !g_otgdev->os_dep.base)
		return 0;
	return readl(g_otgdev->os_dep.base + addr);
}

static inline void dwc_otg_reg_write(uint32_t addr, uint32_t val)
{
	if (!g_otgdev || !g_otgdev->os_dep.base)
		return ;
	writel(val, g_otgdev->os_dep.base + addr);
}

static inline void dwc_otg_reg_modify(uint32_t addr,uint32_t clear_mask,
	uint32_t set_mask)
{
	if (!g_otgdev || !g_otgdev->os_dep.base)
		return ;
	writel((readl(g_otgdev->os_dep.base + addr) & ~clear_mask)
		| set_mask, g_otgdev->os_dep.base + addr);
}

/* atomic operations */
static ssize_t otg_dbgfs_read(char __user *buff, size_t count, loff_t *ppos,
	enum otg_dbgfs_type type)
{
	char *str;
	u32 data = 0;
	ssize_t len = 0;

	str = kzalloc(count, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	switch (type) {
	case OTG_REG_ADDR:
		len = sprintf(str, "addr = 0x%x\n", otg_dbgfs.addr);
		break;
	case OTG_REG_VAL:
		if (otg_dbgfs.addr < 0x1000) {
			/*read resigter value */
			data = dwc_otg_reg_read(otg_dbgfs.addr);
			len = sprintf(str, "addr = 0x%x, value = 0x%x\n", otg_dbgfs.addr, data);
		} else {
			len = sprintf(str, "addr = 0x%x, value = 0x%x\n", otg_dbgfs.addr, 0);
		}
		break;
	case OTG_LINK:
		break;
	default:
		break;
	}

	if (len < 0)
		DWC_PRINTF("Can't read data\n");
	else
		len = simple_read_from_buffer(buff, count, ppos, str, len);

	kfree(str);

	return len;
}

static int otg_dbgfs_write(const char __user *buff, size_t count,
		enum otg_dbgfs_type type)
{
	int err = 0, i = 0, ret = 0;
	unsigned int arg = 0;
	char *start, *str;
	dctl_data_t dctl = { 0 };

	str = kzalloc(count, GFP_KERNEL);
	if (!str)
		return -ENOMEM;

	if (copy_from_user(str, buff, count)) {
		ret = -EFAULT;
		goto exit_otg_dbgfs_write;
	}

	start = str;

	while (*start == ' ')
		start++;

	/* strip ending whitespace */
	for (i = count - 1; i > 0 && isspace(str[i]); i--)
		str[i] = 0;

	switch (type) {
	case OTG_REG_ADDR:
		if (kstrtouint(start, 16, &(otg_dbgfs.addr)))
			ret = -EINVAL;

		if (otg_dbgfs.addr > 0x1000) {
			DWC_PRINTF("error: the addr %d is out of region.\n", otg_dbgfs.addr);
			otg_dbgfs.addr = 0;
			goto exit_otg_dbgfs_write;
		}

		if (otg_dbgfs.addr%4) {
			DWC_PRINTF("error: the addr %d don't align with 4.\n", otg_dbgfs.addr);
			otg_dbgfs.addr -= otg_dbgfs.addr%4;
			goto exit_otg_dbgfs_write;
		}

		break;
	case OTG_REG_VAL:
		if (kstrtouint(start, 16, &arg)) {
			ret = -EINVAL;
			goto exit_otg_dbgfs_write;
		}

		printk("addr = 0x%x, value =0x%x\n", otg_dbgfs.addr, arg);
		dwc_otg_reg_write(otg_dbgfs.addr,arg);
		break;

	case OTG_LINK:
		if (kstrtouint(start, 16, &arg)) {
			ret = -EINVAL;
			goto exit_otg_dbgfs_write;
		}

		dctl.b.sftdiscon = 1;
		/* Device Control Register */
		if (arg == 0x0) {
			/*disconnect*/
			dwc_otg_reg_modify(0x804, 0, dctl.d32);
			printk("disconnect\n");
		} else {
			/*connect*/
			dwc_otg_reg_modify(0x804, dctl.d32, 0);
			printk("connect\n");
		}
		break;
	default:
		break;
	}

	if (err) {
		DWC_PRINTF("error\n");
		ret = -1;
	}

exit_otg_dbgfs_write:
	kfree(str);
	return ret;
}

static ssize_t otg_dbgfs_addr_read(struct file *file, char __user *buff,
				size_t count, loff_t *ppos)
{
	ssize_t len = 0;

	if (*ppos < 0 || !count)
		return -EINVAL;

	len = otg_dbgfs_read(buff, count, ppos, OTG_REG_ADDR);

	return len;
}

static ssize_t otg_dbgfs_get_reg_read(struct file *file, char __user *buff,
				   size_t count, loff_t *ppos)
{
	ssize_t len;

	if (*ppos < 0 || !count)
		return -EINVAL;

	len = otg_dbgfs_read(buff, count, ppos, OTG_REG_VAL);
	return len;
}

static ssize_t otg_dbgfs_addr_write(struct file *file, const char __user *buff,
				size_t count, loff_t *ppos)
{
	ssize_t ret = 0;
	int err = 0;

	ret = count;

	if (*ppos < 0 || !count)
		return -EINVAL;

	err = otg_dbgfs_write(buff, count, OTG_REG_ADDR);
	if (err < 0)
		return err;

	*ppos += ret;

	return ret;
}

static ssize_t otg_dbgfs_set_reg_write(struct file *file, const char __user *buff,
				    size_t count, loff_t *ppos)
{
	ssize_t ret = 0;
	int err = 0;

	ret = count;

	if (*ppos < 0 || !count)
		return -EINVAL;

	err = otg_dbgfs_write(buff, count, OTG_REG_VAL);
	if (err < 0)
		return err;

	*ppos += ret;

	return count;
}

static ssize_t otg_dbgfs_set_link_write(struct file *file, const char __user *buff,
				    size_t count, loff_t *ppos)
{
	ssize_t ret = 0;
	int err = 0;

	ret = count;

	if (*ppos < 0 || !count)
		return -EINVAL;

	err = otg_dbgfs_write(buff, count, OTG_LINK);
	if (err < 0)
		return err;

	*ppos += ret;

	return count;
}

void dwc_otg_debugfs_create(void)
{
	otg_dbgfs.dir = debugfs_create_dir("dwc_otg", NULL);
	if (otg_dbgfs.dir == NULL) {
		DWC_PRINTF(" cannot create debugfs directory\n");
		return;
	}

	/* atomic ops */
	otg_dbgfs.addr_set = debugfs_create_file("addr",
				S_IFREG | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP,
				otg_dbgfs.dir, NULL,
				&otg_dbgfs_addr_ops);
	if (otg_dbgfs.addr_set == NULL)
		DWC_PRINTF("cannot create debugfs entry addr\n");

	otg_dbgfs.reg = debugfs_create_file("reg",
				S_IFREG | S_IRUSR | S_IRGRP | S_IWUSR | S_IWGRP,
				otg_dbgfs.dir, NULL,
				&otg_dbgfs_reg_ops);
	if (otg_dbgfs.reg == NULL)
		DWC_PRINTF("cannot create debugfs entry reg\n");

	otg_dbgfs.link = debugfs_create_file("link",
				S_IFREG | S_IRUSR | S_IRGRP,
				otg_dbgfs.dir, NULL,
				&otg_dbgfs_link_ops);
	if (otg_dbgfs.link == NULL)
		DWC_PRINTF("cannot create debugfs entry link\n");

}

/*-------------------------------------------------------------------------*/


/**
 * This function is called when an lm_device is bound to a
 * dwc_otg_driver. It creates the driver components required to
 * control the device (CIL, HCD, and PCD) and it initializes the
 * device. The driver components are stored in a dwc_otg_device
 * structure. A reference to the dwc_otg_device is saved in the
 * lm_device. This allows the driver to access the dwc_otg_device
 * structure on subsequent calls to driver methods for this device.
 *
 * @param _dev Bus device
 */
static int dwc_otg_driver_probe(struct platform_device *_dev)
{
	int retval = 0;
	dwc_otg_device_t *dwc_otg_device;
	struct resource *res;
	struct otg_cfg *cfg;

	dev_dbg(&_dev->dev, "dwc_otg_driver_probe(%p)\n", _dev);
	cfg = (struct otg_cfg *)(_dev->dev.platform_data);
	if (!cfg) {
		dev_err(&_dev->dev, "Otg platform data miss\n");
		return -ENODEV;
	}
#if 0
	imapx_pad_set_mode(1, 1, 78);      
	imapx_pad_set_dir(0, 1, 78);       
	imapx_pad_set_outdat(0, 1, 78);
#endif
	dwc_otg_device = DWC_ALLOC(sizeof(dwc_otg_device_t));

	if (!dwc_otg_device) {
		dev_err(&_dev->dev, "kmalloc of dwc_otg_device failed\n");
		return -ENOMEM;
	}

	memset(dwc_otg_device, 0, sizeof(*dwc_otg_device));
	dwc_otg_device->os_dep.reg_offset = 0xFFFFFFFF;

	/*
	 * Map the DWC_otg Core memory into virtual address space.
	 */
	dwc_otg_device->irq = platform_get_irq(_dev, 0);
	if (dwc_otg_device->irq == 0) {
		dev_err(&_dev->dev, "no device irq\n");
		retval = -ENODEV;
		goto fail;
	}
	dev_dbg(&_dev->dev, "OTG - device irq: %d\n", dwc_otg_device->irq);
	res = platform_get_resource(_dev, IORESOURCE_MEM, 0);
	if (res == NULL) {
		dev_err(&_dev->dev, "no CSR address\n");
		retval = -ENODEV;
		goto fail;
	}
	dev_dbg(&_dev->dev, "OTG - ioresource_mem start0x%08x: end:0x%08x\n",
		(unsigned)res->start, (unsigned)res->end);

	dwc_otg_device->phys_addr = res->start;
	dwc_otg_device->base_len = res->end - res->start + 1;
	if (request_mem_region(dwc_otg_device->phys_addr, dwc_otg_device->base_len,
	    dwc_driver_name) == NULL) {
		dev_err(&_dev->dev, "request_mem_region failed\n");
		retval = -EBUSY;
		goto fail;
	}

	/*
	*  Map the DWC_otg Core memory into virtual address space.
	*/
	dwc_otg_device->base = ioremap_nocache(dwc_otg_device->phys_addr, dwc_otg_device->base_len);
	if (dwc_otg_device->base == NULL)    {
		dev_err(&_dev->dev, "ioremap() failed\n");
		retval = -ENOMEM;
		goto fail;
    	}
	dwc_otg_device->os_dep.base = dwc_otg_device->base;
    	dev_dbg(&_dev->dev, "mapped base=0x%08x\n", (unsigned)dwc_otg_device->base);

	/*
	 * Initialize driver data to point to the global DWC_otg
	 * Device structure.
	 */
    	platform_set_drvdata(_dev, dwc_otg_device);
        g_otgdev = dwc_otg_device;
	dev_dbg(&_dev->dev, "dwc_otg_device=0x%p\n", dwc_otg_device);

	otg_phy_config(24000000, 1, 1);
	dwc_otg_device->core_if = dwc_otg_cil_init(dwc_otg_device->os_dep.base);
	if (!dwc_otg_device->core_if) {
		dev_err(&_dev->dev, "CIL initialization failed!\n");
		retval = -ENOMEM;
		goto fail;
	}

	/*
	 * Attempt to ensure this device is really a DWC_otg Controller.
	 * Read and verify the SNPSID register contents. The value should be
	 * 0x45F42XXX, which corresponds to "OT2", as in "OTG version 2.XX".
	 */

	if ((dwc_otg_get_gsnpsid(dwc_otg_device->core_if) & 0xFFFFF000) !=
	    0x4F542000) {
		dev_err(&_dev->dev, "Bad value for SNPSID: 0x%08x\n",
			dwc_otg_get_gsnpsid(dwc_otg_device->core_if));
		retval = -EINVAL;
		goto fail;
	}

	/*
	 * Validate parameter values.
	 */
	if (set_parameters(dwc_otg_device->core_if)) {
		retval = -EINVAL;
		goto fail;
	}

	/*
	 * Create Device Attributes in sysfs
	 */
	dwc_otg_attr_create(_dev);

	/*
	 * Disable the global interrupt until all the interrupt
	 * handlers are installed.
	 */
	dwc_otg_disable_global_interrupts(dwc_otg_device->core_if);

	/*
	 * Install the interrupt handler for the common interrupts before
	 * enabling common interrupts in core_init below.
	 */
	DWC_DEBUGPL(DBG_CIL, "registering (common) handler for irq%d\n",
		    dwc_otg_device->irq);
	retval = request_irq((unsigned int)dwc_otg_device->irq, dwc_otg_common_irq,
			     IRQF_SHARED | IRQF_DISABLED | IRQ_LEVEL, "dwc_otg",
			     dwc_otg_device);
	if (retval) {
		DWC_ERROR("request of irq%d failed\n", dwc_otg_device->irq);
		retval = -EBUSY;
		goto fail;
	} else {
		dwc_otg_device->common_irq_installed = 1;
	}

	if (dwc_otg_get_param_adp_enable(dwc_otg_device->core_if)) {
		/*
		 * Performs initial actions required for
		 * Internal ADP logic
		 */
		dwc_otg_adp_start(dwc_otg_device->core_if);
	} else {
		/*
		 * Initialize the DWC_otg core.
		 */
		dwc_otg_core_init(dwc_otg_device->core_if);

#ifndef DWC_HOST_ONLY
		/*
		 * Initialize the PCD
		 */
		retval = pcd_init(_dev);
		if (retval != 0) {
			DWC_ERROR("pcd_init failed\n");
			dwc_otg_device->pcd = NULL;
			goto fail;
		}
#endif
#ifndef DWC_DEVICE_ONLY
		/*
		 * Initialize the HCD
		 */
		retval = hcd_init(_dev);
		if (retval != 0) {
			DWC_ERROR("hcd_init failed\n");
			dwc_otg_device->hcd = NULL;
			goto fail;
		}
#endif
	}

	/*
	 * Enable the global interrupt after all the interrupt
	 * handlers are installed.
	 */
	dwc_otg_enable_global_interrupts(dwc_otg_device->core_if);

	om.pin_id = abs(cfg->extraid);
	om.pin_id_host = (cfg->extraid < 0);
	if (om.pin_id && gpio_is_valid(om.pin_id)) {
		retval = gpio_request(om.pin_id, "otg_extraid");
		if (retval) {
			pr_err("failed request gpio for otg_extraid %d\n", om.pin_id);
			goto fail;
		}
		gpio_direction_input(om.pin_id);
	}

	om.pin_vbus = abs(cfg->drvvbus);
	om.pin_vbus_host = (cfg->drvvbus > 0);
	if (om.pin_vbus && gpio_is_valid(om.pin_vbus)) {
		retval = gpio_request(om.pin_vbus, "otg_drvbus");
		if (retval) {
			pr_err("failed request gpio for otg_vbus %d\n", om.pin_vbus);
			goto fail;
		}
	}

	/* start otg monitor */
	om.is_host = -1;
	INIT_DELAYED_WORK(&om.work, otg_monitor_double_check);
	om.task = kthread_run(otg_monitor_thread, NULL, "otg-monitor");
	if (IS_ERR(om.task))                            
		printk(KERN_ERR "cannot create kernel thread\n");

	/* dwc_otg debugfs create */
	dwc_otg_debugfs_create();
	return 0;
fail:
	dwc_otg_driver_remove(_dev);
	return retval;
}
#ifdef CONFIG_PM
static int dwc_otg_driver_suspend(struct platform_device *pdev, pm_message_t state)
{
        return 0;
}

static int dwc_otg_revert_state(dwc_otg_device_t *dwc_otg_device)
{
    dwc_otg_core_if_t *core_if = dwc_otg_device->core_if;

    /* dwc_otg_cil_init */
    core_if->dev_if->speed = 0;
    core_if->lx_state = DWC_OTG_L3;
    core_if->hcfg.d32 = DWC_READ_REG32(&core_if->host_if->host_global_regs->hcfg);
    core_if->dcfg.d32 = DWC_READ_REG32(&core_if->dev_if->dev_global_regs->dcfg);

    core_if->srp_success = 0;
    core_if->srp_timer_started = 0;
    core_if->snpsid = DWC_READ_REG32(&core_if->core_global_regs->gsnpsid);
    core_if->hibernation_suspend = 0;
    core_if->phy_init_done = 0;

    return 0;
}

int dwc_otg_driver_reinit(void)
{
        dwc_otg_device_t *dwc_otg_device = g_otgdev;

        dwc_otg_revert_state(dwc_otg_device);
        dwc_otg_disable_global_interrupts(dwc_otg_device->core_if);
        if (dwc_otg_get_param_adp_enable(dwc_otg_device->core_if)) {
                dwc_otg_adp_start(dwc_otg_device->core_if);
        } else 
        {
                dwc_otg_core_init(dwc_otg_device->core_if);
                if (dwc_otg_is_device_mode(dwc_otg_device->core_if)) {
                        dwc_otg_core_dev_init(dwc_otg_device->core_if);
                }
		else {
			//DWC_WORKQ_SCHEDULE(core_if->wq_otg, w_conn_id_status_change,core_if, "connection id status change");
		}
        }

	dwc_otg_enable_global_interrupts(dwc_otg_device->core_if);      

        return 0;
}

static int dwc_otg_driver_resume(struct platform_device *pdev)
{
	dwc_otg_device_t *dwc_otg_device = g_otgdev;
	dwc_otg_core_if_t *core_if = dwc_otg_device->core_if;

	/* re-read usb-id state */
	if(!om.is_host) {
		otg_phy_config(24000000, 1, 1);
		dwc_otg_revert_state(dwc_otg_device);
		dwc_otg_disable_global_interrupts(dwc_otg_device->core_if);
		if (dwc_otg_get_param_adp_enable(dwc_otg_device->core_if)) {
			dwc_otg_adp_start(dwc_otg_device->core_if);
		} else 
		{
			dwc_otg_core_init(dwc_otg_device->core_if);
			if (dwc_otg_is_device_mode(dwc_otg_device->core_if)) {
				dwc_otg_core_dev_init(dwc_otg_device->core_if);
			} else {
				DWC_WORKQ_SCHEDULE(core_if->wq_otg, w_conn_id_status_change,core_if, "connection id status change");
			}
		}

		dwc_otg_enable_global_interrupts(dwc_otg_device->core_if);      
	}
	return 0;
}
#else
#define dwc_otg_driver_suspend NULL
#define dwc_otg_driver_resume NULL
#endif
/**
 * This structure defines the methods to be called by a bus driver
 * during the lifecycle of a device on that bus. Both drivers and
 * devices are registered with a bus driver. The bus driver matches
 * devices to drivers based on information in the device and driver
 * structures.
 *
 * The probe function is called when the bus driver matches a device
 * to this driver. The remove function is called when a device is
 * unregistered with the bus driver.
 */
struct platform_driver dwc_otg_driver = {
	.probe	= dwc_otg_driver_probe,
	.remove	= dwc_otg_driver_remove,
	.suspend = dwc_otg_driver_suspend,
	.resume = dwc_otg_driver_resume,
	.driver = {
		.name = dwc_driver_name,
		.owner = THIS_MODULE,
	},
};

/**
 * This function is called when the dwc_otg_driver is installed with the
 * insmod command. It registers the dwc_otg_driver structure with the
 * appropriate bus driver. This will cause the dwc_otg_driver_probe function
 * to be called. In addition, the bus driver will automatically expose
 * attributes defined for the device and driver in the special sysfs file
 * system.
 *
 * @return
 */
static int __init dwc_otg_driver_init(void)
{
	int retval = 0;
	printk(KERN_INFO "%s: version %s\n", dwc_driver_name,
	       DWC_DRIVER_VERSION);
	retval = platform_driver_register(&dwc_otg_driver);
	if (retval < 0) {
		printk(KERN_ERR "%s retval=%d\n", __func__, retval);
		return retval;
	}
	
   	retval = driver_create_file(&dwc_otg_driver.driver, &driver_attr_version);
	if(retval < 0) {
        	printk(KERN_ERR "%s retval=%d\n", __func__, retval);
		return retval;
	}

#if defined(CONFIG_DWC_OTG_DOUBLE_MANUAL)
	retval = driver_create_file(&dwc_otg_driver.driver, &driver_attr_is_host);
	if(retval < 0) {
		printk(KERN_ERR "%s retval=%d\n", __func__, retval);
		return retval;
	}
#endif//CONFIG_DWC_OTG_DOUBLE_MANUAL

	return retval;
}
fs_initcall(dwc_otg_driver_init);
//module_init(dwc_otg_driver_init);

/**
 * This function is called when the driver is removed from the kernel
 * with the rmmod command. The driver unregisters itself with its bus
 * driver.
 *
 */
static void __exit dwc_otg_driver_cleanup(void)
{
	printk(KERN_DEBUG "dwc_otg_driver_cleanup()\n");

	driver_remove_file(&dwc_otg_driver.driver, &driver_attr_debuglevel);
  	driver_remove_file(&dwc_otg_driver.driver, &driver_attr_version);
#if defined(CONFIG_DWC_OTG_DOUBLE_MANUAL)
	driver_remove_file(&dwc_otg_driver.driver, &driver_attr_is_host);
#endif

	platform_driver_unregister(&dwc_otg_driver);

	printk(KERN_INFO "%s module removed\n", dwc_driver_name);
}

module_exit(dwc_otg_driver_cleanup);

MODULE_DESCRIPTION(DWC_DRIVER_DESC);
MODULE_AUTHOR("Synopsys Inc.");
MODULE_LICENSE("GPL");

module_param_named(otg_cap, dwc_otg_module_params.otg_cap, int, 0444);
MODULE_PARM_DESC(otg_cap, "OTG Capabilities 0=HNP&SRP 1=SRP Only 2=None");
module_param_named(opt, dwc_otg_module_params.opt, int, 0444);
MODULE_PARM_DESC(opt, "OPT Mode");
module_param_named(dma_enable, dwc_otg_module_params.dma_enable, int, 0444);
MODULE_PARM_DESC(dma_enable, "DMA Mode 0=Slave 1=DMA enabled");

module_param_named(dma_desc_enable, dwc_otg_module_params.dma_desc_enable, int,
		   0444);
MODULE_PARM_DESC(dma_desc_enable,
		 "DMA Desc Mode 0=Address DMA 1=DMA Descriptor enabled");

module_param_named(dma_burst_size, dwc_otg_module_params.dma_burst_size, int,
		   0444);
MODULE_PARM_DESC(dma_burst_size,
		 "DMA Burst Size 1, 4, 8, 16, 32, 64, 128, 256");
module_param_named(speed, dwc_otg_module_params.speed, int, 0444);
MODULE_PARM_DESC(speed, "Speed 0=High Speed 1=Full Speed");
module_param_named(host_support_fs_ls_low_power,
		   dwc_otg_module_params.host_support_fs_ls_low_power, int,
		   0444);
MODULE_PARM_DESC(host_support_fs_ls_low_power,
		 "Support Low Power w/FS or LS 0=Support 1=Don't Support");
module_param_named(host_ls_low_power_phy_clk,
		   dwc_otg_module_params.host_ls_low_power_phy_clk, int, 0444);
MODULE_PARM_DESC(host_ls_low_power_phy_clk,
		 "Low Speed Low Power Clock 0=48Mhz 1=6Mhz");
module_param_named(enable_dynamic_fifo,
		   dwc_otg_module_params.enable_dynamic_fifo, int, 0444);
MODULE_PARM_DESC(enable_dynamic_fifo, "0=cC Setting 1=Allow Dynamic Sizing");
module_param_named(data_fifo_size, dwc_otg_module_params.data_fifo_size, int,
		   0444);
MODULE_PARM_DESC(data_fifo_size,
		 "Total number of words in the data FIFO memory 32-32768");
module_param_named(dev_rx_fifo_size, dwc_otg_module_params.dev_rx_fifo_size,
		   int, 0444);
MODULE_PARM_DESC(dev_rx_fifo_size, "Number of words in the Rx FIFO 16-32768");
module_param_named(dev_nperio_tx_fifo_size,
		   dwc_otg_module_params.dev_nperio_tx_fifo_size, int, 0444);
MODULE_PARM_DESC(dev_nperio_tx_fifo_size,
		 "Number of words in the non-periodic Tx FIFO 16-32768");
module_param_named(dev_perio_tx_fifo_size_1,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[0], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_1,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_2,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[1], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_2,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_3,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[2], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_3,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_4,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[3], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_4,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_5,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[4], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_5,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_6,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[5], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_6,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_7,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[6], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_7,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_8,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[7], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_8,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_9,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[8], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_9,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_10,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[9], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_10,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_11,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[10], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_11,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_12,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[11], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_12,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_13,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[12], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_13,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_14,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[13], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_14,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(dev_perio_tx_fifo_size_15,
		   dwc_otg_module_params.dev_perio_tx_fifo_size[14], int, 0444);
MODULE_PARM_DESC(dev_perio_tx_fifo_size_15,
		 "Number of words in the periodic Tx FIFO 4-768");
module_param_named(host_rx_fifo_size, dwc_otg_module_params.host_rx_fifo_size,
		   int, 0444);
MODULE_PARM_DESC(host_rx_fifo_size, "Number of words in the Rx FIFO 16-32768");
module_param_named(host_nperio_tx_fifo_size,
		   dwc_otg_module_params.host_nperio_tx_fifo_size, int, 0444);
MODULE_PARM_DESC(host_nperio_tx_fifo_size,
		 "Number of words in the non-periodic Tx FIFO 16-32768");
module_param_named(host_perio_tx_fifo_size,
		   dwc_otg_module_params.host_perio_tx_fifo_size, int, 0444);
MODULE_PARM_DESC(host_perio_tx_fifo_size,
		 "Number of words in the host periodic Tx FIFO 16-32768");
module_param_named(max_transfer_size, dwc_otg_module_params.max_transfer_size,
		   int, 0444);
/** @todo Set the max to 512K, modify checks */
MODULE_PARM_DESC(max_transfer_size,
		 "The maximum transfer size supported in bytes 2047-65535");
module_param_named(max_packet_count, dwc_otg_module_params.max_packet_count,
		   int, 0444);
MODULE_PARM_DESC(max_packet_count,
		 "The maximum number of packets in a transfer 15-511");
module_param_named(host_channels, dwc_otg_module_params.host_channels, int,
		   0444);
MODULE_PARM_DESC(host_channels,
		 "The number of host channel registers to use 1-16");
module_param_named(dev_endpoints, dwc_otg_module_params.dev_endpoints, int,
		   0444);
MODULE_PARM_DESC(dev_endpoints,
		 "The number of endpoints in addition to EP0 available for device mode 1-15");
module_param_named(phy_type, dwc_otg_module_params.phy_type, int, 0444);
MODULE_PARM_DESC(phy_type, "0=Reserved 1=UTMI+ 2=ULPI");
module_param_named(phy_utmi_width, dwc_otg_module_params.phy_utmi_width, int,
		   0444);
MODULE_PARM_DESC(phy_utmi_width, "Specifies the UTMI+ Data Width 8 or 16 bits");
module_param_named(phy_ulpi_ddr, dwc_otg_module_params.phy_ulpi_ddr, int, 0444);
MODULE_PARM_DESC(phy_ulpi_ddr,
		 "ULPI at double or single data rate 0=Single 1=Double");
module_param_named(phy_ulpi_ext_vbus, dwc_otg_module_params.phy_ulpi_ext_vbus,
		   int, 0444);
MODULE_PARM_DESC(phy_ulpi_ext_vbus,
		 "ULPI PHY using internal or external vbus 0=Internal");
module_param_named(i2c_enable, dwc_otg_module_params.i2c_enable, int, 0444);
MODULE_PARM_DESC(i2c_enable, "FS PHY Interface");
module_param_named(ulpi_fs_ls, dwc_otg_module_params.ulpi_fs_ls, int, 0444);
MODULE_PARM_DESC(ulpi_fs_ls, "ULPI PHY FS/LS mode only");
module_param_named(ts_dline, dwc_otg_module_params.ts_dline, int, 0444);
MODULE_PARM_DESC(ts_dline, "Term select Dline pulsing for all PHYs");
module_param_named(debug, g_dbg_lvl, int, 0444);
MODULE_PARM_DESC(debug, "");

module_param_named(en_multiple_tx_fifo,
		   dwc_otg_module_params.en_multiple_tx_fifo, int, 0444);
MODULE_PARM_DESC(en_multiple_tx_fifo,
		 "Dedicated Non Periodic Tx FIFOs 0=disabled 1=enabled");
module_param_named(dev_tx_fifo_size_1,
		   dwc_otg_module_params.dev_tx_fifo_size[0], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_1, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_2,
		   dwc_otg_module_params.dev_tx_fifo_size[1], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_2, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_3,
		   dwc_otg_module_params.dev_tx_fifo_size[2], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_3, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_4,
		   dwc_otg_module_params.dev_tx_fifo_size[3], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_4, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_5,
		   dwc_otg_module_params.dev_tx_fifo_size[4], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_5, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_6,
		   dwc_otg_module_params.dev_tx_fifo_size[5], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_6, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_7,
		   dwc_otg_module_params.dev_tx_fifo_size[6], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_7, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_8,
		   dwc_otg_module_params.dev_tx_fifo_size[7], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_8, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_9,
		   dwc_otg_module_params.dev_tx_fifo_size[8], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_9, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_10,
		   dwc_otg_module_params.dev_tx_fifo_size[9], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_10, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_11,
		   dwc_otg_module_params.dev_tx_fifo_size[10], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_11, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_12,
		   dwc_otg_module_params.dev_tx_fifo_size[11], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_12, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_13,
		   dwc_otg_module_params.dev_tx_fifo_size[12], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_13, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_14,
		   dwc_otg_module_params.dev_tx_fifo_size[13], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_14, "Number of words in the Tx FIFO 4-768");
module_param_named(dev_tx_fifo_size_15,
		   dwc_otg_module_params.dev_tx_fifo_size[14], int, 0444);
MODULE_PARM_DESC(dev_tx_fifo_size_15, "Number of words in the Tx FIFO 4-768");

module_param_named(thr_ctl, dwc_otg_module_params.thr_ctl, int, 0444);
MODULE_PARM_DESC(thr_ctl,
		 "Thresholding enable flag bit 0 - non ISO Tx thr., 1 - ISO Tx thr., 2 - Rx thr.- bit 0=disabled 1=enabled");
module_param_named(tx_thr_length, dwc_otg_module_params.tx_thr_length, int,
		   0444);
MODULE_PARM_DESC(tx_thr_length, "Tx Threshold length in 32 bit DWORDs");
module_param_named(rx_thr_length, dwc_otg_module_params.rx_thr_length, int,
		   0444);
MODULE_PARM_DESC(rx_thr_length, "Rx Threshold length in 32 bit DWORDs");

module_param_named(pti_enable, dwc_otg_module_params.pti_enable, int, 0444);
module_param_named(mpi_enable, dwc_otg_module_params.mpi_enable, int, 0444);
module_param_named(lpm_enable, dwc_otg_module_params.lpm_enable, int, 0444);
MODULE_PARM_DESC(lpm_enable, "LPM Enable 0=LPM Disabled 1=LPM Enabled");
module_param_named(ic_usb_cap, dwc_otg_module_params.ic_usb_cap, int, 0444);
MODULE_PARM_DESC(ic_usb_cap,
		 "IC_USB Capability 0=IC_USB Disabled 1=IC_USB Enabled");
module_param_named(ahb_thr_ratio, dwc_otg_module_params.ahb_thr_ratio, int,
		   0444);
MODULE_PARM_DESC(ahb_thr_ratio, "AHB Threshold Ratio");
module_param_named(power_down, dwc_otg_module_params.power_down, int, 0444);
MODULE_PARM_DESC(power_down, "Power Down Mode");
module_param_named(reload_ctl, dwc_otg_module_params.reload_ctl, int, 0444);
MODULE_PARM_DESC(reload_ctl, "HFIR Reload Control");
module_param_named(adp_enable, dwc_otg_module_params.adp_enable, int, 0444);
MODULE_PARM_DESC(adp_enable, "ADP Enable 0=ADP Disabled 1=ADP Enabled");
module_param_named(otg_ver, dwc_otg_module_params.otg_ver, int, 0444);
MODULE_PARM_DESC(otg_ver, "OTG revision supported 0=OTG 1.3 1=OTG 2.0");



/** @page "Module Parameters"
 *
 * The following parameters may be specified when starting the module.
 * These parameters define how the DWC_otg controller should be
 * configured. Parameter values are passed to the CIL initialization
 * function dwc_otg_cil_init
 *
 * Example: <code>modprobe dwc_otg speed=1 otg_cap=1</code>
 *

 <table>
 <tr><td>Parameter Name</td><td>Meaning</td></tr>

 <tr>
 <td>otg_cap</td>
 <td>Specifies the OTG capabilities. The driver will automatically detect the
 value for this parameter if none is specified.
 - 0: HNP and SRP capable (default, if available)
 - 1: SRP Only capable
 - 2: No HNP/SRP capable
 </td></tr>

 <tr>
 <td>dma_enable</td>
 <td>Specifies whether to use slave or DMA mode for accessing the data FIFOs.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: Slave
 - 1: DMA (default, if available)
 </td></tr>

 <tr>
 <td>dma_burst_size</td>
 <td>The DMA Burst size (applicable only for External DMA Mode).
 - Values: 1, 4, 8 16, 32, 64, 128, 256 (default 32)
 </td></tr>

 <tr>
 <td>speed</td>
 <td>Specifies the maximum speed of operation in host and device mode. The
 actual speed depends on the speed of the attached device and the value of
 phy_type.
 - 0: High Speed (default)
 - 1: Full Speed
 </td></tr>

 <tr>
 <td>host_support_fs_ls_low_power</td>
 <td>Specifies whether low power mode is supported when attached to a Full
 Speed or Low Speed device in host mode.
 - 0: Don't support low power mode (default)
 - 1: Support low power mode
 </td></tr>

 <tr>
 <td>host_ls_low_power_phy_clk</td>
 <td>Specifies the PHY clock rate in low power mode when connected to a Low
 Speed device in host mode. This parameter is applicable only if
 HOST_SUPPORT_FS_LS_LOW_POWER is enabled.
 - 0: 48 MHz (default)
 - 1: 6 MHz
 </td></tr>

 <tr>
 <td>enable_dynamic_fifo</td>
 <td> Specifies whether FIFOs may be resized by the driver software.
 - 0: Use cC FIFO size parameters
 - 1: Allow dynamic FIFO sizing (default)
 </td></tr>

 <tr>
 <td>data_fifo_size</td>
 <td>Total number of 4-byte words in the data FIFO memory. This memory
 includes the Rx FIFO, non-periodic Tx FIFO, and periodic Tx FIFOs.
 - Values: 32 to 32768 (default 8192)

 Note: The total FIFO memory depth in the FPGA configuration is 8192.
 </td></tr>

 <tr>
 <td>dev_rx_fifo_size</td>
 <td>Number of 4-byte words in the Rx FIFO in device mode when dynamic
 FIFO sizing is enabled.
 - Values: 16 to 32768 (default 1064)
 </td></tr>

 <tr>
 <td>dev_nperio_tx_fifo_size</td>
 <td>Number of 4-byte words in the non-periodic Tx FIFO in device mode when
 dynamic FIFO sizing is enabled.
 - Values: 16 to 32768 (default 1024)
 </td></tr>

 <tr>
 <td>dev_perio_tx_fifo_size_n (n = 1 to 15)</td>
 <td>Number of 4-byte words in each of the periodic Tx FIFOs in device mode
 when dynamic FIFO sizing is enabled.
 - Values: 4 to 768 (default 256)
 </td></tr>

 <tr>
 <td>host_rx_fifo_size</td>
 <td>Number of 4-byte words in the Rx FIFO in host mode when dynamic FIFO
 sizing is enabled.
 - Values: 16 to 32768 (default 1024)
 </td></tr>

 <tr>
 <td>host_nperio_tx_fifo_size</td>
 <td>Number of 4-byte words in the non-periodic Tx FIFO in host mode when
 dynamic FIFO sizing is enabled in the core.
 - Values: 16 to 32768 (default 1024)
 </td></tr>

 <tr>
 <td>host_perio_tx_fifo_size</td>
 <td>Number of 4-byte words in the host periodic Tx FIFO when dynamic FIFO
 sizing is enabled.
 - Values: 16 to 32768 (default 1024)
 </td></tr>

 <tr>
 <td>max_transfer_size</td>
 <td>The maximum transfer size supported in bytes.
 - Values: 2047 to 65,535 (default 65,535)
 </td></tr>

 <tr>
 <td>max_packet_count</td>
 <td>The maximum number of packets in a transfer.
 - Values: 15 to 511 (default 511)
 </td></tr>

 <tr>
 <td>host_channels</td>
 <td>The number of host channel registers to use.
 - Values: 1 to 16 (default 12)

 Note: The FPGA configuration supports a maximum of 12 host channels.
 </td></tr>

 <tr>
 <td>dev_endpoints</td>
 <td>The number of endpoints in addition to EP0 available for device mode
 operations.
 - Values: 1 to 15 (default 6 IN and OUT)

 Note: The FPGA configuration supports a maximum of 6 IN and OUT endpoints in
 addition to EP0.
 </td></tr>

 <tr>
 <td>phy_type</td>
 <td>Specifies the type of PHY interface to use. By default, the driver will
 automatically detect the phy_type.
 - 0: Full Speed
 - 1: UTMI+ (default, if available)
 - 2: ULPI
 </td></tr>

 <tr>
 <td>phy_utmi_width</td>
 <td>Specifies the UTMI+ Data Width. This parameter is applicable for a
 phy_type of UTMI+. Also, this parameter is applicable only if the
 OTG_HSPHY_WIDTH cC parameter was set to "8 and 16 bits", meaning that the
 core has been configured to work at either data path width.
 - Values: 8 or 16 bits (default 16)
 </td></tr>

 <tr>
 <td>phy_ulpi_ddr</td>
 <td>Specifies whether the ULPI operates at double or single data rate. This
 parameter is only applicable if phy_type is ULPI.
 - 0: single data rate ULPI interface with 8 bit wide data bus (default)
 - 1: double data rate ULPI interface with 4 bit wide data bus
 </td></tr>

 <tr>
 <td>i2c_enable</td>
 <td>Specifies whether to use the I2C interface for full speed PHY. This
 parameter is only applicable if PHY_TYPE is FS.
 - 0: Disabled (default)
 - 1: Enabled
 </td></tr>

 <tr>
 <td>ulpi_fs_ls</td>
 <td>Specifies whether to use ULPI FS/LS mode only.
 - 0: Disabled (default)
 - 1: Enabled
 </td></tr>

 <tr>
 <td>ts_dline</td>
 <td>Specifies whether term select D-Line pulsing for all PHYs is enabled.
 - 0: Disabled (default)
 - 1: Enabled
 </td></tr>
 
 <tr>
 <td>en_multiple_tx_fifo</td>
 <td>Specifies whether dedicatedto tx fifos are enabled for non periodic IN EPs.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: Disabled
 - 1: Enabled (default, if available)
 </td></tr>

 <tr>
 <td>dev_tx_fifo_size_n (n = 1 to 15)</td>
 <td>Number of 4-byte words in each of the Tx FIFOs in device mode
 when dynamic FIFO sizing is enabled.
 - Values: 4 to 768 (default 256)
 </td></tr>

 <tr>
 <td>tx_thr_length</td>
 <td>Transmit Threshold length in 32 bit double words
 - Values: 8 to 128 (default 64)
 </td></tr>

 <tr>
 <td>rx_thr_length</td>
 <td>Receive Threshold length in 32 bit double words
 - Values: 8 to 128 (default 64)
 </td></tr>

<tr>
 <td>thr_ctl</td>
 <td>Specifies whether to enable Thresholding for Device mode. Bits 0, 1, 2 of 
 this parmater specifies if thresholding is enabled for non-Iso Tx, Iso Tx and
 Rx transfers accordingly.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - Values: 0 to 7 (default 0)
 Bit values indicate:
 - 0: Thresholding disabled
 - 1: Thresholding enabled
 </td></tr>

<tr>
 <td>dma_desc_enable</td>
 <td>Specifies whether to enable Descriptor DMA mode.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: Descriptor DMA disabled
 - 1: Descriptor DMA (default, if available)
 </td></tr>

<tr>
 <td>mpi_enable</td>
 <td>Specifies whether to enable MPI enhancement mode.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: MPI disabled (default)
 - 1: MPI enable
 </td></tr>

<tr>
 <td>pti_enable</td>
 <td>Specifies whether to enable PTI enhancement support.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: PTI disabled (default)
 - 1: PTI enable
 </td></tr>

<tr>
 <td>lpm_enable</td>
 <td>Specifies whether to enable LPM support.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: LPM disabled
 - 1: LPM enable (default, if available)
 </td></tr>

<tr>
 <td>ic_usb_cap</td>
 <td>Specifies whether to enable IC_USB capability.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: IC_USB disabled (default, if available)
 - 1: IC_USB enable 
 </td></tr>

<tr>
 <td>ahb_thr_ratio</td>
 <td>Specifies AHB Threshold ratio.
 - Values: 0 to 3 (default 0)
 </td></tr>

<tr>
 <td>power_down</td>
 <td>Specifies Power Down(Hibernation) Mode.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: Power Down disabled (default)
 - 2: Power Down enabled
 </td></tr>
 
 <tr>
 <td>reload_ctl</td>
 <td>Specifies whether dynamic reloading of the HFIR register is allowed during
 run time. The driver will automatically detect the value for this parameter if
 none is specified. In case the HFIR value is reloaded when HFIR.RldCtrl == 1'b0
 the core might misbehave.
 - 0: Reload Control disabled (default)
 - 1: Reload Control enabled
 </td></tr>

<tr>
 <td>adp_enable</td>
 <td>Specifies whether ADP feature is enabled.
 The driver will automatically detect the value for this parameter if none is
 specified.
 - 0: ADP feature disabled (default)
 - 1: ADP feature enabled
 </td></tr>

  <tr>
 <td>otg_ver</td>
 <td>Specifies whether OTG is performing as USB OTG Revision 2.0 or Revision 1.3
 USB OTG device.
 - 0: OTG 2.0 support disabled (default)
 - 1: OTG 2.0 support enabled 
 </td></tr>

*/
