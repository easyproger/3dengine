//
//  forsyth.h
//  XTech
//
//  Created by easy proger on 19.02.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef __forsyth__
#define __forsyth__

#include <iostream>

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <math.h>
#include <string.h>

// Set these to adjust the performance and result quality
#define VERTEX_CACHE_SIZE 8
#define CACHE_FUNCTION_LENGTH 32

// The size of these data types affect the memory usage
typedef uint16_t ScoreType;
#define SCORE_SCALING 7281

typedef uint8_t AdjacencyType;
#define MAX_ADJACENCY UINT8_MAX


#include "XTypes.h"

typedef facesType VertexIndexType;
typedef int8_t  CachePosType;
typedef int32_t TriangleIndexType;
typedef int32_t ArrayIndexType;

// The size of the precalculated tables
#define CACHE_SCORE_TABLE_SIZE 32
#define VALENCE_SCORE_TABLE_SIZE 32
#if CACHE_SCORE_TABLE_SIZE < VERTEX_CACHE_SIZE
#error Vertex score table too small
#endif

// Precalculated tables


#define ISADDED(x)  (triangleAdded[(x) >> 3] &  (1 << (x & 7)))
#define SETADDED(x) (triangleAdded[(x) >> 3] |= (1 << (x & 7)))

// Score function constants
#define CACHE_DECAY_POWER	1.5
#define LAST_TRI_SCORE		0.75
#define VALENCE_BOOST_SCALE	2.0f
#define VALENCE_BOOST_POWER	0.5
void initForsyth();
VertexIndexType* reorderForsyth(const VertexIndexType* indices,
                                int nTriangles,
                                int nVertices);

#endif /* defined(__forsyth__) */
