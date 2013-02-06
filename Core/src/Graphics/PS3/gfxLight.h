/* SCE CONFIDENTIAL
 * PlayStation(R)3 Programmer Tool Runtime Library 430.001
 *                Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                                               All Rights Reserved.
 */

#ifndef __GFX_LIGHT_H__
#define __GFX_LIGHT_H__


#include <PSGL/psgl.h>
#include <PSGL/psglu.h>
#include <GLES/glext.h>

#include <vectormath/cpp/vectormath_aos.h>



//-----------------------------------------------------------------------------
// Description: 
// The gfx light class is used to hold data about a simple point light 
// source
// the light has position, diffuse and ambient colors
// Notes: 
//-----------------------------------------------------------------------------
class gfxLight
{
public:
	gfxLight():
		mPos(Vectormath::Aos::Vector3(0.0f,0.0f,0.0f)),
		mCol(Vectormath::Aos::Vector3(1.0f,1.0f,1.0f)),
		mAmb(Vectormath::Aos::Vector3(0.0f,0.0f,0.0f))
		{};

	Vectormath::Aos::Vector3 mPos;		//light position in world space
	Vectormath::Aos::Vector3 mCol;		//light color
	Vectormath::Aos::Vector3 mAmb;		//Ambient light color

	void	render();	//renders the light

private:

};
//----------------------------------------------------------------------------








#endif



