/*!
******************************************************************************
@file   : /home/jenkins/builds/workspace/ISP_PKG/build/CI/felix/regdefs/regdefs//hw_struct/ctx_pointers.h

@brief  

@Author <Autogenerated>

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

<b>Description:</b>\n
		This file contains the CTX_POINTERS_H Defintions.


 Register Attributes meaning:
 @li <REG>_OFFSET <int> offset in bytes from the register bank
 @li <REG>_STRIDE <int> [table register only] distance in bytes between table entries
 @li <REG>_NO_ENTRIES <int> [table register only] number of entries in the table
 @li <REG>_TRUSTED <bool> [only if register is trusted] if the register can only be written by trusted source

 Fields Attributes meaning:
 @li <FIELD>_MASK <int> in register
 @li <FIELD>_LSBMASK <int> when field is shifted to LSBs
 @li <FIELD>_SHIFT <int> in bits from LSB
 @li <FIELD>_LENGTH <int> in bits
 @li <FIELD>_DEFAULT <int>
 @li <FIELD>_SIGNED_FIELD <bool>
 @li <FIELD>_NO_REPS <int> [repeated field only] number of time the field is repeated
 @li <FIELD>_SIZE <int> [repeated field only] size of repeated field (same than LENGTH)

 If the register bank is a structure <BANK>_BYTE_SIZE <int> is defined as the size in memory.
******************************************************************************/

#if !defined (__CTX_POINTERS_H__)
#define __CTX_POINTERS_H__

