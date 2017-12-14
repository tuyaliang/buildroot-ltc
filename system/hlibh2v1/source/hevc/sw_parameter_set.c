/*------------------------------------------------------------------------------
--                                                                                                                               --
--       This software is confidential and proprietary and may be used                                   --
--        only as expressly authorized by a licensing agreement from                                     --
--                                                                                                                               --
--                            Verisilicon.                                                                                    --
--                                                                                                                               --
--                   (C) COPYRIGHT 2014 VERISILICON                                                            --
--                            ALL RIGHTS RESERVED                                                                    --
--                                                                                                                               --
--                 The entire notice above must be reproduced                                                 --
--                  on all copies and should not be removed.                                                    --
--                                                                                                                               --
--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sw_parameter_set.h"
#include "scan.h"
#include "tools.h"
#include "sw_picture.h"
#include "hevcencapi.h"
#include "encpreprocess.h"
#include "instance.h"

#define ENABLE_SAO (0)
#define EXTENDED_SAR            255
/* max MV length is 1024 horizontal and 256 vertical in quarter pixel resolution */
#define LOG2_MAX_MV_LENGTH_HOR        10
#define LOG2_MAX_MV_LENGTH_VER        8


struct vps vps =
{
  .max_num_sub_layers     = 1,
  .temporal_id_nesting_flag   = 1,
  .max_dec_pic_buffering[0]   = 5,
  .max_latency_increase[0]    = -1,
  .slo_info_present_flag      = 1,
  .general_level_idc              = 0,
};

struct sps sps =
{
  .max_num_sub_layers     = 1,
  .temporal_id_nesting_flag   = 1,
  .chroma_format_idc      = 1,
  .log2_max_pic_order_cnt_lsb   = 8,
  .max_dec_pic_buffering[0]   = 5,
  .max_latency_increase[0]    = -1,
  .slo_info_present_flag      = 1,

  .log2_min_cb_size     = 3,
  .log2_diff_cb_size      = 3,
  .log2_min_tr_size     = 2,
  .log2_diff_tr_size      = 2,

  .max_tr_hierarchy_depth_inter   = 3,
  .max_tr_hierarchy_depth_intra   = 1,

  .amp_enabled_flag     = 1,
  .sao_enabled_flag     = ENABLE_SAO,
  .sps_temporal_id_nesting_flag   = 0,
  .num_short_term_ref_pic_sets    = 13,
  .temporal_mvp_enable_flag   = 0,
  .scaling_list_enable_flag   = 0,
  .strong_intra_smoothing_enabled_flag  = 1,
  .long_term_ref_pics_present_flag = 0,
  .vui_parameters_present_flag = 1,
  .general_level_idc              = 0,
};

struct pps pps =
{
  .sign_data_hiding_flag      = 0,
  .cabac_init_present_flag    = 1,
  .num_ref_idx_l0_default_active    = 4,
  .num_ref_idx_l1_default_active    = 4,
  .init_qp        = 26,
  .constrained_intra_pred_flag    = 0,
  .transform_skip_enabled_flag    = 0,
  .cu_qp_delta_enabled_flag   = 0,
  .cb_qp_offset       = 0,
  .cr_qp_offset       = 0,
  .slice_chroma_qp_offsets_present_flag = 0,
  .loop_filter_across_slices_enabled_flag = 1,
  .log2_parallel_merge_level    = 2,
  /*  .transquant_bypass_enable_flag = 1,*/
  .deblocking_filter_control_present_flag = 1,
  .deblocking_filter_disabled_flag  = 0,

  .tc_offset = -4,
  .beta_offset = 6,

  .deblocking_filter_override_enabled_flag = 0,
  .short_term_ref_pic_set_sps_flag = 1,
};

static const u8 const list0[16] =
{
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16
};

static const u8 const list1[64] =
{
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 16, 17, 16, 17, 18,
  17, 18, 18, 17, 18, 21, 19, 20, 21, 20, 19, 21, 24, 22, 22, 24,
  24, 22, 22, 24, 25, 25, 27, 30, 27, 25, 25, 29, 31, 35, 35, 31,
  29, 36, 41, 44, 41, 36, 47, 54, 54, 47, 65, 70, 65, 88, 88, 115
};

static const u8 const list2[64] =
{
  16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 17, 18,
  18, 18, 18, 18, 18, 20, 20, 20, 20, 20, 20, 20, 24, 24, 24, 24,
  24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 28, 28, 28, 28, 28,
  28, 33, 33, 33, 33, 33, 41, 41, 41, 41, 54, 54, 54, 71, 71, 91
};

static const u8 *const default_scaling_list[4][6] =
{
  /* ScalingList[0][0..2][i] and ScalingList[0][3..5][i] */
  {list0, list0, list0, list0, list0, list0},

  /* ScalingList[1..2][0..2] and ScalingList[1..2][3..5][i] */
  {list1, list1, list1, list2, list2, list2},
  {list1, list1, list1, list2, list2, list2},

  /* ScalingList[3][0][i] and ScalingList[3][1][i] */
  {list1, list2, NULL, NULL, NULL, NULL},
};

static const i32 const forward_scaling[6] =
{
  26214, 23302, 20560, 18396, 16384, 14564
};

static const i32 const inverse_scaling[6] =
{
  40, 45, 51, 57, 64, 72
};

static void profile_and_level(struct buffer *b, i32 max_num_sub_layers, u32 level, HEVCEncInst inst);
static void short_term_ref_pic_set(struct container *c, struct sps *s, i32 idx);
static void cnt_ref_pic_set(struct container *c, struct sps *s);
static struct rps *get_ref_pic_set(struct container *c, i32 sps_id, i32 idx);
#if 0


static i32 rt_scan(struct pps *p);
static i32 z_scan(struct pps *p, i32 log2_min_size);
#endif
static void scaling_list(i32 foo);
#if 0
static i32 scaling_lists(struct sps *s, struct pps *p);
#endif
static u8 *scaling_factor(struct sps *s, struct pps *p, i32 log2_size,
                          i32 matrix_id);
static i32 *scaling(struct pps *p, u8 *sf, i32 log2_size, i32 qp_mod_6);
static i32 *inv_scaling(struct pps *p, u8 *sf, i32 log2_size, i32 qp_mod_6);
static void WriteVui(struct buffer *b, vui_t *vui);
static void UpdateVuiPresence(struct sps *sps);


/*------------------------------------------------------------------------------
  get_parameter_set
------------------------------------------------------------------------------*/
struct ps *get_parameter_set(struct container *c, enum nal_type type, i32 id)
{
  struct node *n;
  struct ps *p;

  for (n = c->parameter_set.tail; n; n = n->next)
  {
    p = (struct ps *)n;
    if ((p->nal_unit.type == type) && (p->id == id)) return p;
  }
  return NULL;
}

/*------------------------------------------------------------------------------
  create_parameter_set
------------------------------------------------------------------------------*/
struct ps *create_parameter_set(i32 type)
{
  struct ps *p;

  if (type == VPS_NUT)
  {
    if (!(p = malloc(sizeof(struct vps)))) return NULL;
    memcpy(p, &vps, sizeof(struct vps));
  }
  else if (type == SPS_NUT)
  {
    if (!(p = malloc(sizeof(struct sps)))) return NULL;
    memcpy(p, &sps, sizeof(struct sps));
  }
  else if (type == PPS_NUT)
  {
    if (!(p = malloc(sizeof(struct pps)))) return NULL;
    memcpy(p, &pps, sizeof(struct pps));
  }
  else if (type == RPS)
  {
    if (!(p = malloc(sizeof(struct rps)))) return NULL;
    memset(p, 0, sizeof(struct rps));
  }
  else
  {
    return NULL;
  }
  p->nal_unit.type = type;

  return p;
}

