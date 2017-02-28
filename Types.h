//
//  Types.h
//  X TECH
//
//  Created by easy on 18.11.10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//


#define SHADER_DEPTH_ID 0
#define SHADER_LIGHT_ID 1

#define SHADOW_RENDER_TYPE_SHADOW_MAPS          0
#define SHADOW_RENDER_TYPE_CASCADED_SHADOW_MAPS 1


#define PI 3.1415926535897932384626433832795f


#define MAX_VBOS 4

#define maxSizeVBO 21000000
#define maxSizeVBOI 21000000


#define MAX_CHUNKS 20
#define MAX_BONES 40

#ifndef TYPES_H
#define TYPES_H
#include "Vectors.h"
struct Frustum
{
    float neard;
    float fard;
    float fov;
    float ratio;
    vec3 point[8];
};

#endif



typedef	unsigned char		uint8;
typedef	signed	 char		int8;
typedef	unsigned short		uint16;
typedef	signed	 short		int16;

typedef	signed	 long		int32;


typedef	unsigned long long	uint64;
typedef signed   long long	int64;



typedef	unsigned char		u_char;
typedef	unsigned short		u_short;
typedef	unsigned int		u_int;





typedef	unsigned char		byte;
typedef	uint16				word;
typedef	unsigned long				dword;

typedef	unsigned short		ushort;		
typedef	unsigned int		uint;

typedef unsigned char       byte;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
typedef void  (*CALLBACK)();
#endif




