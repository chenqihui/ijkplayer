//
//  QHIJKPlayer.m
//  IJKMediaDemo
//
//  Created by Anakin chen on 2017/9/18.
//  Copyright © 2017年 chen. All rights reserved.
//

#import "QHIJKPlayer.h"

@implementation QHIJKPlayer

- (void)dealloc {
    [_player.view removeFromSuperview];
    _player = nil;
}

- (instancetype)initWithPlayerURL:(NSURL *)url {
    self = [super init];
    
    if (self) {
        IJKFFOptions *options = [IJKFFOptions optionsByDefault];
        
        self.player = [[IJKFFMoviePlayerController alloc] initWithContentURL:url withOptions:options];
        self.player.view.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
    //    self.player.view.frame = self.view.bounds;
        self.player.scalingMode = IJKMPMovieScalingModeAspectFit;
        self.player.shouldAutoplay = YES;
    }
    return self;
}

- (void)prepareToPlay {
    [self.player prepareToPlay];
}

- (void)play {
    [self.player play];
}

- (void)pause {
    [self.player pause];
}

- (void)stop {
    [self.player stop];
}

- (void)shutdown {
    [self.player shutdown];
}

- (BOOL)isPlaying {
    return [self.player isPlaying];
}

@end
