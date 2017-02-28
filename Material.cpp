//
//  Material.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 14.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//

#include "Material.h"
#include "Texture.h"

Material::Material(bool useBaseTexture) {
    flags = NORMAL_MATERIAL;
    shader_id = 0;
    if (useBaseTexture) {
        // XTODO : create texture Cache !!!! and get cached base texture here !!! 
        
    }else {
        diffuseTexture = NULL;
    }
}

bool Material::validate() {
    bool matValid = true;
    if (this->diffuseTexture) {
        matValid = matValid && !this->diffuseTexture->isDamaged();
    }
    if (this->specularTexture) {
        matValid = matValid && !this->specularTexture->isDamaged();
    }
    if (this->normalMapTexture) {
        matValid = matValid && !this->normalMapTexture->isDamaged();
    }
    return matValid;
}

void Material::reloadTextures() {
    if (this->diffuseTexture && this->diffuseTexture->isDamaged()) {
        this->diffuseTexture->reloadTexture();
    }
    if (this->specularTexture && this->specularTexture->isDamaged()) {
        this->specularTexture->reloadTexture();
    }
    if (this->normalMapTexture && this->normalMapTexture->isDamaged()) {
        this->normalMapTexture->reloadTexture();
    }
}


/*
 // initialising the flags
 // note that assignming a value will clobber any other flags, so you
 // should generally only use the = operator when initialising vars.
 flags = LOG_ERRORS;
 // sets to 1 i.e. bit 0
 
 //initialising to multiple values with OR (|)
 flags = LOG_ERRORS | LOG_WARNINGS | LOG_INCOMING;
 // sets to 1 + 2 + 8 i.e. bits 0, 1 and 3
 
 // setting one flag on, leaving the rest untouched
 // OR bitmask with the current value
 flags |= LOG_INCOMING;
 
 // testing for a flag
 // AND with the bitmask before testing with ==
 if ((flags & LOG_WARNINGS) == LOG_WARNINGS)
 ...
 
 // testing for multiple flags
 // as above, OR the bitmasks
 if ((flags & (LOG_INCOMING | LOG_OUTGOING))
 == (LOG_INCOMING | LOG_OUTGOING))
 ...
 
 // removing a flag, leaving the rest untouched
 // AND with the inverse (NOT) of the bitmask
 flags &= ~LOG_OUTGOING; убрать
 
 // toggling a flag, leaving the rest untouched
 flags ^= LOG_LOOPBACK; включить/выключить
 
 */