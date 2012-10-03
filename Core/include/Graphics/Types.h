/**
 * @file
 *
 * Fundamental graphics subsystem types.
 */
#ifndef _GRAPHICS_TYPES_H_
#define _GRAPHICS_TYPES_H_

#include <Math/Vectors.h>
#include <Content/ResourcePtr.h>
#include <Content/Texture.h>

/// Fundamental unit of drawing.
struct SimpleQuad
{
	Vector2 V[4];
	Vector2 T[4];
	Vector4 Color;
	ResourcePtr< Texture > Diffuse;
};


#endif
