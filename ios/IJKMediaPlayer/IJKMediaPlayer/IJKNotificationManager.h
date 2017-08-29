/*
 * IJKNotificationManager.h
 *
 * Copyright (c) 2016 Bilibili
 * Copyright (c) 2016 Zhang Rui <bbcallen@gmail.com>
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
/**
 AnakinChen:
 
 NSNotification的封装和统一维护
 通知需要add和remove对应，当如果没有remove，它不会想KVO一样崩溃。如果对象没有销毁，添加多次同个，是会造成接收多次通知。
 */
@interface IJKNotificationManager : NSObject

- (nullable instancetype)init;

- (void)addObserver:(nonnull id)observer
           selector:(nonnull SEL)aSelector
               name:(nullable NSString *)aName
             object:(nullable id)anObject;

- (void)removeAllObservers:(nonnull id)observer;

@end
