//
//  FrameBuffer.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 08.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
#ifndef FRAMEBUFFER_H__
#define FRAMEBUFFER_H__

#include "Types.h"
#include "mathLib.h"
#include <math.h>
#include "Texture.h"


enum {
    BUFFER_FORMAT_DEPTH = 1,
    BUFFER_FORMAT_STENSIL = 2
};

class FrameBuffer{
private:
    int width;
    int height;
    uint frameBuffer,renderBuffer;
    uint typeRender;
    uint bufferData;
public:
    FrameBuffer();
    ~FrameBuffer(){};
    
    
    
    void attachTexture(Texture* texture);
    void create(int width,int height,uint typeRenderBuffer);
    void bind ();
    void unbind ();
};


#endif