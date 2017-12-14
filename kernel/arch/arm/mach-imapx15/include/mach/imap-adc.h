#ifndef __IMAP_ADC_H__
#define __IMAP_ADC_H__

#define TSC_CNTL		(0x00)
#define TSC_EVTPAR0		(0x04)
#define TSC_EVTPAR1		(0x08)
#define TSC_EVTPAR2		(0x0C)
#define TSC_EVTPAR3		(0x10)
#define TSC_EVTPAR4		(0x14)
#define TSC_EVTPAR5		(0x18)
#define TSC_EVTPAR6		(0x1C)
#define TSC_EVTPAR7		(0x20)
#define TSC_PP_PAR		(0x24)
#define TSC_FIFO_TH		(0x28)
#define TSC_INT_EN		(0x2C)
#define TSC_INT_PAR		(0x30)
#define TSC_INT_MASK		(0x34)
#define TSC_PRES_SEL		(0x38)
#define TSC_INT_CLEAR 		(0x3C)
#define TSC_PPOUT_0 		(0x40)
#define TSC_PPOUT_1 		(0x44)
#define TSC_PPOUT_2 		(0x48)
#define TSC_PPOUT_3 		(0x4C)
#define TSC_PPOUT_4 		(0x50)
#define TSC_PPOUT_5 		(0x54)
#define TSC_PPOUT_6 		(0x58)
#define TSC_PPOUT_7 		(0x5C)
#define TSC_PPOUT_8 		(0x60)
#define TSC_PPOUT_9 		(0x64)
#define TSC_PPOUT_10 		(0x68)
#define TSC_PPOUT_11 		(0x70)
#define TSC_PPOUT_12 		(0x74)
#define TSC_PPOUT_13 		(0x78)
#define TSC_PPOUT_14 		(0x7C)
#define TSC_PPOUT_15 		(0x80)
#define TSC_PPOUT_16 		(0x84)
#define TSC_PPOUT_17 		(0x88)
#define TSC_PPOUT_18 		(0x8C)
#define TSC_INT_PAR1 		(0x90)
#define TSC_INT_PAR2 		(0x94)
#define TSC_INT_PAR3 		(0x98)
#define TSC_INT_PAR4 		(0x9C)
#define TSC_INT_PAR5 		(0x100)
#define TSC_INT_PAR6 		(0x104)
#define TSC_INT_PAR7 		(0x108)
#define TSC_INT_PAR8 		(0x10C)
#define TSC_INT_PAR9 		(0x110)
#define TSC_INT_PAR10 		(0x114)
#define TSC_INT_PAR11 		(0x118)
#define TSC_MEM_BASE_ADDR	(0x400)
#define TSC_DMA_BASE_ADDR	(0x800)
extern void __imapx_register_batt(int (*func)(void));

#endif
