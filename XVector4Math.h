//
//  XVector4Math.h
//  
//
//  Created by easy proger on 26.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _XVector4Math_h
#define _XVector4Math_h


#define X_INLINE	static __inline__


#include "XTypes.h"
#include "XMathTypes.h"

#include <math.h>


AGRESIVE_INLINE void  XVector4Make(XVector4 *in,float x,float y,float z,float w);
AGRESIVE_INLINE float XVector4Dot(const XVector4 *vectorLeft,const XVector4 *vectorRight);
AGRESIVE_INLINE float XVector4Dot(const XVector4 *vectorLeft,const XVector3 *vectorRight,float wRight);

AGRESIVE_INLINE void  XQuaternion4Slerp(XVector4 * res, XVector4 * q, XVector4 * p, float t);
AGRESIVE_INLINE float XQuaternionLength(XVector4 *quaternion);
AGRESIVE_INLINE void  XQuaternionNormalize(XVector4*res, XVector4* quaternion);
AGRESIVE_INLINE void  XQuaternionNormalize(XVector4*res, XVector4* quaternion);
AGRESIVE_INLINE float XQuaternionLength(XVector4 *quaternion);
AGRESIVE_INLINE void  XQuaternionMakeWithMatrix(XVector4*result, XMatrix4 *mat);
AGRESIVE_INLINE void  XQuaternionMakeWithMatrix2(XVector4*result, XMatrix4 *matIn);

AGRESIVE_INLINE void XQuaternionMakeWithMatrix(XVector4*result, XMatrix4 *mat)
{
    
    double trace = 1 + mat->m[0] + mat->m[5] + mat->m[10];
    double S = 0;
    double X = 0;
    double Y = 0;
    double Z = 0;
    double W = 0;
    
    if (trace > 0.0000001)
    {
        S = sqrt(trace) * 2;
        X = (mat->m[9] - mat->m[6]) / S;
        Y = (mat->m[2] - mat->m[8]) / S;
        Z = (mat->m[4] - mat->m[1]) / S;
        W = 0.25 * S;
    }
    else
    {
        if (mat->m[0] > mat->m[5] && mat->m[0] > mat->m[10])
        {
            // Column 0:
            S = sqrt(1.0 + mat->m[0] - mat->m[5] - mat->m[10]) * 2;
            X = 0.25 * S;
            Y = (mat->m[4] + mat->m[1]) / S;
            Z = (mat->m[2] + mat->m[8]) / S;
            W = (mat->m[9] - mat->m[6]) / S;
        }
        else if (mat->m[5] > mat->m[10])
        {
            // Column 1:
            S = sqrt(1.0 + mat->m[5] - mat->m[0] - mat->m[10]) * 2;
            X = (mat->m[4] + mat->m[1]) / S;
            Y = 0.25 * S;
            Z = (mat->m[9] + mat->m[6]) / S;
            W = (mat->m[2] - mat->m[8]) / S;
        }
        else
        {
            // Column 2:
            S = sqrt(1.0 + mat->m[10] - mat->m[0] - mat->m[5]) * 2;
            X = (mat->m[2] + mat->m[8]) / S;
            Y = (mat->m[9] + mat->m[6]) / S;
            Z = 0.25 * S;
            W = (mat->m[4] - mat->m[1]) / S;
        }
    }
    
    
    result->x = (float)-X;
    result->y = (float)-Y;
    result->z = (float)-Z;
    result->w = (float)W;
    
    
}



AGRESIVE_INLINE void XQuaternionMakeWithMatrix2(XVector4*result, XMatrix4 *matIn)
{
    
    double trace = 1 + matIn->m[0] + matIn->m[5] + matIn->m[10];
    double S = 0;
    double X = 0;
    double Y = 0;
    double Z = 0;
    double W = 0;
    
    if (trace > 0.0000001)
    {
        S = sqrt(trace) * 2;
        X = (matIn->m[6] - matIn->m[9]) / S;
        Y = (matIn->m[8] - matIn->m[2]) / S;
        Z = (matIn->m[1] - matIn->m[4]) / S;
        W = 0.25 * S;
    }
    else
    {
        if (matIn->m[0] > matIn->m[5] && matIn->m[0] > matIn->m[10])
        {
            // Column 0:
            S = sqrt(1.0 + matIn->m[0] - matIn->m[5] - matIn->m[10]) * 2;
            X = 0.25 * S;
            Y = (matIn->m[1] + matIn->m[4]) / S;
            Z = (matIn->m[8] + matIn->m[2]) / S;
            W = (matIn->m[6] - matIn->m[9]) / S;
        }
        else if (matIn->m[5] > matIn->m[10])
        {
            // Column 1:
            S = sqrt(1.0 + matIn->m[5] - matIn->m[0] - matIn->m[10]) * 2;
            X = (matIn->m[1] + matIn->m[4]) / S;
            Y = 0.25 * S;
            Z = (matIn->m[6] + matIn->m[9]) / S;
            W = (matIn->m[8] - matIn->m[2]) / S;
        }
        else
        {
            // Column 2:
            S = sqrt(1.0 + matIn->m[10] - matIn->m[0] - matIn->m[5]) * 2;
            X = (matIn->m[8] + matIn->m[2]) / S;
            Y = (matIn->m[6] + matIn->m[9]) / S;
            Z = 0.25 * S;
            W = (matIn->m[1] - matIn->m[4]) / S;
        }
    }
    
    
    result->x = (float)-X;
    result->y = (float)-Y;
    result->z = (float)-Z;
    result->w = (float)W;
    
    
}








