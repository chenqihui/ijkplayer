/*
 * ffpipeline_ios.c
 *
 * Copyright (c) 2014 Zhou Quan <zhouqicy@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "ffpipeline_ios.h"
#include "ffpipenode_ios_videotoolbox_vdec.h"
#include "ffpipenode_ffplay_vdec.h"
#include "ff_ffplay.h"
#import "ijksdl/ios/ijksdl_aout_ios_audiounit.h"

struct IJKFF_Pipeline_Opaque {
    FFPlayer    *ffp;
    bool         is_videotoolbox_open;
};

static void func_destroy(IJKFF_Pipeline *pipeline)
{
}

static IJKFF_Pipenode *func_open_video_decoder(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    IJKFF_Pipenode* node = NULL;
    IJKFF_Pipeline_Opaque *opaque = pipeline->opaque;
    /**
     AnakinChen:
     
     如果配置了ffp->videotoolbox，会优先去尝试打开硬件解码器，
     
     不管视频解码还是音频解码，其基本流程都是从解码前的数据缓冲区中取出一帧数据进行解码，完成后放入相应的解码后的数据缓冲区，如下图所示：
     
     接收数据 —————>  解码前的数据 -> 解码器 -> 解码后的数据 —————> 渲染(播放)
     */
    if (ffp->videotoolbox) {
        node = ffpipenode_create_video_decoder_from_ios_videotoolbox(ffp);
        if (!node)
            ALOGE("vtb fail!!! switch to ffmpeg decode!!!! \n");
    }
    /**
     AnakinChen:
     
     如果硬件解码器打开失败，则会自动切换至软解
     
     ffp->videotoolbox需要在起播前通过如下方法配置：
     ijkmp_set_option_int(_mediaPlayer, IJKMP_OPT_CATEGORY_PLAYER,     "videotoolbox", 1);
     */
    if (node == NULL) {
        node = ffpipenode_create_video_decoder_from_ffplay(ffp);
        ffp->stat.vdec_type = FFP_PROPV_DECODER_AVCODEC;
        opaque->is_videotoolbox_open = false;
    } else {
        ffp->stat.vdec_type = FFP_PROPV_DECODER_VIDEOTOOLBOX;
        opaque->is_videotoolbox_open = true;
    }
    ffp_notify_msg2(ffp, FFP_MSG_VIDEO_DECODER_OPEN, opaque->is_videotoolbox_open);
    return node;
}

/**
 AnakinChen:4.1.3
 
 */
static SDL_Aout *func_open_audio_output(IJKFF_Pipeline *pipeline, FFPlayer *ffp)
{
    return SDL_AoutIos_CreateForAudioUnit();
}

static SDL_Class g_pipeline_class = {
    .name = "ffpipeline_ios",
};

/**
 AnakinChen:1.3.3
 
 创建平台相关的IJKFF_Pipeline对象，包括视频解码以及音频输出部分
 */
IJKFF_Pipeline *ffpipeline_create_from_ios(FFPlayer *ffp)
{
    IJKFF_Pipeline *pipeline = ffpipeline_alloc(&g_pipeline_class, sizeof(IJKFF_Pipeline_Opaque));
    if (!pipeline)
        return pipeline;

    IJKFF_Pipeline_Opaque *opaque     = pipeline->opaque;
    opaque->ffp                       = ffp;
    pipeline->func_destroy            = func_destroy;
    pipeline->func_open_video_decoder = func_open_video_decoder;
    /**
     AnakinChen:4.1.2
     
     */
    pipeline->func_open_audio_output  = func_open_audio_output;

    return pipeline;
}
