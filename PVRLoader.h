//
//  PVRLoader.h
//  UltraVision
//
//  Created by easy proger on 08.03.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __UltraVision__PVRLoader__
#define __UltraVision__PVRLoader__

#include <iostream>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <GL/glew.h>
#define GL_HALF_FLOAT_OES GL_FLOAT
#else
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#endif

#if (defined(__int64) || defined(_WIN32))
typedef signed __int64     PVRTint64;
typedef unsigned __int64   PVRTuint64;
#elif defined(__GNUC__)
__extension__ typedef signed long long PVRTint64;
__extension__ typedef unsigned long long PVRTuint64;
#else
typedef signed long long   PVRTint64;
typedef unsigned long long PVRTuint64;
#endif


#define PVRTEX3_HEADERSIZE 52
#define PVRT_MIN(a,b)            (((a) < (b)) ? (a) : (b))
#define PVRT_MAX(a,b)            (((a) > (b)) ? (a) : (b))
#include <assert.h>
#define _ASSERT(a) assert(a)

#define FREE(X)		{ if(X) { free(X); (X) = 0; } }
enum EPVRTError
{
	PVR_SUCCESS = 0,    /*!< Success! :D */
	PVR_FAIL = 1,       /*!< Failed :( */
	PVR_OVERFLOW = 2    /*!< Overflow error :| */
};

enum EPVRTColourSpace
{
	ePVRTCSpacelRGB,
	ePVRTCSpacesRGB,
	ePVRTCSpaceNumSpaces
};

typedef char				PVRTchar8;
typedef signed char			PVRTint8;
typedef signed short		PVRTint16;
typedef signed int			PVRTint32;
typedef unsigned char		PVRTuint8;
typedef unsigned short		PVRTuint16;
typedef unsigned int		PVRTuint32;


const PVRTint32 PVRTEX_TOPMIPLEVEL			= 0;
const PVRTint32 PVRTEX_ALLMIPLEVELS			= -1; //This is a special number used simply to return a total of all MIP levels


const PVRTuint32 PVRTEX3_IDENT			= 0x03525650;	// 'P''V''R'3
const PVRTuint32 PVRTEX3_IDENT_REV		= 0x50565203;

const PVRTuint32 PVRTEX_CURR_IDENT		= PVRTEX3_IDENT;
const PVRTuint32 PVRTEX_CURR_IDENT_REV	= PVRTEX3_IDENT_REV;

//Generate a 4 channel PixelID.
#define PVRTGENPIXELID4(C1Name, C2Name, C3Name, C4Name, C1Bits, C2Bits, C3Bits, C4Bits) ( ( (PVRTuint64)C1Name) + ( (PVRTuint64)C2Name<<8) + ( (PVRTuint64)C3Name<<16) + ( (PVRTuint64)C4Name<<24) + ( (PVRTuint64)C1Bits<<32) + ( (PVRTuint64)C2Bits<<40) + ( (PVRTuint64)C3Bits<<48) + ( (PVRTuint64)C4Bits<<56) )

//Generate a 1 channel PixelID.
#define PVRTGENPIXELID3(C1Name, C2Name, C3Name, C1Bits, C2Bits, C3Bits)( PVRTGENPIXELID4(C1Name, C2Name, C3Name, 0, C1Bits, C2Bits, C3Bits, 0) )

//Generate a 2 channel PixelID.
#define PVRTGENPIXELID2(C1Name, C2Name, C1Bits, C2Bits) ( PVRTGENPIXELID4(C1Name, C2Name, 0, 0, C1Bits, C2Bits, 0, 0) )

//Generate a 3 channel PixelID.
#define PVRTGENPIXELID1(C1Name, C1Bits) ( PVRTGENPIXELID4(C1Name, 0, 0, 0, C1Bits, 0, 0, 0))

#ifndef GL_IMG_texture_compression_pvrtc
#define GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG			0x8C00
#define GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG			0x8C01
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG			0x8C02
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG			0x8C03
#endif

#ifndef GL_IMG_texture_compression_pvrtc2
#define GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG			0x9137
#define GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG			0x9138
#endif

#ifndef GL_OES_compressed_ETC1_RGB8_texture
#define GL_ETC1_RGB8_OES                                        0x8D64
#endif

//Compressed pixel formats
enum EPVRTPixelFormat
{
	ePVRTPF_PVRTCI_2bpp_RGB,
	ePVRTPF_PVRTCI_2bpp_RGBA,
	ePVRTPF_PVRTCI_4bpp_RGB,
	ePVRTPF_PVRTCI_4bpp_RGBA,
	ePVRTPF_PVRTCII_2bpp,
	ePVRTPF_PVRTCII_4bpp,
	ePVRTPF_ETC1,
	ePVRTPF_DXT1,
	ePVRTPF_DXT2,
	ePVRTPF_DXT3,
	ePVRTPF_DXT4,
	ePVRTPF_DXT5,
    
