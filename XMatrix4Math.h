//
//  XMatrix4.h
//  
//
//  Created by easy proger on 26.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _XMatrix4Math_h
#define _XMatrix4Math_h
#define X_INLINE	static __inline__




#include <math.h>
#include "XTypes.h"
#include "XMathTypes.h"
#include "XVector3Math.h"
#include "XVector4Math.h"

AGRESIVE_INLINE void XMatrix4MakeWithArray(XMatrix4*result,float m1,float m2,float m3,float m4,float m5,float m6,float m7,float m8,float m9,float m10,float m11,float m12,float m13,float m14,float m15,float m16);
AGRESIVE_INLINE void XMatrix4MakeWithArray(XMatrix4*result,float values[16]);
AGRESIVE_INLINE void XMatrix4Translate(XMatrix4 *matrix, float tx, float ty, float tz);
AGRESIVE_INLINE void XMatrix4AddTranslate(XMatrix4 *matrix, float tx, float ty, float tz);

AGRESIVE_INLINE void XMatrix4Perspective(XMatrix4 *matrix,float fovyRadians, float aspect, float nearZ, float farZ);
AGRESIVE_INLINE void XMatrix4Mult(XMatrix4 *result,XMatrix4 *matrixLeft, XMatrix4 *matrixRight);
AGRESIVE_INLINE void XMatrix4Scale(XMatrix4 *matrix, float sx, float sy, float sz);
AGRESIVE_INLINE void XMatrix4TranslateWithVector3(XMatrix4 *matrix, float x, float y, float z);
AGRESIVE_INLINE void XMatrix4MakeOrtho(XMatrix4*result,float left, float right,float bottom, float top, float nearZ, float farZ);
AGRESIVE_INLINE void XMatrix4MakeOrtho(XMatrix4*result,float w, float h, float zn, float zf);

AGRESIVE_INLINE void XMatrix4MultiplyVector4(XVector4 *result,XMatrix4 *matrixLeft, XVector4 *vectorRight);
AGRESIVE_INLINE void XMatrix4MultiplyAndProjectVector3(XVector3*result, XMatrix4* matrixLeft, XVector3* vectorRight);
AGRESIVE_INLINE void XMatrix4MultiplyVector3WithTranslation(XVector3*result, XMatrix4* matrixLeft, XVector3* vectorRight);
AGRESIVE_INLINE void XMatrix4MultiplyVector3(XVector3*result, XMatrix4* matrixLeft, XVector3* vectorRight);

AGRESIVE_INLINE void XMatrix4RotationZ(XMatrix4*in,float radians);
AGRESIVE_INLINE void XMatrix4RotationY(XMatrix4*in,float radians);
AGRESIVE_INLINE void XMatrix4RotationX(XMatrix4*in,float radians);

AGRESIVE_INLINE XMatrix4 XMatrix4MakeZRotation(float radians);
AGRESIVE_INLINE XMatrix4 XMatrix4MakeYRotation(float radians);
AGRESIVE_INLINE XMatrix4 XMatrix4MakeXRotation(float radians);

AGRESIVE_INLINE XMatrix4 XMatrix4MakeRotation(float radians, float x, float y, float z);

AGRESIVE_INLINE void XMatrix4Inverse(XMatrix4 *mat);
AGRESIVE_INLINE void XMatrix4Transpose(XMatrix4*result,XMatrix4* matrix);
AGRESIVE_INLINE void XMatrix4GetMatrix3(XMatrix4* matrix,XMatrix3*out);

AGRESIVE_INLINE XMatrix4 XMatrix4GetMatrix3(XMatrix4 matrix);
AGRESIVE_INLINE void XMatrix4MakeWithQuaternionAndTranslation(XMatrix4*res, XVector4* quaternion,XVector3*position);
AGRESIVE_INLINE void XMatrix4MakeWithQuaternionAndTranslation2(XMatrix4*result,XVector4 *q,XVector3 *p);
AGRESIVE_INLINE void XMatrix4MakeWithQuaternionAndTranslation3(XMatrix4*res, XVector4* quaternion,XVector3*position);



