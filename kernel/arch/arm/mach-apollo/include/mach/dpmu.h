
#ifndef _IMAP_DPMU_H_
#define	_IMAP_DPMU_H_

//#define DPMU_DEBUG

#define belt_dbg(x...)

#define DPMU_MAJOR 172
#define DPMU_MAGIC 'd'
#define DPMU_IOCMAX 10
#define DPMU_NAME "dpmu"
#define DPMU_NODE "/dev/dpmu"

#define	DPMU_BASE	IO_ADDRESS(0x21a0c000)

#define DPMU_EN			(DPMU_BASE + 0x0)
#define DPMU_SPRD		(DPMU_BASE + 0x04)		
#define DPMU_INTE		(DPMU_BASE + 0x08)
#define DPMU_INT		(DPMU_BASE + 0x0c)
#define CPU_IDMSK0		(DPMU_BASE + 0x10)
#define CPU_IDCMP0		(DPMU_BASE + 0x14)
#define BUS1_IDMSK		(DPMU_BASE + 0x20)
#define BUS1_IDCMP		(DPMU_BASE + 0x24)
#define BUS3_IDMSK		(DPMU_BASE + 0x30)
#define BUS3_IDCMP		(DPMU_BASE + 0x34)
#define BUS4_IDMSK		(DPMU_BASE + 0x40)
#define BUS4_IDCMP		(DPMU_BASE + 0x44)
#define BUS6_IDMSK		(DPMU_BASE + 0x50)
#define BUS6_IDCMP		(DPMU_BASE + 0x54)
#define CPU_IDMSK1		(DPMU_BASE + 0x60)
#define CPU_IDCMP1		(DPMU_BASE + 0x64)
#define CPU_WBSTC0		(DPMU_BASE + 0x80)
#define CPU_RBSTC0		(DPMU_BASE + 0x84)
#define CPU_WDATC0		(DPMU_BASE + 0x88)
#define CPU_RDATC0		(DPMU_BASE + 0x8c)
#define BUS1_WBSTC		(DPMU_BASE + 0x90)
#define BUS1_RBSTC		(DPMU_BASE + 0x94)
#define BUS1_WDATC		(DPMU_BASE + 0x98)
#define BUS1_RDATC		(DPMU_BASE + 0x9c)
#define BUS3_WBSTC		(DPMU_BASE + 0xa0)
#define BUS3_RBSTC		(DPMU_BASE + 0xa4)
#define BUS3_WDATC		(DPMU_BASE + 0xa8)
#define BUS3_RDATC		(DPMU_BASE + 0xac)
#define BUS4_WBSTC		(DPMU_BASE + 0xb0)		
#define BUS4_RBSTC		(DPMU_BASE + 0xb4)
#define BUS4_WDATC		(DPMU_BASE + 0xb8)
#define BUS4_RDATC		(DPMU_BASE + 0xbc)
#define BUS6_WBSTC		(DPMU_BASE + 0xc0)
#define BUS6_RBSTC		(DPMU_BASE + 0xc4)
#define BUS6_WDATC		(DPMU_BASE + 0xc8)
#define BUS6_RDATC		(DPMU_BASE + 0xcc)
#define CPU_WBSTC1		(DPMU_BASE + 0xd0)
#define CPU_RBSTC1		(DPMU_BASE + 0xd4)
#define CPU_WDATC1		(DPMU_BASE + 0xd8)
#define CPU_RDATC1		(DPMU_BASE + 0xdc)
#define DRAM_WCNT		(DPMU_BASE + 0xe0)
#define DRAM_RCNT		(DPMU_BASE + 0xe4)

#define DPMU_IRQ	248

#define ID_0		0x0	//all not mask
#define ID_1		0x1
#define ID_2		0x2
#define ID_3		0x3
#define ID_4		0x4
#define ID_5		0x5
#define ID_6		0x6
#define ID_7		0x7
#define ID_ALL		0x0
#define ID_NMSK		0x1
#define ID_NCMP		0x0
#define ID_CMP0		0x0
#define ID_CMP1		0x1
#define ID_CMP2		0x2
#define ID_CMP3		0x3
#define ID_CMP4		0x4
#define ID_CMP5		0x5
#define ID_CMP6		0x6
#define ID_CMP7		0x6
#define BUS1_NUM	3
#define BUS3_NUM	4
#define BUS4_NUM	4
#define BUS6_NUM	7
#define MSK_L		0x300
#define MSK_H		0xe0
#define CMP_L0		0x0
#define CMP_L1		0x100
#define CMP_L2		0x200
#define CMP_M3		0x300
#define CMP_H0		0x0
#define CMP_H1		0x20
#define CMP_H2		0x40
#define CMP_H3		0x60
#define CMP_H4		0x80
#define CMP_H5		0xa0
#define CMP_H6		0xc0
#endif /* _IMAP_DPMU_H_ */