	//These formats are identical to some DXT formats.
	ePVRTPF_BC1 = ePVRTPF_DXT1,
	ePVRTPF_BC2 = ePVRTPF_DXT3,
	ePVRTPF_BC3 = ePVRTPF_DXT5,
    
	//These are currently unsupported:
	ePVRTPF_BC4,
	ePVRTPF_BC5,
	ePVRTPF_BC6,
	ePVRTPF_BC7,
    
	//These are supported
	ePVRTPF_UYVY,
	ePVRTPF_YUY2,
	ePVRTPF_BW1bpp,
	ePVRTPF_SharedExponentR9G9B9E5,
	ePVRTPF_RGBG8888,
	ePVRTPF_GRGB8888,
	ePVRTPF_ETC2_RGB,
	ePVRTPF_ETC2_RGBA,
	ePVRTPF_ETC2_RGB_A1,
	ePVRTPF_EAC_R11,
	ePVRTPF_EAC_RG11,
    
	//Invalid value
	ePVRTPF_NumCompressedPFs
};
static const PVRTuint64 PVRTEX_PFHIGHMASK=0xffffffff00000000ull;
enum EPVRTVariableType
{
	ePVRTVarTypeUnsignedByteNorm,
	ePVRTVarTypeSignedByteNorm,
	ePVRTVarTypeUnsignedByte,
	ePVRTVarTypeSignedByte,
	ePVRTVarTypeUnsignedShortNorm,
	ePVRTVarTypeSignedShortNorm,
	ePVRTVarTypeUnsignedShort,
	ePVRTVarTypeSignedShort,
	ePVRTVarTypeUnsignedIntegerNorm,
	ePVRTVarTypeSignedIntegerNorm,
	ePVRTVarTypeUnsignedInteger,
	ePVRTVarTypeSignedInteger,
	ePVRTVarTypeSignedFloat,	ePVRTVarTypeFloat=ePVRTVarTypeSignedFloat, //the name ePVRTVarTypeFloat is now deprecated.
	ePVRTVarTypeUnsignedFloat,
	ePVRTVarTypeNumVarTypes
};

struct PVRTextureHeaderV3{
	PVRTuint32	u32Version;			///< Version of the file header, used to identify it.
	PVRTuint32	u32Flags;			///< Various format flags.
	PVRTuint64	u64PixelFormat;		///< The pixel format, 8cc value storing the 4 channel identifiers and their respective sizes.
	PVRTuint32	u32ColourSpace;		///< The Colour Space of the texture, currently either linear RGB or sRGB.
	PVRTuint32	u32ChannelType;		///< Variable type that the channel is stored in. Supports signed/unsigned int/short/byte or float for now.
	PVRTuint32	u32Height;			///< Height of the texture.
	PVRTuint32	u32Width;			///< Width of the texture.
	PVRTuint32	u32Depth;			///< Depth of the texture. (Z-slices)
	PVRTuint32	u32NumSurfaces;		///< Number of members in a Texture Array.
	PVRTuint32	u32NumFaces;		///< Number of faces in a Cube Map. Maybe be a value other than 6.
	PVRTuint32	u32MIPMapCount;		///< Number of MIP Maps in the texture - NB: Includes top level.
	PVRTuint32	u32MetaDataSize;	///< Size of the accompanying meta data.
    
