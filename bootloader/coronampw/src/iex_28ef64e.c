/*************************************************
 * this file is auto generated by gen-entry.sh
 * do not edit !
 *
 * 2017年 08月 30日 星期三 14:29:26 CST
 ************************************************/

#include <asm-arm/io.h>
#include "preloader.h"

#define __F(x) (void *)(x)

struct irom_export irf_coronampw = {

    .init_timer          = __F(0x0000896c),
    .init_serial         = __F(0x00008908),
    .printf              = __F(0x0000d0b0),
    .udelay              = __F(0x00008a18),
    .memcpy              = __F(0x000013d8),
    .strnlen             = __F(0x00001390),
    .sprintf             = __F(0x0000cef8),
    .vs_reset            = __F(0x00004b6c),
    .vs_read             = __F(0x000050c0),
    .vs_write            = __F(0x00004ba8),
    .vs_erase            = __F(0x00004c00),
    .vs_isbad            = __F(0x00004c3c),
    .vs_scrub            = __F(0x00004c78),
    .vs_special          = __F(0x00004cb4),
    .vs_assign_by_name   = __F(0x00004fbc),
    .vs_assign_by_id     = __F(0x00004d4c),
    .vs_device_id        = __F(0x00004f6c),
    .vs_is_assigned      = __F(0x00004ac8),
    .vs_align            = __F(0x00004cf0),
    .vs_is_device        = __F(0x0000505c),
    .vs_is_opt_available = __F(0x00004ae0),
    .vs_device_name      = __F(0x00004ee0),
    .boot_device         = __F(0x00000604),
    .isi_check_header    = __F(0x00001978),
    .cdbg_shell          = __F(0x0000624c),
    .simple_strtol       = __F(0x0000c180),
    .strncmp             = __F(0x000012f4),
    .strncpy             = __F(0x00001230),
    .cdbg_log_toggle     = __F(0x000060e8),
    .module_set_clock    = __F(0x00000710),
    .module_get_clock    = __F(0x00001078),
    .module_enable       = __F(0x0000073c),
    .set_pll             = __F(0x00000620),
    .memset              = __F(0x000013b8),
    .ss_jtag_en          = __F(0x0000f090),
    .malloc              = __F(0x0000156c),
    .free                = __F(0x0000170c),
    .pads_chmod          = __F(0x00000bb8),
    .pads_pull           = __F(0x00000cf0),
    .get_xom             = __F(0x0000058c),
    .hash_init           = __F(0x00005804),
    .hash_data           = __F(0x00005770),
    .hash_value          = __F(0x00005700),
    .get_timer           = __F(0x00008a48),
};

