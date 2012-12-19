#include <global_header.h>

namespace CloudberryKingdom
{

	void BobPhsxDouble::InitializeStatics()
	{
		BobPhsxDouble::instance = boost::make_shared<BobPhsxDouble>();
	}

	// Statics
	boost::shared_ptr<BobPhsxDouble> BobPhsxDouble::instance;


	void BobPhsxDouble::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
		phsx->DoubleJumpModel = true;

		boost::shared_ptr<BobPhsxNormal> normal = boost::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
			normal->JetPack = false;
			normal->NumJumps = 2;
		}

		phsx->CapePrototype = CapeType_NONE;
	}

	void BobPhsxDouble::SetDoubleObject( const boost::shared_ptr<ObjectClass> &obj, const boost::shared_ptr<BobPhsx> &phsx )
	{
		if ( obj->QuadList.size() > 0 )
		{
			// Angel wings.
			//obj.FindQuad("Wing1").Show = true;
			//obj.FindQuad("Wing2").Show = true;
			//obj.FindQuad("Wings").Show = true;
			obj->FindQuad( std::wstring( L"Wings_Front" ) )->Show = true;
			obj->FindQuad( std::wstring( L"Wings_Back" ) )->Show = true;
			obj->FindQuad( std::wstring( L"Wings_Front" ) )->MyEffect = Tools::HslGreenEffect;
			obj->FindQuad( std::wstring( L"Wings_Back" ) )->MyEffect = Tools::HslGreenEffect;

			//BaseQuad quad = obj.FindQuad("Arm_Right");
			//if (quad != null) quad.Show = false;
			//else return;

			//obj.FindQuad("Arm_Left").Show = false;
			//bool feet = !(phsx is BobPhsxBox);
			//{
			//    obj.FindQuad("Foot_Left").Show = feet;
			//    obj.FindQuad("Foot_Right").Show = feet;
			//}
			//obj.FindQuad("Leg_Left").Show = false;
			//obj.FindQuad("Leg_Right").Show = false;
			//obj.FindQuad("Body").Show = false;
		}
	}

	void BobPhsxDouble::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 0, 1, 0 );
		Name = Localization::Words_DOUBLE_JUMP;
		Adjective = std::wstring( L"double jump" );

		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"HeroIcon_Double" ) ), Color::White, 1.1f * DefaultIconWidth * 286 / 240 );
		( boost::static_pointer_cast<PictureIcon>( Icon ) )->IconQuad->Quad_Renamed.Shift( Vector2( -.3f,.085f ) );
	}

	const boost::shared_ptr<BobPhsxDouble> &BobPhsxDouble::getInstance()
	{
		return instance;
	}

	BobPhsxDouble::BobPhsxDouble()
	{
		// Pulled out to avoid using shared_from_this inside constructor.
		//Set( shared_from_this() );
	}
}
