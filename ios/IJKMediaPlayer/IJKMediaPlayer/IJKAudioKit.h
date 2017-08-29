/*
 * IJKAudioKit.h
 *
 * Copyright (c) 2013-2014 Bilibili
 * Copyright (c) 2013-2014 Zhang Rui <bbcallen@gmail.com>
 *
 * based on https://github.com/kolyvan/kxmovie
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

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

/**
 AnakinChen:
 
 对AudioSession的设置
 设置是否设置生效及交出音频会话
 保证可同时进行声音的播放和录制这种模式AVAudioSessionCategoryPlayAndRecord
 
 参考地址：
 1、[iOS音频播放(二)：AudioSession](http://www.cocoachina.com/industry/20140717/9162.html)
 2、[AVAudioSession应用指南](http://blog.csdn.net/gang544043963/article/details/53444075)
 
 官方API文档是这样对AVAudioSession描述的：
 audiosession负责调节你的app和iOS系统里的音频行为.一旦加载了audiosession你可以获得一个audiosession的单例.你可以配置这个audiosession来控制你的app的音频行为.例如:
 当你的app播放声音的时候,你是希望其他正在播放声音的app静音还是混合两个app的声音?
 你的app如何回应突发的打断,例如这时候闹铃突然响了?
 你的app又该如何回应耳机口的拔插呢?
 AuioSession的配置会影响你的app在运行中所有的音频活动,除了利用System Sounds Services API控制的音频.
 你还可以利用AudioSession来检测你所用硬件的参数,例如声道和采样率.
 你还可以随时激活或者停止你的audioSession,当你的app播放声音或者正在录音的时候,你必须确保AudioSession处于激活状态.
 系统也有权利随时中断你的audioSession,例如,当你来电话的时候.当然,AudioSession提供了api来让你的app从这种中断中恢复.
 
 */
@interface IJKAudioKit : NSObject

+ (IJKAudioKit *)sharedInstance;

/**
 AnakinChen:
 
 保证可同时进行声音的播放和录制这种模式AVAudioSessionCategoryPlayAndRecord
 */
- (void)setupAudioSession;

/**
 AnakinChen:
 
 设置是否设置生效及交出音频会话
 */
- (BOOL)setActive:(BOOL)active;

@end
