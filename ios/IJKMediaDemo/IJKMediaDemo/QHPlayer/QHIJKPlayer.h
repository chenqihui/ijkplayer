//
//  QHIJKPlayer.h
//  IJKMediaDemo
//
//  Created by Anakin chen on 2017/9/18.
//  Copyright © 2017年 bilibili. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <IJKMediaFramework/IJKMediaFramework.h>

@interface QHIJKPlayer : NSObject

@property(atomic, retain) id<IJKMediaPlayback> player;

@end
