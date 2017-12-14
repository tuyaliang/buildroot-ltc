/*************************************************************************
    > File Name: drivers/infotm/common/adc/adc-ip6303-keys.c
    > Author: tsico
    > Mail: can.chai@infotm.com 
    > Created Time: 2017年10月25日 星期三 17时36分45秒
 ************************************************************************/
#include <linux/device.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/irq.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/input.h>
#include <linux/workqueue.h>
#include <linux/adc_keys.h>
#include <linux/adc.h>
#include <mach/ip6303.h>
#include <mach/imap-rtc.h>
#include <asm/io.h>

struct adc_button_data {
	unsigned int code;
	int chan;
	int ref_val;
	bool state;
	char *desc;
};

struct adc_keys_drvdata {
	const struct adc_keys_platform_data *pdata;
	struct input_dev *input;
	struct adc_device *adc;
	unsigned long  adc_chan_bitmap;
	int nkeys;
	int debounce_period;
	int debounce_delay;
	int key_cal_val;
	bool key_pressed;
	int id;
	int irq;
	int irq_watermark;
	struct delayed_work	work;
	struct adc_button_data bdata[MAX_ADC_KEYS_NUM];
};

static int ip6303_adckey_irq_enable(int en)
{
	uint8_t val;
	void __iomem *rtc_base = IO_ADDRESS(SYSMGR_RTC_BASE);
	val = readl(rtc_base + 0x5c);
	if (en)
		val |= 1 << 0;
	else
		val &= ~(1 << 0);
	writel(val, rtc_base + 0x5c);

	return 0;
}

static int ip6303_pwrkey_irq_clr(void)
{
	uint8_t val; 
	void __iomem *rtc_base = IO_ADDRESS(SYSMGR_RTC_BASE);
	val = readl(rtc_base + 0x8);
	if (val & (1 << 3))
		writel((1 << 3), rtc_base + 0x4); 
	return 0;
}

static int ip6303_adckey_set_dir(int dir)
{
	uint8_t val;
	void __iomem *rtc_base = IO_ADDRESS(SYSMGR_RTC_BASE);
	val = readl(rtc_base + 0x4c);
	if (dir)
		val |= 1 << 0;
	else
		val &= ~(1 << 0);
	writel(val, rtc_base + 0x4c);
	return 0;
}

static int ip6303_adckey_set_pulldown(int en)
{
	uint8_t val;
	void __iomem *rtc_base = IO_ADDRESS(SYSMGR_RTC_BASE);
	val = readl(rtc_base + 0x54);
	if (en)
		val |= 1 << 0;
	else
		val &= ~(1 << 0);
	writel(val, rtc_base + 0x54);
	return 0;
}

static int ip6303_adckey_set_polarity(int polar)
{
	uint8_t val;
	void __iomem *rtc_base = IO_ADDRESS(SYSMGR_RTC_BASE);
	val = readl(rtc_base + 0x5c);
	if (polar) 
		val |= 1 << 4;
	else
		val &= ~(1 << 4);
	writel(val, rtc_base + 0x5c);
	return 0;
}

static int ip6303_adckey_hw_init(void)
{
	/* disable rtc gpio0 irq */
	ip6303_adckey_irq_enable(0);
	/* set rtc gpio0 to input */
	ip6303_adckey_set_dir(1);
	/* rtc gpio0 pulldown enable */
	ip6303_adckey_set_pulldown(0); 
	/* high valid */
	ip6303_adckey_set_polarity(0);
	/* enable rtc gpio0 irq */
	ip6303_adckey_irq_enable(1);
}

static int ip6303_adc_find_keyindex_bysample(struct adc_keys_drvdata *ddata, int val) {
	int i , ret = -1;
	for (i = 0; i < ddata->nkeys; i++) {
		if((val > (ddata->bdata[i].ref_val - ddata->key_cal_val))
				&& (val < (ddata->bdata[i].ref_val + ddata->key_cal_val))) { 
			ret = i;
			break;
		}
	}
	return ret;
}


static void ip6303_adc_key_worker(struct work_struct *work) {
	struct adc_keys_drvdata *ddata = 
		container_of(to_delayed_work(work), struct adc_keys_drvdata, work);
	unsigned int val, val1;
	uint8_t key_index, ret;
	bool debounced = false;
	int i;
	
	if(adc_get_irq_state(ddata->adc) & 0x2) {
		ret = adc_read_raw(ddata->adc, &val, &val1);
		if(ret <= 0xdf){
			if(!ddata->key_pressed) {
				key_index = ip6303_adc_find_keyindex_bysample(ddata, ret);
				if ( key_index == -1) {
					debounced = true;
					goto out;
				}
				ddata->bdata[key_index].state = true;
				ddata->key_pressed = true;
				input_event(ddata->input, EV_KEY, ddata->bdata[key_index].code, 1);
				input_sync(ddata->input);
				pr_info("[adc-key] down: %s\n", ddata->bdata[key_index].desc);
			}
		}
	}else {
			ddata->key_pressed = false;
			for (i = 0; i < ddata->nkeys; i++ )
				if (ddata->bdata[i].state == true) {
					ddata->bdata[i].state = false;
					input_event(ddata->input, EV_KEY, ddata->bdata[i].code, 0);
					input_sync(ddata->input);
					pr_info("[adc-key] up: %s\n", ddata->bdata[i].desc);
				}

		}
	adc_clear_irq(ddata->adc);

out:
	if(ddata->key_pressed || debounced)
		schedule_delayed_work(&ddata->work, msecs_to_jiffies(10));
	else
		ip6303_adckey_irq_enable(1);
	
	return;
}