/*------------------------------------------------------------------------------
  init_parameter_set TODO: tiles/slices from api?
------------------------------------------------------------------------------*/
i32 init_parameter_set(struct sps *s, struct pps *p)
{
  struct queue *m = &p->ps.memory;
  i32 tmp;

  /* Sequence parameter set image size rounded up to next integer
   * multiple of min cb size */
  s->min_cb_size = tmp = 1 << s->log2_min_cb_size;
  s->width_min_cbs = (s->width + tmp - 1) / tmp * tmp;
  s->height_min_cbs = (s->height + tmp - 1) / tmp * tmp;

  /* Picture parameter set */
  p->ctb_per_row = (s->width + p->ctb_size - 1) / p->ctb_size;
  p->ctb_per_column = (s->height + p->ctb_size - 1) / p->ctb_size;
  p->ctb_per_picture = p->ctb_per_row * p->ctb_per_column;
  p->mcb_per_row = (s->width + s->min_cb_size - 1) / s->min_cb_size;
  p->mcb_per_column = (s->height + s->min_cb_size - 1) / s->min_cb_size;
  ASSERT(s->log2_min_tr_size < s->log2_min_cb_size);
  ASSERT(p->log2_max_tr_size <= MIN(p->log2_ctb_size, 5));

  /* Quantization parameter array resolution stuff...  */
  p->log2_qp_size = p->log2_ctb_size - p->diff_cu_qp_delta_depth;
  p->qp_size = 1 << p->log2_qp_size;
  p->qp_per_row = p->ctb_per_row * (p->ctb_size >> p->log2_qp_size);
  p->qp_per_column = p->ctb_per_column * (p->ctb_size >> p->log2_qp_size);

  /* Tiles TODO: test_bench.c comman line interface... */
  if (tile_demo(p, 0, 2, 2)) goto out;

  /* Coding tree block raster and tile scanning process  6.5.1 */
  if (rt_scan(p)) goto out;

  /* Z-scan order array initialization process 6.5.2 */
  if (z_scan(p, s->log2_min_tr_size)) goto out;

  /* Scaling list initialization */
  if (scaling_lists(s, p)) goto out;

  return OK;

out:
  qfree(m);
  return NOK;
}

/*------------------------------------------------------------------------------
  set_reference_pic_set
  poc[n*2  ] = delta_poc
  poc[n*2+1] = used_by_curr_pic
  poc[n*2  ] = 0, termination
------------------------------------------------------------------------------*/
i32 set_reference_pic_set(struct rps *r)
{
  struct queue *m = &r->ps.memory;
  struct buffer *b = &r->ps.b;
  i32 *poc = (i32 *)b->stream;
  i32 size = b->size / sizeof(i32);
  i32 tmp, i;

  if (r->ps.id < 0) return NOK;     /* Ref id sanity */

  for (tmp = 0, i = 0; i < size; i++)
  {
    if (poc[0] >= 0) break;
    if (poc[0] >= tmp) return NOK;    /* Delta poc sanity */
    if (poc[1] & ~1) return NOK;    /* Used flag sanity */
    tmp = poc[0];
    r->num_negative_pics++;
    poc += 2;
  }
  for (tmp = 0; i < size; i++)
  {
    if (poc[0] <= 0) break;
    if (poc[0] <= tmp) return NOK;
    if (poc[1] & ~1) return NOK;
    tmp = poc[0];
    r->num_positive_pics++;
    poc += 2;
  }

  r->ref_pic_s0 = qalloc(m, r->num_negative_pics, sizeof(struct ref_pic));
  r->ref_pic_s1 = qalloc(m, r->num_positive_pics, sizeof(struct ref_pic));
  if (!r->ref_pic_s1 && !r->ref_pic_s0) goto out;

  poc = (i32 *)b->stream;
  for (i = 0; i < r->num_negative_pics; i++)
  {
    r->ref_pic_s0[i].delta_poc        = poc[0];
    r->ref_pic_s0[i].used_by_curr_pic = poc[1];
    poc += 2;
  }
  for (i = 0; i < r->num_positive_pics; i++)
  {
    r->ref_pic_s1[i].delta_poc        = poc[0];
    r->ref_pic_s1[i].used_by_curr_pic = poc[1];
    poc += 2;
  }

  /*  Five lists what you can use when calculating pocs of reference
   *  pictures. See 8.3.2 Decoding process for reference picture set */
  tmp = r->num_negative_pics + r->num_positive_pics;
  if (!(r->before     = qalloc(m, tmp, sizeof(i32)))) goto out;
  if (!(r->after      = qalloc(m, tmp, sizeof(i32)))) goto out;;
  if (!(r->follow     = qalloc(m, tmp, sizeof(i32)))) goto out;;
  /*  if (!(r->lt_current = qalloc(m, tmp, sizeof(i32)))) goto out;;*/
  /*  if (!(r->lt_follow  = qalloc(m, tmp, sizeof(i32)))) goto out;;*/

  return OK;

out:
  qfree(m);
  return NOK;
}

/*------------------------------------------------------------------------------
  get_reference_pic_set
------------------------------------------------------------------------------*/
i32 get_reference_pic_set(struct rps *r)
{
  struct buffer *b = &r->ps.b;
  i32 *poc = (i32 *)b->stream;
  i32 i;

  for (i = 0; i < r->num_negative_pics; i++)
  {
    poc[0] = r->ref_pic_s0[i].delta_poc;
    poc[1] = r->ref_pic_s0[i].used_by_curr_pic;
    poc += 2;
  }
  for (i = 0; i < r->num_positive_pics; i++)
  {
    poc[0] = r->ref_pic_s1[i].delta_poc;
    poc[1] = r->ref_pic_s1[i].used_by_curr_pic;
    poc += 2;
  }
  poc[0] = 0; /* Zero termination */

  return OK;
}

/*------------------------------------------------------------------------------
  tile_demo
------------------------------------------------------------------------------*/
i32 tile_demo(struct pps *p, i32 demo_id, i32 c, i32 r)
{
  struct queue *m = &p->ps.memory;
  i32 i;

  if (demo_id == 0)
  {
    /* No tiles */
    p->tiles_enabled_flag = 0;
    p->uniform_spacing_flag = 0;
    p->num_tile_columns = 1;
    p->num_tile_rows = 1;

    p->col_width = qalloc(m, p->num_tile_columns, sizeof(i32));
    p->row_height = qalloc(m, p->num_tile_rows, sizeof(i32));
    if (!p->col_width || !p->row_height) return NOK;

    p->col_width[0] = p->ctb_per_row;
    p->row_height[0] = p->ctb_per_column;

    return OK;
  }

  /* Uniform spacing tile demo */
  p->tiles_enabled_flag = 0;
  p->uniform_spacing_flag = 1;
  p->num_tile_columns = c;
  p->num_tile_rows = r;

  p->col_width = qalloc(m, p->num_tile_columns, sizeof(i32));
  p->row_height = qalloc(m, p->num_tile_rows, sizeof(i32));
  if (!p->col_width || !p->row_height) return NOK;

  for (i = 0; i < p->num_tile_columns; i++)
  {
    p->col_width[i] =
      (i + 1) * p->ctb_per_row / p->num_tile_columns -
      (i * p->ctb_per_row) / p->num_tile_columns;
  }

  for (i = 0; i < p->num_tile_rows; i++)
  {
    p->row_height[i] =
      (i + 1) * p->ctb_per_column / p->num_tile_rows -
      (i * p->ctb_per_column) / p->num_tile_rows;
  }

  return OK;
}

