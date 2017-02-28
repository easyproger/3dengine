
#ifndef XMatrix3Math_h
#define XMatrix3Math_h

#include <math.h>
#include "XTypes.h"
#include "XMathTypes.h"


AGRESIVE_INLINE XMatrix3 XMatrix3Transpose(XMatrix3* matrix);
AGRESIVE_INLINE XMatrix3 XMatrix3Invert(XMatrix3 *matrix, bool *isInvertible);
AGRESIVE_INLINE XMatrix3 XMatrix3InvertAndTranspose(XMatrix3* matrix, bool *isInvertible);
AGRESIVE_INLINE void XMatrix3MakeWithArray(XMatrix3*result,float values[9]);
AGRESIVE_INLINE XMatrix3 XMatrix3MakeWithArray(float values[9]);

AGRESIVE_INLINE XMatrix3 XMatrix3MakeWithArray(float values[9])
{
    XMatrix3 m = { values[0], values[1], values[2],
                     values[3], values[4], values[5],
                     values[6], values[7], values[8] };
    return m;
}


AGRESIVE_INLINE void XMatrix3MakeWithArray(XMatrix3*result,float values[9])
{
	for (int i = 0; i < 9; i++) {
        result->m[i] = values[i];
    }
}


AGRESIVE_INLINE XMatrix3 XMatrix3Transpose(XMatrix3* matrix)
{
    XMatrix3 m = { matrix->m[0], matrix->m[3], matrix->m[6],
                     matrix->m[1], matrix->m[4], matrix->m[7],
                     matrix->m[2], matrix->m[5], matrix->m[8] };
    return m;
}

AGRESIVE_INLINE void XMatrix3Scale(XMatrix3* matrix, float sx, float sy, float sz)
{
	matrix->m[0]*=sx; matrix->m[1]*=sx; matrix->m[2]*=sx;
    matrix->m[3]*=sy; matrix->m[4]*=sy; matrix->m[5]*=sy;
    matrix->m[6]*=sz; matrix->m[7]*=sz; matrix->m[8]*=sz;
}

AGRESIVE_INLINE XMatrix3 XMatrix3Invert(XMatrix3 *matrix, bool *isInvertible) {
    float determinant = (matrix->m00 * (matrix->m11 * matrix->m22 - matrix->m12 * matrix->m21)) + (matrix->m01 * (matrix->m12 * matrix->m20 - matrix->m22 * matrix->m10)) + (matrix->m02 * (matrix->m10 * matrix->m21 - matrix->m11 *matrix->m20));
    bool canInvert = determinant != 0.0f;
    if (isInvertible) {
        *isInvertible = canInvert;
    }
    
    if (!canInvert) {
		XMatrix3 ident = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};
        return ident;
    }
	XMatrix3 returnMatrix = XMatrix3Transpose(matrix);
    XMatrix3Scale(&returnMatrix, determinant, determinant, determinant);
    return returnMatrix;
}

AGRESIVE_INLINE XMatrix3 XMatrix3InvertAndTranspose(XMatrix3* matrix, bool *isInvertible) {
    XMatrix3 inverted = XMatrix3Invert(matrix, isInvertible);
    return XMatrix3Transpose(&inverted);
}

#endif