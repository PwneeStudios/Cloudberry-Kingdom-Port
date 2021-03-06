#include "MasterHack.h"

#include <small_header.h>

#include <Hacks/List.h>

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <Core\Animation\AnimQueue.h>

#include "Game/Menus/Concrete Menus/Loading Screen/ILoadingScreen.h"
#include "Game/Menus/Concrete Menus/Loading Screen/LoadingScreen.h"
#include "Core/Text/EzText.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/Doll.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/GamerTag.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/HeroLevel.h"
#include "Game/Games/GameType.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Player/PlayerData.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/Waiting.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/JoinText.h"
#include "Game/Menus/Menu Components/MenuList.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Player/Awardments/Awardment.h"
#include "Game/Tools/Recycler.h"
#include "Game/Games/ActionGame.h"
#include "Game/Games/NormalGame.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
#include "Game/Games/ScreenSaver.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld_Endurance.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Lives.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Score.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"
#include "Game/Objects/Game Objects/GameObjects/TimerWarning.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGameBase.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_NextLife.h"
#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"

namespace CloudberryKingdom
{

	void ReleaseLoadingScreen( boost::shared_ptr<ILoadingScreen> loadingscreen )
	{
		boost::shared_ptr<LoadingScreen> ls = boost::dynamic_pointer_cast<LoadingScreen>( loadingscreen );
		
		if ( 0 == ls ) return;

		if ( ls->BackgroundQuad != 0 )
		{
			ls->BackgroundQuad->Release();
			ls->BackgroundQuad.reset();
		}

		if ( ls->BlackQuad != 0)
		{
			ls->BlackQuad->Release();
			ls->BlackQuad.reset();
		}

		if ( ls->CenterObject != 0)
		{
			ls->CenterObject->Release();
			ls->CenterObject.reset();
		}

		if ( ls->HintText != 0)
		{
			ls->HintText->Release();
			ls->HintText.reset();
		}

		if ( ls->LoadingText != 0)
		{
			ls->LoadingText->Release();
			ls->LoadingText.reset();
		}

		if ( ls->TextObject != 0)
		{
			ls->TextObject->Release();
			ls->TextObject.reset();
		}
	}

	void InitBobPhsxSingleton( const boost::shared_ptr<BobPhsx> &This )
	{
		if ( !This->SingletonInitialized )
			This->InitSingleton();
	}

	void CharacterSelect_PostConstruct( const boost::shared_ptr<CharacterSelect> &This, int PlayerIndex, bool QuickJoin )
	{
		boost::shared_ptr<GameData> game = Tools::CurGameData;

		Tools::StartGUIDraw();

		This->PlayerIndex = PlayerIndex;
		This->QuickJoin = QuickJoin;

		This->InitCenters();
		This->Center = This->Centers[ PlayerIndex ];
		This->NormalZoomCenter = This->Center;

		This->MyDoll = MakeMagic( Doll, ( PlayerIndex, This->shared_from_this() ) );
		This->MyGamerTag = MakeMagic( GamerTag, ( PlayerIndex, This->shared_from_this() ) );
		This->MyHeroLevel = MakeMagic( HeroLevel, ( PlayerIndex, This->shared_from_this() ) );
		game->AddGameObject( This->MyDoll );
		game->AddGameObject( This->MyGamerTag );
		game->AddGameObject( This->MyHeroLevel );

		This->InitColorScheme( PlayerIndex );

        if ( QuickJoin && PlayerIndex >= 0 && PlayerManager::Get( PlayerIndex ) != 0 && PlayerManager::Get( PlayerIndex )->Exists)
        {
            This->Fake = true;
            game->AddGameObject( MakeMagic( Waiting, (PlayerIndex, This->shared_from_this(), false) ) );
        }
        else
        {
            This->Fake = false;
            game->AddGameObject( MakeMagic( JoinText, (PlayerIndex, This->shared_from_this() ) ) );
        }

		Tools::EndGUIDraw();
	}


	void MenuList_PostConstruct( const boost::shared_ptr<MenuList> &This )
	{
		This->setOverrideA( false );

	#if defined(PC_VERSION)
		This->Padding.Y = 7;
		This->setExpandOnGo( true );
	#endif

		This->InitializeArrows();
	}

