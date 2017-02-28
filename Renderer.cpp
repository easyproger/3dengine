//
//  Renderer.cpp
//  XTech
//
//  Created by easy proger on 07.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#include "Renderer.h"




Renderer::~Renderer() {
    
}

Renderer::Renderer(Camera*camera) {
   




    
    Texture* depthTexture = new Texture();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	depthTexture->createClearTexture(WIDTH_SHADOW_MAP, HEIGHT_SHADOW_MAP, GL_TEXTURE_2D, GL_R32F, GL_RED, GL_FLOAT);
#else
    depthTexture->createClearTexture(WIDTH_SHADOW_MAP, HEIGHT_SHADOW_MAP, GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_HALF_FLOAT_OES);
#endif


	   
    depthFrameBuffer = new FrameBuffer();
    depthFrameBuffer->create(WIDTH_SHADOW_MAP, HEIGHT_SHADOW_MAP, BUFFER_FORMAT_DEPTH);
    depthFrameBuffer->attachTexture(depthTexture);
    
    shaderParamsSetter = new ShaderParamsSetter(camera,
                                                depthTexture->getTextureID(),
                                                0,
                                                0,
                                                0);
    
    
    action[LIGHT_PRE_PASS_RENDERER][SHADOW_DEPTH_TEHNICS] = &Renderer::renderToShadowMap;
    action[LIGHT_PRE_PASS_RENDERER][BACK_BUFFER_TEHNICS] = &Renderer::renderToShadowMap;
    action[LIGHT_PRE_PASS_RENDERER][CUSTOM_TEHNICS] = &Renderer::renderToShadowMap;
    
    
    action[FORWARD_RENDERER][SHADOW_DEPTH_TEHNICS] = &Renderer::renderToShadowMap;
    action[FORWARD_RENDERER][BACK_BUFFER_TEHNICS] = &Renderer::renderBackBufferFR;
    action[FORWARD_RENDERER][CUSTOM_TEHNICS] = &Renderer::renderToShadowMap;
    
    
    
    GET_GLERROR();
}

void Renderer::setDefaultBuffer(uint bufferID) {
    mDefaultFrameBuffer = bufferID;
}
void Renderer::setDefaultSceneGraph(SceneGraph* sceneGraph) {
    defaultSceneGraph = sceneGraph;
}

void Renderer::renderBackBufferFR(XQuery* query) {

    glBindFramebuffer(GL_FRAMEBUFFER, mDefaultFrameBuffer);
    
    
#if SHOW_AR
    glViewport(viewport[0], viewport[1],viewport[2]   ,viewport[3] );
#else
    glViewport(0, 0,WIDTH_VIEWPORT   ,HEIGHT_VIEWPORT );
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
#endif

    
    glEnable(GL_DEPTH_TEST);
    
    uint lastShaderID = 0;
    
    if (defaultSceneGraph->listLights.size() > 0) {
        Light* defaultLight = defaultSceneGraph->listLights[0];
        shaderParamsSetter->setLight(defaultLight);
    }
    
    for (unsigned int i=0;i<query->size;i++)
    {
        SceneNode* node = query->list[i];
        Mesh* model = node->getMesh();
        // XTODO : hackVisible object and damaged ! need some normal idea !
        if (!node->isVisible || model->isDamaged) continue;
        
        
        Shader* shader = node->getShaderObject(BACK_BUFFER_TEHNICS);
        
        shaderParamsSetter->setRenderObject(node);
        
        if (lastShaderID != shader->idProgram) {
            lastShaderID = shader->idProgram;
            glUseProgram(lastShaderID);
        }
        
        
        
        
        for (unsigned int chunkI = 0; chunkI < model->numChunks; chunkI++) {
            
            glBindBuffer(GL_ARRAY_BUFFER, model->vertexBufferID[chunkI]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBufferID[chunkI]);
            
            
            for (unsigned int u=0; u<shader->uniformsLenght; u++) {
                (shaderParamsSetter->*shader->uniforms[u].action)(shader->uniforms[u].idUniform);
            }
            for (unsigned int a=0; a<shader->attributesLenght; a++) {
                
                glEnableVertexAttribArray(shader->attributes[a].idAttribute);
                glVertexAttribPointer(shader->attributes[a].idAttribute,
                                      shader->attributes[a].size,
                                      shader->attributes[a].type,
                                      shader->attributes[a].normalized,
                                      model->sizeVertex,
                                      model->offsets[chunkI][shader->attributes[a].idAttributeConstant]);
            }
            
            
            // XTODO : GL_UNSIGNED_SHORT !
            glDrawElements(GL_TRIANGLES, model->numFacesC[chunkI]*3, GL_UNSIGNED_INT, model->indexOffset[chunkI]);
            for (unsigned int a=0; a<shader->attributesLenght; a++) {
                glDisableVertexAttribArray(shader->attributes[a].idAttribute);
            }
        }
    }
        
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
 
}


