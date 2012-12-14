#include <global_header.h>

#include <MasterHack.h>

namespace CloudberryKingdom
{

	std::shared_ptr<GameData> NormalFactory::Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		std::shared_ptr<NormalGameData> temp = std::make_shared<NormalGameData>( data, MakeInBackground );
		NormalGameData_Construct( temp, data, MakeInBackground );
		return std::static_pointer_cast<GameData>( temp );
	}

	void NormalGameData::SetCreatedBobParameters( const std::shared_ptr<Bob> &bob )
	{
		bob->Immortal = false;
		bob->ScreenWrap = false;
		bob->ScreenWrapToCenter = false;
	}

	void NormalGameData::SetAdditionalLevelParameters()
	{
		MyLevel->AllowRecording = true;
	}

	std::shared_ptr<GameFactory> NormalGameData::Factory = std::make_shared<NormalFactory>();

	NormalGameData::NormalGameData() :
		_MakeThreadMakeInBackground( false )
	{
		assert( !"Should not be called." );
	}

	NormalGameData::NormalGameData( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground ) :
		_MakeThreadMakeInBackground( false )
	{
		// Now in NormalGameData_Construct.
		// Init( LevelSeed, MakeInBackground );
	}

	void NormalGameData::Init( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		GameData::Init();

		AllowQuickJoin = true;
		DefaultHeroType = LevelSeed->DefaultHeroType;

		if ( !MakeInBackground )
			Tools::CurGameData = shared_from_this();

		//Tools.Recycle.Empty();
		Loading = true;

		if ( !MakeInBackground )
		{
			Tools::BeginLoadingScreen( !LevelSeed->NoMusicStart );
			if ( LevelSeed->OnBeginLoad != 0 )
				LevelSeed->OnBeginLoad->Apply();
		}

		_MakeThreadLevelSeed = LevelSeed;
		_MakeThreadMakeInBackground = MakeInBackground;
		// FIXME: Add threading.
		_MakeThreadFunc(); // WARNING: This is just to test the level construction without a thread.
	//	std::shared_ptr<Thread> MakeThread = std::make_shared<Thread>( std::make_shared<ThreadStart>( this->_MakeThreadFunc ) )
	//	{
	//#if defined(WINDOWS)
	//		Name = _T( "MakeLevelThread" ),Priority = ThreadPriority::Normal,
	//#else
	//		Name = _T( "MakeLevelThread" ),
	//#endif
	//	};

	//	MakeThread->Start();
	}

	void NormalGameData::_MakeThreadFunc()
	{
		std::shared_ptr<LevelSeedData> LevelSeed = _MakeThreadLevelSeed;
		bool MakeInBackground = _MakeThreadMakeInBackground;

		// FIXME: Related to threading.
	//#if defined(XBOX) && !defined(WINDOWS)
	//	const int tempVector[] = { 3 };
	//	Thread::CurrentThread->SetProcessorAffinity( VecFromArray( tempVector ) );
	//#endif
	//	Tools::TheGame->Exiting += std::make_shared<EventHandler<EventArgs*> >( shared_from_this(), &NormalGameData::KillThread );

		MyLevel = LevelSeed->MakeLevel( shared_from_this() );

		if ( MyLevel->ReturnedEarly )
		{
			Tools::CurLevel = MyLevel;
			Tools::CurGameData = shared_from_this();
		}

		Tools::LevelIsFinished();

		if ( !MakeInBackground )
			Tools::CurLevel = MyLevel;
		MyLevel->MyGame = shared_from_this();

		if ( MyLevel->SetToWatchMake )
		{
			Loading = false;
			Tools::EndLoadingScreen();
			return;
		}

		MyLevel->CanWatchComputer = MyLevel->CanWatchReplay = true;

		if ( MyLevel->SetToWatchMake )
			return;

		MakeBobs( MyLevel );
		SetAdditionalBobParameters( MyLevel->Bobs );

		MyLevel->Name = LevelSeed->Name;
		SetAdditionalLevelParameters();

		// Post process the level
		if ( LevelSeed->PostMake != 0 )
			LevelSeed->PostMake->Apply( MyLevel );

		// Final level reset
		MyLevel->PlayMode = 0;
		MyLevel->ResetAll( false, !MakeInBackground );

		// Mark the level as loaded
		LevelSeed->Loaded->MyMutex.Lock();
		{
			Loading = false;
			LevelSeed->Loaded->setval( true );
			LevelSeed->MyGame = shared_from_this();
		}
		LevelSeed->Loaded->MyMutex.Unlock();

		// End the loading screen
		if ( !MakeInBackground )
		{
			Tools::EndLoadingScreen();
		}

		// FIXME: Related to threading.
		//Tools::TheGame->Exiting -= KillThread;
	}

	void NormalGameData::PhsxStep()
	{
		GameData::PhsxStep();

		if ( Tools::AutoLoop )
		{
			Tools::AutoLoopDelay++;
			if ( Tools::AutoLoopDelay == 20 || Tools::AutoLoopDelay == 40 )
				for ( std::vector<std::shared_ptr<EzSound> >::const_iterator snd = Tools::SoundWad->SoundList.begin(); snd != Tools::SoundWad->SoundList.end(); ++snd )
					( *snd )->Play();
			if ( Tools::AutoLoopDelay > 60 )
			{
				Tools::AutoLoopDelay = 0;
				Tools::WorldMap->SetToReturnTo( 0 );
			}
		}
	}

	void NormalGameData::PostDraw()
	{
		GameData::PostDraw();
	}

	void NormalGameData::AdditionalReset()
	{
		GameData::AdditionalReset();

		if ( !MyLevel->Watching && MyLevel->Recording_Renamed && !( MyLevel->PlayMode != 0 || MyLevel->Watching ) )
			MyLevel->StartRecording();
	}

	void NormalGameData::BobDie( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob )
	{
		GameData::BobDie( level, bob );
	}

	void NormalGameData::BobDoneDying( const std::shared_ptr<Level> &level, const std::shared_ptr<Bob> &bob )
	{
		GameData::BobDoneDying( level, bob );
	}

}
