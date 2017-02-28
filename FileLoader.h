//
//  FileLoader.h
//  
//
//  Created by easy proger on 05.07.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef ____FileLoader__
#define ____FileLoader__

#include <iostream>
#include "MeshCache.h"
#include "XAnimation.h"




using namespace Xengine;

class FileLoader {
public:
    FileLoader(MeshCache*meshCache);
    
    
    //
    void loadSceneAnimations(const char*path,std::vector<XAnimation*>*anims,std::vector<int>*indexs);
    void loadScene(const char*path,std::vector<Mesh*>*meshs,std::vector<int>*indexs);
	void writeEditorData(Mesh*model);
    void reloadChunkInMesh(Mesh*model);
    int getTypeMesh(const char* path,int indexMesh);
    XAnimation * loadAnimationFile(const char* pathFile,int indexAnimation);
    void loadAnimationFile(const char* pathFile,int indexAnim,XAnimation*anim);
    
private:
	XAnimation* loadAnimation(FILE*file);
    XAnimation* loadAnimation(FILE*file,XAnimation*anim) ;
	void loadOffsets(FILE*file,int numMeshes,std::vector<int>*offsets);
	void fillGPU(Mesh*model);
    MeshCache*_meshCache;
    std::string loadStaticMesh(FILE*file,Mesh*model,bool reload = false);
};





#endif /* defined(____FileLoader__) */
