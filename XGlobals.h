//
//  XGlobals.h
//  
//
//  Created by easy proger on 08.03.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _XGlobals_h
#define _XGlobals_h

#include <iostream>

bool IsGLExtensionSupported(const char * const extension)
{
	// The recommended technique for querying OpenGL extensions;
	// from http://opengl.org/resources/features/OGLextensions/
	const GLubyte *extensions = NULL;
	const GLubyte *start;
	GLubyte *where, *terminator;
    
	/* Extension names should not have spaces. */
	where = (GLubyte *) strchr(extension, ' ');
	if (where || *extension == '\0')
		return 0;
    
	extensions = glGetString(GL_EXTENSIONS);
    
	/* It takes a bit of care to be fool-proof about parsing the
     OpenGL extensions string. Don't be fooled by sub-strings, etc. */
	start = extensions;
	for (;;) {
		where = (GLubyte *) strstr((const char *) start, extension);
		if (!where)
			break;
		terminator = where + strlen(extension);
		if (where == start || *(where - 1) == ' ')
			if (*terminator == ' ' || *terminator == '\0')
				return true;
		start = terminator;
	}
    
	return false;
}
#endif
