#ifndef __TGA_H__
#define __TGA_H__

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <GL/glew.h>
#else
#include <OpenGLES/ES2/gl.h>
#endif

#include "stdlib.h"
#include "stdio.h"

#include <string>
#include "XSingleton.h"
#include "Texture.h"



using namespace std;
using namespace Xengine;

typedef struct
{
	GLubyte Header[12];									// TGA File Header
} TGAHeader;


struct  TgaHeader
{
    byte    idLength;
    byte    colormapType;
    byte    imageType;
    uint16  colormapIndex;
    uint16  colormapLength;
    
    uint16  xOrigin;
    uint16  yOrigin;
    uint16  width;
    uint16  height;
    byte    pixelSize;
    byte    imageDesc;
};


typedef struct
{
	GLubyte		header[6];								// First 6 Useful Bytes From The Header
	GLuint		bytesPerPixel;							// Holds Number Of Bytes Per Pixel Used In The TGA File
	GLuint		imageSize;								// Used To Store The Image Size When Setting Aside Ram
	GLuint		temp;									// Temporary Variable
	GLuint		type;	
	GLuint		Height;									//Height of Image
	GLuint		Width;									//Width ofImage
	GLuint		Bpp;									// Bits Per Pixel
} TGA;

class TGAImage: public XSingleton<TGAImage> {
    byte  * bits;
	int		length;
	int		pos;
	string	file;
public:
    TGAImage(){};
    ~TGAImage(){};

    TGAHeader tgaheader;									// TGA header
    TGA tga;
    Texture * load (Texture * texture, TgaHeader*tgaHeader );
    
    bool LoadTGA(Texture * texture, const char * filename);
    bool LoadUncompressedTGA(Texture *, const char *, FILE *);	// Load an Uncompressed file
    bool LoadCompressedTGA(Texture *, const char *, FILE *);
};




												// TGA image data



	// Compressed TGA Header

#endif
