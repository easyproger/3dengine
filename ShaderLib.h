//
//  ShaderLib.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 14.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
#ifndef SHADER_LIB_H__
#define SHADER_LIB_H__

#define NORMAL_PASS 1
#define DEPTH_PASS  2
#define LIGHT_PASS  3
#define FINAL_LPP_PASS  4
#define SHADOWMAPS_DEPTH_PASS 5
#define CASCADED_SHADOWMAPS_DEPTH_PASS 6


#define TEST_COLOR_PASS 9



#include "stdlib.h"
#include "XSingleton.h"
#include "Types.h"
#include <string>
#include "Material.h"
#include "Mesh.h"
#include "FlagsForShaderCompile.h"
#include <vector>
#include <iostream>

using namespace Xengine;
using namespace std;




class ShaderLib: public XSingleton<ShaderLib>
{
    uint allocatedLibrarysShader;
    
public:
    
    void get(Material*mat ,Mesh*model, uint pass,vector<string> *outList);
    ShaderLib();
    ~ShaderLib(){};
};

#endif