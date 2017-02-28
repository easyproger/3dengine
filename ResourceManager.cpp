//
//  ResourceManager.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 15.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "ResourceManager.h"

ResourcesManager::ResourcesManager(){
    initialized = false;
}



void ResourcesManager::init(char*shadersURL){
    initialized = true;
    shaderURL = shadersURL;
}


char* ResourcesManager::getShadersURL(){
    if (!initialized) {
        printf("resourceManager not initialized invoke first init");
        return (char*)"";
    }
    return (char*)shaderURL.c_str();
}



void ResourcesManager::loadImage(Texture *texture,const char*fileName){
    TGAImage::me()->LoadTGA(texture, fileName);
}


int ResourcesManager::readShaderSource(char * fileName, char** shader)
{
    if (!initialized) {
        printf("resourceManager not initialized invoke first init");
        return -1;
    }
    // Allocate memory to hold the source of our shaders.
    FILE *fp;
    int count, pos, shaderSize;

    fp = fopen( fileName, "r");
    if ( !fp )
        return 0;
	
    pos = (int) ftell ( fp );
    fseek ( fp, 0, SEEK_END );			//move to end
    shaderSize = ( int ) ftell ( fp ) - pos;	//calculates file size	
    fseek ( fp, 0, SEEK_SET ); 			//rewind to beginning
	
    if ( shaderSize <= 0 ){
        printf("Shader %s empty\n", fileName);
        fclose(fp);
        return 0;
    }
	
    *shader = (char *) malloc( shaderSize + 1);
    
    // Read the source code
	
    count = (int) fread(*shader, 1, shaderSize, fp);
    (*shader)[count] = '\0';
	
    if (ferror(fp))
        count = 0;
        
    fclose(fp);
    return 1;
}