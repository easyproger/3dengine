//
//  XVector3Math.h
//  
//
//  Created by easy proger on 26.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _XVector3Math_h
#define _XVector3Math_h
#define X_INLINE	static __inline__
#include "XTypes.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#else
#include <math.h>
#endif

AGRESIVE_INLINE XVector3 XVector3Make(float x,float y,float z);
AGRESIVE_INLINE void     XVector3MultiplyScalar(XVector3 *vector, float value);
AGRESIVE_INLINE void     XVector3MultiplyScalar(XVector3 *result, const XVector3 *left, float value);
AGRESIVE_INLINE void     XVector3AddScalar(XVector3 *result, float value);
AGRESIVE_INLINE void     XVector3AddScalar(XVector3 *result,const XVector3 *left, float value);
AGRESIVE_INLINE void     XVector3Add(XVector3 *result,const XVector3 *vectorRight);
AGRESIVE_INLINE void     XVector3Add(XVector3 *result,const XVector3 *vectorLeft,const XVector3 *vectorRight);
AGRESIVE_INLINE void     XVector3Subtract(XVector3 *result,const XVector3 *vectorLeft,const XVector3 *vectorRight);
AGRESIVE_INLINE float    XVector3Length(XVector3* vector);
AGRESIVE_INLINE void     XVector3Normalize(XVector3* vector);
AGRESIVE_INLINE void     XVector3Lepr(XVector3*result,XVector3* vector,XVector3* vectorRight,float t);







AGRESIVE_INLINE void XVector3Lepr(XVector3*result,XVector3* vector,XVector3* vectorRight,float t) {
    if (t <= 0.0f) {
        result->x = vector->x;
        result->y = vector->y;
        result->z = vector->z;
        return;
    }
    
    
    result->x = vector->x + (vectorRight->x - vector->x) * t;
	result->y = vector->y + (vectorRight->y - vector->y) * t;
	result->z = vector->z + (vectorRight->z - vector->z) * t;
}

AGRESIVE_INLINE void XVector3Normalize(XVector3* vector)
{
    float scale = 1.0f / XVector3Length(vector);
	vector->v[0]*= scale;
	vector->v[1]*= scale;
	vector->v[2]*= scale;
}

AGRESIVE_INLINE float XVector3Length(XVector3* vector)
{
    return sqrt(vector->v[0] * vector->v[0] + vector->v[1] * vector->v[1] + vector->v[2] * vector->v[2]);
}


AGRESIVE_INLINE
XVector3 XVector3Make(float x,float y,float z) {
    XVector3 v = { x, y, z };
    return v;
}

AGRESIVE_INLINE void XVector3MultiplyScalar(XVector3 *result, const XVector3 *left, float value)
{
    result->v[0] = left->v[0] * value;
    result->v[1] = left->v[1] * value;
    result->v[2] = left->v[2] * value;
}

AGRESIVE_INLINE void XVector3MultiplyScalar(XVector3 *result, float value)
{
    result->v[0] = result->v[0] * value;
    result->v[1] = result->v[1] * value;
    result->v[2] = result->v[2] * value;
}


AGRESIVE_INLINE void XVector3AddScalar(XVector3 *result, float value)
{
    result->v[0] = result->v[0] + value;
    result->v[1] = result->v[1] + value;
    result->v[2] = result->v[2] + value;
}

AGRESIVE_INLINE void XVector3AddScalar(XVector3 *result,const XVector3 *left, float value) {
    result->v[0] = left->v[0] + value;
    result->v[1] = left->v[1] + value;
    result->v[2] = left->v[2] + value;
}


AGRESIVE_INLINE void XVector3Add(XVector3 *result,const XVector3 *vectorRight)
{
    result->v[0] = result->v[0] + vectorRight->v[0];
    result->v[1] = result->v[1] + vectorRight->v[1];
    result->v[2] = result->v[2] + vectorRight->v[2];
}
AGRESIVE_INLINE void XVector3Add(XVector3 *result,const XVector3 *vectorLeft,const XVector3 *vectorRight)
{
    result->v[0] = vectorLeft->v[0] + vectorRight->v[0];
    result->v[1] = vectorLeft->v[1] + vectorRight->v[1];
    result->v[2] = vectorLeft->v[2] + vectorRight->v[2];
}

AGRESIVE_INLINE void XVector3Subtract(XVector3 *result,const XVector3 *vectorLeft,const XVector3 *vectorRight)
{
    result->v[0] = vectorLeft->v[0] - vectorRight->v[0];
    result->v[1] = vectorLeft->v[1] - vectorRight->v[1];
    result->v[2] = vectorLeft->v[2] - vectorRight->v[2];
}



#endif
