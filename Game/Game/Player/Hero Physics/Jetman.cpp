#include <global_header.h>

namespace CloudberryKingdom
{

	void BobPhsxJetman::InitializeStatics()
	{
		BobPhsxJetman::instance = boost::make_shared<BobPhsxJetman>();
	}

	// Statics
	boost::shared_ptr<BobPhsxJetman> BobPhsxJetman::instance;


	void BobPhsxJetman::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
		boost::shared_ptr<BobPhsxNormal> normal = boost::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
			normal->JetPack = true;
			normal->NumJumps = 1;
		}

		phsx->CapePrototype = CapeType_NONE;

		if ( boost::dynamic_pointer_cast<BobPhsxWheel>( phsx ) != 0 && 0 != normal )
		{
			phsx->JetpackModel = false;

			normal->ThrustPos1 = Vector2( -141, -75 );
			normal->ThrustPos2 = Vector2( 141, -75 );
			normal->ThrustDir1 = Vector2( -.4f, -.6f );
			normal->ThrustDir2 = Vector2( .4f, -.6f );

			//normal.ThrustPos1 = new Vector2(-101f, -70);
			//normal.ThrustPos2 = new Vector2(127f, -70);
			//normal.ThrustDir1 = new Vector2(-.4f, -.6f);
			//normal.ThrustDir2 = new Vector2(.4f, -.6f);

			normal->ThrustType = RocketThrustType_DOUBLE;
		}
		else
		{
			phsx->JetpackModel = true;

			normal->ThrustPos1 = Vector2( -45, -70 );
			normal->ThrustDir1 = Vector2( -.115f, -1.1f );
			normal->ThrustType = RocketThrustType_SINGLE;

			normal->ThrustPos_Duck = ThrustPos1 + Vector2( -35, 20 );
			normal->ThrustDir_Duck = Vector2( -.35f, -.8f );
		}
	}

	void BobPhsxJetman::SetJetmanObject( const boost::shared_ptr<ObjectClass> &obj )
	{
		if ( obj->QuadList.size() > 0 )
		{
			obj->FindQuad( std::wstring( L"Rocket" ) )->Show = true;
		}
	}

	void BobPhsxJetman::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 0, 2, 0 );
		Name = Localization::Words_JETMAN;
		Adjective = std::wstring( L"jetman" );

		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"HeroIcon_Jetman" ) ), Color::White, 1.1f * DefaultIconWidth );
		( boost::static_pointer_cast<PictureIcon>( Icon ) )->IconQuad->Quad_Renamed.Shift( Vector2( -.25f, -.01f ) );
	}

	const boost::shared_ptr<BobPhsxJetman> &BobPhsxJetman::getInstance()
	{
		return instance;
	}

	BobPhsxJetman::BobPhsxJetman()
	{
		// Pulled out to avoid using shared_from_this inside constructor.
		//Set( shared_from_this() );
	}
}
