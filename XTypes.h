//
//  XTypes.h
//  XTech
//
//  Created by easy proger on 09.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef XTypes_h
#define XTypes_h


#if defined(__ARM_NEON__)
#include <arm_neon.h>
#endif


#define TARGET_iOS 1

#define WIDTH_SHADOW_MAP 1024
#define HEIGHT_SHADOW_MAP 1024

#define WIDTH_VIEWPORT 800
#define HEIGHT_VIEWPORT 600


#define PRINT_COMPRESSED_TEXTURE_FORMATS 0
#define X_DEBUG 1
#define X_DEBUG_SHADERS 1


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    #define GL_DEPTH_COMPONENT24_OES GL_DEPTH_COMPONENT24 
    #define GL_DEPTH24_STENCIL8_OES GL_DEPTH24_STENCIL8 

#else
#if TARGET_iOS
    #define GL_DEPTH_COMPONENT24 GL_DEPTH_COMPONENT24_OES
    #define GL_DEPTH24_STENCIL8 GL_DEPTH24_STENCIL8_OES
#endif
#endif




#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <GL/glew.h>
#else
#include <OpenGLES/ES2/gl.h>
#endif



#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define AGRESIVE_INLINE static 
#define X_INLINE_X  inline
#else
#define AGRESIVE_INLINE inline __attribute__((always_inline))
#define X_INLINE_X  inline
#endif





#ifndef X_REGCALL
#ifdef __INTEL_COMPILER
#define X_REGCALL __regcall
#else
#define X_REGCALL __fastcall
#endif
#endif

#define X_ALIGN16 __attribute__((aligned(16)))


typedef unsigned long DWORD;


#define DW_AS_FLT(DW) (*(FLOAT*)&(DW))
#define FLT_AS_DW(F) (*(DWORD*)&(F))
#define FLT_SIGN(F) ((FLT_AS_DW(F) & 0x80000000L))
#define ALMOST_ZERO(F) ((FLT_AS_DW(F) & 0x7f800000L)==0)


AGRESIVE_INLINE  
const char * xOpenGLStrError(GLenum code)
{
    switch(code)
    {
        case GL_NO_ERROR:
            return "No error";
            break;
        case GL_INVALID_ENUM:
            return "Invalid enum";
            break;
        case GL_INVALID_VALUE:
            return "Invalid value";
            break;
        case GL_INVALID_OPERATION:
            return "Invalid operation";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "invalid frame buffer";
            break;
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
            break;
    }
    return "Unknown error";
}


#define GET_GLERROR()                                                                                 \
{                                                                                                     \
    GLenum code = glGetError();                                                                       \
    while (code!=GL_NO_ERROR) {                                                                       \
        fprintf(stderr, "%s [line %d]  GL Error: %s\n",__FUNCTION__,__LINE__,xOpenGLStrError(code));  \
        code = glGetError();                                                                          \
    }                                                                                                 \
}                                                                                                     \




typedef int facesType;






#endif