#ifdef __cplusplus
extern "C" {
#endif


#define FELIX_LINK_LIST_CONTEXT_TAG_OFFSET		(0x0000)

/* FELIX_LINK_LIST, CONTEXT_TAG, CONTEXT_TAG
*/
#define FELIX_LINK_LIST_CONTEXT_TAG_CONTEXT_TAG_MASK		(0x000000FF)
#define FELIX_LINK_LIST_CONTEXT_TAG_CONTEXT_TAG_LSBMASK		(0x000000FF)
#define FELIX_LINK_LIST_CONTEXT_TAG_CONTEXT_TAG_SHIFT		(0)
#define FELIX_LINK_LIST_CONTEXT_TAG_CONTEXT_TAG_LENGTH		(8)
#define FELIX_LINK_LIST_CONTEXT_TAG_CONTEXT_TAG_DEFAULT		(0)
#define FELIX_LINK_LIST_CONTEXT_TAG_CONTEXT_TAG_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_ENC_Y_ADDR_OFFSET		(0x0004)

/* FELIX_LINK_LIST, MEM_ENC_Y_ADDR, MEM_ENC_Y_ADDR
*/
#define FELIX_LINK_LIST_MEM_ENC_Y_ADDR_MEM_ENC_Y_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_ENC_Y_ADDR_MEM_ENC_Y_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_ENC_Y_ADDR_MEM_ENC_Y_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_ENC_Y_ADDR_MEM_ENC_Y_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_ENC_Y_ADDR_MEM_ENC_Y_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_ENC_Y_ADDR_MEM_ENC_Y_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_ENC_Y_STR_OFFSET		(0x0008)

/* FELIX_LINK_LIST, MEM_ENC_Y_STR, MEM_ENC_Y_STR
*/
#define FELIX_LINK_LIST_MEM_ENC_Y_STR_MEM_ENC_Y_STR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_ENC_Y_STR_MEM_ENC_Y_STR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_ENC_Y_STR_MEM_ENC_Y_STR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_ENC_Y_STR_MEM_ENC_Y_STR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_ENC_Y_STR_MEM_ENC_Y_STR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_ENC_Y_STR_MEM_ENC_Y_STR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_ENC_Y_LAST_PAGE_OFFSET		(0x000C)

/* FELIX_LINK_LIST, MEM_ENC_Y_LAST_PAGE, MEM_ENC_Y_LAST_PAGE
*/
#define FELIX_LINK_LIST_MEM_ENC_Y_LAST_PAGE_MEM_ENC_Y_LAST_PAGE_MASK		(0xFFFFF000)
#define FELIX_LINK_LIST_MEM_ENC_Y_LAST_PAGE_MEM_ENC_Y_LAST_PAGE_LSBMASK		(0x000FFFFF)
#define FELIX_LINK_LIST_MEM_ENC_Y_LAST_PAGE_MEM_ENC_Y_LAST_PAGE_SHIFT		(12)
#define FELIX_LINK_LIST_MEM_ENC_Y_LAST_PAGE_MEM_ENC_Y_LAST_PAGE_LENGTH		(20)
#define FELIX_LINK_LIST_MEM_ENC_Y_LAST_PAGE_MEM_ENC_Y_LAST_PAGE_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_ENC_Y_LAST_PAGE_MEM_ENC_Y_LAST_PAGE_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_ENC_C_ADDR_OFFSET		(0x0010)

/* FELIX_LINK_LIST, MEM_ENC_C_ADDR, MEM_ENC_C_ADDR
*/
#define FELIX_LINK_LIST_MEM_ENC_C_ADDR_MEM_ENC_C_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_ENC_C_ADDR_MEM_ENC_C_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_ENC_C_ADDR_MEM_ENC_C_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_ENC_C_ADDR_MEM_ENC_C_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_ENC_C_ADDR_MEM_ENC_C_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_ENC_C_ADDR_MEM_ENC_C_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_ENC_C_STR_OFFSET		(0x0014)

/* FELIX_LINK_LIST, MEM_ENC_C_STR, MEM_ENC_C_STR
*/
#define FELIX_LINK_LIST_MEM_ENC_C_STR_MEM_ENC_C_STR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_ENC_C_STR_MEM_ENC_C_STR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_ENC_C_STR_MEM_ENC_C_STR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_ENC_C_STR_MEM_ENC_C_STR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_ENC_C_STR_MEM_ENC_C_STR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_ENC_C_STR_MEM_ENC_C_STR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_ENC_C_LAST_PAGE_OFFSET		(0x0018)

/* FELIX_LINK_LIST, MEM_ENC_C_LAST_PAGE, MEM_ENC_C_LAST_PAGE
*/
#define FELIX_LINK_LIST_MEM_ENC_C_LAST_PAGE_MEM_ENC_C_LAST_PAGE_MASK		(0xFFFFF000)
#define FELIX_LINK_LIST_MEM_ENC_C_LAST_PAGE_MEM_ENC_C_LAST_PAGE_LSBMASK		(0x000FFFFF)
#define FELIX_LINK_LIST_MEM_ENC_C_LAST_PAGE_MEM_ENC_C_LAST_PAGE_SHIFT		(12)
#define FELIX_LINK_LIST_MEM_ENC_C_LAST_PAGE_MEM_ENC_C_LAST_PAGE_LENGTH		(20)
#define FELIX_LINK_LIST_MEM_ENC_C_LAST_PAGE_MEM_ENC_C_LAST_PAGE_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_ENC_C_LAST_PAGE_MEM_ENC_C_LAST_PAGE_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_DISP_DE_ADDR_OFFSET		(0x001C)

/* FELIX_LINK_LIST, MEM_DISP_DE_ADDR, MEM_DISP_DE_ADDR
*/
#define FELIX_LINK_LIST_MEM_DISP_DE_ADDR_MEM_DISP_DE_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_DISP_DE_ADDR_MEM_DISP_DE_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_DISP_DE_ADDR_MEM_DISP_DE_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_DISP_DE_ADDR_MEM_DISP_DE_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_DISP_DE_ADDR_MEM_DISP_DE_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_DISP_DE_ADDR_MEM_DISP_DE_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_DISP_DE_STR_OFFSET		(0x0020)

/* FELIX_LINK_LIST, MEM_DISP_DE_STR, MEM_DISP_DE_STR
*/
#define FELIX_LINK_LIST_MEM_DISP_DE_STR_MEM_DISP_DE_STR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_DISP_DE_STR_MEM_DISP_DE_STR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_DISP_DE_STR_MEM_DISP_DE_STR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_DISP_DE_STR_MEM_DISP_DE_STR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_DISP_DE_STR_MEM_DISP_DE_STR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_DISP_DE_STR_MEM_DISP_DE_STR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_DISP_DE_LAST_PAGE_OFFSET		(0x0024)

/* FELIX_LINK_LIST, MEM_DISP_DE_LAST_PAGE, MEM_DISP_DE_LAST_PAGE
*/
#define FELIX_LINK_LIST_MEM_DISP_DE_LAST_PAGE_MEM_DISP_DE_LAST_PAGE_MASK		(0xFFFFF000)
#define FELIX_LINK_LIST_MEM_DISP_DE_LAST_PAGE_MEM_DISP_DE_LAST_PAGE_LSBMASK		(0x000FFFFF)
#define FELIX_LINK_LIST_MEM_DISP_DE_LAST_PAGE_MEM_DISP_DE_LAST_PAGE_SHIFT		(12)
#define FELIX_LINK_LIST_MEM_DISP_DE_LAST_PAGE_MEM_DISP_DE_LAST_PAGE_LENGTH		(20)
#define FELIX_LINK_LIST_MEM_DISP_DE_LAST_PAGE_MEM_DISP_DE_LAST_PAGE_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_DISP_DE_LAST_PAGE_MEM_DISP_DE_LAST_PAGE_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_DPF_WR_MAP_ADDR_OFFSET		(0x0028)

/* FELIX_LINK_LIST, DPF_WR_MAP_ADDR, DPF_WR_MAP_ADDR
*/
#define FELIX_LINK_LIST_DPF_WR_MAP_ADDR_DPF_WR_MAP_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_DPF_WR_MAP_ADDR_DPF_WR_MAP_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_DPF_WR_MAP_ADDR_DPF_WR_MAP_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_DPF_WR_MAP_ADDR_DPF_WR_MAP_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_DPF_WR_MAP_ADDR_DPF_WR_MAP_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_DPF_WR_MAP_ADDR_DPF_WR_MAP_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_ENS_WR_ADDR_OFFSET		(0x002C)

/* FELIX_LINK_LIST, ENS_WR_ADDR, ENS_WR_ADDR
*/
#define FELIX_LINK_LIST_ENS_WR_ADDR_ENS_WR_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_ENS_WR_ADDR_ENS_WR_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_ENS_WR_ADDR_ENS_WR_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_ENS_WR_ADDR_ENS_WR_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_ENS_WR_ADDR_ENS_WR_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_ENS_WR_ADDR_ENS_WR_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_RAW_2D_ADDR_OFFSET		(0x0030)

/* FELIX_LINK_LIST, MEM_RAW_2D_ADDR, MEM_RAW_2D_ADDR
*/
#define FELIX_LINK_LIST_MEM_RAW_2D_ADDR_MEM_RAW_2D_ADDR_MASK		(0xFFFFFFFF)
#define FELIX_LINK_LIST_MEM_RAW_2D_ADDR_MEM_RAW_2D_ADDR_LSBMASK		(0xFFFFFFFF)
#define FELIX_LINK_LIST_MEM_RAW_2D_ADDR_MEM_RAW_2D_ADDR_SHIFT		(0)
#define FELIX_LINK_LIST_MEM_RAW_2D_ADDR_MEM_RAW_2D_ADDR_LENGTH		(32)
#define FELIX_LINK_LIST_MEM_RAW_2D_ADDR_MEM_RAW_2D_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_RAW_2D_ADDR_MEM_RAW_2D_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_RAW_2D_STR_OFFSET		(0x0034)

/* FELIX_LINK_LIST, MEM_RAW_2D_STR, MEM_RAW_2D_STR
*/
#define FELIX_LINK_LIST_MEM_RAW_2D_STR_MEM_RAW_2D_STR_MASK		(0xFFFFFFFF)
#define FELIX_LINK_LIST_MEM_RAW_2D_STR_MEM_RAW_2D_STR_LSBMASK		(0xFFFFFFFF)
#define FELIX_LINK_LIST_MEM_RAW_2D_STR_MEM_RAW_2D_STR_SHIFT		(0)
#define FELIX_LINK_LIST_MEM_RAW_2D_STR_MEM_RAW_2D_STR_LENGTH		(32)
#define FELIX_LINK_LIST_MEM_RAW_2D_STR_MEM_RAW_2D_STR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_RAW_2D_STR_MEM_RAW_2D_STR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_RAW_2D_LAST_PAGE_OFFSET		(0x0038)

/* FELIX_LINK_LIST, MEM_RAW_2D_LAST_PAGE, MEM_RAW_2D_LAST_PAGE
*/
#define FELIX_LINK_LIST_MEM_RAW_2D_LAST_PAGE_MEM_RAW_2D_LAST_PAGE_MASK		(0xFFFFF000)
#define FELIX_LINK_LIST_MEM_RAW_2D_LAST_PAGE_MEM_RAW_2D_LAST_PAGE_LSBMASK		(0x000FFFFF)
#define FELIX_LINK_LIST_MEM_RAW_2D_LAST_PAGE_MEM_RAW_2D_LAST_PAGE_SHIFT		(12)
#define FELIX_LINK_LIST_MEM_RAW_2D_LAST_PAGE_MEM_RAW_2D_LAST_PAGE_LENGTH		(20)
#define FELIX_LINK_LIST_MEM_RAW_2D_LAST_PAGE_MEM_RAW_2D_LAST_PAGE_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_RAW_2D_LAST_PAGE_MEM_RAW_2D_LAST_PAGE_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_HDF_WR_ADDR_OFFSET		(0x003C)

/* FELIX_LINK_LIST, MEM_HDF_WR_ADDR, MEM_HDF_WR_ADDR
*/
#define FELIX_LINK_LIST_MEM_HDF_WR_ADDR_MEM_HDF_WR_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_HDF_WR_ADDR_MEM_HDF_WR_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_HDF_WR_ADDR_MEM_HDF_WR_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_HDF_WR_ADDR_MEM_HDF_WR_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_HDF_WR_ADDR_MEM_HDF_WR_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_HDF_WR_ADDR_MEM_HDF_WR_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_HDF_WR_STR_OFFSET		(0x0040)

/* FELIX_LINK_LIST, MEM_HDF_WR_STR, MEM_HDF_WR_STR
*/
#define FELIX_LINK_LIST_MEM_HDF_WR_STR_MEM_HDF_WR_STR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_HDF_WR_STR_MEM_HDF_WR_STR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_HDF_WR_STR_MEM_HDF_WR_STR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_HDF_WR_STR_MEM_HDF_WR_STR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_HDF_WR_STR_MEM_HDF_WR_STR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_HDF_WR_STR_MEM_HDF_WR_STR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_HDF_WR_LAST_PAGE_OFFSET		(0x0044)

/* FELIX_LINK_LIST, MEM_HDF_WR_LAST_PAGE, MEM_HDF_WR_LAST_PAGE
*/
#define FELIX_LINK_LIST_MEM_HDF_WR_LAST_PAGE_MEM_HDF_WR_LAST_PAGE_MASK		(0xFFFFF000)
#define FELIX_LINK_LIST_MEM_HDF_WR_LAST_PAGE_MEM_HDF_WR_LAST_PAGE_LSBMASK		(0x000FFFFF)
#define FELIX_LINK_LIST_MEM_HDF_WR_LAST_PAGE_MEM_HDF_WR_LAST_PAGE_SHIFT		(12)
#define FELIX_LINK_LIST_MEM_HDF_WR_LAST_PAGE_MEM_HDF_WR_LAST_PAGE_LENGTH		(20)
#define FELIX_LINK_LIST_MEM_HDF_WR_LAST_PAGE_MEM_HDF_WR_LAST_PAGE_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_HDF_WR_LAST_PAGE_MEM_HDF_WR_LAST_PAGE_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_HDF_RD_ADDR_OFFSET		(0x0048)

/* FELIX_LINK_LIST, MEM_HDF_RD_ADDR, MEM_HDF_RD_ADDR
*/
#define FELIX_LINK_LIST_MEM_HDF_RD_ADDR_MEM_HDF_RD_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_HDF_RD_ADDR_MEM_HDF_RD_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_HDF_RD_ADDR_MEM_HDF_RD_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_HDF_RD_ADDR_MEM_HDF_RD_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_HDF_RD_ADDR_MEM_HDF_RD_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_HDF_RD_ADDR_MEM_HDF_RD_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_MEM_HDF_RD_STR_OFFSET		(0x004C)

/* FELIX_LINK_LIST, MEM_HDF_RD_STR, MEM_HDF_RD_STR
*/
#define FELIX_LINK_LIST_MEM_HDF_RD_STR_MEM_HDF_RD_STR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_MEM_HDF_RD_STR_MEM_HDF_RD_STR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_MEM_HDF_RD_STR_MEM_HDF_RD_STR_SHIFT		(6)
#define FELIX_LINK_LIST_MEM_HDF_RD_STR_MEM_HDF_RD_STR_LENGTH		(26)
#define FELIX_LINK_LIST_MEM_HDF_RD_STR_MEM_HDF_RD_STR_DEFAULT		(0)
#define FELIX_LINK_LIST_MEM_HDF_RD_STR_MEM_HDF_RD_STR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_TILING_CONTROL_OFFSET		(0x0050)

/* FELIX_LINK_LIST, TILING_CONTROL, DISP_DE_TILE_EN
*/
#define FELIX_LINK_LIST_TILING_CONTROL_DISP_DE_TILE_EN_MASK		(0x00000001)
#define FELIX_LINK_LIST_TILING_CONTROL_DISP_DE_TILE_EN_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_TILING_CONTROL_DISP_DE_TILE_EN_SHIFT		(0)
#define FELIX_LINK_LIST_TILING_CONTROL_DISP_DE_TILE_EN_LENGTH		(1)
#define FELIX_LINK_LIST_TILING_CONTROL_DISP_DE_TILE_EN_DEFAULT		(0)
#define FELIX_LINK_LIST_TILING_CONTROL_DISP_DE_TILE_EN_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, TILING_CONTROL, HDF_WR_TILE_EN
*/
#define FELIX_LINK_LIST_TILING_CONTROL_HDF_WR_TILE_EN_MASK		(0x00000002)
#define FELIX_LINK_LIST_TILING_CONTROL_HDF_WR_TILE_EN_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_TILING_CONTROL_HDF_WR_TILE_EN_SHIFT		(1)
#define FELIX_LINK_LIST_TILING_CONTROL_HDF_WR_TILE_EN_LENGTH		(1)
#define FELIX_LINK_LIST_TILING_CONTROL_HDF_WR_TILE_EN_DEFAULT		(0)
#define FELIX_LINK_LIST_TILING_CONTROL_HDF_WR_TILE_EN_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, TILING_CONTROL, ENC_L_TILE_EN
*/
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_L_TILE_EN_MASK		(0x00000004)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_L_TILE_EN_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_L_TILE_EN_SHIFT		(2)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_L_TILE_EN_LENGTH		(1)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_L_TILE_EN_DEFAULT		(0)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_L_TILE_EN_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, TILING_CONTROL, ENC_C_TILE_EN
*/
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_C_TILE_EN_MASK		(0x00000008)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_C_TILE_EN_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_C_TILE_EN_SHIFT		(3)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_C_TILE_EN_LENGTH		(1)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_C_TILE_EN_DEFAULT		(0)
#define FELIX_LINK_LIST_TILING_CONTROL_ENC_C_TILE_EN_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_LOAD_CONFIG_ADDR_OFFSET		(0x0054)

/* FELIX_LINK_LIST, LOAD_CONFIG_ADDR, LOAD_CONFIG_ADDR
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_ADDR_LOAD_CONFIG_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_LOAD_CONFIG_ADDR_LOAD_CONFIG_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_LOAD_CONFIG_ADDR_LOAD_CONFIG_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_LOAD_CONFIG_ADDR_LOAD_CONFIG_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_LOAD_CONFIG_ADDR_LOAD_CONFIG_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_ADDR_LOAD_CONFIG_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_OFFSET		(0x0058)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, CONFIG_TAG
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_CONFIG_TAG_MASK		(0x00FF0000)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_CONFIG_TAG_LSBMASK		(0x000000FF)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_CONFIG_TAG_SHIFT		(16)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_CONFIG_TAG_LENGTH		(8)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_CONFIG_TAG_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_CONFIG_TAG_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, LOAD_CONFIG_GRP_6
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_6_MASK		(0x00000040)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_6_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_6_SHIFT		(6)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_6_LENGTH		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_6_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_6_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, LOAD_CONFIG_GRP_5
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_5_MASK		(0x00000020)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_5_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_5_SHIFT		(5)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_5_LENGTH		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_5_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_5_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, LOAD_CONFIG_GRP_4
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_4_MASK		(0x00000010)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_4_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_4_SHIFT		(4)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_4_LENGTH		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_4_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_4_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, LOAD_CONFIG_GRP_3
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_3_MASK		(0x00000008)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_3_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_3_SHIFT		(3)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_3_LENGTH		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_3_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_3_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, LOAD_CONFIG_GRP_2
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_2_MASK		(0x00000004)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_2_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_2_SHIFT		(2)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_2_LENGTH		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_2_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_2_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, LOAD_CONFIG_GRP_1
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_1_MASK		(0x00000002)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_1_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_1_SHIFT		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_1_LENGTH		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_1_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_1_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, LOAD_CONFIG_FLAGS, LOAD_CONFIG_GRP_0
*/
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_0_MASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_0_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_0_SHIFT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_0_LENGTH		(1)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_0_DEFAULT		(0)
#define FELIX_LINK_LIST_LOAD_CONFIG_FLAGS_LOAD_CONFIG_GRP_0_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_SAVE_RESULTS_ADDR_OFFSET		(0x005C)

/* FELIX_LINK_LIST, SAVE_RESULTS_ADDR, SAVE_RESULTS_ADDR
*/
#define FELIX_LINK_LIST_SAVE_RESULTS_ADDR_SAVE_RESULTS_ADDR_MASK		(0xFFFFFFC0)
#define FELIX_LINK_LIST_SAVE_RESULTS_ADDR_SAVE_RESULTS_ADDR_LSBMASK		(0x03FFFFFF)
#define FELIX_LINK_LIST_SAVE_RESULTS_ADDR_SAVE_RESULTS_ADDR_SHIFT		(6)
#define FELIX_LINK_LIST_SAVE_RESULTS_ADDR_SAVE_RESULTS_ADDR_LENGTH		(26)
#define FELIX_LINK_LIST_SAVE_RESULTS_ADDR_SAVE_RESULTS_ADDR_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_RESULTS_ADDR_SAVE_RESULTS_ADDR_SIGNED_FIELD	(IMG_FALSE)

#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_OFFSET		(0x0060)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, HDF_WR_FORMAT
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_FORMAT_MASK		(0x18000000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_FORMAT_LSBMASK		(0x00000003)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_FORMAT_SHIFT		(27)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_FORMAT_LENGTH		(2)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_FORMAT_DEFAULT		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_FORMAT_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_FORMAT_ENUM {
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_HDF_WR_FORMAT_HDF_WR_NOT_VALID_2 = 0x3,
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_HDF_WR_FORMAT_HDF_WR_NOT_VALID_1 = 0x2,
	/**
	 * @brief 32-bit RGB101010
	 */
	FELIX_LINK_LIST_HDF_WR_FORMAT_RGB10 = 0x1,
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_HDF_WR_FORMAT_HDF_WR_NOT_VALID_0 = 0x0,
};

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, HDF_WR_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_ENABLE_MASK		(0x04000000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_ENABLE_SHIFT		(26)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_WR_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, HDF_RD_FORMAT
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_FORMAT_MASK		(0x03000000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_FORMAT_LSBMASK		(0x00000003)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_FORMAT_SHIFT		(24)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_FORMAT_LENGTH		(2)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_FORMAT_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_FORMAT_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_FORMAT_ENUM {
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_HDF_RD_FORMAT_HDF_RD_NOT_VALID_3 = 0x3,
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_HDF_RD_FORMAT_HDF_RD_NOT_VALID_2 = 0x2,
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_HDF_RD_FORMAT_HDF_RD_NOT_VALID_1 = 0x1,
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_HDF_RD_FORMAT_HDF_RD_NOT_VALID_0 = 0x0,
};

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, HDF_RD_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_ENABLE_MASK		(0x00800000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_ENABLE_SHIFT		(23)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HDF_RD_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, RAW_2D_FORMAT
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_FORMAT_MASK		(0x00600000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_FORMAT_LSBMASK		(0x00000003)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_FORMAT_SHIFT		(21)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_FORMAT_LENGTH		(2)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_FORMAT_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_FORMAT_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_FORMAT_ENUM {
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_RAW_2D_FORMAT_DNG_NOT_VALID_3 = 0x3,
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_RAW_2D_FORMAT_DNG_NOT_VALID_2 = 0x2,
	/**
	 * @brief : TIFF 12 bits/pixel format
	 */
	FELIX_LINK_LIST_RAW_2D_FORMAT_TIFF_12 = 0x1,
	/**
	 * @brief : TIFF 10 bits/pixel format
	 */
	FELIX_LINK_LIST_RAW_2D_FORMAT_TIFF_10 = 0x0,
};

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, RAW_2D_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_ENABLE_MASK		(0x00100000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_ENABLE_SHIFT		(20)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_RAW_2D_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, DPF_WRITE_MAP_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_WRITE_MAP_ENABLE_MASK		(0x00080000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_WRITE_MAP_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_WRITE_MAP_ENABLE_SHIFT		(19)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_WRITE_MAP_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_WRITE_MAP_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_WRITE_MAP_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, DPF_READ_MAP_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_READ_MAP_ENABLE_MASK		(0x00040000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_READ_MAP_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_READ_MAP_ENABLE_SHIFT		(18)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_READ_MAP_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_READ_MAP_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DPF_READ_MAP_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, ENS_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENS_ENABLE_MASK		(0x00020000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENS_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENS_ENABLE_SHIFT		(17)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENS_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENS_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENS_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, TIME_STAMP_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_TIME_STAMP_ENABLE_MASK		(0x00010000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_TIME_STAMP_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_TIME_STAMP_ENABLE_SHIFT		(16)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_TIME_STAMP_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_TIME_STAMP_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_TIME_STAMP_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, CRC_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_CRC_ENABLE_MASK		(0x00008000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_CRC_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_CRC_ENABLE_SHIFT		(15)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_CRC_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_CRC_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_CRC_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, FLD_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FLD_ENABLE_MASK		(0x00004000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FLD_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FLD_ENABLE_SHIFT		(14)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FLD_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FLD_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FLD_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, HIS_REGION_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_REGION_ENABLE_MASK		(0x00002000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_REGION_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_REGION_ENABLE_SHIFT		(13)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_REGION_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_REGION_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_REGION_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, HIS_GLOB_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_GLOB_ENABLE_MASK		(0x00001000)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_GLOB_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_GLOB_ENABLE_SHIFT		(12)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_GLOB_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_GLOB_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_HIS_GLOB_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, WBS_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_WBS_ENABLE_MASK		(0x00000800)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_WBS_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_WBS_ENABLE_SHIFT		(11)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_WBS_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_WBS_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_WBS_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, FOS_ROI_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_ROI_ENABLE_MASK		(0x00000400)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_ROI_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_ROI_ENABLE_SHIFT		(10)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_ROI_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_ROI_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_ROI_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, FOS_GRID_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_GRID_ENABLE_MASK		(0x00000200)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_GRID_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_GRID_ENABLE_SHIFT		(9)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_GRID_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_GRID_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_FOS_GRID_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, EXS_GLOB_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_GLOB_ENABLE_MASK		(0x00000100)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_GLOB_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_GLOB_ENABLE_SHIFT		(8)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_GLOB_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_GLOB_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_GLOB_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, EXS_REGION_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_REGION_ENABLE_MASK		(0x00000080)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_REGION_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_REGION_ENABLE_SHIFT		(7)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_REGION_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_REGION_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_EXS_REGION_ENABLE_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, DE_NO_DISP
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DE_NO_DISP_MASK		(0x00000040)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DE_NO_DISP_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DE_NO_DISP_SHIFT		(6)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DE_NO_DISP_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DE_NO_DISP_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DE_NO_DISP_SIGNED_FIELD	(IMG_FALSE)

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, DISP_DE_FORMAT
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_FORMAT_MASK		(0x00000030)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_FORMAT_LSBMASK		(0x00000003)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_FORMAT_SHIFT		(4)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_FORMAT_LENGTH		(2)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_FORMAT_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_FORMAT_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_FORMAT_ENUM {
	/**
	 * @brief Display: 32-bit RGB888 / Data extraction: not valid.
	 */
	FELIX_LINK_LIST_DISP_DE_FORMAT_BD8_32 = 0x3,
	/**
	 * @brief Display: not valid / Data extraction: 12-bit Bayer, 24 components per 288-bits.
	 */
	FELIX_LINK_LIST_DISP_DE_FORMAT_BD12 = 0x2,
	/**
	 * @brief Display: 32-bit RGB101010 / Data extraction: 10-bit Bayer, padded to 32-bits.
	 */
	FELIX_LINK_LIST_DISP_DE_FORMAT_BD10 = 0x1,
	/**
	 * @brief Display: 24-bit RGB888 / Data extraction: 8-bit Bayer, 4 components per 32-bits.
	 */
	FELIX_LINK_LIST_DISP_DE_FORMAT_BD8_24 = 0x0,
};

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, DISP_DE_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_ENABLE_MASK		(0x00000008)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_ENABLE_SHIFT		(3)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_ENABLE_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_DISP_DE_ENABLE_ENUM {
	/**
	 * @brief Display or Data Extraction output is enabled.
	 */
	FELIX_LINK_LIST_DISP_DE_ENABLE_DISP_ENABLED = 0x1,
	/**
	 * @brief Display or Data Extraction output is disabled.
	 */
	FELIX_LINK_LIST_DISP_DE_ENABLE_DISP_DISABLED = 0x0,
};

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, ENC_FORMAT
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_FORMAT_MASK		(0x00000006)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_FORMAT_LSBMASK		(0x00000003)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_FORMAT_SHIFT		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_FORMAT_LENGTH		(2)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_FORMAT_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_FORMAT_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_FORMAT_ENUM {
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_ENC_FORMAT_ENC_NOT_VALID_3 = 0x3,
	/**
	 * @brief : Not valid
	 */
	FELIX_LINK_LIST_ENC_FORMAT_ENC_NOT_VALID_2 = 0x2,
	/**
	 * @brief : 4:2:2 or 4:2:0 10-bit packed PL12 (Y/VU)
	 */
	FELIX_LINK_LIST_ENC_FORMAT_ENC_42XPL12YUV10 = 0x1,
	/**
	 * @brief : 4:2:2 or 4:2:0 8-bit PL12 (Y/VU)
	 */
	FELIX_LINK_LIST_ENC_FORMAT_ENC_42XPL12YUV8 = 0x0,
};

/* FELIX_LINK_LIST, SAVE_CONFIG_FLAGS, ENC_ENABLE
*/
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_ENABLE_MASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_ENABLE_LSBMASK		(0x00000001)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_ENABLE_SHIFT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_ENABLE_LENGTH		(1)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_ENABLE_DEFAULT		(0)
#define FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_ENABLE_SIGNED_FIELD	(IMG_FALSE)

enum FELIX_LINK_LIST_SAVE_CONFIG_FLAGS_ENC_ENABLE_ENUM {
	/**
	 * @brief Encoder output is enabled.
	 */
	FELIX_LINK_LIST_ENC_ENABLE_ENC_ENABLED = 0x1,
	/**
	 * @brief Encoder output is disabled.
	 */
	FELIX_LINK_LIST_ENC_ENABLE_ENC_DISABLED = 0x0,
};

/*
 * size of the memory structure FELIX_LINK_LIST
 * Computed from SAVE_CONFIG_FLAGS offset and size
 */
#define FELIX_LINK_LIST_BYTE_SIZE		(0x0064)


#ifdef __cplusplus
}
#endif

#endif /* __CTX_POINTERS_H__ */
