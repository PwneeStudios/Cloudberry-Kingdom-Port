#include <global_header.h>
namespace CloudberryKingdom
{

	void BobPhsxTime::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 0, 0, 1 );
		Name = Localization::Words_TIME_MASTER;
		Adjective = _T( "Chrono" );
		Icon = std::make_shared<PictureIcon>( Tools::TextureWad->FindByName( _T( "HeroIcon_Classic" ) ), Color::White, 1.2f * DefaultIconWidth );
	}

const std::shared_ptr<BobPhsxTime> BobPhsxTime::instance = std::make_shared<BobPhsxTime>();

	const std::shared_ptr<BobPhsxTime> &BobPhsxTime::getInstance()
	{
		return instance;
	}

	BobPhsxTime::BobPhsxTime()
	{
		InitializeInstanceFields();
		Set( shared_from_this() );
	}

	void BobPhsxTime::Set( const std::shared_ptr<BobPhsx> &phsx )
	{
		Set( phsx, Vector2(1) );
	}

	void BobPhsxTime::Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize )
	{
		phsx->UseGroundSpeed = false;

		std::shared_ptr<BobPhsxNormal> normal = std::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
		}
	}

	void BobPhsxTime::Init( const std::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );
	}

	void BobPhsxTime::PhsxStep()
	{
		BobPhsxNormal::PhsxStep();
	}

	void BobPhsxTime::LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn )
	{
		BobPhsxNormal::LandOnSomething( MakeReadyToJump, ThingLandedOn );
	}

	void BobPhsxTime::GenerateInput( int CurPhsxStep )
	{
		BobPhsxNormal::GenerateInput( CurPhsxStep );

		// Change behavior
		if ( CurPhsxStep < 10 )
		{
			CurBehavior = Behavior_PAUSE;
			BehaviorLength = 0;
		}
		else
		{
			if ( BehaviorLength == 0 )
			{
				if ( getMyLevel()->getRnd()->RndFloat() > 0.7f )
				{
					CurBehavior = Behavior_PAUSE;
					BehaviorLength = getMyLevel()->getRnd()->RndInt(5, 10);
					//BehaviorLength = MyLevel.Rnd.RndInt(5, 40);
				}
				else
				{
					CurBehavior = Behavior_REGULAR;
					BehaviorLength = getMyLevel()->getRnd()->RndInt(25, 60);
				}
			}
			else
				BehaviorLength--;
		}

		// Act according to behavior
		switch ( CurBehavior )
		{
			case Behavior_PAUSE:
				MyBob->CurInput.xVec.X = 0;
				break;
			case Behavior_REGULAR:
				break;
		}
	}

	void BobPhsxTime::ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style )
	{
		BobPhsxNormal::ModData( makeData, Style );

		Style->TimeType = TimeTypes_X_SYNC;
	}

	void BobPhsxTime::InitializeInstanceFields()
	{
		CurBehavior = Behavior_PAUSE;
	}
}
