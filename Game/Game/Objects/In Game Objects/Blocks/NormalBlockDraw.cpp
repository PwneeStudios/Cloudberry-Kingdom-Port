#include "NormalBlockDraw.h"
#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	NormalBlockDraw::NormalBlockDraw()
	{
		InitializeInstanceFields();
		MakeNew();
	}

	void NormalBlockDraw::MakeNew()
	{
		SetTint( Color::White );
		MyTemplate.reset();
	}

	void NormalBlockDraw::Clone( const std::shared_ptr<NormalBlockDraw> &DrawA )
	{
		SetTint( DrawA->Tint );
		MyTemplate = DrawA->MyTemplate;
	}

	void NormalBlockDraw::SetTint( Vector4 v )
	{
		SetTint( Color( v ) );
	}

	void NormalBlockDraw::SetTint( Color Tint )
	{
		this->Tint = Tint;

		if ( MyPieces != 0 )
			MyPieces->SetColor( Tint );
	}

	void NormalBlockDraw::Release()
	{
		MyPieces.reset();
		MyBlock.reset();
	}

Vector2 NormalBlockDraw::ModCeilingSize = Vector2( 25, 0 );

	void NormalBlockDraw::Init( const std::shared_ptr<BlockBase> &block )
	{
		Init( block, 0, false );
	}

	void NormalBlockDraw::Init( const std::shared_ptr<BlockBase> &block, const std::shared_ptr<PieceQuad> &template_Renamed, bool Invert )
	{
		if ( MyTemplate != 0 )
			template_Renamed = MyTemplate;

		//MyPieces.Init(Tools.TextureWad.FindByName("White"), Tools.BasicEffect);

		if ( template_Renamed != 0 )
		{
			if ( MyPieces == 0 )
				MyPieces = std::make_shared<PieceQuad>();
			MyPieces->Clone( template_Renamed );
		}

		MyBlock = block;

		// Grow the block a bit if it is a ceiling piece
		Vector2 ModSize = Vector2::Zero;

		if ( MyPieces != 0 )
		{
			MyPieces->Invert = Invert;

			MyPieces->MyOrientation = block->getBlockCore()->MyOrientation;

			MyPieces->CalcQuads( MyBlock->getBox()->Current->Size + ModSize );
		}

		// Tint
		SetTint( MyBlock->getCore()->getMyTileSet()->Tint );

		SetTint( Tint );
	}

	void NormalBlockDraw::Update()
	{
		if ( MyPieces != 0 )
			MyPieces->Base.Origin = MyBlock->getBox()->Current->Center;
	}

	void NormalBlockDraw::Draw()
	{
		if ( MyPieces != 0 )
		{
			MyPieces->Draw();
		}
	}

	void NormalBlockDraw::InitializeInstanceFields()
	{
		Shadow = false;
		ShadowOffset = Vector2::Zero;
		ShadowColor = Color::Black;
	}
}
