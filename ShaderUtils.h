//
//  ShaderUtils.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 14.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//



#ifndef SHADERUTILS_H
#define SHADERUTILS_H

#include "Material.h"
#include "Mesh.h"
#include "ShaderLib.h"
#include "ShaderCache.h"

Shader* getShader(Material*mtl,Mesh*mesh,int pass);

#endif 