	void Bob_PostConstruct( const boost::shared_ptr<Bob> &This, const boost::shared_ptr<BobPhsx> &type, bool boxesOnly )
	{
		This->SetHeroPhsx( This->MyHeroType );
		This->SetColorScheme( This->MyHeroType->Prototype->MyColorScheme );
	}

	void Awardment_PostConstruct( const boost::shared_ptr<Awardment> &This )
	{
		if ( This->Unlockable != 0 )
			This->Unlockable->AssociatedAward = This->shared_from_this();

		Awardments::Awards.push_back( This->shared_from_this() );
	}

	void Quad_PostConstruct( const boost::shared_ptr<Quad> &This, const boost::shared_ptr<Quad> &quad, bool DeepClone )
	{
		This->InitVertices();

		quad->Center->Clone( This->Center, DeepClone );
		quad->xAxis->Clone( This->xAxis, DeepClone );
		quad->yAxis->Clone( This->yAxis, DeepClone );
		for ( int i = 0; i < 4; i++ )
			quad->Corner[ i ]->Clone( This->Corner[ i ], DeepClone );

		for ( int i = 0; i < This->NumVertices; i++ )
			This->Vertices[ i ] = quad->Vertices[ i ];
	}

	void ObjectClass_PostConstruct( const boost::shared_ptr<ObjectClass> &This, const boost::shared_ptr<QuadDrawer> &Drawer, const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height, const boost::shared_ptr<EzEffect> &BaseEffect, const boost::shared_ptr<EzTexture> &BaseTexture )
	{
		This->VersionNumber = ObjectClass::ObjectClassVersionNumber;

		This->AnimQueue = std::queue<boost::shared_ptr<AnimQueueEntry> >();

		This->CenterFlipOnBox = true;

		This->ParentQuad = boost::make_shared<Quad>();
		This->ParentQuad->InitVertices();
		This->ParentQuad->SetColor( Color( 1.f, 1.f, 1.f ) );
		This->ParentQuad->ParentObject = This->shared_from_this();
		This->ParentQuad->MyEffect = BaseEffect;
		This->ParentQuad->MyTexture = BaseTexture;

		This->QuadList = std::vector<boost::shared_ptr<BaseQuad> >();
		This->BoxList = std::vector<boost::shared_ptr<ObjectBox> >();

		This->AnimLength = std::vector<int>( 50 );
		This->AnimSpeed = std::vector<float>( 50 );
		This->AnimName = std::vector<std::wstring>( 50 );
		for ( int i = 0; i < 50; i++ )
		{
			This->AnimName[ i ] = std::wstring( L"Anim_" ) + StringConverterHelper::toString( i );
			This->AnimSpeed[ i ] = 1;
		}

		This->QDrawer = Drawer;

		if ( Height > 0 && Width > 0 )
			This->InitRenderTargets( device, pp, Width, Height );

		This->UpdateEffectList();
	}

