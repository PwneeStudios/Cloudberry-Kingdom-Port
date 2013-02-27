#include <global_header.h>

namespace CloudberryKingdom
{

	void Challenge_TimeCrisis::InitializeStatics()
	{
		Challenge_TimeCrisis::instance = boost::make_shared<Challenge_TimeCrisis>();
	}

	// Statics
	boost::shared_ptr<Challenge_TimeCrisis> Challenge_TimeCrisis::instance;

	Challenge_TimeCrisis::OnSwapLambda::OnSwapLambda( const boost::shared_ptr<Challenge_TimeCrisis> &ch )
	{
		this->ch = ch;
	}

	void Challenge_TimeCrisis::OnSwapLambda::Apply( const boost::shared_ptr<LevelSeedData> &data )
	{
		data->MyGame->AddGameObject( boost::make_shared<TimeCrisis_Tutorial>( ch ) );
	}

	const boost::shared_ptr<Challenge_TimeCrisis> &Challenge_TimeCrisis::getInstance()
	{
		return instance;
	}

	Challenge_TimeCrisis::Challenge_TimeCrisis()
	{
		GameTypeId = 1;
		MenuName = Name = Localization::Words_TimeCrisis;
	}

	boost::shared_ptr<BobPhsx> Challenge_TimeCrisis::GetHero( int i )
	{
		return Challenge::ChosenHero;
	}

	void Challenge_TimeCrisis::PreStart_Tutorial( bool TemporarySkip )
	{
		HeroRush_Tutorial::TemporarySkip = TemporarySkip;
		MyStringWorld->OnSwapToFirstLevel->Add( boost::make_shared<OnSwapLambda>( boost::static_pointer_cast<Challenge_TimeCrisis>( shared_from_this() ) ) );
	}

	int Challenge_TimeCrisis::GetLength( int Index, float Difficulty )
	{
		int Length = Challenge_HeroRush::GetLength( Index, Difficulty );

		if ( Challenge::ChosenHero == BobPhsxRocketbox::getInstance() )
		{
			Length = (int)( Length * CoreMath.LerpRestrict(1.0f, 10.0f, Index / 1000.0f ) );
		}

		return Length;
	}
	boost::shared_ptr<LevelSeedData> Challenge_TimeCrisis::Make( int Index, float Difficulty )
	{
		std::vector<float> lerp_vec;

		lerp_vec.push_back(-.5f);
		lerp_vec.push_back(0);
		lerp_vec.push_back(1.5f);
		lerp_vec.push_back(2.75f);
		lerp_vec.push_back(3.5f);
		lerp_vec.push_back(4.25f);
		lerp_vec.push_back(5.0f);
		lerp_vec.push_back(5.5f);
		lerp_vec.push_back(6.5f);

		float difficulty = CoreMath::MultiLerpRestrict( Index / 20.0f, lerp_vec );
		
		boost::shared_ptr<LevelSeedData> data = Challenge_HeroRush::Make( Index, Difficulty );

		return data;
	}

	void Challenge_TimeCrisis::Start(int StartLevel)
	{
		Challenge_HeroRush::Start( StartLevel );

        CloudberryKingdomGame::SetPresence( CloudberryKingdomGame::Presence_TimeCrisis );
	}
}
