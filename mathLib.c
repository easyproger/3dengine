/*
 *  mathLib.c
 *  3dEngine
 *
 *  Created by I art on 09.01.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "mathLib.h"

#define PI 3.1415926535897932384626433832795f
#define PI_OVER_180	 0.017453292519943295769236907684886
#define PI_OVER_360	 0.0087266462599716478846184538424431

#define DELTA 0.0005f






// Math Lib









// ------------------------------------------------------------------ Matrix4x4 MATH ------------------------------------------------------------------ //

void MATHLIB_API
Matrix4x4Multiply(Matrix4x4 *result, Matrix4x4 *srcA, Matrix4x4 *srcB)
{
    Matrix4x4    tmp;
    int         i;
	
	for (i=0; i<4; i++)
	{
		tmp.m[i][0] =	(srcA->m[i][0] * srcB->m[0][0]) +
		(srcA->m[i][1] * srcB->m[1][0]) +
		(srcA->m[i][2] * srcB->m[2][0]) +
		(srcA->m[i][3] * srcB->m[3][0]) ;
		
		tmp.m[i][1] =	(srcA->m[i][0] * srcB->m[0][1]) + 
		(srcA->m[i][1] * srcB->m[1][1]) +
		(srcA->m[i][2] * srcB->m[2][1]) +
		(srcA->m[i][3] * srcB->m[3][1]) ;
		
		tmp.m[i][2] =	(srcA->m[i][0] * srcB->m[0][2]) + 
		(srcA->m[i][1] * srcB->m[1][2]) +
		(srcA->m[i][2] * srcB->m[2][2]) +
		(srcA->m[i][3] * srcB->m[3][2]) ;
		
		tmp.m[i][3] =	(srcA->m[i][0] * srcB->m[0][3]) + (srcA->m[i][1] * srcB->m[1][3]) +(srcA->m[i][2] * srcB->m[2][3]) +(srcA->m[i][3] * srcB->m[3][3]) ;
	}
    // XTODO : old matematic (
    
    //void *, const void *, size_t
   // memcpy(result, &tmp, sizeof(Matrix4x4));
}

void MATHLIB_API
buildGLPerspectiveMatrix(float *m, float fov, float aspect, float zNear, float zFar)
{
    
    const float h = 1.0f/tanf(fov*PI_OVER_360);
    float neg_depth = zNear-zFar;
    
    m[0] = h / aspect;
    m[1] = 0;
    m[2] = 0;
    m[3] = 0;
    
    m[4] = 0;
    m[5] = h;
    m[6] = 0;
    m[7] = 0;
    
    m[8] = 0;
    m[9] = 0;
    m[10] = (zFar + zNear)/neg_depth;
    m[11] = -1;
    
    m[12] = 0;
    m[13] = 0;
    m[14] = 2.0f*(zNear*zFar)/neg_depth;
    m[15] = 0;
}

void MATHLIB_API
Matrix4x4Inverse1(Matrix4x4 *mat) 
{
	/*
	// 84+4+16 = 104 multiplications
	//			   1 division
	double det, invDet;
	
	// 2x2 sub-determinants required to calculate 4x4 determinant
	float det2_01_01 = mat->m[0][0] * mat->m[1][1] - mat->m[0][1] * mat->m[1][0];
	float det2_01_02 = mat->m[0][0] * mat->m[1][2] - mat->m[0][2] * mat->m[1][0];
	float det2_01_03 = mat->m[0][0] * mat->m[1][3] - mat->m[0][3] * mat->m[1][0];
	float det2_01_12 = mat->m[0][1] * mat->m[1][2] - mat->m[0][2] * mat->m[1][1];
	float det2_01_13 = mat->m[0][1] * mat->m[1][3] - mat->m[0][3] * mat->m[1][1];
	float det2_01_23 = mat->m[0][2] * mat->m[1][3] - mat->m[0][3] * mat->m[1][2];
	
	// 3x3 sub-determinants required to calculate 4x4 determinant
	float det3_201_012 = mat->m[2][0] * det2_01_12 - mat->m[2][1] * det2_01_02 + mat->m[2][2] * det2_01_01;
	float det3_201_013 = mat->m[2][0] * det2_01_13 - mat->m[2][1] * det2_01_03 + mat->m[2][3] * det2_01_01;
	float det3_201_023 = mat->m[2][0] * det2_01_23 - mat->m[2][2] * det2_01_03 + mat->m[2][3] * det2_01_02;
	float det3_201_123 = mat->m[2][1] * det2_01_23 - mat->m[2][2] * det2_01_13 + mat->m[2][3] * det2_01_12;
	
	det = ( - det3_201_123 * mat->m[3][0] + det3_201_023 * mat->m[3][1] - det3_201_013 * mat->m[3][2] + det3_201_012 * mat->m[3][3] );
	
	
	
	invDet = 1.0f / det;
	
	// remaining 2x2 sub-determinants
	float det2_03_01 = mat->m[0][0] * mat->m[3][1] - mat->m[0][1] * mat->m[3][0];
	float det2_03_02 = mat->m[0][0] * mat->m[3][2] - mat->m[0][2] * mat->m[3][0];
	float det2_03_03 = mat->m[0][0] * mat->m[3][3] - mat->m[0][3] * mat->m[3][0];
	float det2_03_12 = mat->m[0][1] * mat->m[3][2] - mat->m[0][2] * mat->m[3][1];
	float det2_03_13 = mat->m[0][1] * mat->m[3][3] - mat->m[0][3] * mat->m[3][1];
	float det2_03_23 = mat->m[0][2] * mat->m[3][3] - mat->m[0][3] * mat->m[3][2];
	
	float det2_13_01 = mat->m[1][0] * mat->m[3][1] - mat->m[1][1] * mat->m[3][0];
	float det2_13_02 = mat->m[1][0] * mat->m[3][2] - mat->m[1][2] * mat->m[3][0];
	float det2_13_03 = mat->m[1][0] * mat->m[3][3] - mat->m[1][3] * mat->m[3][0];
	float det2_13_12 = mat->m[1][1] * mat->m[3][2] - mat->m[1][2] * mat->m[3][1];
	float det2_13_13 = mat->m[1][1] * mat->m[3][3] - mat->m[1][3] * mat->m[3][1];
	float det2_13_23 = mat->m[1][2] * mat->m[3][3] - mat->m[1][3] * mat->m[3][2];
	
	// remaining 3x3 sub-determinants
	float det3_203_012 = mat->m[2][0] * det2_03_12 - mat->m[2][1] * det2_03_02 + mat->m[2][2] * det2_03_01;
	float det3_203_013 = mat->m[2][0] * det2_03_13 - mat->m[2][1] * det2_03_03 + mat->m[2][3] * det2_03_01;
	float det3_203_023 = mat->m[2][0] * det2_03_23 - mat->m[2][2] * det2_03_03 + mat->m[2][3] * det2_03_02;
	float det3_203_123 = mat->m[2][1] * det2_03_23 - mat->m[2][2] * det2_03_13 + mat->m[2][3] * det2_03_12;
	
	float det3_213_012 = mat->m[2][0] * det2_13_12 - mat->m[2][1] * det2_13_02 + mat->m[2][2] * det2_13_01;
	float det3_213_013 = mat->m[2][0] * det2_13_13 - mat->m[2][1] * det2_13_03 + mat->m[2][3] * det2_13_01;
	float det3_213_023 = mat->m[2][0] * det2_13_23 - mat->m[2][2] * det2_13_03 + mat->m[2][3] * det2_13_02;
	float det3_213_123 = mat->m[2][1] * det2_13_23 - mat->m[2][2] * det2_13_13 + mat->m[2][3] * det2_13_12;
	
	float det3_301_012 = mat->m[3][0] * det2_01_12 - mat->m[3][1] * det2_01_02 + mat->m[3][2] * det2_01_01;
	float det3_301_013 = mat->m[3][0] * det2_01_13 - mat->m[3][1] * det2_01_03 + mat->m[3][3] * det2_01_01;
	float det3_301_023 = mat->m[3][0] * det2_01_23 - mat->m[3][2] * det2_01_03 + mat->m[3][3] * det2_01_02;
	float det3_301_123 = mat->m[3][1] * det2_01_23 - mat->m[3][2] * det2_01_13 + mat->m[3][3] * det2_01_12;
	
	mat->m[0][0] = - det3_213_123 * invDet;
	mat->m[1][0] = + det3_213_023 * invDet;
	mat->m[2][0] = - det3_213_013 * invDet;
	mat->m[3][0] = + det3_213_012 * invDet;
	
	mat->m[0][1] = + det3_203_123 * invDet;
	mat->m[1][1] = - det3_203_023 * invDet;
	mat->m[2][1] = + det3_203_013 * invDet;
	mat->m[3][1] = - det3_203_012 * invDet;
	
	mat->m[0][2] = + det3_301_123 * invDet;
	mat->m[1][2] = - det3_301_023 * invDet;
	mat->m[2][2] = + det3_301_013 * invDet;
	mat->m[3][2] = - det3_301_012 * invDet;
	
	mat->m[0][3] = - det3_201_123 * invDet;
	mat->m[1][3] = + det3_201_023 * invDet;
	mat->m[2][3] = - det3_201_013 * invDet;
	mat->m[3][3] = + det3_201_012 * invDet;
	*/
}


