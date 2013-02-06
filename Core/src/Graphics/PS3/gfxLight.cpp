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

#include "gfxLight.h"

using namespace Vectormath;
using namespace Aos;

#define GFX_LIGHT_VERTEX_COUNT (3*8)
#define GFX_LIGHT_SCALE 0.2f

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
float basicLightV[] = {
0.500000f, 0.000000f, 0.000000f,  
0.000000f, 0.500000f, 0.000000f,  
0.000000f, 0.000000f, 0.500000f,

0.000000f, 0.500000f, 0.000000f, 
0.500000f, 0.000000f, 0.000000f,  
0.000000f, 0.000000f, -0.500000f,

0.000000f, -0.500000f, 0.000000f,  
0.500000f, 0.000000f, 0.000000f, 
0.000000f, 0.000000f, 0.500000f,

0.500000f, 0.000000f, 0.000000f,  
0.000000f, -0.500000f, 0.000000f,  
0.000000f, 0.000000f, -0.500000f,

0.000000f, 0.500000f, 0.000000f,
-0.500000f, 0.000000f, 0.000000f,
0.000000f, 0.000000f, 0.500000f,

-0.500000f, 0.000000f, 0.000000f,
0.000000f, 0.500000f, 0.000000f,
0.000000f, 0.000000f, -0.500000f,

-0.500000f, 0.000000f, 0.000000f,
0.000000f, -0.500000f, 0.000000f,
0.000000f, 0.000000f, 0.500000f,

0.000000f, -0.500000f, 0.000000f,
-0.500000f, 0.000000f, 0.000000f,
0.000000f, 0.000000f, -0.500000f,
};


//-----------------------------------------------------------------------------
// void gfxLight::render()	
// Description: renders the light
// Returns: 
// Notes:
// This function assumes that the model view matrix is set with only the view 
// component.  It uses this combined with the lights position to render the 
// light using the fixed function pipeline
//-----------------------------------------------------------------------------
void gfxLight::render()	//renders the light
{

	glPushMatrix();
	glTranslatef(mPos[0],mPos[1],mPos[2]);
	glScalef (GFX_LIGHT_SCALE,GFX_LIGHT_SCALE,GFX_LIGHT_SCALE);

	glColor4f(mCol[0]+mAmb[0],mCol[1]+mAmb[1],mCol[2]+mAmb[2],1.0f);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3,GL_FLOAT,0,basicLightV);
	glDrawArrays(GL_TRIANGLES,0,GFX_LIGHT_VERTEX_COUNT);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();

}
