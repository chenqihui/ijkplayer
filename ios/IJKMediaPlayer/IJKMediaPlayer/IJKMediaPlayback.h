/*
 * IJKMediaPlayback.h
 *
 * Copyright (c) 2013 Bilibili
 * Copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
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
#import <UIKit/UIKit.h>
/**
 AnakinChen:
 
 显示填充模式
 */
typedef NS_ENUM(NSInteger, IJKMPMovieScalingMode) {
    IJKMPMovieScalingModeNone,       // No scaling
    IJKMPMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    IJKMPMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    IJKMPMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
};
/**
 AnakinChen:
 
 视频播放状态
 */
typedef NS_ENUM(NSInteger, IJKMPMoviePlaybackState) {
    IJKMPMoviePlaybackStateStopped,
    IJKMPMoviePlaybackStatePlaying,
    IJKMPMoviePlaybackStatePaused,
    IJKMPMoviePlaybackStateInterrupted,
    IJKMPMoviePlaybackStateSeekingForward,
    IJKMPMoviePlaybackStateSeekingBackward
};
/**
 AnakinChen:
 
 视频加载状态
 */
typedef NS_OPTIONS(NSUInteger, IJKMPMovieLoadState) {
    IJKMPMovieLoadStateUnknown        = 0,
    IJKMPMovieLoadStatePlayable       = 1 << 0,
    IJKMPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    IJKMPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
};
/**
 AnakinChen:
 
 播放结束，即停止时的情况
 */
typedef NS_ENUM(NSInteger, IJKMPMovieFinishReason) {
    IJKMPMovieFinishReasonPlaybackEnded,
    IJKMPMovieFinishReasonPlaybackError,
    IJKMPMovieFinishReasonUserExited
};

// -----------------------------------------------------------------------------
// Thumbnails

typedef NS_ENUM(NSInteger, IJKMPMovieTimeOption) {
    IJKMPMovieTimeOptionNearestKeyFrame,
    IJKMPMovieTimeOptionExact
};
/**
 AnakinChen:
 
 播放器使用的协议，
 目前有AVPlayer、MPMovieController和ffmpeg。
 如果后续扩展其他播放器，可以通过封装实现IJKMediaPlayback。
 */
@protocol IJKMediaPlayback;

#pragma mark IJKMediaPlayback

@protocol IJKMediaPlayback <NSObject>
/**
 AnakinChen:
 
 准备成功后就播放
 */
- (void)prepareToPlay;
/**
 AnakinChen:
 
 播放
 */
- (void)play;
/**
 AnakinChen:
 
 暂停
 */
- (void)pause;
/**
 AnakinChen:
 
 AVPlayer是暂停
 MPMovie无
 FFmpeg是关闭
 */
- (void)stop;
/**
 AnakinChen:
 
 当前播放器的播放状态
 */
- (BOOL)isPlaying;
/**
 AnakinChen:
 
 AVPlayer是关闭
 MPMovie无
 FFmpeg是彻底关闭
 */
- (void)shutdown;
/**
 AnakinChen:
 
 是否压后台暂停播放pause
 [TODO]
 了解FFmpeg在压后台时不暂停，绘制画面和播放声音的控制。
 */
- (void)setPauseInBackground:(BOOL)pause;

@property(nonatomic, readonly)  UIView *view;
@property(nonatomic)            NSTimeInterval currentPlaybackTime;
@property(nonatomic, readonly)  NSTimeInterval duration;
@property(nonatomic, readonly)  NSTimeInterval playableDuration;
@property(nonatomic, readonly)  NSInteger bufferingProgress;

/**
 AnakinChen:
 
 准备完毕，可以播放状态
 */
@property(nonatomic, readonly)  BOOL isPreparedToPlay;
@property(nonatomic, readonly)  IJKMPMoviePlaybackState playbackState;
@property(nonatomic, readonly)  IJKMPMovieLoadState loadState;

/**
 AnakinChen:
 
 累积传输的字节数，MP有
 */
@property(nonatomic, readonly) int64_t numberOfBytesTransferred;

@property(nonatomic, readonly) CGSize naturalSize;
@property(nonatomic) IJKMPMovieScalingMode scalingMode;
@property(nonatomic) BOOL shouldAutoplay;

/**
 AnakinChen:
 
 链接AirPlay的使用情况
 [TODO]
 */
@property (nonatomic) BOOL allowsMediaAirPlay;
@property (nonatomic) BOOL isDanmakuMediaAirPlay;
@property (nonatomic, readonly) BOOL airPlayMediaActive;

@property (nonatomic) float playbackRate;
@property (nonatomic) float playbackVolume;

- (UIImage *)thumbnailImageAtCurrentTime;

/**
 AnakinChen:
 
 各种通知的名称
 
 总结
 是控件，即UI类的模块，使用delegate
 是逻辑功能，就可以使用Notifications或者delegate都可以。不过一般功能独立的第三方SDK确实采用Nofitication会在内部和外部解耦比较强。但是Nofitication相对阅读性就没delegate那么高，不过确实第三方的对外使用Notification，对内使用delegate。
 */
#pragma mark Notifications

#ifdef __cplusplus
#define IJK_EXTERN extern "C" __attribute__((visibility ("default")))
#else
#define IJK_EXTERN extern __attribute__((visibility ("default")))
#endif

// -----------------------------------------------------------------------------
//  MPMediaPlayback.h