void MATHLIB_API
Matrix4x4Transpose(Matrix4x4 *mat)
{
	Matrix4x4 transpose;
	int		i, j;
	
	for( i = 0; i < 4; i++ ) {
		for( j = 0; j < 4; j++ ) {
			transpose.m[ i ][ j ] = mat->m[ j ][ i ];
        }
	}
	//memcpy(&transpose, &mat, sizeof(Matrix4x4));
}

void MATHLIB_API
Matrix4x4Frustum(Matrix4x4 *result, float left, float right, float bottom, float top, float nearZ, float farZ)
{
    float       deltaX = right - left;
    float       deltaY = top - bottom;
    float       deltaZ = farZ - nearZ;
    Matrix4x4    frust;
	
    if ( (nearZ <= 0.0f) || (farZ <= 0.0f) ||
		(deltaX <= 0.0f) || (deltaY <= 0.0f) || (deltaZ <= 0.0f) )
		return;
	
    frust.m[0][0] = 2.0f * nearZ / deltaX;
    frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;
	
    frust.m[1][1] = 2.0f * nearZ / deltaY;
    frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;
	
    frust.m[2][0] = (right + left) / deltaX;
    frust.m[2][1] = (top + bottom) / deltaY;
    frust.m[2][2] = -(nearZ + farZ) / deltaZ;
    frust.m[2][3] = -1.0f;
	
    frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
    frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;
	
    Matrix4x4Multiply(result, &frust, result);
}


