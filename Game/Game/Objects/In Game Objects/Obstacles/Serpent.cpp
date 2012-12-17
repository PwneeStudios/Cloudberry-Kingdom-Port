#include <global_header.h>

namespace CloudberryKingdom
{

	void Serpent::SerpentTileInfo::InitializeInstanceFields()
	{
		Serpent_Renamed = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( _T( "Serpent" ) ), Vector2( 200, -1 ), Vector2( 0, -.875f ), Color::White, true );
		Fish = boost::make_shared<SpriteInfo>( TextureOrAnim::Get( _T( "Fish_1" ) ), Vector2( 35, -1 ) );
		BoxSize = Vector2( 90, 1000 );
	}

	void Serpent::MakeNew()
	{
		_BoxDeath::MakeNew();

		AutoGenSingleton = Serpent_AutoGen::getInstance();
		getCore()->MyType = ObjectType_SERPENT;
		DeathType = BobDeathType_NONE;
		getCore()->DrawLayer = 8;

		PhsxCutoff_Playing = Vector2( 200, 4000 );
		PhsxCutoff_BoxesOnly = Vector2( -150, 4000 );

		getCore()->GenData.NoBlockOverlap = false;
		getCore()->GenData.LimitGeneralDensity = false;

		getCore()->WakeUpRequirements = true;
	}

	void Serpent::Init( Vector2 pos, const boost::shared_ptr<Level> &level )
	{
		boost::shared_ptr<SerpentTileInfo> info = level->getInfo()->Serpents;

		BoxSize = info->BoxSize * level->getInfo()->ScaleAll * level->getInfo()->ScaleAllObjects;

		Start = Vector2( pos.X, level->MyCamera->BL.Y - 200 );
		End = Vector2( pos.X, level->MyCamera->TR.Y - 600 );

		if ( !level->BoxesOnly )
		{
			info->Serpent_Renamed->Offset = Vector2( 0, -.79f );
			MyQuad->Set( info->Serpent_Renamed );
			MyFish->Set( info->Fish );
		}

		_BoxDeath::Init( pos, level );
	}

	Serpent::Serpent( bool BoxesOnly ) :
		Offset( 0 ),
		UpT( 0 ),
		DownT( 0 ),
		WaitT1( 0 ),
		WaitT2( 0 ),
		Exposed( false )
	{
		if ( !BoxesOnly )
		{
			MyQuad = boost::make_shared<QuadClass>();
			MyFish = boost::make_shared<QuadClass>();
		}

		Construct( BoxesOnly );
	}

	void Serpent::SetPeriod( int Period )
	{
		WaitT1 = 58;
		UpT = 67;
		DownT = 45;
		WaitT2 = 5;

		int Total = WaitT1 + UpT + DownT + WaitT2;
		WaitT1 = static_cast<int>( WaitT1 * Period / static_cast<float>( Total ) );
		WaitT2 = static_cast<int>( WaitT2 * Period / static_cast<float>( Total ) );
		DownT = static_cast<int>( DownT * Period / static_cast<float>( Total ) );
		UpT = static_cast<int>( UpT * Period / static_cast<float>( Total ) );

		//WaitT1 = 50;
		//UpT = 67;
		//DownT = 45;

		//WaitT2 = Period - UpT - DownT - WaitT1;
		//if (WaitT2 < 0) WaitT2 = 0;
	}

	void Serpent::ActivePhsxStep()
	{
		_BoxDeath::ActivePhsxStep();
		AnimStep();
	}

	void Serpent::AnimStep()
	{
		AnimStep( getCore()->SkippedPhsx );
	}

	void Serpent::AnimStep( bool Skip )
	{
		if ( Skip )
			return;

		Exposed = true;

		float t = static_cast<float>( CoreMath::Modulo( getCore()->GetIndependentPhsxStep() + Offset, static_cast<float>( UpT + DownT + WaitT1 + WaitT2 ) ) );

		float s = 0, s_fish = 0;

		// Fish
		if ( !getCore()->BoxesOnly )
		{
			if ( t < WaitT1 + UpT )
				s_fish = CoreMath::ParabolaInterp( t / ( WaitT1 ), Vector2( 1.2f, 1.00f ), 0, 2.5f );

			MyFish->setPos( Vector2::Lerp( Start, End, s_fish ) );
		}

		// Serpent
		if ( t < WaitT1 )
			s = 0;
		else if ( t < UpT + WaitT1 )
			s = CoreMath::ParabolaInterp( ( t - WaitT1 ) / static_cast<float>( UpT ), Vector2( 1, 1 ), 0, 2.5f );
		else if ( t < WaitT2 + UpT + WaitT1 )
			s = 1;
		else
			s = CoreMath::ParabolaInterp( 1 + ( t - WaitT2 - UpT - WaitT1 ) / static_cast<float>( DownT ), Vector2( 1, 1 ), 0 );

		//if (!Core.BoxesOnly)
		//{
		//    MyQuad.Quad.Playing = true;
		//    if (t < WaitT1 + UpT * .51f)
		//    {
		//        MyQuad.Quad.Playing = false;
		//        MyQuad.Quad.CalcTexture(0, 0);
		//    }
		//    else
		//    {
		//        MyQuad.Quad.Playing = false;
		//        MyQuad.Quad.CalcTexture(0, 1);
		//    }
		//}


		setPos( Vector2::Lerp( Start, End, s ) - Vector2( 0, BoxSize.Y ) );
	}

	void Serpent::DrawGraphics()
	{
		if ( MyFish->getPos().Y > getPos().Y + BoxSize.Y - 50 )
			MyFish->Draw();

		MyQuad->setPos( getPos() + Vector2(0, BoxSize.Y) );
		MyQuad->Draw();
	}

	void Serpent::Move( Vector2 shift )
	{
		_BoxDeath::Move( shift );
	}

	void Serpent::Reset( bool BoxesOnly )
	{
		_BoxDeath::Reset( BoxesOnly );
	}

	void Serpent::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());
		Init( A->getCore()->StartData.Position, A->getMyLevel() );

		boost::shared_ptr<Serpent> SerpentA = boost::dynamic_pointer_cast<Serpent>( A );

		Offset = SerpentA->Offset;
		UpT = SerpentA->UpT;
		DownT = SerpentA->DownT;
		WaitT1 = SerpentA->WaitT1;
		WaitT2 = SerpentA->WaitT2;

		Exposed = SerpentA->Exposed;

		getCore()->WakeUpRequirements = true;
	}
}
