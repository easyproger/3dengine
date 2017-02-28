//
//  ShaderCache.cpp
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 15.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include "ShaderCache.h"
#include "XMathBase.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <algorithm>
#endif


ShaderCache::ShaderCache(){
    attributesTableLenght = 20;

    string shaderDeclarationTableURL;
    shaderDeclarationTableURL = ResourcesManager::me()->getShadersURL();
    shaderDeclarationTableURL+= "shaderDeclarationTable.xml";
    declorationTableXML.load_file(shaderDeclarationTableURL.c_str());
    

    action[UNIFORM_PERSPECTIVE_MATRIX]              = &ShaderParamsSetter::setPerspectiveMatrixUniform;
    action[UNIFORM_CAMERA_VIEW_MATRIX]              = &ShaderParamsSetter::setCameraViewMatrixUniform;
    action[UNIFORM_WORLD_OBJECT_POSITION]           = &ShaderParamsSetter::setWorldObjectMatrixUniform;
    action[UNIFORM_FAR_PLANE]                       = &ShaderParamsSetter::setFarPlaneUniform;
    action[UNIFORM_MODEL_NORMAL_MATRIX]             = &ShaderParamsSetter::setModelNormalMatrixUniform;
    action[UNIFORM_LIGHT_POSITION]                  = &ShaderParamsSetter::setLightPositionUniform;
    action[UNIFORM_DEPTH_TEXTURE]                   = &ShaderParamsSetter::setDepthBufferUniform; 
    action[UNIFORM_CAMERA_VIEW_INVERSE3]            = &ShaderParamsSetter::setCameraViewInverse3x3Uniform; 
    action[UNIFORM_CAMERA_POSITION]                 = &ShaderParamsSetter::setCameraPositionUniform;
    action[UNIFORM_OBJECT_DIFFUSE_TEXTURE]          = &ShaderParamsSetter::setObjectDiffuseTextureUniform;
    action[UNIFORM_PERSPECTIVE_VIEW_INVERSE_MATRIX] = &ShaderParamsSetter::setPerspectiveViewInverseUniform;
    action[UNIFORM_NORMAL_MATERIAL_TEXTURE]         = &ShaderParamsSetter::setNormalAndMaterialBufferUniform;
    action[UNIFORM_ALBEDO_TEXTURE]                  = &ShaderParamsSetter::setAlbedoBufferUniform;
    action[UNIFORM_LIGHT_TEXTURE]                   = &ShaderParamsSetter::setLightBufferUniform;
    action[UNIFORM_PERSPECTIVE_LIGHT_MATRIX]        = &ShaderParamsSetter::setPerspectiveLightMatrixUniform;
    action[UNIFORM_LIGHT_VIEW_MATRIX]               = &ShaderParamsSetter::setLightViewMatrixUniform;
    action[UNIFORM_LIGHT_PROJ_MODEL_VIEW_MATRIX]    = &ShaderParamsSetter::setLightProjViewMatrixUniform;
    action[UNIFORM_LIGHT_PROJ_MODEL_VIEW_ST_MATRIX] = &ShaderParamsSetter::setLightProjViewMatrixSTUniform;
    action[UNIFORM_PROJ_CAMERA_MODEL_VIEW]          = &ShaderParamsSetter::setProjCameraModelViewUniform;
    action[UNIFORM_BONES_TRANSLATIONS]              = &ShaderParamsSetter::setBonesTranslations;
    action[UNIFORM_BONES_ROTATIONS]                 = &ShaderParamsSetter::setBonesRotations;
    action[UNIFORM_NORMAL_MAP]                      = &ShaderParamsSetter::setObjectNormalMapTextureUniform;
    action[UNIFORM_SPECULAR_MAP]                    = &ShaderParamsSetter::setObjectSpecularMapTextureUniform;
}



Shader* ShaderCache::get(Material*mat ,Mesh*model, uint pass){
    
    
    
    
    uint udidint = (mat->shader_id) | (mat->flags << 8) | model->vertexDeclaration << 16 | pass << 24;
    char str[16];
    itostr(udidint, str);
    uid = str;
    
    Shader* sds = shadersCache[uid];
    if (sds) {
        return sds;
    }
    
    shadersCache[uid] = createShader(mat ,model, pass);
    
    return shadersCache[uid];
    
}

bool sortShaderSections(const pugi::xml_node &a, const pugi::xml_node &b)
{
    if (!a.attribute("zIndex").empty() && !b.attribute("zIndex").empty()) {
        return a.attribute("zIndex").as_uint() < b.attribute("zIndex").as_uint();
    }
    return true;
}

