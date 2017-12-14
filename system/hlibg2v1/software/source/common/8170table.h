/* Copyright 2013 Google Inc. All Rights Reserved. */
/* Register interface based on the document version 0.19 */
/* HWIF_DEC_TIMEOUT       */ {/*swreg*/1 ,  1, 18,  1},
/* HWIF_DEC_ERROR_INT     */ {/*swreg*/1 ,  1, 16,  1},
/* HWIF_DEC_BUFFER_INT    */ {/*swreg*/1 ,  1, 14,  1},
/* HWIF_DEC_BUS_INT       */ {/*swreg*/1 ,  1, 13,  1},
/* HWIF_DEC_RDY_INT       */ {/*swreg*/1 ,  1, 12,  1},
/* HWIF_DEC_ABORT_INT     */ {/*swreg*/1 ,  1, 11,  1},
/* HWIF_DEC_IRQ           */ {/*swreg*/1 ,  1,  8,  1},
/* HWIF_DEC_ABORT_E       */ {/*swreg*/1 ,  1,  5,  1},
/* HWIF_DEC_IRQ_DIS       */ {/*swreg*/1 ,  1,  4,  1},
/* HWIF_DEC_E             */ {/*swreg*/1 ,  1,  0,  1},
/* HWIF_DEC_STRM_SWAP     */ {/*swreg*/2 ,  4, 28,  1},
/* HWIF_DEC_PIC_SWAP      */ {/*swreg*/2 ,  4, 24,  1},
/* HWIF_DEC_DIRMV_SWAP    */ {/*swreg*/2 ,  4, 20,  1},
/* HWIF_DEC_TAB0_SWAP     */ {/*swreg*/2 ,  4, 16,  1},
/* HWIF_DEC_TAB1_SWAP     */ {/*swreg*/2 ,  4, 12,  1},
/* HWIF_DEC_TAB2_SWAP     */ {/*swreg*/2 ,  4,  8,  1},
/* HWIF_DEC_TAB3_SWAP     */ {/*swreg*/2 ,  4,  4,  1},
/* HWIF_DEC_RSCAN_SWAP    */ {/*swreg*/2 ,  4,  0,  1},
/* HWIF_DEC_MODE          */ {/*swreg*/3 ,  5, 27,  1},
/* HWIF_DEC_COMP_TABLE_SWAP */ {/*swreg*/3 ,  4, 20,  1},
/* HWIF_DEC_OUT_EC_BYPASS */ {/*swreg*/3 ,  1, 17,  1},
/* HWIF_DEC_OUT_RS_E      */ {/*swreg*/3 ,  1, 16,  1},
/* HWIF_DEC_OUT_DIS       */ {/*swreg*/3 ,  1, 15,  1},
/* HWIF_FILTERING_DIS     */ {/*swreg*/3 ,  1, 14,  1},
/* HWIF_WRITE_MVS_E       */ {/*swreg*/3 ,  1, 12,  1},
/* HWIF_APF_ONE_PID       */ {/*swreg*/3 ,  1, 11,  1},
/* HWIF_PIC_WIDTH_IN_CBS  */ {/*swreg*/4 , 13, 19,  1},
/* HWIF_PIC_HEIGHT_IN_CBS */ {/*swreg*/4 , 13,  6,  1},
/* HWIF_REF_FRAMES        */ {/*swreg*/4 ,  5,  0,  1},
/* HWIF_STRM_START_BIT    */ {/*swreg*/5 ,  7, 25,  1},
/* HWIF_SCALING_LIST_E    */ {/*swreg*/5 ,  1, 24,  1},
/* HWIF_CH_QP_OFFSET      */ {/*swreg*/5 ,  5, 19,  1},
/* HWIF_CH_QP_OFFSET2     */ {/*swreg*/5 ,  5, 14,  1},
/* HWIF_SIGN_DATA_HIDE    */ {/*swreg*/5 ,  1, 12,  1},
/* HWIF_TEMPOR_MVP_E      */ {/*swreg*/5 ,  1, 11,  1},
/* HWIF_MAX_CU_QPD_DEPTH  */ {/*swreg*/5 ,  6,  5,  1},
/* HWIF_CU_QPD_E          */ {/*swreg*/5 ,  1,  4,  1},
/* HWIF_STREAM_LEN        */ {/*swreg*/6 , 32,  0,  1},
/* HWIF_CABAC_INIT_PRESENT */ {/*swreg*/7 ,  1, 31,  1},
/* HWIF_BLACKWHITE_E      */ {/*swreg*/7 ,  1, 30,  1},
/* HWIF_WEIGHT_PRED_E     */ {/*swreg*/7 ,  1, 28,  1},
/* HWIF_WEIGHT_BIPR_IDC   */ {/*swreg*/7 ,  2, 26,  1},
/* HWIF_FILT_SLICE_BORDER */ {/*swreg*/7 ,  1, 25,  1},
/* HWIF_FILT_TILE_BORDER  */ {/*swreg*/7 ,  1, 24,  1},
/* HWIF_ASYM_PRED_E       */ {/*swreg*/7 ,  1, 23,  1},
/* HWIF_SAO_E             */ {/*swreg*/7 ,  1, 22,  1},
/* HWIF_PCM_FILT_DISABLE  */ {/*swreg*/7 ,  1, 21,  1},
/* HWIF_SLICE_CHQP_FLAG   */ {/*swreg*/7 ,  1, 20,  1},
/* HWIF_DEPEND_SLICE_E    */ {/*swreg*/7 ,  1, 19,  1},
/* HWIF_FILT_OVERRIDE_E   */ {/*swreg*/7 ,  1, 18,  1},
/* HWIF_STRONG_SMOOTH_E   */ {/*swreg*/7 ,  1, 17,  1},
/* HWIF_FILT_OFFSET_BETA  */ {/*swreg*/7 ,  5, 12,  1},
/* HWIF_FILT_OFFSET_TC    */ {/*swreg*/7 ,  5,  7,  1},
/* HWIF_SLICE_HDR_EXT_E   */ {/*swreg*/7 ,  1,  6,  1},
/* HWIF_SLICE_HDR_EBITS   */ {/*swreg*/7 ,  3,  3,  1},
/* HWIF_CONST_INTRA_E     */ {/*swreg*/8 ,  1, 31,  1},
/* HWIF_FILT_CTRL_PRES    */ {/*swreg*/8 ,  1, 30,  1},
/* HWIF_IDR_PIC_E         */ {/*swreg*/8 ,  1, 16,  1},
/* HWIF_PCM_BITDEPTH_Y    */ {/*swreg*/8 ,  4, 12,  1},
/* HWIF_PCM_BITDEPTH_C    */ {/*swreg*/8 ,  4,  8,  1},
/* HWIF_BIT_DEPTH_Y_MINUS8 */ {/*swreg*/8 ,  2,  6,  1},
/* HWIF_BIT_DEPTH_C_MINUS8 */ {/*swreg*/8 ,  2,  4,  1},
/* HWIF_OUTPUT_8_BITS     */ {/*swreg*/8 ,  1,  3,  1},
/* HWIF_OUTPUT_FORMAT     */ {/*swreg*/8 ,  3,  0,  1},
/* HWIF_REFIDX1_ACTIVE    */ {/*swreg*/9 ,  5, 19,  1},
/* HWIF_REFIDX0_ACTIVE    */ {/*swreg*/9 ,  5, 14,  1},
/* HWIF_HDR_SKIP_LENGTH   */ {/*swreg*/9 , 14,  0,  1},
/* HWIF_START_CODE_E      */ {/*swreg*/10,  1, 31,  1},
/* HWIF_INIT_QP_V0        */ {/*swreg*/10,  6, 25,  1},
/* HWIF_INIT_QP           */ {/*swreg*/10,  7, 24,  1},
/* HWIF_NUM_TILE_COLS_V0  */ {/*swreg*/10,  5, 20,  1},
/* HWIF_NUM_TILE_COLS     */ {/*swreg*/10,  5, 19,  1},
/* HWIF_NUM_TILE_ROWS_V0  */ {/*swreg*/10,  5, 15,  1},
/* HWIF_NUM_TILE_ROWS     */ {/*swreg*/10,  5, 14,  1},
/* HWIF_TILE_ENABLE       */ {/*swreg*/10,  1,  1,  1},
/* HWIF_ENTR_CODE_SYNCH_E */ {/*swreg*/10,  1,  0,  1},
/* HWIF_TRANSFORM_MODE    */ {/*swreg*/11,  3, 27,  1},
/* HWIF_FILT_SHARPNESS    */ {/*swreg*/11,  3, 21,  1},
/* HWIF_FILT_TYPE         */ {/*swreg*/11,  1, 19,  1},
/* HWIF_MCOMP_FILT_TYPE   */ {/*swreg*/11,  3,  8,  1},
/* HWIF_HIGH_PREC_MV_E    */ {/*swreg*/11,  1,  7,  1},
/* HWIF_COMP_PRED_MODE    */ {/*swreg*/11,  2,  4,  1},
/* HWIF_GREF_SIGN_BIAS    */ {/*swreg*/11,  1,  2,  1},
/* HWIF_AREF_SIGN_BIAS    */ {/*swreg*/11,  1,  0,  1},
/* HWIF_REFER_LTERM_E     */ {/*swreg*/12, 16, 16,  1},
/* HWIF_MIN_CB_SIZE       */ {/*swreg*/12,  3, 13,  1},
/* HWIF_MAX_CB_SIZE       */ {/*swreg*/12,  3, 10,  1},
/* HWIF_MIN_PCM_SIZE      */ {/*swreg*/12,  3,  7,  1},
/* HWIF_MAX_PCM_SIZE      */ {/*swreg*/12,  3,  4,  1},
/* HWIF_PCM_E             */ {/*swreg*/12,  1,  3,  1},
/* HWIF_TRANSFORM_SKIP_E  */ {/*swreg*/12,  1,  2,  1},
/* HWIF_TRANSQ_BYPASS_E   */ {/*swreg*/12,  1,  1,  1},
/* HWIF_REFPICLIST_MOD_E  */ {/*swreg*/12,  1,  0,  1},
/* HWIF_MIN_TRB_SIZE      */ {/*swreg*/13,  3, 13,  1},
/* HWIF_MAX_TRB_SIZE      */ {/*swreg*/13,  3, 10,  1},
/* HWIF_MAX_INTRA_HIERDEPTH */ {/*swreg*/13,  3,  7,  1},
/* HWIF_MAX_INTER_HIERDEPTH */ {/*swreg*/13,  3,  4,  1},
/* HWIF_PARALLEL_MERGE    */ {/*swreg*/13,  4,  0,  1},
/* HWIF_QP_DELTA_Y_DC     */ {/*swreg*/13,  6, 23,  1},
/* HWIF_QP_DELTA_CH_DC    */ {/*swreg*/13,  6, 17,  1},
/* HWIF_QP_DELTA_CH_AC    */ {/*swreg*/13,  6, 11,  1},
/* HWIF_LAST_SIGN_BIAS    */ {/*swreg*/13,  1, 10,  1},
/* HWIF_LOSSLESS_E        */ {/*swreg*/13,  1,  9,  1},
/* HWIF_COMP_PRED_VAR_REF1 */ {/*swreg*/13,  2,  7,  1},
/* HWIF_COMP_PRED_VAR_REF0 */ {/*swreg*/13,  2,  5,  1},
/* HWIF_COMP_PRED_FIXED_REF */ {/*swreg*/13,  2,  3,  1},
/* HWIF_SEGMENT_TEMP_UPD_E */ {/*swreg*/13,  1,  2,  1},
/* HWIF_SEGMENT_UPD_E     */ {/*swreg*/13,  1,  1,  1},
/* HWIF_SEGMENT_E         */ {/*swreg*/13,  1,  0,  1},
/* HWIF_INIT_RLIST_B2     */ {/*swreg*/14,  5, 25,  1},
/* HWIF_INIT_RLIST_F2     */ {/*swreg*/14,  5, 20,  1},
/* HWIF_INIT_RLIST_B1     */ {/*swreg*/14,  5, 15,  1},
/* HWIF_INIT_RLIST_F1     */ {/*swreg*/14,  5, 10,  1},
/* HWIF_INIT_RLIST_B0     */ {/*swreg*/14,  5,  5,  1},
/* HWIF_INIT_RLIST_F0     */ {/*swreg*/14,  5,  0,  1},
/* HWIF_FILT_LEVEL        */ {/*swreg*/14,  6, 18,  1},
/* HWIF_REFPIC_SEG0       */ {/*swreg*/14,  3, 15,  1},
/* HWIF_SKIP_SEG0         */ {/*swreg*/14,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG0   */ {/*swreg*/14,  6,  8,  1},
/* HWIF_QUANT_SEG0        */ {/*swreg*/14,  8,  0,  1},
/* HWIF_INIT_RLIST_B5     */ {/*swreg*/15,  5, 25,  1},
/* HWIF_INIT_RLIST_F5     */ {/*swreg*/15,  5, 20,  1},
/* HWIF_INIT_RLIST_B4     */ {/*swreg*/15,  5, 15,  1},
/* HWIF_INIT_RLIST_F4     */ {/*swreg*/15,  5, 10,  1},
/* HWIF_INIT_RLIST_B3     */ {/*swreg*/15,  5,  5,  1},
/* HWIF_INIT_RLIST_F3     */ {/*swreg*/15,  5,  0,  1},
/* HWIF_REFPIC_SEG1       */ {/*swreg*/15,  3, 15,  1},
/* HWIF_SKIP_SEG1         */ {/*swreg*/15,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG1   */ {/*swreg*/15,  6,  8,  1},
/* HWIF_QUANT_SEG1        */ {/*swreg*/15,  8,  0,  1},
/* HWIF_INIT_RLIST_B8     */ {/*swreg*/16,  5, 25,  1},
/* HWIF_INIT_RLIST_F8     */ {/*swreg*/16,  5, 20,  1},
/* HWIF_INIT_RLIST_B7     */ {/*swreg*/16,  5, 15,  1},
/* HWIF_INIT_RLIST_F7     */ {/*swreg*/16,  5, 10,  1},
/* HWIF_INIT_RLIST_B6     */ {/*swreg*/16,  5,  5,  1},
/* HWIF_INIT_RLIST_F6     */ {/*swreg*/16,  5,  0,  1},
/* HWIF_REFPIC_SEG2       */ {/*swreg*/16,  3, 15,  1},
/* HWIF_SKIP_SEG2         */ {/*swreg*/16,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG2   */ {/*swreg*/16,  6,  8,  1},
/* HWIF_QUANT_SEG2        */ {/*swreg*/16,  8,  0,  1},
/* HWIF_INIT_RLIST_B11    */ {/*swreg*/17,  5, 25,  1},
/* HWIF_INIT_RLIST_F11    */ {/*swreg*/17,  5, 20,  1},
/* HWIF_INIT_RLIST_B10    */ {/*swreg*/17,  5, 15,  1},
/* HWIF_INIT_RLIST_F10    */ {/*swreg*/17,  5, 10,  1},
/* HWIF_INIT_RLIST_B9     */ {/*swreg*/17,  5,  5,  1},
/* HWIF_INIT_RLIST_F9     */ {/*swreg*/17,  5,  0,  1},
/* HWIF_REFPIC_SEG3       */ {/*swreg*/17,  3, 15,  1},
/* HWIF_SKIP_SEG3         */ {/*swreg*/17,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG3   */ {/*swreg*/17,  6,  8,  1},
/* HWIF_QUANT_SEG3        */ {/*swreg*/17,  8,  0,  1},
/* HWIF_INIT_RLIST_B14    */ {/*swreg*/18,  5, 25,  1},
/* HWIF_INIT_RLIST_F14    */ {/*swreg*/18,  5, 20,  1},
/* HWIF_INIT_RLIST_B13    */ {/*swreg*/18,  5, 15,  1},
/* HWIF_INIT_RLIST_F13    */ {/*swreg*/18,  5, 10,  1},
/* HWIF_INIT_RLIST_B12    */ {/*swreg*/18,  5,  5,  1},
/* HWIF_INIT_RLIST_F12    */ {/*swreg*/18,  5,  0,  1},
/* HWIF_REFPIC_SEG4       */ {/*swreg*/18,  3, 15,  1},
/* HWIF_SKIP_SEG4         */ {/*swreg*/18,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG4   */ {/*swreg*/18,  6,  8,  1},
/* HWIF_QUANT_SEG4        */ {/*swreg*/18,  8,  0,  1},
/* HWIF_INIT_RLIST_B15    */ {/*swreg*/19,  5,  5,  1},
/* HWIF_INIT_RLIST_F15    */ {/*swreg*/19,  5,  0,  1},
/* HWIF_REFPIC_SEG5       */ {/*swreg*/19,  3, 15,  1},
/* HWIF_SKIP_SEG5         */ {/*swreg*/19,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG5   */ {/*swreg*/19,  6,  8,  1},
/* HWIF_QUANT_SEG5        */ {/*swreg*/19,  8,  0,  1},
/* HWIF_PARTIAL_CTB_X     */ {/*swreg*/20,  1, 31,  1},
/* HWIF_PARTIAL_CTB_Y     */ {/*swreg*/20,  1, 30,  1},
/* HWIF_PIC_WIDTH_4X4     */ {/*swreg*/20, 12, 16,  1},
/* HWIF_PIC_HEIGHT_4X4    */ {/*swreg*/20, 12,  0,  1},
/* HWIF_REFPIC_SEG6       */ {/*swreg*/31,  3, 15,  1},
/* HWIF_SKIP_SEG6         */ {/*swreg*/31,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG6   */ {/*swreg*/31,  6,  8,  1},
/* HWIF_QUANT_SEG6        */ {/*swreg*/31,  8,  0,  1},
/* HWIF_REFPIC_SEG7       */ {/*swreg*/32,  3, 15,  1},
/* HWIF_SKIP_SEG7         */ {/*swreg*/32,  1, 14,  1},
/* HWIF_FILT_LEVEL_SEG7   */ {/*swreg*/32,  6,  8,  1},
/* HWIF_QUANT_SEG7        */ {/*swreg*/32,  8,  0,  1},
/* HWIF_LREF_WIDTH        */ {/*swreg*/33, 16, 16,  1},
/* HWIF_LREF_HEIGHT       */ {/*swreg*/33, 16,  0,  1},
/* HWIF_GREF_WIDTH        */ {/*swreg*/34, 16, 16,  1},
/* HWIF_GREF_HEIGHT       */ {/*swreg*/34, 16,  0,  1},
/* HWIF_AREF_WIDTH        */ {/*swreg*/35, 16, 16,  1},
/* HWIF_AREF_HEIGHT       */ {/*swreg*/35, 16,  0,  1},
/* HWIF_LREF_HOR_SCALE    */ {/*swreg*/36, 16, 16,  1},
/* HWIF_LREF_VER_SCALE    */ {/*swreg*/36, 16,  0,  1},
/* HWIF_GREF_HOR_SCALE    */ {/*swreg*/37, 16, 16,  1},
/* HWIF_GREF_VER_SCALE    */ {/*swreg*/37, 16,  0,  1},
/* HWIF_AREF_HOR_SCALE    */ {/*swreg*/38, 16, 16,  1},
/* HWIF_AREF_VER_SCALE    */ {/*swreg*/38, 16,  0,  1},
/* HWIF_TIMEOUT_OVERRIDE_E */ {/*swreg*/45,  1, 31,  1},
/* HWIF_TIMEOUT_CYCLES    */ {/*swreg*/45, 31,  0,  1},
/* HWIF_CUR_POC_00        */ {/*swreg*/46,  8, 24,  1},
/* HWIF_CUR_POC_01        */ {/*swreg*/46,  8, 16,  1},
/* HWIF_CUR_POC_02        */ {/*swreg*/46,  8,  8,  1},
/* HWIF_CUR_POC_03        */ {/*swreg*/46,  8,  0,  1},
/* HWIF_FILT_REF_ADJ_0    */ {/*swreg*/46,  7, 24,  1},
/* HWIF_FILT_REF_ADJ_1    */ {/*swreg*/46,  7, 16,  1},
/* HWIF_FILT_REF_ADJ_2    */ {/*swreg*/46,  7,  8,  1},
/* HWIF_FILT_REF_ADJ_3    */ {/*swreg*/46,  7,  0,  1},
/* HWIF_CUR_POC_04        */ {/*swreg*/47,  8, 24,  1},
/* HWIF_CUR_POC_05        */ {/*swreg*/47,  8, 16,  1},
/* HWIF_CUR_POC_06        */ {/*swreg*/47,  8,  8,  1},
/* HWIF_CUR_POC_07        */ {/*swreg*/47,  8,  0,  1},
/* HWIF_FILT_MB_ADJ_0     */ {/*swreg*/47,  7, 24,  1},
/* HWIF_FILT_MB_ADJ_1     */ {/*swreg*/47,  7, 16,  1},
/* HWIF_FILT_MB_ADJ_2     */ {/*swreg*/47,  7,  8,  1},
/* HWIF_FILT_MB_ADJ_3     */ {/*swreg*/47,  7,  0,  1},
/* HWIF_CUR_POC_08        */ {/*swreg*/48,  8, 24,  1},
/* HWIF_CUR_POC_09        */ {/*swreg*/48,  8, 16,  1},
/* HWIF_CUR_POC_10        */ {/*swreg*/48,  8,  8,  1},
/* HWIF_CUR_POC_11        */ {/*swreg*/48,  8,  0,  1},
/* HWIF_CUR_POC_12        */ {/*swreg*/49,  8, 24,  1},
/* HWIF_CUR_POC_13        */ {/*swreg*/49,  8, 16,  1},
/* HWIF_CUR_POC_14        */ {/*swreg*/49,  8,  8,  1},
/* HWIF_CUR_POC_15        */ {/*swreg*/49,  8,  0,  1},
/* HWIF_APF_DISABLE       */ {/*swreg*/55,  1, 31,  1},
/* HWIF_APF_SINGLE_PU_MODE */ {/*swreg*/55,  1, 30,  1},
/* HWIF_APF_THRESHOLD     */ {/*swreg*/55, 16,  0,  1},
/* HWIF_DEC_CLK_GATE_IDLE_E */ {/*swreg*/58,  1, 17,  1},
/* HWIF_DEC_CLK_GATE_E    */ {/*swreg*/58,  1, 16,  1},
/* HWIF_DEC_REFER_DOUBLEBUFFER_E */ {/*swreg*/58,  1, 15,  1},
/* HWIF_DEC_AXI_RD_ID_E   */ {/*swreg*/58,  1, 14,  1},
/* HWIF_DEC_AXI_WD_ID_E   */ {/*swreg*/58,  1, 13,  1},
/* HWIF_DEC_BUSWIDTH      */ {/*swreg*/58,  3,  8,  1},
/* HWIF_DEC_MAX_BURST     */ {/*swreg*/58,  8,  0,  1},
/* HWIF_DEC_AXI_WR_ID     */ {/*swreg*/59, 16, 16,  1},
/* HWIF_DEC_AXI_RD_ID     */ {/*swreg*/59, 16,  0,  1},
/* HWIF_PERF_CYCLE_COUNT  */ {/*swreg*/63, 32,  0,  1},
/* HWIF_DEC_OUT_YBASE_MSB */ {/*swreg*/64, 32,  0,  1},
/* HWIF_DEC_OUT_YBASE_LSB */ {/*swreg*/65, 32,  0,  1},
/* HWIF_REFER0_YBASE_MSB  */ {/*swreg*/66, 32,  0,  1},
/* HWIF_REFER0_YBASE_LSB  */ {/*swreg*/67, 32,  0,  1},
/* HWIF_REFER1_YBASE_MSB  */ {/*swreg*/68, 32,  0,  1},
/* HWIF_REFER1_YBASE_LSB  */ {/*swreg*/69, 32,  0,  1},
/* HWIF_REFER2_YBASE_MSB  */ {/*swreg*/70, 32,  0,  1},
/* HWIF_REFER2_YBASE_LSB  */ {/*swreg*/71, 32,  0,  1},
/* HWIF_REFER3_YBASE_MSB  */ {/*swreg*/72, 32,  0,  1},
/* HWIF_REFER3_YBASE_LSB  */ {/*swreg*/73, 32,  0,  1},
/* HWIF_REFER4_YBASE_MSB  */ {/*swreg*/74, 32,  0,  1},
/* HWIF_REFER4_YBASE_LSB  */ {/*swreg*/75, 32,  0,  1},
/* HWIF_REFER5_YBASE_MSB  */ {/*swreg*/76, 32,  0,  1},
/* HWIF_REFER5_YBASE_LSB  */ {/*swreg*/77, 32,  0,  1},
/* HWIF_REFER6_YBASE_MSB  */ {/*swreg*/78, 32,  0,  1},
/* HWIF_SEGMENT_WRITE_BASE_MSB */ {/*swreg*/78, 32,  0,  1},
/* HWIF_REFER6_YBASE_LSB  */ {/*swreg*/79, 32,  0,  1},
/* HWIF_SEGMENT_WRITE_BASE_LSB */ {/*swreg*/79, 32,  0,  1},
/* HWIF_REFER7_YBASE_MSB  */ {/*swreg*/80, 32,  0,  1},
/* HWIF_SEGMENT_READ_BASE_MSB */ {/*swreg*/80, 32,  0,  1},
/* HWIF_REFER7_YBASE_LSB  */ {/*swreg*/81, 32,  0,  1},
/* HWIF_SEGMENT_READ_BASE_LSB */ {/*swreg*/81, 32,  0,  1},
/* HWIF_REFER8_YBASE_MSB  */ {/*swreg*/82, 32,  0,  1},
/* HWIF_REFER8_YBASE_LSB  */ {/*swreg*/83, 32,  0,  1},
/* HWIF_REFER9_YBASE_MSB  */ {/*swreg*/84, 32,  0,  1},
/* HWIF_REFER9_YBASE_LSB  */ {/*swreg*/85, 32,  0,  1},
/* HWIF_REFER10_YBASE_MSB */ {/*swreg*/86, 32,  0,  1},
/* HWIF_REFER10_YBASE_LSB */ {/*swreg*/87, 32,  0,  1},
/* HWIF_REFER11_YBASE_MSB */ {/*swreg*/88, 32,  0,  1},
/* HWIF_REFER11_YBASE_LSB */ {/*swreg*/89, 32,  0,  1},
/* HWIF_REFER12_YBASE_MSB */ {/*swreg*/90, 32,  0,  1},
/* HWIF_REFER12_YBASE_LSB */ {/*swreg*/91, 32,  0,  1},
/* HWIF_REFER13_YBASE_MSB */ {/*swreg*/92, 32,  0,  1},
/* HWIF_REFER13_YBASE_LSB */ {/*swreg*/93, 32,  0,  1},
/* HWIF_REFER14_YBASE_MSB */ {/*swreg*/94, 32,  0,  1},
/* HWIF_REFER14_YBASE_LSB */ {/*swreg*/95, 32,  0,  1},
/* HWIF_REFER15_YBASE_MSB */ {/*swreg*/96, 32,  0,  1},
/* HWIF_REFER15_YBASE_LSB */ {/*swreg*/97, 32,  0,  1},
/* HWIF_DEC_OUT_CBASE_MSB */ {/*swreg*/98, 32,  0,  1},
/* HWIF_DEC_OUT_CBASE_LSB */ {/*swreg*/99, 32,  0,  1},
/* HWIF_REFER0_CBASE_MSB  */ {/*swreg*/100, 32,  0,  1},
/* HWIF_REFER0_CBASE_LSB  */ {/*swreg*/101, 32,  0,  1},
/* HWIF_REFER1_CBASE_MSB  */ {/*swreg*/102, 32,  0,  1},
/* HWIF_REFER1_CBASE_LSB  */ {/*swreg*/103, 32,  0,  1},
/* HWIF_REFER2_CBASE_MSB  */ {/*swreg*/104, 32,  0,  1},
/* HWIF_REFER2_CBASE_LSB  */ {/*swreg*/105, 32,  0,  1},
/* HWIF_REFER3_CBASE_MSB  */ {/*swreg*/106, 32,  0,  1},
/* HWIF_REFER3_CBASE_LSB  */ {/*swreg*/107, 32,  0,  1},
/* HWIF_REFER4_CBASE_MSB  */ {/*swreg*/108, 32,  0,  1},
/* HWIF_REFER4_CBASE_LSB  */ {/*swreg*/109, 32,  0,  1},
/* HWIF_REFER5_CBASE_MSB  */ {/*swreg*/110, 32,  0,  1},
/* HWIF_REFER5_CBASE_LSB  */ {/*swreg*/111, 32,  0,  1},
/* HWIF_REFER6_CBASE_MSB  */ {/*swreg*/112, 32,  0,  1},
/* HWIF_REFER6_CBASE_LSB  */ {/*swreg*/113, 32,  0,  1},
/* HWIF_REFER7_CBASE_MSB  */ {/*swreg*/114, 32,  0,  1},
/* HWIF_REFER7_CBASE_LSB  */ {/*swreg*/115, 32,  0,  1},
/* HWIF_REFER8_CBASE_MSB  */ {/*swreg*/116, 32,  0,  1},
/* HWIF_REFER8_CBASE_LSB  */ {/*swreg*/117, 32,  0,  1},
/* HWIF_REFER9_CBASE_MSB  */ {/*swreg*/118, 32,  0,  1},
/* HWIF_REFER9_CBASE_LSB  */ {/*swreg*/119, 32,  0,  1},
/* HWIF_REFER10_CBASE_MSB */ {/*swreg*/120, 32,  0,  1},
/* HWIF_REFER10_CBASE_LSB */ {/*swreg*/121, 32,  0,  1},
/* HWIF_REFER11_CBASE_MSB */ {/*swreg*/122, 32,  0,  1},
/* HWIF_REFER11_CBASE_LSB */ {/*swreg*/123, 32,  0,  1},
/* HWIF_REFER12_CBASE_MSB */ {/*swreg*/124, 32,  0,  1},
/* HWIF_REFER12_CBASE_LSB */ {/*swreg*/125, 32,  0,  1},
/* HWIF_REFER13_CBASE_MSB */ {/*swreg*/126, 32,  0,  1},
/* HWIF_REFER13_CBASE_LSB */ {/*swreg*/127, 32,  0,  1},
/* HWIF_REFER14_CBASE_MSB */ {/*swreg*/128, 32,  0,  1},
/* HWIF_REFER14_CBASE_LSB */ {/*swreg*/129, 32,  0,  1},
/* HWIF_REFER15_CBASE_MSB */ {/*swreg*/130, 32,  0,  1},
/* HWIF_REFER15_CBASE_LSB */ {/*swreg*/131, 32,  0,  1},
/* HWIF_DEC_OUT_DBASE_MSB */ {/*swreg*/132, 32,  0,  1},
/* HWIF_DEC_OUT_DBASE_LSB */ {/*swreg*/133, 32,  0,  1},
/* HWIF_REFER0_DBASE_MSB  */ {/*swreg*/134, 32,  0,  1},
/* HWIF_REFER0_DBASE_LSB  */ {/*swreg*/135, 32,  0,  1},
/* HWIF_REFER1_DBASE_MSB  */ {/*swreg*/136, 32,  0,  1},
/* HWIF_REFER1_DBASE_LSB  */ {/*swreg*/137, 32,  0,  1},
/* HWIF_REFER2_DBASE_MSB  */ {/*swreg*/138, 32,  0,  1},
/* HWIF_REFER2_DBASE_LSB  */ {/*swreg*/139, 32,  0,  1},
/* HWIF_REFER3_DBASE_MSB  */ {/*swreg*/140, 32,  0,  1},
/* HWIF_REFER3_DBASE_LSB  */ {/*swreg*/141, 32,  0,  1},
/* HWIF_REFER4_DBASE_MSB  */ {/*swreg*/142, 32,  0,  1},
/* HWIF_REFER4_DBASE_LSB  */ {/*swreg*/143, 32,  0,  1},
/* HWIF_REFER5_DBASE_MSB  */ {/*swreg*/144, 32,  0,  1},
/* HWIF_REFER5_DBASE_LSB  */ {/*swreg*/145, 32,  0,  1},
/* HWIF_REFER6_DBASE_MSB  */ {/*swreg*/146, 32,  0,  1},
/* HWIF_REFER6_DBASE_LSB  */ {/*swreg*/147, 32,  0,  1},
/* HWIF_REFER7_DBASE_MSB  */ {/*swreg*/148, 32,  0,  1},
/* HWIF_REFER7_DBASE_LSB  */ {/*swreg*/149, 32,  0,  1},
/* HWIF_REFER8_DBASE_MSB  */ {/*swreg*/150, 32,  0,  1},
/* HWIF_REFER8_DBASE_LSB  */ {/*swreg*/151, 32,  0,  1},
/* HWIF_REFER9_DBASE_MSB  */ {/*swreg*/152, 32,  0,  1},
/* HWIF_REFER9_DBASE_LSB  */ {/*swreg*/153, 32,  0,  1},
/* HWIF_REFER10_DBASE_MSB */ {/*swreg*/154, 32,  0,  1},
/* HWIF_REFER10_DBASE_LSB */ {/*swreg*/155, 32,  0,  1},
/* HWIF_REFER11_DBASE_MSB */ {/*swreg*/156, 32,  0,  1},
/* HWIF_REFER11_DBASE_LSB */ {/*swreg*/157, 32,  0,  1},
/* HWIF_REFER12_DBASE_MSB */ {/*swreg*/158, 32,  0,  1},
/* HWIF_REFER12_DBASE_LSB */ {/*swreg*/159, 32,  0,  1},
/* HWIF_REFER13_DBASE_MSB */ {/*swreg*/160, 32,  0,  1},
/* HWIF_REFER13_DBASE_LSB */ {/*swreg*/161, 32,  0,  1},
/* HWIF_REFER14_DBASE_MSB */ {/*swreg*/162, 32,  0,  1},
/* HWIF_REFER14_DBASE_LSB */ {/*swreg*/163, 32,  0,  1},
/* HWIF_REFER15_DBASE_MSB */ {/*swreg*/164, 32,  0,  1},
/* HWIF_REFER15_DBASE_LSB */ {/*swreg*/165, 32,  0,  1},
/* HWIF_TILE_BASE_MSB     */ {/*swreg*/166, 32,  0,  1},
/* HWIF_TILE_BASE_LSB     */ {/*swreg*/167, 32,  0,  1},
/* HWIF_STREAM_BASE_MSB   */ {/*swreg*/168, 32,  0,  1},
/* HWIF_STREAM_BASE_LSB   */ {/*swreg*/169, 32,  0,  1},
/* HWIF_SCALE_LIST_BASE_MSB */ {/*swreg*/170, 32,  0,  1},
/* HWIF_CTX_COUNTER_BASE_MSB */ {/*swreg*/170, 32,  0,  1},
/* HWIF_SCALE_LIST_BASE_LSB */ {/*swreg*/171, 32,  0,  1},
/* HWIF_CTX_COUNTER_BASE_LSB */ {/*swreg*/171, 32,  0,  1},
/* HWIF_PROB_TAB_BASE_MSB */ {/*swreg*/172, 32,  0,  1},
/* HWIF_PROB_TAB_BASE_LSB */ {/*swreg*/173, 32,  0,  1},
/* HWIF_DEC_RSY_BASE_MSB  */ {/*swreg*/174, 32,  0,  1},
/* HWIF_DEC_RSY_BASE_LSB  */ {/*swreg*/175, 32,  0,  1},
/* HWIF_DEC_RSC_BASE_MSB  */ {/*swreg*/176, 32,  0,  1},
/* HWIF_DEC_RSC_BASE_LSB  */ {/*swreg*/177, 32,  0,  1},
/* HWIF_DEC_VERT_FILT_BASE_MSB */ {/*swreg*/178, 32,  0,  1},
/* HWIF_DEC_VERT_FILT_BASE_LSB */ {/*swreg*/179, 32,  0,  1},
/* HWIF_DEC_VERT_SAO_BASE_MSB */ {/*swreg*/180, 32,  0,  1},
/* HWIF_DEC_VERT_SAO_BASE_LSB */ {/*swreg*/181, 32,  0,  1},
/* HWIF_DEC_BSD_CTRL_BASE_MSB */ {/*swreg*/182, 32,  0,  1},
/* HWIF_DEC_BSD_CTRL_BASE_LSB */ {/*swreg*/183, 32,  0,  1},
/* HWIF_DEC_DS_E          */ {/*swreg*/184,  1,  7,  1},
/* HWIF_DEC_DS_Y          */ {/*swreg*/184,  2,  2,  1},
/* HWIF_DEC_DS_X          */ {/*swreg*/184,  2,  0,  1},
/* HWIF_DEC_DSY_BASE_MSB  */ {/*swreg*/185, 32,  0,  1},
/* HWIF_DEC_DSY_BASE_LSB  */ {/*swreg*/186, 32,  0,  1},
/* HWIF_DEC_DSC_BASE_MSB  */ {/*swreg*/187, 32,  0,  1},
/* HWIF_DEC_DSC_BASE_LSB  */ {/*swreg*/188, 32,  0,  1},
#ifdef NEW_REG
/* HWIF_DEC_OUT_TYBASE_MSB */ {/*swreg*/189, 32,  0,  1},
/* HWIF_DEC_OUT_TYBASE_LSB */ {/*swreg*/190, 32,  0,  1},
/* HWIF_REFER0_TYBASE_MSB */ {/*swreg*/191, 32,  0,  1},
/* HWIF_REFER0_TYBASE_LSB */ {/*swreg*/192, 32,  0,  1},
/* HWIF_REFER1_TYBASE_MSB */ {/*swreg*/193, 32,  0,  1},
/* HWIF_REFER1_TYBASE_LSB */ {/*swreg*/194, 32,  0,  1},
/* HWIF_REFER2_TYBASE_MSB */ {/*swreg*/195, 32,  0,  1},
/* HWIF_REFER2_TYBASE_LSB */ {/*swreg*/196, 32,  0,  1},
/* HWIF_REFER3_TYBASE_MSB */ {/*swreg*/197, 32,  0,  1},
/* HWIF_REFER3_TYBASE_LSB */ {/*swreg*/198, 32,  0,  1},
/* HWIF_REFER4_TYBASE_MSB */ {/*swreg*/199, 32,  0,  1},
/* HWIF_REFER4_TYBASE_LSB */ {/*swreg*/200, 32,  0,  1},
/* HWIF_REFER5_TYBASE_MSB */ {/*swreg*/201, 32,  0,  1},
/* HWIF_REFER5_TYBASE_LSB */ {/*swreg*/202, 32,  0,  1},
/* HWIF_REFER6_TYBASE_MSB */ {/*swreg*/203, 32,  0,  1},
/* HWIF_REFER6_TYBASE_LSB */ {/*swreg*/204, 32,  0,  1},
/* HWIF_REFER7_TYBASE_MSB */ {/*swreg*/205, 32,  0,  1},
/* HWIF_REFER7_TYBASE_LSB */ {/*swreg*/206, 32,  0,  1},
/* HWIF_REFER8_TYBASE_MSB */ {/*swreg*/207, 32,  0,  1},
/* HWIF_REFER8_TYBASE_LSB */ {/*swreg*/208, 32,  0,  1},
/* HWIF_REFER9_TYBASE_MSB */ {/*swreg*/209, 32,  0,  1},
/* HWIF_REFER9_TYBASE_LSB */ {/*swreg*/210, 32,  0,  1},
/* HWIF_REFER10_TYBASE_MSB */ {/*swreg*/211, 32,  0,  1},
/* HWIF_REFER10_TYBASE_LSB */ {/*swreg*/212, 32,  0,  1},
/* HWIF_REFER11_TYBASE_MSB */ {/*swreg*/213, 32,  0,  1},
/* HWIF_REFER11_TYBASE_LSB */ {/*swreg*/214, 32,  0,  1},
/* HWIF_REFER12_TYBASE_MSB */ {/*swreg*/215, 32,  0,  1},
/* HWIF_REFER12_TYBASE_LSB */ {/*swreg*/216, 32,  0,  1},
/* HWIF_REFER13_TYBASE_MSB */ {/*swreg*/217, 32,  0,  1},
/* HWIF_REFER13_TYBASE_LSB */ {/*swreg*/218, 32,  0,  1},
/* HWIF_REFER14_TYBASE_MSB */ {/*swreg*/219, 32,  0,  1},
/* HWIF_REFER14_TYBASE_LSB */ {/*swreg*/220, 32,  0,  1},
/* HWIF_REFER15_TYBASE_MSB */ {/*swreg*/221, 32,  0,  1},
/* HWIF_REFER15_TYBASE_LSB */ {/*swreg*/222, 32,  0,  1},
/* HWIF_DEC_OUT_TCBASE_MSB */ {/*swreg*/223, 32,  0,  1},
/* HWIF_DEC_OUT_TCBASE_LSB */ {/*swreg*/224, 32,  0,  1},
/* HWIF_REFER0_TCBASE_MSB */ {/*swreg*/225, 32,  0,  1},
/* HWIF_REFER0_TCBASE_LSB */ {/*swreg*/226, 32,  0,  1},
/* HWIF_REFER1_TCBASE_MSB */ {/*swreg*/227, 32,  0,  1},
/* HWIF_REFER1_TCBASE_LSB */ {/*swreg*/228, 32,  0,  1},
/* HWIF_REFER2_TCBASE_MSB */ {/*swreg*/229, 32,  0,  1},
/* HWIF_REFER2_TCBASE_LSB */ {/*swreg*/230, 32,  0,  1},
/* HWIF_REFER3_TCBASE_MSB */ {/*swreg*/231, 32,  0,  1},
/* HWIF_REFER3_TCBASE_LSB */ {/*swreg*/232, 32,  0,  1},
/* HWIF_REFER4_TCBASE_MSB */ {/*swreg*/233, 32,  0,  1},
/* HWIF_REFER4_TCBASE_LSB */ {/*swreg*/234, 32,  0,  1},
/* HWIF_REFER5_TCBASE_MSB */ {/*swreg*/235, 32,  0,  1},
/* HWIF_REFER5_TCBASE_LSB */ {/*swreg*/236, 32,  0,  1},
/* HWIF_REFER6_TCBASE_MSB */ {/*swreg*/237, 32,  0,  1},
/* HWIF_REFER6_TCBASE_LSB */ {/*swreg*/238, 32,  0,  1},
/* HWIF_REFER7_TCBASE_MSB */ {/*swreg*/239, 32,  0,  1},
/* HWIF_REFER7_TCBASE_LSB */ {/*swreg*/240, 32,  0,  1},
/* HWIF_REFER8_TCBASE_MSB */ {/*swreg*/241, 32,  0,  1},
/* HWIF_REFER8_TCBASE_LSB */ {/*swreg*/242, 32,  0,  1},
/* HWIF_REFER9_TCBASE_MSB */ {/*swreg*/243, 32,  0,  1},
/* HWIF_REFER9_TCBASE_LSB */ {/*swreg*/244, 32,  0,  1},
/* HWIF_REFER10_TCBASE_MSB */ {/*swreg*/245, 32,  0,  1},
/* HWIF_REFER10_TCBASE_LSB */ {/*swreg*/246, 32,  0,  1},
/* HWIF_REFER11_TCBASE_MSB */ {/*swreg*/247, 32,  0,  1},
/* HWIF_REFER11_TCBASE_LSB */ {/*swreg*/248, 32,  0,  1},
/* HWIF_REFER12_TCBASE_MSB */ {/*swreg*/249, 32,  0,  1},
/* HWIF_REFER12_TCBASE_LSB */ {/*swreg*/250, 32,  0,  1},
/* HWIF_REFER13_TCBASE_MSB */ {/*swreg*/251, 32,  0,  1},
/* HWIF_REFER13_TCBASE_LSB */ {/*swreg*/252, 32,  0,  1},
/* HWIF_REFER14_TCBASE_MSB */ {/*swreg*/253, 32,  0,  1},
/* HWIF_REFER14_TCBASE_LSB */ {/*swreg*/254, 32,  0,  1},
/* HWIF_REFER15_TCBASE_MSB */ {/*swreg*/255, 32,  0,  1},
/* HWIF_REFER15_TCBASE_LSB */ {/*swreg*/256, 32,  0,  1},
/* HWIF_STRM_BUF_LEN      */ {/*swreg*/258, 32,  0,  1},
/* HWIF_STRM_START_OFFSET */ {/*swreg*/259, 32,  0,  1},
#endif
