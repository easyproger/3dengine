//
//  Snippets.h
//  
//
//  Created by easy proger on 05.09.14.
//  Copyright (c) 2014 easy proger. All rights reserved.
//

#ifndef _Snippets_h
#define _Snippets_h



 
 // make data provider with data.
 CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, buffer, myDataLength, NULL);
 // prep the ingredients
 int bitsPerComponent = 8;
 int bitsPerPixel = 8*bytesNum;
 int bytesPerRow = bytesNum * w ;
 CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
 CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault;
 CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
 // make the cgimage
 CGImageRef imageRef = CGImageCreate(w, h, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
 // then make the uiimage from that
 UIImage *myImage = [ UIImage imageWithCGImage:imageRef scale:1.0 orientation:UIImageOrientationUp ];
 [self performSelectorOnMainThread:@selector(addImage:) withObject:[myImage copy] waitUntilDone:NO];
 
 


 int width = qcarImageYUV->getWidth();
 int height = qcarImageYUV->getHeight();
 int bitsPerComponent = 8;
 int bitsPerPixel = QCAR::getBitsPerPixel(QCAR::RGB888);
 int bytesPerRow = qcarImageYUV->getBufferWidth() * bitsPerPixel / bitsPerComponent;
 CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
 CGBitmapInfo bitmapInfo = kCGBitmapByteOrderDefault | kCGImageAlphaNone;
 CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;
 
 CGDataProviderRef provider = CGDataProviderCreateWithData(NULL, qcarImageYUV->getPixels(), QCAR::getBufferSize(width, height, QCAR::RGB888), NULL);
 
 CGImageRef imageRef = CGImageCreate(width, height, bitsPerComponent, bitsPerPixel, bytesPerRow, colorSpaceRef, bitmapInfo, provider, NULL, NO, renderingIntent);
 CGImageRef imageRefRetain = CGImageRetain(imageRef);
 UIImage *image = [UIImage imageWithCGImage:imageRefRetain];
 
 UIImageWriteToSavedPhotosAlbum(image,nil,nil,nil);
 
 CGDataProviderRelease(provider);
 CGColorSpaceRelease(colorSpaceRef);
 CGImageRelease(imageRef);
 
 image = [self drawableToCGImage];
 UIImageWriteToSavedPhotosAlbum(image,nil,nil,nil);



//Quat mult

highp vec4 multQuat(highp vec4 q1, highp vec4 q2)
{
    return vec4(
                q1.w * q2.x + q1.x * q2.w + q1.z * q2.y - q1.y * q2.z,
                q1.w * q2.y + q1.y * q2.w + q1.x * q2.z - q1.z * q2.x,
                q1.w * q2.z + q1.z * q2.w + q1.y * q2.x - q1.x * q2.y,
                q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z
                );
}

highp vec3 rotate_vector2(highp vec3 vec ,highp vec4 quat)
{
    highp vec4 qv = multQuat( quat, vec4(vec, 0.0) );
    return multQuat( qv, vec4(-quat.x, -quat.y, -quat.z, quat.w) ).xyz;
}


highp vec3 rotate_vector( highp vec3 vec,highp vec4 quat )
{
    return vec + 2.0 * cross( cross( vec, quat.xyz ) + quat.w * vec, quat.xyz );
}

highp vec3 boneTransf ( int index,highp vec3 pos )
{
    return bonesTranslations[index].xyz + rotate_vector2(pos,bonesRotations[index] ).xyz;
}


 highp vec2 fenc = a_normal.xy*4.0-2.0;
 highp float f = dot(fenc,fenc);
 highp float g = sqrt(1.0-f/4.0);
 highp vec3 n;
 n.xy = fenc*g;
 n.z = 1.0-f/2.0;
 
//highp float cosTheta = 0.005*tan(acos(clamp(dot(lightPosition_v,normal_v.xyz),0.0,1.0)));
//bias_v = clamp(cosTheta, 0.0,0.01);


rtRay Camera::GetRay( real32 x, real32 y, real32 width, real32 height )
{
#define mm(m,i,j) m._x[i][j]
    
    // Compute the vector of the pick ray in screen space
    vec3 dir, orig;
    real32 mx = -( ( ( 2.0f * x ) / width  ) - 1.0f ) / mm( m_m4Proj, 0, 0 );
    real32 my =  ( ( ( 2.0f * y ) / height ) - 1.0f ) / mm( m_m4Proj, 1, 1 );
    
    // Get the inverse view matrix
    mat4 m = m_m4TransfInv;
    
    // Transform the screen space pick ray into 3D space
    dir.x  = -( mx * mm( m, 0, 0 ) + my * mm( m, 1, 0 ) + mm( m, 2, 0 ) );
    dir.y  = -( mx * mm( m, 0, 1 ) + my * mm( m, 1, 1 ) + mm( m, 2, 1 ) );
    dir.z  = -( mx * mm( m, 0, 2 ) + my * mm( m, 1, 2 ) + mm( m, 2, 2 ) );
    orig.x = mm( m, 3, 0 );
    orig.y = mm( m, 3, 1 );
    orig.z = mm( m, 3, 2 );
    
    return rtRay( orig, dir );
}

static bool rtIntersectRayTriangle_NonCull( const rtRay& ray, const rtMath::vec3& v0, const rtMath::vec3& v1, const rtMath::vec3& v2, real32& t, real32& u, real32& v )
{
    /* find vectors for two edges sharing vert0 */
    rtMath::vec3 edge1 = v1 - v0;
    rtMath::vec3 edge2 = v2 - v0;
    /* begin calculating determinant - also used to calculate U parameter */
    rtMath::vec3 pvec = rtMath::cross( ray.dir, edge2 );
    /* if determinant is near zero, ray lies in plane of triangle */
    real32 det = rtMath::dot( edge1, pvec );
    if ( det > -rtMath::EPSILON && det < rtMath::EPSILON )
        return false;
    real32 inv_det = 1.0 / det;
    /* calculate distance from vert0 to ray origin */
    rtMath::vec3 tvec = ray.origin - v0;
    /* calculate U parameter and test bounds */
    u = rtMath::dot( tvec, pvec ) * inv_det;
    if ( u < -0.0001 || u > 1.0001 )
        return false;
    /* prepare to test V parameter */
    rtMath::vec3 qvec = rtMath::cross( tvec, edge1 );
    /* calculate V parameter and test bounds */
    v = rtMath::dot( ray.dir, qvec ) * inv_det;
    if ( v < -0.0001 || (u + v) > 1.0001 )
        return false;
    /* calculate t, ray intersects triangle */
    t = rtMath::dot( edge2, qvec ) * inv_det;
    return true;
}
ПРАВКО:
m_m4Proj == Матрица проекции 
m_m4Transf == Мировая матрица 
m_m4TransfInv = m_m4Transf.inverse();




function () {
    CGPoint startLoc0 = [[[touches allObjects] objectAtIndex:0] locationInView:self];
    
    XMatrix4*perspectiveMatrix = camera->getPerspectiveMatrix();
    
    float width  = self.frame.size.width;
    float height = self.frame.size.height;
    
    
    float mx = -( ( ( 2.0f * startLoc0.x ) / width  ) - 1.0f ) / perspectiveMatrix->m[0];
	float my =  ( ( ( 2.0f * startLoc0.y ) / height ) - 1.0f ) / perspectiveMatrix->m[5];
    
    
    
    
    
    
    
    GLKMatrix4 viewMatrixInverse = GLKMatrix4MakeWithArray(camera->getModelViewMatrix()->m);
    bool isInvertible = true;
    viewMatrixInverse = GLKMatrix4Invert(viewMatrixInverse, &isInvertible);
    
    XMatrix4 inverseView;
    XMatrix4MakeWithArray(&inverseView, viewMatrixInverse.m);
    
    XVector3 rayDir;
    XVector3 rayOrigin;
    
	// Transform the screen space pick ray into 3D space
	rayDir.x  = -( mx * inverseView.m[0]  + my * inverseView.m[4] + inverseView.m[8] );
	rayDir.y  = -( mx * inverseView.m[1]  + my * inverseView.m[5] + inverseView.m[9] );
	rayDir.z  = -( mx * inverseView.m[2]  + my * inverseView.m[6] + inverseView.m[10] );
	
	rayOrigin.x = viewMatrixInverse.m[12];
	rayOrigin.y = viewMatrixInverse.m[13];
	rayOrigin.z = viewMatrixInverse.m[14];
    
    
    
    bool intersect = true;
    
    
    XVector3 centerBBox = sphere2->getMesh()->bboxCenter;
    XVector3 widthBBox  = sphere2->getMesh()->bboxWidth;
    
    
    centerBBox.x = centerBBox.x;
    centerBBox.y = centerBBox.y;
    centerBBox.z = centerBBox.z;
    
    widthBBox.x = widthBBox.x;
    widthBBox.y = -widthBBox.y;
    widthBBox.z = widthBBox.z;
    
    
    
    float bminx = centerBBox.x - widthBBox.x / 2;
	float bminy = centerBBox.y - widthBBox.y / 2;
	float bminz = centerBBox.z - widthBBox.z / 2;
    
	float bmaxx = centerBBox.x + widthBBox.x / 2;
	float bmaxy = centerBBox.y + widthBBox.y / 2;
	float bmaxz = centerBBox.z + widthBBox.z / 2;
    
	float txmin = 0, txmax = 0, tymin = 0, tymax = 0, tzmin = 0, tzmax = 0;
	
	if (rayDir.x > 0)
	{
		txmin = (bminx - rayOrigin.x) / rayDir.x;
		txmax = (bmaxx - rayOrigin.x) / rayDir.x;
	}
	else
	{
		txmin = (bmaxx - rayOrigin.x) / rayDir.x;
		txmax = (bminx - rayOrigin.x) / rayDir.x;
	}
	if (rayDir.y > 0)
	{
		tymin = (bminy - rayOrigin.y) / rayDir.y;
		tymax = (bmaxy - rayOrigin.y) / rayDir.y;
	}
	else
	{
		tymin = (bmaxy - rayOrigin.y) / rayDir.y;
		tymax = (bminy - rayOrigin.y) / rayDir.y;
	}
	if (txmin > tymax || tymin > txmax) intersect = false;
	if (tymin > txmin) txmin = tymin;
	if (tymax < txmax) txmax = tymax;
	if (rayDir.z > 0)
	{
		tzmin = (bminz - rayOrigin.z) / rayDir.z;
		tzmax = (bmaxz - rayOrigin.z) / rayDir.z;
	}
	else
	{
		tzmin = (bmaxz - rayOrigin.z) / rayDir.z;
		tzmax = (bminz - rayOrigin.z) / rayDir.z;
	}
	if (txmin > tzmax || tzmin > txmax) intersect = false;
    
    if (intersect){
        NSLog(@"fired");
    }
}




bool Box::intersect(const Ray &r, float t0, float t1) const {
    float tmin, tmax, tymin, tymax, tzmin, tzmax;
    if (r.direction.x() >= 0) {
        tmin = (bounds[0].x() - r.origin.x()) / r.direction.x();
        tmax = (bounds[1].x() - r.origin.x()) / r.direction.x();
    }
    else {
        tmin = (bounds[1].x() - r.origin.x()) / r.direction.x();
        tmax = (bounds[0].x() - r.origin.x()) / r.direction.x();
    }
    if (r.direction.y() >= 0) {
        tymin = (bounds[0].y() - r.origin.y()) / r.direction.y();
        tymax = (bounds[1].y() - r.origin.y()) / r.direction.y();
    }
    else {
        tymin = (bounds[1].y() - r.origin.y()) / r.direction.y();
        tymax = (bounds[0].y() - r.origin.y()) / r.direction.y();
    }
    if ( (tmin > tymax) || (tymin > tmax) )
        return false;
    1if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;
    if (r.direction.z() >= 0) {
        tzmin = (bounds[0].z() - r.origin.z()) / r.direction.z();
        tzmax = (bounds[1].z() - r.origin.z()) / r.direction.z();
    }
    else {
        tzmin = (bounds[1].z() - r.origin.z()) / r.direction.z();
        tzmax = (bounds[0].z() - r.origin.z()) / r.direction.z();
    }
    if ( (tmin > tzmax) || (tzmin > tmax) )
        return false;
    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;
    return ( (tmin < t1) && (tmax > t0) );
}








function RayIntersectAABB(rayOrig, rayDir, boxMin, boxMax: TVector3f;
                          var tIsect0, tIsect1: single): boolean;
var i: integer;
tNear, tFar: single;
t0, t1, tmp: single;
begin
Result:= false;
// The first part of this code tests for line-AABB intersection.
tNear:= -INFINITY;
tFar:= INFINITY;
for i:=0 to 2 do
begin
// Check if the line is parallel to the min[i] and max[i] planes.
if (abs(rayDir.xyz[i]) < MY_MATH_EPSILON) then
begin
// The line is parallel to the min[i] and max[i] planes.
if (rayOrig.xyz[i] < boxMin.xyz[i]) or
(rayOrig.xyz[i] > boxMax.xyz[i]) then
begin
// The line is outside the slab defined by min[i] and max[i].
Exit; //return false;
end;
// else:  The line is inside the slab defined by min[i] and max[i].
// Just continue testing with the next slab.
continue;
end;

// The line is not parallel to the slab planes, so compute the
// parameters of intersection.  The line segment of intersection is
// P+t*d, where t0 <= t <= t1.
t0:= (boxMin.xyz[i] - rayOrig.xyz[i])/rayDir.xyz[i];
t1:= (boxMax.xyz[i] - rayOrig.xyz[i])/rayDir.xyz[i];
if (t0 > t1) then
begin
tmp:= t1;
t1:= t0;
t0:= tmp;
end;

// Compare with current values.  The current slab may have increased
// tNear and/or decreased tFar.
if (t0 > tNear) then
tNear:= t0;
if (t1 < tFar) then
tFar:= t1;

// Check if the line misses the AABB entirely.
if (tNear > tFar) then
Exit; //return false;
end;

// At this place in the code, the line intersects the AABB in the line
// segment P+t*d, tNear <= t <= tFar.  If all you care about is line-AABB
// intersection, then use the following three lines of code and omit the
// remaining pseudocode.
//
// tIntersect[0] = tNear;
// tIntersect[1] = tFar;
// return true;

// The ray is (P+t*d, t >= 0).  We need to compute the intersection of
// the interval tNear <= t <= tFar with the interval t >= 0.
if (tFar < 0) then
Exit; //return false;
if (tNear < 0) then
tNear:= 0;
//
tIsect0:= tNear;
tIsect1:= tFar;
Result:= true; //return true;
end;

#endif