bool sortCodeSections(const CodeMap *a,const CodeMap *b) {
    return a->id<b->id;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}


Shader* ShaderCache::createShader(Material*mat ,Mesh*model, uint pass){
    
	vertexShaderSource = "";
    varyingsBlock      = "";
    codeHeader         = "";
    attributesBlock    = "";
    uniformsBlock      = "";
    pixelShaderSource  = "";
    extensionBlock     = "";
    
    
    string colorPrefix = "";
#if defined(TARGET_iOS)
    positionBlock      = "highp vec4 position;";
    colorPrefix        = "highp";
#else
    positionBlock      = "vec4 position;";
#endif
    
    
    vector<string> shaderList;
    ShaderLib::me()->get(mat,model,pass,&shaderList);
    
    char*shadersPath = ResourcesManager::me()->getShadersURL();
    
    string shaderXMLSource;
    string shaderpath;
    for (uint i = 0; i < shaderList.size(); i++) {
        FILE *fp;
        int count, pos, shaderSize;
        char*shaderXMLsrc;
        
        shaderpath = shaderList[i];
        shaderpath.insert(0, shadersPath, strlen(shadersPath));
        
        fp = fopen( shaderpath.c_str(), "r");
        if ( !fp )
            return 0;
        
        pos = (int) ftell ( fp );
        fseek ( fp, 0, SEEK_END );			//move to end
        shaderSize = ( int ) ftell ( fp ) - pos;	//calculates file size
        fseek ( fp, 0, SEEK_SET ); 			//rewind to beginning
        
        if ( shaderSize <= 0 ){
            continue;
        }
        
        shaderXMLsrc = (char *) malloc(shaderSize + 1);
        
        // Read the source code
        count = (int) fread(shaderXMLsrc, 1, shaderSize, fp);
        shaderXMLsrc[count] = '\0';
        
        if (ferror(fp))
            count = 0;
        fclose(fp);
        
        shaderXMLSource+=shaderXMLsrc;
        free(shaderXMLsrc);
    }
    
    replaceAll(shaderXMLSource,"<![CDATA[","");
    replaceAll(shaderXMLSource,"]]>","");
    
    replaceAll(shaderXMLSource,"<code>","<code><![CDATA[");
    replaceAll(shaderXMLSource,"</code>","]]></code>");
    
    replaceAll(shaderXMLSource,"<functions>","<functions><![CDATA[");
    replaceAll(shaderXMLSource,"</functions>","]]></functions>");
    
    shaderXML.load(shaderXMLSource.c_str());
    
    //shaderXML.load_file("/code/XTech/XTech/shaders/baseShading.xml"); // old path to loading shaders source
    
    
    attributesLenght = 0;
    
    uniforms = 0;
    attributes = 0;
    
    // FillVertexShader version 1 ))) 
    
    vector<CodeMap*> nodes;
    
    map<uint, string> codeMap;
    
    uint i = 0;
    for (pugi::xml_node vertextShaderSection = shaderXML.child("vertexShader"); vertextShaderSection; vertextShaderSection = vertextShaderSection.next_sibling("vertexShader"))
    {
        fillUniforms(&vertextShaderSection);
        fillAttributes(&vertextShaderSection);
        fillVaryings(&vertextShaderSection);
        fillExtensions(&vertextShaderSection);
        fillLocalVars(&vertextShaderSection);
        
        uint zIndex = i;
        if (!vertextShaderSection.attribute("zIndex").empty()) {
            zIndex = vertextShaderSection.attribute("zIndex").as_uint();
        }
        
        CodeMap* codemap = new CodeMap();
        codemap->id = zIndex;
        codemap->code = vertextShaderSection.child("code").child_value();
        nodes.push_back(codemap);
        i++;
    }
    // sort vertext sections by zIndex
    
    std::sort(nodes.begin(), nodes.end(), sortCodeSections);
    
    
    vertexShaderSource+=extensionBlock;
    vertexShaderSource+=uniformsBlock;
    vertexShaderSource+=attributesBlock;
    vertexShaderSource+=varyingsBlock;
    
    
    for (pugi::xml_node vertextShaderSection = shaderXML.child("vertexShader"); vertextShaderSection; vertextShaderSection = vertextShaderSection.next_sibling("vertexShader"))
    {
        vertexShaderSource+=vertextShaderSection.child("functions").child_value();
    }
    
    
    
    
    // Fill main code
    
    vertexShaderSource+=(string)"\n void main(void)\n{\n"+positionBlock+"\n"; // Open Main section
    vertexShaderSource+=codeHeader;
    
    for (uint i = 0;i<nodes.size();i++)
    {
        CodeMap* codemap = nodes[i];
        vertexShaderSource+=codemap->code;
    }
    vertexShaderSource+=(string)"\n gl_Position = position;\n"; // set final position
    vertexShaderSource+=(string)"\n}"; // close main section

    // FillPixelShaders version 1 ))) 
    
    uniformsBlock="";
    
    for (uint i = 0;i<nodes.size();i++)
    {
        CodeMap* codemap = nodes[i];
        delete codemap;
    }
    nodes.clear();
    
    
    
    
    codeHeader = "";
    
    uint iF = 0;
    for (pugi::xml_node pixelShaderSection = shaderXML.child("fragmentShader"); pixelShaderSection; pixelShaderSection = pixelShaderSection.next_sibling("fragmentShader"))
    {
        fillUniforms(&pixelShaderSection);
        fillExtensions(&pixelShaderSection);
        fillLocalVars(&pixelShaderSection);
        uint zIndex = i;
        if (!pixelShaderSection.attribute("zIndex").empty()) {
            zIndex = pixelShaderSection.attribute("zIndex").as_uint();
        }
        CodeMap* codemap = new CodeMap();
        codemap->id = zIndex;
        codemap->code = pixelShaderSection.child("code").child_value();
        nodes.push_back(codemap);

        iF++;
    }
    std::sort(nodes.begin(), nodes.end(), sortCodeSections);
  
    
    pixelShaderSource+=extensionBlock;
    pixelShaderSource+=uniformsBlock;
    pixelShaderSource+=varyingsBlock;
    
    
    for (pugi::xml_node pixelShaderSection = shaderXML.child("fragmentShader"); pixelShaderSection; pixelShaderSection = pixelShaderSection.next_sibling("fragmentShader"))
    {
        pixelShaderSource+=pixelShaderSection.child("functions").child_value();
    }
    
    
    pixelShaderSource+=(string)"\n void main(void)\n{\n "+colorPrefix+" vec4 color;"; // open Fragment main code
    pixelShaderSource+=codeHeader;
    for (uint i = 0;i<nodes.size();i++)
    {
        CodeMap* codemap = nodes[i];
        pixelShaderSource+=codemap->code;
    }
    
    pixelShaderSource+=(string)"\n gl_FragColor = color;\n"; // final set color
    pixelShaderSource+=(string)"\n}"; // close fragment main code

    
    for (uint i = 0;i<nodes.size();i++)
    {
        CodeMap* codemap = nodes[i];
        delete codemap;
    }
    nodes.clear();

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
	replaceAll(vertexShaderSource,"highp ","");
	replaceAll(pixelShaderSource,"highp ","");
#endif
	#if X_DEBUG_SHADERS
    cout<<vertexShaderSource<<endl;
    cout<<pixelShaderSource<<endl;
#endif
    return createShaderProgram(vertexShaderSource.c_str(),pixelShaderSource.c_str(),model);
}

