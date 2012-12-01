#include <global_header.h>
namespace CloudberryKingdom
{

	void ConveyorBlock::MakeNew()
	{
		getCore()->Init();
		getCore()->DrawLayer = 3;
		getBlockCore()->MyType = ObjectType_CONVEYOR_BLOCK;
	}

	void ConveyorBlock::Release()
	{
		BlockBase::Release();

		MyQuad = LeftEnd = RightEnd = 0;
	}

	ConveyorBlock::ConveyorBlock( bool BoxesOnly )
	{
		InitializeInstanceFields();
		if ( !BoxesOnly )
		{
			MyQuad = std::make_shared<QuadClass>();
			MyQuad->Quad_Renamed->U_Wrap = true;
			MyQuad->setTextureName( _T( "Conveyor" ) );

			LeftEnd = std::make_shared<QuadClass>();
			LeftEnd->setTextureName( _T( "ConveyorEnd" ) );

			RightEnd = std::make_shared<QuadClass>();
			RightEnd->setTextureName( _T( "ConveyorEnd" ) );
		}

		MyBox = std::make_shared<AABox>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	void ConveyorBlock::SetUV()
	{
		float repeats = Size.X / texture_size.X;
		MyQuad->Quad_Renamed->UVFromBounds( Vector2( repeats + u_offset, 1 ), Vector2( 0 + u_offset, 0 ) );
	}

	void ConveyorBlock::Init( Vector2 center, Vector2 size )
	{
		Active = true;

		Size = size;
		Size.Y = texture_size.Y;

		getBlockCore()->Layer = .35f;
		MyBox = std::make_shared<AABox>( center, Size );
		MyQuad->Base.Origin = getBlockCore()->Data.Position = getBlockCore()->StartData.Position = center;

		MyBox->Initialize( center, Size );

		MyQuad->Base.e1.X = Size.X;
		MyQuad->Base.e2.Y = Size.Y;

		LeftEnd->Scale( Size.Y );
		LeftEnd->ScaleXToMatchRatio();
		LeftEnd->Base.e1.X *= -1;

		RightEnd->Scale( Size.Y );
		RightEnd->ScaleXToMatchRatio();

		Update();
	}

	void ConveyorBlock::Reset( bool BoxesOnly )
	{
		getBlockCore()->BoxesOnly = BoxesOnly;

		Active = true;

		getBlockCore()->Data = getBlockCore()->StartData;

		getBlockCore()->StoodOn = false;

		MyBox->Current->Center = getBlockCore()->StartData.Position;

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();

		Update();
	}

	void ConveyorBlock::PhsxStep()
	{
		Active = getCore()->Active = true;
		if ( !getCore()->Held )
		{
			if ( !getCore()->MyLevel->getMainCamera()->OnScreen(MyBox->Current->BL, MyBox->Current->TR, 10) )
				Active = getCore()->Active = false;
		}

		// Update the block's apparent center according to attached objects
		getBlockCore()->UseCustomCenterAsParent = true;
		getBlockCore()->CustomCenterAsParent = getBox()->Target->Center;

		Update();

		getBlockCore()->GroundSpeed = 2 * Speed * texture_size.X;
		u_offset += Speed;
		SetUV();

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );

		getBlockCore()->StoodOn = false;
	}

	void ConveyorBlock::PhsxStep2()
	{
		if ( !Active )
			return;

		MyBox->SwapToCurrent();
	}

	void ConveyorBlock::Update()
	{
		if ( getBlockCore()->BoxesOnly )
			return;
	}

	void ConveyorBlock::Extend( Side side, float pos )
	{
		switch ( side )
		{
			case Side_LEFT:
				MyBox->Target->BL.X = pos;
				break;
			case Side_RIGHT:
				MyBox->Target->TR.X = pos;
				break;
			case Side_TOP:
				MyBox->Target->TR.Y = pos;
				break;
			case Side_BOTTOM:
				MyBox->Target->BL.Y = pos;
				break;
		}

		MyBox->Target->FromBounds();
		MyBox->SwapToCurrent();

		Update();

		getBlockCore()->StartData.Position = MyBox->Current->Center;
	}

	void ConveyorBlock::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;

		getBox()->Move(shift);

		Update();
	}

	void ConveyorBlock::Draw()
	{
		Update();

		if ( Tools::DrawBoxes )
			MyBox->Draw( Tools::QDrawer, Color::Olive, 15 );

		if ( Tools::DrawGraphics )
		{
			if ( !getBlockCore()->BoxesOnly )
			{
				MyQuad->setTextureName( _T( "Chain_Tile" ) );
				MyQuad->Base.Origin = MyBox->Current->Center;
				MyQuad->Draw();

				//LeftEnd.Pos = Core.Data.Position - new Vector2(Size.X, 0);
				//LeftEnd.Draw();

				//RightEnd.Pos = Core.Data.Position + new Vector2(Size.X, 0);
				//RightEnd.Draw();
			}

			getBlockCore()->Draw();
		}
	}

	void ConveyorBlock::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<ConveyorBlock> BlockA = std::dynamic_pointer_cast<ConveyorBlock>( A );

		Speed = BlockA->Speed;
		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size );
	}

	void ConveyorBlock::InitializeInstanceFields()
	{
		Speed = -.05f;
		texture_size = Vector2( 100, 100 );
	}
}