	/*!***************************************************************************
     @brief      	Constructor for the header - used to make sure that the header is initialised usefully.
     The initial pixel format is an invalid one and must be set.
     *****************************************************************************/
	PVRTextureHeaderV3() :
    u32Version(PVRTEX3_IDENT),			        ///< Version of the file header.
    u32Flags(0),			                    ///< Format flags.
    u64PixelFormat(ePVRTPF_NumCompressedPFs),   ///< The pixel format.
    u32ColourSpace(0),		                    ///< The Colour Space of the texture.
    u32ChannelType(0),              		    ///< Variable type that the channel is stored in.
    u32Height(1),                           	///< Height of the texture.
    u32Width(1),    			                ///< Width of the texture.
    u32Depth(1),                		    	///< Depth of the texture. (Z-slices)
    u32NumSurfaces(1),                  		///< Number of members in a Texture Array.
    u32NumFaces(1),                        		///< Number of faces in a Cube Map. Maybe be a value other than 6.
    u32MIPMapCount(1),          		        ///< Number of MIP Maps in the texture - NB: Includes top level.
    u32MetaDataSize(0)                         	///< Size of the accompanying meta data.
	{}
};
struct PVR_Texture_Header
{
	PVRTuint32 dwHeaderSize;		/*!< size of the structure */
	PVRTuint32 dwHeight;			/*!< height of surface to be created */
	PVRTuint32 dwWidth;				/*!< width of input surface */
	PVRTuint32 dwMipMapCount;		/*!< number of mip-map levels requested */
	PVRTuint32 dwpfFlags;			/*!< pixel format flags */
	PVRTuint32 dwTextureDataSize;	/*!< Total size in bytes */
	PVRTuint32 dwBitCount;			/*!< number of bits per pixel  */
	PVRTuint32 dwRBitMask;			/*!< mask for red bit */
	PVRTuint32 dwGBitMask;			/*!< mask for green bits */
	PVRTuint32 dwBBitMask;			/*!< mask for blue bits */
	PVRTuint32 dwAlphaBitMask;		/*!< mask for alpha channel */
	PVRTuint32 dwPVR;				/*!< magic number identifying pvr file */
	PVRTuint32 dwNumSurfs;			/*!< the number of surfaces present in the pvr */
} ;

enum PVRTPixelType
{
    MGLPT_ARGB_4444 = 0x00,
    MGLPT_ARGB_1555,
    MGLPT_RGB_565,
    MGLPT_RGB_555,
    MGLPT_RGB_888,
    MGLPT_ARGB_8888,
    MGLPT_ARGB_8332,
    MGLPT_I_8,
    MGLPT_AI_88,
    MGLPT_1_BPP,
    MGLPT_VY1UY0,
    MGLPT_Y1VY0U,
    MGLPT_PVRTC2,
    MGLPT_PVRTC4,
    
    // OpenGL version of pixel types
    OGL_RGBA_4444= 0x10,
    OGL_RGBA_5551,
    OGL_RGBA_8888,
    OGL_RGB_565,
    OGL_RGB_555,
    OGL_RGB_888,
    OGL_I_8,
    OGL_AI_88,
    OGL_PVRTC2,
    OGL_PVRTC4,
    OGL_BGRA_8888,
    OGL_A_8,
    OGL_PVRTCII4,	///< Not in use
    OGL_PVRTCII2,	///< Not in use
    
    // S3TC Encoding
    D3D_DXT1 = 0x20,
    D3D_DXT2,
    D3D_DXT3,
    D3D_DXT4,
    D3D_DXT5,
    
    //RGB Formats
    D3D_RGB_332,
    D3D_AL_44,
    D3D_LVU_655,
    D3D_XLVU_8888,
    D3D_QWVU_8888,
    
    //10 bit integer - 2 bit alpha
    D3D_ABGR_2101010,
    D3D_ARGB_2101010,
    D3D_AWVU_2101010,
    
    //16 bit integers
    D3D_GR_1616,
    D3D_VU_1616,
    D3D_ABGR_16161616,
    
    //Float Formats
    D3D_R16F,
    D3D_GR_1616F,
    D3D_ABGR_16161616F,
    
    //32 bits per channel
    D3D_R32F,
    D3D_GR_3232F,
    D3D_ABGR_32323232F,
    
    // Ericsson
    ETC_RGB_4BPP,
    ETC_RGBA_EXPLICIT,				///< Unimplemented
    ETC_RGBA_INTERPOLATED,			///< Unimplemented
    
    D3D_A8 = 0x40,
    D3D_V8U8,
    D3D_L16,
    
    D3D_L8,
    D3D_AL_88,
    
    //Y'UV Colourspace
    D3D_UYVY,
    D3D_YUY2,
    
    // DX10
    DX10_R32G32B32A32_FLOAT= 0x50,
    DX10_R32G32B32A32_UINT ,
    DX10_R32G32B32A32_SINT,
    
    DX10_R32G32B32_FLOAT,
    DX10_R32G32B32_UINT,
    DX10_R32G32B32_SINT,
    
    DX10_R16G16B16A16_FLOAT ,
    DX10_R16G16B16A16_UNORM,
    DX10_R16G16B16A16_UINT ,
    DX10_R16G16B16A16_SNORM ,
    DX10_R16G16B16A16_SINT ,
    
    DX10_R32G32_FLOAT ,
    DX10_R32G32_UINT ,
    DX10_R32G32_SINT ,
    
    DX10_R10G10B10A2_UNORM ,
    DX10_R10G10B10A2_UINT ,
    
