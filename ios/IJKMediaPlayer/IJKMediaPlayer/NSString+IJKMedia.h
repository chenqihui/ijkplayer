/*
 * NSString+IJKMedia.h
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
 
 IJKPlayer使用的String类别
 1、nil判断，如果是nil会返回空字符串@""
 2、ipv4的判断
 */
@interface NSString (IJKMedia)

+ (NSString *) ijk_stringBeEmptyIfNil:(NSString *)src;

- (BOOL) ijk_isIpv4;

@end
