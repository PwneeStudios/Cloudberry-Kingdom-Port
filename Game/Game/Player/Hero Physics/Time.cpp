#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	void BobPhsxTime::InitializeStatics()
	{
		BobPhsxTime::instance = boost::make_shared<BobPhsxTime>();
			InitBobPhsxSingleton( BobPhsxTime::instance );
	}

	// Statics
	boost::shared_ptr<BobPhsxTime> BobPhsxTime::instance;


	void BobPhsxTime::InitSingleton()
	{
		BobPhsxNormal::InitSingleton();

		Specification = HeroSpec( 0, 0, 0, 1 );
		Name = Localization::Words_TIME_MASTER;
		Adjective = std::wstring( L"Chrono" );
		Icon = boost::make_shared<PictureIcon>( Tools::TextureWad->FindByName( std::wstring( L"HeroIcon_Classic" ) ), Color::White, 1.2f * DefaultIconWidth );
	}

	const boost::shared_ptr<BobPhsxTime> &BobPhsxTime::getInstance()
	{
		return instance;
	}

	boost::shared_ptr<BobPhsx> BobPhsxTime::Clone()
	{
		boost::shared_ptr<BobPhsxTime> newBob = boost::make_shared<BobPhsxTime>();
			InitBobPhsxSingleton( newBob );
		CopyTo( newBob );
		return boost::static_pointer_cast<BobPhsxTime>( newBob );
	}

	void BobPhsxTime::CopyTo( const boost::shared_ptr<BobPhsxTime> &bob )
	{
		BobPhsxNormal::CopyTo( boost::static_pointer_cast<BobPhsxNormal>( bob ) );

		bob->CurBehavior = CurBehavior;
		bob->BehaviorLength = BehaviorLength;
	}

	BobPhsxTime::BobPhsxTime() :
		CurBehavior( Behavior_PAUSE ),
		BehaviorLength( 0 )
	{
		InitializeInstanceFields();
		// Pulled out to avoid using shared_from_this inside constructor.
		//Set( shared_from_this() );
		DefaultValues();
	}

	void BobPhsxTime::Set( const boost::shared_ptr<BobPhsx> &phsx )
	{
		Set( phsx, Vector2(1) );
	}

	void BobPhsxTime::Set( const boost::shared_ptr<BobPhsx> &phsx, Vector2 modsize )
	{
		phsx->UseGroundSpeed = false;

		boost::shared_ptr<BobPhsxNormal> normal = boost::dynamic_pointer_cast<BobPhsxNormal>( phsx );
		if ( 0 != normal )
		{
		}
	}

	void BobPhsxTime::Init( const boost::shared_ptr<Bob> &bob )
	{
		BobPhsxNormal::Init( bob );
	}

	void BobPhsxTime::PhsxStep()
	{
		BobPhsxNormal::PhsxStep();
	}

	void BobPhsxTime::LandOnSomething( bool MakeReadyToJump, const boost::shared_ptr<ObjectBase> &ThingLandedOn )
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

	void BobPhsxTime::ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style )
	{
		BobPhsxNormal::ModData( makeData, Style );

		Style->TimeType = TimeTypes_X_SYNC;
	}

	void BobPhsxTime::InitializeInstanceFields()
	{
		CurBehavior = Behavior_PAUSE;
	}
}