void MATHLIB_API 
Matrix4x4Perspective(Matrix4x4 *result, float fovy, float aspect, float nearZ, float farZ)
{
	GLfloat frustumW, frustumH;
	
	frustumH = tanf( fovy / 360.0f * PI ) * nearZ;
	frustumW = frustumH * aspect;
	
	Matrix4x4Frustum( result, -frustumW, frustumW, -frustumH, frustumH, nearZ, farZ );
}


void MATHLIB_API
Matrix4x4Translate(Matrix4x4 *result, GLfloat tx, GLfloat ty, GLfloat tz)
{
    result->m[3][0] += (result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz);
    result->m[3][1] += (result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz);
    result->m[3][2] += (result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz);
    result->m[3][3] += (result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz);
}

void MATHLIB_API
Matrix4x4Rotate(Matrix4x4 *result, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat sinAngle, cosAngle;
	GLfloat mag = sqrtf(x * x + y * y + z * z);
	
	sinAngle = sinf ( angle * PI / 180.0f );
	cosAngle = cosf ( angle * PI / 180.0f );
	if ( mag > 0.0f )
	{
		GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
		GLfloat oneMinusCos;
		Matrix4x4 rotMat;
		
		x /= mag;
		y /= mag;
		z /= mag;
		
		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sinAngle;
		ys = y * sinAngle;
		zs = z * sinAngle;
		oneMinusCos = 1.0f - cosAngle;
		
		rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
		rotMat.m[0][1] = (oneMinusCos * xy) - zs;
		rotMat.m[0][2] = (oneMinusCos * zx) + ys;
		rotMat.m[0][3] = 0.0F; 
		
		rotMat.m[1][0] = (oneMinusCos * xy) + zs;
		rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
		rotMat.m[1][2] = (oneMinusCos * yz) - xs;
		rotMat.m[1][3] = 0.0F;
		
		rotMat.m[2][0] = (oneMinusCos * zx) - ys;
		rotMat.m[2][1] = (oneMinusCos * yz) + xs;
		rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
		rotMat.m[2][3] = 0.0F; 
		
		rotMat.m[3][0] = 0.0F;
		rotMat.m[3][1] = 0.0F;
		rotMat.m[3][2] = 0.0F;
		rotMat.m[3][3] = 1.0F;
		
		Matrix4x4Multiply( result, &rotMat, result );
	}
}

