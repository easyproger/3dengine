//
//  XVector3.h
//  
//
//  Created by easy proger on 26.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _XVector3_h
#define _XVector3_h

#include "XTypes.h"
#include <iostream>





union _XVector3
{
    struct { float x, y, z; };
    struct { float r, g, b; };
    struct { float s, t, p; };
    float v[3];
};
typedef union _XVector3 XVector3;


union _XVector4
{
    struct { float x, y, z, w; };
    struct { float r, g, b, a; };
    struct { float s, t, p, u; };
    float v[4];
};
typedef union _XVector4 XVector4;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
union _XMatrix4
{
    struct
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    float m[16];
} ;
typedef union _XMatrix4 XMatrix4;
#else
union _XMatrix4
{
    struct
    {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
    float m[16];
} __attribute__((aligned(16)));
typedef union _XMatrix4 XMatrix4;
#endif




union _XMatrix3
{
    struct
    {
        float m00, m01, m02;
        float m10, m11, m12;
        float m20, m21, m22;
    };
    float m[9];
};
typedef union _XMatrix3 XMatrix3;



#endif