Shader* ShaderCache::createShaderProgram(const char*vertexSource,const char*pixelSource,Mesh*model){
    GLuint program;
	
	GLuint vShaderName,fShaderName;

	GLint logLength, status;
	
    program = glCreateProgram();

    
	vShaderName = glCreateShader(GL_VERTEX_SHADER);
	fShaderName = glCreateShader(GL_FRAGMENT_SHADER);
    
	glShaderSource(vShaderName, 1, (const GLchar**)&vertexSource, NULL);
    glShaderSource(fShaderName, 1, (const GLchar**)&pixelSource,  NULL);
    
	glCompileShader(vShaderName);
    glGetShaderiv(vShaderName, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) 
	{
		GLchar *log = (GLchar*) malloc(logLength);
		glGetShaderInfoLog(vShaderName, logLength, &logLength, log);
		printf("Vtx Shader compile log:%s\n", log);
		free(log);
	}
    glGetShaderiv(vShaderName, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		printf("Failed to compile vtx shader:\n%s\n",vertexSource);
		return 0;
	}
    
    glAttachShader(program, vShaderName);
    
    
	glCompileShader(fShaderName);
    glGetShaderiv(fShaderName, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0) 
	{
		GLchar *log = (GLchar*)malloc(logLength);
		glGetShaderInfoLog(fShaderName, logLength, &logLength, log);
		printf("Frag Shader compile log:\n%s\n", log);
		free(log);
	}
    
    glGetShaderiv(fShaderName, GL_COMPILE_STATUS, &status);
	if (status == 0)
	{
		printf("Failed to compile frag shader:\n%s\n", pixelSource);
		return 0;
	}
	
	glAttachShader(program, fShaderName);
    
     
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar*)malloc(logLength);
		glGetProgramInfoLog(program, logLength, &logLength, log);
		printf("Program link log:\n%s\n", log);
		free(log);
	}
    glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == 0)
	{
		printf("Failed to link program");
		return 0;
	}
    
    
	glValidateProgram(program);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
	if (logLength > 0)
	{
		GLchar *log = (GLchar*)malloc(logLength);
		glGetProgramInfoLog(program, logLength, &logLength, log);
		printf("Program validate log:\n%s\n", log);
		free(log);
	}
    
	glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
	if (status == 0)
	{
		printf("Failed to validate program");
		//return 0;
	}    
    
    
    
    GLint max_length = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORM_MAX_LENGTH, &max_length);
    
    GLint active_uniforms = 0;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &active_uniforms);
    
    
    
    
    Shader*newShader = (Shader*)malloc(sizeof(Shader));
    
    newShader->attributes = (AttributeShader*)malloc(sizeof(AttributeShader)*(attributesLenght+1));
    newShader->attributesLenght = attributesLenght;
    
    int i = 0;
    newShader->uniforms = (UniformShader*)malloc(sizeof(UniformShader)*(active_uniforms+1));
    newShader->uniformsLenght = active_uniforms;
    
    for (GLint i = 0; i != active_uniforms; ++i)
    {
        GLsizei length;
        GLint   value_count;
        GLenum  type;
        GLchar *nameUniform = (GLchar*)malloc(sizeof(GLchar)*max_length);// new char[max_length];
        glGetActiveUniform(program, i, max_length, &length, &value_count, &type, nameUniform);
        std::string uniformStd = nameUniform;
        std::size_t pos = uniformStd.find("[");
        if (pos != -1) {
            uniformStd = uniformStd.substr(0,pos);
        }
        int idd = declorationTableXML.child("uniforms").child((char*)uniformStd.c_str()).attribute("id").as_uint();
        newShader->uniforms[i].idUniformConstant = idd;
        newShader->uniforms[i].action            = action[newShader->uniforms[i].idUniformConstant];
        newShader->uniforms[i].idUniform         = glGetUniformLocation(program, nameUniform);
        free(nameUniform);
        
    }
    
    i = 0;
    
    for (pugi::xml_node attributeInfo = declorationTableXML.child("attributes").first_child(); attributeInfo; attributeInfo = attributeInfo.next_sibling())
    {
        
       

        if (attributesBlock.find(attributeInfo.name())!=-1) {
            
            if (i>attributesLenght) {
                break;
            }
            
            newShader->attributes[i].idAttributeConstant = attributeInfo.attribute("id").as_uint();
            
            string var = attributeInfo.attribute("var").value();
            
            
            if(var=="vec4"){
                newShader->attributes[i].size = 4;
                newShader->attributes[i].type = GL_FLOAT;
            }else if(var=="vec3") {
                newShader->attributes[i].size = 3;
                newShader->attributes[i].type = GL_FLOAT;
            }else if(var=="vec2"){
                newShader->attributes[i].size = 2;
                newShader->attributes[i].type = GL_FLOAT;
            }else if(var=="float"){
                newShader->attributes[i].size = 1;
                newShader->attributes[i].type = GL_FLOAT;
            }
			newShader->attributes[i].normalized  = attributeInfo.attribute("normalized").as_bool();
            newShader->attributes[i].idAttribute = glGetAttribLocation(program, attributeInfo.attribute("bindName").value());
            
            i++;
        }
    }
    
    
    
    
    for (uint a=0; a<newShader->attributesLenght; a++) {
        glEnableVertexAttribArray(newShader->attributes[a].idAttribute);
    }
    
    
    shaderXML.reset();
    
    
    newShader->idProgram = program;
	return newShader;
}


