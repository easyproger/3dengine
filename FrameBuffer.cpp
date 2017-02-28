//
//  FrameBuffer.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 08.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "FrameBuffer.h"
#include "XTypes.h"



FrameBuffer::FrameBuffer(){
    
    
    
    
    
    
}


void FrameBuffer::create(int width,int height,uint typeRenderBuffer){
    this->typeRender = typeRenderBuffer;
    this->width      = width;
    this->height     = height;
    
    glGenFramebuffers(1, &frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    
    
    if (typeRenderBuffer & BUFFER_FORMAT_DEPTH) {
        glGenRenderbuffers(1, &renderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
        glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    }
    if (typeRenderBuffer & BUFFER_FORMAT_STENSIL) {
        glGenRenderbuffers(1, &renderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer (GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
    }
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}


void FrameBuffer::attachTexture(Texture* texture){
    bufferData = texture->getTextureID();
    
    glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->getTextureFormat(), bufferData, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
}





void FrameBuffer::bind ()
{
    glBindFramebuffer (GL_FRAMEBUFFER, frameBuffer);
    
}

void FrameBuffer::unbind ()
{
    glBindFramebuffer (GL_FRAMEBUFFER, 0);
    
}