/*------------------------------------------------------------------------------
  rt_scan 6.5.1 Coding tree block raster and tile scanning conversion
  process
------------------------------------------------------------------------------*/
i32 rt_scan(struct pps *p)
{
  struct queue *m = &p->ps.memory;
  i32 col_b[p->num_tile_columns + 1]; /* Note size because of ... */
  i32 row_b[p->num_tile_rows + 1];  /* ... p->tile_id calculation */
  i32 i, j, x, y, tmp;
  i32 tx = 0, ty = 0, id = 0;

  p->addr_rs_to_ts = qalloc(m, p->ctb_per_picture, sizeof(i32));
  p->addr_ts_to_rs = qalloc(m, p->ctb_per_picture, sizeof(i32));
  p->tile_id       = qalloc(m, p->ctb_per_picture, sizeof(i32));
  if (!p->addr_rs_to_ts || !p->addr_ts_to_rs || !p->tile_id) return NOK;

  for (i = col_b[0] = 0; i < p->num_tile_columns; i++)
  {
    col_b[i + 1] = col_b[i] + p->col_width[i];
  }
  for (i = row_b[0] = 0; i < p->num_tile_rows; i++)
  {
    row_b[i + 1] = row_b[i] + p->row_height[i];
  }

  /* Raster scan to tile scan */
  for (i = 0; i < p->ctb_per_picture; i++)
  {
    x = i % p->ctb_per_row;
    y = i / p->ctb_per_row;

    for (j = 0; j < p->num_tile_columns; j++)
    {
      if (x >= col_b[j]) tx = j;
    }
    for (j = 0; j < p->num_tile_rows; j++)
    {
      if (y >= row_b[j]) ty = j;
    }

    p->addr_rs_to_ts[i] = 0;
    for (j = 0; j < tx; j++)
    {
      p->addr_rs_to_ts[i] +=
        p->row_height[ty] * p->col_width[j];
    }
    for (j = 0; j < ty; j++)
    {
      p->addr_rs_to_ts[i] +=
        p->ctb_per_row * p->row_height[j];
    }
    p->addr_rs_to_ts[i] +=
      (y - row_b[ty]) * p->col_width[tx] + x - col_b[tx];
  }

  /* Tile scan to raster scan */
  for (i = 0; i < p->ctb_per_picture; i++)
  {
    p->addr_ts_to_rs[p->addr_rs_to_ts[i]] = i;
  }

  /* Tile id */
  for (j = 0; j < p->num_tile_rows; j++)
    for (i = 0; i < p->num_tile_columns; i++, id++)
      for (y = row_b[j]; y < row_b[j + 1]; y++)
        for (x = col_b[i]; x < col_b[i + 1]; x++)
        {
          tmp = y * p->ctb_per_row + x;
          p->tile_id[p->addr_rs_to_ts[tmp]] = id;
        }

#if 0

  printf("\nscannin process: ctbAddrRs\n");
  for (i = 0; i < p->ctb_per_picture; i++)
  {
    printf("%4i ", i);
    if (!((i + 1) % p->ctb_per_row)) printf("\n");
  }

  printf("\nscannin process: ctbAddrRStoTS\n");
  for (i = 0; i < p->ctb_per_picture; i++)
  {
    printf("%4i ", p->addr_rs_to_ts[i]);
    if (!((i + 1) % p->ctb_per_row)) printf("\n");
  }

  printf("\nscannin process: ctbAddrTStoRS\n");
  for (i = 0; i < p->ctb_per_picture; i++)
  {
    printf("%4i ", p->addr_ts_to_rs[i]);
    if (!((i + 1) % p->ctb_per_row)) printf("\n");
  }

  printf("\nscannin process: tile_id[addr_rs_to_ts[i]]\n");
  for (i = 0; i < p->ctb_per_picture; i++)
  {
    printf("%4i ", p->tile_id[p->addr_rs_to_ts[i]]);
    if (!((i + 1) % p->ctb_per_row)) printf("\n");
  }
#endif
  return OK;
}

/*------------------------------------------------------------------------------
  z_scan 6.5.2 Z-scan order array initialization process
------------------------------------------------------------------------------*/
#if 0
void print_scanning_process(i32 **zs, i32 w, i32 h)
{
  printf("\nscannin process: min_tb_addr_zs[x][y]\n");
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      printf("%3i ", zs[x][y]);
    }
    printf("\n");
  }
}
#else
#define print_scanning_process(zs,x,y) {}
#endif

i32 z_scan(struct pps *p, i32 log2_min_size)
{
  struct queue *m = &p->ps.memory;
  i32 x, y, w, h, i, j, k;
  i32 bx, by, num;
  i32 log2_size;
  i32 **zs;

  log2_size = p->log2_ctb_size - log2_min_size;
  w = x = p->ctb_per_row << log2_size;
  h = y = p->ctb_per_column << log2_size;
  if (!(zs = (i32 **)malloc_array(m, x, y, sizeof(i32)))) return NOK;

  for (y = 0; y < h; y++)
  {
    for (x = 0; x < w; x++)
    {
      bx = (x << log2_min_size) >> p->log2_ctb_size;
      by = (y << log2_min_size) >> p->log2_ctb_size;

      num = p->ctb_per_row * by + bx;
      zs[x][y] = p->addr_rs_to_ts[num] << (log2_size * 2);

      for (i = 0, j = 0; i < log2_size; i++)
      {
        k = 1 << i;
        j += (k & x ? k * k : 0) + (k & y ? 2 * k * k : 0);
      }
      zs[x][y] += j;
    }
  }

  print_scanning_process(zs, w, h);
  p->min_tb_addr_zs = zs;

  return OK;
}

/*------------------------------------------------------------------------------
  scaling_lists
------------------------------------------------------------------------------*/
i32 scaling_lists(struct sps *s, struct pps *p)
{
  i32 list_cnt[6] = {0, 0, 6, 6, 6, 2};
  i32 i, j, k;
  u8 *sf;

  /* Scaling factor */
  for (i = 2; i < 6; i++)       /* log2_size */
  {
    for (j = 0; j < list_cnt[i]; j++)   /* matrixId */
    {
      p->scaling_factor[i][j] = scaling_factor(s, p, i, j);
      if (!p->scaling_factor[i][j]) return NOK;
    }
  }

  /* Scaling list derived from scaling factor */
  for (i = 2; i < 6; i++)       /* log2_size */
  {
    for (j = 0; j < list_cnt[i]; j++)   /* matrixId */
    {
      for (k = 0; k < 6; k++)   /* qp%6  */
      {
        sf = p->scaling_factor[i][j];

        /* Forward scaling */
        p->scaling[i][j][k] = scaling(p, sf, i, k);
        if (!p->scaling[i][j][k]) return NOK;

        /* Inverse scaling */
        p->inv_scaling[i][j][k] =
          inv_scaling(p, sf, i, k);
        if (!p->inv_scaling[i][j][k]) return NOK;
      }
    }
  }

  return OK;
}

/*------------------------------------------------------------------------------
  scaling_factor TODO: custom scaling list. NOTE: When
  scaling_list_dc_coef_minus8 is not present, it is inferred to be equal
  to 8.
------------------------------------------------------------------------------*/
u8 *scaling_factor(struct sps *s, struct pps *p, i32 log2_size, i32 matrix_id)
{
  struct queue *m = &p->ps.memory;
  const u8 *scaling_list = default_scaling_list[log2_size - 2][matrix_id];
  struct comp const *scan;
  i32 size, i, j, k, x, y;
  u8 *list;

  size = 1 << log2_size;
  if (!(list = qalloc(m, size * size, sizeof(u8)))) return NULL;

  /* If scaling lists are not used all lists uses default value 16 */
  if (!s->scaling_list_enable_flag)
  {
    memset(list, 0x10, size * size);
    return list;
  }

  switch (size)
  {
    case 4:
      scan = scan_order[2][0];  /* scan block: size 4x4 up and right */
      for (i = 0; i < 16; i++)
      {
        x = scan[i].x;
        y = scan[i].y;
        list[x * 4 + y] = scaling_list[i];
      }
      break;
    case 8:
      scan = scan_order[3][0];  /* scan block: size 8x8 up and right */
      for (i = 0; i < 64; i++)
      {
        x = scan[i].x;
        y = scan[i].y;
        list[x * 8 + y] = scaling_list[i];
      }
      break;
    case 16:
      scan = scan_order[3][0];  /* scan block: size 8x8 up and right */
      for (i = 0; i < 64; i++)
      {
        for (j = 0; j < 2; j++)
        {
          for (k = 0; k < 2; k++)
          {
            x = 2 * scan[i].x + k;
            y = 2 * scan[i].y + j;
            list[x * 16 + y] = scaling_list[i];
          }
        }
      }
      list[0] = 16; /* TODO: scaling_list_dc_coef_minus8[][]+8 */
      break;
    case 32:
      scan = scan_order[3][0];  /* scan block: size 8x8 up and right */
      for (i = 0; i < 64; i++)
      {
        for (j = 0; j < 4; j++)
        {
          for (k = 0; k < 4; k++)
          {
            x = 4 * scan[i].x + k;
            y = 4 * scan[i].y + j;
            list[x * 32 + y] = scaling_list[i];
          }
        }
      }
      list[0] = 16; /* TODO: scaling_list_dc_coef_minus8[][]+8 */
      break;
  }

  return list;
}

