/**
******************************************************************************
@file   /home/jenkins/builds/workspace/ISP_PKG/build/CI/felix/regdefs2.7/regdefs//registers/fields_gasket_parallel.h

@brief  FIELDS_GASKET_PARALLEL_H registers and fields property array (name, offset, etc)

@author <Autogenerated>
		<b>Copyright 2005 by Imagination Technologies Limited.</b>
		All rights reserved.  No part of this software, either
		material or conceptual may be copied or distributed,
		transmitted, transcribed, stored in a retrieval system
		or translated into any human or computer language in any
		form by any means, electronic, mechanical, manual or
		other-wise, or disclosed to third parties without the
		express written permission of Imagination Technologies
		Limited, Unit 8, HomePark Industrial Estate,
		King's Langley, Hertfordshire, WD4 8LZ, U.K.


<b>Description:</b>
		Defines the FieldDefnListEl structure if not already defined (FIELD_DEFN_LIST_EL).


		Defines an array of FieldDefnListEl that contains all registers and fields information (non-sorted).
<b>Platform:</b> ?
@Version 1.0

******************************************************************************/

#if !defined (__FIELDS_GASKET_PARALLEL_H__)
#define __FIELDS_GASKET_PARALLEL_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FIELD_DEFN_LIST_EL
#define FIELD_DEFN_LIST_EL
/** @brief Register information structure */
typedef struct _FieldDefnListEl
{
	const IMG_CHAR*		szRegName; /**< @brief Register's name */
	const IMG_CHAR*		szFieldName; /**< @brief Field's name */
	IMG_UINT32		ui32RegOffset; /**< @brief Register's offset in Bytes in the register bank */
	IMG_UINT32		ui32FieldStart; /**< @brief Field's starting offset in bits (from ui32RegOffset) */
	IMG_UINT32		ui32FieldEnd; /**< @brief Field's ending offset in bits (from ui32RegOffset) */
	IMG_UINT32		ui32FieldDefault; /**< @brief Field's default value */
} FieldDefnListEl;
#endif // FIELD_DEFN_LIST_EL


#define FELIX_GAS_PARA_FIELDS FieldDefnListEl felix_gas_para_fields[] = {\
	{"GPIO_IN", "GPIO_IN", 0x00000000, 0, 15, 0x0},\
	{"GPIO_OUT", "GPIO_OUT", 0x00000004, 0, 7, 0x0},\
	{"GASKET_INTER_ENABLE", "GPIO_IN_WRITE_EN", 0x00000008, 0, 0, 0x0},\
	{"GASKET_INTER_CLEAR", "GPIO_IN_WRITE_CLR", 0x0000000C, 0, 0, 0x0},\
	{"GASKET_INTER_STATUS", "GPIO_IN_WRITE", 0x00000010, 0, 0, 0x0},\
	{"GASKET_CONTROL", "GASKET_RESET", 0x00000014, 2, 2, 0x0},\
	{"GASKET_CONTROL", "GASKET_CLEAR_CNT", 0x00000014, 1, 1, 0x0},\
	{"GASKET_CONTROL", "GASKET_ENABLE", 0x00000014, 0, 0, 0x0},\
	{"GASKET_FORMAT", "PARALLEL_H_SYNC_POLARITY", 0x00000018, 1, 1, 0x1},\
	{"GASKET_FORMAT", "PARALLEL_V_SYNC_POLARITY", 0x00000018, 0, 0, 0x1},\
	{"GASKET_FRAME_SIZE", "PARALLEL_FRAME_HEIGHT", 0x0000001C, 16, 28, 0x0},\
	{"GASKET_FRAME_SIZE", "PARALLEL_FRAME_WIDTH", 0x0000001C, 0, 12, 0x0},\
	{"GASKET_FRAME_CNT", "GASKET_FRAME_CNT", 0x00000080, 0, 31, 0x0},\
	{"GASKET_CRC", "GASKET_CRC", 0x00000100, 0, 31, 0x0},\
};

#define FELIX_GAS_PARA_ADD_FIELD_DEFNS(DefnSet, Memspace, MemspaceID) \
	{ \
		int i; \
		FELIX_GAS_PARA_FIELDS; \
		for (i = 0; i < (sizeof(felix_gas_para_fields)/sizeof(*felix_gas_para_fields)); i++) \
		{ \
			addFieldDefn(DefnSet, Memspace, MemspaceID, \
				felix_gas_para_fields[i].szRegName, \
				felix_gas_para_fields[i].szFieldName, \
				felix_gas_para_fields[i].ui32RegOffset, \
				felix_gas_para_fields[i].ui32FieldStart, \
				felix_gas_para_fields[i].ui32FieldEnd, \
				felix_gas_para_fields[i].ui32FieldDefault); \
		} \
	}




#ifdef __cplusplus
}
#endif

#endif /* __FIELDS_GASKET_PARALLEL_H__ */
