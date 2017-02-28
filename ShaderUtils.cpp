//
//  ShaderUtils.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 14.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "ShaderUtils.h"
/*GetShader( Material * mtl, Mesh * mesh, int pass ) 
 { 
 StrID shader_name = ShaderLib.Get( mtl->shader_id, pass ); 
 return ShaderCache.Get( shader_name,  // "water_cbm.fx" 
 mtl->flags,                                //  alpha blend 
 mesh->vertex_format,            //  skinned, normal, 1 texcoord 
 pass                                        //  backbuffer 
 ); 
 }*/








Shader* getShader(Material*mtl,Mesh*mesh,int pass){
    return ShaderCache::me()->get(mtl,mesh,pass);
}