/*------------------------------------------------------------------------------
  scaling
------------------------------------------------------------------------------*/
i32 *scaling(struct pps *p, u8 *sf, i32 log2_size, i32 qp_mod_6)
{
  struct queue *m = &p->ps.memory;
  i32 size, i, j;
  i32 scale = forward_scaling[qp_mod_6] << 4;
  i32 *list;

  size = 1 << log2_size;
  if (!(list = qalloc(m, size * size, sizeof(i32)))) return NULL;

  for (i = 0; i < size; i++)
  {
    for (j = 0; j < size; j++)
    {
      list[i * size + j] = scale / sf[i * size + j];
    }
  }

  return list;
}

/*------------------------------------------------------------------------------
  inv_scaling
------------------------------------------------------------------------------*/
i32 *inv_scaling(struct pps *p, u8 *sf, i32 log2_size, i32 qp_mod_6)
{
  struct queue *m = &p->ps.memory;
  i32 size, i, j;
  i32 scale = inverse_scaling[qp_mod_6];
  i32 *list;

  size = 1 << log2_size;
  if (!(list = qalloc(m, size * size, sizeof(i32)))) return NULL;

  for (i = 0; i < size; i++)
  {
    for (j = 0; j < size; j++)
    {
      list[i * size + j] = scale * sf[i * size + j];
    }
  }

  return list;
}

/*------------------------------------------------------------------------------
  free_parameter_set
------------------------------------------------------------------------------*/
void free_parameter_set(struct ps *ps)
{
  qfree(&ps->memory);
  free(ps);
}

/*------------------------------------------------------------------------------
  free_parameter_sets
------------------------------------------------------------------------------*/
void free_parameter_sets(struct container *c)
{
  struct node *n;

  while ((n = queue_get(&c->parameter_set)))
  {
    free_parameter_set((struct ps *)n);
  }
}

/*------------------------------------------------------------------------------
  remove_parameter_set
------------------------------------------------------------------------------*/
void remove_parameter_set(struct container *c, enum nal_type type, i32 id)
{
  struct ps *p;

  if (!(p = get_parameter_set(c, type, id))) return;
  queue_remove(&c->parameter_set, (struct node *)p);
  free_parameter_set(p);
}

/*------------------------------------------------------------------------------
  video_parameter_set See 7.4.2.1 Video parameter set RBSP semantics
------------------------------------------------------------------------------*/
void video_parameter_set(struct vps *v, HEVCEncInst inst)
{
  struct hevc_instance *hevc_instance = (struct hevc_instance *)inst;
  struct buffer *b = &v->ps.b;
  i32 i;
  if (v->hevcStrmMode == HEVCENC_BYTE_STREAM)
  {
    put_bits_startcode(b);
  }
  /* Nal unit header */
  nal_unit(b, &v->ps.nal_unit);

  COMMENT(b, "video_parameter_set_id")
  put_bit(b, v->ps.id, 4);

  COMMENT(b, "vps_reserved_three_2bits")
  put_bit(b, 3, 2);

  COMMENT(b, "vps_max_layers_minus1")
  put_bit(b, 0, 6);

  COMMENT(b, "vps_max_sub_layers_minus1")
  put_bit(b, v->max_num_sub_layers - 1, 3);

  COMMENT(b, "vps_temporal_id_nesting_flag")
  put_bit(b, v->temporal_id_nesting_flag, 1);

  COMMENT(b, "vps_reserved_0xffff_16bits")
  put_bit(b, 255, 8);
  put_bit(b, 255, 8);

  profile_and_level(b, v->max_num_sub_layers, v->general_level_idc, inst);

  COMMENT(b, "vps_sub_layer_ordering_info_present_flag")
  put_bit(b, v->slo_info_present_flag, 1);

  if (v->slo_info_present_flag)
  {
    for (i = 0; i < v->max_num_sub_layers; i++)
    {
      COMMENT(b, "vps_max_dec_pic_buffering_minux1[%i]", i)
      put_bit_ue(b, v->max_dec_pic_buffering[i] - 1);

      COMMENT(b, "vps_max_num_reorder_pics[%i]", i)
      put_bit_ue(b, v->max_num_reorder_pics[i]);

      COMMENT(b, "vps_max_latency_increase_plus1[%i]", i)
      put_bit_ue(b, v->max_latency_increase[i] + 1);
    }
  }

  COMMENT(b, "vps_max_layer_id")
  put_bit(b, 0, 6);

  COMMENT(b, "vps_num_layer_sets_minus1 ")
  put_bit_ue(b, 0);

  COMMENT(b, "vps_timing_info_present_flag")
  put_bit(b, 0, 1);

  /* TODO: if (vps_timing_info_present_flag)... */

  COMMENT(b, "vps_extension_flag")
  put_bit(b, 0, 1);

  rbsp_trailing_bits(b);
}


/*------------------------------------------------------------------------------
  profile_and_level
------------------------------------------------------------------------------*/
void profile_and_level(struct buffer *b, i32 max_num_sub_layers, u32 level, HEVCEncInst inst)
{
  struct hevc_instance *hevc_instance = (struct hevc_instance *)inst;
  preProcess_s *preProcess = &hevc_instance->preProcess;
  i32 i;

  COMMENT(b, "general_profile_space")
  put_bit(b, 0, 2);

  COMMENT(b, "general_tier_flag")
  put_bit(b, 0, 1);

  COMMENT(b, "general_profile_idc")
  put_bit(b, 1, 5);

  for (i = 0; i < 32; i++)
  {
    COMMENT(b, "general_profile_compatibility_flag[%i]", i)
    put_bit(b, 0, 1);
  }

  COMMENT(b, "general_progressive_source_flag")
  put_bit(b, !preProcess->interlacedFrame, 1);

  COMMENT(b, "general_interlaced_source_flag")
  put_bit(b, preProcess->interlacedFrame, 1);

  COMMENT(b, "general_non_packed_constraint_flag")
  put_bit(b, 0, 1);

  COMMENT(b, "general_frame_only_constraint_flag")
  put_bit(b, 0, 1);

  COMMENT(b, "general_reserved_zero_44bits")
  put_bit(b, 0, 8);
  put_bit(b, 0, 8);
  put_bit(b, 0, 8);
  put_bit(b, 0, 8);
  put_bit(b, 0, 8);
  put_bit(b, 0, 4);

  COMMENT(b, "general_level_idc")
  put_bit(b, level, 8);

  /* TODO: for( i = 0; i < MaxNumSubLayersMinus1; i++ ).... */
  ASSERT(max_num_sub_layers < 2);
}


