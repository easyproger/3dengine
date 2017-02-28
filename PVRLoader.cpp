//
//  PVRLoader.cpp
//  UltraVision
//
//  Created by easy proger on 08.03.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "PVRLoader.h"
static const void PVRTGetOGLES2TextureFormat(const PVRTextureHeaderV3& sTextureHeader, PVRTuint32& internalformat, PVRTuint32& format, PVRTuint32& type)
{
	PVRTuint64 PixelFormat = sTextureHeader.u64PixelFormat;
	EPVRTVariableType ChannelType = (EPVRTVariableType)sTextureHeader.u32ChannelType;
	
	//Initialisation. Any invalid formats will return 0 always.
	format = 0;
	type = 0;
	internalformat=0;
    
	//Get the last 32 bits of the pixel format.
	PVRTuint64 PixelFormatPartHigh = PixelFormat&PVRTEX_PFHIGHMASK;
    
	//Check for a compressed format (The first 8 bytes will be 0, so the whole thing will be equal to the last 32 bits).
	if (PixelFormatPartHigh==0)
	{
		//Format and type == 0 for compressed textures.
		switch (PixelFormat)
		{
            case ePVRTPF_PVRTCI_2bpp_RGB:
			{
				internalformat=GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
				return;
			}
            case ePVRTPF_PVRTCI_2bpp_RGBA:
			{
				internalformat=GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
				return;
			}
            case ePVRTPF_PVRTCI_4bpp_RGB:
			{
				internalformat=GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
				return;
			}
            case ePVRTPF_PVRTCI_4bpp_RGBA:
			{
				internalformat=GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
				return;
			}
#ifndef TARGET_OS_IPHONE
            case ePVRTPF_PVRTCII_2bpp:
			{
				internalformat=GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG;
				return;
			}
            case ePVRTPF_PVRTCII_4bpp:
			{
				internalformat=GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG;
				return;
			}
            case ePVRTPF_ETC1:
			{
				internalformat=GL_ETC1_RGB8_OES;
				return;
			}
#endif
            default:
                return;
		}
	}
	else
	{
		switch (ChannelType)
		{
            case ePVRTVarTypeFloat:
			{
				switch (PixelFormat)
				{
                        //HALF_FLOAT_OES
                    case PVRTGENPIXELID4('r','g','b','a',16,16,16,16):
					{
						type=GL_HALF_FLOAT_OES;
						format = GL_RGBA;
						internalformat=GL_RGBA;
						return;
					}
                    case PVRTGENPIXELID3('r','g','b',16,16,16):
					{
						type=GL_HALF_FLOAT_OES;
						format = GL_RGB;
						internalformat=GL_RGB;
						return;
					}
                    case PVRTGENPIXELID2('l','a',16,16):
					{
						type=GL_HALF_FLOAT_OES;
						format = GL_LUMINANCE_ALPHA;
						internalformat=GL_LUMINANCE_ALPHA;
						return;
					}
                    case PVRTGENPIXELID1('l',16):
					{
						type=GL_HALF_FLOAT_OES;
						format = GL_LUMINANCE;
						internalformat=GL_LUMINANCE;
						return;
					}
                    case PVRTGENPIXELID1('a',16):
					{
						type=GL_HALF_FLOAT_OES;
						format = GL_ALPHA;
						internalformat=GL_ALPHA;
						return;
					}
                        //FLOAT (OES)
                    case PVRTGENPIXELID4('r','g','b','a',32,32,32,32):
					{
						type=GL_FLOAT;
						format = GL_RGBA;
						internalformat=GL_RGBA;
						return;
					}
                    case PVRTGENPIXELID3('r','g','b',32,32,32):
					{
						type=GL_FLOAT;
						format = GL_RGB;
						internalformat=GL_RGB;
						return;
					}
                    case PVRTGENPIXELID2('l','a',32,32):
					{
						type=GL_FLOAT;
						format = GL_LUMINANCE_ALPHA;
						internalformat=GL_LUMINANCE_ALPHA;
						return;
					}
                    case PVRTGENPIXELID1('l',32):
					{
						type=GL_FLOAT;
						format = GL_LUMINANCE;
						internalformat=GL_LUMINANCE;
						return;
					}
                    case PVRTGENPIXELID1('a',32):
					{
						type=GL_FLOAT;
						format = GL_ALPHA;
						internalformat=GL_ALPHA;
						return;
					}
				}
				break;
			}
            case ePVRTVarTypeUnsignedByteNorm:
			{
				type = GL_UNSIGNED_BYTE;
				switch (PixelFormat)
				{
                    case PVRTGENPIXELID4('r','g','b','a',8,8,8,8):
					{
						format = internalformat = GL_RGBA;
						return;
					}
                    case PVRTGENPIXELID3('r','g','b',8,8,8):
					{
						format = internalformat = GL_RGB;
						return;
					}
                    case PVRTGENPIXELID2('l','a',8,8):
					{
						format = internalformat = GL_LUMINANCE_ALPHA;
						return;
					}
                    case PVRTGENPIXELID1('l',8):
					{
						format = internalformat = GL_LUMINANCE;
						return;
					}
                    case PVRTGENPIXELID1('a',8):
					{
						format = internalformat = GL_ALPHA;
						return;
					}
                    case PVRTGENPIXELID4('b','g','r','a',8,8,8,8):
					{
						format = internalformat = GL_BGRA;
						return;
					}
				}
				break;
			}
            case ePVRTVarTypeUnsignedShortNorm:
			{
				switch (PixelFormat)
				{
                    case PVRTGENPIXELID4('r','g','b','a',4,4,4,4):
					{
						type = GL_UNSIGNED_SHORT_4_4_4_4;
						format = internalformat = GL_RGBA;
						return;
					}
                    case PVRTGENPIXELID4('r','g','b','a',5,5,5,1):
					{
						type = GL_UNSIGNED_SHORT_5_5_5_1;
						format = internalformat = GL_RGBA;
						return;
					}
                    case PVRTGENPIXELID3('r','g','b',5,6,5):
					{
						type = GL_UNSIGNED_SHORT_5_6_5;
						format = internalformat = GL_RGB;
						return;
					}
				}
				break;
			}
            default:
                return;
		}
	}
}



void PVRTGetFormatMinDims(PVRTuint64 u64PixelFormat, PVRTuint32 &minX, PVRTuint32 &minY, PVRTuint32 &minZ)
{
	switch(u64PixelFormat)
	{
        case ePVRTPF_DXT1:
        case ePVRTPF_DXT2:
        case ePVRTPF_DXT3:
        case ePVRTPF_DXT4:
        case ePVRTPF_DXT5:
        case ePVRTPF_BC4:
        case ePVRTPF_BC5:
        case ePVRTPF_ETC1:
        case ePVRTPF_ETC2_RGB:
        case ePVRTPF_ETC2_RGBA:
        case ePVRTPF_ETC2_RGB_A1:
        case ePVRTPF_EAC_R11:
        case ePVRTPF_EAC_RG11:
            minX = 4;
            minY = 4;
            minZ = 1;
            break;
        case ePVRTPF_PVRTCI_4bpp_RGB:
        case ePVRTPF_PVRTCI_4bpp_RGBA:
            minX = 8;
            minY = 8;
            minZ = 1;
            break;
        case ePVRTPF_PVRTCI_2bpp_RGB:
        case ePVRTPF_PVRTCI_2bpp_RGBA:
            minX = 16;
            minY = 8;
            minZ = 1;
            break;
        case ePVRTPF_PVRTCII_4bpp:
            minX = 4;
            minY = 4;
            minZ = 1;
            break;
        case ePVRTPF_PVRTCII_2bpp:
            minX = 8;
            minY = 4;
            minZ = 1;
            break;
        case ePVRTPF_UYVY:
        case ePVRTPF_YUY2:
        case ePVRTPF_RGBG8888:
        case ePVRTPF_GRGB8888:
            minX = 2;
            minY = 1;
            minZ = 1;
            break;
        case ePVRTPF_BW1bpp:
            minX = 8;
            minY = 1;
            minZ = 1;
            break;
        default: //Non-compressed formats all return 1.
            minX = 1;
            minY = 1;
            minZ = 1;
            break;
	}
}
PVRTuint32 PVRTGetBitsPerPixel(PVRTuint64 u64PixelFormat)
{
	if((u64PixelFormat&PVRTEX_PFHIGHMASK)!=0)
	{
		PVRTuint8* PixelFormatChar=(PVRTuint8*)&u64PixelFormat;
		return PixelFormatChar[4]+PixelFormatChar[5]+PixelFormatChar[6]+PixelFormatChar[7];
	}
	else
	{
		switch (u64PixelFormat)
		{
            case ePVRTPF_BW1bpp:
                return 1;
            case ePVRTPF_PVRTCI_2bpp_RGB:
            case ePVRTPF_PVRTCI_2bpp_RGBA:
            case ePVRTPF_PVRTCII_2bpp:
                return 2;
            case ePVRTPF_PVRTCI_4bpp_RGB:
            case ePVRTPF_PVRTCI_4bpp_RGBA:
            case ePVRTPF_PVRTCII_4bpp:
            case ePVRTPF_ETC1:
            case ePVRTPF_EAC_R11:
            case ePVRTPF_ETC2_RGB:
            case ePVRTPF_ETC2_RGB_A1:
            case ePVRTPF_DXT1:
            case ePVRTPF_BC4:
                return 4;
            case ePVRTPF_DXT2:
            case ePVRTPF_DXT3:
            case ePVRTPF_DXT4:
            case ePVRTPF_DXT5:
            case ePVRTPF_BC5:
            case ePVRTPF_EAC_RG11:
            case ePVRTPF_ETC2_RGBA:
                return 8;
            case ePVRTPF_YUY2:
            case ePVRTPF_UYVY:
            case ePVRTPF_RGBG8888:
            case ePVRTPF_GRGB8888:
                return 16;
            case ePVRTPF_SharedExponentR9G9B9E5:
                return 32;
            case ePVRTPF_NumCompressedPFs:
                return 0;
		}
	}
	return 0;
}

PVRTextureHeaderV3 *PVRTTextureCreate(
                                      const unsigned int	w,
                                      const unsigned int	h,
                                      const unsigned int	wMin,
                                      const unsigned int	hMin,
                                      const unsigned int	nBPP,
                                      const bool			bMIPMap)
{
	size_t			len;
	unsigned char	*p;
    
	{
		unsigned int	wTmp = w, hTmp = h;
        
		len = 0;
		do
		{
			len += PVRT_MAX(wTmp, wMin) * PVRT_MAX(hTmp, hMin);
			wTmp >>= 1;
			hTmp >>= 1;
		}
		while(bMIPMap && (wTmp || hTmp));
	}
    
	len = (len * nBPP) / 8;
	len += PVRTEX3_HEADERSIZE;
    
	p = (unsigned char*)malloc(len);
	_ASSERT(p);
    
	if(p)
	{
		PVRTextureHeaderV3 * const psTexHeader = (PVRTextureHeaderV3*)p;
        
		*psTexHeader=PVRTextureHeaderV3();
        
		psTexHeader->u32Width=w;
		psTexHeader->u32Height=h;
        
		return psTexHeader;
	}
	else
	{
		return 0;
	}
}
void PVRTTextureTwiddle(unsigned int &a, const unsigned int u, const unsigned int v)
{
	_ASSERT(!((u|v) & 0xFFFF0000));
	a = 0;
	for(int i = 0; i < 16; ++i)
	{
		a |= ((u & (1 << i)) << (i+1));
		a |= ((v & (1 << i)) << (i+0));
	}
}
void PVRTTextureDeTwiddle(unsigned int &u, unsigned int &v, const unsigned int a)
{
	u = 0;
	v = 0;
	for(int i = 0; i < 16; ++i)
	{
		u |= (a & (1 << ((2*i)+1))) >> (i+1);
		v |= (a & (1 << ((2*i)+0))) >> (i+0);
	}
}
void PVRTTextureLoadTiled(
                          PVRTuint8		* const pDst,
                          const unsigned int	nWidthDst,
                          const unsigned int	nHeightDst,
                          const PVRTuint8	* const pSrc,
                          const unsigned int	nWidthSrc,
                          const unsigned int	nHeightSrc,
                          const unsigned int	nElementSize,
                          const bool			bTwiddled)
{
	unsigned int nXs, nYs;
	unsigned int nXd, nYd;
	unsigned int nIdxSrc, nIdxDst;
    
	for(nIdxDst = 0; nIdxDst < nWidthDst*nHeightDst; ++nIdxDst)
	{
		if(bTwiddled)
		{
			PVRTTextureDeTwiddle(nXd, nYd, nIdxDst);
		}
		else
		{
			nXd = nIdxDst % nWidthDst;
			nYd = nIdxDst / nWidthDst;
		}
        
		nXs = nXd % nWidthSrc;
		nYs = nYd % nHeightSrc;
        
		if(bTwiddled)
		{
			PVRTTextureTwiddle(nIdxSrc, nXs, nYs);
		}
		else
		{
			nIdxSrc = nYs * nWidthSrc + nXs;
		}
        
		memcpy(pDst + nIdxDst*nElementSize, pSrc + nIdxSrc*nElementSize, nElementSize);
	}
}
/*!***************************************************************************
 @Function		PVRTTextureTile
 @Modified		pOut		The tiled texture in system memory
 @Input			pIn			The source texture
 @Input			nRepeatCnt	Number of times to repeat the source texture
 @Description	Allocates and fills, in system memory, a texture large enough
 to repeat the source texture specified number of times.
 *****************************************************************************/
