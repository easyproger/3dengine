//
//  TextureCache.cpp
//  UltraVision
//
//  Created by easy proger on 27.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "TextureCache.h"


TextureCache::TextureCache() {
    _textureCache[""] = 0; // default value !
    
}




void TextureCache::correctCache() {
    typedef std::map<std::string,Texture*>::iterator it_type;
    for(it_type iterator = _textureCache.begin(); iterator != _textureCache.end(); iterator++) {
        Texture*tex = iterator->second;
        if (tex) {
            tex->releaseTexture();
        }
    }
}


Texture* TextureCache::getTextureByPath(std::string path) {
    
    Texture* texture = 0;
    if (_textureCache.find(path) != _textureCache.end()) {
        if (_textureCache[path]) {
            texture = _textureCache[path];
        }
    }else {
        Texture*tex = new Texture();
        int ret = tex->createTexture(path);
        if (ret) {
            texture = tex;
            _textureCache[path] = tex;
        }
    }
    return texture;
}