void ShaderCache::fillExtensions(pugi::xml_node *shader){
    pugi::xml_node xml;
    xml = shader->child("extensions");
    if (!xml.empty()) {
        for (pugi::xml_node extension = xml.child("extension"); extension; extension = extension.next_sibling("varying"))
        {
            extensionBlock+=(string)"\n "+extension.attribute("code").value();
        }
    }
}

void ShaderCache::fillVaryings(pugi::xml_node *shader){
    pugi::xml_node xml;
    xml = shader->child("varyings");
    if (!xml.empty()) {

        for (pugi::xml_node varying = xml.child("varying"); varying; varying = varying.next_sibling("varying"))
        {
            if (varyingsBlock.find(varying.attribute("name").value())==-1) {
                varyingsBlock+=(string)"\n varying "+varying.attribute("prefix").value()+" "+varying.attribute("type").value()+" "+varying.attribute("name").value()+";";
            }
        }
    }
}

void ShaderCache::fillLocalVars(pugi::xml_node *shader) {
    pugi::xml_node xml;
    xml = shader->child("localVars");
    if (!xml.empty()) {
        
        for (pugi::xml_node localVar = xml.child("localVar"); localVar; localVar = localVar.next_sibling("localVar"))
        {
            if (codeHeader.find(localVar.attribute("name").value())==-1) {
                codeHeader+=(string)"\n "+localVar.attribute("prefix").value()+" "+localVar.attribute("type").value()+" "+localVar.attribute("name").value();
                if (!localVar.attribute("code").empty()) {
                    codeHeader+="=";
                    codeHeader+=localVar.attribute("code").value();
                }else {
                    codeHeader+=";";
                }
            }
        }
    }
}