void MATHLIB_API
Matrix4x4LoadIdentity(Matrix4x4 *result)
{
    int		i, j;
	for( i = 0; i < 4; i++ ) {
		for( j = 0; j < 4; j++ ) {
			result->m[ i ][ j ] = 0;
        }
	}
    result->m[0][0] = 1.0f;
    result->m[1][1] = 1.0f;
    result->m[2][2] = 1.0f;
    result->m[3][3] = 1.0f;
}

void MATHLIB_API
Matrix4x4Copy(Matrix4x4 *result, Matrix4x4 *src)
{
    int		i, j;
	for( i = 0; i < 4; i++ ) {
		for( j = 0; j < 4; j++ ) {
			result->m[ i ][ j ] = src->m[ i ][ j ];
        }
	}
}
void MATHLIB_API
Matrix4to3(Matrix3x3 *result, Matrix4x4 *src)
{
    int		i, j;
	for( i = 0; i < 3; i++ ) {
		for( j = 0; j < 3; j++ ) {
			result->m[ i ][ j ] = src->m[ i ][ j ];
        }
	}
}


void MATHLIB_API
Matrix4to3Inverse(Matrix3x3 *result,Matrix4x4 *src){
    Matrix4x4 viewMatrixInv;
    Matrix4x4LoadIdentity(&viewMatrixInv);
    Matrix4x4Copy(&viewMatrixInv, src);
    Matrix4x4Inverse1(&viewMatrixInv);
    Matrix4to3(result, &viewMatrixInv);
}



// ------------------------------------------------------------------ Quaternion MATH ------------------------------------------------------------------ //


void MATHLIB_API
QuaternionAndPositionToMatrix4x4(Matrix4x4*result,VERTEX4 *q,VERTEX3 *p)
{
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
	
	x2 =  q->x + q->x; y2 =  q->y + q->y; z2 =  q->z + q->z;
	xx =  q->x * x2;  xy =  q->x * y2;  xz =  q->x * z2;
	yy =  q->y * y2;  yz =  q->y * z2;  zz =  q->z * z2;
	wx =  q->w * x2;  wy =  q->w * y2;  wz =  q->w * z2;
	
	
	result->m[0][0] = 1 - (yy + zz);  result->m[1][0] = xy + wz;        result->m[2][0] = xz - wy;
	result->m[0][1] = xy - wz;        result->m[1][1] = 1 - (xx + zz);  result->m[2][1] = yz + wx;
	result->m[0][2] = xz + wy;        result->m[1][2] = yz - wx;        result->m[2][2] = 1 - (xx + yy);
	
	result->m[3][0] = 0;
	result->m[3][1] = 0;
	result->m[3][2] = 0;
	
	result->m[0][3] = p->x;
	result->m[1][3] = p->y;
	result->m[2][3] = p->z;
	result->m[3][3] = 1;
	
}

