/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Support for Intel Camera Imaging ISP subsystem.
 * Copyright (c) 2015, Intel Corporation.
 */

#ifndef __IA_CSS_REF_PARAM_H
#define __IA_CSS_REF_PARAM_H

#include <type_support.h>
#include "sh_css_defs.h"
#include "dma.h"

/* Reference frame */
struct ia_css_ref_configuration {
	const struct ia_css_frame *ref_frames[MAX_NUM_VIDEO_DELAY_FRAMES];
	u32 dvs_frame_delay;
};

struct sh_css_isp_ref_isp_config {
	u32 width_a_over_b;
	struct dma_port_config port_b;
	ia_css_ptr ref_frame_addr_y[MAX_NUM_VIDEO_DELAY_FRAMES];
	ia_css_ptr ref_frame_addr_c[MAX_NUM_VIDEO_DELAY_FRAMES];
	u32 dvs_frame_delay;
};

#endif /* __IA_CSS_REF_PARAM_H */