/*------------------------------------------------------------------------------
  sequence_parameter_set
------------------------------------------------------------------------------*/
void sequence_parameter_set(struct container *c, struct sps *s, HEVCEncInst inst)
{
  struct hevc_instance *hevc_instance = (struct hevc_instance *)inst;
  struct buffer *b = &s->ps.b;
  i32 i;
  if (s->hevcStrmMode == HEVCENC_BYTE_STREAM)
  {
    put_bits_startcode(b);
  }

  /* Nal unit header */
  nal_unit(b, &s->ps.nal_unit);

  COMMENT(b, "video_parameter_set_id")
  put_bit(b, s->vps_id, 4);

  COMMENT(b, "sps_max_sub_layers_minus1")
  put_bit(b, s->max_num_sub_layers - 1, 3);

  COMMENT(b, "sps_temporal_id_nesting_flag ")
  put_bit(b, s->temporal_id_nesting_flag, 1);

  profile_and_level(b, s->max_num_sub_layers, s->general_level_idc, inst);

  COMMENT(b, "seq_parameter_set_id")
  put_bit_ue(b, s->ps.id);

  COMMENT(b, "chroma_format_idc")
  put_bit_ue(b, s->chroma_format_idc);

  /* TODO: if (chroma_format_idc == 3)... */
  ASSERT(s->chroma_format_idc == 1);

  /* Note that pic_width_in_luma_samples and pic_height_in_luma_samples
   * shall be an integer multiple of (1 << Log2MinCbSize). */
  COMMENT(b, "pic_width_in_luma_samples")
  put_bit_ue(b, s->width_min_cbs);

  COMMENT(b, "pic_height_in_luma_samples")
  put_bit_ue(b, s->height_min_cbs);

  COMMENT(b, "conformance_window_flag")
  if (s->width_min_cbs == s->width && s->height_min_cbs == s->height)
  {
    put_bit(b, 0, 1);
  }
  else
  {
    put_bit(b, 1, 1);

    COMMENT(b, "conf_win_left_offset")
    put_bit_ue(b, s->frameCropLeftOffset);

    COMMENT(b, "conf_win_right_offset")
    put_bit_ue(b, s->frameCropRightOffset);

    COMMENT(b, "conf_win_top_offset ")
    put_bit_ue(b, s->frameCropTopOffset);

    COMMENT(b, "conf_win_bottom_offset")
    put_bit_ue(b, s->frameCropBottomOffset);
  }

  COMMENT(b, "bit_depth_luma_minus8")
  put_bit_ue(b, 0);

  COMMENT(b, "bit_depth_chroma_minus8")
  put_bit_ue(b, 0);

  /* TODO: if (pcm_enabled_flag)... */
  ASSERT(!s->pcm_enabled_flag);

  COMMENT(b, "log2_max_pic_order_cnt_lsb_minus4")
  put_bit_ue(b, s->log2_max_pic_order_cnt_lsb - 4);

  COMMENT(b, "sps_sub_layer_ordering_info_present_flag")
  put_bit(b, s->slo_info_present_flag, 1);

  if (s->slo_info_present_flag)
  {
    for (i = 0; i < s->max_num_sub_layers; i++)
    {
      COMMENT(b, "sps_max_dec_pic_buffering_minus1[%i]", i)
      put_bit_ue(b, s->max_dec_pic_buffering[i] - 1);

      COMMENT(b, "sps_max_num_reorder_pics[%i]", i)
      put_bit_ue(b, s->max_num_reorder_pics[i]);

      COMMENT(b, "sps_max_latency_increase_plus1[%i]", i)
      put_bit_ue(b, s->max_latency_increase[i] + 1);
    }
  }

  COMMENT(b, "log2_min_coding_block_size_minus3")
  put_bit_ue(b, s->log2_min_cb_size - 3);

  COMMENT(b, "log2_diff_max_min_coding_block_size")
  put_bit_ue(b, s->log2_diff_cb_size);

  COMMENT(b, "log2_min_transform_block_size_minus2")
  put_bit_ue(b, s->log2_min_tr_size - 2);

  COMMENT(b, "log2_diff_max_min_transform_block_size")
  put_bit_ue(b, s->log2_diff_tr_size);

  COMMENT(b, "max_transform_hierarchy_depth_inter")
  put_bit_ue(b, s->max_tr_hierarchy_depth_inter);

  COMMENT(b, "max_transform_hierarchy_depth_intra")
  put_bit_ue(b, s->max_tr_hierarchy_depth_intra);

  COMMENT(b, "scaling_list_enable_flag")
  put_bit(b, s->scaling_list_enable_flag, 1);

  if (s->scaling_list_enable_flag)
  {
    COMMENT(b, "sps_scaling_list_data_present_flag");
    put_bit(b, s->scaling_list_data_present_flag, 1);

    if (s->scaling_list_data_present_flag)
    {
      scaling_list(0);
    }
  }

  COMMENT(b, "amp_enabled_flag")
  put_bit(b, s->amp_enabled_flag, 1);

  COMMENT(b, "sample_adaptive_offset_enabled_flag")
  put_bit(b, s->sao_enabled_flag, 1);

  COMMENT(b, "pcm_enabled_flag")
  put_bit(b, s->pcm_enabled_flag, 1);

  /* TODO if (pcm_enabled_flag)... */
  ASSERT(!s->pcm_enabled_flag);

  /* Let's find out how many referense picture sets we have and set
   * indexing */
  cnt_ref_pic_set(c, s);

  COMMENT(b, "num_short_term_ref_pic_sets")
  put_bit_ue(b, s->num_short_term_ref_pic_sets);

  for (i = 0; i < s->num_short_term_ref_pic_sets; i++)
  {
    short_term_ref_pic_set(c, s, i);
  }

  COMMENT(b, "long_term_ref_pics_present_flag")
  put_bit(b, s->long_term_ref_pics_present_flag, 1);

  /* TODO: if (long_term_ref_pics_present_flag)... */
  ASSERT(!s->long_term_ref_pics_present_flag);

  COMMENT(b, "sps_temporal_mvp_enable_flag")
  put_bit(b, s->temporal_mvp_enable_flag, 1);

  COMMENT(b, "strong_intra_smoothing_enabled_flag")
  put_bit(b, s->strong_intra_smoothing_enabled_flag , 1);
  s->vui.bitStreamRestrictionFlag = 1;
  UpdateVuiPresence(s);

  COMMENT(b, "vui_parameters_present_flag")
  put_bit(b, s->vui_parameters_present_flag, 1);

  /* TODO: if (vui_parameters_present_flag)... */
  if (s->vui_parameters_present_flag)
  {
    WriteVui(b, &s->vui);
  }

  COMMENT(b, "sps_extension_flag")
  put_bit(b, 0, 1);

  rbsp_trailing_bits(b);
}

/*------------------------------------------------------------------------------
  cnt_ref_pic_set scans every RPS and if r->sps_id is same than s->sps_id
  it is part of this referense picture set and referred as idx
------------------------------------------------------------------------------*/
void cnt_ref_pic_set(struct container *c, struct sps *s)
{
  struct node *n;
  struct rps *r;
  i32 idx = 0;

  for (n = c->parameter_set.tail; n; n = n->next)
  {
    r = (struct rps *)n;
    if (r->ps.nal_unit.type != RPS) continue;
    if (r->sps_id != s->ps.id) continue;

    /* NOTE that sps supports only 64 sets */
    if (idx < 64)
    {
      r->idx = idx++;
    }
    else
    {
      r->idx = -1;
    }
  }
  idx--;
  s->num_short_term_ref_pic_sets = idx;
}

/*------------------------------------------------------------------------------
  get_reference_pic_set
------------------------------------------------------------------------------*/
struct rps *get_ref_pic_set(struct container *c, i32 sps_id, i32 idx)
{
  struct node *n;
  struct rps *r;

  for (n = c->parameter_set.tail; n; n = n->next)
  {
    r = (struct rps *)n;
    if (r->ps.nal_unit.type != RPS) continue;
    if (r->sps_id != sps_id) continue;
    if (r->idx == idx) return r;
  }
  return NULL;
}

/*------------------------------------------------------------------------------
  init_poc_list TODO long term stuff...
------------------------------------------------------------------------------*/
void init_poc_list(struct rps *r, i32 poc)
{
  struct ref_pic *p;
  i32 tmp, i, j, k = 0;

  tmp = r->num_negative_pics + r->num_positive_pics;
  memset(r->before, 0xff, tmp * sizeof(i32));
  memset(r->after,  0xff, tmp * sizeof(i32));
  memset(r->follow, 0xff, tmp * sizeof(i32));

  for (i = 0, j = 0; i < r->num_negative_pics; i++)
  {
    p = &r->ref_pic_s0[i];
    if (p->used_by_curr_pic)
    {
      r->before[j++] = poc + p->delta_poc;
    }
    else
    {
      r->follow[k++] = poc + p->delta_poc;
    }
  }
  r->before_cnt = j;

  for (i = 0, j = 0; i < r->num_positive_pics; i++)
  {
    p = &r->ref_pic_s1[i];
    if (p->used_by_curr_pic)
    {
      r->after[j++] = poc + p->delta_poc;
    }
    else
    {
      r->follow[k++] = poc + p->delta_poc;
    }
  }
  r->after_cnt = j;
  r->follow_cnt = k;
}

/*------------------------------------------------------------------------------
  ref_pic_marking TODO long term stuff...
------------------------------------------------------------------------------*/
i32 ref_pic_marking(struct container *c, struct rps *r)
{
  struct sw_picture *p;
  struct node *n;
  i32 i, ret = OK;

  /* First mark every picture to not used as referene */
  for (n = c->picture.tail; n; n = n->next)
  {
    p = (struct sw_picture *)n;
    p->reference = false;
  }

  /* Then mark pictures to used as reference and if not found fix list
   * and note caller that it should use correct rps so that every
   * reference picture is really available */
  for (i = 0; i < r->before_cnt; i++)
  {
    if ((p = get_picture(c, r->before[i])))
    {
      p->reference = true;
    }
    else
    {
      r->before[i] = -1;
      ret = NOK;
    }
  }
  for (i = 0; i < r->after_cnt; i++)
  {
    if ((p = get_picture(c, r->after[i])))
    {
      p->reference = true;
    }
    else
    {
      r->after[i] = -1;
      ret = NOK;
    }
  }
  for (i = 0; i < r->follow_cnt; i++)
  {
    if ((p = get_picture(c, r->follow[i])))
    {
      p->reference = true;
    }
    else
    {
      r->follow[i] = -1;
      ret = NOK;
    }
  }

  /* Finally reset poc cnt to be sure that picture is not used as
   * referene pictue in future. Encoder can't use picture if it is not in
   * the decoders buffer anymore, picture might be available here and
   * ref_pic_marking() fails. */
  for (n = c->picture.tail; n; n = n->next)
  {
    p = (struct sw_picture *)n;
    if (!p->reference) p->poc = -1;
  }
  return ret;
}