void ShaderCache::createLocalVarForAttribute(pugi::xml_node &attributeInfo,pugi::xml_node &attribute,string &prefix) {
    if (!attribute.attribute("localVar").empty() &&
        attribute.attribute("localVar").as_bool() &&
        codeHeader.find(attributeInfo.attribute("localName").value())==-1) {
        if (attributeInfo.attribute("localVar").empty()) {
            codeHeader      +="\n";
            codeHeader      +=prefix;
            codeHeader      +=attributeInfo.attribute("var").value();
            codeHeader      +=" ";
            codeHeader      +=attributeInfo.attribute("localName").value();
            codeHeader      +="=";
            codeHeader      +=attributeInfo.attribute("bindName").value();
            codeHeader      +=";";
        }else{
            codeHeader      +="\n";
            codeHeader      +=prefix;
            codeHeader      +=attributeInfo.attribute("localVar").value();
            codeHeader      +=" ";
            codeHeader      +=attributeInfo.attribute("localCode").value();
        }
        if (codeHeader.find("position")!=-1) {
            positionBlock = "";
        }
    }
}


void ShaderCache::fillAttributes(pugi::xml_node *shader){
    pugi::xml_node xml;
    xml = shader->child("attributes");
    if (!xml.empty()) {
        for (pugi::xml_node attribute = xml.child("attribute"); attribute; attribute = attribute.next_sibling("attribute"))
        {
            string prefix = "";
            #if defined(TARGET_iOS)
            if (!attribute.attribute("prefix").empty()) prefix = attribute.attribute("prefix").as_string();
            #endif
            prefix+=" ";
            pugi::xml_node attributeInfo = declorationTableXML.child("attributes").child(attribute.attribute("name").value());
            
            if (!attributeInfo.empty() && attributesBlock.find(attributeInfo.attribute("bindName").value())==-1) {
                attributesBlock +="\n attribute ";
                attributesBlock +=prefix;
                attributesBlock +=attributeInfo.attribute("var").value();
                attributesBlock +=" ";
                attributesBlock +=attributeInfo.attribute("bindName").value();
                attributesBlock +=";";
                attributesLenght++;
            }
            
            createLocalVarForAttribute(attributeInfo,attribute,prefix);
            
        }
    }
}

void ShaderCache::fillUniforms(pugi::xml_node *shader){
    pugi::xml_node xml;
    xml = shader->child("uniforms");
    if (!xml.empty()) {
        for (pugi::xml_node uniform = xml.child("uniform"); uniform; uniform = uniform.next_sibling("uniform"))
        {
            
            pugi::xml_node uniformInfo = declorationTableXML.child("uniforms").child(uniform.attribute("name").value());
            uint idUniform = uniformInfo.attribute("id").as_uint();
            string prefix = "";
            #if defined(TARGET_iOS)
            if (!uniform.attribute("prefix").empty()) prefix = uniform.attribute("prefix").as_string();
            #endif
            prefix+=" ";
            if (!uniformInfo.empty() && uniformsBlock.find(uniform.attribute("name").value())==-1) {
                uniforms     |=idUniform;
                uniformsBlock+="\n uniform ";
                uniformsBlock+=prefix;
                uniformsBlock+=uniformInfo.attribute("var").value();
                uniformsBlock+=" ";
                uniformsBlock+=uniform.attribute("name").value();
                
                if (!uniformInfo.attribute("size").empty()){
                    uniformsBlock+="[";
                    uniformsBlock+=uniformInfo.attribute("size").value();
                    uniformsBlock+="]";
                }
                
                
                uniformsBlock+=";";
                
            }
         
        }
    }
    
    
    
}


char* ShaderCache::itoa(int val, int base){
    
    static char buf[32] = {0};
    
    int i = 30;
    
    for(; val && i ; --i, val /= base)
        
        buf[i] = "0123456789abcdef"[val % base];
    
    return &buf[i+1];
    
}