	void ObjectClass_PostConstruct_3params( const boost::shared_ptr<ObjectClass> &This, const boost::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone )
	{
		This->InitializeInstanceFields();
		This->LoadingRunSpeed = obj->LoadingRunSpeed;

		This->CapeThickness = obj->CapeThickness;
		This->p1_Left = obj->p1_Left;
		This->p2_Left = obj->p2_Left;
		This->p1_Right = obj->p1_Right;
		This->p2_Right = obj->p2_Right;



		This->Linear = obj->Linear;

		This->VersionNumber = obj->VersionNumber;

		This->BoxesOnly = _BoxesOnly;

		This->LoadingRunSpeed = obj->LoadingRunSpeed;

		This->AnimQueue = std::queue<boost::shared_ptr<AnimQueueEntry> >();
		std::queue<boost::shared_ptr<AnimQueueEntry> > QueueCopy = std::queue<boost::shared_ptr<AnimQueueEntry> >( obj->AnimQueue );
		std::vector<boost::shared_ptr<AnimQueueEntry> > array_Renamed;
		while( !QueueCopy.empty() )
		{
			array_Renamed.push_back( QueueCopy.front() );
			QueueCopy.pop();
		}

		// FIXME: Make sure make_shared actually copies the object.
		if ( array_Renamed.size() > 0 )
		{
			This->LastAnimEntry = boost::make_shared<AnimQueueEntry>( array_Renamed[ array_Renamed.size() - 1 ] );
			for ( size_t i = 0; i < array_Renamed.size() - 1; i++ )
				This->AnimQueue.push( boost::make_shared<AnimQueueEntry>( array_Renamed[ i ] ) );
			This->AnimQueue.push( This->LastAnimEntry );
		}



		This->CenterFlipOnBox = obj->CenterFlipOnBox;

		This->ParentQuad = boost::make_shared<Quad>( obj->ParentQuad, DeepClone );
		Quad_PostConstruct( This->ParentQuad, obj->ParentQuad, DeepClone );
		This->ParentQuad->ParentObject = This->shared_from_this();
		This->ParentQuad->MyEffect = obj->ParentQuad->MyEffect;
		This->ParentQuad->MyTexture = obj->ParentQuad->MyTexture;

		This->MySkinTexture = obj->MySkinTexture;
		This->MySkinEffect = obj->MySkinEffect;

		// Add quads and boxes            
		if ( !This->BoxesOnly )
		{
			This->QuadList = std::vector<boost::shared_ptr<BaseQuad> >();

			for ( std::vector<boost::shared_ptr<BaseQuad> >::const_iterator quad = obj->QuadList.begin(); quad != obj->QuadList.end(); ++quad )
			{
				if ( dynamic_cast<Quad*>( ( *quad ).get() ) != 0 )
				{
					// FIXME: Check static_pointer_cast.
					boost::shared_ptr<Quad> nquad = boost::make_shared<Quad>( boost::static_pointer_cast<Quad>( *quad ), DeepClone );
					Quad_PostConstruct( nquad, boost::static_pointer_cast<Quad>( *quad ), DeepClone );
					This->QuadList.push_back( nquad );
					nquad->ParentObject = This->shared_from_this();
					if ( ( *quad )->ParentQuad == ( *quad )->ParentObject->ParentQuad )
						This->ParentQuad->AddQuadChild( nquad );
				}
			}
		}

		// Clone boxes
		This->BoxList = std::vector<boost::shared_ptr<ObjectBox> >();
		for ( std::vector<boost::shared_ptr<ObjectBox> >::const_iterator box = obj->BoxList.begin(); box != obj->BoxList.end(); ++box )
			This->BoxList.push_back( boost::make_shared<ObjectBox>( *box, DeepClone ) );


		// Make sure pointers match up
		if ( !This->BoxesOnly && This->QuadList.size() > 0 )
		{
			for ( size_t i = 0; i < obj->QuadList.size(); i++ )
			{
				// Preserve Parent-Point relationship (for quads attached to splines)
				if ( dynamic_cast<Quad*>( obj->QuadList[ i ].get() ) != 0 )
				{
					// FIXME: Check static_pointer_cast.
					boost::shared_ptr<BaseQuad> parent = ( boost::static_pointer_cast<Quad>( obj->QuadList[ i ] ) )->Center->ParentQuad;
					if ( parent != 0 )
					{
						if ( parent == obj->ParentQuad )
							( boost::static_pointer_cast<Quad>( This->QuadList[ i ] ) )->Center->ParentQuad = This->ParentQuad;
						else
						{
							int j = IndexOf( obj->QuadList, parent );
							( boost::static_pointer_cast<Quad>( This->QuadList[ i ] ) )->Center->ParentQuad = This->QuadList[ j ];
						}
					}
				}

				// Preserve Parent-Child quad relationship
				if ( obj->QuadList[ i ]->ParentQuad != obj->ParentQuad )
				{
					//((Quad)QuadList[obj.QuadList.IndexOf(obj.QuadList[i].ParentQuad)]).AddQuadChild(QuadList[i]);
					//((Quad)                               QuadList[obj.QuadList.IndexOf(                                obj.QuadList[i].ParentQuad)]).          AddQuadChild(QuadList[i]);
					( boost::static_pointer_cast<Quad>( This->QuadList[ IndexOf<boost::shared_ptr<BaseQuad> >( obj->QuadList, obj->QuadList[ i ]->ParentQuad ) ] ) )->AddQuadChild( This->QuadList[ i ] );
				}
			}
		}
		for ( size_t i = 0; i < obj->BoxList.size(); i++ )
		{
			if ( !This->BoxesOnly && obj->BoxList[ i ]->BL->ParentQuad != obj->ParentQuad )
			{
				//BoxList[i].TR.ParentQuad = BoxList[i].BL.ParentQuad = (Quad)QuadList[obj.QuadList.IndexOf(obj.BoxList[i].BL.ParentQuad)];
				//    BoxList[i].TR.ParentQuad	   =       BoxList[i].BL.ParentQuad     = (Quad)							    QuadList[obj.QuadList.IndexOf(obj.BoxList[i].BL.ParentQuad)];
				This->BoxList[ i ]->TR->ParentQuad = This->BoxList[ i ]->BL->ParentQuad = boost::static_pointer_cast<Quad>( This->QuadList[ IndexOf( obj->QuadList, obj->BoxList[ i ]->BL->ParentQuad ) ] );
			}
			else
				This->BoxList[ i ]->TR->ParentQuad = This->BoxList[ i ]->BL->ParentQuad = This->ParentQuad;
		}


		This->Play = obj->Play;
		This->Loop = obj->Loop;
		This->anim = obj->anim;
		This->t = obj->t;

		This->AnimLength = std::vector<int>( 50 );
		//obj->AnimLength.CopyTo( AnimLength, 0 );
		//This->AnimLength.assign( obj->AnimLength.begin(), obj->AnimLength.end() );
		CopyFromTo( obj->AnimLength, This->AnimLength );

		This->AnimSpeed = std::vector<float>( 50 );
		//obj->AnimSpeed.CopyTo( AnimSpeed, 0 );
		//This->AnimSpeed.assign( obj->AnimSpeed.begin(), obj->AnimSpeed.end() );
		CopyFromTo( obj->AnimSpeed, This->AnimSpeed );

		This->AnimName = std::vector<std::wstring>( 50 );
		//obj->AnimName.CopyTo( AnimName, 0 );
		//This->AnimName.assign( obj->AnimName.begin(), obj->AnimName.end() );
		CopyFromTo( obj->AnimName, This->AnimName );

		This->QDrawer = obj->QDrawer;

		This->InitRenderTargets( obj );

		This->UpdateEffectList();
	}