void MATHLIB_API
QuaternionToMatrix4x4(Matrix4x4*result, VERTEX4 *rotation)
{
    double x = rotation->x;
    float num9 = (float) (x * x);
    double y = rotation->y;
    float num8 = (float) (y * y);
    double z = rotation->z;
    float num7 = (float) (z * z);
    float num6 = rotation->y * rotation->x;
    float num5 = rotation->w * rotation->z;
    float num4 = rotation->z * rotation->x;
    float num3 = rotation->w * rotation->y;
    float num2 = rotation->z * rotation->y;
    float num =  rotation->w * rotation->x;
    result->m[0][0] = (float) (1.0 - ((num7 + num8) * 2.0));
    result->m[0][1] = (float) ((num5 + num6) * 2.0);
    result->m[0][2] = (float) ((num4 - num3) * 2.0);
    result->m[0][3] = 0;
    result->m[1][0] = (float) ((num6 - num5) * 2.0);
    result->m[1][1] = (float) (1.0 - ((num7 + num9) * 2.0));
    result->m[1][2] = (float) ((num + num2) * 2.0);
    result->m[1][3] = 0;
    result->m[2][0] = (float) ((num3 + num4) * 2.0);
    result->m[2][1] = (float) ((num2 - num) * 2.0);
    result->m[2][2] = (float) (1.0 - ((num8 + num9) * 2.0));
    result->m[2][3] = 0;
    result->m[3][0] = 0;
    result->m[3][1] = 0;
    result->m[3][2] = 0;
    result->m[3][3] = 1;
}

void MATHLIB_API
Matrix4x4ToQuaternion(VERTEX4*result, Matrix4x4 *mat)
{
	/*
	float  tr, s, q[4];
	int    i, j, k;
	
	int nxt[3] = {1, 2, 0};
	
	tr = mat->m[0][0] + mat->m[1][1] + mat->m[2][2];
	
	if (tr > 0.0)
	{
		s = sqrt (tr + 1.0);
		result->w = s / 2.0;
		s = 0.5 / s;
		result->x = ( mat->m[1][2] - mat->m[2][1]) * s;
		result->y = ( mat->m[2][0] - mat->m[0][2]) * s;
		result->z = ( mat->m[0][1] - mat->m[1][0]) * s;
	}
	else
	{
		i = 0;
		if ( mat->m[1][1] > mat->m[0][0]) i = 1;
		if ( mat->m[2][2] > mat->m[i][i]) i = 2;
		j = nxt[i];
		k = nxt[j];
		
		s = sqrt (( mat->m[i][i] - ( mat->m[j][j] +  mat->m[k][k])) + 1.0);
		
		q[i] = s * 0.5;
		
		if (s != 0.0) s = 0.5 / s;
		
		q[3] = ( mat->m[j][k] -  mat->m[k][j]) * s;
		q[j] = ( mat->m[i][j] +  mat->m[j][i]) * s;
		q[k] = ( mat->m[i][k] +  mat->m[k][i]) * s;
		
		result->x = q[0];
		result->y = q[1];
		result->z = q[2];
		result->w = q[3];
	}
	result->x = -result->x;
	result->y = -result->y;
	result->z = -result->z;
	result->w = result->w;
	*/
}
void MATHLIB_API
QuaternionInverse(VERTEX4  *qa )
{
    qa->w =  qa->w;
    qa->x = -qa->x;
    qa->y = -qa->y;
    qa->z = -qa->z;
}

void MATHLIB_API
QuaternionsMultiply(VERTEX4 *result,VERTEX4 *left, VERTEX4 *right )
{
    float x = left->x;
    float y = left->y;
    float z = left->z;
    float w = left->w;
    float num4 = right->x;
    float num3 = right->y;
    float num2 = right->z;
    float num = right->w;
    result->x = (((num4 * w) + (num * x)) + (num2 * y)) - (num3 * z);
    result->y = (((num3 * w) + (num * y)) + (num4 * z)) - (num2 * x);
    result->z = (((num2 * w) + (num * z)) + (num3 * x)) - (num4 * y);
    result->w = (num * w) - (((num3 * y) + (num4 * x)) + (num2 * z));
	QuaternionsNormalize(result);
	
}


