#include <global_header.h>



namespace CloudberryKingdom
{

	void BobPhsxDouble::Set( const std::shared_ptr<BobPhsx> &phsx )
	{
		phsx->DoubleJumpModel = true;

		std::shared_ptr<BobPhsxNormal> normal = dynamic_cast<BobPhsxNormal*>( phsx );
		if ( 0 != normal )
		{
			normal->JetPack = false;
			normal->NumJumps = 2;
		}

		phsx->CapePrototype = Cape::CapeType_NONE;
	}

	void BobPhsxDouble::SetDoubleObject( const std::shared_ptr<ObjectClass> &obj, const std::shared_ptr<BobPhsx> &phsx )
	{
		if ( obj->QuadList.size() > 0 )
		{
			// Angel wings.
			//obj.FindQuad("Wing1").Show = true;
			//obj.FindQuad("Wing2").Show = true;
			//obj.FindQuad("Wings").Show = true;
			obj->FindQuad( _T( "Wings_Front" ) )->Show = true;
			obj->FindQuad( _T( "Wings_Back" ) )->Show = true;
			obj->FindQuad( _T( "Wings_Front" ) )->MyEffect = Tools::HslGreenEffect;
			obj->FindQuad( _T( "Wings_Back" ) )->MyEffect = Tools::HslGreenEffect;

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
		Adjective = _T( "double jump" );

		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "HeroIcon_Double" ) ), Color::White, 1.1f * DefaultIconWidth * 286 / 240 );
		( static_cast<PictureIcon*>( Icon ) )->IconQuad->Quad_Renamed->Shift( Vector2( -.3f,.085f ) );
	}

const std::shared_ptr<BobPhsxDouble> BobPhsxDouble::instance = std::make_shared<BobPhsxDouble>();

	const std::shared_ptr<BobPhsxDouble> &BobPhsxDouble::getInstance()
	{
		return instance;
	}

	BobPhsxDouble::BobPhsxDouble()
	{
		Set( this );
	}
}
