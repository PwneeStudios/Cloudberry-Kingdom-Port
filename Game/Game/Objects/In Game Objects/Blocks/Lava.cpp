#include <global_header.h>
namespace CloudberryKingdom
{

	void LavaBlock::MakeNew()
	{
		getCore()->Init();
		getCore()->DrawLayer = 9;
		getBlockCore()->MyType = ObjectType_LAVA_BLOCK;

		MyQuad->setEffectName( _T( "Lava" ) );
	}

	void LavaBlock::Release()
	{
		BlockBase::Release();

		MyQuad.reset();
	}

	LavaBlock::LavaBlock( bool BoxesOnly )
	{
		InitializeInstanceFields();
		MyQuad = std::make_shared<QuadClass>();

		MyBox = std::make_shared<AABox>();

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;
	}

	void LavaBlock::SetUV()
	{
		float repeats = Size.X / TextureSize.X;
		MyQuad->Quad_Renamed.UVFromBounds( Vector2( repeats + u_offset, 1 ), Vector2( 0 + u_offset, 0 ) );
	}

	void LavaBlock::Init( float top, float left, float right, float depth )
	{
		float width = right - left;
		Vector2 centerTop = Vector2( ( left + right ) / 2, top );
		centerTop.Y -= depth / 2;
		Init( centerTop, Vector2( width, depth / 2 ) );
	}

	void LavaBlock::Init( Vector2 center, Vector2 size )
	{
		Active = true;
		Size = size;

		MyBox->Initialize( center, size );

		getBlockCore()->Layer = .35f;

		MyBox = std::make_shared<AABox>( center, size );

		SetQuad( center, size );

		SetUV();

		Update();
	}

	void LavaBlock::SetQuad( Vector2 center, Vector2 size )
	{
		MyQuad->Base.Origin = getBlockCore()->Data.Position = getBlockCore()->StartData.Position = center;

		MyQuad->Base.e1.X = size.X;
		MyQuad->Base.e2.Y = size.Y;
	}

	void LavaBlock::Reset( bool BoxesOnly )
	{
		getBlockCore()->BoxesOnly = BoxesOnly;

		Active = true;

		getBlockCore()->Data = getBlockCore()->StartData;

		getBlockCore()->StoodOn = false;

		MyBox->Current->Center = getBlockCore()->StartData.Position;

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );
		MyBox->SwapToCurrent();

		Update();
		SetUV();
	}

	void LavaBlock::CollisionCheck( const std::shared_ptr<Bob> &bob )
	{
		float h = MyBox->TR.Y;

		if ( bob->Box->BL.Y < h - 40 )
			bob->Die( Bob::BobDeathType_LAVA );
	}

	void LavaBlock::PhsxStep()
	{
		Active = getCore()->Active = true;
		if ( !getCore()->Held )
		{
			if ( !getCore()->MyLevel->getMainCamera()->OnScreen(MyBox->Current->BL, MyBox->Current->TR, 10) )
				Active = getCore()->Active = false;
		}

		if ( getCore()->MyLevel->PlayMode == 0 )
		{
			Active = getCore()->Active = false;
			for ( BobVec::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
				if ( ( *bob )->getCanDie() )
					CollisionCheck( *bob );
		}

		// Update the block's apparent center according to attached objects
		getBlockCore()->UseCustomCenterAsParent = true;
		getBlockCore()->CustomCenterAsParent = getBox()->Target->Center;

		Update();

		MyBox->SetTarget( MyBox->Current->Center, MyBox->Current->Size );

		getBlockCore()->StoodOn = false;
	}

	void LavaBlock::PhsxStep2()
	{
		if ( !Active )
			return;

		MyBox->SwapToCurrent();
	}

	void LavaBlock::Update()
	{
		if ( getBlockCore()->BoxesOnly )
			return;
	}

	void LavaBlock::Extend( Side side, float pos )
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
		SetQuad( MyBox->Target->Center, MyBox->Target->Size );
		SetUV();

		getBlockCore()->StartData.Position = MyBox->Current->Center;
	}

	void LavaBlock::Move( Vector2 shift )
	{
		getBlockCore()->Data.Position += shift;
		getBlockCore()->StartData.Position += shift;

		getBox()->Move(shift);

		Update();
	}

	void LavaBlock::Draw()
	{
	}

	bool LavaBlock::PreDecision( const std::shared_ptr<Bob> &bob )
	{
		// If the computer gets close, move the lava block down
		if ( bob->Box->Current->TR.X > getBox()->Current->BL.X && bob->Box->Current->BL.X < getBox()->Current->TR.X )
		{
			bob->getCore()->MyLevel->PushLava(bob->Box->Target->BL.Y - 60, this);
		}

		return true;
	}

	void LavaBlock::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<LavaBlock> BlockA = std::dynamic_pointer_cast<LavaBlock>( A );

		Init( BlockA->getBox()->Current->Center, BlockA->getBox()->Current->Size );
	}

	void LavaBlock::InitializeInstanceFields()
	{
		u_offset = 0;
		TextureSize = Vector2( 1400, 1000 );
	}
}