void PVRTTextureTile(
                     PVRTextureHeaderV3			**pOut,
                     const PVRTextureHeaderV3	* const pIn,
                     const int					nRepeatCnt)
{
	unsigned int		nFormat = 0, nType = 0, nBPP, nSize, nElW = 0, nElH = 0, nElD = 0;
	PVRTuint8		*pMmSrc, *pMmDst;
	unsigned int		nLevel;
	PVRTextureHeaderV3	*psTexHeaderNew;
    
	_ASSERT(pIn->u32Width);
	_ASSERT(pIn->u32Width == pIn->u32Height);
	_ASSERT(nRepeatCnt > 1);
    
	PVRTGetOGLES2TextureFormat(*pIn,nFormat,nFormat,nType);
	PVRTGetFormatMinDims(pIn->u64PixelFormat,nElW,nElH,nElD);
	
	nBPP = PVRTGetBitsPerPixel(pIn->u64PixelFormat);
	nSize = pIn->u32Width * nRepeatCnt;
    
	psTexHeaderNew	= PVRTTextureCreate(nSize, nSize, nElW, nElH, nBPP, true);
	*psTexHeaderNew	= *pIn;
	pMmDst	= (PVRTuint8*)psTexHeaderNew + sizeof(*psTexHeaderNew);
	pMmSrc	= (PVRTuint8*)pIn + sizeof(*pIn);
    
	for(nLevel = 0; ((unsigned int)1 << nLevel) < nSize; ++nLevel)
	{
		int nBlocksDstW = PVRT_MAX((unsigned int)1, (nSize >> nLevel) / nElW);
		int nBlocksDstH = PVRT_MAX((unsigned int)1, (nSize >> nLevel) / nElH);
		int nBlocksSrcW = PVRT_MAX((unsigned int)1, (pIn->u32Width >> nLevel) / nElW);
		int nBlocksSrcH = PVRT_MAX((unsigned int)1, (pIn->u32Height >> nLevel) / nElH);
		int nBlocksS	= nBPP * nElW * nElH / 8;
        
		PVRTTextureLoadTiled(
                             pMmDst,
                             nBlocksDstW,
                             nBlocksDstH,
                             pMmSrc,
                             nBlocksSrcW,
                             nBlocksSrcH,
                             nBlocksS,
                             (/*pIn->u64PixelFormat>=ePVRTPF_PVRTCI_2bpp_RGB &&*/ pIn->u64PixelFormat<=ePVRTPF_PVRTCI_4bpp_RGBA) ? true : false);
        
		pMmDst += nBlocksDstW * nBlocksDstH * nBlocksS;
		pMmSrc += nBlocksSrcW * nBlocksSrcH * nBlocksS;
	}
    
	psTexHeaderNew->u32Width = nSize;
	psTexHeaderNew->u32Height = nSize;
	psTexHeaderNew->u32MIPMapCount = nLevel+1;
	*pOut = psTexHeaderNew;
}


PVRTuint32 PVRTGetTextureDataSize(PVRTextureHeaderV3 sTextureHeader, PVRTint32 iMipLevel, bool bAllSurfaces, bool bAllFaces)
{
	//The smallest divisible sizes for a pixel format
	PVRTuint32 uiSmallestWidth=1;
	PVRTuint32 uiSmallestHeight=1;
	PVRTuint32 uiSmallestDepth=1;
    
	PVRTuint64 PixelFormatPartHigh = sTextureHeader.u64PixelFormat&PVRTEX_PFHIGHMASK;
	
	//If the pixel format is compressed, get the pixel format's minimum dimensions.
	if (PixelFormatPartHigh==0)
	{
		PVRTGetFormatMinDims((EPVRTPixelFormat)sTextureHeader.u64PixelFormat, uiSmallestWidth, uiSmallestHeight, uiSmallestDepth);
	}
    
	//Needs to be 64-bit integer to support 16kx16k and higher sizes.
	PVRTuint64 uiDataSize = 0;
	if (iMipLevel==-1)
	{
		for (PVRTuint8 uiCurrentMIP = 0; uiCurrentMIP<sTextureHeader.u32MIPMapCount; ++uiCurrentMIP)
		{
			//Get the dimensions of the current MIP Map level.
			PVRTuint32 uiWidth = PVRT_MAX(1,sTextureHeader.u32Width>>uiCurrentMIP);
			PVRTuint32 uiHeight = PVRT_MAX(1,sTextureHeader.u32Height>>uiCurrentMIP);
			PVRTuint32 uiDepth = PVRT_MAX(1,sTextureHeader.u32Depth>>uiCurrentMIP);
            
			//If pixel format is compressed, the dimensions need to be padded.
			if (PixelFormatPartHigh==0)
			{
				uiWidth=uiWidth+( (-1*uiWidth)%uiSmallestWidth);
				uiHeight=uiHeight+( (-1*uiHeight)%uiSmallestHeight);
				uiDepth=uiDepth+( (-1*uiDepth)%uiSmallestDepth);
			}
            
			//Add the current MIP Map's data size to the total.
			uiDataSize+=(PVRTuint64)PVRTGetBitsPerPixel(sTextureHeader.u64PixelFormat)*(PVRTuint64)uiWidth*(PVRTuint64)uiHeight*(PVRTuint64)uiDepth;
		}
	}
	else
	{
		//Get the dimensions of the specified MIP Map level.
		PVRTuint32 uiWidth = PVRT_MAX(1,sTextureHeader.u32Width>>iMipLevel);
		PVRTuint32 uiHeight = PVRT_MAX(1,sTextureHeader.u32Height>>iMipLevel);
		PVRTuint32 uiDepth = PVRT_MAX(1,sTextureHeader.u32Depth>>iMipLevel);
        
		//If pixel format is compressed, the dimensions need to be padded.
		if (PixelFormatPartHigh==0)
		{
			uiWidth=uiWidth+( (-1*uiWidth)%uiSmallestWidth);
			uiHeight=uiHeight+( (-1*uiHeight)%uiSmallestHeight);
			uiDepth=uiDepth+( (-1*uiDepth)%uiSmallestDepth);
		}
        
		//Work out the specified MIP Map's data size
		uiDataSize=PVRTGetBitsPerPixel(sTextureHeader.u64PixelFormat)*uiWidth*uiHeight*uiDepth;
	}
	
	//The number of faces/surfaces to register the size of.
	PVRTuint32 numfaces = ((bAllFaces)?(sTextureHeader.u32NumFaces):(1));
	PVRTuint32 numsurfs = ((bAllSurfaces)?(sTextureHeader.u32NumSurfaces):(1));
    
	//Multiply the data size by number of faces and surfaces specified, and return.
	return (PVRTuint32)(uiDataSize/8)*numsurfs*numfaces;
}


#include "XGlobals.h"


/*!***************************************************************************
 @Function		PVRTTextureLoadFromPointer
 @Input			pointer				Pointer to header-texture's structure
 @Modified		texName				the OpenGL ES texture name as returned by glBindTexture
 @Modified		psTextureHeader		Pointer to a PVRTextureHeaderV3 struct. Modified to
 contain the header data of the returned texture Ignored if NULL.
 @Input			bAllowDecompress	Allow decompression if PVRTC is not supported in hardware.
 @Input			nLoadFromLevel		Which mip map level to start loading from (0=all)
 @Input			texPtr				If null, texture follows header, else texture is here.
 @Modified		pMetaData			If a valid map is supplied, this will return any and all
 MetaDataBlocks stored in the texture, organised by DevFourCC
 then identifier. Supplying NULL will ignore all MetaData.
 @Return		PVR_SUCCESS on success
 @Description	Allows textures to be stored in C header files and loaded in. Can load parts of a
 mip mapped texture (i.e. skipping the highest detailed levels). In OpenGL Cube Map, each
 texture's up direction is defined as next (view direction, up direction),
 (+x,-y)(-x,-y)(+y,+z)(-y,-z)(+z,-y)(-z,-y).
 Sets the texture MIN/MAG filter to GL_LINEAR_MIPMAP_NEAREST/GL_LINEAR
 if mip maps are present, GL_LINEAR/GL_LINEAR otherwise.
 *****************************************************************************/
