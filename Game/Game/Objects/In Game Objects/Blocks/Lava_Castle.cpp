#include <small_header.h>
#include "Game/Objects/In Game Objects/Blocks/Lava_Castle.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/In Game Objects/Blocks/Lava.h"
#include "Game/Tools/Tools.h"

#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/FloatRectangle.h"

namespace CloudberryKingdom
{

	LavaBlock_Castle::LavaBlock_Castle( bool BoxesOnly ) : LavaBlock( BoxesOnly )
	{
	}

	void LavaBlock_Castle::MakeNew()
	{
		LavaBlock::MakeNew();

		MyQuad->setEffectName( std::wstring( L"Basic" ) );
		MyQuad->setTextureName( std::wstring( L"Castle_Lava" ) );
		TextureSize = Vector2( 2048, 128 ) * 1;
	}

	void LavaBlock_Castle::SetQuad( Vector2 center, Vector2 size )
	{
		LavaBlock::SetQuad( center, size );

		MyQuad->setSizeY( 400 );
		MyQuad->setPosY( getBox()->Target->TR.Y - MyQuad->getSizeY() + 75 );
	}

	void LavaBlock_Castle::PhsxStep()
	{
		LavaBlock::PhsxStep();

		u_offset = -.15f * Tools::t;
		SetUV();
	}

	void LavaBlock_Castle::Draw()
	{
		Update();

		MyQuad->setPosY( getBox()->Target->TR.Y - MyQuad->getSizeY() + 75 + static_cast<float>(cos(Tools::t)) * 15 );

		if ( Tools::DrawGraphics )
		{
			if ( !getBlockCore()->BoxesOnly )
			{
				MyQuad->Quad_Renamed.U_Wrap = true;

				MyQuad->Draw();
				Tools::QDrawer->Flush();
			}

			getBlockCore()->Draw();
		}

		if ( Tools::DrawBoxes )
		{
			MyBox->Draw( Tools::QDrawer, Color::Olive, 15 );
		}
	}

	void LavaBlock_Castle::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<LavaBlock> BlockA = boost::dynamic_pointer_cast<LavaBlock>( A );

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size );
	}
}