AGRESIVE_INLINE float XQuaternionLength(XVector4 *quaternion)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)quaternion,
                              *(float32x4_t *)quaternion);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return sqrt(vget_lane_f32(v2, 0));
#elif defined(X_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(quaternion.q[0]);
	const __m128 product = q * q;
	const __m128 halfsum = _mm_hadd_ps(product, product);
	return _mm_cvtss_f32(_mm_sqrt_ss(_mm_hadd_ps(halfsum, halfsum)));
#else
    return sqrt(quaternion->v[0] * quaternion->v[0] +
                quaternion->v[1] * quaternion->v[1] +
                quaternion->v[2] * quaternion->v[2] +
                quaternion->v[3] * quaternion->v[3]);
#endif
}

AGRESIVE_INLINE void XQuaternionNormalize(XVector4*res, XVector4* quaternion)
{
    float scale = 1.0f / XQuaternionLength(quaternion);
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)quaternion,
                              vdupq_n_f32((float32_t)scale));
    res = (XVector4 *)&v;
#elif defined(X_SSE3_INTRINSICS)
	const __m128 q = _mm_load_ps(quaternion.q[0]);
    __m128 v = q * _mm_set1_ps(scale);
    res = (XVector4 *)&v;
#else
    res->x = quaternion->v[0] * scale;
    res->y = quaternion->v[1] * scale;
    res->z = quaternion->v[2] * scale;
    res->w = quaternion->v[3] * scale;
#endif
}

#define DELTA 0.0005f
AGRESIVE_INLINE void XQuaternion4Slerp(XVector4 * res, XVector4 * q, XVector4 * p, float t)
{
	float p1[4];
	double omega, cosom, sinom, scale0, scale1;
	
	// косинус угла
	cosom = q->x*p->x + q->y*p->y + q->z*p->z + q->w*p->w;
	
	if ( cosom <0.0 )
	{
		cosom = -cosom;
		p1[0] = - p->x;  p1[1] = - p->y;
		p1[2] = - p->z;  p1[3] = - p->w;
	}
	else
	{
		p1[0] = p->x;    p1[1] = p->y;
		p1[2] = p->z;    p1[3] = p->w;
	}
	
	if ( (1.0 - cosom) > DELTA )
	{
		// стандартный случай (slerp)
		omega = acos(cosom);
		sinom = sin(omega);
		scale0 = sin((1.0 - t) * omega) / sinom;
		scale1 = sin(t * omega) / sinom;
	}
	else
	{
		// если маленький угол - линейная интерполяция
		scale0 = 1.0 - t;
		scale1 = t;
	}
	
	res->x =(float) (scale0 * q->x + scale1 * p1[0]);
	res->y =(float) (scale0 * q->y + scale1 * p1[1]);
	res->z =(float) (scale0 * q->z + scale1 * p1[2]);
	res->w =(float) (scale0 * q->w + scale1 * p1[3]);
}



AGRESIVE_INLINE void XVector4Make(XVector4 *in,float x,float y,float z,float w) {
	in->x = x;
	in->y = y;
	in->z = z;
	in->w = w;
}




AGRESIVE_INLINE float XVector4Dot(const XVector4 *vectorLeft,const XVector4 *vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4_t v = vmulq_f32(*(float32x4_t *)vectorLeft,
                              *(float32x4_t *)vectorRight);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return vget_lane_f32(v2, 0);
#else
    return vectorLeft->v[0] * vectorRight->v[0] +
           vectorLeft->v[1] * vectorRight->v[1] +
           vectorLeft->v[2] * vectorRight->v[2] +
           vectorLeft->v[3] * vectorRight->v[3];
#endif
}


AGRESIVE_INLINE float XVector4Dot(const XVector4 *vectorLeft,const XVector3 *vectorRight,float wRight)
{
    
#if defined(__ARM_NEON__)
    XVector4 vectorRight4 = {vectorRight->x,vectorRight->y,vectorRight->z,wRight};
    float32x4_t v = vmulq_f32(*(float32x4_t *)vectorLeft,
                              *(float32x4_t *)&vectorRight4);
    float32x2_t v2 = vpadd_f32(vget_low_f32(v), vget_high_f32(v));
    v2 = vpadd_f32(v2, v2);
    return vget_lane_f32(v2, 0);
#else
    return vectorLeft->v[0] * vectorRight->v[0] +
           vectorLeft->v[1] * vectorRight->v[1] +
           vectorLeft->v[2] * vectorRight->v[2] +
           vectorLeft->v[3] * wRight;
#endif
}



#endif