AGRESIVE_INLINE void XMatrix4MultiplyVector4(XVector4 *result,XMatrix4 *matrixLeft, XVector4 *vectorRight)
{
#if defined(__ARM_NEON__)
    float32x4x4_t *iMatrix = (float32x4x4_t *)matrixLeft;
    float32x4_t v;
    float32x4_t v0,v1,v2,v3;
    
    v0 = vmulq_n_f32(iMatrix->val[0], (float32_t)vectorRight->v[0]);
    v1 = vmulq_n_f32(iMatrix->val[1], (float32_t)vectorRight->v[1]);
    v2 = vmulq_n_f32(iMatrix->val[2], (float32_t)vectorRight->v[2]);
    v3 = vmulq_n_f32(iMatrix->val[3], (float32_t)vectorRight->v[3]);
    
    v0 = vaddq_f32(v0, v1);
    v2 = vaddq_f32(v2, v3);
    
    v = vaddq_f32(v0, v2);
    
    result->v[0] = v[0];
    result->v[1] = v[1];
    result->v[2] = v[2];
    result->v[3] = v[3];
    
#else
    
    result->v[0] = matrixLeft->m[0] * vectorRight->v[0] + matrixLeft->m[4] * vectorRight->v[1] + matrixLeft->m[8] * vectorRight->v[2] + matrixLeft->m[12] * vectorRight->v[3];
    result->v[1] = matrixLeft->m[1] * vectorRight->v[0] + matrixLeft->m[5] * vectorRight->v[1] + matrixLeft->m[9] * vectorRight->v[2] + matrixLeft->m[13] * vectorRight->v[3];
    result->v[2] = matrixLeft->m[2] * vectorRight->v[0] + matrixLeft->m[6] * vectorRight->v[1] + matrixLeft->m[10] * vectorRight->v[2] + matrixLeft->m[14] * vectorRight->v[3];
    result->v[3] = matrixLeft->m[3] * vectorRight->v[0] + matrixLeft->m[7] * vectorRight->v[1] + matrixLeft->m[11] * vectorRight->v[2] + matrixLeft->m[15] * vectorRight->v[3];
    
#endif
}


AGRESIVE_INLINE void XMatrix4MakeWithQuaternionAndTranslation3(XMatrix4*res, XVector4* quaternion,XVector3*position)
{
    XQuaternionNormalize(quaternion,quaternion);
    
    float x = quaternion->v[0];
    float y = quaternion->v[1];
    float z = quaternion->v[2];
    float w = quaternion->v[3];
    
    float _2x = x + x;
    float _2y = y + y;
    float _2z = z + z;
    float _2w = w + w;
    
    
    res->m[0] = 1.0f - _2y * y - _2z * z;
    res->m[1] = _2x * y + _2w * z;
    res->m[2] = _2x * z - _2w * y;
    res->m[3] = position->x;
    res->m[4] = _2x * y - _2w * z;
    res->m[5] = 1.0f - _2x * x - _2z * z;
    res->m[6] = _2y * z + _2w * x;
    res->m[7] = position->y;
    res->m[8] = _2x * z + _2w * y;
    res->m[9] = _2y * z - _2w * x;
    res->m[10] = 1.0f - _2x * x - _2y * y;
    res->m[11] = position->z;
    res->m[12] = 0.0f;
    res->m[13] = 0.0f;
    res->m[14] = 0.0f;
    res->m[15] = 1.0f;
}

AGRESIVE_INLINE void XMatrix4MakeWithQuaternionAndTranslation(XMatrix4*result,XVector4 *q,XVector3 *p)
{
    float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
    
    x2 =  q->x + q->x; y2 =  q->y + q->y; z2 =  q->z + q->z;
    xx =  q->x * x2;   xy =  q->x * y2;   xz =  q->x * z2;
    yy =  q->y * y2;   yz =  q->y * z2;   zz =  q->z * z2;
    wx =  q->w * x2;   wy =  q->w * y2;   wz =  q->w * z2;
    
    
    
    result->m[0] = 1 - (yy + zz);  result->m[1] = xy + wz;        result->m[2] = xz - wy;
    result->m[4] = xy - wz;        result->m[5] = 1 - (xx + zz);  result->m[6] = yz + wx;
    result->m[8] = xz + wy;        result->m[9] = yz - wx;        result->m[10] = 1 - (xx + yy);
    
    result->m[3]  = p->x;
    result->m[7]  = p->y;
    result->m[11] = p->z;
    
    result->m[12] = 0.0f;
    result->m[13] = 0.0f;
    result->m[14] = 0.0f;
    result->m[15] = 1.0f;
    
}

AGRESIVE_INLINE void XMatrix4MakeWithQuaternionAndTranslation2(XMatrix4*result,XVector4 *q,XVector3 *p)
{
    float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
    
    x2 =  q->x + q->x; y2 =  q->y + q->y; z2 =  q->z + q->z;
    xx =  q->x * x2;   xy =  q->x * y2;   xz =  q->x * z2;
    yy =  q->y * y2;   yz =  q->y * z2;   zz =  q->z * z2;
    wx =  q->w * x2;   wy =  q->w * y2;   wz =  q->w * z2;
    
    
    result->m[0] = 1 - (yy + zz);  result->m[4] = xy + wz;        result->m[8] = xz - wy;
    result->m[1] = xy - wz;        result->m[5] = 1 - (xx + zz);  result->m[9] = yz + wx;
    result->m[2] = xz + wy;        result->m[6] = yz - wx;        result->m[10] = 1 - (xx + yy);
    
    result->m[3]  = 0.0f;
    result->m[7]  = 0.0f;
    result->m[11] = 0.0f;
    
    result->m[12] = p->x;
    result->m[13] = p->y;
    result->m[14] = p->z;
    result->m[15] = 1.0f;
}


