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
}