/*------------------------------------------------------------------------------
  short_term_ref_pic_set TODO Referense picture set prediction stuff not
  supported yet
------------------------------------------------------------------------------*/
void short_term_ref_pic_set(struct container *c, struct sps *s, i32 idx)
{
  struct buffer *b = &s->ps.b;
  struct rps *r;
  struct ref_pic *p;
  i32 i, tmp;

  r = get_ref_pic_set(c, s->ps.id, idx);
  ASSERT(r);

  if (idx)
  {
    COMMENT(b, "inter_ref_pic_set_prediction_flag idx %i", idx)
    put_bit(b, 0, 1);
  }

  /*  if (inter_ref_pic_set_prediction_flag) {*/
  if (0)
  {
#if 0
    if (idx == s->num_short_term_ref_pic_sets)
    {
      COMMENT(b, "delta_idx_minus1")
      put_bit_ue(b, ref_pic_set->delta_idx - 1);
    }
    COMMENT(b, "delta_rps_sign")
    put_bit(b, ref_pic_set->delta_rps_sign, 1);

    COMMENT(b, "abs_delta_rps_minus1")
    put_bit_ue(b, ref_pic_set->abs_delta_rps - 1);

    for (i = 0; i <= foo[idx]; i++)   /* TODO */
    {
      COMMENT(b, "used_by_curr_pic_flag[%i] foo %i", i, foo[idx])
      put_bit(b, ref_pic_set->used_by_curr_pic_flag[i] , 1);

      if (!ref_pic_set->used_by_curr_pic_flag[i])
      {
        COMMENT(b, "use_delta_flag[%i]", i)
        put_bit(b, ref_pic_set->use_delta_flag[i], 1);
      }
    }
#endif
  }
  else
  {
    COMMENT(b, "num_negative_pics")
    put_bit_ue(b, r->num_negative_pics);

    COMMENT(b, "num_positive_pics")
    put_bit_ue(b, r->num_positive_pics);

    for (tmp = 0, i = 0; i < r->num_negative_pics; i++)
    {
      p = &r->ref_pic_s0[i];
      COMMENT(b, "delta_poc_s0_minus1[%i]", i)
      put_bit_ue(b, -p->delta_poc - 1 + tmp);
      tmp = p->delta_poc;

      COMMENT(b, "used_by_curr_pic_s0_flag[%i]", i)
      put_bit(b, p->used_by_curr_pic, 1);
    }

    for (tmp = 0, i = 0; i < r->num_positive_pics; i++)
    {
      p = &r->ref_pic_s1[i];
      COMMENT(b, "delta_poc_s1_minus1[%i]", i)
      put_bit_ue(b, p->delta_poc - 1 - tmp);
      tmp = p->delta_poc;

      COMMENT(b, "used_by_curr_pic_s1_flag[%i]", i)
      put_bit(b, p->used_by_curr_pic, 1);
    }
  }
}

/*------------------------------------------------------------------------------
  picture_parameter_set
------------------------------------------------------------------------------*/
void picture_parameter_set(struct pps *p)
{
  struct buffer *b = &p->ps.b;
  i32 i;
  if (p->hevcStrmMode == HEVCENC_BYTE_STREAM)
  {
    put_bits_startcode(b);
  }

  /* Nal unit header  */
  nal_unit(b, &p->ps.nal_unit);

  COMMENT(b, "pic_parameter_set_id")
  put_bit_ue(b, p->ps.id);
  COMMENT(b, "seq_parameter_set_id")
  put_bit_ue(b, p->sps_id);

  COMMENT(b, "dependent_slice_segments_enabled_flag")
  put_bit(b, p->dependent_slice_enabled_flag, 1);

  COMMENT(b, "output_flag_present_flag")
  put_bit(b, p->output_flag_present_flag, 1);

  COMMENT(b, "num_extra_slice_header_bits")
  put_bit(b, 0, 3);

  COMMENT(b, "sign_data_hiding_flag")
  put_bit(b, p->sign_data_hiding_flag, 1);

  COMMENT(b, "cabac_init_present_flag")
  put_bit(b, p->cabac_init_present_flag, 1);

  COMMENT(b, "num_ref_idx_l0_default_active_minus1")
  put_bit_ue(b, p->num_ref_idx_l0_default_active - 1);

  COMMENT(b, "num_ref_idx_l1_default_active_minus1")
  put_bit_ue(b, p->num_ref_idx_l1_default_active - 1);

  COMMENT(b, "init_qp_minus26")
  put_bit_se(b, p->init_qp - 26);

  COMMENT(b, "constrained_intra_pred_flag")
  put_bit(b, p->constrained_intra_pred_flag, 1);

  COMMENT(b, "transform_skip_enabled_flag")
  put_bit(b, p->transform_skip_enabled_flag, 1);

  COMMENT(b, "cu_qp_delta_enabled_flag")
  put_bit(b, p->cu_qp_delta_enabled_flag, 1);

  if (p->cu_qp_delta_enabled_flag)
  {
    COMMENT(b, "diff_cu_qp_delta_depth")
    put_bit_ue(b, p->diff_cu_qp_delta_depth);
  }

  COMMENT(b, "pps_cb_qp_offset")
  put_bit_se(b, p->cb_qp_offset);

  COMMENT(b, "pps_cr_qp_offset")
  put_bit_se(b, p->cr_qp_offset);

  COMMENT(b, "pps_slice_chroma_qp_offsets_present_flag ")
  put_bit(b, p->slice_chroma_qp_offsets_present_flag, 1);

  COMMENT(b, "weighted_pred_flag")
  put_bit(b, p->weighted_pred_flag, 1);

  COMMENT(b, "weighted_bipred_flag")
  put_bit(b, p->weighted_bipred_flag, 1);

  COMMENT(b, "transquant_bypass_enable_flag")
  put_bit(b, p->transquant_bypass_enable_flag, 1);

  COMMENT(b, "tiles_enabled_flag")
  put_bit(b, p->tiles_enabled_flag, 1);

  COMMENT(b, "entropy_coding_sync_enabled_flag")
  put_bit(b, p->entropy_coding_sync_enabled_flag, 1);

  if (p->tiles_enabled_flag)
  {
    COMMENT(b, "num_tile_columns_minus1")
    put_bit_ue(b, p->num_tile_columns - 1);

    COMMENT(b, "num_tile_rows_minus1")
    put_bit_ue(b, p->num_tile_rows - 1);

    COMMENT(b, "uniform_spacing_flag")
    put_bit(b, p->uniform_spacing_flag, 1);

    if (!p->uniform_spacing_flag)
    {
      for (i = 0; i < p->num_tile_columns - 1; i++)
      {
        COMMENT(b, "column_width_minus1[%i]", i)
        put_bit_ue(b, p->col_width[i] - 1);
      }

      for (i = 0; i < p->num_tile_rows - 1; i++)
      {
        COMMENT(b, "row_height_minus1[[%i]", i)
        put_bit_ue(b, p->row_height[i] - 1);
      }
    }
    COMMENT(b, "loop_filter_across_tiles_enabled_flag")
    put_bit(b, p->loop_filter_across_tiles_enabled_flag, 1);
  }

  COMMENT(b, "loop_filter_across_slices_enabled_flag")
  put_bit(b, p->loop_filter_across_slices_enabled_flag, 1);

  COMMENT(b, "deblocking_filter_control_present_flag")
  put_bit(b, p->deblocking_filter_control_present_flag, 1);

  if (p->deblocking_filter_control_present_flag)
  {
    COMMENT(b, "deblocking_filter_override_enabled_flag")
    put_bit(b, p->deblocking_filter_override_enabled_flag, 1);

    COMMENT(b, "pps_deblocking_filter_disabled_flag ")
    put_bit(b, p->deblocking_filter_disabled_flag, 1);

    if (!p->deblocking_filter_disabled_flag)
    {
      COMMENT(b, "pps_beta_offset_div2")
      put_bit_se(b, p->beta_offset / 2);

      COMMENT(b, "pps_tc_offset_div2")
      put_bit_se(b, p->tc_offset / 2);
    }
  }

  COMMENT(b, "pps_scaling_list_data_present_flag");
  put_bit(b, p->scaling_list_data_present_flag, 1);

  if (p->scaling_list_data_present_flag)
  {
    scaling_list(0);
  }

  COMMENT(b, "lists_modification_present_flag")
  put_bit(b, p->lists_modification_present_flag, 1);

  COMMENT(b, "log2_parallel_merge_level_minus2")
  put_bit_ue(b, p->log2_parallel_merge_level - 2);

  COMMENT(b, "slice_segment_header_extension_present_flag")
  put_bit(b, 0, 1);

  COMMENT(b, "pps_extension_flag ")
  put_bit(b, 0, 1);

  rbsp_trailing_bits(b);
}