AGRESIVE_INLINE XMatrix4 XMatrix4GetMatrix3(XMatrix4 matrix)
{
    
    XMatrix4 m = { matrix.m[0], matrix.m[1], matrix.m[2],
        matrix.m[4], matrix.m[5], matrix.m[6],
        matrix.m[8], matrix.m[9], matrix.m[10] };
    return m;
}


AGRESIVE_INLINE void XMatrix4GetMatrix3(XMatrix4* matrix,XMatrix3*out)
{
    
    
    out->m[0] = matrix->m[0];out->m[3] = matrix->m[1];out->m[6] = matrix->m[2];
    out->m[1] = matrix->m[4];out->m[4] = matrix->m[5];out->m[7] = matrix->m[6];
    out->m[2] = matrix->m[8];out->m[5] = matrix->m[9];out->m[8] = matrix->m[10];
    
    //out->m[0] = matrix->m[0];out->m[1] = matrix->m[1];out->m[2] = matrix->m[2];
    //out->m[3] = matrix->m[4];out->m[4] = matrix->m[5];out->m[5] = matrix->m[6];
    //out->m[6] = matrix->m[8];out->m[7] = matrix->m[9];out->m[8] = matrix->m[10];
    
    
}


AGRESIVE_INLINE void XMatrix4Transpose(XMatrix4*result,XMatrix4* matrix)
{
#if defined(__ARM_NEON__)
    float32x4x4_t m = vld4q_f32(matrix->m);
    float32x4x4_t* __restrict__ r = (float32x4x4_t*)result;
    
    (*r).val[0] =m.val[0];
    (*r).val[1] =m.val[1];
    (*r).val[2] =m.val[2];
    (*r).val[3] =m.val[3];
#else
    XMatrix4 m = { matrix->m[0], matrix->m[4], matrix->m[8], matrix->m[12],
        matrix->m[1], matrix->m[5], matrix->m[9], matrix->m[13],
        matrix->m[2], matrix->m[6], matrix->m[10], matrix->m[14],
        matrix->m[3], matrix->m[7], matrix->m[11], matrix->m[15] };
    XMatrix4MakeWithArray(result, &m.m[0]);
    
#endif
}



AGRESIVE_INLINE void XMatrix4MakeWithArray(XMatrix4*result,float m1,float m2,float m3,float m4,float m5,float m6,float m7,float m8,float m9,float m10,float m11,float m12,float m13,float m14,float m15,float m16) {
    result->m[ 0] = m1;
    result->m[ 1] = m2;
    result->m[ 2] = m3;
    result->m[ 3] = m4;
    result->m[ 4] = m5;
    result->m[ 5] = m6;
    result->m[ 6] = m7;
    result->m[ 7] = m8;
    result->m[ 8] = m9;
    result->m[ 9] = m10;
    result->m[10] = m11;
    result->m[11] = m12;
    result->m[12] = m13;
    result->m[13] = m14;
    result->m[14] = m15;
    result->m[15] = m16;
    
}


AGRESIVE_INLINE XMatrix4 XMatrix4MakeRotation(float radians, float x, float y, float z)
{
    XVector3 v = XVector3Make(x, y, z);
    XVector3Normalize(&v);
    
    float cos = cosf(radians);
    float cosp = 1.0f - cos;
    float sin = sinf(radians);
    
    XMatrix4 m = { cos + cosp * v.v[0] * v.v[0],
        cosp * v.v[0] * v.v[1] + v.v[2] * sin,
        cosp * v.v[0] * v.v[2] - v.v[1] * sin,
        0.0f,
        cosp * v.v[0] * v.v[1] - v.v[2] * sin,
        cos + cosp * v.v[1] * v.v[1],
        cosp * v.v[1] * v.v[2] + v.v[0] * sin,
        0.0f,
        cosp * v.v[0] * v.v[2] + v.v[1] * sin,
        cosp * v.v[1] * v.v[2] - v.v[0] * sin,
        cos + cosp * v.v[2] * v.v[2],
        0.0f,
        0.0f,
        0.0f,
        0.0f,
        1.0f };
    
    return m;
}

