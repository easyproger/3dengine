//
//  Material.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 14.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
#ifndef MATERIAL_H_DEF
#define MATERIAL_H_DEF
#include <iostream>
#include "Types.h"
#include "FlagsForShaderCompile.h"
#include "Texture.h"


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <GL/glew.h>
#else

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif


class Material {
private:
public:
    
    Texture* diffuseTexture;
    Texture* normalMapTexture;
    Texture* specularTexture;
    
    Material(bool useBaseTexture = true);
    ~Material(){};
    uint shader_id;
    uint flags;
    bool validate();
    void reloadTextures();
};

#endif