void Renderer::changeShadowRender(int type) {
    switch (type) {
        case 0:
            action[FORWARD_RENDERER][SHADOW_DEPTH_TEHNICS] = &Renderer::renderToShadowMap;
            break;
        case 1:
            action[FORWARD_RENDERER][SHADOW_DEPTH_TEHNICS] = &Renderer::nop;
            break;
        default:
            break;
    }
}






void Renderer::nop(XQuery* query) {
    
}
void Renderer::renderToShadowMap(XQuery* query) {

    depthFrameBuffer->bind();
    glViewport(0, 0, WIDTH_SHADOW_MAP, HEIGHT_SHADOW_MAP);
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    
    // XTODO: cull facing posible slower (( 
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 2.0);
    
    uint lastShaderID = 0;
    
    
    Light* defaultLight = defaultSceneGraph->listLights[0];
    shaderParamsSetter->setLight(defaultLight);
    
    for (unsigned int i=0;i<query->size;i++)
    {
        SceneNode* node = query->list[i];
        Mesh* model = node->getMesh();
        
        if (!node->isVisible ) continue;
        
        Shader* shader = node->getShaderObject(SHADOW_DEPTH_TEHNICS);
        
        shaderParamsSetter->setRenderObject(node);
        
        if (lastShaderID != shader->idProgram) {
            lastShaderID = shader->idProgram;
            glUseProgram(lastShaderID);
        }
        
        for (unsigned int chunkI = 0; chunkI < model->numChunks; chunkI++) {
            
            glBindBuffer(GL_ARRAY_BUFFER, model->vertexBufferID[chunkI]);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->indexBufferID[chunkI]);
            
            
            for (unsigned int u=0; u<shader->uniformsLenght; u++) {
                (shaderParamsSetter->*shader->uniforms[u].action)(shader->uniforms[u].idUniform);
            }
            for (unsigned int a=0; a<shader->attributesLenght; a++) {
                
                glEnableVertexAttribArray(shader->attributes[a].idAttribute);
                glVertexAttribPointer(shader->attributes[a].idAttribute,
                                      shader->attributes[a].size,
                                      shader->attributes[a].type,
                                      shader->attributes[a].normalized,
                                      model->sizeVertex,
                                      model->offsets[chunkI][shader->attributes[a].idAttributeConstant]);
            }
            
            
            // XTODO : GL_UNSIGNED_SHORT !
            glDrawElements(GL_TRIANGLES, model->numFacesC[chunkI]*3, GL_UNSIGNED_INT, model->indexOffset[chunkI]);
            for (unsigned int a=0; a<shader->attributesLenght; a++) {
                glDisableVertexAttribArray(shader->attributes[a].idAttribute);
            }
        }
    }
    
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    glDisable(GL_CULL_FACE);
    glDisable(GL_POLYGON_OFFSET_FILL);
    
    depthFrameBuffer->unbind();
 
}


void Renderer::render() {
#if SHOW_AR
    glGetIntegerv(GL_VIEWPORT, viewport);
#endif
    
    SceneChildsController*ch = defaultSceneGraph->childController;
    XQuery*querys = ch->querys;
    for (unsigned int i = 0; i<ch->sizeQuerys; i++) {
        (this->*action[querys[i].renderID][querys[i].queryID])(&querys[i]);
    }
}