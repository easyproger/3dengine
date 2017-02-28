/*
 *  mathLib.h
 *  3dEngine
 *
 *  Created by I art on 09.01.10.
 *  Copyright 2010 iArtCorp. All rights reserved.
 *
 */
#ifndef MATHLIB_H
#define MATHLIB_H
#include <math.h>


#define X_INLINE	static __inline__



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <GL/glew.h>
#else
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>
#endif



#include "XTypes.h"



#ifdef __cplusplus


extern "C" {
#endif
    // new math lib
    
 
    
    
    
    
    
    
    // MATRIX4x4
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
#define MATHLIB_API
    
    
    
	
    typedef struct
    {
        GLfloat   m[4][4];
    } Matrix4x4;
    typedef struct
    {
        GLfloat   m[3][3];
    } Matrix3x3;
    
    typedef struct /* vertex4 */ 
    {
        float x, y, z,w;
    }VERTEX4;
    
    typedef struct /*vertex3*/
    {
        GLfloat x,y,z;	
    }VERTEX3;
    
    
    
    
    typedef struct /*vertex2*/
    {
        GLfloat x,y;	
    }VERTEX2;
    
    typedef struct /*vertex2*/
    {
        VERTEX3 c;
        float width;
        float height;
        float depth;
    }AABB;
    
    typedef struct {
        VERTEX3 v_00;
        VERTEX3 v_10;
        VERTEX3 v_11;
        VERTEX3 v_01;
    }Quads;
    
    typedef struct {
        VERTEX2 v0;
        VERTEX2 v1;
    }Quads2D;
    
    typedef struct {
        VERTEX3 v_00;
        VERTEX3 v_10;
        VERTEX3 v_11;
    }Triangle;
    
    typedef struct {
        int t[3];
    }TriInd;

    
    
    
    
	
	// MATRIX4x4MATH	
	void MATHLIB_API Matrix4x4Multiply(Matrix4x4 *result, Matrix4x4 *srcA, Matrix4x4 *srcB);
	void MATHLIB_API Matrix4x4Inverse1(Matrix4x4 *mat);
	void MATHLIB_API Matrix4x4Transpose(Matrix4x4 *mat);
	void MATHLIB_API Matrix4x4Frustum(Matrix4x4 *result, float left, float right, float bottom, float top, float nearZ, float farZ);
	void MATHLIB_API Matrix4x4Perspective(Matrix4x4 *result, float fovy, float aspect, float nearZ, float farZ);
	void MATHLIB_API Matrix4x4Translate(Matrix4x4 *result, GLfloat tx, GLfloat ty, GLfloat tz);
	void MATHLIB_API Matrix4x4Rotate(Matrix4x4 *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	void MATHLIB_API Matrix4x4LoadIdentity(Matrix4x4 *result);
    void MATHLIB_API Matrix4x4Copy(Matrix4x4 *result, Matrix4x4 *src);
	void MATHLIB_API Matrix4to3Inverse(Matrix3x3 *result,Matrix4x4 *src);
    // MATRIX3x3MATH
    void MATHLIB_API Matrix4to3(Matrix3x3 *result, Matrix4x4 *src);
    
    
    void MATHLIB_API buildGLPerspectiveMatrix(float *m, float fov, float aspect, float zNear, float zFar);
    
	// QuaternionMath
	void MATHLIB_API QuaternionAndPositionToMatrix4x4(Matrix4x4*result,VERTEX4 *q,VERTEX3 *p);	
	void MATHLIB_API QuaternionToMatrix4x4(Matrix4x4*result, VERTEX4 *rotation);
	void MATHLIB_API Matrix4x4ToQuaternion(VERTEX4*result, Matrix4x4 *mat);
	void MATHLIB_API QuaternionInverse(VERTEX4  *qa );
	void MATHLIB_API Slerp(VERTEX4 * res, VERTEX4 * q, VERTEX4 * p, float t);
	void MATHLIB_API QuaternionsNormalize(VERTEX4*result);
	void MATHLIB_API QuaternionsMultiply(VERTEX4 *qr, VERTEX4 *qa, VERTEX4 *qb );
	// VERTEXMATH
    void MATHLIB_API vec4Old(VERTEX4*result, float x, float y,float z,float w);
	void MATHLIB_API vec3Old(VERTEX3*result, float x, float y,float z);
	void MATHLIB_API Vec3ADD(VERTEX3 *result,VERTEX3 *v1,VERTEX3 *v2);
	void MATHLIB_API Vec3DEC(VERTEX3 *result,VERTEX3 *v1,VERTEX3 *v2);
	void MATHLIB_API Vec3Mul(VERTEX3 *result,VERTEX3 *v1,VERTEX3 *v2);
   float MATHLIB_API DotVec3(VERTEX3 *v1,VERTEX3*v2);
	void MATHLIB_API NormalizeVec3(VERTEX3 *src);
	void MATHLIB_API CrossVec3(VERTEX3*result,VERTEX3 *v1, VERTEX3*v2);
	void MATHLIB_API ScaleVec3(VERTEX4*result,VERTEX4 *src,float s);
	void MATHLIB_API Vec3Lerp(VERTEX3*ret,VERTEX3* v1, VERTEX3* v2, float t);
	// SAMEMATH
	int  MATHLIB_API clamp(int X, int Min, int Max);
	void MATHLIB_API ComputeNormals(VERTEX3*res,VERTEX3 *u,VERTEX3 *v,VERTEX3 *w);
	

#ifdef __cplusplus
}
#endif

#endif // ESUTIL_H