// Posted when the prepared state changes of an object conforming to the MPMediaPlayback protocol changes.
// This supersedes MPMoviePlayerContentPreloadDidFinishNotification.
IJK_EXTERN NSString *const IJKMPMediaPlaybackIsPreparedToPlayDidChangeNotification;

// -----------------------------------------------------------------------------
//  MPMoviePlayerController.h
//  Movie Player Notifications

// Posted when the scaling mode changes.
IJK_EXTERN NSString* const IJKMPMoviePlayerScalingModeDidChangeNotification;

// Posted when movie playback ends or a user exits playback.
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackDidFinishNotification;
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackDidFinishReasonUserInfoKey; // NSNumber (IJKMPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
IJK_EXTERN NSString* const IJKMPMoviePlayerPlaybackStateDidChangeNotification;

// Posted when the network load state changes.
IJK_EXTERN NSString* const IJKMPMoviePlayerLoadStateDidChangeNotification;

// Posted when the movie player begins or ends playing video via AirPlay.
IJK_EXTERN NSString* const IJKMPMoviePlayerIsAirPlayVideoActiveDidChangeNotification;

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
IJK_EXTERN NSString* const IJKMPMovieNaturalSizeAvailableNotification;

// -----------------------------------------------------------------------------
//  Extend Notifications

IJK_EXTERN NSString *const IJKMPMoviePlayerVideoDecoderOpenNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerFirstVideoFrameRenderedNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerFirstAudioFrameRenderedNotification;

IJK_EXTERN NSString *const IJKMPMoviePlayerDidSeekCompleteNotification;
IJK_EXTERN NSString *const IJKMPMoviePlayerDidSeekCompleteTargetKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerDidSeekCompleteErrorKey;
IJK_EXTERN NSString *const IJKMPMoviePlayerDidAccurateSeekCompleteCurPos;
IJK_EXTERN NSString *const IJKMPMoviePlayerAccurateSeekCompleteNotification;

@end

#pragma mark IJKMediaUrlOpenDelegate

// Must equal to the defination in ijkavformat/ijkavformat.h
typedef NS_ENUM(NSInteger, IJKMediaEvent) {

    // Notify Events
    IJKMediaEvent_WillHttpOpen         = 1,       // attr: url
    IJKMediaEvent_DidHttpOpen          = 2,       // attr: url, error, http_code
    IJKMediaEvent_WillHttpSeek         = 3,       // attr: url, offset
    IJKMediaEvent_DidHttpSeek          = 4,       // attr: url, offset, error, http_code
    // Control Message
    IJKMediaCtrl_WillTcpOpen           = 0x20001, // IJKMediaUrlOpenData: no args
    IJKMediaCtrl_DidTcpOpen            = 0x20002, // IJKMediaUrlOpenData: error, family, ip, port, fd
    IJKMediaCtrl_WillHttpOpen          = 0x20003, // IJKMediaUrlOpenData: url, segmentIndex, retryCounter
    IJKMediaCtrl_WillLiveOpen          = 0x20005, // IJKMediaUrlOpenData: url, retryCounter
    IJKMediaCtrl_WillConcatSegmentOpen = 0x20007, // IJKMediaUrlOpenData: url, segmentIndex, retryCounter
};

#define IJKMediaEventAttrKey_url            @"url"
#define IJKMediaEventAttrKey_host           @"host"
#define IJKMediaEventAttrKey_error          @"error"
#define IJKMediaEventAttrKey_time_of_event  @"time_of_event"
#define IJKMediaEventAttrKey_http_code      @"http_code"
#define IJKMediaEventAttrKey_offset         @"offset"

// event of IJKMediaUrlOpenEvent_xxx
@interface IJKMediaUrlOpenData: NSObject

- (id)initWithUrl:(NSString *)url
            event:(IJKMediaEvent)event
     segmentIndex:(int)segmentIndex
     retryCounter:(int)retryCounter;

@property(nonatomic, readonly) IJKMediaEvent event;
@property(nonatomic, readonly) int segmentIndex;
@property(nonatomic, readonly) int retryCounter;

@property(nonatomic, retain) NSString *url;
@property(nonatomic, assign) int fd;
@property(nonatomic, strong) NSString *msg;
@property(nonatomic) int error; // set a negative value to indicate an error has occured.
@property(nonatomic, getter=isHandled)    BOOL handled;     // auto set to YES if url changed
@property(nonatomic, getter=isUrlChanged) BOOL urlChanged;  // auto set to YES by url changed

@end
/**
 AnakinChen:
 
 检验地址是否可打开，这个用法比较特别，或者说是针对Objective-C在语法上方法的返回只能是一个对象。我们有使用集合的，struct结构体（相对较少），对象的返回出来。而这里特别的是，它将入参和出参都放在同个IJKMediaUrlOpenData对象里面。这样设计的接口比较简洁，可读性较差。需要了解IJKMediaUrlOpenData的属性。
 */
@protocol IJKMediaUrlOpenDelegate <NSObject>

- (void)willOpenUrl:(IJKMediaUrlOpenData*) urlOpenData;

@end
/**
 AnakinChen:
 
 保存ffmpeg的AVAppHttpEvent状态过程的数据
 [TODO]后续测测
 */
@protocol IJKMediaNativeInvokeDelegate <NSObject>

- (int)invoke:(IJKMediaEvent)event attributes:(NSDictionary *)attributes;

@end
