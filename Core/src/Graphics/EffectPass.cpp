#include <Graphics/EffectPass.h>

#include <GL/glew.h>

EffectPass::EffectPass( unsigned int progId ) :
	progId_( progId )
{
}

void EffectPass::Apply()
{
	glUseProgram( progId_ );
}