/*------------------------------------------------------------------------------
  scaling_list TODO
------------------------------------------------------------------------------*/
void scaling_list(i32 foo)
{
  foo = foo;
  ASSERT(0);
}
void endofsequence(struct buffer *b, u32 byte_stream)
{
  struct nal_unit nal_unit_val;
  nal_unit_val.type = EOS_NUT;
  nal_unit_val.temporal_id = 0;
  if (byte_stream == HEVCENC_BYTE_STREAM)
  {
    put_bits_startcode(b);
  }
  /* Nal unit header  */
  nal_unit(b, &nal_unit_val);
  rbsp_flush_bits(b);
}


/*------------------------------------------------------------------------------

    Function: HEVCSpsSetVui

        Functional description:
          Set VUI parameters in the SPS structure

        Inputs:
          u32 timeScale
          u32 numUnitsInTick
          bool zeroReorderFrames

        Outputs:
          seqParamSet_t *       pointer to SPS structure

------------------------------------------------------------------------------*/
void HEVCSpsSetVuiTimigInfo(struct sps *sps, u32 timeScale, u32 numUnitsInTick)
{
  if (timeScale)
    sps->vui_parameters_present_flag = ENCHW_YES;

  sps->vui.timeScale = timeScale; /* used as timing_info_present_flag */
  sps->vui.numUnitsInTick = numUnitsInTick;
}

void HEVCSpsSetVuiVideoInfo(struct sps *sps, u32 videoFullRange)
{
  if (videoFullRange)
    sps->vui_parameters_present_flag = ENCHW_YES;

  sps->vui.videoFullRange = videoFullRange;   /* used as video_signal_type_present_flag */
}

void HEVCSpsSetVuiAspectRatio(struct sps *sps, u32 sampleAspectRatioWidth,
                              u32 sampleAspectRatioHeight)
{
  ASSERT(sampleAspectRatioWidth < (1 << 16));
  ASSERT(sampleAspectRatioHeight < (1 << 16));

  if (sampleAspectRatioWidth)
    sps->vui_parameters_present_flag = ENCHW_YES;

  sps->vui.sarWidth = sampleAspectRatioWidth; /* used as aspect_ratio_info_present_flag */
  sps->vui.sarHeight = sampleAspectRatioHeight;
}

/*------------------------------------------------------------------------------

    Function: HEVCSpsSetVuiHrd

        Functional description:
          Set VUI HRD parameters in the SPS structure

        Inputs:
          seqParamSet_t *       pointer to SPS structure

        Outputs:
          seqParamSet_t *       pointer to SPS structure

------------------------------------------------------------------------------*/

void HEVCSpsSetVuiHrd(struct sps *sps, u32 present)
{
  ASSERT(sps);

  sps->vui.nalHrdParametersPresentFlag = present;

  if (present)
    sps->vui_parameters_present_flag = ENCHW_YES;
  else
  {
    return;
  }

  ASSERT(sps->vui.timeScale && sps->vui.numUnitsInTick);  /* set these first */

  sps->vui.initialCpbRemovalDelayLength = 24;
  sps->vui.cpbRemovalDelayLength = 24;
  sps->vui.dpbOutputDelayLength = 24;

  {
    u32 n = 1;

    while (sps->vui.numUnitsInTick > (1U << n))
    {
      n++;
    }
    sps->vui.timeOffsetLength = n;

  }
}

/*------------------------------------------------------------------------------

    Function: HEVCSpsSetVuiHrdBitRate

        Functional description:
          Set VUI HRD bit rate in the SPS structure

        Inputs:
          seqParamSet_t *       pointer to SPS structure
          u32 bitRate

        Outputs:
          seqParamSet_t *       pointer to SPS structure

------------------------------------------------------------------------------*/

void HEVCSpsSetVuiHrdBitRate(struct sps *sps, u32 bitRate)
{
  ASSERT(sps);

  sps->vui.bitRate = bitRate;
}

void HEVCSpsSetVuiHrdCpbSize(struct sps *sps, u32 cpbSize)
{
  ASSERT(sps);

  sps->vui.cpbSize = cpbSize;
}

u32 HEVCSpsGetVuiHrdBitRate(struct sps *sps)
{
  ASSERT(sps);

  return sps->vui.bitRate;
}

u32 HEVCSpsGetVuiHrdCpbSize(struct sps *sps)
{
  ASSERT(sps);

  return sps->vui.cpbSize;
}
/*------------------------------------------------------------------------------
    Function name   : HEVCSpsSetVuiPictStructPresentFlag
    Description     : Signal presence of pic_struct in picture timing SEI
    Return type     : void
    Argument        : sps_s * sps
    Argument        : u32 flag
------------------------------------------------------------------------------*/
void HEVCSpsSetVuiPictStructPresentFlag(struct sps *sps, u32 flag)
{
  sps->vui.frame_field_info_present_flag = flag;
}

/*------------------------------------------------------------------------------
    Function name   : HEVCSpsSetVuiPictStructPresentFlag
    Description     : Signal presence of pic_struct in picture timing SEI
    Return type     : void
    Argument        : sps_s * sps
    Argument        : u32 flag
------------------------------------------------------------------------------*/
void HEVCSpsSetVui_field_seq_flag(struct sps *sps, u32 flag)
{
  sps->vui.field_seq_flag = flag;
}

/*------------------------------------------------------------------------------

    Function: GetAspectRatioIdc

        Functional description:

        Inputs:
          u32 sarWidth      sample aspect ratio width
          u32 sarHeight     sample aspect ratio height

        Outputs:

        Returns:
          u32   acpectRatioIdc

------------------------------------------------------------------------------*/
static i32 GetAspectRatioIdc(i32 sarWidth, i32 sarHeight)
{

  i32 aspectRatioIdc;

  if (sarWidth == 0 || sarHeight == 0) /* unspecified */
    aspectRatioIdc = 0;
  else if (sarWidth == sarHeight) /* square, 1:1 */
    aspectRatioIdc = 1;
  else if (sarHeight == 11)
  {
    if (sarWidth == 12) /* 12:11 */
      aspectRatioIdc = 2;
    else if (sarWidth == 10) /* 10:11 */
      aspectRatioIdc = 3;
    else if (sarWidth == 16) /* 16:11 */
      aspectRatioIdc = 4;
    else if (sarWidth == 24) /* 24:11 */
      aspectRatioIdc = 6;
    else if (sarWidth == 20) /* 20:11 */
      aspectRatioIdc = 7;
    else if (sarWidth == 32) /* 32:11 */
      aspectRatioIdc = 8;
    else if (sarWidth == 18) /* 18:11 */
      aspectRatioIdc = 10;
    else if (sarWidth == 15) /* 15:11 */
      aspectRatioIdc = 11;
    else    /* Extended_SAR */
      aspectRatioIdc = EXTENDED_SAR;
  }
  else if (sarHeight == 33)
  {
    if (sarWidth == 40) /* 40:33 */
      aspectRatioIdc = 5;
    else if (sarWidth == 80) /* 80:33 */
      aspectRatioIdc = 9;
    else if (sarWidth == 64) /* 64:33 */
      aspectRatioIdc = 12;
    else    /* Extended_SAR */
      aspectRatioIdc = EXTENDED_SAR;
  }
  else if (sarWidth == 160 && sarHeight == 99) /* 160:99 */
    aspectRatioIdc = 13;
  else if (sarWidth == 4 && sarHeight == 3) /* 4:3 */
    aspectRatioIdc = 14;
  else if (sarWidth == 3 && sarHeight == 2) /* 3:2 */
    aspectRatioIdc = 15;
  else if (sarWidth == 2 && sarHeight == 1) /* 2:1 */
    aspectRatioIdc = 16;
  else    /* Extended_SAR */
    aspectRatioIdc = EXTENDED_SAR;

  return (aspectRatioIdc);

}