    DX10_R11G11B10_FLOAT ,				///< Unimplemented
    
    DX10_R8G8B8A8_UNORM ,
    DX10_R8G8B8A8_UNORM_SRGB ,
    DX10_R8G8B8A8_UINT ,
    DX10_R8G8B8A8_SNORM ,
    DX10_R8G8B8A8_SINT ,
    
    DX10_R16G16_FLOAT ,
    DX10_R16G16_UNORM ,
    DX10_R16G16_UINT ,
    DX10_R16G16_SNORM ,
    DX10_R16G16_SINT ,
    
    DX10_R32_FLOAT ,
    DX10_R32_UINT ,
    DX10_R32_SINT ,
    
    DX10_R8G8_UNORM ,
    DX10_R8G8_UINT ,
    DX10_R8G8_SNORM ,
    DX10_R8G8_SINT ,
    
    DX10_R16_FLOAT ,
    DX10_R16_UNORM ,
    DX10_R16_UINT ,
    DX10_R16_SNORM ,
    DX10_R16_SINT ,
    
    DX10_R8_UNORM,
    DX10_R8_UINT,
    DX10_R8_SNORM,
    DX10_R8_SINT,
    
    DX10_A8_UNORM,
    DX10_R1_UNORM,
    DX10_R9G9B9E5_SHAREDEXP,	///< Unimplemented
    DX10_R8G8_B8G8_UNORM,		///< Unimplemented
    DX10_G8R8_G8B8_UNORM,		///< Unimplemented
    
    DX10_BC1_UNORM,
    DX10_BC1_UNORM_SRGB,
    
    DX10_BC2_UNORM,
    DX10_BC2_UNORM_SRGB,
    
    DX10_BC3_UNORM,
    DX10_BC3_UNORM_SRGB,
    
    DX10_BC4_UNORM,				///< Unimplemented
    DX10_BC4_SNORM,				///< Unimplemented
    
    DX10_BC5_UNORM,				///< Unimplemented
    DX10_BC5_SNORM,				///< Unimplemented
    
    // OpenVG
    
    /* RGB{A,X} channel ordering */
    ePT_VG_sRGBX_8888  = 0x90,
    ePT_VG_sRGBA_8888,
    ePT_VG_sRGBA_8888_PRE,
    ePT_VG_sRGB_565,
    ePT_VG_sRGBA_5551,
    ePT_VG_sRGBA_4444,
    ePT_VG_sL_8,
    ePT_VG_lRGBX_8888,
    ePT_VG_lRGBA_8888,
    ePT_VG_lRGBA_8888_PRE,
    ePT_VG_lL_8,
    ePT_VG_A_8,
    ePT_VG_BW_1,
    
    /* {A,X}RGB channel ordering */
    ePT_VG_sXRGB_8888,
    ePT_VG_sARGB_8888,
    ePT_VG_sARGB_8888_PRE,
    ePT_VG_sARGB_1555,
    ePT_VG_sARGB_4444,
    ePT_VG_lXRGB_8888,
    ePT_VG_lARGB_8888,
    ePT_VG_lARGB_8888_PRE,
    
    /* BGR{A,X} channel ordering */
    ePT_VG_sBGRX_8888,
    ePT_VG_sBGRA_8888,
    ePT_VG_sBGRA_8888_PRE,
    ePT_VG_sBGR_565,
    ePT_VG_sBGRA_5551,
    ePT_VG_sBGRA_4444,
    ePT_VG_lBGRX_8888,
    ePT_VG_lBGRA_8888,
    ePT_VG_lBGRA_8888_PRE,
    
    /* {A,X}BGR channel ordering */
    ePT_VG_sXBGR_8888,
    ePT_VG_sABGR_8888 ,
    ePT_VG_sABGR_8888_PRE,
    ePT_VG_sABGR_1555,
    ePT_VG_sABGR_4444,
    ePT_VG_lXBGR_8888,
    ePT_VG_lABGR_8888,
    ePT_VG_lABGR_8888_PRE,
    
    // max cap for iterating
    END_OF_PIXEL_TYPES,
    
    MGLPT_NOTYPE = 0xffffffff
    
};

int PVRTDecompressPVRTC(const void *pCompressedData,
				const int Do2bitMode,
				const int XDim,
				const int YDim,
				unsigned char* pResultImage);

EPVRTError PVRTTextureLoadFromPVR(	const void*DataPtr,
                                  GLuint * const texName,
                                  const void *psTextureHeader=NULL,
                                  bool bAllowDecompress = true,
                                  const unsigned int nLoadFromLevel=0);

#endif /* defined(__UltraVision__PVRLoader__) */