	boost::shared_ptr<GameData> GameData_Construct( const boost::shared_ptr<GameData> &This )
	{
		This->InitializeInstanceFields();

		This->CreationTime = Tools::TheGame->DrawCount;

		This->Recycle = Recycler::GetRecycler();

		This->EndGame = boost::make_shared<GameData::FinishProxy>( This->shared_from_this() );

		This->Loading = false;

		This->CurToDo = std::vector<boost::shared_ptr<ToDoItem> >();
		This->NextToDo = std::vector<boost::shared_ptr<ToDoItem> >();

		return This;
	}

	boost::shared_ptr<ActionGameData> ActionGameData_Construct( const boost::shared_ptr<ActionGameData> &This )
	{
		GameData_Construct( boost::static_pointer_cast<GameData>( This ) );

		This->InitializeInstanceFields();

		return This;
	}

	
	boost::shared_ptr<ActionGameData> ActionGameData_Construct( const boost::shared_ptr<ActionGameData> &This, const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		GameData_Construct( boost::static_pointer_cast<GameData>( This ) );

		This->InitializeInstanceFields();
		This->Init( LevelSeed, MakeInBackground );

		return This;
	}

	boost::shared_ptr<NormalGameData> NormalGameData_Construct( const boost::shared_ptr<NormalGameData> &This, const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground )
	{
		GameData_Construct( boost::static_pointer_cast<GameData>( This ) );

		This->Init( LevelSeed, MakeInBackground );

		return This;
	}

