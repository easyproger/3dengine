//
//  TextureCache.h
//
//
//  Created by easy proger on 27.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __TextureCache__
#define __TextureCache__

#include <stdio.h>
#include <iostream>
#include <map>
#include "XMathBase.h"
#include "Texture.h"


class TextureCache {
public:
    TextureCache();
    ~TextureCache() {
        
    };
    Texture* getTextureByPath(std::string path);
    void correctCache();
private:
    
    std::map<std::string,Texture*> _textureCache;
};



#endif /* defined(__TextureCache__) */