EPVRTError PVRTTextureLoadFromPointer(	const void* pointer,
                                      GLuint *const texName,
                                      const void *psTextureHeader,
                                      bool bAllowDecompress,
                                      const unsigned int nLoadFromLevel,
                                      const void * const texPtr)
{
	//Compression bools
	bool bIsCompressedFormatSupported=false;
	bool bIsCompressedFormat=false;
	bool bIsLegacyPVR=false;
    
	//Texture setup
	PVRTextureHeaderV3 sTextureHeader;
	PVRTuint8* pTextureData=NULL;
    
	//Just in case header and pointer for decompression.
	PVRTextureHeaderV3 sTextureHeaderDecomp;
	void* pDecompressedData=NULL;
    
	//Check if it's an old header format
	if((*(PVRTuint32*)pointer)!=PVRTEX3_IDENT)
	{
		return PVR_FAIL;
	}
	else
	{
		//Get the header from the main pointer.
		sTextureHeader=*(PVRTextureHeaderV3*)pointer;
        
		//Get the texture data.
		pTextureData = texPtr? (PVRTuint8*)texPtr:(PVRTuint8*)pointer+PVRTEX3_HEADERSIZE+sTextureHeader.u32MetaDataSize;
        
		
	}
    
	//Return the PVRTextureHeader.
	if (psTextureHeader)
	{
		*(PVRTextureHeaderV3*)psTextureHeader=sTextureHeader;
	}
	
	//Setup GL Texture format values.
	GLenum eTextureFormat = 0;
	GLenum eTextureInternalFormat = 0;	// often this is the same as textureFormat, but not for BGRA8888 on iOS, for instance
	GLenum eTextureType = 0;
    
	//Get the OGLES format values.
	PVRTGetOGLES2TextureFormat(sTextureHeader,eTextureInternalFormat,eTextureFormat,eTextureType);
    
	//Check supported texture formats.

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	bool bIsPVRTCSupported = false;
	bool bIsPVRTC2Supported = false;

	bool bIsBGRA8888Supported = true;

	bool bIsFloat16Supported = false;
	bool bIsFloat32Supported = true;
	bool bIsETCSupported = true;
#else
	bool bIsPVRTCSupported = IsGLExtensionSupported("GL_IMG_texture_compression_pvrtc");
	bool bIsPVRTC2Supported = IsGLExtensionSupported("GL_IMG_texture_compression_pvrtc2");
#ifndef TARGET_OS_IPHONE
	bool bIsBGRA8888Supported  = IsGLExtensionSupported("GL_IMG_texture_format_BGRA8888");
#else
	bool bIsBGRA8888Supported  = IsGLExtensionSupported("GL_APPLE_texture_format_BGRA8888");
#endif
	bool bIsFloat16Supported = IsGLExtensionSupported("GL_OES_texture_half_float");
	bool bIsFloat32Supported = IsGLExtensionSupported("GL_OES_texture_float");
#ifndef TARGET_OS_IPHONE
	bool bIsETCSupported = IsGLExtensionSupported("GL_OES_compressed_ETC1_RGB8_texture");
#endif
#endif

	




    
	//Check for compressed formats
	if (eTextureFormat==0 && eTextureType==0 && eTextureInternalFormat!=0)
	{
		if (eTextureInternalFormat>=GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG && eTextureInternalFormat<=GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG)
		{
			//Check for PVRTCI support.
			if(bIsPVRTCSupported)
			{
				bIsCompressedFormatSupported = bIsCompressedFormat = true;
			}
			else
			{



				if(bAllowDecompress)
				{

					//Output a warning.
					printf("PVRTTextureLoadFromPointer warning: PVRTC not supported. Converting to RGBA8888 instead.\n");

					//Modify boolean values.
					bIsCompressedFormatSupported = false;
					bIsCompressedFormat = true;

					//Check if it's 2bpp.
					bool bIs2bppPVRTC = (eTextureInternalFormat==GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG || eTextureInternalFormat==GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG);

					//Change texture format.
					eTextureFormat = eTextureInternalFormat = GL_RGBA;
					eTextureType = GL_UNSIGNED_BYTE;

					//Create a near-identical texture header for the decompressed header.
					sTextureHeaderDecomp = sTextureHeader;
					sTextureHeaderDecomp.u32ChannelType=ePVRTVarTypeUnsignedByteNorm;
					sTextureHeaderDecomp.u32ColourSpace=ePVRTCSpacelRGB;
					sTextureHeaderDecomp.u64PixelFormat=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);

					//Allocate enough memory for the decompressed data. OGLES2, so only decompress one surface, but all faces.
					pDecompressedData = malloc(PVRTGetTextureDataSize(sTextureHeaderDecomp, PVRTEX_ALLMIPLEVELS, false, true) );

					//Check the malloc.
					if (!pDecompressedData)
					{
						printf("PVRTTextureLoadFromPointer error: Unable to allocate memory to decompress texture.\n");
						return PVR_FAIL;
					}

					//Get the dimensions for the current MIP level.
					PVRTuint32 uiMIPWidth = sTextureHeaderDecomp.u32Width>>nLoadFromLevel;
					PVRTuint32 uiMIPHeight = sTextureHeaderDecomp.u32Height>>nLoadFromLevel;

					//Setup temporary variables.
					PVRTuint8* pTempDecompData = (PVRTuint8*)pDecompressedData;
					PVRTuint8* pTempCompData = (PVRTuint8*)pTextureData;

					if (bIsLegacyPVR)
					{
						//Decompress all the MIP levels.
						for (PVRTuint32 uiFace=0;uiFace<sTextureHeader.u32NumFaces;++uiFace)
						{

							for (PVRTuint32 uiMIPMap=nLoadFromLevel;uiMIPMap<sTextureHeader.u32MIPMapCount;++uiMIPMap)
							{
								//Get the face offset. Varies per MIP level.
								PVRTuint32 decompressedFaceOffset = PVRTGetTextureDataSize(sTextureHeaderDecomp, uiMIPMap, false, false);
								PVRTuint32 compressedFaceOffset = PVRTGetTextureDataSize(sTextureHeader, uiMIPMap, false, false);

								//Decompress the texture data.
								PVRTDecompressPVRTC(pTempCompData,bIs2bppPVRTC?1:0,uiMIPWidth,uiMIPHeight,pTempDecompData);

								//Move forward through the pointers.
								pTempDecompData+=decompressedFaceOffset;
								pTempCompData+=compressedFaceOffset;

								//Work out the current MIP dimensions.
								uiMIPWidth=PVRT_MAX(1,uiMIPWidth>>1);
								uiMIPHeight=PVRT_MAX(1,uiMIPHeight>>1);
							}

							//Reset the dims.
							uiMIPWidth=sTextureHeader.u32Width;
							uiMIPHeight=sTextureHeader.u32Height;
						}
					}
					else
					{
						//Decompress all the MIP levels.
						for (PVRTuint32 uiMIPMap=nLoadFromLevel;uiMIPMap<sTextureHeader.u32MIPMapCount;++uiMIPMap)
						{
							//Get the face offset. Varies per MIP level.
							PVRTuint32 decompressedFaceOffset = PVRTGetTextureDataSize(sTextureHeaderDecomp, uiMIPMap, false, false);
							PVRTuint32 compressedFaceOffset = PVRTGetTextureDataSize(sTextureHeader, uiMIPMap, false, false);

							for (PVRTuint32 uiFace=0;uiFace<sTextureHeader.u32NumFaces;++uiFace)
							{
								//Decompress the texture data.
								PVRTDecompressPVRTC(pTempCompData,bIs2bppPVRTC?1:0,uiMIPWidth,uiMIPHeight,pTempDecompData);

								//Move forward through the pointers.
								pTempDecompData+=decompressedFaceOffset;
								pTempCompData+=compressedFaceOffset;
							}

							//Work out the current MIP dimensions.
							uiMIPWidth=PVRT_MAX(1,uiMIPWidth>>1);
							uiMIPHeight=PVRT_MAX(1,uiMIPHeight>>1);
						}
					}
				}else {
					printf("PVRTTextureLoadFromPointer error: PVRTC not supported.\n");
                    return PVR_FAIL;
				}
			}
		}
#ifndef TARGET_OS_IPHONE //TODO
		else if (eTextureInternalFormat==GL_COMPRESSED_RGBA_PVRTC_4BPPV2_IMG || eTextureInternalFormat==GL_COMPRESSED_RGBA_PVRTC_2BPPV2_IMG)
		{
			//Check for PVRTCI support.
			if(bIsPVRTC2Supported)
			{
				bIsCompressedFormatSupported = bIsCompressedFormat = true;
			}
			else
			{
				printf("PVRTTextureLoadFromPointer error: PVRTC not supported.\n");
				return PVR_FAIL;
			}
		}
		else if (eTextureInternalFormat==GL_ETC1_RGB8_OES)
		{
			if(bIsETCSupported)
			{
				bIsCompressedFormatSupported = bIsCompressedFormat = true;
			}
			else
			{
				
                printf("PVRTTextureLoadFromPointer error: ETC not supported.\n");
                return PVR_FAIL;
				
			}
		}
#endif
	}
    
	//Check for BGRA support.
	if(eTextureFormat==GL_BGRA)
	{
#ifdef TARGET_OS_IPHONE
		eTextureInternalFormat = GL_RGBA;
#endif
		if(!bIsBGRA8888Supported)
		{
#ifdef TARGET_OS_IPHONE
			printf("PVRTTextureLoadFromPointer failed: Unable to load GL_BGRA texture as extension GL_APPLE_texture_format_BGRA8888 is unsupported.\n");
#else
			printf("PVRTTextureLoadFromPointer failed: Unable to load GL_BGRA texture as extension GL_IMG_texture_format_BGRA8888 is unsupported.\n");
#endif
			return PVR_FAIL;
		}
	}
    
	//Check for floating point textures
	if (eTextureType==GL_HALF_FLOAT_OES)
	{
		if(!bIsFloat16Supported)
		{
			printf("PVRTTextureLoadFromPointer failed: Unable to load GL_HALF_FLOAT_OES texture as extension GL_OES_texture_half_float is unsupported.\n");
		}
	}
	if (eTextureType==GL_FLOAT)
	{
		if(!bIsFloat32Supported)
		{
			printf("PVRTTextureLoadFromPointer failed: Unable to load GL_FLOAT texture as extension GL_OES_texture_float is unsupported.\n");
		}
	}
    
	//Deal with unsupported texture formats
	if (eTextureInternalFormat==0)
	{
		printf("PVRTTextureLoadFromPointer failed: pixel type not supported.\n");
		return PVR_FAIL;
	}
    
	//PVR files are never row aligned.
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    
	//Generate a texture


	glGenTextures(1, texName);

	
    
	//Initialise a texture target.
	GLint eTarget=GL_TEXTURE_2D;
	
	if(sTextureHeader.u32NumFaces>1)
	{
		eTarget=GL_TEXTURE_CUBE_MAP;
	}
    
	//Check if this is a texture array.
	if(sTextureHeader.u32NumSurfaces>1)
	{
		//Not supported in OpenGLES 2.0
		printf("PVRTTextureLoadFromPointer failed: Texture arrays are not available in OGLES2.0.\n");
		return PVR_FAIL;
	}
    
	//Bind the 2D texture
	glBindTexture(eTarget, *texName);
    
	if(glGetError())
	{
		printf("PVRTTextureLoadFromPointer failed: glBindTexture() failed.\n");
		//return PVR_FAIL;
	}
    
	//Initialise the current MIP size.
	PVRTuint32 uiCurrentMIPSize=0;
    
	//Loop through the faces
	//Check if this is a cube map.
	if(sTextureHeader.u32NumFaces>1)
	{
		eTarget=GL_TEXTURE_CUBE_MAP_POSITIVE_X;
	}
    
	//Initialise the width/height
	PVRTuint32 u32MIPWidth = sTextureHeader.u32Width;
	PVRTuint32 u32MIPHeight = sTextureHeader.u32Height;
    
	//Temporary data to save on if statements within the load loops.
	PVRTuint8* pTempData=NULL;
	PVRTextureHeaderV3 *psTempHeader=NULL;
	if (bIsCompressedFormat && !bIsCompressedFormatSupported)
	{
		pTempData=(PVRTuint8*)pDecompressedData;
		psTempHeader=&sTextureHeaderDecomp;
	}
	else
	{
		pTempData=pTextureData;
		psTempHeader=&sTextureHeader;
	}
    
	//Loop through all MIP levels.
	if (bIsLegacyPVR)
	{
		//Temporary texture target.
		GLint eTextureTarget=eTarget;
        
		//Loop through all the faces.
		for (PVRTuint32 uiFace=0; uiFace<psTempHeader->u32NumFaces; ++uiFace)
		{
			//Loop through all the mip levels.
			for (PVRTuint32 uiMIPLevel=0; uiMIPLevel<psTempHeader->u32MIPMapCount; ++uiMIPLevel)
			{
				//Get the current MIP size.
				uiCurrentMIPSize=PVRTGetTextureDataSize(*psTempHeader,uiMIPLevel,false,false);
                
				if (uiMIPLevel>=nLoadFromLevel)
				{
					//Upload the texture
					if (bIsCompressedFormat && bIsCompressedFormatSupported)
					{
						glCompressedTexImage2D(eTextureTarget,uiMIPLevel-nLoadFromLevel,eTextureInternalFormat,u32MIPWidth, u32MIPHeight, 0, uiCurrentMIPSize, pTempData);
					}
					else
					{
						glTexImage2D(eTextureTarget,uiMIPLevel-nLoadFromLevel,eTextureInternalFormat, u32MIPWidth, u32MIPHeight, 0, eTextureFormat, eTextureType, pTempData);
					}
				}
				pTempData+=uiCurrentMIPSize;
                
				//Reduce the MIP Size.
				u32MIPWidth=PVRT_MAX(1,u32MIPWidth>>1);
				u32MIPHeight=PVRT_MAX(1,u32MIPHeight>>1);
			}
            
			//Increase the texture target.
			eTextureTarget++;
            
			//Reset the current MIP dimensions.
			u32MIPWidth=psTempHeader->u32Width;
			u32MIPHeight=psTempHeader->u32Height;
            
			//Error check
			if(glGetError())
			{
				FREE(pDecompressedData);
				printf("PVRTTextureLoadFromPointer failed: glTexImage2D() failed.\n");
				return PVR_FAIL;
			}
		}
	}
	else
	{
		for (PVRTuint32 uiMIPLevel=0; uiMIPLevel<psTempHeader->u32MIPMapCount; ++uiMIPLevel)
		{
			//Get the current MIP size.
			uiCurrentMIPSize=PVRTGetTextureDataSize(*psTempHeader,uiMIPLevel,false,false);
            
			GLint eTextureTarget=eTarget;
            
			for (PVRTuint32 uiFace=0; uiFace<psTempHeader->u32NumFaces; ++uiFace)
			{
				if (uiMIPLevel>=nLoadFromLevel)
				{
					//Upload the texture
					if (bIsCompressedFormat && bIsCompressedFormatSupported)
					{
						glCompressedTexImage2D(eTextureTarget,uiMIPLevel-nLoadFromLevel,eTextureInternalFormat,u32MIPWidth, u32MIPHeight, 0, uiCurrentMIPSize, pTempData);
					}
					else
					{
						glTexImage2D(eTextureTarget,uiMIPLevel-nLoadFromLevel,eTextureInternalFormat, u32MIPWidth, u32MIPHeight, 0, eTextureFormat, eTextureType, pTempData);
					}
				}
				pTempData+=uiCurrentMIPSize;
				eTextureTarget++;
			}
            
			//Reduce the MIP Size.
			u32MIPWidth=PVRT_MAX(1,u32MIPWidth>>1);
			u32MIPHeight=PVRT_MAX(1,u32MIPHeight>>1);
            
			//Error check
			if(glGetError())
			{
				//FREE(pDecompressedData);
				printf("PVRTTextureLoadFromPointer failed: glTexImage2D() failed.\n");
				//return PVR_FAIL;
			}
		}
	}
    
	FREE(pDecompressedData);
    
	if (eTarget!=GL_TEXTURE_2D)
	{
		eTarget=GL_TEXTURE_CUBE_MAP;
	}
    
	//Error check
	if(glGetError())
	{
		printf("PVRTTextureLoadFromPointer failed: glTexImage2D() failed.\n");
		//return PVR_FAIL;
	}
	
	//Set Minification and Magnification filters according to whether MIP maps are present.
	if(eTextureType==GL_FLOAT || eTextureType==GL_HALF_FLOAT_OES)
	{
		if(sTextureHeader.u32MIPMapCount==1)
		{	// Texture filter modes are limited to these for float textures
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
		else
		{
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}
	}
	else
	{
		if(sTextureHeader.u32MIPMapCount==1)
		{
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			glTexParameteri(eTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
			glTexParameteri(eTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}
    
	if(	(sTextureHeader.u32Width & (sTextureHeader.u32Width - 1)) | (sTextureHeader.u32Height & (sTextureHeader.u32Height - 1)))
	{
		/*
         NPOT textures requires the wrap mode to be set explicitly to
         GL_CLAMP_TO_EDGE or the texture will be inconsistent.
         */
		glTexParameteri(eTarget, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(eTarget, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else
	{
		glTexParameteri(eTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(eTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
    
	//Error check
	if(glGetError())
	{
		printf("PVRTTextureLoadFromPointer failed: glTexParameter() failed.\n");
		//return PVR_FAIL;
	}
    
	return PVR_SUCCESS;
}
inline bool PVRTIsLittleEndian()
{
	static bool bLittleEndian;
	static bool bIsInit = false;
    
	if(!bIsInit)
	{
		short int word = 0x0001;
		char *byte = (char*) &word;
		bLittleEndian = byte[0] ? true : false;
		bIsInit = true;
	}
    
	return bLittleEndian;
}
template <typename T>
inline void PVRTswap(T& a, T& b)
{
	T temp = a;
	a = b;
	b = temp;
}
inline void PVRTByteSwap(unsigned char* pBytes, int i32ByteNo)
{
	int i = 0, j = i32ByteNo - 1;
    
	while(i < j)
		PVRTswap<unsigned char>(pBytes[i++], pBytes[j--]);
}
inline unsigned int PVRTByteSwap32(unsigned int ui32Long)
{
	return ((ui32Long&0x000000FF)<<24) + ((ui32Long&0x0000FF00)<<8) + ((ui32Long&0x00FF0000)>>8) + ((ui32Long&0xFF000000) >> 24);
}

/*!***************************************************************************
 @brief      	Converts the endianness of a unsigned short
 @param[in]		ui16Short   A number
 @return		ui16Short with its endianness changed
 *****************************************************************************/
inline unsigned short PVRTByteSwap16(unsigned short ui16Short)
{
	return (ui16Short>>8) | (ui16Short<<8);
}

/*!***********************************************************************
 @Function		PVRTMapLegacyTextureEnumToNewFormat
 @Input			OldFormat		Legacy Enumeration Value
 @Modified		newType			New PixelType identifier.
 @Modified		newCSpace		New ColourSpace
 @Modified		newChanType		New Channel Type
 @Modified		isPreMult		Whether format is pre-multiplied
 @Description	Maps a legacy enumeration value to the new PVR3 style format.
 *************************************************************************/
void PVRTMapLegacyTextureEnumToNewFormat(PVRTPixelType OldFormat, PVRTuint64& newType, EPVRTColourSpace& newCSpace, EPVRTVariableType& newChanType, bool& isPreMult)
{
	//Default value.
	isPreMult=false;
    
	switch (OldFormat)
	{
        case MGLPT_ARGB_4444:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',4,4,4,4);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case MGLPT_ARGB_1555:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',1,5,5,5);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case MGLPT_RGB_565:
		{
			newType=PVRTGENPIXELID3('r','g','b',5,6,5);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case MGLPT_RGB_555:
		{
			newType=PVRTGENPIXELID4('x','r','g','b',1,5,5,5);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case MGLPT_RGB_888:
		{
			newType=PVRTGENPIXELID3('r','g','b',8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case MGLPT_ARGB_8888:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case MGLPT_ARGB_8332:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',8,3,3,2);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case MGLPT_I_8:
		{
			newType=PVRTGENPIXELID1('i',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case MGLPT_AI_88:
		{
			newType=PVRTGENPIXELID2('a','i',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case MGLPT_1_BPP:
		{
			newType=ePVRTPF_BW1bpp;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case MGLPT_VY1UY0:
		{
			newType=ePVRTPF_YUY2;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case MGLPT_Y1VY0U:
		{
			newType=ePVRTPF_UYVY;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case MGLPT_PVRTC2:
		{
			newType=ePVRTPF_PVRTCI_2bpp_RGBA;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case MGLPT_PVRTC4:
		{
			newType=ePVRTPF_PVRTCI_4bpp_RGBA;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_RGBA_4444:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',4,4,4,4);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case OGL_RGBA_5551:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',5,5,5,1);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case OGL_RGBA_8888:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_RGB_565:
		{
			newType=PVRTGENPIXELID3('r','g','b',5,6,5);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case OGL_RGB_555:
		{
			newType=PVRTGENPIXELID4('r','g','b','x',5,5,5,1);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case OGL_RGB_888:
		{
			newType=PVRTGENPIXELID3('r','g','b',8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_I_8:
		{
			newType=PVRTGENPIXELID1('l',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_AI_88:
		{
			newType=PVRTGENPIXELID2('l','a',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_PVRTC2:
		{
			newType=ePVRTPF_PVRTCI_2bpp_RGBA;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_PVRTC4:
		{
			newType=ePVRTPF_PVRTCI_4bpp_RGBA;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_BGRA_8888:
		{
			newType=PVRTGENPIXELID4('b','g','r','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_A_8:
		{
			newType=PVRTGENPIXELID1('a',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_PVRTCII4:
		{
			newType=ePVRTPF_PVRTCII_4bpp;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case OGL_PVRTCII2:
		{
			newType=ePVRTPF_PVRTCII_2bpp;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
#ifdef _WIN32
        case D3D_DXT1:
		{
			newType=ePVRTPF_DXT1;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case D3D_DXT2:
		{
			newType=ePVRTPF_DXT2;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case D3D_DXT3:
		{
			newType=ePVRTPF_DXT3;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case D3D_DXT4:
		{
			newType=ePVRTPF_DXT4;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case D3D_DXT5:
		{
			newType=ePVRTPF_DXT5;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
#endif
        case D3D_RGB_332:
		{
			newType=PVRTGENPIXELID3('r','g','b',3,3,2);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_AL_44:
		{
			newType=PVRTGENPIXELID2('a','l',4,4);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_LVU_655:
		{
			newType=PVRTGENPIXELID3('l','g','r',6,5,5);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedIntegerNorm;
			break;
		}
            
        case D3D_XLVU_8888:
		{
			newType=PVRTGENPIXELID4('x','l','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedIntegerNorm;
			break;
		}
            
        case D3D_QWVU_8888:
		{
			newType=PVRTGENPIXELID4('a','b','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedIntegerNorm;
			break;
		}
            
        case D3D_ABGR_2101010:
		{
			newType=PVRTGENPIXELID4('a','b','g','r',2,10,10,10);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_ARGB_2101010:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',2,10,10,10);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_AWVU_2101010:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',2,10,10,10);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_GR_1616:
		{
			newType=PVRTGENPIXELID2('g','r',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_VU_1616:
		{
			newType=PVRTGENPIXELID2('g','r',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedIntegerNorm;
			break;
		}
            
        case D3D_ABGR_16161616:
		{
			newType=PVRTGENPIXELID4('a','b','g','r',16,16,16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_R16F:
		{
			newType=PVRTGENPIXELID1('r',16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case D3D_GR_1616F:
		{
			newType=PVRTGENPIXELID2('g','r',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case D3D_ABGR_16161616F:
		{
			newType=PVRTGENPIXELID4('a','b','g','r',16,16,16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case D3D_R32F:
		{
			newType=PVRTGENPIXELID1('r',32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case D3D_GR_3232F:
		{
			newType=PVRTGENPIXELID2('g','r',32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case D3D_ABGR_32323232F:
		{
			newType=PVRTGENPIXELID4('a','b','g','r',32,32,32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case ETC_RGB_4BPP:
		{
			newType=ePVRTPF_ETC1;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case D3D_A8:
		{
			newType=PVRTGENPIXELID1('a',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_V8U8:
		{
			newType=PVRTGENPIXELID2('g','r',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedIntegerNorm;
			break;
		}
            
        case D3D_L16:
		{
			newType=PVRTGENPIXELID1('l',16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_L8:
		{
			newType=PVRTGENPIXELID1('l',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_AL_88:
		{
			newType=PVRTGENPIXELID2('a','l',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case D3D_UYVY:
		{
			newType=ePVRTPF_UYVY;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case D3D_YUY2:
		{
			newType=ePVRTPF_YUY2;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_R32G32B32A32_FLOAT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',32,32,32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R32G32B32A32_UINT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',32,32,32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedInteger;
			break;
		}
            
        case DX10_R32G32B32A32_SINT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',32,32,32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedInteger;
			break;
		}
            
        case DX10_R32G32B32_FLOAT:
		{
			newType=PVRTGENPIXELID3('r','g','b',32,32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R32G32B32_UINT:
		{
			newType=PVRTGENPIXELID3('r','g','b',32,32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedInteger;
			break;
		}
            
        case DX10_R32G32B32_SINT:
		{
			newType=PVRTGENPIXELID3('r','g','b',32,32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedInteger;
			break;
		}
            
        case DX10_R16G16B16A16_FLOAT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',16,16,16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R16G16B16A16_UNORM:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',16,16,16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case DX10_R16G16B16A16_UINT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',16,16,16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShort;
			break;
		}
            
        case DX10_R16G16B16A16_SNORM:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',16,16,16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedShortNorm;
			break;
		}
            
        case DX10_R16G16B16A16_SINT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',16,16,16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedShort;
			break;
		}
            
        case DX10_R32G32_FLOAT:
		{
			newType=PVRTGENPIXELID2('r','g',32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R32G32_UINT:
		{
			newType=PVRTGENPIXELID2('r','g',32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedInteger;
			break;
		}
            
        case DX10_R32G32_SINT:
		{
			newType=PVRTGENPIXELID2('r','g',32,32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedInteger;
			break;
		}
            
        case DX10_R10G10B10A2_UNORM:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',10,10,10,2);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_R10G10B10A2_UINT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',10,10,10,2);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedInteger;
			break;
		}
            
        case DX10_R11G11B10_FLOAT:
		{
			newType=PVRTGENPIXELID3('r','g','b',11,11,10);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R8G8B8A8_UNORM:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_R8G8B8A8_UNORM_SRGB:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_R8G8B8A8_UINT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByte;
			break;
		}
            
        case DX10_R8G8B8A8_SNORM:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedByteNorm;
			break;
		}
            
        case DX10_R8G8B8A8_SINT:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedByte;
			break;
		}
            
        case DX10_R16G16_FLOAT:
		{
			newType=PVRTGENPIXELID2('r','g',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R16G16_UNORM:
		{
			newType=PVRTGENPIXELID2('r','g',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case DX10_R16G16_UINT:
		{
			newType=PVRTGENPIXELID2('r','g',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShort;
			break;
		}
            
        case DX10_R16G16_SNORM:
		{
			newType=PVRTGENPIXELID2('r','g',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedShortNorm;
			break;
		}
            
        case DX10_R16G16_SINT:
		{
			newType=PVRTGENPIXELID2('r','g',16,16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedShort;
			break;
		}
            
        case DX10_R32_FLOAT:
		{
			newType=PVRTGENPIXELID1('r',32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R32_UINT:
		{
			newType=PVRTGENPIXELID1('r',32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedInteger;
			break;
		}
            
        case DX10_R32_SINT:
		{
			newType=PVRTGENPIXELID1('r',32);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedInteger;
			break;
		}
            
        case DX10_R8G8_UNORM:
		{
			newType=PVRTGENPIXELID2('r','g',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_R8G8_UINT:
		{
			newType=PVRTGENPIXELID2('r','g',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByte;
			break;
		}
            
        case DX10_R8G8_SNORM:
		{
			newType=PVRTGENPIXELID2('r','g',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedByteNorm;
			break;
		}
            
        case DX10_R8G8_SINT:
		{
			newType=PVRTGENPIXELID2('r','g',8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedByte;
			break;
		}
            
        case DX10_R16_FLOAT:
		{
			newType=PVRTGENPIXELID1('r',16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R16_UNORM:
		{
			newType=PVRTGENPIXELID1('r',16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case DX10_R16_UINT:
		{
			newType=PVRTGENPIXELID1('r',16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedShort;
			break;
		}
            
        case DX10_R16_SNORM:
		{
			newType=PVRTGENPIXELID1('r',16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedShortNorm;
			break;
		}
            
        case DX10_R16_SINT:
		{
			newType=PVRTGENPIXELID1('r',16);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedShort;
			break;
		}
            
        case DX10_R8_UNORM:
		{
			newType=PVRTGENPIXELID1('r',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_R8_UINT:
		{
			newType=PVRTGENPIXELID1('r',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByte;
			break;
		}
            
        case DX10_R8_SNORM:
		{
			newType=PVRTGENPIXELID1('r',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedByteNorm;
			break;
		}
            
        case DX10_R8_SINT:
		{
			newType=PVRTGENPIXELID1('r',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedByte;
			break;
		}
            
        case DX10_A8_UNORM:
		{
			newType=PVRTGENPIXELID1('r',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_R1_UNORM:
		{
			newType=ePVRTPF_BW1bpp;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_R9G9B9E5_SHAREDEXP:
		{
			newType=ePVRTPF_SharedExponentR9G9B9E5;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedFloat;
			break;
		}
            
        case DX10_R8G8_B8G8_UNORM:
		{
			newType=ePVRTPF_RGBG8888;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case DX10_G8R8_G8B8_UNORM:
		{
			newType=ePVRTPF_GRGB8888;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
#ifdef _WIN32
        case DX10_BC1_UNORM:
		{
			newType=ePVRTPF_DXT1;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC1_UNORM_SRGB:
		{
			newType=ePVRTPF_DXT1;
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC2_UNORM:
		{
			newType=ePVRTPF_DXT3;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC2_UNORM_SRGB:
		{
			newType=ePVRTPF_DXT3;
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC3_UNORM:
		{
			newType=ePVRTPF_DXT5;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC3_UNORM_SRGB:
		{
			newType=ePVRTPF_DXT5;
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC4_UNORM:
		{
			newType=ePVRTPF_BC4;
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC4_SNORM:
		{
			newType=ePVRTPF_BC4;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedIntegerNorm;
			break;
		}
            
        case DX10_BC5_UNORM:
		{
			newType=ePVRTPF_BC5;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedIntegerNorm;
			break;
		}
            
        case DX10_BC5_SNORM:
		{
			newType=ePVRTPF_BC5;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeSignedIntegerNorm;
			break;
		}
            
#endif
        case ePT_VG_sRGBX_8888:
		{
			newType=PVRTGENPIXELID4('r','g','b','x',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sRGBA_8888:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sRGBA_8888_PRE:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case ePT_VG_sRGB_565:
		{
			newType=PVRTGENPIXELID3('r','g','b',5,6,5);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_sRGBA_5551:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',5,5,5,1);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_sRGBA_4444:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',4,4,4,4);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_sL_8:
		{
			newType=PVRTGENPIXELID1('l',8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lRGBX_8888:
		{
			newType=PVRTGENPIXELID4('r','g','b','x',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lRGBA_8888:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lRGBA_8888_PRE:
		{
			newType=PVRTGENPIXELID4('r','g','b','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case ePT_VG_lL_8:
		{
			newType=PVRTGENPIXELID1('l',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_A_8:
		{
			newType=PVRTGENPIXELID1('a',8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_BW_1:
		{
			newType=ePVRTPF_BW1bpp;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sXRGB_8888:
		{
			newType=PVRTGENPIXELID4('x','r','g','b',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sARGB_8888:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sARGB_8888_PRE:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case ePT_VG_sARGB_1555:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',1,5,5,5);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_sARGB_4444:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',4,4,4,4);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_lXRGB_8888:
		{
			newType=PVRTGENPIXELID4('x','r','g','b',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lARGB_8888:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lARGB_8888_PRE:
		{
			newType=PVRTGENPIXELID4('a','r','g','b',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case ePT_VG_sBGRX_8888:
		{
			newType=PVRTGENPIXELID4('b','g','r','x',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sBGRA_8888:
		{
			newType=PVRTGENPIXELID4('b','g','r','a',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sBGRA_8888_PRE:
		{
			newType=PVRTGENPIXELID4('b','g','r','a',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case ePT_VG_sBGR_565: 
		{
			newType=PVRTGENPIXELID3('b','g','r',5,6,5);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_sBGRA_5551: 
		{
			newType=PVRTGENPIXELID4('b','g','r','a',5,5,5,1);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_sBGRA_4444: 
		{
			newType=PVRTGENPIXELID4('b','g','r','x',4,4,4,4);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_lBGRX_8888: 
		{
			newType=PVRTGENPIXELID4('b','g','r','x',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lBGRA_8888: 
		{
			newType=PVRTGENPIXELID4('b','g','r','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lBGRA_8888_PRE: 
		{
			newType=PVRTGENPIXELID4('b','g','r','a',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case ePT_VG_sXBGR_8888: 
		{
			newType=PVRTGENPIXELID4('x','b','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sABGR_8888: 
		{
			newType=PVRTGENPIXELID4('a','b','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_sABGR_8888_PRE: 
		{
			newType=PVRTGENPIXELID4('a','b','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
            
        case ePT_VG_sABGR_1555: 
		{
			newType=PVRTGENPIXELID4('a','b','g','r',1,5,5,5);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_sABGR_4444: 
		{
			newType=PVRTGENPIXELID4('x','b','g','r',4,4,4,4);
			newCSpace=ePVRTCSpacesRGB;
			newChanType=ePVRTVarTypeUnsignedShortNorm;
			break;
		}
            
        case ePT_VG_lXBGR_8888: 
		{
			newType=PVRTGENPIXELID4('x','b','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lABGR_8888: 
		{
			newType=PVRTGENPIXELID4('a','b','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			break;
		}
            
        case ePT_VG_lABGR_8888_PRE: 
		{
			newType=PVRTGENPIXELID4('a','b','g','r',8,8,8,8);
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeUnsignedByteNorm;
			isPreMult=true;
			break;
		}
        default:
		{
			newType=ePVRTPF_NumCompressedPFs;
			newCSpace=ePVRTCSpacelRGB;
			newChanType=ePVRTVarTypeNumVarTypes;
			break;
		}
	}
}

/*!***************************************************************************
 @Function		PVRTTextureLoadFromPVR
 @Input			filename			Filename of the .PVR file to load the texture from
 @Modified		texName				the OpenGL ES texture name as returned by glBindTexture
 @Modified		psTextureHeader		Pointer to a PVRTextureHeaderV3 struct. Modified to
 contain the header data of the returned texture Ignored if NULL.
 @Input			bAllowDecompress	Allow decompression if PVRTC is not supported in hardware.
 @Input			nLoadFromLevel		Which mip map level to start loading from (0=all)
 @Modified		pMetaData			If a valid map is supplied, this will return any and all
 MetaDataBlocks stored in the texture, organised by DevFourCC
 then identifier. Supplying NULL will ignore all MetaData.
 @Return		PVR_SUCCESS on success
 @Description	Allows textures to be stored in binary PVR files and loaded in. Can load parts of a
 mip mapped texture (i.e. skipping the highest detailed levels).
 Sets the texture MIN/MAG filter to GL_LINEAR_MIPMAP_NEAREST/GL_LINEAR
 if mip maps are present, GL_LINEAR/GL_LINEAR otherwise.
 *****************************************************************************/
EPVRTError PVRTTextureLoadFromPVR(	const void*DataPtr,
                                  GLuint * const texName,
                                  const void *psTextureHeader,
                                  bool bAllowDecompress,
                                  const unsigned int nLoadFromLevel)
{

    
	//Header size.
	PVRTuint32 u32HeaderSize=0;
    
	//Boolean whether to byte swap the texture data or not.
	bool bSwapDataEndianness=false;
    
	//Texture header to check against.
	PVRTextureHeaderV3 sTextureHeader;
    
	//The channel type for endian swapping.
	EPVRTVariableType u32CurrentChannelType=ePVRTVarTypeUnsignedByte;
    
	//Check the first word of the file and see if it's equal to the current identifier (or reverse identifier)
	if(*(PVRTuint32*)DataPtr!=PVRTEX_CURR_IDENT && *(PVRTuint32*)DataPtr!=PVRTEX_CURR_IDENT_REV)
	{
		//Swap the header bytes if necessary.
		if(!PVRTIsLittleEndian())
		{
			bSwapDataEndianness=true;
			PVRTuint32 u32HeaderSize=PVRTByteSwap32(*(PVRTuint32*)DataPtr);
            
			for (PVRTuint32 i=0; i<u32HeaderSize; ++i)
			{
				PVRTByteSwap( (PVRTuint8*)( ( (PVRTuint32*)DataPtr )+i),sizeof(PVRTuint32) );
			}
		}
        
		//Get a pointer to the header.
		PVR_Texture_Header* sLegacyTextureHeader=(PVR_Texture_Header*)DataPtr;
        
		//Set the header size.
		u32HeaderSize=sLegacyTextureHeader->dwHeaderSize;
        
		//We only really need the channel type.
		PVRTuint64 tempFormat;
		EPVRTColourSpace tempColourSpace;
		bool tempIsPreMult;
        
		//Map the enum to get the channel type.
		PVRTMapLegacyTextureEnumToNewFormat( (PVRTPixelType)( sLegacyTextureHeader->dwpfFlags&0xff),tempFormat,tempColourSpace, u32CurrentChannelType, tempIsPreMult);
	}
	// If the header file has a reverse identifier, then we need to swap endianness
	else if(*(PVRTuint32*)DataPtr==PVRTEX_CURR_IDENT_REV)
	{
		//Setup the texture header
		sTextureHeader=*(PVRTextureHeaderV3*)DataPtr;
        
		bSwapDataEndianness=true;
		PVRTextureHeaderV3* pTextureHeader=(PVRTextureHeaderV3*)DataPtr;
        
		pTextureHeader->u32ChannelType=PVRTByteSwap32(pTextureHeader->u32ChannelType);
		pTextureHeader->u32ColourSpace=PVRTByteSwap32(pTextureHeader->u32ColourSpace);
		pTextureHeader->u32Depth=PVRTByteSwap32(pTextureHeader->u32Depth);
		pTextureHeader->u32Flags=PVRTByteSwap32(pTextureHeader->u32Flags);
		pTextureHeader->u32Height=PVRTByteSwap32(pTextureHeader->u32Height);
		pTextureHeader->u32MetaDataSize=PVRTByteSwap32(pTextureHeader->u32MetaDataSize);
		pTextureHeader->u32MIPMapCount=PVRTByteSwap32(pTextureHeader->u32MIPMapCount);
		pTextureHeader->u32NumFaces=PVRTByteSwap32(pTextureHeader->u32NumFaces);
		pTextureHeader->u32NumSurfaces=PVRTByteSwap32(pTextureHeader->u32NumSurfaces);
		pTextureHeader->u32Version=PVRTByteSwap32(pTextureHeader->u32Version);
		pTextureHeader->u32Width=PVRTByteSwap32(pTextureHeader->u32Width);
		PVRTByteSwap((PVRTuint8*)&pTextureHeader->u64PixelFormat,sizeof(PVRTuint64));
        
		//Channel type.
		u32CurrentChannelType=(EPVRTVariableType)pTextureHeader->u32ChannelType;
        
		//Header size.
		u32HeaderSize=PVRTEX3_HEADERSIZE+sTextureHeader.u32MetaDataSize;
	}
	else
	{
		//Header size.
		u32HeaderSize=PVRTEX3_HEADERSIZE+sTextureHeader.u32MetaDataSize;
	}
    
	// Convert the data if needed
	if(bSwapDataEndianness)
	{
		//Get the size of the variables types.
		PVRTuint32 ui32VariableSize=0;
		switch(u32CurrentChannelType)
		{
            case ePVRTVarTypeFloat:
            case ePVRTVarTypeUnsignedInteger:
            case ePVRTVarTypeUnsignedIntegerNorm:
            case ePVRTVarTypeSignedInteger:
            case ePVRTVarTypeSignedIntegerNorm:
			{
				ui32VariableSize=4;
				break;
			}
            case ePVRTVarTypeUnsignedShort:
            case ePVRTVarTypeUnsignedShortNorm:
            case ePVRTVarTypeSignedShort:
            case ePVRTVarTypeSignedShortNorm:
			{
				ui32VariableSize=2;
				break;
			}
            case ePVRTVarTypeUnsignedByte:
            case ePVRTVarTypeUnsignedByteNorm:
            case ePVRTVarTypeSignedByte:
            case ePVRTVarTypeSignedByteNorm:
			{
				ui32VariableSize=1;
				break;
			}
            default:
                break;
		}
		
		//If the size of the variable type is greater than 1, then we need to byte swap.
		if (ui32VariableSize>1)
		{
			//Get the texture data.
			PVRTuint8* pu8OrigData = ( (PVRTuint8*)DataPtr + u32HeaderSize);
            
			//Get the size of the texture data.
            
			PVRTuint32 ui32TextureDataSize = PVRTGetTextureDataSize(sTextureHeader,PVRTEX_ALLMIPLEVELS,true,true);
            
			//Loop through and byte swap all the data. It's swapped in place so no need to do anything special.
			for(PVRTuint32 i = 0; i < ui32TextureDataSize; i+=ui32VariableSize)
			{
				PVRTByteSwap(pu8OrigData+i,ui32VariableSize);
			}
		}
	}
	
	return PVRTTextureLoadFromPointer(DataPtr, texName, psTextureHeader, bAllowDecompress, nLoadFromLevel,NULL);
}

/*!***************************************************************************
 @Function			PVRTTextureFormatGetBPP
 @Input				nFormat
 @Input				nType
 @Description		Returns the bits per pixel (BPP) of the format.
 *****************************************************************************/
unsigned int PVRTTextureFormatGetBPP(const GLuint nFormat, const GLuint nType)
{
	switch(nFormat)
	{
        case GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
        case GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
            return 2;
        case GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
        case GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
            return 4;
        case GL_UNSIGNED_BYTE:
            switch(nType)
		{
            case GL_RGBA:
            case GL_BGRA:
                return 32;
		}
        case GL_UNSIGNED_SHORT_5_5_5_1:
            switch(nType)
		{
            case GL_RGBA:
                return 16;
		}
	}
    
	return 0xFFFFFFFF;
}



/***********************************************************
				DECOMPRESSION ROUTINES
************************************************************/
/*****************************************************************************
 * Useful structs
 *****************************************************************************/
struct Pixel32
{
	PVRTuint8 red,green,blue,alpha;
};

struct Pixel128S
{
	PVRTint32 red,green,blue,alpha;
};

struct PVRTCWord
{
	PVRTuint32 u32ModulationData;
	PVRTuint32 u32ColourData;
};

struct PVRTCWordIndices
{
	int P[2], Q[2], R[2], S[2];
};	
/********************************************************************************/
/*!***********************************************************************
 @Function		getColourA
 @Input			u32ColourData	Colour information from a PVRTCWord.
 @Return		Returns the first colour in a PVRTCWord's colour data.
 @Description	Decodes the first colour in a PVRTCWord's colour data.
*************************************************************************/
static Pixel32 getColourA(PVRTuint32 u32ColourData)
{
	Pixel32 colour;

	// Opaque Colour Mode - RGB 554
	if ((u32ColourData & 0x8000) != 0)
	{
		colour.red   = (PVRTuint8)((u32ColourData & 0x7c00) >> 10); // 5->5 bits
		colour.green = (PVRTuint8)((u32ColourData & 0x3e0)  >> 5); // 5->5 bits
		colour.blue  = (PVRTuint8)(u32ColourData  & 0x1e) | ((u32ColourData & 0x1e) >> 4); // 4->5 bits
		colour.alpha = (PVRTuint8)0xf;// 0->4 bits
	}
	// Transparent Colour Mode - ARGB 3443
	else
	{	
		colour.red   = (PVRTuint8)((u32ColourData & 0xf00)  >> 7) | ((u32ColourData & 0xf00) >> 11); // 4->5 bits
		colour.green = (PVRTuint8)((u32ColourData & 0xf0)   >> 3) | ((u32ColourData & 0xf0)  >> 7); // 4->5 bits
		colour.blue  = (PVRTuint8)((u32ColourData & 0xe)    << 1) | ((u32ColourData & 0xe)   >> 2); // 3->5 bits
		colour.alpha = (PVRTuint8)((u32ColourData & 0x7000) >> 11);// 3->4 bits - note 0 at right
	}

	return colour;
}

/*!***********************************************************************
 @Function		getColourB
 @Input			u32ColourData	Colour information from a PVRTCWord.
 @Return		Returns the second colour in a PVRTCWord's colour data.
 @Description	Decodes the second colour in a PVRTCWord's colour data.
*************************************************************************/
static Pixel32 getColourB(PVRTuint32 u32ColourData)
{ 
	Pixel32 colour;

	// Opaque Colour Mode - RGB 555
	if (u32ColourData & 0x80000000)
	{	
		colour.red   = (PVRTuint8)((u32ColourData & 0x7c000000) >> 26); // 5->5 bits 
		colour.green = (PVRTuint8)((u32ColourData & 0x3e00000)  >> 21); // 5->5 bits
		colour.blue  = (PVRTuint8)((u32ColourData & 0x1f0000)   >> 16); // 5->5 bits
		colour.alpha = (PVRTuint8)0xf;// 0 bits
	}
	// Transparent Colour Mode - ARGB 3444
	else
	{	
		colour.red   = (PVRTuint8)(((u32ColourData & 0xf000000)  >> 23) | ((u32ColourData & 0xf000000) >> 27)); // 4->5 bits
		colour.green = (PVRTuint8)(((u32ColourData & 0xf00000)   >> 19) | ((u32ColourData & 0xf00000)  >> 23)); // 4->5 bits
		colour.blue  = (PVRTuint8)(((u32ColourData & 0xf0000)    >> 15) | ((u32ColourData & 0xf0000)   >> 19)); // 4->5 bits
		colour.alpha = (PVRTuint8)((u32ColourData & 0x70000000) >> 27);// 3->4 bits - note 0 at right
	}

	return colour;
}

/*!***********************************************************************
 @Function		interpolateColours
 @Input			P,Q,R,S				Low bit-rate colour values for each PVRTCWord.
 @Modified		pPixel				Output array for upscaled colour values.
 @Input			ui8Bpp				Number of bpp.
 @Description	Bilinear upscale from 2x2 pixels to 4x4/8x4 pixels (depending on PVRTC bpp mode).
*************************************************************************/
static void interpolateColours(Pixel32 P, Pixel32 Q, Pixel32 R, Pixel32 S, 
						Pixel128S *pPixel, PVRTuint8 ui8Bpp)
{
	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	//Convert to int 32.
	Pixel128S hP = {(PVRTint32)P.red,(PVRTint32)P.green,(PVRTint32)P.blue,(PVRTint32)P.alpha};
	Pixel128S hQ = {(PVRTint32)Q.red,(PVRTint32)Q.green,(PVRTint32)Q.blue,(PVRTint32)Q.alpha};
	Pixel128S hR = {(PVRTint32)R.red,(PVRTint32)R.green,(PVRTint32)R.blue,(PVRTint32)R.alpha};
	Pixel128S hS = {(PVRTint32)S.red,(PVRTint32)S.green,(PVRTint32)S.blue,(PVRTint32)S.alpha};

	//Get vectors.
	Pixel128S QminusP = {hQ.red - hP.red, hQ.green - hP.green, hQ.blue - hP.blue, hQ.alpha - hP.alpha};	
	Pixel128S SminusR = {hS.red - hR.red, hS.green - hR.green, hS.blue - hR.blue, hS.alpha - hR.alpha};	

	//Multiply colours.
	hP.red		*=	ui32WordWidth;
	hP.green	*=	ui32WordWidth;
	hP.blue		*=	ui32WordWidth;
	hP.alpha	*=	ui32WordWidth;
	hR.red		*=	ui32WordWidth;
	hR.green	*=	ui32WordWidth;
	hR.blue		*=	ui32WordWidth;
	hR.alpha	*=	ui32WordWidth;
	
	if (ui8Bpp==2)
	{
		//Loop through pixels to achieve results.
		for (unsigned int x=0; x < ui32WordWidth; x++)
		{			
			Pixel128S Result={4*hP.red, 4*hP.green, 4*hP.blue, 4*hP.alpha};
			Pixel128S dY = {hR.red - hP.red, hR.green - hP.green, hR.blue - hP.blue, hR.alpha - hP.alpha};	

			for (unsigned int y=0; y < ui32WordHeight; y++)				
			{
				pPixel[y*ui32WordWidth+x].red   = (PVRTint32)((Result.red   >> 7) + (Result.red   >> 2));
				pPixel[y*ui32WordWidth+x].green = (PVRTint32)((Result.green >> 7) + (Result.green >> 2));
				pPixel[y*ui32WordWidth+x].blue  = (PVRTint32)((Result.blue  >> 7) + (Result.blue  >> 2));
				pPixel[y*ui32WordWidth+x].alpha = (PVRTint32)((Result.alpha >> 5) + (Result.alpha >> 1));				

				Result.red		+= dY.red;
				Result.green	+= dY.green;
				Result.blue		+= dY.blue;
				Result.alpha	+= dY.alpha;
			}			

			hP.red		+= QminusP.red;
			hP.green	+= QminusP.green;
			hP.blue		+= QminusP.blue;
			hP.alpha	+= QminusP.alpha;

			hR.red		+= SminusR.red;
			hR.green	+= SminusR.green;
			hR.blue		+= SminusR.blue;
			hR.alpha	+= SminusR.alpha;
		}
	}
	else
	{
		//Loop through pixels to achieve results.
		for (unsigned int y=0; y < ui32WordHeight; y++)
		{			
			Pixel128S Result={4*hP.red, 4*hP.green, 4*hP.blue, 4*hP.alpha};
			Pixel128S dY = {hR.red - hP.red, hR.green - hP.green, hR.blue - hP.blue, hR.alpha - hP.alpha};	

			for (unsigned int x=0; x < ui32WordWidth; x++)				
			{
				pPixel[y*ui32WordWidth+x].red   = (PVRTint32)((Result.red   >> 6) + (Result.red   >> 1));
				pPixel[y*ui32WordWidth+x].green = (PVRTint32)((Result.green >> 6) + (Result.green >> 1));
				pPixel[y*ui32WordWidth+x].blue  = (PVRTint32)((Result.blue  >> 6) + (Result.blue  >> 1));
				pPixel[y*ui32WordWidth+x].alpha = (PVRTint32)((Result.alpha >> 4) + (Result.alpha));				

				Result.red += dY.red;
				Result.green += dY.green;
				Result.blue += dY.blue;
				Result.alpha += dY.alpha;
			}			

			hP.red += QminusP.red;
			hP.green += QminusP.green;
			hP.blue += QminusP.blue;
			hP.alpha += QminusP.alpha;

			hR.red += SminusR.red;
			hR.green += SminusR.green;
			hR.blue += SminusR.blue;
			hR.alpha += SminusR.alpha;
		}
	}
}

/*!***********************************************************************
 @Function		unpackModulations
 @Input			word				PVRTCWord to be decompressed
 @Input			offsetX				X position within the PVRTCWord
 @Input			offsetY				Y position within the PVRTCWord
 @Modified		i32ModulationValues	The array of modulation values.
 @Modified		i32ModulationModes	The array of modulation modes.
 @Input			ui8Bpp				Number of bpp.
 @Description	Reads out and decodes the modulation values within the a given PVRTCWord
*************************************************************************/
static void unpackModulations(const PVRTCWord& word, int offsetX, int offsetY, PVRTint32 i32ModulationValues[16][8], PVRTint32 i32ModulationModes[16][8], PVRTuint8 ui8Bpp)
{	
	PVRTuint32 WordModMode = word.u32ColourData & 0x1;
	PVRTuint32 ModulationBits = word.u32ModulationData;

	// Unpack differently depending on 2bpp or 4bpp modes.
	if (ui8Bpp==2)
	{
		if(WordModMode)
		{
			// determine which of the three modes are in use:

			// If this is the either the H-only or V-only interpolation mode...
			if(ModulationBits & 0x1)
			{
				// look at the "LSB" for the "centre" (V=2,H=4) texel. Its LSB is now
				// actually used to indicate whether it's the H-only mode or the V-only...

				// The centre texel data is the at (y==2, x==4) and so its LSB is at bit 20.
				if(ModulationBits & (0x1 << 20))
				{
					// This is the V-only mode
					WordModMode = 3; 
				}
				else
				{
					// This is the H-only mode
					WordModMode = 2; 
				}

				// Create an extra bit for the centre pixel so that it looks like
				// we have 2 actual bits for this texel. It makes later coding much easier.
				if(ModulationBits & (0x1 << 21))
				{
					// set it to produce code for 1.0
					ModulationBits |= (0x1 << 20); 
				}
				else
				{
					// clear it to produce 0.0 code
					ModulationBits &= ~(0x1 << 20);
				}
			}// end if H-Only or V-Only interpolation mode was chosen

			if(ModulationBits & 0x2)
			{
				ModulationBits |= 0x1; /*set it*/
			}
			else
			{
				ModulationBits &= ~0x1; /*clear it*/
			}

			// run through all the pixels in the block. Note we can now treat all the
			// "stored" values as if they have 2bits (even when they didn't!)
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					i32ModulationModes[x+offsetX][y+offsetY] = WordModMode;				

					// if this is a stored value...
					if(((x^y)&1) == 0)
					{
						i32ModulationValues[x+offsetX][y+offsetY] = ModulationBits & 3;						
						ModulationBits >>= 2;
					}
				}
			} // end for y
		}
		// else if direct encoded 2bit mode - i.e. 1 mode bit per pixel
		else
		{
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					i32ModulationModes[x+offsetX][y+offsetY] = WordModMode;					

					/*
					// double the bits so 0=> 00, and 1=>11
					*/
					if(ModulationBits & 1)
					{
						i32ModulationValues[x+offsetX][y+offsetY] = 0x3;						
					}
					else
					{
						i32ModulationValues[x+offsetX][y+offsetY] = 0x0;					
					}
					ModulationBits >>= 1;
				}
			}// end for y
		}		
	}
	else
	{
		//Much simpler than the 2bpp decompression, only two modes, so the n/8 values are set directly.
		// run through all the pixels in the word.
		if (WordModMode)
		{
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 4; x++)
				{
					i32ModulationValues[y+offsetY][x+offsetX] = ModulationBits & 3;
					//if (i32ModulationValues==0) {}; don't need to check 0, 0 = 0/8.
					if (i32ModulationValues[y+offsetY][x+offsetX]==1) { i32ModulationValues[y+offsetY][x+offsetX]=4;}
					else if (i32ModulationValues[y+offsetY][x+offsetX]==2) { i32ModulationValues[y+offsetY][x+offsetX]=14;} //+10 tells the decompressor to punch through alpha.
					else if (i32ModulationValues[y+offsetY][x+offsetX]==3) { i32ModulationValues[y+offsetY][x+offsetX]=8;}
					ModulationBits >>= 2;
				} // end for x
			} // end for y
		}
		else
		{
			for(int y = 0; y < 4; y++)
			{
				for(int x = 0; x < 4; x++)
				{
					i32ModulationValues[y+offsetY][x+offsetX] = ModulationBits & 3;
					i32ModulationValues[y+offsetY][x+offsetX]*=3;
					if (i32ModulationValues[y+offsetY][x+offsetX]>3) i32ModulationValues[y+offsetY][x+offsetX]-=1;
					ModulationBits >>= 2;
				} // end for x
			} // end for y
		}
	}
}

/*!***********************************************************************
 @Function		getModulationValues
 @Input			i32ModulationValues	The array of modulation values.
 @Input			i32ModulationModes	The array of modulation modes.
 @Input			xPos				The x Position within the current word.
 @Input			yPos				The y Position within the current word.
 @Input			ui8Bpp				Number of bpp.
 @Return		Returns the modulation value.
 @Description	Gets the effective modulation values for a given pixel.
*************************************************************************/
static PVRTint32 getModulationValues(PVRTint32 i32ModulationValues[16][8],PVRTint32 i32ModulationModes[16][8],PVRTuint32 xPos,PVRTuint32 yPos,PVRTuint8 ui8Bpp)
{
	if (ui8Bpp==2)
	{
		const int RepVals0[4] = {0, 3, 5, 8};				

		// extract the modulation value. If a simple encoding
		if(i32ModulationModes[xPos][yPos]==0)
		{
			return RepVals0[i32ModulationValues[xPos][yPos]];
		}
		else
		{
			// if this is a stored value
			if(((xPos^yPos)&1)==0)
			{
				return RepVals0[i32ModulationValues[xPos][yPos]];				
			}

			// else average from the neighbours
			// if H&V interpolation...
			else if(i32ModulationModes[xPos][yPos] == 1)
			{
				return (RepVals0[i32ModulationValues[xPos][yPos-1]] + 
					RepVals0[i32ModulationValues[xPos][yPos+1]] + 
					RepVals0[i32ModulationValues[xPos-1][yPos]] + 
					RepVals0[i32ModulationValues[xPos+1][yPos]] + 2) / 4;				
			}
			// else if H-Only
			else if(i32ModulationModes[xPos][yPos] == 2)
			{
				return (RepVals0[i32ModulationValues[xPos-1][yPos]] + 
					RepVals0[i32ModulationValues[xPos+1][yPos]] + 1) / 2;
			}
			// else it's V-Only
			else
			{
				return (RepVals0[i32ModulationValues[xPos][yPos-1]] + 
					RepVals0[i32ModulationValues[xPos][yPos+1]] + 1) / 2;
			}
		}
	}
	else if (ui8Bpp==4)
		return i32ModulationValues[xPos][yPos];

	return 0;
}

/*!***********************************************************************
 @Function		pvrtcGetDecompressedPixels
 @Input			P,Q,R,S				PVRTWords in current decompression area.
 @Modified		pColourData			Output pixels.
 @Input			ui8Bpp				Number of bpp.
 @Description	Gets decompressed pixels for a given decompression area.
*************************************************************************/
static void pvrtcGetDecompressedPixels(const PVRTCWord& P, const PVRTCWord& Q, 
								const PVRTCWord& R, const PVRTCWord& S, 
								Pixel32 *pColourData,
								PVRTuint8 ui8Bpp)
{
	//4bpp only needs 8*8 values, but 2bpp needs 16*8, so rather than wasting processor time we just statically allocate 16*8.
	PVRTint32 i32ModulationValues[16][8];
	//Only 2bpp needs this.
	PVRTint32 i32ModulationModes[16][8];
	//4bpp only needs 16 values, but 2bpp needs 32, so rather than wasting processor time we just statically allocate 32.
	Pixel128S upscaledColourA[32];
	Pixel128S upscaledColourB[32];

	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	//Get the modulations from each word.
	unpackModulations(P, 0, 0, i32ModulationValues, i32ModulationModes, ui8Bpp);
	unpackModulations(Q, ui32WordWidth, 0, i32ModulationValues, i32ModulationModes, ui8Bpp);
	unpackModulations(R, 0, ui32WordHeight, i32ModulationValues, i32ModulationModes, ui8Bpp);
	unpackModulations(S, ui32WordWidth, ui32WordHeight, i32ModulationValues, i32ModulationModes, ui8Bpp);

	// Bilinear upscale image data from 2x2 -> 4x4
	interpolateColours(getColourA(P.u32ColourData), getColourA(Q.u32ColourData), 
		getColourA(R.u32ColourData), getColourA(S.u32ColourData), 
		upscaledColourA, ui8Bpp);
	interpolateColours(getColourB(P.u32ColourData), getColourB(Q.u32ColourData), 
		getColourB(R.u32ColourData), getColourB(S.u32ColourData), 
		upscaledColourB, ui8Bpp);

	for (unsigned int y=0; y < ui32WordHeight; y++)
	{
		for (unsigned int x=0; x < ui32WordWidth; x++)
		{
			PVRTint32 mod = getModulationValues(i32ModulationValues,i32ModulationModes,x+ui32WordWidth/2,y+ui32WordHeight/2,ui8Bpp);
			bool punchthroughAlpha=false;
			if (mod>10) {punchthroughAlpha=true; mod-=10;}

			Pixel128S result;				
			result.red   = (upscaledColourA[y*ui32WordWidth+x].red * (8-mod) + upscaledColourB[y*ui32WordWidth+x].red * mod) / 8;
			result.green = (upscaledColourA[y*ui32WordWidth+x].green * (8-mod) + upscaledColourB[y*ui32WordWidth+x].green * mod) / 8;
			result.blue  = (upscaledColourA[y*ui32WordWidth+x].blue * (8-mod) + upscaledColourB[y*ui32WordWidth+x].blue * mod) / 8;
			if (punchthroughAlpha) result.alpha = 0;
			else result.alpha = (upscaledColourA[y*ui32WordWidth+x].alpha * (8-mod) + upscaledColourB[y*ui32WordWidth+x].alpha * mod) / 8;

			//Convert the 32bit precision result to 8 bit per channel colour.
			if (ui8Bpp==2)
			{
				pColourData[y*ui32WordWidth+x].red = (PVRTuint8)result.red;
				pColourData[y*ui32WordWidth+x].green = (PVRTuint8)result.green;
				pColourData[y*ui32WordWidth+x].blue = (PVRTuint8)result.blue;
				pColourData[y*ui32WordWidth+x].alpha = (PVRTuint8)result.alpha;
			}
			else if (ui8Bpp==4)
			{
				pColourData[y+x*ui32WordHeight].red = (PVRTuint8)result.red;
				pColourData[y+x*ui32WordHeight].green = (PVRTuint8)result.green;
				pColourData[y+x*ui32WordHeight].blue = (PVRTuint8)result.blue;
				pColourData[y+x*ui32WordHeight].alpha = (PVRTuint8)result.alpha;				
			}
		}
	}	
}

/*!***********************************************************************
 @Function		wrapWordIndex
 @Input			numWords			Total number of PVRTCWords in the current surface.
 @Input			word				Original index for a PVRTCWord.
 @Return		unsigned int		Wrapped PVRTCWord index.
 @Description	Maps decompressed data to the correct location in the output buffer.
*************************************************************************/
static unsigned int wrapWordIndex(unsigned int numWords, int word)
{
	return ((word + numWords) % numWords);
}

#if defined(_DEBUG)
 /*!***********************************************************************
  @Function		isPowerOf2
  @Input		input	Value to be checked
  @Returns		true if the number is an integer power of two, else false.
  @Description	Check that a number is an integer power of two, i.e.
             	1, 2, 4, 8, ... etc.
				Returns false for zero.
*************************************************************************/
static bool isPowerOf2( unsigned int input )
{
  unsigned int minus1;

  if( !input ) return 0;

  minus1 = input - 1;
  return ( (input | minus1) == (input ^ minus1) );
}
#endif

/*!***********************************************************************
 @Function		TwiddleUV
 @Input			YSize	Y dimension of the texture in pixels
 @Input			XSize	X dimension of the texture in pixels
 @Input			YPos	Pixel Y position
 @Input			XPos	Pixel X position
 @Returns		The twiddled offset of the pixel
 @Description	Given the Word (or pixel) coordinates and the dimension of
 				the texture in words (or pixels) this returns the twiddled
 				offset of the word (or pixel) from the start of the map.

				NOTE: the dimensions of the texture must be a power of 2
*************************************************************************/
static PVRTuint32 TwiddleUV(PVRTuint32 XSize, PVRTuint32 YSize, PVRTuint32 XPos, PVRTuint32 YPos)
{
	//Initially assume X is the larger size.
	PVRTuint32 MinDimension=XSize;
	PVRTuint32 MaxValue=YPos;
	PVRTuint32 Twiddled=0;
	PVRTuint32 SrcBitPos=1;
	PVRTuint32 DstBitPos=1;
	int ShiftCount=0;

	//Check the sizes are valid.
	_ASSERT(YPos < YSize);
	_ASSERT(XPos < XSize);
	//If Y is the larger dimension - switch the min/max values.
	if(YSize < XSize)
	{
		MinDimension = YSize;
		MaxValue	 = XPos;
	}

	// Step through all the bits in the "minimum" dimension
	while(SrcBitPos < MinDimension)
	{
		if(YPos & SrcBitPos)
		{
			Twiddled |= DstBitPos;
		}

		if(XPos & SrcBitPos)
		{
			Twiddled |= (DstBitPos << 1);
		}

		SrcBitPos <<= 1;
		DstBitPos <<= 2;
		ShiftCount += 1;
	}

	// Prepend any unused bits
	MaxValue >>= ShiftCount;
	Twiddled |=  (MaxValue << (2*ShiftCount));

	return Twiddled;
}

/*!***********************************************************************
 @Function		mapDecompressedData
 @Modified		pOutput				The PVRTC texture data to decompress
 @Input			width				Width of the texture surface.
 @Input			pWord				A pointer to the decompressed PVRTCWord in pixel form.
 @Input			&words				Indices for the PVRTCword.
 @Input			ui8Bpp				number of bits per pixel
 @Description	Maps decompressed data to the correct location in the output buffer.
*************************************************************************/
static void mapDecompressedData(Pixel32* pOutput, int width,
						 const Pixel32 *pWord,
						 const PVRTCWordIndices &words,
						 const PVRTuint8 ui8Bpp)
{
	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	for (unsigned int y=0; y < ui32WordHeight/2; y++)
	{
		for (unsigned int x=0; x < ui32WordWidth/2; x++)
		{
			pOutput[(((words.P[1] * ui32WordHeight) + y + ui32WordHeight/2)
				* width + words.P[0] *ui32WordWidth + x + ui32WordWidth/2)]	= pWord[y*ui32WordWidth+x];			// map P

			pOutput[(((words.Q[1] * ui32WordHeight) + y + ui32WordHeight/2)	
				* width + words.Q[0] *ui32WordWidth + x)]					= pWord[y*ui32WordWidth+x+ui32WordWidth/2];		// map Q

			pOutput[(((words.R[1] * ui32WordHeight) + y)						
				* width + words.R[0] *ui32WordWidth + x + ui32WordWidth/2)]	= pWord[(y+ui32WordHeight/2)*ui32WordWidth+x];		// map R

			pOutput[(((words.S[1] * ui32WordHeight) + y)						
				* width + words.S[0] *ui32WordWidth + x)]					= pWord[(y+ui32WordHeight/2)*ui32WordWidth+x+ui32WordWidth/2];	// map S
		}
	}
}
/*!***********************************************************************
 @Function		pvrtcDecompress
 @Input			pCompressedData		The PVRTC texture data to decompress
 @Modified		pDecompressedData	The output buffer to decompress into.
 @Input			ui32Width			X dimension of the texture
 @Input			ui32Height			Y dimension of the texture
 @Input			ui8Bpp				number of bits per pixel
 @Description	Internally decompresses PVRTC to RGBA 8888
*************************************************************************/
static int pvrtcDecompress(	PVRTuint8 *pCompressedData,
							Pixel32 *pDecompressedData,
							PVRTuint32 ui32Width,
							PVRTuint32 ui32Height,
							PVRTuint8 ui8Bpp)
{
	PVRTuint32 ui32WordWidth=4;
	PVRTuint32 ui32WordHeight=4;
	if (ui8Bpp==2)
		ui32WordWidth=8;

	PVRTuint32 *pWordMembers = (PVRTuint32 *)pCompressedData;
	Pixel32 *pOutData = pDecompressedData;

	// Calculate number of words
	int i32NumXWords = (int)(ui32Width / ui32WordWidth);
	int i32NumYWords = (int)(ui32Height / ui32WordHeight);

	// Structs used for decompression
	PVRTCWordIndices indices;
	Pixel32 *pPixels;
	pPixels = (Pixel32*)malloc(ui32WordWidth*ui32WordHeight*sizeof(Pixel32));
	
	// For each row of words
	for(int wordY=-1; wordY < i32NumYWords-1; wordY++)
	{
		// for each column of words
		for(int wordX=-1; wordX < i32NumXWords-1; wordX++)
		{
			indices.P[0] = wrapWordIndex(i32NumXWords, wordX);
			indices.P[1] = wrapWordIndex(i32NumYWords, wordY);
			indices.Q[0] = wrapWordIndex(i32NumXWords, wordX + 1); 
			indices.Q[1] = wrapWordIndex(i32NumYWords, wordY);
			indices.R[0] = wrapWordIndex(i32NumXWords, wordX); 
			indices.R[1] = wrapWordIndex(i32NumYWords, wordY + 1);
			indices.S[0] = wrapWordIndex(i32NumXWords, wordX + 1);
			indices.S[1] = wrapWordIndex(i32NumYWords, wordY + 1);

			//Work out the offsets into the twiddle structs, multiply by two as there are two members per word.
			PVRTuint32 WordOffsets[4] =
			{
				TwiddleUV(i32NumXWords,i32NumYWords,indices.P[0], indices.P[1])*2,
				TwiddleUV(i32NumXWords,i32NumYWords,indices.Q[0], indices.Q[1])*2,
				TwiddleUV(i32NumXWords,i32NumYWords,indices.R[0], indices.R[1])*2,
				TwiddleUV(i32NumXWords,i32NumYWords,indices.S[0], indices.S[1])*2,
			};

			//Access individual elements to fill out PVRTCWord
			PVRTCWord P,Q,R,S;
			P.u32ColourData = pWordMembers[WordOffsets[0]+1];
			P.u32ModulationData = pWordMembers[WordOffsets[0]];
			Q.u32ColourData = pWordMembers[WordOffsets[1]+1];
			Q.u32ModulationData = pWordMembers[WordOffsets[1]];
			R.u32ColourData = pWordMembers[WordOffsets[2]+1];
			R.u32ModulationData = pWordMembers[WordOffsets[2]];
			S.u32ColourData = pWordMembers[WordOffsets[3]+1];
			S.u32ModulationData = pWordMembers[WordOffsets[3]];
							
			// assemble 4 words into struct to get decompressed pixels from
			pvrtcGetDecompressedPixels(P,Q,R,S,pPixels,ui8Bpp);
			mapDecompressedData(pOutData, ui32Width, pPixels, indices, ui8Bpp);
			
		} // for each word
	} // for each row of words

	free(pPixels);
	//Return the data size
	return ui32Width * ui32Height / (PVRTuint32)(ui32WordWidth/2);
}

/*!***********************************************************************
 @Function		PVRTDecompressPVRTC
 @Input			pCompressedData The PVRTC texture data to decompress
 @Input			Do2bitMode Signifies whether the data is PVRTC2 or PVRTC4
 @Input			XDim X dimension of the texture
 @Input			YDim Y dimension of the texture
 @Modified		pResultImage The decompressed texture data
 @Return		Returns the amount of data that was decompressed.
 @Description	Decompresses PVRTC to RGBA 8888
*************************************************************************/
int PVRTDecompressPVRTC(const void *pCompressedData,
				const int Do2bitMode,
				const int XDim,
				const int YDim,
				unsigned char* pResultImage)
{
	//Cast the output buffer to a Pixel32 pointer.
	Pixel32* pDecompressedData = (Pixel32*)pResultImage;

	//Check the X and Y values are at least the minimum size.
	int XTrueDim = PVRT_MAX(XDim,((Do2bitMode==1)?16:8));
	int YTrueDim = PVRT_MAX(YDim,8);

	//If the dimensions aren't correct, we need to create a new buffer instead of just using the provided one, as the buffer will overrun otherwise.
	if(XTrueDim!=XDim || YTrueDim!=YDim)
	{
		pDecompressedData=(Pixel32*)malloc(XTrueDim*YTrueDim*sizeof(Pixel32));
	}
		
	//Decompress the surface.
	int retval = pvrtcDecompress((PVRTuint8*)pCompressedData,pDecompressedData,XTrueDim,YTrueDim,(Do2bitMode==1?2:4));

	//If the dimensions were too small, then copy the new buffer back into the output buffer.
	if(XTrueDim!=XDim || YTrueDim!=YDim)
	{
		//Loop through all the required pixels.
		for (int x=0; x<XDim; ++x)
		{
			for (int y=0; y<YDim; ++y)
			{
				((Pixel32*)pResultImage)[x+y*XDim]=pDecompressedData[x+y*XTrueDim];
			}
		}

		//Free the temporary buffer.
		free(pDecompressedData);
	}
	return retval;
}

/****************************
**	ETC Compression
****************************/

/*****************************************************************************
Macros
*****************************************************************************/
#define _CLAMP_(X,Xmin,Xmax) (  (X)<(Xmax) ?  (  (X)<(Xmin)?(Xmin):(X)  )  : (Xmax)    )

/*****************************************************************************
Constants
******************************************************************************/
unsigned int ETC_FLIP =  0x01000000;
unsigned int ETC_DIFF = 0x02000000;
const int mod[8][4]={{2, 8,-2,-8},
					{5, 17, -5, -17},
					{9, 29, -9, -29},
					{13, 42, -13, -42},
					{18, 60, -18, -60},
					{24, 80, -24, -80},
					{33, 106, -33, -106},
					{47, 183, -47, -183}};

 /*!***********************************************************************
 @Function		modifyPixel
 @Input			red		Red value of pixel
 @Input			green	Green value of pixel
 @Input			blue	Blue value of pixel
 @Input			x	Pixel x position in block
 @Input			y	Pixel y position in block
 @Input			modBlock	Values for the current block
 @Input			modTable	Modulation values
 @Returns		Returns actual pixel colour
 @Description	Used by ETCTextureDecompress
*************************************************************************/
static unsigned int modifyPixel(int red, int green, int blue, int x, int y, unsigned int modBlock, int modTable)
{
	int index = x*4+y, pixelMod;
	unsigned int mostSig = modBlock<<1;

	if (index<8)
		pixelMod = mod[modTable][((modBlock>>(index+24))&0x1)+((mostSig>>(index+8))&0x2)];
	else
		pixelMod = mod[modTable][((modBlock>>(index+8))&0x1)+((mostSig>>(index-8))&0x2)];

	red = _CLAMP_(red+pixelMod,0,255);
	green = _CLAMP_(green+pixelMod,0,255);
	blue = _CLAMP_(blue+pixelMod,0,255);

	return ((red<<16) + (green<<8) + blue)|0xff000000;
}


