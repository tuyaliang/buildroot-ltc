/**
******************************************************************************
@file   /home/jenkins/builds/workspace/ISP_PKG/build/CI/felix/regdefs2.7/regdefs//registers/fields_core.h

@brief  FIELDS_CORE_H registers and fields property array (name, offset, etc)

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

#if !defined (__FIELDS_CORE_H__)
#define __FIELDS_CORE_H__

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


#define FELIX_CORE_FIELDS FieldDefnListEl felix_core_fields[] = {\
	{"CORE_ID_PADDING_0", "CORE_ID_RESERVED_0", 0x00000008, 0, 31, 0x0},\
	{"CORE_ID_PADDING_1", "CORE_ID_RESERVED_1", 0x0000000C, 0, 31, 0x0},\
	{"CORE_REVISION_PADDING_0", "CORE_REVISION_PAD_RESERVED_0", 0x00000018, 0, 31, 0x0},\
	{"CORE_REVISION_PADDING_1", "CORE_REVISION_PAD_RESERVED_1", 0x0000001C, 0, 31, 0x0},\
	{"CORE_REV_FIELD1_PADDING_0", "CORE_REV_FIELD1_RESERVED_0", 0x00000024, 0, 31, 0x0},\
	{"CORE_REV_FIELD1_PADDING_1", "CORE_REV_FIELD1_RESERVED_1", 0x00000028, 0, 31, 0x0},\
	{"CORE_REV_FIELD1_PADDING_2", "CORE_REV_FIELD1_RESERVED_2", 0x0000002C, 0, 31, 0x0},\
	{"DESIGNER_REV_FIELD4_0", "DESIGNER_REV_FIELD4_RESERVED_0", 0x00000044, 0, 31, 0x0},\
	{"DESIGNER_REV_FIELD4_1", "DESIGNER_REV_FIELD4_RESERVED_1", 0x00000048, 0, 31, 0x0},\
	{"DESIGNER_REV_FIELD4_2", "DESIGNER_REV_FIELD4_RESERVED_2", 0x0000004C, 0, 31, 0x0},\
	{"DESIGNER_REV_FIELD5_0", "IMGR_PORT_WIDTH_0", 0x00000120, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_0", "GASKET_TYPE_0", 0x00000120, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_0", "GASKET_BIT_DEPTH_0", 0x00000120, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_0", "GASKET_MAX_FRAME_WIDTH_0", 0x00000120, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_1", "IMGR_PORT_WIDTH_1", 0x00000124, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_1", "GASKET_TYPE_1", 0x00000124, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_1", "GASKET_BIT_DEPTH_1", 0x00000124, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_1", "GASKET_MAX_FRAME_WIDTH_1", 0x00000124, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_2", "IMGR_PORT_WIDTH_2", 0x00000128, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_2", "GASKET_TYPE_2", 0x00000128, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_2", "GASKET_BIT_DEPTH_2", 0x00000128, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_2", "GASKET_MAX_FRAME_WIDTH_2", 0x00000128, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_3", "IMGR_PORT_WIDTH_3", 0x0000012C, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_3", "GASKET_TYPE_3", 0x0000012C, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_3", "GASKET_BIT_DEPTH_3", 0x0000012C, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_3", "GASKET_MAX_FRAME_WIDTH_3", 0x0000012C, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_4", "IMGR_PORT_WIDTH_4", 0x00000130, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_4", "GASKET_TYPE_4", 0x00000130, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_4", "GASKET_BIT_DEPTH_4", 0x00000130, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_4", "GASKET_MAX_FRAME_WIDTH_4", 0x00000130, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_5", "IMGR_PORT_WIDTH_5", 0x00000134, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_5", "GASKET_TYPE_5", 0x00000134, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_5", "GASKET_BIT_DEPTH_5", 0x00000134, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_5", "GASKET_MAX_FRAME_WIDTH_5", 0x00000134, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_6", "IMGR_PORT_WIDTH_6", 0x00000138, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_6", "GASKET_TYPE_6", 0x00000138, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_6", "GASKET_BIT_DEPTH_6", 0x00000138, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_6", "GASKET_MAX_FRAME_WIDTH_6", 0x00000138, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_7", "IMGR_PORT_WIDTH_7", 0x0000013C, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_7", "GASKET_TYPE_7", 0x0000013C, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_7", "GASKET_BIT_DEPTH_7", 0x0000013C, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_7", "GASKET_MAX_FRAME_WIDTH_7", 0x0000013C, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_8", "IMGR_PORT_WIDTH_8", 0x00000140, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_8", "GASKET_TYPE_8", 0x00000140, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_8", "GASKET_BIT_DEPTH_8", 0x00000140, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_8", "GASKET_MAX_FRAME_WIDTH_8", 0x00000140, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_9", "IMGR_PORT_WIDTH_9", 0x00000144, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_9", "GASKET_TYPE_9", 0x00000144, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_9", "GASKET_BIT_DEPTH_9", 0x00000144, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_9", "GASKET_MAX_FRAME_WIDTH_9", 0x00000144, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_10", "IMGR_PORT_WIDTH_10", 0x00000148, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_10", "GASKET_TYPE_10", 0x00000148, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_10", "GASKET_BIT_DEPTH_10", 0x00000148, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_10", "GASKET_MAX_FRAME_WIDTH_10", 0x00000148, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_11", "IMGR_PORT_WIDTH_11", 0x0000014C, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_11", "GASKET_TYPE_11", 0x0000014C, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_11", "GASKET_BIT_DEPTH_11", 0x0000014C, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_11", "GASKET_MAX_FRAME_WIDTH_11", 0x0000014C, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_12", "IMGR_PORT_WIDTH_12", 0x00000150, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_12", "GASKET_TYPE_12", 0x00000150, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_12", "GASKET_BIT_DEPTH_12", 0x00000150, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_12", "GASKET_MAX_FRAME_WIDTH_12", 0x00000150, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_13", "IMGR_PORT_WIDTH_13", 0x00000154, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_13", "GASKET_TYPE_13", 0x00000154, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_13", "GASKET_BIT_DEPTH_13", 0x00000154, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_13", "GASKET_MAX_FRAME_WIDTH_13", 0x00000154, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_14", "IMGR_PORT_WIDTH_14", 0x00000158, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_14", "GASKET_TYPE_14", 0x00000158, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_14", "GASKET_BIT_DEPTH_14", 0x00000158, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_14", "GASKET_MAX_FRAME_WIDTH_14", 0x00000158, 0, 15, 0x0},\
	{"DESIGNER_REV_FIELD5_15", "IMGR_PORT_WIDTH_15", 0x0000015C, 22, 25, 0x0},\
	{"DESIGNER_REV_FIELD5_15", "GASKET_TYPE_15", 0x0000015C, 20, 21, 0x0},\
	{"DESIGNER_REV_FIELD5_15", "GASKET_BIT_DEPTH_15", 0x0000015C, 16, 19, 0x0},\
	{"DESIGNER_REV_FIELD5_15", "GASKET_MAX_FRAME_WIDTH_15", 0x0000015C, 0, 15, 0x0},\
	{"DEBUG_DRIVER_INFO_0", "DEBUG_DRIVER_ADDR_0", 0x00000300, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_1", "DEBUG_DRIVER_ADDR_1", 0x00000304, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_2", "DEBUG_DRIVER_ADDR_2", 0x00000308, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_3", "DEBUG_DRIVER_ADDR_3", 0x0000030C, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_4", "DEBUG_DRIVER_ADDR_4", 0x00000310, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_5", "DEBUG_DRIVER_ADDR_5", 0x00000314, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_6", "DEBUG_DRIVER_ADDR_6", 0x00000318, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_7", "DEBUG_DRIVER_ADDR_7", 0x0000031C, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_8", "DEBUG_DRIVER_ADDR_8", 0x00000320, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_9", "DEBUG_DRIVER_ADDR_9", 0x00000324, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_10", "DEBUG_DRIVER_ADDR_10", 0x00000328, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_11", "DEBUG_DRIVER_ADDR_11", 0x0000032C, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_12", "DEBUG_DRIVER_ADDR_12", 0x00000330, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_13", "DEBUG_DRIVER_ADDR_13", 0x00000334, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_14", "DEBUG_DRIVER_ADDR_14", 0x00000338, 0, 31, 0x0},\
	{"DEBUG_DRIVER_INFO_15", "DEBUG_DRIVER_ADDR_15", 0x0000033C, 0, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_0", "MMU_CMD_STALL_ENABLE_0", 0x00000600, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_0", "MMU_CMD_SEED_GAP_0", 0x00000600, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_0", "MMU_CMD_SEED_BURST_0", 0x00000600, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_0", "MMU_CMD_MAX_GAP_0", 0x00000600, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_0", "MMU_CMD_MAX_BURST_0", 0x00000600, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_1", "MMU_CMD_STALL_ENABLE_1", 0x00000604, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_1", "MMU_CMD_SEED_GAP_1", 0x00000604, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_1", "MMU_CMD_SEED_BURST_1", 0x00000604, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_1", "MMU_CMD_MAX_GAP_1", 0x00000604, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_1", "MMU_CMD_MAX_BURST_1", 0x00000604, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_2", "MMU_CMD_STALL_ENABLE_2", 0x00000608, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_2", "MMU_CMD_SEED_GAP_2", 0x00000608, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_2", "MMU_CMD_SEED_BURST_2", 0x00000608, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_2", "MMU_CMD_MAX_GAP_2", 0x00000608, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_2", "MMU_CMD_MAX_BURST_2", 0x00000608, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_3", "MMU_CMD_STALL_ENABLE_3", 0x0000060C, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_3", "MMU_CMD_SEED_GAP_3", 0x0000060C, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_3", "MMU_CMD_SEED_BURST_3", 0x0000060C, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_3", "MMU_CMD_MAX_GAP_3", 0x0000060C, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_3", "MMU_CMD_MAX_BURST_3", 0x0000060C, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_4", "MMU_CMD_STALL_ENABLE_4", 0x00000610, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_4", "MMU_CMD_SEED_GAP_4", 0x00000610, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_4", "MMU_CMD_SEED_BURST_4", 0x00000610, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_4", "MMU_CMD_MAX_GAP_4", 0x00000610, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_4", "MMU_CMD_MAX_BURST_4", 0x00000610, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_5", "MMU_CMD_STALL_ENABLE_5", 0x00000614, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_5", "MMU_CMD_SEED_GAP_5", 0x00000614, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_5", "MMU_CMD_SEED_BURST_5", 0x00000614, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_5", "MMU_CMD_MAX_GAP_5", 0x00000614, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_5", "MMU_CMD_MAX_BURST_5", 0x00000614, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_6", "MMU_CMD_STALL_ENABLE_6", 0x00000618, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_6", "MMU_CMD_SEED_GAP_6", 0x00000618, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_6", "MMU_CMD_SEED_BURST_6", 0x00000618, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_6", "MMU_CMD_MAX_GAP_6", 0x00000618, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_6", "MMU_CMD_MAX_BURST_6", 0x00000618, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_7", "MMU_CMD_STALL_ENABLE_7", 0x0000061C, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_7", "MMU_CMD_SEED_GAP_7", 0x0000061C, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_7", "MMU_CMD_SEED_BURST_7", 0x0000061C, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_7", "MMU_CMD_MAX_GAP_7", 0x0000061C, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_7", "MMU_CMD_MAX_BURST_7", 0x0000061C, 0, 3, 0x0},\
	{"MMU_CMD_STALL_CTRL_8", "MMU_CMD_STALL_ENABLE_8", 0x00000620, 31, 31, 0x0},\
	{"MMU_CMD_STALL_CTRL_8", "MMU_CMD_SEED_GAP_8", 0x00000620, 19, 29, 0x0},\
	{"MMU_CMD_STALL_CTRL_8", "MMU_CMD_SEED_BURST_8", 0x00000620, 8, 18, 0x0},\
	{"MMU_CMD_STALL_CTRL_8", "MMU_CMD_MAX_GAP_8", 0x00000620, 4, 7, 0x0},\
	{"MMU_CMD_STALL_CTRL_8", "MMU_CMD_MAX_BURST_8", 0x00000620, 0, 3, 0x0},\
	{"CORE_ID", "GROUP_ID", 0x00000000, 24, 31, 0x0},\
	{"CORE_ID", "ALLOCATION_ID", 0x00000000, 16, 23, 0x0},\
	{"CORE_ID", "CONFIG_ID", 0x00000000, 0, 15, 0x0},\
	{"CORE_ID2", "FELIX_NUM_IMAGERS", 0x00000004, 24, 31, 0x0},\
	{"CORE_ID2", "FELIX_BIT_DEPTH", 0x00000004, 16, 23, 0x0},\
	{"CORE_ID2", "FELIX_NUM_CONTEXT", 0x00000004, 8, 15, 0x0},\
	{"CORE_ID2", "FELIX_PARALLELISM", 0x00000004, 0, 7, 0x0},\
	{"CORE_REVISION", "CORE_DESIGNER", 0x00000010, 24, 31, 0x0},\
	{"CORE_REVISION", "CORE_MAJOR_REV", 0x00000010, 16, 23, 0x1},\
	{"CORE_REVISION", "CORE_MINOR_REV", 0x00000010, 8, 15, 0x1},\
	{"CORE_REVISION", "CORE_MAINT_REV", 0x00000010, 0, 7, 0x1},\
	{"UID_NUM", "UID_NUM", 0x00000014, 0, 31, 0x0},\
	{"DESIGNER_REV_FIELD1", "DG_IIF_ACTIVE", 0x00000020, 20, 20, 0x0},\
	{"DESIGNER_REV_FIELD1", "BLACK_LEV_SUPPORTED", 0x00000020, 18, 18, 0x0},\
	{"DESIGNER_REV_FIELD1", "GASKET_PIXELS_PER_CLOCK", 0x00000020, 16, 17, 0x0},\
	{"DESIGNER_REV_FIELD1", "MEMORY_LATENCY", 0x00000020, 12, 15, 0x0},\
	{"DESIGNER_REV_FIELD2", "DESIGNER_FIELD2", 0x00000030, 0, 31, 0x0},\
	{"HDF_CONTEXTS_SUPPORTED", "HDF_CONTEXTS_SUPPORTED", 0x00000034, 0, 3, 0x0},\
	{"MAX_ACTIVE_WIDTH", "MAX_ACTIVE_WIDTH", 0x00000038, 0, 31, 0x0},\
	{"DPF_READ_MAP_FIFO_SIZE", "DPF_READ_MAP_BUF_FIFO_SIZE", 0x0000003C, 0, 31, 0x0},\
	{"DESIGNER_REV_FIELD3", "ENC_SCALER_H_LUMA_TAPS", 0x00000040, 24, 28, 0x0},\
	{"DESIGNER_REV_FIELD3", "ENC_SCALER_V_LUMA_TAPS", 0x00000040, 16, 20, 0x0},\
	{"DESIGNER_REV_FIELD3", "ENC_SCALER_V_CHROMA_TAPS", 0x00000040, 8, 11, 0x0},\
	{"DESIGNER_REV_FIELD3", "DISP_SCALER_H_LUMA_TAPS", 0x00000040, 4, 7, 0x0},\
	{"DESIGNER_REV_FIELD3", "DISP_SCALER_V_LUMA_TAPS", 0x00000040, 0, 3, 0x0},\
	{"FELIX_CONTROL", "TS_ENABLE", 0x00000050, 0, 0, 0x0},\
	{"FELIX_CONTROL", "MMU_TILING_SCHEME", 0x00000050, 8, 8, 0x0},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_MEM", 0x00000054, 26, 27, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_CTRL", 0x00000054, 24, 25, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_GRP_6", 0x00000054, 12, 13, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_GRP_5", 0x00000054, 10, 11, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_GRP_4", 0x00000054, 8, 9, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_GRP_3", 0x00000054, 6, 7, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_GRP_2", 0x00000054, 4, 5, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_GRP_1", 0x00000054, 2, 3, 0x2},\
	{"FELIX_PWR_CTRL", "CLOCK_GATECTRL_GRP_0", 0x00000054, 0, 1, 0x2},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_MEM", 0x00000058, 26, 26, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_CTRL", 0x00000058, 24, 24, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_GRP_6", 0x00000058, 12, 12, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_GRP_5", 0x00000058, 10, 10, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_GRP_4", 0x00000058, 8, 8, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_GRP_3", 0x00000058, 6, 6, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_GRP_2", 0x00000058, 4, 4, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_GRP_1", 0x00000058, 2, 2, 0x0},\
	{"FELIX_PWR_STATUS", "CLOCK_GATESTATUS_GRP_0", 0x00000058, 0, 0, 0x0},\
	{"CORE_RESET", "CORE_RESET", 0x0000005C, 0, 0, 0x0},\
	{"CORE_RESET", "ALL_RESET", 0x0000005C, 1, 1, 0x0},\
	{"CORE_RESET", "MMU_RESET", 0x0000005C, 2, 2, 0x0},\
	{"CORE_RESET", "DG_IIF_RESET", 0x0000005C, 3, 3, 0x0},\
	{"CORE_RESET", "GASKET_RESET", 0x0000005C, 4, 4, 0x0},\
	{"CORE_RESET", "AXI_RESET", 0x0000005C, 6, 6, 0x0},\
	{"ENC_OUT_CTRL", "ENC_OUT_CTRL_SEL", 0x00000060, 4, 5, 0x3},\
	{"ENC_OUT_CTRL", "ENC_OUT_PULSE_WTH_MINUS1", 0x00000060, 0, 3, 0x0},\
	{"DE_CTRL", "DE_SELECT", 0x00000064, 0, 2, 0x0},\
	{"FELIX_INTERRUPT_STATUS", "DG_TEST_INTERRUPT", 0x00000068, 16, 31, 0x0},\
	{"FELIX_INTERRUPT_STATUS", "DG_IIF_INTERRUPT", 0x00000068, 9, 9, 0x0},\
	{"FELIX_INTERRUPT_STATUS", "MMU_INTERRUPT", 0x00000068, 8, 8, 0x0},\
	{"FELIX_INTERRUPT_STATUS", "CONTEXT_INTERRUPT", 0x00000068, 0, 7, 0x0},\
	{"FELIX_TS_COUNTER", "FELIX_TS_COUNTER", 0x0000006C, 0, 31, 0x0},\
	{"DI_CTRL", "DI_MODE", 0x00000070, 6, 7, 0x0},\
	{"DI_CTRL", "DI_CONTEXT", 0x00000070, 4, 5, 0x0},\
	{"DI_CTRL", "DI_FLOW", 0x00000070, 3, 3, 0x0},\
	{"DI_CTRL", "DI_SELECT", 0x00000070, 0, 2, 0x0},\
	{"DI_SIZE", "DI_FRAME_HEIGHT", 0x00000074, 16, 29, 0x0},\
	{"DI_SIZE", "DI_FRAME_WIDTH", 0x00000074, 0, 13, 0x0},\
	{"DI_PIXEL_RATE", "DI_CLK_PER_PIXEL", 0x00000078, 0, 7, 0x0},\
	{"DI_LINK_ADDR", "DI_LINK_ADDR", 0x0000007C, 0, 25, 0x0},\
	{"DI_TAG", "DI_TAG", 0x00000080, 0, 7, 0x0},\
	{"DI_ADDR_Y", "DI_ADDR_Y", 0x00000084, 6, 31, 0x0},\
	{"DI_ADDR_Y_STRIDE", "DI_ADDR_Y_STRIDE", 0x00000088, 6, 31, 0x0},\
	{"DI_ADDR_C", "DI_ADDR_C", 0x0000008C, 6, 31, 0x0},\
	{"DI_ADDR_C_STRIDE", "DI_ADDR_C_STRIDE", 0x00000090, 6, 31, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "FLD_ACTIVE", 0x00000094, 22, 22, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "DGM_ACTIVE", 0x00000094, 21, 21, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "Y2R_ACTIVE", 0x00000094, 20, 20, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "HUS_ACTIVE", 0x00000094, 19, 19, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "DSC_ACTIVE", 0x00000094, 18, 18, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "VSS_ACTIVE", 0x00000094, 17, 17, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "ESC_ACTIVE", 0x00000094, 16, 16, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "SHA_ACTIVE", 0x00000094, 15, 15, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "TNM_ACTIVE", 0x00000094, 14, 14, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "HSS_ACTIVE", 0x00000094, 13, 13, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "MIE_ACTIVE", 0x00000094, 12, 12, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "R2Y_ACTIVE", 0x00000094, 11, 11, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "GMA_ACTIVE", 0x00000094, 10, 10, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "MGM_ACTIVE", 0x00000094, 9, 9, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "CCM_ACTIVE", 0x00000094, 8, 8, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "DMO_ACTIVE", 0x00000094, 7, 7, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "LCA_ACTIVE", 0x00000094, 6, 6, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "DPF_ACTIVE", 0x00000094, 5, 5, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "DNS_ACTIVE", 0x00000094, 4, 4, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "LSH_ACTIVE", 0x00000094, 3, 3, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "RLT_ACTIVE", 0x00000094, 2, 2, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "BLC_ACTIVE", 0x00000094, 1, 1, 0x0},\
	{"DEBUG_ACTIVE_BLOCKS", "IIF_ACTIVE", 0x00000094, 0, 0, 0x0},\
	{"FELIX_INTERRUPT_ENABLE", "MMU_INTERRUPT_EN", 0x00000098, 8, 8, 0x0},\
	{"FELIX_INTERRUPT_CLEAR", "MMU_INTERRUPT_CLEAR", 0x0000009C, 8, 8, 0x0},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_7", 0x00000100, 14, 15, 0x2},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_6", 0x00000100, 12, 13, 0x2},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_5", 0x00000100, 10, 11, 0x2},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_4", 0x00000100, 8, 9, 0x2},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_3", 0x00000100, 6, 7, 0x2},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_2", 0x00000100, 4, 5, 0x2},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_1", 0x00000100, 2, 3, 0x2},\
	{"FELIX_PWR_CTRL2", "CLOCK_GATECTRL_CTX_0", 0x00000100, 0, 1, 0x2},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_7", 0x00000104, 14, 14, 0x0},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_6", 0x00000104, 12, 12, 0x0},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_5", 0x00000104, 10, 10, 0x0},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_4", 0x00000104, 8, 8, 0x0},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_3", 0x00000104, 6, 6, 0x0},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_2", 0x00000104, 4, 4, 0x0},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_1", 0x00000104, 2, 2, 0x0},\
	{"FELIX_PWR_STATUS2", "CLOCK_GATESTATUS_CTX_0", 0x00000104, 0, 0, 0x0},\
	{"RTM_A_CTRL", "RTM_A_CTRL", 0x00000200, 0, 31, 0x0},\
	{"RTM_A_EXT_CTRL", "RTM_A_EXT_CTRL", 0x00000204, 0, 1, 0x0},\
	{"RTM_A", "RTM_A", 0x00000208, 0, 31, 0x0},\
	{"RTM_B_CTRL", "RTM_B_CTRL", 0x0000020C, 0, 31, 0x0},\
	{"RTM_B_EXT_CTRL", "RTM_B_EXT_CTRL", 0x00000210, 0, 1, 0x0},\
	{"RTM_B", "RTM_B", 0x00000214, 0, 31, 0x0},\
	{"MMU_RESP_STALL_CTRL", "MMU_RESP_STALL_ENABLE", 0x00000500, 31, 31, 0x0},\
	{"MMU_RESP_STALL_CTRL", "MMU_RESP_SEED_GAP", 0x00000500, 19, 29, 0x0},\
	{"MMU_RESP_STALL_CTRL", "MMU_RESP_SEED_BURST", 0x00000500, 8, 18, 0x0},\
	{"MMU_RESP_STALL_CTRL", "MMU_RESP_MAX_GAP", 0x00000500, 4, 7, 0x0},\
	{"MMU_RESP_STALL_CTRL", "MMU_RESP_MAX_BURST", 0x00000500, 0, 3, 0x0},\
	{"REQ_CMD_STALL", "RBW_STALLING", 0x00000504, 0, 3, 0x0},\
	{"REQ_CMD_STALL", "HDF_STALLING", 0x00000504, 4, 7, 0x0},\
	{"DEBUG_GRP_0", "GRP_0_PACKED", 0x00000700, 0, 31, 0x0},\
	{"DEBUG_GRP_1", "GRP_1_PACKED", 0x00000704, 0, 31, 0x0},\
	{"DEBUG_GRP_2", "GRP_2_PACKED", 0x00000708, 0, 31, 0x0},\
	{"DEBUG_GRP_3", "GRP_3_PACKED", 0x0000070C, 0, 31, 0x0},\
	{"DEBUG_GRP_4", "GRP_4_PACKED", 0x00000710, 0, 31, 0x0},\
	{"DEBUG_GRP_5", "GRP_5_PACKED", 0x00000714, 0, 31, 0x0},\
	{"DEBUG_GRP_6", "GRP_6_PACKED", 0x00000718, 0, 31, 0x0},\
	{"FPGA_BUILD", "FPGA_BUILD_VERSION", 0x000007FC, 0, 31, 0x0},\
};

#define FELIX_CORE_ADD_FIELD_DEFNS(DefnSet, Memspace, MemspaceID) \
	{ \
		int i; \
		FELIX_CORE_FIELDS; \
		for (i = 0; i < (sizeof(felix_core_fields)/sizeof(*felix_core_fields)); i++) \
		{ \
			addFieldDefn(DefnSet, Memspace, MemspaceID, \
				felix_core_fields[i].szRegName, \
				felix_core_fields[i].szFieldName, \
				felix_core_fields[i].ui32RegOffset, \
				felix_core_fields[i].ui32FieldStart, \
				felix_core_fields[i].ui32FieldEnd, \
				felix_core_fields[i].ui32FieldDefault); \
		} \
	}




#ifdef __cplusplus
}
#endif

#endif /* __FIELDS_CORE_H__ */