/*------------------------------------------------------------------------------

    Function: WriteVui

        Functional description:
          Write VUI params into the stream

        Inputs:
          vui_t *vui            pointer to VUI params structure
          u32 numRefFrames      number of reference frames, used as
                                max_dec_frame_buffering

        Outputs:
          stream_s *            pointer to stream data

------------------------------------------------------------------------------*/
static void WriteVui(struct buffer *b, vui_t *vui)
{

  /* Variables */

  i32 sarIdc;

  /* Code */

  ASSERT(b);
  ASSERT(vui);

  sarIdc = GetAspectRatioIdc(vui->sarWidth, vui->sarHeight);

  if (sarIdc == 0) /* unspecified sample aspect ratio -> not present */
  {
    put_bit(b, 0, 1);
    COMMENT(b, "aspect_ratio_info_present_flag");
  }
  else
  {
    put_bit(b, 1, 1);
    COMMENT(b, "aspect_ratio_info_present_flag");
    put_bit(b, sarIdc, 8);
    COMMENT(b, "aspect_ratio_idc");
    if (sarIdc == EXTENDED_SAR)
    {
      put_bit_32(b, vui->sarWidth, 16);
      COMMENT(b, "sar_width");
      put_bit_32(b, vui->sarHeight, 16);
      COMMENT(b, "sar_height");
    }
  }

  put_bit(b, 0, 1);
  COMMENT(b, "overscan_info_present_flag");

  if (vui->videoFullRange != 0)
  {
    put_bit(b, 1, 1);
    COMMENT(b, "video_signal_type_present_flag");
    put_bit(b, 5, 3);
    COMMENT(b, "unspecified video_format");
    put_bit(b, 1, 1);
    COMMENT(b, "video_full_range_flag");
    put_bit(b, 0, 1);
    COMMENT(b, "colour_description_present_flag");
  }
  else
  {
    put_bit(b, 0, 1);
    COMMENT(b, "video_signal_type_present_flag");
  }

  put_bit(b, 0, 1);
  COMMENT(b, "chroma_loc_info_present_flag");

  put_bit(b, 0, 1);
  COMMENT(b, "neutral_chroma_indication_flag");


  put_bit(b, vui->field_seq_flag, 1);
  COMMENT(b, "field_seq_flag");


  put_bit(b, vui->frame_field_info_present_flag, 1);
  //input support  progressive frame and interlacedfield picture: pic_struct=0(display in progressive),source_scan_type=1(source is progressive), duplicate_flag=0(not duplicate frame)
  COMMENT(b, "frame_field_info_present_flag");

  put_bit(b, 0, 1);
  COMMENT(b, "default_display_window_flag");

  if (vui->timeScale != 0)
  {
    put_bit(b, 1, 1);
    COMMENT(b, "vui_timing_info_present_flag");
    put_bit_32(b, (i32)vui->numUnitsInTick, 32);
    COMMENT(b, "vui_num_units_in_tick");
    put_bit_32(b, (i32)vui->timeScale, 32);
    COMMENT(b, "vui_time_scale");
    put_bit(b, 0, 1);
    COMMENT(b, "vui_poc_proportional_to_timing_flag");

    put_bit(b, (i32) vui->nalHrdParametersPresentFlag, 1);
    COMMENT(b, "vui_hrd_parameters_present_flag");


    if (vui->nalHrdParametersPresentFlag == ENCHW_YES)
    {
      put_bit(b, vui->nalHrdParametersPresentFlag, 1);
      COMMENT(b, "nal_hrd_parameters_present_flag");
      put_bit(b, 0, 1);
      COMMENT(b, "vcl_hrd_parameters_present_flag");
      put_bit(b, 0, 1);
      COMMENT(b, "sub_pic_hrd_params_present_flag");



      {
        u32 bit_rate_scale = 1;
        u32 cpb_size_scale = 1;
        u32 tmp, i = 0;

        tmp = vui->cpbSize;
        while (4095 < (tmp >> (4 + i++)));
        cpb_size_scale = i;

        i = 0;
        tmp = vui->bitRate;
        while (4095 < (tmp >> (6 + i++)));
        bit_rate_scale = i;

        put_bit(b, bit_rate_scale, 4);
        COMMENT(b, "bit_rate_scale");

        put_bit(b, cpb_size_scale, 4);
        COMMENT(b, "cpb_size_scale");

        put_bit(b, vui->initialCpbRemovalDelayLength - 1, 5);
        COMMENT(b, "initial_cpb_removal_delay_length_minus1");
        put_bit(b, vui->cpbRemovalDelayLength - 1, 5);
        COMMENT(b, "au_cpb_removal_delay_length_minus1");
        put_bit(b, vui->dpbOutputDelayLength - 1, 5);
        COMMENT(b, "dpb_output_delay_length_minus1");

        put_bit(b, 1, 1);
        COMMENT(b, "fixed_pic_rate_general_flag[ i ]");
#if 0
        put_bit(b, 1, 1);
        COMMENT("fixed_pic_rate_within_cvs_flag[ i ]");

        put_bit(b, 0, 1);
        COMMENT("low_delay_hrd_flag[ i ]");
#endif
        //why is 0 in HM?
        put_bit_ue(b, 0);
        COMMENT(b, "elemental_duration_in_tc_minus1[ i ]");

        put_bit_ue(b, 0);
        COMMENT(b, "cpb_cnt_minus1[ i ]");

        tmp = vui->bitRate >> (6 + bit_rate_scale);
        put_bit_ue(b, tmp - 1);
        vui->bitRate = tmp << (6 + bit_rate_scale);
        COMMENT(b, "bit_rate_value_minus1");

        tmp = vui->cpbSize >> (4 + cpb_size_scale);
        put_bit_ue(b, tmp - 1);
        vui->cpbSize = tmp << (4 + cpb_size_scale);
        COMMENT(b, "cpb_size_value_minus1");
        put_bit(b, 0, 1);
        COMMENT(b, "cbr_flag");
      }

    }
  }
  else
  {
    put_bit(b, 0, 1);
    COMMENT(b, "vui_timing_info_present_flag");
  }




  put_bit(b, (i32) vui->bitStreamRestrictionFlag, 1);
  COMMENT(b, "bitstream_restriction_flag");

  if (vui->bitStreamRestrictionFlag == ENCHW_YES)
  {
    put_bit(b, 1, 1);
    COMMENT(b, "tiles_fixed_structure_flag");

    put_bit(b, 1, 1);
    COMMENT(b, "motion_vectors_over_pic_boundaries");

    put_bit(b, 1, 1);
    COMMENT(b, "restricted_ref_pic_lists_flag");


    put_bit_ue(b, 0);
    COMMENT(b, "min_spatial_segmentation_idc");

    put_bit_ue(b, 0);
    COMMENT(b, "max_bytes_per_pic_denom");

    put_bit_ue(b, 0);
    COMMENT(b, "max_bits_per_min_cu_denom");

    put_bit_ue(b, LOG2_MAX_MV_LENGTH_HOR);
    COMMENT(b, "log2_max_mv_length_horizontal");

    put_bit_ue(b, LOG2_MAX_MV_LENGTH_VER);
    COMMENT(b, "log2_max_mv_length_vertical");

  }

}

void UpdateVuiPresence(struct sps *sps)
{

  if (sps->vui.nalHrdParametersPresentFlag == 0 &&
      sps->vui.timeScale == 0 &&
      sps->vui.frame_field_info_present_flag == 0 &&
      sps->vui.sarWidth == 0 && sps->vui.videoFullRange == 0 &&
      sps->vui.bitStreamRestrictionFlag == 0)
  {
    sps->vui_parameters_present_flag = ENCHW_NO;
  }
}

