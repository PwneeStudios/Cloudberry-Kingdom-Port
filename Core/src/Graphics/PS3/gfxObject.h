/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#ifndef __GFX_OBJECT_H__
#define __GFX_OBJECT_H__


#include <PSGL/psgl.h>
#include <PSGL/psglu.h>
#include <GLES/glext.h>

#include <vectormath/cpp/vectormath_aos.h>


//-----------------------------------------------------------------------------
// Description: 
// The gfx object class is used to hold data about the geometry that will
// be used in the simple examples.
// It contains pointers to simple mesh data, a reference to a diffuse texture
// and also orientation information for the object
// Notes: 
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class gfxObject 
{
public:
	gfxObject():	//constructor sets object to something reasonable
	mTexture(0),                        
	mVertexCount(0),                   
	mHasIndices(false),
	mT(NULL),mN(NULL),mV(NULL), mI(NULL), 
	mScale(Vectormath::Aos::Vector3(1.0f,1.0f,1.0f)),        
	mPos(Vectormath::Aos::Vector3(0.0f,0.0f,0.0f)),      
	mRot(Vectormath::Aos::Vector3(0.0f,0.0f,0.0f)),      
	mRotD(Vectormath::Aos::Vector3(0.0f,0.0f,0.0f))      
	{};

	~gfxObject() {};   

	GLuint      mTexture;		// a simple texture
	GLuint      mEnvTexture;	// an environment cubemap
	int         mVertexCount;	// vertex count
	int 	    mIndexCount; 	// index count 
	bool 	    mHasIndices; 	// has vertex indices flag 
		
	float       *mT;			// texture coordinates
	float       *mN;			// normals
	float       *mV;			// vertex positions 
	GLuint 	    *mI;  			// object indices
	
	GLuint 	    mTexVBO;			// texture vertex buffer object id  
	GLuint      mNormVBO; 			// normal vertex buffer object id  
	GLuint 	    mVertVBO; 			// point vertex buffer object id
	GLuint 	    mIndexVBO;                  // index vertex buffer object id 
	
	Vectormath::Aos::Vector3     mScale;		// local to world scale
	Vectormath::Aos::Vector3     mPos;		// local to world translation
	Vectormath::Aos::Vector3     mRot;		// local to world rotation
	Vectormath::Aos::Vector3     mRotD;		// rotation delta
	Vectormath::Aos::Matrix4     mLocalToWorld;	// current local to world matrix

	void setMesh(int VertexCount,float *T,float *N,float *V); //hook up the mesh pointers
	void setMeshIndices( int IndexCount, GLuint * indices ); 
	
	void update();	//update the objects local to world matrix based on the objects orientation 
	void render(bool SetTexture = true);	//submit the mesh data for rendering by psgl

};

#define gfxDoNotSetTexture false 
//-----------------------------------------------------------------------------


#endif
