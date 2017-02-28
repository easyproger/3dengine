//
//  Vector.h
//  ShadowMapsTestProject
//
//  Created by Easy.proger on 13.04.11.
//  Copyright 2011 Immortal Engine. All rights reserved.
//
///////////////////////////////////////////////////////////////////////////////
// inline functions for vec3
///////////////////////////////////////////////////////////////////////////////

#ifndef VECTORS_H_DEF
#define VECTORS_H_DEF

#include <math.h>



///////////////////////////////////////////////////////////////////////////////
// 3D vector
///////////////////////////////////////////////////////////////////////////////



class vec3
{
public:
    float x;
    float y;
    float z;
    
    // ctors
    vec3() : x(0), y(0), z(0) {};
    vec3(float x, float y, float z) : x(x), y(y), z(z) {};
    
    vec3(const float*rsh): x(rsh[0]), y(rsh[1]), z(rsh[2]){};
    
    // utils functions
    float       length() const;                         //
    float       distance(const vec3& vec) const;     // distance between two vectors
    vec3&    normalize();                            //
    float       dot(const vec3& vec) const;          // dot product
    vec3     cross(const vec3& vec) const;        // cross product, same as *operator
    
    // operators
    vec3&    operator=(const vec3&); 
    vec3     operator-() const;                      // unary operator (negate)
    vec3     operator+(const vec3& rhs) const;    // add rhs
    vec3     operator-(const vec3& rhs) const;    // subtract rhs
    vec3&    operator+=(const vec3& rhs);         // add rhs and update this object
    vec3&    operator-=(const vec3& rhs);         // subtract rhs and update this object
    vec3     operator*(const float scale) const;     // scale
    vec3     operator*(const vec3& rhs) const;    // cross product
    vec3&    operator*=(const float scale);          // scale and update this object
    vec3&    operator*=(const vec3& rhs);         // cross product and update this object
    vec3     operator/(const float scale) const;     // inverse scale
    vec3&    operator/=(const float scale);          // scale and update this object
    bool        operator==(const vec3& rhs) const;   // exact compare, no epsilon
    bool        operator!=(const vec3& rhs) const;   // exact compare, no epsilon
    float       operator[](int index) const;            // subscript operator v[0], v[1]
    float&      operator[](int index);                  // subscript operator v[0], v[1]
    
    friend vec3 operator*(const float a, const vec3 vec);
   
};

class vec4
{
public:
    float x;
    float y;
    float z;
    float w;
    
    // ctors
    vec4() : x(0), y(0), z(0), w(0) {};
    vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};
    vec4(const vec3& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {};
    
};

// fast math routines from Doom3 SDK
inline float invSqrt(float x)
{
    float xhalf = 0.5f * x;
    int i = *(int*)&x;          // get bits for floating value
    i = 0x5f3759df - (i>>1);    // gives initial guess
    x = *(float*)&i;            // convert bits back to float
    x = x * (1.5f - xhalf*x*x); // Newton step
    return x;
}


inline vec3& vec3::operator=(const vec3& vec) {
    x = vec.x; y = vec.y; z = vec.z;
    return *this;
}

inline vec3 vec3::operator-() const {
    return vec3(-x, -y, -z);
}

inline vec3 vec3::operator+(const vec3& rhs) const {
    return vec3(x+rhs.x, y+rhs.y, z+rhs.z);
}

inline vec3 vec3::operator-(const vec3& rhs) const {
    return vec3(x-rhs.x, y-rhs.y, z-rhs.z);
}

inline vec3& vec3::operator+=(const vec3& rhs) {
    x += rhs.x; y += rhs.y; z += rhs.z; return *this;
}

inline vec3& vec3::operator-=(const vec3& rhs) {
    x -= rhs.x; y -= rhs.y; z -= rhs.z; return *this;
}

inline vec3 vec3::operator*(const float a) const {
    return vec3(x*a, y*a, z*a);
}

inline vec3 vec3::operator*(const vec3& rhs) const {
    return vec3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

inline vec3& vec3::operator*=(const float a) {
    x *= a; y *= a; z *= a; return *this;
}

inline vec3 vec3::operator/(const float a) const {
    return vec3(x/a, y/a, z/a);
}

inline vec3& vec3::operator/=(const float a) {
    x /= a; y /= a; z /= a; return *this;
}

inline bool vec3::operator==(const vec3& rhs) const {
    return (x == rhs.x) && (y == rhs.y) && (z == rhs.z);
}

inline bool vec3::operator!=(const vec3& rhs) const {
    return (x != rhs.x) || (y != rhs.y) || (z != rhs.z);
}

inline float vec3::operator[](int index) const {
    return (&x)[index];
}

inline float& vec3::operator[](int index) {
    return (&x)[index];
}

inline float vec3::length() const {
    return sqrtf(x*x + y*y + z*z);
}

inline float vec3::distance(const vec3& vec) const {
    return sqrtf((vec.x-x)*(vec.x-x) + (vec.y-y)*(vec.y-y) + (vec.z-z)*(vec.z-z));
}

inline vec3& vec3::normalize() {
    float invLength = invSqrt(x*x + y*y + z*z);
    x *= invLength;
    y *= invLength;
    z *= invLength;
    return *this;
}

inline float vec3::dot(const vec3& rhs) const {
    return (x*rhs.x + y*rhs.y + z*rhs.z);
}

inline vec3 vec3::cross(const vec3& rhs) const {
    return vec3(y*rhs.z - z*rhs.y, z*rhs.x - x*rhs.z, x*rhs.y - y*rhs.x);
}

inline vec3 operator*(const float a, const vec3 vec) {
    return vec3(a*vec.x, a*vec.y, a*vec.z);
}


// END OF vec3 /////////////////////////////////////////////////////////////
#endif