static irqreturn_t ip6303_adc_keys_isr(int irq, void *priv) {
	struct adc_keys_drvdata *ddata = priv;
	int irqstate;
	unsigned int val, val1;
	uint8_t ret;

	adc_disable(ddata->adc);
	/*disable and clear RTC INT*/
	ip6303_adckey_irq_enable(0);
	ip6303_pwrkey_irq_clr();
	schedule_delayed_work(&ddata->work, msecs_to_jiffies(ddata->debounce_delay));
	return IRQ_HANDLED;
}


static int ip6303_adc_keys_probe(struct platform_device *pdev) {
	const struct adc_keys_platform_data *pdata = dev_get_platdata(&pdev->dev);
	struct adc_keys_drvdata *ddata;
	struct input_dev *input;
	struct adc_request adc_req;
	int i, ret;

	if (pdata->nbuttons <= 0 || pdata->nbuttons > MAX_ADC_KEYS_NUM)
		goto FAIL0;

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if(!ddata)
		goto FAIL0;

	input = input_allocate_device();
	if(!input)
		goto FAIL1;

	ddata->pdata = pdata;
	ddata->input = input;
	ddata->nkeys = pdata->nbuttons;
	ddata->debounce_period = 30;
	ddata->debounce_delay = 50;
	ddata->key_cal_val = 8;
	ddata->irq_watermark = 0;
	ddata->key_pressed = false;
	

	platform_set_drvdata(pdev, ddata);
	input_set_drvdata(input, ddata);
	input->name = dev_name(&pdev->dev);
	input->dev.parent = &pdev->dev;
	
	for (i = 0; i < pdata->nbuttons; i++) {
		const struct adc_keys_button *button = &pdata->buttons[i];
		struct adc_button_data  *bdata = &ddata->bdata[i]; 
		bdata->code = button->code;
		bdata->chan = button->chan;
		bdata->ref_val = button->ref_val; // 41 is a magic number which is confirmed by CSL@2009
		bdata->desc = button->desc;
		bdata->state = false;
		ddata->adc_chan_bitmap |= (0x1 << button->chan); 
		input_set_capability(input, EV_KEY, bdata->code);
	}

	/*
	* TODO we only support all keys share the same adc channel
     */
	ddata->id = ddata->bdata[0].chan;
	ddata->irq_watermark = 0;

	adc_req.chip_name = "ip6303-adc";
	adc_req.id = ddata->id;
	adc_req.mode = ADC_DEV_IRQ_SAMPLE;
	adc_req.label = "adc-keys"; 
	ddata->adc = adc_request(&adc_req);
	if(!ddata->adc || IS_ERR(ddata->adc)) {
		pr_err("adc-keys can't request adc channel%d, error: %d\n", adc_req.id, PTR_ERR(ddata->adc));
		goto FAIL2;
	}
	
	ddata->irq = ddata->adc->irq;
	ret = devm_request_irq(&pdev->dev, ddata->irq, ip6303_adc_keys_isr,
			IRQF_SHARED | IRQF_DISABLED | IRQF_ONESHOT,
			dev_name(&pdev->dev), ddata);
	if(0 > ret) {
		dev_err(&(pdev->dev), "fail to install IRQ:%d\n", ret);
		goto FAIL3;
	}


	INIT_DELAYED_WORK(&ddata->work, ip6303_adc_key_worker);

	ret = input_register_device(input);
	if (ret) {
		pr_err("Unable to register adc-key input device\n");
		goto FAIL3;
	}
	ip6303_adckey_hw_init();
	adc_set_irq_watermark(ddata->adc, ddata->irq_watermark);
	pr_info("[adc-key] %s succesed.\n", __func__);
	return 0;
FAIL3:
	adc_free(ddata->adc);
FAIL2:	
	input_free_device(input);
FAIL1:
	devm_kfree(&pdev->dev, ddata);
FAIL0:
	pr_err("[adc-key] %s failed.\n", __func__);
	return -1;
}

static int ip6303_adc_keys_remove(struct platform_device *pdev) {
	struct adc_keys_drvdata *ddata = platform_get_drvdata(pdev);
	adc_free(ddata->adc);
	input_free_device(ddata->input);
	devm_kfree(&pdev->dev, ddata);
	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int ip6303_adc_keys_suspend(struct device *dev) {
	return 0;
}

static int ip6303_adc_keys_resume(struct device *dev) {
	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(ip6303_adc_keys_pm_ops, ip6303_adc_keys_suspend, ip6303_adc_keys_resume);

static struct platform_driver ip6303_adc_keys_device_driver = {
	.probe          = ip6303_adc_keys_probe,
	.remove         = ip6303_adc_keys_remove,
	.driver		= {
		.name = "ip6303-adc-keys",
		.owner  = THIS_MODULE,
		.pm     = &ip6303_adc_keys_pm_ops,
	},
};

static int __init ip6303_adc_keys_init(void) {
	return platform_driver_register(&ip6303_adc_keys_device_driver);
}

static void __exit ip6303_adc_keys_exit(void) {
	platform_driver_unregister(&ip6303_adc_keys_device_driver);
}

late_initcall(ip6303_adc_keys_init);
module_exit(ip6303_adc_keys_exit);

MODULE_AUTHOR("Infotm-PS");
MODULE_DESCRIPTION("ADC Key Driver");
MODULE_LICENSE("GPL");
