//
//  ResourceManager.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 15.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
#ifndef RESOURCEMANAGER_H__
#define RESOURCEMANAGER_H__

#include "XSingleton.h"
#include "stdio.h"
#include "stdlib.h"
#include <string>
#include "TGAImage.h"


using namespace std;
using namespace Xengine;
class ResourcesManager: public XSingleton<ResourcesManager> {
private:
    bool initialized;
    string shaderURL;
public:
    void loadImage(Texture *texture,const char*fileName);
    void init(char*shadersURL);
    int readShaderSource(char * fileName, char** shader);
    char*getShadersURL();
    ResourcesManager();
    ~ResourcesManager(){};
};


#endif