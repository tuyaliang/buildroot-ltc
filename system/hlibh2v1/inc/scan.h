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

#ifndef SCAN_H
#define SCAN_H

#include "base_type.h"

struct comp
{
  u8 x;
  u8 y;
};

static const struct comp const scan_0[] =
{
  {0, 0}
};

static const struct comp const diagonal_scan_1[] =
{
  {0, 0}, {0, 1}, {1, 0}, {1, 1}
};

static const struct comp const diagonal_scan_2[] =
{
  {0, 0}, {0, 1}, {1, 0}, {0, 2}, {1, 1}, {2, 0}, {0, 3}, {1, 2},
  {2, 1}, {3, 0}, {1, 3}, {2, 2}, {3, 1}, {2, 3}, {3, 2}, {3, 3}
};

static const struct comp const diagonal_scan_3[] =
{
  {0, 0}, {0, 1}, {1, 0}, {0, 2}, {1, 1}, {2, 0}, {0, 3}, {1, 2},
  {2, 1}, {3, 0}, {0, 4}, {1, 3}, {2, 2}, {3, 1}, {4, 0}, {0, 5},
  {1, 4}, {2, 3}, {3, 2}, {4, 1}, {5, 0}, {0, 6}, {1, 5}, {2, 4},
  {3, 3}, {4, 2}, {5, 1}, {6, 0}, {0, 7}, {1, 6}, {2, 5}, {3, 4},
  {4, 3}, {5, 2}, {6, 1}, {7, 0}, {1, 7}, {2, 6}, {3, 5}, {4, 4},
  {5, 3}, {6, 2}, {7, 1}, {2, 7}, {3, 6}, {4, 5}, {5, 4}, {6, 3},
  {7, 2}, {3, 7}, {4, 6}, {5, 5}, {6, 4}, {7, 3}, {4, 7}, {5, 6},
  {6, 5}, {7, 4}, {5, 7}, {6, 6}, {7, 5}, {6, 7}, {7, 6}, {7, 7}
};

static const struct comp const horizontal_scan_1[] =
{
  {0, 0}, {1, 0}, {0, 1}, {1, 1}
};

static const struct comp const horizontal_scan_2[] =
{
  {0, 0}, {1, 0}, {2, 0}, {3, 0}, {0, 1}, {1, 1}, {2, 1}, {3, 1},
  {0, 2}, {1, 2}, {2, 2}, {3, 2}, {0, 3}, {1, 3}, {2, 3}, {3, 3},
};

static const struct comp const horizontal_scan_3[] =
{
  {0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 0}, {7, 0},
  {0, 1}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 1}, {7, 1},
  {0, 2}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 2}, {7, 2},
  {0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}, {7, 3},
  {0, 4}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4},
  {0, 5}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 5}, {7, 5},
  {0, 6}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 6}, {7, 6},
  {0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}, {7, 7}
};

static const struct comp const vertical_scan_1[] =
{
  {0, 0}, {0, 1}, {1, 0}, {1, 1}
};

static const struct comp const vertical_scan_2[] =
{
  {0, 0}, {0, 1}, {0, 2}, {0, 3}, {1, 0}, {1, 1}, {1, 2}, {1, 3},
  {2, 0}, {2, 1}, {2, 2}, {2, 3}, {3, 0}, {3, 1}, {3, 2}, {3, 3}
};

static const struct comp const vertical_scan_3[] =
{
  {0, 0}, {0, 1}, {0, 2}, {0, 3}, {0, 4}, {0, 5}, {0, 6}, {0, 7},
  {1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}, {1, 6}, {1, 7},
  {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}, {2, 6}, {2, 7},
  {3, 0}, {3, 1}, {3, 2}, {3, 3}, {3, 4}, {3, 5}, {3, 6}, {3, 7},
  {4, 0}, {4, 1}, {4, 2}, {4, 3}, {4, 4}, {4, 5}, {4, 6}, {4, 7},
  {5, 0}, {5, 1}, {5, 2}, {5, 3}, {5, 4}, {5, 5}, {5, 6}, {5, 7},
  {6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5}, {6, 6}, {6, 7},
  {7, 0}, {7, 1}, {7, 2}, {7, 3}, {7, 4}, {7, 5}, {7, 6}, {7, 7}
};

static struct comp const *scan_order[][3] =
{
  {         scan_0,            scan_0,          scan_0},
  {diagonal_scan_1, horizontal_scan_1, vertical_scan_1},
  {diagonal_scan_2, horizontal_scan_2, vertical_scan_2},
  {diagonal_scan_3, horizontal_scan_3, vertical_scan_3}
};

#endif
