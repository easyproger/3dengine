//
//  FlagsForShaderCompile.h
//  XTech
//
//  Created by easy proger on 20.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef XTech_FlagsForShaderCompile_h
#define XTech_FlagsForShaderCompile_h


#define NORMAL_MESH                  1   // 2^0, bit 0
#define SKINING_MESH                 2   // 2^1, bit 1


#define NORMAL_MATERIAL               1   // 2^2, bit 2
#define COLOR_MATERIAL                2   // 2^2, bit 2
#define DYNAMIC_PER_PIXEL_BASE_LIGHT  4   // 2^3, bit 3
#define RESAVE_SHADOW_SM              8  // 2^4, bit 4
#define SPECULAR_MATERIAL             16 // and so on...
#define NORMAL_MAP_MATERIAL           32 // and so on...
#define DYNAMIC_PER_VERTEX_BASE_LIGHT 64 // and so on...
#define CUSTOM_CODE                  128 // and so on...
#endif