	boost::shared_ptr<StringWorldGameData> StringWorldGameData_Construct( const boost::shared_ptr<StringWorldGameData> &This )
	{
		GameData_Construct( boost::static_pointer_cast<GameData>( This ) );

		This->InitializeInstanceFields();

		return This;
	}

	boost::shared_ptr<StringWorldGameData> StringWorldGameData_Construct( const boost::shared_ptr<StringWorldGameData> &This, const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed )
	{
		GameData_Construct( boost::static_pointer_cast<GameData>( This ) );

		This->InitializeInstanceFields();
		This->GetSeedFunc = GetSeed;

		return This;
	}

	boost::shared_ptr<ScreenSaver> ScreenSaver_Construct( const boost::shared_ptr<ScreenSaver> &This )
	{
		StringWorldGameData_Construct( boost::static_pointer_cast<StringWorldGameData>( This ) );

		This->InitializeInstanceFields();
		This->Constructor();

		return This;
	}

	boost::shared_ptr<StringWorldEndurance> StringWorldEndurance_Construct( const boost::shared_ptr<StringWorldEndurance> &This, const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife )
	{
		StringWorldGameData_Construct( boost::static_pointer_cast<StringWorldGameData>( This ), GetSeed );

		// Lives
		This->Gui_LivesLeft = Gui_LivesLeft;
		This->Gui_Lives = MakeMagic( GUI_Lives, ( Gui_LivesLeft ) );
		This->Gui_NextLife = boost::make_shared<GUI_NextLife>( NextLife, Gui_LivesLeft );

		// Coin score multiplier
		This->MyCoinScoreMultiplier = boost::make_shared<CoinScoreMultiplierObject>();

		// Level and Score
		This->MyGUI_Score = MakeMagic( GUI_Score, ( false ) ) ;
		This->MyGUI_Level = MakeMagic( GUI_Level, ( false ) );

		// Add game objects, including 'Perfect' watcher
		This->OnSwapToFirstLevel->Add( boost::make_shared<StringWorldEndurance::OnSwapLambda>( boost::static_pointer_cast<StringWorldEndurance>( This->shared_from_this() ) ) );

		return This;
	}

	boost::shared_ptr<StringWorldTimed> StringWorldTimed_Construct( const boost::shared_ptr<StringWorldTimed> &This, const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_Timer> &Timer )
	{
		StringWorldGameData_Construct( boost::static_pointer_cast<StringWorldGameData>( This ), GetSeed );

		This->MyGUI_Timer = Timer;

		This->Warning = boost::make_shared<TimerWarning>();
		This->Warning->MyTimer = Timer;

		This->MyGUI_Score = MakeMagic( GUI_Score, ( true ) );
		This->MyGUI_Level = MakeMagic( GUI_Level, ( true ) );

		Timer->OnTimeExpired->Add( boost::make_shared<StringWorldTimed::StringWorldOnTimerExpiredLambda>( This->MyGUI_Score, This->MyGUI_Level ) );

		// Coin score multiplier
		This->MyCoinScoreMultiplier = boost::make_shared<CoinScoreMultiplierObject>();

		// Add 'Perfect' watcher
		This->OnSwapToFirstLevel->Add( boost::make_shared<StringWorldTimed::OnSwapLambda>( boost::static_pointer_cast<StringWorldTimed>( This->shared_from_this() ) ) );

		return This;
	}

	boost::shared_ptr<TitleGameData> TitleGameData_Construct( const boost::shared_ptr<TitleGameData> &This )
	{
		GameData_Construct( boost::static_pointer_cast<GameData>( This ) );

		This->InitializeInstanceFields();
		This->LockLevelStart = false;
		This->SuppressQuickSpawn = true;

		This->Init();

		Tools::CurGameData->SuppressQuickSpawn = true;
		Tools::CurGameData->SuppressSongInfo = true;

		return This;
	}

	boost::shared_ptr<TitleGameData_MW> TitleGameData_MW_Construct( const boost::shared_ptr<TitleGameData_MW> &This )
	{
		TitleGameData_Construct( boost::static_pointer_cast<TitleGameData>( This ) );

		return This;
	}
}