void MATHLIB_API
QuaternionsNormalize(VERTEX4*result)
{ 
	float mag = (result->x*result->x + result->y*result->y + result->z*result->z + result->w*result->w); 
	if (mag > 0){
		mag = 1/sqrtf(mag);
 	    result->x *= mag;	
		result->y *= mag; 
		result->z *= mag;	
		result->w *= mag; 
	}
}


void MATHLIB_API
Slerp(VERTEX4 * res, VERTEX4 * q, VERTEX4 * p, float t)
{
	/*
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
	
	res->x = scale0 * q->x + scale1 * p1[0];
	res->y = scale0 * q->y + scale1 * p1[1];
	res->z = scale0 * q->z + scale1 * p1[2];
	res->w = scale0 * q->w + scale1 * p1[3];
	*/
}


// ------------------------------------------------------------------ VERTEX MATH ------------------------------------------------------------------ //

void MATHLIB_API
vec3Old(VERTEX3*result, float x, float y,float z)
{
	result->x = x;
	result->y = y;
	result->z = z;
}
void MATHLIB_API
vec4Old(VERTEX4*result, float x, float y,float z,float w)
{
	result->x = x;
	result->y = y;
	result->z = z;
    result->w = w;
}
void MATHLIB_API
Vec3ADD(VERTEX3 *result,VERTEX3 *v1,VERTEX3 *v2)
{
	result->x = v1->x+v2->x;
	result->y = v1->y+v2->y;
	result->z = v1->z+v2->z;
}
void MATHLIB_API
Vec3DEC(VERTEX3 *result,VERTEX3 *v1,VERTEX3 *v2)
{
	result->x = v1->x-v2->x;
	result->y = v1->y-v2->y;
	result->z = v1->z-v2->z;
}
void MATHLIB_API
Vec3Mul(VERTEX3 *result,VERTEX3 *v1,VERTEX3 *v2)
{
	result->x = v1->x*v2->x;
	result->y = v1->y*v2->y;
	result->z = v1->z*v2->z;
}

void MATHLIB_API
CrossVec3(VERTEX3*result,VERTEX3 *v1, VERTEX3*v2)
{
	result->x = v1->y*v2->z-v2->y*v1->z;
	result->y = v1->z*v2->x-v2->z*v1->x;
	result->z = v1->x*v2->y-v2->x*v1->y;
}

float MATHLIB_API
DotVec3(VERTEX3 *v1,VERTEX3*v2){return (v1->x*v2->x+v1->y*v2->y+v1->z*v2->z);}

void MATHLIB_API
NormalizeVec3(VERTEX3 *src)
{
	/*
	float inv_length = sqrt(src->x*src->x + src->y*src->y + src->z*src->z);
	if (inv_length!=0.0) {
		inv_length = 1.0f /inv_length;
		src->x = src->x*inv_length;
	    src->y = src->y*inv_length;
		src->z = src->z*inv_length;
	}
	*/
}

void MATHLIB_API
ScaleVec3(VERTEX4*result,VERTEX4 *src,float s)
{
	result->x = src->x * s;
	result->y = src->y * s;
	result->z = src->z * s;
	result->w = src->w;
}
void MATHLIB_API
Vec3Lerp(VERTEX3*ret,VERTEX3* v1, VERTEX3* v2, float t)
{
	ret->x = v1->x + (v2->x - v1->x) * t;
	ret->y = v1->y + (v2->y - v1->y) * t;
	ret->z = v1->z + (v2->z - v1->z) * t;
}






// ------------------------------------------------------------------ OTHER MATH ------------------------------------------------------------------ //

int MATHLIB_API
clamp(int X, int Min, int Max) { if( X > Max ) X = Max; else if( X < Min ) X = Min; return X; }

void MATHLIB_API
ComputeNormals(VERTEX3*res,VERTEX3 *u,VERTEX3 *v,VERTEX3 *w)
{
	VERTEX3 dv;
	VERTEX3 dw;
	
		
	Vec3DEC(&dv,v, u);
	NormalizeVec3(&dv);
	
	Vec3DEC(&dw,w, u);
	NormalizeVec3(&dw);
	
	CrossVec3(res,&dv,&dw);
	
	NormalizeVec3(res);
} 
















