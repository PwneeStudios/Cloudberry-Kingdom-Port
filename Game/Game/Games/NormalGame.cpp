#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;

namespace CloudberryKingdom
{

	std::shared_ptr<GameData> NormalFactory::Make( const std::shared_ptr<LevelSeedData> &data, bool MakeInBackground )
	{
		return std::make_shared<NormalGameData>( data, MakeInBackground );
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

	NormalGameData::NormalGameData()
	{
	}

	NormalGameData::NormalGameData( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		Init( LevelSeed, MakeInBackground );
	}

	void NormalGameData::Init( const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		GameData::Init();

		AllowQuickJoin = true;
		DefaultHeroType = LevelSeed->DefaultHeroType;

		if ( !MakeInBackground )
			Tools::CurGameData = this;

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
		std::shared_ptr<Thread> MakeThread = std::make_shared<Thread>( std::make_shared<ThreadStart>( this->_MakeThreadFunc ) )
		{
	#if defined(WINDOWS)
			Name = _T( "MakeLevelThread" ),Priority = ThreadPriority::Normal,
	#else
			Name = _T( "MakeLevelThread" ),
	#endif
		};

		MakeThread->Start();
	}

	void NormalGameData::_MakeThreadFunc()
	{
		std::shared_ptr<LevelSeedData> LevelSeed = _MakeThreadLevelSeed;
		bool MakeInBackground = _MakeThreadMakeInBackground;

	#if defined(XBOX) && !defined(WINDOWS)
		const int tempVector[] = { 3 };
		Thread::CurrentThread->SetProcessorAffinity( std::vector<int>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) ) );
	#endif
		Tools::TheGame->Exiting += std::make_shared<EventHandler<EventArgs*> >( this, &NormalGameData::KillThread );

		MyLevel = LevelSeed->MakeLevel( this );

		if ( MyLevel->ReturnedEarly )
		{
			Tools::CurLevel = MyLevel;
			Tools::CurGameData = this;
		}

		Tools::LevelIsFinished();

		if ( !MakeInBackground )
			Tools::CurLevel = MyLevel;
		MyLevel->MyGame = this;

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
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		lock ( LevelSeed->Loaded )
		{
			Loading = false;
			LevelSeed->Loaded->setval( true );
			LevelSeed->MyGame = this;
		}

		// End the loading screen
		if ( !MakeInBackground )
		{
			Tools::EndLoadingScreen();
		}

		Tools::TheGame->Exiting -= KillThread;
	}

	void NormalGameData::PhsxStep()
	{
		GameData::PhsxStep();

		if ( Tools::AutoLoop )
		{
			Tools::AutoLoopDelay++;
			if ( Tools::AutoLoopDelay == 20 || Tools::AutoLoopDelay == 40 )
				for ( std::vector<EzSound*>::const_iterator snd = Tools::SoundWad->SoundList.begin(); snd != Tools::SoundWad->SoundList.end(); ++snd )
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
