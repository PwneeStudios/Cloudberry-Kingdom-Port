/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <PSGL/psgl.h>
#include <PSGL/psglu.h>
#include <GLES/glext.h>
#include <vectormath/cpp/vectormath_aos.h>

#include "gfxObject.h"
#include "gfxCommon.h"

using namespace Vectormath;
using namespace Aos;


//-----------------------------------------------------------------------------
// Description: Sets the mesh parameters
// Parameters:	
//	int		VertexCount		number of vertices
//  float	*ST				pointer to array of texture coorindates
//	float   *N				pointer to array of normals
//	float	*V				pointer to array of vertex positions
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void gfxObject::setMesh(int VertexCount,float *T,float *N,float*V) 
{
	mVertexCount = VertexCount;
	mT = T;
	mN = N;
	mV = V;
	
	// Create Vertex Buffer Objects for each

	// verts 
	glGenBuffers(1,&mVertVBO);
	glBindBuffer(GL_ARRAY_BUFFER,mVertVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*mVertexCount,mV,GL_STATIC_DRAW);
	// let's make sure we turn this bind off 
	glBindBuffer(GL_ARRAY_BUFFER, 0 ); 
	
	if ( mN )
	{
		// normals
		glEnableClientState(GL_NORMAL_ARRAY);
		glGenBuffers(1,&mNormVBO);
		glBindBuffer(GL_ARRAY_BUFFER,mNormVBO);
		glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*3*mVertexCount,mN,GL_STATIC_DRAW);
		glDisableClientState(GL_NORMAL_ARRAY);
		// let's make sure we turn this bind off 
		glBindBuffer(GL_ARRAY_BUFFER, 0 ); 
	}
	
	
	if ( mT )
	{
		// texture coordinates 	
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glGenBuffers(1,&mTexVBO); 
		glBindBuffer(GL_ARRAY_BUFFER,mTexVBO);
		glBufferData(GL_ARRAY_BUFFER,sizeof(GLfloat)*2*mVertexCount,mT,GL_STATIC_DRAW); 
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		// let's make sure we turn this bind off 
		glBindBuffer(GL_ARRAY_BUFFER, 0 ); 
	}
	
	printf("gfxObject::Created Vertex Buffers for V-%d, N-%d, T-%d \n", mVertVBO, mNormVBO, mTexVBO );  
}

//-----------------------------------------------------------------------------
// Description: Sets the mesh indices 
// Parameters:	
//	int	IndexCount		number of indices 
//	GLuint  *I 			pointer to indices 
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void gfxObject::setMeshIndices(int IndexCount, GLuint * I) 
{
	mIndexCount = IndexCount;
	mI = I;

	for ( GLuint i = 0; i < (GLuint)IndexCount; i++)
	{
		assert( mI[i] < (GLuint)mVertexCount ); 
	}

	// Create Vertex Buffer Object for the Indices 
	glGenBuffers(1,& mIndexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mIndexVBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(GLuint)*IndexCount,mI,GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,0); 
		
	printf("gfxObject::Created Vertex Buffers for Indices %d NumIndices %d \n", 
		mIndexVBO, IndexCount );  
	
	mHasIndices = true; 
}

//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Description: Updates the objects local to world matrix to reflect the 
// current state of the objects scale, translation and rotation vectors
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void gfxObject::update()
{
	//build the local to world matrix for the object
	Matrix4 scale   =Matrix4::scale(mScale);        
	Matrix4 trans   =Matrix4::translation(mPos);        
	Matrix4 rotX    =Matrix4::rotationX(mRot[0]);   
	Matrix4 rotY    =Matrix4::rotationY(mRot[1]);   
	Matrix4 rotZ    =Matrix4::rotationZ(mRot[2]);   

	mLocalToWorld =  trans*rotX*rotY*rotZ*scale;
	//update the objects orientation
	mRot+=mRotD;    
}
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// Description: Submits the object for drawing
// sets the objects diffuse texture as current
// then submits the vertices
// Parameters:	
// Returns:
// Notes:
//-----------------------------------------------------------------------------
void gfxObject::render( bool SetTexture )
{
	// Check if exit callback has been called
	gfxCheckSysutilCallback();
	
	if ( SetTexture )
	{
		// set the active texture
		glBindTexture(GL_TEXTURE_2D,mTexture );
	}

	// enable the draw arrays, send them for drawing and then disable them
	glEnableClientState(GL_VERTEX_ARRAY);

	bool renderWithVBOs = true; 
	
	//        OPTIMIZATION NOTE!!!!!! 	
	//You can draw with this method with PSGL on PS3, however it is slow.
	//Indexed Vertex Buffer Objects are many times faster.  See below  
	
	if ( !renderWithVBOs )
	{
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glTexCoordPointer(2,GL_FLOAT,0,mT);
		glNormalPointer(GL_FLOAT,0,mN);
		glVertexPointer(3,GL_FLOAT,0,mV);

		glDrawArrays(GL_TRIANGLES,0,mVertexCount);

	}
	else
	{	
	
		glEnableClientState(GL_VERTEX_ARRAY);
		// set the vertex vbo
	        glBindBuffer(GL_ARRAY_BUFFER, mVertVBO);
        	glVertexPointer(3,GL_FLOAT,0,NULL);	

		// if there were normals set use them.
		if ( mN )
		{	
			glEnableClientState(GL_NORMAL_ARRAY);
			// set the normal vbo
			glBindBuffer(GL_ARRAY_BUFFER, mNormVBO);
			glNormalPointer(GL_FLOAT,0,NULL);
		
		}
		else
		{
			glDisableClientState(GL_NORMAL_ARRAY);
		}
	
		// if there were texcoord set then use them. 	
		if ( mT )
		{
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		       	// set the texture coord vbo
			glBindBuffer(GL_ARRAY_BUFFER, mTexVBO);
			glTexCoordPointer(2,GL_FLOAT,0,NULL);
		}
		else
		{
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		}
		
		// if there were indices set use them 
		if ( mHasIndices )
		{	        
			// set the index vbo and draw with the Optimal DrawRangedElements call.  
       			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexVBO);
		        glDrawRangeElements(GL_TRIANGLES, 0, mVertexCount-1, mIndexCount, GL_UNSIGNED_INT, NULL);
	        	
	        	// just to make sure we turn this back off 
	        	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0); 
 		}
 		else
 		{	
 			// otherwise if there are no indices just call draw arrays 
			glDrawArrays(GL_TRIANGLES,0,mVertexCount); 	 	
 		}
	}
	
	glBindBuffer(GL_ARRAY_BUFFER, 0 );	 	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

 }
//-----------------------------------------------------------------------------