AGRESIVE_INLINE XMatrix4 XMatrix4MakeXRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    XMatrix4 m = { 1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cos, sin, 0.0f,
        0.0f, -sin, cos, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

AGRESIVE_INLINE XMatrix4 XMatrix4MakeYRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    XMatrix4 m = { cos, 0.0f, -sin, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        sin, 0.0f, cos, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}

AGRESIVE_INLINE XMatrix4 XMatrix4MakeZRotation(float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    XMatrix4 m = { cos, sin, 0.0f, 0.0f,
        -sin, cos, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f };
    
    return m;
}


AGRESIVE_INLINE void XMatrix4RotationX(XMatrix4*in,float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    in->m[0] = 1.0;  in->m[1] = 0.0f; in->m[2] = 0.0f; in->m[3] = 0.0f;
    in->m[4] = 0.0f; in->m[5] = cos;  in->m[6] = sin;  in->m[7] = 0.0f;
    in->m[8] = 0.0f; in->m[9] = -sin; in->m[10] = cos; in->m[11] = 0.0f;
    in->m[12] = 0.0f;in->m[13] = 0.0f;in->m[14] = 0.0f;in->m[15] = 1.0;
}

AGRESIVE_INLINE void XMatrix4RotationY(XMatrix4*in,float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    
    in->m[0]  = cos; in->m[1]  = 0.0f;in->m[2]  = -sin;in->m[3]  = 0.0f;
    in->m[4]  = 0.0f;in->m[5]  = 1.0f;in->m[6]  = 0.0f;in->m[7]  = 0.0f;
    in->m[8]  = sin; in->m[9]  = 0.0f;in->m[10] = cos; in->m[11] = 0.0f;
    in->m[12] = 0.0f;in->m[13] = 0.0f;in->m[14] = 0.0f;in->m[15] = 1.0;
}

AGRESIVE_INLINE void XMatrix4RotationZ(XMatrix4*in,float radians)
{
    float cos = cosf(radians);
    float sin = sinf(radians);
    
    in->m[0]  = cos;  in->m[1]  = sin; in->m[2]  = 0.0f;in->m[3]  = 0.0f;
    in->m[4]  = -sin; in->m[5]  = cos; in->m[6]  = 0.0f;in->m[7]  = 0.0f;
    in->m[8]  = 0.0f; in->m[9]  = 0.0f;in->m[10] = 1.0f;in->m[11] = 0.0f;
    in->m[12] = 0.0f; in->m[13] = 0.0f;in->m[14] = 0.0f;in->m[15] = 1.0;
    
    
}


AGRESIVE_INLINE void XMatrix4MakeWithArray(XMatrix4*result,float values[16])
{
    for (int i = 0; i < 16; i++) {
        result->m[i] = values[i];
    }
}

AGRESIVE_INLINE void XMatrix4AddTranslate(XMatrix4 *matrix, float tx, float ty, float tz)
{
    matrix->m[12] = matrix->m[0] * tx + matrix->m[4] * ty + matrix->m[8]  * tz + matrix->m[12];
    matrix->m[13] = matrix->m[1] * tx + matrix->m[5] * ty + matrix->m[9]  * tz + matrix->m[13];
    matrix->m[14] = matrix->m[2] * tx + matrix->m[6] * ty + matrix->m[10] * tz + matrix->m[14];
}

AGRESIVE_INLINE void XMatrix4Translate(XMatrix4 *matrix, float tx, float ty, float tz)
{
    matrix->m[12] = matrix->m[0] * tx + matrix->m[4] * ty + matrix->m[8]  * tz + matrix->m[12];
    matrix->m[13] = matrix->m[1] * tx + matrix->m[5] * ty + matrix->m[9]  * tz + matrix->m[13];
    matrix->m[14] = matrix->m[2] * tx + matrix->m[6] * ty + matrix->m[10] * tz + matrix->m[14];
}

#define PI_OVER_360 0.0087266
AGRESIVE_INLINE void XMatrix4Perspective(XMatrix4 *matrix,float fovyRadians, float aspect, float nearZ, float farZ)
{
    
    
    float xymax = nearZ * tanf(fovyRadians * (float)PI_OVER_360);
    float ymin = -xymax;
    float xmin = -xymax;
    
    float width = xymax - xmin;
    float height = xymax - ymin;
    
    float depth = farZ - nearZ;
    float q = -(farZ + nearZ) / depth;
    float qn = -2 * (farZ * nearZ) / depth;
    
    float w = 2 * nearZ / width;
    w = w / aspect;
    float h = 2 * nearZ / height;
    
    matrix->m[0]  = w;
    matrix->m[1]  = 0;
    matrix->m[2]  = 0;
    matrix->m[3]  = 0;
    
    matrix->m[4]  = 0;
    matrix->m[5]  = h;
    matrix->m[6]  = 0;
    matrix->m[7]  = 0;
    
    matrix->m[8]  = 0;
    matrix->m[9]  = 0;
    matrix->m[10] = q;
    matrix->m[11] = -1;
    
    matrix->m[12] = 0;
    matrix->m[13] = 0;
    matrix->m[14] = qn;
    matrix->m[15] = 0;
    
    /*
     
     float cotan = 1.0f / tanf(fovyRadians / 2.0f);
     matrix->m[0] = cotan / aspect;
     matrix->m[1] = 0.0f;
     matrix->m[2] = 0.0f;
     matrix->m[3] = 0.0f;
     
     matrix->m[4] = 0.0f;
     matrix->m[5] = cotan;
     matrix->m[6] = 0.0f;
     matrix->m[7] = 0.0f;
     
     matrix->m[8]  = 0.0f;
     matrix->m[9]  = 0.0f;
     matrix->m[10] = (farZ + nearZ) / (nearZ - farZ);
     matrix->m[11] = -1.0f;
     
     matrix->m[12] = 0.0f;
     matrix->m[13] = 0.0f;
     matrix->m[14] = (2.0f * farZ * nearZ) / (nearZ - farZ);
     matrix->m[15] = 0.0f;
     */
}



AGRESIVE_INLINE void XMatrix4MakeOrtho(XMatrix4*result,float w, float h, float zn, float zf){
    
    // float fsn = zf-zn;
    // float fan = zf+zn;
    
    result->m[0]  = 2.0f/w;  result->m[1]   = 0;          result->m[2]  = 0;                 result->m[3]  = 0;
    result->m[4]  = 0;       result->m[5]   = 2.0f/(-h);  result->m[6]  = 0;                 result->m[7]  = 0;
    result->m[8]  = 0;       result->m[9]   = 0;          result->m[10] = -2.0f/(zf-zn);     result->m[11] = 0;
    result->m[12] = -1.0f;   result->m[13]  = 1.0f;       result->m[14] = -(zf+zn)/(zf-zn);  result->m[15] = 1.0f;
}


AGRESIVE_INLINE void XMatrix4MakeOrtho(XMatrix4*result,float left, float right,
                                       float bottom, float top,
                                       float nearZ, float farZ)
{
    float rsl = right - left;
    float tsb = top - bottom;
    
    
    result->m[0] = 2.0f / rsl;result->m[4] = 0.0f;       result->m[8]  = 0.0f;        result->m[12]  = ( left + right ) / ( left - right );
    result->m[1] = 0.0f;      result->m[5] = 2.0f / tsb; result->m[9]  = 0.0f;        result->m[13]  = ( top + bottom ) / ( bottom - top );
    result->m[2] = 0.0f;      result->m[6] = 0.0f;       result->m[10] = 1.0f / (nearZ - farZ); result->m[14]  = nearZ / ( nearZ - farZ );
    result->m[3] = 0.0f;      result->m[7] = 0.0f;       result->m[11] = 0.0f;        result->m[15]  = 1.0f;
}


AGRESIVE_INLINE void XMatrix4Mult(XMatrix4 *result,XMatrix4 *matrixLeft, XMatrix4 *matrixRight)
{
#if defined(__ARM_NEON__)
    
    const float32x4x4_t* __restrict__ m1 = (float32x4x4_t*)matrixLeft;
    const float32x4x4_t* __restrict__ m2 = (float32x4x4_t*)matrixRight;
    float32x4x4_t* __restrict__ r = (float32x4x4_t*)result;
    
    (*r).val[0] = vmulq_n_f32((*m1).val[0], vgetq_lane_f32((*m2).val[0], 0));
    (*r).val[1] = vmulq_n_f32((*m1).val[0], vgetq_lane_f32((*m2).val[1], 0));
    (*r).val[2] = vmulq_n_f32((*m1).val[0], vgetq_lane_f32((*m2).val[2], 0));
    (*r).val[3] = vmulq_n_f32((*m1).val[0], vgetq_lane_f32((*m2).val[3], 0));
    
    (*r).val[0] = vmlaq_n_f32((*r).val[0], (*m1).val[1], vgetq_lane_f32((*m2).val[0], 1));
    (*r).val[1] = vmlaq_n_f32((*r).val[1], (*m1).val[1], vgetq_lane_f32((*m2).val[1], 1));
    (*r).val[2] = vmlaq_n_f32((*r).val[2], (*m1).val[1], vgetq_lane_f32((*m2).val[2], 1));
    (*r).val[3] = vmlaq_n_f32((*r).val[3], (*m1).val[1], vgetq_lane_f32((*m2).val[3], 1));
    
    (*r).val[0] = vmlaq_n_f32((*r).val[0], (*m1).val[2], vgetq_lane_f32((*m2).val[0], 2));
    (*r).val[1] = vmlaq_n_f32((*r).val[1], (*m1).val[2], vgetq_lane_f32((*m2).val[1], 2));
    (*r).val[2] = vmlaq_n_f32((*r).val[2], (*m1).val[2], vgetq_lane_f32((*m2).val[2], 2));
    (*r).val[3] = vmlaq_n_f32((*r).val[3], (*m1).val[2], vgetq_lane_f32((*m2).val[3], 2));
    
    (*r).val[0] = vmlaq_n_f32((*r).val[0], (*m1).val[3], vgetq_lane_f32((*m2).val[0], 3));
    (*r).val[1] = vmlaq_n_f32((*r).val[1], (*m1).val[3], vgetq_lane_f32((*m2).val[1], 3));
    (*r).val[2] = vmlaq_n_f32((*r).val[2], (*m1).val[3], vgetq_lane_f32((*m2).val[2], 3));
    (*r).val[3] = vmlaq_n_f32((*r).val[3], (*m1).val[3], vgetq_lane_f32((*m2).val[3], 3));
#else
    
    result->m[0]  = matrixLeft->m[0] * matrixRight->m[0]  + matrixLeft->m[4] * matrixRight->m[1]  + matrixLeft->m[8] * matrixRight->m[2]   + matrixLeft->m[12] * matrixRight->m[3];
    result->m[4]  = matrixLeft->m[0] * matrixRight->m[4]  + matrixLeft->m[4] * matrixRight->m[5]  + matrixLeft->m[8] * matrixRight->m[6]   + matrixLeft->m[12] * matrixRight->m[7];
    result->m[8]  = matrixLeft->m[0] * matrixRight->m[8]  + matrixLeft->m[4] * matrixRight->m[9]  + matrixLeft->m[8] * matrixRight->m[10]  + matrixLeft->m[12] * matrixRight->m[11];
    result->m[12] = matrixLeft->m[0] * matrixRight->m[12] + matrixLeft->m[4] * matrixRight->m[13] + matrixLeft->m[8] * matrixRight->m[14]  + matrixLeft->m[12] * matrixRight->m[15];
    
    result->m[1]  = matrixLeft->m[1] * matrixRight->m[0]  + matrixLeft->m[5] * matrixRight->m[1]  + matrixLeft->m[9] * matrixRight->m[2]   + matrixLeft->m[13] * matrixRight->m[3];
    result->m[5]  = matrixLeft->m[1] * matrixRight->m[4]  + matrixLeft->m[5] * matrixRight->m[5]  + matrixLeft->m[9] * matrixRight->m[6]   + matrixLeft->m[13] * matrixRight->m[7];
    result->m[9]  = matrixLeft->m[1] * matrixRight->m[8]  + matrixLeft->m[5] * matrixRight->m[9]  + matrixLeft->m[9] * matrixRight->m[10]  + matrixLeft->m[13] * matrixRight->m[11];
    result->m[13] = matrixLeft->m[1] * matrixRight->m[12] + matrixLeft->m[5] * matrixRight->m[13] + matrixLeft->m[9] * matrixRight->m[14]  + matrixLeft->m[13] * matrixRight->m[15];
    
    result->m[2]  = matrixLeft->m[2] * matrixRight->m[0]  + matrixLeft->m[6] * matrixRight->m[1]  + matrixLeft->m[10] * matrixRight->m[2]  + matrixLeft->m[14] * matrixRight->m[3];
    result->m[6]  = matrixLeft->m[2] * matrixRight->m[4]  + matrixLeft->m[6] * matrixRight->m[5]  + matrixLeft->m[10] * matrixRight->m[6]  + matrixLeft->m[14] * matrixRight->m[7];
    result->m[10] = matrixLeft->m[2] * matrixRight->m[8]  + matrixLeft->m[6] * matrixRight->m[9]  + matrixLeft->m[10] * matrixRight->m[10] + matrixLeft->m[14] * matrixRight->m[11];
    result->m[14] = matrixLeft->m[2] * matrixRight->m[12] + matrixLeft->m[6] * matrixRight->m[13] + matrixLeft->m[10] * matrixRight->m[14] + matrixLeft->m[14] * matrixRight->m[15];
    
    result->m[3]  = matrixLeft->m[3] * matrixRight->m[0]  + matrixLeft->m[7] * matrixRight->m[1]  + matrixLeft->m[11] * matrixRight->m[2]  + matrixLeft->m[15] * matrixRight->m[3];
    result->m[7]  = matrixLeft->m[3] * matrixRight->m[4]  + matrixLeft->m[7] * matrixRight->m[5]  + matrixLeft->m[11] * matrixRight->m[6]  + matrixLeft->m[15] * matrixRight->m[7];
    result->m[11] = matrixLeft->m[3] * matrixRight->m[8]  + matrixLeft->m[7] * matrixRight->m[9]  + matrixLeft->m[11] * matrixRight->m[10] + matrixLeft->m[15] * matrixRight->m[11];
    result->m[15] = matrixLeft->m[3] * matrixRight->m[12] + matrixLeft->m[7] * matrixRight->m[13] + matrixLeft->m[11] * matrixRight->m[14] + matrixLeft->m[15] * matrixRight->m[15];
    
#endif
}


AGRESIVE_INLINE void XMatrix4Scale(XMatrix4 *matrix, float sx, float sy, float sz)
{
#if defined(__ARM_NEON__)
    float32x4x4_t* __restrict__ r = (float32x4x4_t*)matrix;
    (*r).val[0] = vmulq_n_f32((*r).val[0], (float32_t)sx);
    (*r).val[1] = vmulq_n_f32((*r).val[1], (float32_t)sy);
    (*r).val[2] = vmulq_n_f32((*r).val[2], (float32_t)sz);
#else
    
    
    matrix->m[0] = matrix->m[0] * sx;matrix->m[4] = matrix->m[4] * sy;matrix->m[8]  = matrix->m[8]  * sz;
    matrix->m[1] = matrix->m[1] * sx;matrix->m[5] = matrix->m[5] * sy;matrix->m[9]  = matrix->m[9]  * sz;
    matrix->m[2] = matrix->m[2] * sx;matrix->m[6] = matrix->m[6] * sy;matrix->m[10] = matrix->m[10] * sz;
    matrix->m[3] = matrix->m[3] * sx;matrix->m[7] = matrix->m[7] * sy;matrix->m[11] = matrix->m[11] * sz;
#endif
}

AGRESIVE_INLINE void XMatrix4TranslateWithVector3(XMatrix4 *matrix, float x, float y, float z)
{
    matrix->m[12] = matrix->m[0] * x + matrix->m[4] * y + matrix->m[8]  * z + matrix->m[12];
    matrix->m[13] = matrix->m[1] * x + matrix->m[5] * y + matrix->m[9]  * z + matrix->m[13];
    matrix->m[14] = matrix->m[2] * x + matrix->m[6] * y + matrix->m[10] * z + matrix->m[14];
    
}





AGRESIVE_INLINE void XMatrix4MultiplyVector3(XVector3*result,XMatrix4* matrixLeft, XVector3* vectorRight)
{
    XVector4 tmp = {vectorRight->v[0], vectorRight->v[1], vectorRight->v[2], 0.0f};
    XVector4 tmpR;
    XMatrix4MultiplyVector4(&tmpR,matrixLeft, &tmp);
    
    result->x = tmpR.x;
    result->y = tmpR.y;
    result->z = tmpR.z;
}

AGRESIVE_INLINE void XMatrix4MultiplyVector3WithTranslation(XVector3*result,XMatrix4* matrixLeft, XVector3* vectorRight)
{
    XVector4 tmp = {vectorRight->v[0], vectorRight->v[1], vectorRight->v[2], 1.0f};
    XVector4 tmpR;
    XMatrix4MultiplyVector4(&tmpR,matrixLeft, &tmp);
    result->x = tmpR.x;
    result->y = tmpR.y;
    result->z = tmpR.z;
}

AGRESIVE_INLINE void XMatrix4MultiplyAndProjectVector3(XVector3*result,XMatrix4* matrixLeft, XVector3* vectorRight)
{
    XVector4 tmp = {vectorRight->v[0], vectorRight->v[1], vectorRight->v[2], 1.0f};
    XVector4 tmpR;
    XMatrix4MultiplyVector4(&tmpR,matrixLeft, &tmp);
    
    result->x = tmpR.x;
    result->y = tmpR.y;
    result->z = tmpR.z;
    
    XVector3MultiplyScalar(result, 1.0f / tmpR.w);
}




AGRESIVE_INLINE void XMatrix4Inverse(XMatrix4 *mat)
{
    // 84+4+16 = 104 multiplications
    //			   1 division
    float det, invDet;
    
    // 2x2 sub-determinants required to calculate 4x4 determinant
    float det2_01_01 = mat->m[0] * mat->m[5] - mat->m[1] * mat->m[4];
    float det2_01_02 = mat->m[0] * mat->m[6] - mat->m[2] * mat->m[4];
    float det2_01_03 = mat->m[0] * mat->m[7] - mat->m[3] * mat->m[4];
    float det2_01_12 = mat->m[1] * mat->m[6] - mat->m[2] * mat->m[5];
    float det2_01_13 = mat->m[1] * mat->m[7] - mat->m[3] * mat->m[5];
    float det2_01_23 = mat->m[2] * mat->m[7] - mat->m[3] * mat->m[6];
    
    // 3x3 sub-determinants required to calculate 4x4 determinant
    float det3_201_012 = mat->m[8] * det2_01_12 - mat->m[9] * det2_01_02 + mat->m[10] * det2_01_01;
    float det3_201_013 = mat->m[8] * det2_01_13 - mat->m[9] * det2_01_03 + mat->m[11] * det2_01_01;
    float det3_201_023 = mat->m[8] * det2_01_23 - mat->m[10] * det2_01_03 + mat->m[11] * det2_01_02;
    float det3_201_123 = mat->m[9] * det2_01_23 - mat->m[10] * det2_01_13 + mat->m[11] * det2_01_12;
    
    det = ( - det3_201_123 * mat->m[12] + det3_201_023 * mat->m[13] - det3_201_013 * mat->m[14] + det3_201_012 * mat->m[15] );
    
    
    
    invDet = 1.0f / det;
    
    // remaining 2x2 sub-determinants
    float det2_03_01 = mat->m[0] * mat->m[13] - mat->m[1] * mat->m[12];
    float det2_03_02 = mat->m[0] * mat->m[14] - mat->m[2] * mat->m[12];
    float det2_03_03 = mat->m[0] * mat->m[15] - mat->m[3] * mat->m[12];
    float det2_03_12 = mat->m[1] * mat->m[14] - mat->m[2] * mat->m[13];
    float det2_03_13 = mat->m[1] * mat->m[15] - mat->m[3] * mat->m[13];
    float det2_03_23 = mat->m[2] * mat->m[15] - mat->m[3] * mat->m[14];
    
    float det2_13_01 = mat->m[4] * mat->m[13] - mat->m[5] * mat->m[12];
    float det2_13_02 = mat->m[4] * mat->m[14] - mat->m[6] * mat->m[12];
    float det2_13_03 = mat->m[4] * mat->m[15] - mat->m[7] * mat->m[12];
    float det2_13_12 = mat->m[5] * mat->m[14] - mat->m[6] * mat->m[13];
    float det2_13_13 = mat->m[5] * mat->m[15] - mat->m[7] * mat->m[13];
    float det2_13_23 = mat->m[6] * mat->m[15] - mat->m[7] * mat->m[14];
    
    // remaining 3x3 sub-determinants
    float det3_203_012 = mat->m[8] * det2_03_12 - mat->m[9] * det2_03_02 + mat->m[10] * det2_03_01;
    float det3_203_013 = mat->m[8] * det2_03_13 - mat->m[9] * det2_03_03 + mat->m[11] * det2_03_01;
    float det3_203_023 = mat->m[8] * det2_03_23 - mat->m[10] * det2_03_03 + mat->m[11] * det2_03_02;
    float det3_203_123 = mat->m[9] * det2_03_23 - mat->m[10] * det2_03_13 + mat->m[11] * det2_03_12;
    
    float det3_213_012 = mat->m[8] * det2_13_12 - mat->m[9] * det2_13_02 + mat->m[10] * det2_13_01;
    float det3_213_013 = mat->m[8] * det2_13_13 - mat->m[9] * det2_13_03 + mat->m[11] * det2_13_01;
    float det3_213_023 = mat->m[8] * det2_13_23 - mat->m[10] * det2_13_03 + mat->m[11] * det2_13_02;
    float det3_213_123 = mat->m[9] * det2_13_23 - mat->m[10] * det2_13_13 + mat->m[11] * det2_13_12;
    
    float det3_301_012 = mat->m[12] * det2_01_12 - mat->m[13] * det2_01_02 + mat->m[14] * det2_01_01;
    float det3_301_013 = mat->m[12] * det2_01_13 - mat->m[13] * det2_01_03 + mat->m[15] * det2_01_01;
    float det3_301_023 = mat->m[12] * det2_01_23 - mat->m[14] * det2_01_03 + mat->m[15] * det2_01_02;
    float det3_301_123 = mat->m[13] * det2_01_23 - mat->m[14] * det2_01_13 + mat->m[15] * det2_01_12;
    
    mat->m[0] = - det3_213_123 * invDet;
    mat->m[4] = + det3_213_023 * invDet;
    mat->m[8] = - det3_213_013 * invDet;
    mat->m[12] = + det3_213_012 * invDet;
    
    mat->m[1] = + det3_203_123 * invDet;
    mat->m[5] = - det3_203_023 * invDet;
    mat->m[9] = + det3_203_013 * invDet;
    mat->m[13] = - det3_203_012 * invDet;
    
    mat->m[2] = + det3_301_123 * invDet;
    mat->m[6] = - det3_301_023 * invDet;
    mat->m[10] = + det3_301_013 * invDet;
    mat->m[14] = - det3_301_012 * invDet;
    
    mat->m[3] = - det3_201_123 * invDet;
    mat->m[7] = + det3_201_023 * invDet;
    mat->m[11] = - det3_201_013 * invDet;
    mat->m[15] = + det3_201_012 * invDet;
    
}



#endif
