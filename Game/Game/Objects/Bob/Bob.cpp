#include <global_header.h>

#include "Hacks/List.h"
#include "Hacks/String.h"

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <MasterHack.h>

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"

namespace CloudberryKingdom
{

	void Bob::InitializeStatics()
	{
		typedef std::pair<BobDeathType, Localization::Words> DeathNamePair;
		Bob::BobDeathNames = std::map<BobDeathType, Localization::Words>();
		
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_NONE, Localization::Words_None ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_FIREBALL, Localization::Words_Fireball ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_FIRE_SPINNER, Localization::Words_Firespinner ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_BOULDER, Localization::Words_Boulder ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_SPIKEY_GUY, Localization::Words_SpikeyGuy ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_SPIKE, Localization::Words_Spike ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_FALL, Localization::Words_Falling ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_LAVA, Localization::Words_Lava ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_BLOB, Localization::Words_FlyingBlobs ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_LASER, Localization::Words_Laser ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_LAVA_FLOW, Localization::Words_Sludge ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_FALLING_SPIKE, Localization::Words_FallingSpikey ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_SERPENT, Localization::Words_Serpent ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_TIME, Localization::Words_TimeLimit ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_LEFT_BEHIND, Localization::Words_LeftBehind ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_OTHER, Localization::Words_Other ) );
		Bob::BobDeathNames.insert( DeathNamePair( BobDeathType_TOTAL, Localization::Words_Total ) );

		Bob::AllExplode = true;
		Bob::ShowCorpseAfterExplode = false;
		Bob::ImmortalLength = 55;

		Bob::JumpSound_Default = 0; Bob::DieSound_Default = 0;
		boost::shared_ptr<BobPhsx> tempVector[] = { BobPhsxNormal::getInstance(), BobPhsxJetman::getInstance(), BobPhsxDouble::getInstance(), BobPhsxSmall::getInstance(), BobPhsxWheel::getInstance(), BobPhsxSpaceship::getInstance(), BobPhsxBox::getInstance(), BobPhsxBouncy::getInstance(), BobPhsxRocketbox::getInstance(), BobPhsxBig::getInstance(), BobPhsxScale::getInstance(), BobPhsxInvert::getInstance() };
		Bob::HeroTypes = VecFromArray( tempVector );

		Bob::GuideActivated = false;
		Bob::GuideQuad = 0;

		Bob::GuideLength = 8;
		Bob::Guide_h = 1.f / GuideLength;
	}

	// Statics
	std::map<BobDeathType, Localization::Words> Bob::BobDeathNames;
	bool Bob::AllExplode;
	bool Bob::ShowCorpseAfterExplode;
	int Bob::ImmortalLength;

	boost::shared_ptr<EzSound> Bob::JumpSound_Default, Bob::DieSound_Default;
	std::vector<boost::shared_ptr<BobPhsx> > Bob::HeroTypes;

	bool Bob::GuideActivated;
	boost::shared_ptr<QuadClass> Bob::GuideQuad;

	int Bob::GuideLength;
	float Bob::Guide_h;



	void Bob::BobMove::Init()
	{
		MaxTargetY = 600;
		MinTargetY = -500;

		Copy = -1;
	}

	void Bob::ResetLightSourceFade()
	{
		LightSourceFade = 1;
		LightSourceFadeVel = 0;
	}

	void Bob::SetLightSourceToFade()
	{
		LightSourceFadeVel = -.022f;
	}

	void Bob::SetLightSourceToFadeIn()
	{
		LightSourceFadeVel = .022f;
		LightSourceFade = 0;
	}

	void Bob::DoLightSourceFade()
	{
		LightSourceFade += LightSourceFadeVel;
		CoreMath::Restrict( 0, 1, LightSourceFade );
	}

	void Bob::SetToFadeIn()
	{
		FadingIn = true;
		Fade = 0;
	}

	void Bob::Release()
	{
		ObjectBase::Release();

		ControlFunc.reset();
		OnLand.reset();
		OnApexReached.reset();
		OnAnimFinish.reset();

		MyPiece.reset();
		if ( MyRecord != 0 )
			MyRecord->Release();
			MyRecord.reset();

		if ( MyBobLinks.size() > 0 )
			for ( std::vector<boost::shared_ptr<BobLink> >::const_iterator link = MyBobLinks.begin(); link != MyBobLinks.end(); ++link )
				( *link )->Release();
		MyBobLinks.clear();

		if ( MyCape != 0 )
			MyCape->Release();
			MyCape.reset();

		if ( MyPhsx != 0 )
			MyPhsx->Release();
			MyPhsx.reset();

		if ( PlayerObject != 0 )
			PlayerObject->Release();
			PlayerObject.reset();

		if ( temp != 0 )
			temp->Release();
			temp.reset();
	}

	void Bob::SetObject( const boost::shared_ptr<ObjectClass> &obj, bool boxesOnly )
	{
		if ( PlayerObject != 0 )
			PlayerObject->Release();

		PlayerObject = boost::make_shared<ObjectClass>( obj, BoxesOnly, false );
		ObjectClass_PostConstruct_3params( PlayerObject, obj, BoxesOnly, false );

		Vector2 size = PlayerObject->BoxList[ 0 ]->Size();
		float ratio = size.Y / size.X;
		int width = Tools::TheGame->Resolution.Bob_Renamed.X;

		//PlayerObject.FinishLoading();
		PlayerObject->FinishLoading( Tools::QDrawer, Tools::Device, Tools::TextureWad, Tools::EffectWad, Tools::Device->PP, width, static_cast<int>( width * ratio ), false );

		Head.reset();
	}

	void Bob::SetColorScheme( ColorScheme scheme )
	{
		//scheme = ColorSchemeManager.ColorSchemes[2];
		//Tools::Write(scheme.ToString());

		if ( BoxesOnly || PlayerObject->QuadList.empty() )
			return;

		if ( scheme.HatData == 0 )
			scheme.HatData = Hat::None;
		if ( scheme.BeardData == 0 )
			scheme.BeardData = Hat::None;

		if ( CanHaveHat )
		{
			boost::shared_ptr<CloudberryKingdom::BaseQuad> head = PlayerObject->FindQuad( std::wstring( L"Head" ) );
			//if (null != head) head.Show = scheme.HatData.DrawHead;
			if ( 0 != head )
				head->Show = false;

			for ( std::vector<boost::shared_ptr<BaseQuad> >::const_iterator quad = PlayerObject->QuadList.begin(); quad != PlayerObject->QuadList.end(); ++quad )
			{
				if ( Contains( ( *quad )->Name, std::wstring( L"Hat_" ) ) )
				{
					boost::shared_ptr<Quad> _Quad = boost::dynamic_pointer_cast<Quad>( *quad );
					if ( CompareIgnoreCase( ( *quad )->Name, scheme.HatData->QuadName ) == 0 )
					{
						( *quad )->Show = scheme.HatData->DrawSelf;

						if ( 0 != _Quad )
							_Quad->ShowChildren();
					}
					else
					{
						( *quad )->Show = false;
						if ( 0 != _Quad )
							_Quad->HideChildren();
					}
				}

				if ( Contains( ( *quad )->Name, std::wstring( L"Facial_" ) ) )
				{
					boost::shared_ptr<Quad> _Quad = boost::dynamic_pointer_cast<Quad>( *quad );

					if ( scheme.SkinColor->Clr.A != 0 && 
                        !( scheme.HatData != 0 && !scheme.HatData->DrawHead ) && CompareIgnoreCase( ( *quad )->Name, scheme.BeardData->QuadName ) == 0 )
					{
						( *quad )->Show = scheme.BeardData->DrawSelf;

						if ( 0 != _Quad )
							_Quad->ShowChildren();
					}
					else
					{
						( *quad )->Show = false;
						if ( 0 != _Quad )
							_Quad->HideChildren();
					}
				}
			}
		}


		boost::shared_ptr<CloudberryKingdom::BaseQuad> q = PlayerObject->FindQuad( std::wstring( L"MainQuad" ) );
		if ( q != 0 )
		{
			q->setMyMatrix( scheme.SkinColor->M );

            if ( scheme.SkinColor->Clr.A == 0 )
            {
                q->MyEffect = Tools::BasicEffect;
                q->SetColor( Color::Transparent );
            }
            else
            {
                q->MyEffect = Tools::HslGreenEffect;
                q->SetColor( Color::White );
            }

			boost::shared_ptr<CloudberryKingdom::BaseQuad> wf = PlayerObject->FindQuad( std::wstring( L"Wings_Front" ) );
			if ( wf != 0 )
				wf->setMyMatrix( scheme.SkinColor->M );
			boost::shared_ptr<CloudberryKingdom::BaseQuad> wb = PlayerObject->FindQuad( std::wstring( L"Wings_Back" ) );
			if ( wb != 0 )
				wb->setMyMatrix( scheme.SkinColor->M );
		}

		if ( MyCape != 0 )
		{
			if ( scheme.CapeColor->Clr.A == 0 || scheme.CapeOutlineColor->Clr.A == 0 )
			{
				MyCape->setMyOutlineColor( Color::Transparent );
				MyCape->setMyColor( MyCape->getMyOutlineColor() );
			}
			else
			{
				MyCape->setMyColor( scheme.CapeColor->Clr );
				MyCape->setMyOutlineColor( scheme.CapeOutlineColor->Clr );
			}

			MyCape->MyQuad->Quad_Renamed.setMyTexture( scheme.CapeColor->Texture );
			MyCape->MyQuad->Quad_Renamed.MyEffect = scheme.CapeColor->Effect;

			if ( scheme.CapeColor->ModObject != 0 )
				scheme.CapeColor->ModObject->Apply( boost::static_pointer_cast<Bob>( shared_from_this() ) );

			if ( scheme.CapeColor->Clr.A == 0 || scheme.CapeOutlineColor->Clr.A == 0 )
				ShowCape = false;
		}

		MyColorScheme = scheme;
	}

	void Bob::SetCodeControl()
	{
		CodeControl = true;
		ControlCount = 0;
		ControlFunc.reset();
	}

	const boost::shared_ptr<PlayerData> Bob::getMyPlayerData() const
	{
		return PlayerManager::Get( MyPlayerIndex );
	}

	Vector2 Bob::Feet()
	{
		Box->CalcBounds();

		return Vector2( Box->Current->Center.X, Box->BL.Y );
	}

	boost::shared_ptr<AABox> Bob::GetBox( int DifficultyLevel )
	{
		int index = CoreMath::RestrictVal( 0, Boxes.size() - 1, DifficultyLevel );
		return Boxes[ index ];
	}

	Bob::Bob( const boost::shared_ptr<BobPhsx> &type, bool boxesOnly ) :
		ShowCape( false ),
		HeldObjectIteration( 0 ),
		ImmortalCountDown( 0 ),
		Moved( false ),
		FadingIn( false ),
		Fade( 0 ),
		CanHaveCape( false ), CanHaveHat( false ),
		SideHitCount( 0 ),
		CanInteract( false ),
		Count_ButtonA( 0 ),
		WantsToLand( false ),
		WantsToLand_Reluctant( false ),
		GroundSpeed( 0 ),
		ComputerWaitAtStart( false ),
		ComputerWaitAtStartLength( 0 ),
		SaveNoBlock( false ),
		PlaceDelay( 0 ),
		PlaceTimer( 0 ),
		Flying( false ),
		Immortal( false ), DoNotTrackOffScreen( false ),
		TopCol( false ), BottomCol( false ),
		CompControl( false ), CharacterSelect_Renamed( false ), CharacterSelect2( false ), Cinematic( false ), DrawWithLevel( false ), AffectsCamera( false ),
		IndexOffset( 0 ),
		ControlCount( 0 ),
		CodeControl( false ),
		MyPieceIndex( 0 ),
		MyPieceIndexOffset( 0 ),
		DeadCount( 0 ),
		Dying( false ), Dead( false ), FlamingCorpse( false ),
		BoxesOnly( false ),
		ScreenWrap( false ), ScreenWrapToCenter( false ), CollideWithCamera( false ),
		MyPlayerIndex( static_cast<PlayerIndex>( 0 ) ),
		TryPastTop( false ),
		MinFall( 0 ), MinDrop( 0 ),
		MakingLava( false ), MakingCeiling( false ),
		NumBoxes( 0 ),
		PopModifier( 0 ),
		IsPlayer( false ),
		DeathCount( 0 ),
		CameraWeight( 0 ), CameraWeightSpeed( 0 )
	{
		InitializeInstanceFields();
		MyHeroType = type;
		boost::shared_ptr<Bob> bob = type->Prototype;

		CanHaveCape = bob->CanHaveCape;
		CanHaveHat = bob->CanHaveHat;
		MyObjectType = bob->MyObjectType;

		getCore()->DrawLayer = 6;
		getCore()->Show = true;

		BoxesOnly = boxesOnly;

		SetObject( bob->PlayerObject, BoxesOnly );

		getCore()->Data.Position = bob->getCore()->Data.Position;
		getCore()->Data.Velocity = bob->getCore()->Data.Velocity;
		PlayerObject->ParentQuad->Update();
		PlayerObject->Update( 0 );
		PlayerObject->PlayUpdate( 0 );

		Box = boost::make_shared<AABox>( getCore()->Data.Position, PlayerObject->BoxList[ 1 ]->Size() / 2 );
		Box2 = boost::make_shared<AABox>( getCore()->Data.Position, PlayerObject->BoxList[ 2 ]->Size() / 2 );

		// Pulled out to avoid using shared_from_this inside constructor.
		//SetHeroPhsx( MyHeroType );
		//SetColorScheme( bob->MyColorScheme );
	}

	Bob::Bob( const std::wstring &file, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad ) :
		NewY( 0 ),
		ShowCape( false ),
		HeldObjectIteration( 0 ),
		ImmortalCountDown( 0 ),
		Moved( false ),
		FadingIn( false ),
		Fade( 0 ),
		CanHaveCape( false ), CanHaveHat( false ),
		SideHitCount( 0 ),
		CanInteract( false ),
		Count_ButtonA( 0 ),
		WantsToLand( false ),
		WantsToLand_Reluctant( false ),
		GroundSpeed( 0 ),
		ComputerWaitAtStart( false ),
		ComputerWaitAtStartLength( 0 ),
		SaveNoBlock( false ),
		PlaceDelay( 0 ),
		PlaceTimer( 0 ),
		Immortal( false ), DoNotTrackOffScreen( false ),
		TopCol( false ), BottomCol( false ),
		CompControl( false ), CharacterSelect_Renamed( false ), CharacterSelect2( false ), Cinematic( false ), DrawWithLevel( false ), AffectsCamera( false ),
		IndexOffset( 0 ),
		ControlCount( 0 ),
		CodeControl( false ),
		MyPieceIndex( 0 ),
		MyPieceIndexOffset( 0 ),
		Dying( false ), Dead( false ), FlamingCorpse( false ),
		BoxesOnly( false ),
		ScreenWrap( false ), ScreenWrapToCenter( false ), CollideWithCamera( false ),
		MyPlayerIndex( static_cast<PlayerIndex>( 0 ) ),
		TryPastTop( false ),
		MinFall( 0 ), MinDrop( 0 ),
		MakingLava( false ), MakingCeiling( false ),
		NumBoxes( 0 ),
		PopModifier( 0 ),
		IsPlayer( false ),
		DeathCount( 0 ),
		CameraWeight( 0 ), CameraWeightSpeed( 0 )
	{
		InitializeInstanceFields();
		// Pulled out to avoid using shared_from_this inside constructor.
		//LoadFromFile( file, EffectWad, TextureWad, BobPhsxNormal::getInstance() );
	}

	Bob::Bob( const std::wstring &file, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad, const boost::shared_ptr<BobPhsx> &MyHeroType, bool AllowHats ) :
		NewY( 0 ),
		ShowCape( false ),
		HeldObjectIteration( 0 ),
		ImmortalCountDown( 0 ),
		Moved( false ),
		FadingIn( false ),
		Fade( 0 ),
		CanHaveCape( false ), CanHaveHat( false ),
		SideHitCount( 0 ),
		CanInteract( false ),
		Count_ButtonA( 0 ),
		WantsToLand( false ),
		WantsToLand_Reluctant( false ),
		GroundSpeed( 0 ),
		ComputerWaitAtStart( false ),
		ComputerWaitAtStartLength( 0 ),
		SaveNoBlock( false ),
		PlaceDelay( 0 ),
		PlaceTimer( 0 ),
		Immortal( false ), DoNotTrackOffScreen( false ),
		TopCol( false ), BottomCol( false ),
		CompControl( false ), CharacterSelect_Renamed( false ), CharacterSelect2( false ), Cinematic( false ), DrawWithLevel( false ), AffectsCamera( false ),
		IndexOffset( 0 ),
		ControlCount( 0 ),
		CodeControl( false ),
		MyPieceIndex( 0 ),
		MyPieceIndexOffset( 0 ),
		Dying( false ), Dead( false ), FlamingCorpse( false ),
		BoxesOnly( false ),
		ScreenWrap( false ), ScreenWrapToCenter( false ), CollideWithCamera( false ),
		MyPlayerIndex( static_cast<PlayerIndex>( 0 ) ),
		TryPastTop( false ),
		MinFall( 0 ), MinDrop( 0 ),
		MakingLava( false ), MakingCeiling( false ),
		NumBoxes( 0 ),
		PopModifier( 0 ),
		IsPlayer( false ),
		DeathCount( 0 ),
		CameraWeight( 0 ), CameraWeightSpeed( 0 )
	{
		InitializeInstanceFields();
		CanHaveHat = AllowHats;
		// Pulled out to avoid using shared_from_this inside constructor.
		//LoadFromFile( file, EffectWad, TextureWad, MyHeroType );
	}

	Bob::Bob( const boost::shared_ptr<ObjectClass> &obj, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad, const boost::shared_ptr<BobPhsx> &MyHeroType, bool AllowHats ) :
		ShowCape( false ),
		HeldObjectIteration( 0 ),
		ImmortalCountDown( 0 ),
		Moved( false ),
		FadingIn( false ),
		Fade( 0 ),
		CanHaveCape( false ), CanHaveHat( false ),
		SideHitCount( 0 ),
		CanInteract( false ),
		Count_ButtonA( 0 ),
		WantsToLand( false ),
		WantsToLand_Reluctant( false ),
		GroundSpeed( 0 ),
		ComputerWaitAtStart( false ),
		ComputerWaitAtStartLength( 0 ),
		SaveNoBlock( false ),
		PlaceDelay( 0 ),
		PlaceTimer( 0 ),
		Immortal( false ), DoNotTrackOffScreen( false ),
		TopCol( false ), BottomCol( false ),
		CompControl( false ), CharacterSelect_Renamed( false ), CharacterSelect2( false ), Cinematic( false ), DrawWithLevel( false ), AffectsCamera( false ),
		IndexOffset( 0 ),
		ControlCount( 0 ),
		CodeControl( false ),
		MyPieceIndex( 0 ),
		MyPieceIndexOffset( 0 ),
		Dying( false ), Dead( false ), FlamingCorpse( false ),
		BoxesOnly( false ),
		ScreenWrap( false ), ScreenWrapToCenter( false ), CollideWithCamera( false ),
		MyPlayerIndex( static_cast<PlayerIndex>( 0 ) ),
		TryPastTop( false ),
		MinFall( 0 ), MinDrop( 0 ),
		MakingLava( false ), MakingCeiling( false ),
		NumBoxes( 0 ),
		PopModifier( 0 ),
		IsPlayer( false ),
		DeathCount( 0 ),
		CameraWeight( 0 ), CameraWeightSpeed( 0 )
	{
		InitializeInstanceFields();
		CanHaveHat = AllowHats;
		_Load( obj, EffectWad, TextureWad, MyHeroType );
	}

	void Bob::LoadFromFile( const std::wstring &file, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad, const boost::shared_ptr<BobPhsx> &HeroType )
	{
		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( stream, Encoding::UTF8 );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( file );

		Vector2 size = Vector2( 1, 2 );
		float ratio = size.Y / size.X;
		int width = Tools::TheGame->Resolution.Bob_Renamed.X;
		int height = static_cast<int>( width * ratio );

		boost::shared_ptr<ObjectClass> obj = boost::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, width, height, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );
		ObjectClass_PostConstruct( obj, Tools::QDrawer, Tools::Device, Tools::Device->PP, width, height, EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), TextureWad->FindByName( std::wstring( L"White" ) ) );

		obj->ReadFile( reader, EffectWad, TextureWad );
		
		//reader->Close();
		//stream->Close();
		reader->Close();

		obj->ParentQuad->Scale( Vector2( 260, 260 ) );

		_Load( obj, EffectWad, TextureWad, MyHeroType );
	}

	void Bob::_Load( const boost::shared_ptr<ObjectClass> &obj, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad, const boost::shared_ptr<BobPhsx> &HeroType )
	{
		this->PlayerObject = obj;

		this->MyHeroType = HeroType;

		CoreData = boost::make_shared<ObjectData>();
		getCore()->Show = true;

		JumpSound = JumpSound_Default = Tools::SoundWad->FindByName( std::wstring( L"Jump5" ) );
		JumpSound->DefaultVolume = .1f;
		JumpSound->DelayTillNextSoundCanPlay = 10;

		DieSound = DieSound_Default = Tools::Sound( std::wstring( L"Death_Chime" ) );

		PlayerObject->Read( 0, 0 );
		PlayerObject->Play = true;

		getCore()->Data.Position = Vector2(100, 50);
		getCore()->Data.Velocity = Vector2(0, 0);
		PlayerObject->ParentQuad->Update();
		PlayerObject->Update( 0 );
		PlayerObject->PlayUpdate( 0 );

		Box = boost::make_shared<AABox>( getCore()->Data.Position, PlayerObject->BoxList[ 1 ]->Size() / 2 );
		Box2 = boost::make_shared<AABox>( getCore()->Data.Position, PlayerObject->BoxList[ 2 ]->Size() / 2 );

		MyPhsx = boost::make_shared<BobPhsx>();
			InitBobPhsxSingleton( MyPhsx );
		MyPhsx->Init( boost::static_pointer_cast<Bob>( shared_from_this() ) );

		SetColorScheme( ColorSchemeManager::ColorSchemes[ 0 ] );
	}

	void Bob::SwitchHero( const boost::shared_ptr<BobPhsx> &hero )
	{
		Vector2 HoldVel = MyPhsx->getVel();

		if ( MyCape != 0 )
			MyCape->Release();
			MyCape.reset();

		SetObject( hero->Prototype->PlayerObject, false );
		SetHeroPhsx( hero );

		if ( MyCape != 0 )
			MyCape->Move( getPos() );

		//MakeCape();

		SetColorScheme( PlayerManager::Get( boost::static_pointer_cast<Bob>( shared_from_this() ) )->ColorScheme_Renamed );

		MyPhsx->setVel( HoldVel );

		//PhsxStep();
		AnimAndUpdate();
		//PhsxStep2();
	}

	void Bob::SetHeroPhsx( const boost::shared_ptr<BobPhsx> &type )
	{
		MyCapeType = CapeType_NORMAL;

		MyPhsx = type->Clone();
		//MyPhsx = new BobPhsxNormal();

		MyPhsx->Init( boost::static_pointer_cast<Bob>( shared_from_this() ) );
		MakeCape( MyCapeType );
	}

	void Bob::MakeCape( CapeType CapeType )
	{
		if ( MyCape == 0 && !BoxesOnly && CanHaveCape )
		{
			MyCape = boost::make_shared<Cape>( boost::static_pointer_cast<Bob>( shared_from_this() ), CapeType, MyPhsx );
			MyCape->Reset();
		}
	}

	void Bob::Init( bool BoxesOnly, PhsxData StartData, const boost::shared_ptr<GameData> &game )
	{
		getCore()->Show = true;

		HeldObjectIteration = 0;

		boost::shared_ptr<BobPhsx> type = game->DefaultHeroType;
		if ( getCore()->MyLevel != 0 )
			type = getCore()->MyLevel->DefaultHeroType;
		MyHeroType = type;

		getCore()->DrawLayer = 6;

		if ( CharacterSelect2 )
		{
			MyPhsx = boost::make_shared<BobPhsxCharSelect>();
				InitBobPhsxSingleton( MyPhsx );
			MyPhsx->Init( boost::static_pointer_cast<Bob>( shared_from_this() ) );
			MakeCape( CapeType_NORMAL );
		}
		else
			SetHeroPhsx( type );

		ImmortalCountDown = ImmortalLength;
		Moved = false;

		PlaceTimer = 0;

		GroundSpeed = 0;

		Dead = Dying = false;
		DeadCount = 0;

		Move( StartData.Position - getCore()->Data.Position );
		getCore()->StartData = getCore()->Data = StartData;


		if ( PlayerObject == 0 )
		{
			PlayerObject = boost::make_shared<ObjectClass>( type->Prototype->PlayerObject, BoxesOnly, false );
			ObjectClass_PostConstruct_3params( PlayerObject, type->Prototype->PlayerObject, BoxesOnly, false );

			PlayerObject->FinishLoading();
			Vector2 size = PlayerObject->BoxList[ 0 ]->Size();
			float ratio = size.Y / size.X;
			int width = Tools::TheGame->Resolution.Bob_Renamed.X;
			int height = static_cast<int>( width * ratio );
			PlayerObject->FinishLoading( Tools::QDrawer, Tools::Device, Tools::TextureWad, Tools::EffectWad, Tools::Device->PP, width, height );
		}

		PlayerObject->Read( 0, 0 );
		PlayerObject->Play = true;

		PlayerObject->ParentQuad->Update();
		PlayerObject->Update( 0 );
		PlayerObject->PlayUpdate( 0 );

		Move( StartData.Position - getCore()->Data.Position );
		getCore()->Data = StartData;
		Box->SetTarget( getCore()->Data.Position, Box->Current->Size );
		Box2->SetTarget( getCore()->Data.Position, Box2->Current->Size );
		Box->SwapToCurrent();
		Box2->SwapToCurrent();
		UpdateObject();

		Box->CalcBounds();
		Box2->CalcBounds();

		LastCoinPos = getCore()->Data.Position;


		if ( MyCape != 0 )
		{
			MyCape->AnchorPoint[ 0 ] = getCore()->Data.Position;
			MyCape->Reset();
		}

		SetColorScheme( MyColorScheme );
	}

	boost::shared_ptr<PlayerData> Bob::GetPlayerData()
	{
		if ( !IsPlayer )
			return 0;

		return PlayerManager::Get( static_cast<int>( MyPlayerIndex ) );
	}

	bool Bob::GiveStats()
	{
		return getCore()->MyLevel->PlayMode == 0 && !CompControl && !getCore()->MyLevel->Watching && !Dead && !Dying;
	}

	const boost::shared_ptr<PlayerStats> &Bob::getMyStats() const
	{
		return PlayerManager::Get( static_cast<int>( MyPlayerIndex ) )->getStats();
	}

	const boost::shared_ptr<PlayerStats> &Bob::getMyTempStats() const
	{
		return PlayerManager::Get( static_cast<int>( MyPlayerIndex ) )->TempStats;
	}

	void Bob::Die( BobDeathType DeathType, bool ForceDeath, bool DoAnim )
	{
		Die( DeathType, 0, ForceDeath, DoAnim );
	}

	void Bob::Die( BobDeathType DeathType )
	{
		Die( DeathType, 0, false, true );
	}

	void Bob::Die( BobDeathType DeathType, const boost::shared_ptr<ObjectBase> &KillingObject )
	{
		Die( DeathType, KillingObject, false, true );
	}

	void Bob::Die( BobDeathType DeathType, const boost::shared_ptr<ObjectBase> &KillingObject, bool ForceDeath, bool DoAnim )
	{
		if ( Dying )
			return;

		if ( !ForceDeath )
		{
			if ( Immortal || ( !getCore()->MyLevel->Watching && getCore()->MyLevel->PlayMode == 0 && ImmortalCountDown > 0 ) )
				return;

			if ( CompControl )
				return;
		}

		DeathCount = 0;

		//getCore()->DrawLayer = 9;

		FlamingCorpse = false;

		this->KillingObject = KillingObject;

	#if defined(XBOX)
		Tools::SetVibration( MyPlayerIndex,.5f,.5f, 45 );
	#endif

		// Update stats
		if ( DeathType != BobDeathType_NONE )
			getMyStats()->DeathsBy[ static_cast<int>(BobDeathType_TOTAL) ]++;

		getMyStats()->DeathsBy[ static_cast<int>(DeathType) ]++;

		Dying = true;

		if ( DoAnim )
			MyPhsx->Die( DeathType );

		Tools::CurGameData->BobDie( getCore()->MyLevel, boost::static_pointer_cast<Bob>( shared_from_this() ) );
	}

	const bool Bob::getCanDie() const
	{
		return !Immortal && !Dead && !Dying && getCore()->MyLevel->PlayMode == 0 && !getCore()->MyLevel->Watching;
	}

	const bool Bob::getCanFinish() const
	{
		return !Dead && !Dying && getCore()->MyLevel->PlayMode == 0 && !getCore()->MyLevel->Watching;
	}

	void Bob::DyingPhsxStep()
	{
		DeathCount++;

		if ( getCore()->Data.Velocity.Y > -30 )
			getCore()->Data.Velocity += getCore()->Data.Acceleration;

		getCore()->Data.Position += getCore()->Data.Velocity;

		PlayerObject->PlayUpdate( 1000.f / 60.f / 150.f );

		// Check to see if any other players are alive
		/*
		if (PlayerManager::AllDead())
		{
		    // Check to see if we should give a hint about quickspawning
		    if (Hints.CurrentGiver != null)
		    {
		        Hints.CurrentGiver.Check_QuickSpawn();
		    }
		}*/

		// Check to see if we've fallen past the edge of the screen,
		// if so, officially declare the player dead.
		if ( !Dead && ( ( IsVisible() && getCore()->Show && getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - getGame()->DoneDyingDistance ) || (!IsVisible() && DeathCount > getGame()->DoneDyingCount) ) )
		{
			Tools::CurGameData->BobDoneDying( getCore()->MyLevel, boost::static_pointer_cast<Bob>( shared_from_this() ) );
			if (!Dead && !Dying) DeadCount = 0;
			Dead = true;
		}

		Box->Current->Size = PlayerObject->BoxList[ 1 ]->Size() / 2;
		Box->SetTarget( getCore()->Data.Position, Box->Current->Size );
	}

	void Bob::CheckForScreenWrap()
	{
		if ( ScreenWrap )
		{
			if ( ScreenWrapToCenter )
			{
				bool OffScreen = false;
				if ( getCore()->Data.Position.X < getCore()->MyLevel->getMainCamera()->BL.X - 100 )
					OffScreen = true;
				if ( getCore()->Data.Position.X > getCore()->MyLevel->getMainCamera()->TR.X + 100 )
					OffScreen = true;
				if ( getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - 600 )
					OffScreen = true;
				if ( getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + 600 )
					OffScreen = true;

				if ( OffScreen )
				{
					// Find highest bob
					Vector2 Destination = getCore()->MyLevel->getMainCamera()->Data.Position;
					if ( getCore()->MyLevel->Bobs.size() > 1 )
					{
						boost::shared_ptr<Bob> HighestBob = 0;
						for ( BobVec::const_iterator bob = getCore()->MyLevel->Bobs.begin(); bob != getCore()->MyLevel->Bobs.end(); ++bob )
						{
							if ( *bob != shared_from_this() && ( *bob )->AffectsCamera && ( HighestBob == 0 || ( *bob )->getCore()->Data.Position.Y > HighestBob->getCore()->Data.Position.Y ) )
							{
								HighestBob = *bob;
							}
						}
						Destination = HighestBob->getCore()->Data.Position;
					}
					Move( Destination - getCore()->Data.Position );
					ParticleEffects::AddPop( getCore()->MyLevel, getCore()->Data.Position );
				}
			}
			else
			{
				// Do the screen wrap
				//bool Moved = false;
				Vector2 w = getCore()->MyLevel->getMainCamera()->TR - getCore()->MyLevel->getMainCamera()->BL + Vector2(1200, 1600);
				if ( getCore()->Data.Position.X < getCore()->MyLevel->getMainCamera()->BL.X - 100 )
				{
					//Moved = true;
					Move( Vector2( w.X, 0 ) );
				}
				if ( getCore()->Data.Position.X > getCore()->MyLevel->getMainCamera()->TR.X + 100 )
				{
					//Moved = true;
					Move( Vector2( -w.X, 0 ) );
				}
				if ( getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - 600 )
				{
					//Moved = true;
					Move( Vector2( 0, w.Y ) );
				}
				if ( getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + 600 )
				{
					//Moved = true;
					Move( Vector2( 0, -w.Y ) );
				}

				// If multiplayer, decrease the bob's camera weight
				//if (Moved && PlayerManager::GetNumPlayers() > 1)
				//{
				//    CameraWeight = 0;
				//    CameraWeightSpeed = .01f;
				//}
			}
		}
	}

	void Bob::GetPlayerInput()
	{
	//#elif XBOX
		CurInput.Clean();

		if ( Immobile )
			return;

		GamePadState pad = Tools::GamepadState[ static_cast<int>( MyPlayerIndex ) ];
#if defined(WINDOWS)
        bool GamepadUsed = false;
#endif


		if ( pad.IsConnected )
		{
			if ( pad.Buttons.A == ButtonState_Pressed )
			{
				CurInput.A_Button = true;
			}
			else
				CurInput.A_Button = false;

			CurInput.xVec.X = CurInput.xVec.Y = 0;
			if ( fabs( pad.ThumbSticks.Left.X ) > .15f )
				CurInput.xVec.X = pad.ThumbSticks.Left.X;
			if ( fabs( pad.ThumbSticks.Left.Y ) > .15f )
				CurInput.xVec.Y = pad.ThumbSticks.Left.Y;

			if ( pad.DPad.Right == ButtonState_Pressed )
				CurInput.xVec.X = 1;
			if ( pad.DPad.Left == ButtonState_Pressed )
				CurInput.xVec.X = -1;
			if ( pad.DPad.Up == ButtonState_Pressed )
				CurInput.xVec.Y = 1;
			if ( pad.DPad.Down == ButtonState_Pressed )
				CurInput.xVec.Y = -1;


			CurInput.B_Button = ( pad.Buttons.LeftShoulder == ButtonState_Pressed || pad.Buttons.RightShoulder == ButtonState_Pressed );
#if defined(WINDOWS)
            if ( CurInput.xVec != Vector2() || CurInput.A_Button || CurInput.B_Button )
            {
                GamepadUsed = true;
                InputFromKeyboard = false;
            }
#endif
        }

#if defined(WINDOWS)
		Vector2 KeyboardDir = Vector2();

		CurInput.A_Button |= KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Up );
		CurInput.A_Button |= KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, ButtonCheck::Up_Secondary );
		KeyboardDir.X = KeyboardDir.Y = 0;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Up ) )
			KeyboardDir.Y = 1;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Down ) )
			KeyboardDir.Y = -1;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Right ) )
			KeyboardDir.X = 1;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, Keys_Left ) )
			KeyboardDir.X = -1;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, ButtonCheck::Left_Secondary ) )
			KeyboardDir.X = -1;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, ButtonCheck::Right_Secondary ) )
			KeyboardDir.X = 1;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, ButtonCheck::Up_Secondary ) )
			KeyboardDir.Y = 1;
		if ( KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, ButtonCheck::Down_Secondary ) )
			KeyboardDir.Y = -1;

		CurInput.B_Button |= KeyboardExtension::IsKeyDownCustom( Tools::Keyboard, ButtonCheck::Back_Secondary );

		if ( KeyboardDir.LengthSquared() > CurInput.xVec.LengthSquared() )
			CurInput.xVec = KeyboardDir;

#if defined(WINDOWS)
        if ( !GamepadUsed && ( CurInput.xVec != Vector2() || CurInput.A_Button || CurInput.B_Button ) )
        {
            InputFromKeyboard = true;
        }
#endif

#endif        

		// Invert left-right for inverted levels
		if ( getCore()->MyLevel != 0 && getCore()->MyLevel->ModZoom.X < 0 )
			CurInput.xVec.X *= -1;
	}

	void Bob::GetRecordedInput( int Step )
	{
		if ( getCore()->MyLevel->Replay )
		{
			if ( Step < static_cast<int>( MyRecord->Input.size() ) )
				CurInput = MyRecord->Input[ Step ];

			return;
		}

		if ( MyPiece != 0 && Step < MyPiece->PieceLength )
		{
			CurInput = MyRecord->Input[ Step ];
		}
		else
		{
			CurInput.xVec = Vector2( 1, 0 );
			CurInput.A_Button = true;
			CurInput.B_Button = false;
		}
	}

	void Bob::RecordInput( int Step )
	{
		MyRecord->Input[ Step ] = CurInput;
	}

	void Bob::AnimStep()
	{
		if ( Dying )
			return;

		MyPhsx->AnimStep();
	}

	void Bob::AnimAndUpdate()
	{
		AnimStep();
		UpdateObject();
	}

	const Vector2 &Bob::getObjectPos() const
	{
		return PlayerObject->ParentQuad->Center->Pos;
	}

	void Bob::UpdateObject()
	{
		Vector2 NewCenter = getCore()->Data.Position - (PlayerObject->BoxList[ 1 ]->TR->Pos - PlayerObject->ParentQuad->Center->Pos - Box->Current->Size);
		//Vector2 NewCenter = Core.Data.Position - (PlayerObject.ParentQuad.Center.Pos - PlayerObject.BoxList[1].BL.Pos + new Vector2(69.09941f, 104.1724f));
		//NewCenter += ExtraShift;

		PlayerObject->ParentQuad->Center->Move( NewCenter );
		PlayerObject->ParentQuad->Update();

		PlayerObject->Update( 0 );
		//Core.Data.Position = PlayerObject.BoxList[1].Center();
	}

	void Bob::UpdateColors()
	{
		if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( MyObjectType ) != 0 && PlayerObject->QuadList.size() > 0 )
		{
			std::vector<boost::shared_ptr<BaseQuad> > ql = PlayerObject->QuadList;
			if ( ql.size() >= 1 )
				PlayerObject->QuadList[ 1 ]->SetColor( Color::White );
			if ( ql.size() >= 1 )
				PlayerObject->QuadList[ 1 ]->setMyMatrix( MyColorScheme.SkinColor->M );
			if ( ql.size() >= 1 )
				PlayerObject->QuadList[ 1 ]->MyEffect = Tools::HslGreenEffect;
			if ( ql.size() >= 0 )
				PlayerObject->QuadList[ 0 ]->Show = false;
			if ( ql.size() >= 2 )
				PlayerObject->QuadList[ 2 ]->Show = false;
		}
	}

	void Bob::InitGuideQuad()
	{
		if ( GuideQuad != 0 )
			return;

		GuideQuad = boost::make_shared<QuadClass>();
		GuideQuad->setEffectName( std::wstring( L"Circle" ) );
		GuideQuad->setSize( Vector2( 100, 100 ) );
	}

	void Bob::DrawGuidePiece( int Step, std::vector<Vector2> Loc, int i )
	{
		if ( static_cast<int>( Loc.size() ) > Step )
		{
			InitGuideQuad();

			Vector2 Size = Vector2( 100 - 50 * Guide_h * i );
			//Vector2 Size = new Vector2(40);

			GuideQuad->Quad_Renamed.SetColor( Color( 0, 0, 0, 1 - Guide_h * i ) );
			GuideQuad->setSize( Size * 1.15f );

			GuideQuad->setPos( Loc[ Step ] );
			GuideQuad->Draw();


			Color c = MyColorScheme.SkinColor->Clr;
			c.A = static_cast<unsigned char>( 255 * ( 1 - Guide_h * i ) );
			//GuideQuad.Quad.SetColor(new Color(0f, 1f, 0f, 1f - Guide_h * i));
			GuideQuad->Quad_Renamed.SetColor( c );
			GuideQuad->setSize( Size );

			GuideQuad->setPos( Loc[ Step ] );
			GuideQuad->Draw();
		}
	}

	void Bob::InitSectionDraw()
	{
		Vector2 Size = Vector2( 15 );

		GuideQuad->Quad_Renamed.SetColor( Color::PowderBlue );
		//GuideQuad.Quad.SetColor(Color.Black);
		//GuideQuad.Quad.SetColor(new Color(0,255,0,150));
		GuideQuad->setSize( Size );
	}

	void Bob::DrawSection( int Step, std::vector<Vector2> Loc )
	{
			GuideQuad->setPos( Loc[ Step ] );
			GuideQuad->Draw();
	}

	void Bob::DrawGuide()
	{
		if ( MyPiece != 0 && static_cast<int>( MyPiece->Recording_Renamed.size() ) > 0 && static_cast<int>( MyPiece->Recording_Renamed.size() ) > MyPieceIndex )
		{
			int Step = getCore()->MyLevel->GetPhsxStep();
			Step = __max( 0, Step - 2 );

			std::vector<Vector2> Loc = MyPiece->Recording_Renamed[ MyPieceIndex ]->AutoLocs;

			InitGuideQuad();
			int N = __min( 1000, Loc.size() );
			N = __min( N, MyPiece->PieceLength );
			InitSectionDraw();

			for ( int i = 1; i < N; i += 2 )
			{
				//DrawSection( i, Loc );
				Tools::QDrawer->DrawCircleDot( Loc[ i ] );
			}

			if ( Loc.size() > 0 && N > Step )
				DrawGuidePiece( Step, Loc, 2 );
			Tools::QDrawer->Flush();
		}
	}

	bool Bob::IsVisible()
	{
		if ( !getCore()->Show )
			return false;

		if ( Bob::AllExplode )
		{
			if ( Dying || Dead )
				return false;
		}

		return true;
	}

	void Bob::DrawTheRocket()
	{
		if ( Rocket == 0 )
		{
			Rocket = boost::make_shared<QuadClass>( std::wstring( L"Castle_Jet_Pack" ) );
			//Rocket = new QuadClass("RocketPack");
			Rocket->FancyAngle = boost::make_shared<FancyVector2>();
			Rocket->Quad_Renamed.MyEffect = Tools::HslEffect;
			Rocket->setDegrees( -20 );
		}
		else
		{
			float scale = .3675f;

			Rocket->setDegrees( -33 );
			Rocket->ScaleYToMatchRatio( PlayerObject->ParentQuad->getSize().X * scale );
			Rocket->setPos( getPos() + Vector2(-88, 20) * GetScale() );
			Rocket->Draw();

			Rocket->setDegrees( 33 );
			Rocket->Quad_Renamed.MirrorUV_Horizontal();
			Rocket->ScaleYToMatchRatio( PlayerObject->ParentQuad->getSize().X * scale );
			Rocket->setPos( getPos() + Vector2(93, 20) * GetScale() );
			Rocket->Draw();
			Rocket->Quad_Renamed.MirrorUV_Horizontal();
		}
	}

	Vector2 Bob::GetScale()
	{
		return PlayerObject->ParentQuad->getSize() / Vector2(260);
	}

	void Bob::Draw()
	{
		bool SkipDraw = false;

		// Draw guide
		if ( GuideActivated && getCore()->MyLevel != 0 && !getCore()->MyLevel->Watching && !getCore()->MyLevel->Replay )
			DrawGuide();

		if ( !getCore()->Show )
			return;

		if ( Dying || Dead )
		{
			if ( Bob::AllExplode && !Bob::ShowCorpseAfterExplode )
				return;

			if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( MyObjectType ) != 0 )
			{
				return;
			}
		}

		if ( ( Dying || Dead ) && FlamingCorpse )
			ParticleEffects::Flame( getCore()->MyLevel, getCore()->Data.Position + 1.5f * getCore()->Data.Velocity, getCore()->MyLevel->GetPhsxStep(), 1, 10, false );

		UpdateColors();

		// Draw guide
		//if (GuideActivated && Core.MyLevel != null && !Core.MyLevel.Watching && !Core.MyLevel.Replay)
		//    DrawGuide();

		if ( FadingIn )
		{
			Fade += .033f;
			if ( Fade >= 1 )
			{
				FadingIn = false;
				Fade = 1;
				PlayerObject->ContainedQuad->SetColor( Color( 1.f, 1.f, 1.f, 1.f ) );
			}

			if ( MyCape != 0 )
				MyCape->_MyColor.A = static_cast<unsigned char>( 255 * Fade );
		}


		if ( MyCape != 0 && CanHaveCape && getCore()->Show && ShowCape && !SkipDraw && Tools::DrawGraphics )
		{
			MyCape->Draw();
			Tools::QDrawer->Flush();
			//return;
		}

		if ( Tools::DrawGraphics && !BoxesOnly && getCore()->Show )
		{
			if ( !SkipDraw )
			{
				if ( MyPhsx->ThrustType == BobPhsx::RocketThrustType_DOUBLE )
					DrawTheRocket();

				Tools::QDrawer->SetAddressMode( false, false );
				if ( PlayerObject->ContainedQuadAngle == 0 )
				{
					PlayerObject->Draw( true );
				}
				else
				{
					PlayerObject->Update( 0 );
					boost::shared_ptr<Quad> w = boost::static_pointer_cast<Quad>( PlayerObject->FindQuad( std::wstring( L"Wheel" ) ) );
					boost::shared_ptr<CloudberryKingdom::Quad> p = PlayerObject->ParentQuad;
					Vector2 hold = p->Center->Pos;

					float D = 116.6666f * p->getSize().Y / 260;

					Vector2 d = D * CoreMath::AngleToDir( PlayerObject->ContainedQuadAngle + 1.57 );
					Vector2 move = Vector2( 0, D ) - d;
					PlayerObject->ParentQuad->Center->Move( move + p->Center->Pos );

					PlayerObject->ParentQuad->PointxAxisTo( CoreMath::AngleToDir( PlayerObject->ContainedQuadAngle ) );
					PlayerObject->Draw( true );
					PlayerObject->ParentQuad->PointxAxisTo( CoreMath::AngleToDir( 0 ) );

					PlayerObject->ParentQuad->Center->Move( hold );
					PlayerObject->Update( 0 );
				}
			}
		}

		if ( Tools::DrawBoxes )
		{
			Box->Draw( Tools::QDrawer, Color::HotPink, 12 );
			Box->DrawT( Tools::QDrawer, Color::HotPink, 6 );

			Box2->Draw( Tools::QDrawer, Color::HotPink, 12 );
			Box2->DrawT( Tools::QDrawer, Color::HotPink, 12 );

			if ( Boxes.size() > 0 )
			{
				Boxes[ 0 ]->Draw( Tools::QDrawer, Color::Red, 8 );
				Boxes[ 3 ]->Draw( Tools::QDrawer, Color::Green, 8 );
				Boxes[ 8 ]->Draw( Tools::QDrawer, Color::Blue, 8 );
			}
		}
	}

	void Bob::Move( Vector2 shift )
	{
		getCore()->Data.Position += shift;

		Box->Move( shift );
		Box2->Move( shift );

		if ( PlayerObject == 0 )
			return;

		PlayerObject->ParentQuad->Center->Move( PlayerObject->ParentQuad->Center->Pos + shift );
		PlayerObject->ParentQuad->Update();
		PlayerObject->Update( 0 );

		if ( MyCape != 0 )
			MyCape->Move( shift );
	}

	void Bob::InteractWithBlock( const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block, ColType Col )
	{
		if ( block != 0 && !block->getIsActive() )
			return;

		if ( block != 0 && Col != ColType_NO_COL )
			block->Hit( boost::static_pointer_cast<Bob>( shared_from_this() ) );

		if ( block != 0 && Col != ColType_NO_COL )
			if ( Col != ColType_TOP )
				block->getBlockCore()->NonTopUsed = true;


		ColType OriginalColType = Col;

		if ( MyPhsx->IsTopCollision( Col, box, block ) )
		{
			//if (Col != ColType.Top) Tools::Write(0);

			Col = ColType_TOP;

			NewY = box->Target->TR.Y + Box->Current->Size.Y + .01f;

			if ( getCore()->Data.Position.Y <= NewY )
			{
				NewVel = __max( -1000, MyPhsx->ForceDown + box->Target->TR.Y - box->Current->TR.Y );

				if ( block != 0 )
				{
					block->getBlockCore()->StoodOn = true;
					block->LandedOn( boost::static_pointer_cast<Bob>( shared_from_this() ) );
				}

				if ( !TopCol )
				{
					BottomCol = true;

					if ( OriginalColType == ColType_TOP )
					{
						getCore()->Data.Position.Y = NewY;

						if ( block == 0 || block->getBlockCore()->GivesVelocity )
						{
							if ( MyPhsx->getSticky() )
								getCore()->Data.Velocity.Y = NewVel;
							else
								getCore()->Data.Velocity.Y = __max(NewVel, getCore()->Data.Velocity.Y);
						}

						UpdateGroundSpeed( box, block );
					}
					else
					{
						// We hit the block from the side, just at the top edge
						// Keep bigger Y values
						getCore()->Data.Position.Y = __max(getCore()->Data.Position.Y, NewY);
						if ( block == 0 || block->getBlockCore()->GivesVelocity )
							getCore()->Data.Velocity.Y = __max(getCore()->Data.Velocity.Y, NewVel);
					}

					//MyPhsx.ObjectLandedOn = block;
					MyPhsx->LandOnSomething( false, block );

					if ( OnLand != 0 )
						OnLand->Apply();
						OnLand.reset();
				}
			}
		}

		if ( Col != ColType_NO_COL && ( block == 0 || block->getBlockCore()->MyType != ObjectType_LAVA_BLOCK ) )
		{
			if ( !box->TopOnly )
			{
				if ( Col == ColType_BOTTOM && !( Col == ColType_LEFT || Col == ColType_RIGHT ) )
				{
					TopCol = true;
				}

				//if (Col == ColType.Right) Tools::Write(0);
				//if (Col == ColType.Left) Tools::Write(0);

				if ( MyPhsx->IsBottomCollision( Col, box, block ) )
					Col = ColType_BOTTOM;

				NewY = box->Target->BL.Y - Box->Current->Size.Y - .01f;
				if ( getCore()->Data.Position.Y > NewY && Col == ColType_BOTTOM )
				{
					if ( MyPhsx->OnGround && block->getBlockCore()->DoNotPushHard )
					{
						block->Smash( boost::static_pointer_cast<Bob>( shared_from_this() ) );
						return;
					}

					MyPhsx->HitHeadOnSomething( block );

					if ( block != 0 )
						block->HitHeadOn( boost::static_pointer_cast<Bob>( shared_from_this() ) );

					if ( OriginalColType == ColType_BOTTOM )
					{
						getCore()->Data.Position.Y = NewY;

						if ( block == 0 || block->getBlockCore()->GivesVelocity )
						{
							NewVel = __min( __min( 0, NewVel ), box->Target->BL.Y - box->Current->BL.Y ) + 10;
							getCore()->Data.Velocity.Y = __min(NewVel, getCore()->Data.Velocity.Y);
						}

						// If we are inverted, then we can take on the speed of the block we have landed on upside-down.
						if ( MyPhsx->Gravity < 0 )
							UpdateGroundSpeed( box, block );
					}
					else
					{
						// We hit the block from the side, just at the bottom edge
						// Keep smaller Y values
						getCore()->Data.Position.Y = __min(getCore()->Data.Position.Y, NewY);
						if ( block == 0 || block->getBlockCore()->GivesVelocity )
						{
							NewVel = __min( 0, box->Target->BL.Y - box->Current->BL.Y ) + 10;
							getCore()->Data.Velocity.Y = __min(NewVel, getCore()->Data.Velocity.Y);
						}

					}
				}
				else
				{
					Xvel = box->Target->TR.X - box->Current->TR.X;

					if ( Col == ColType_LEFT )
					{
						if ( block != 0 )
							block->SideHit( boost::static_pointer_cast<Bob>( shared_from_this() ) );

						MyPhsx->SideHit( Col, block );

						getCore()->Data.Position.X = box->Target->BL.X - Box->Current->Size.X - .01f;

						SideHitCount += 2;
						if ( SideHitCount > 5 )
							getCore()->Data.Velocity.X *= .4f;

						if ( block == 0 || block->getBlockCore()->GivesVelocity )
						if ( Xvel < getCore()->Data.Velocity.X )
							if ( Box->Current->BL.Y < box->Current->TR.Y - 35 && Box->Current->TR.Y > box->Current->BL.Y + 35 )
								getCore()->Data.Velocity.X = Xvel;
					}

					if ( Col == ColType_RIGHT )
					{
						if ( block != 0 )
							block->SideHit( boost::static_pointer_cast<Bob>( shared_from_this() ) );

						MyPhsx->SideHit( Col, block );

						getCore()->Data.Position.X = box->Target->TR.X + Box->Current->Size.X + .01f;

						SideHitCount += 2;
						if ( SideHitCount > 5 )
							getCore()->Data.Velocity.X *= .4f;

						if ( block == 0 || block->getBlockCore()->GivesVelocity )
						if ( Xvel > getCore()->Data.Velocity.X )
							if ( Box->Current->BL.Y < box->Current->TR.Y - 35 && Box->Current->TR.Y > box->Current->BL.Y + 35 )
								getCore()->Data.Velocity.X = Xvel;
					}
				}
			}
		}
	}

	void Bob::UpdateGroundSpeed( const boost::shared_ptr<AABox> &box, const boost::shared_ptr<BlockBase> &block )
	{
		GroundSpeed = box->xSpeed();

		if ( block != 0 )
			GroundSpeed += block->getBlockCore()->GroundSpeed;
	}

	void Bob::InitBoxesForCollisionDetect()
	{
		//PlayerObject.Update(null);
		Box->Current->Size = PlayerObject->BoxList[ 1 ]->Size() / 2;
		Box2->Current->Size = PlayerObject->BoxList[ 2 ]->Size() / 2;

		if ( getCore()->MyLevel->PlayMode != 0 && boost::dynamic_pointer_cast<BobPhsxSpaceship>(getCore()->MyLevel->DefaultHeroType) != 0 )
		{
			Box->Current->Size *= 1.2f;
			Box2->Current->Size *= 1.2f;
		}

		if ( MyPhsx->Gravity > 0 )
		{
			Box->SetTarget( getCore()->Data.Position, Box->Current->Size + Vector2(.0f,.02f) );
			Box->Target->TR.Y += 5;
		}
		else
		{
			Box->SetTarget( getCore()->Data.Position, Box->Current->Size + Vector2(.0f, -.02f) );
			Box->Target->BL.Y -= 5;
		}

		Box2->SetTarget( getCore()->Data.Position, Box2->Current->Size );

		MyPhsx->OnInitBoxes();
	}

	void Bob::UpdateCape()
	{
		if ( !CanHaveCape ) // || !ShowCape)
			return;

		MyCape->Wind = CapeWind;
		Vector2 AdditionalWind = Vector2();
		if ( getCore()->MyLevel != 0 && getCore()->MyLevel->MyBackground != 0 )
		{
			AdditionalWind += getCore()->MyLevel->MyBackground->Wind;
			MyCape->Wind += AdditionalWind;
		}
		//MyCape.Wind.X -= .2f * Core.Data.Velocity.X;

		if ( MyPhsx->Ducking && MyObjectType != BobPhsxBox::getInstance() )
			MyCape->GravityScale = .4f;
		else
			MyCape->GravityScale = 1;

		// Set the anchor point
		if ( temp == 0 )
		{
			temp = boost::make_shared<ObjectVector>();
			temp->ModifiedEventCallback = boost::make_shared<ObjectVector::DefaultCallbackLambda>( temp->shared_from_this() );
		}

		if ( Head == 0 )
			Head = boost::static_pointer_cast<Quad>( PlayerObject->FindQuad( std::wstring( L"Head" ) ) );
		temp->Pos = Head->Center->Pos;

        if (Dead)
            temp->Pos += Vector2( 60, -50 ) * MyPhsx->ModCapeSize + Vector2( 0, 3 * ( 1.f / MyPhsx->ModCapeSize.Y - 1 ) );
        else  if ( MyPhsx->Ducking )
			temp->Pos += MyPhsx->CapeOffset_Ducking * MyPhsx->ModCapeSize + Vector2( 0, 3 * ( 1 / MyPhsx->ModCapeSize.Y - 1 ) );
		else
			temp->Pos += MyPhsx->CapeOffset * MyPhsx->ModCapeSize;


		MyCape->Gravity = MyPhsx->CapeGravity;

		Vector2 vel = MyPhsx->getApparentVelocity();
		MyCape->AnchorPoint[ 0 ] = temp->Pos + ( vel );

		//Console.WriteLine("{0} {1} {2}", Core.Data.Position, MyCape.AnchorPoint[0], MyCape.AnchorPoint[1]);

		if ( getCore()->MyLevel != 0 )
		{
			float t = getCore()->MyLevel->GetPhsxStep() / 2.5f;
			if ( CharacterSelect2 )
				t = Tools::DrawCount / 2.5f;
			float AmplitudeX = __min( 2.5f, fabs( vel.X - AdditionalWind.X ) / 20 );
			MyCape->AnchorPoint[ 0 ].Y += 15 * static_cast<float>( cos( t ) * AmplitudeX );
			float Amp = 2;
			if ( vel.Y < 0 )
				Amp = 8;
			float AmplitudeY = __min( 2.5f, fabs( vel.Y - AdditionalWind.Y ) / 45 );
			MyCape->AnchorPoint[ 0 ].X += Amp * static_cast<float>( sin( t ) * AmplitudeY );
		}
		//MyCape.AnchorPoint[0].X += .1f * (Core.Data.Velocity).X;
		Vector2 CheatShift = Vector2(); //new Vector2(.15f, .35f) * Core.Data.Velocity;
		float l = ( vel - 2*AdditionalWind ).Length();
		if ( l > 15 )
		{
			CheatShift = ( vel - 1*AdditionalWind );
			CheatShift.Normalize();
			CheatShift = ( l - 15 ) * CheatShift;
		}
		MyCape->Move( CheatShift );
		//for (int i = 0; i < 1; i++)
		MyCape->PhsxStep();
		//MyCape.MyColor = Color.Gray;
	}

	void Bob::CorePhsxStep()
	{
	}

	void Bob::DollPhsxStep()
	{
		CurInput.A_Button = false;
		CurInput.B_Button = false;
		CurInput.xVec = Vector2();

		// Phsyics update
		MyPhsx->PhsxStep();

		// Integrate velocity
		getCore()->Data.Position += getCore()->Data.Velocity;
		if ( MyPhsx->UseGroundSpeed )
			getCore()->Data.Position += Vector2(GroundSpeed, 0);

		// Cape
		if ( getCore()->MyLevel->PlayMode == 0 && MyCape != 0 )
			UpdateCape();

		MyPhsx->OnGround = true;
	}

    void Bob::FlyingPhsx()
    {
		if ( MyPhsx->OnGround && CurInput.xVec.Y > 0) MyPhsx->setyVel( MyPhsx->getyVel() + .7f );

        MyPhsx->setVel( MyPhsx->getVel() * .985f );

        MyPhsx->setVel( MyPhsx->getVel() + CurInput.xVec );
    }

	void Bob::PhsxStep()
	{
		DoLightSourceFade();

		if ( !getCore()->Show )
			return;

		if ( CharacterSelect2 )
		{
			DollPhsxStep();
			return;
		}

		if ( ImmortalCountDown > 0 )
		{
			ImmortalCountDown--;
			if ( ImmortalCountDown < ImmortalLength - 15 )
			if ( fabs( CurInput.xVec.X ) > .5f || CurInput.A_Button )
				ImmortalCountDown = 0;
		}

		SaveNoBlock = false;


		int CurPhsxStep = getCore()->MyLevel->CurPhsxStep;



		// Bob connections
		if ( MyBobLinks.size() > 0 )
			for ( std::vector<boost::shared_ptr<BobLink> >::const_iterator link = MyBobLinks.begin(); link != MyBobLinks.end(); ++link )
				( *link )->PhsxStep( boost::static_pointer_cast<Bob>( shared_from_this() ) );

		if (Dead || Dying) DeadCount++;

		if ( Dying )
		{
			DyingPhsxStep();

			// Cape
			if ( getCore()->MyLevel->PlayMode == 0 && MyCape != 0 )
				UpdateCape();

			return;
		}

		// Track Star bonus book keeping
		if ( GiveStats() && getCore()->MyLevel->CurPhsxStep > 45 )
		{
			getMyTempStats()->FinalTimeSpent++;

			if ( fabs( CurInput.xVec.X ) < .75f )
				getMyTempStats()->FinalTimeSpentNotMoving++;
		}

		// Increment life counter
		if ( getCore()->MyLevel->PlayMode == 0 && !CompControl && !getCore()->MyLevel->Watching )
			getMyStats()->TimeAlive++;

		// Screen wrap
		CheckForScreenWrap();

		if ( !CharacterSelect_Renamed )
		{
			int Mode = getCore()->MyLevel->PlayMode;
			if ( getCore()->MyLevel->NumModes == 1 )
				if ( Mode == 1 )
					Mode = 2;

			switch ( Mode )
			{
				case 0:
					if ( !CompControl )
					{
						if ( Cinematic )
							Tools::Nothing(); //AnimAndUpdate();
						else
						{
							if ( CodeControl )
							{
								CurInput.Clean();
								if ( ControlFunc != 0 )
								{
									ControlCount++;
									ControlFunc->Apply( ControlCount );
								}
							}
							else
								GetPlayerInput();
						}
					}
					else
						GetRecordedInput( CurPhsxStep - IndexOffset );

					break;

				case 1:
					GetRecordedInput( CurPhsxStep - IndexOffset );

					break;

				case 2:
					MyPhsx->GenerateInput( CurPhsxStep );
					RecordInput( CurPhsxStep - IndexOffset );

					break;
			}
		}
		else
		{
			CurInput.A_Button = false;
			CurInput.B_Button = false;
			CurInput.xVec = Vector2();
		}

		// Phsyics update
		if ( MoveData.InvertDirX )
			CurInput.xVec.X *= -1;
		float Windx = Wind.X;
		if ( MyPhsx->OnGround )
			Windx /= 2;
		getCore()->Data.Velocity.X -= Windx;
        if (Flying)
            FlyingPhsx();
        else
			MyPhsx->PhsxStep();
		getCore()->Data.Velocity.X += Windx;
		MyPhsx->CopyPrev();
		if ( MoveData.InvertDirX )
			CurInput.xVec.X *= -1;

		// Collision with screen boundary
		if ( CollideWithCamera && !Cinematic )
		{
			Box->CalcBounds();
			if ( Box->TR.X > getCore()->MyLevel->getMainCamera()->TR.X - 40 && getCore()->Data.Velocity.X > 0 )
			{
				getCore()->Data.Velocity.X = 0;
				MyPhsx->SideHit( ColType_RIGHT, 0 );
				if ( Box->TR.X > getCore()->MyLevel->getMainCamera()->TR.X - 20 && getCore()->Data.Velocity.X > 0 )
				{
					Move( Vector2( getCore()->MyLevel->getMainCamera()->TR.X - 20 - Box->TR.X, 0 ) );
				}
			}
			if ( Box->BL.X < getCore()->MyLevel->getMainCamera()->BL.X + 40 && getCore()->Data.Velocity.X < 0 )
			{
				getCore()->Data.Velocity.X = 0;
				MyPhsx->SideHit( ColType_LEFT, 0 );
				if ( Box->BL.X < getCore()->MyLevel->getMainCamera()->BL.X + 20 && getCore()->Data.Velocity.X < 0 )
				{
					Move( Vector2( getCore()->MyLevel->getMainCamera()->BL.X + 20 - Box->BL.X, 0 ) );
				}
			}
		}


		// Integrate velocity
		if ( !Cinematic )
			//Core.Data.Position += Core.Data.Velocity + new Vector2(GroundSpeed, 0);
			MyPhsx->Integrate();

		// Cape
		if ( getCore()->MyLevel->PlayMode == 0 && MyCape != 0 )
			UpdateCape();
		Wind /= 2;
		CapeWind /= 2;

		// If cinematic, don't do any death or object interactions
		if ( Cinematic )
		{
			AnimAndUpdate();
			ControlCount++;
			if ( CinematicFunc != 0 )
				CinematicFunc->Apply( ControlCount );

			return;
		}

		// If too high, knock Bob down a bit
		if ( getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + 900 && getCore()->Data.Velocity.Y > 0 )
			getCore()->Data.Velocity.Y = 0;

		// Check for death by falling or by off screen
		if ( getCore()->MyLevel->PlayMode == 0 )
		{
			float DeathDist = 650;
			if ( getCore()->MyLevel->MyGame->MyGameFlags.IsTethered )
				DeathDist = 900;
			if ( getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - DeathDist )
				Die( BobDeathType_FALL );
			else if ( MyPhsx->Gravity < 0 && getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + DeathDist )
				Die( BobDeathType_FALL );
			else
				if ( getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + 1500 || getCore()->Data.Position.X < getCore()->MyLevel->getMainCamera()->BL.X - 550 || getCore()->Data.Position.X > getCore()->MyLevel->getMainCamera()->TR.X + 550 )
				{
					Die( BobDeathType_LEFT_BEHIND );
				}
		}

		// Check for death by time out
		if ( getCore()->MyLevel->PlayMode == 0 && getCore()->MyLevel->CurPhsxStep > getCore()->MyLevel->TimeLimit && getCore()->MyLevel->TimeLimit > 0 )
			Die( BobDeathType_TIME );

		// Initialize boxes for collision detection
		InitBoxesForCollisionDetect();

		/////////////////////////////////////////////////////////////////////////////////////////////
		//                 Block Interactions                                                      //
		/////////////////////////////////////////////////////////////////////////////////////////////            
		NewVel = 0;
		BlockInteractions();

		/////////////////////////////////////////////////////////////////////////////////////////////
		//                 Object Interactions                                                     //
		/////////////////////////////////////////////////////////////////////////////////////////////            
		if ( DoObjectInteractions )
			ObjectInteractions();

		// Reset boxes to normal
		Box->SetCurrent( getCore()->Data.Position, Box->Current->Size );
		Box2->SetCurrent( getCore()->Data.Position, Box2->Current->Size );

	//if (Core.MyLevel.PlayMode != 0)
	//    for (int i = 0; i <= NumBoxes; i++)
	//    {
	//        AABox box = Boxes[i];
	//        box.SetCurrent(Core.Data.Position, box.Current.Size);
	//    }

		// Closing phsx
		MyPhsx->PhsxStep2();

		PrevInput = CurInput;
	}

	void Bob::ObjectInteractions()
	{
		if ( getCore()->MyLevel->PlayMode != 0 )
		{
			// Create list of boxes
			if ( Boxes.empty() )
			{
				Boxes = std::vector<boost::shared_ptr<AABox> >();
				for ( int i = 0; i <= NumBoxes; i++ )
					Boxes.push_back( boost::make_shared<AABox>( Vector2(), Vector2(1) ) );
			}

			// Update box list
			UpdateBoxList();
		}
		else
			Box2->SetTarget( getCore()->Data.Position, Box2->Current->Size );
		Box->SetTarget( getCore()->Data.Position, Box->Current->Size + Vector2(.0f,.2f) );


		for ( ObjectVec::const_iterator obj = getCore()->MyLevel->ActiveObjectList.begin(); obj != getCore()->MyLevel->ActiveObjectList.end(); ++obj )
		{
			if ( !( *obj )->getCore()->MarkedForDeletion && (*obj)->getCore()->Real && (*obj)->getCore()->Active && (*obj)->getCore()->Show )
				( *obj )->Interact( boost::static_pointer_cast<Bob>( shared_from_this() ) );
		}
	}

	void Bob::UpdateBoxList()
	{
		float extra = 0; // 5;
		for ( int i = 0; i <= NumBoxes; i++ )
		{
			boost::shared_ptr<AABox> box = Boxes[ i ];

			box->Current->Size = Box2->Current->Size;

			//box.Current.Size.X += Upgrades.MaxBobWidth * ((NumBoxes - i) * .1f);

			box->Current->Size.X += extra + .7f * Upgrades::MaxBobWidth * ( ( NumBoxes - i ) *.1f );
			box->Current->Size.Y += extra + .23f * Upgrades::MaxBobWidth * ( ( NumBoxes - i ) *.1f );

			box->SetCurrent( Box2->Current->Center, box->Current->Size );
			box->SetTarget( getCore()->Data.Position, box->Current->Size );
		}
		RegularBox2 = Boxes[ Boxes.size() - 1 ];

		Box2->Current->Size.X += extra + .7f * Upgrades::MaxBobWidth;
		Box2->Current->Size.Y += extra + .23f * Upgrades::MaxBobWidth;
		Box2->SetTarget( getCore()->Data.Position, Box2->Current->Size );
	}

	void Bob::DeleteObj( const boost::shared_ptr<ObjectBase> &obj )
	{
		obj->getCore()->DeletedByBob = true;
		getCore()->getRecycle()->CollectObject(obj);
	}

	void Bob::BlockInteractions()
	{
		//OldBlockInteractions();
		NewBlockInteractions();
	}
	
	void Bob::NewBlockInteractions()
	{
		int CurPhsxStep = getCore()->MyLevel->CurPhsxStep;

		GroundSpeed = 0;

		SideHitCount--;
		if ( SideHitCount < 0 )
			SideHitCount = 0;

		MyPhsx->ResetJumpModifiers();

		BottomCol = TopCol = false;
		if ( CanInteract )
			if ( getCore()->MyLevel->PlayMode != 2 )
				MyPhsx->BlockInteractions();
			else
			{
				CeilingParams = boost::static_pointer_cast<Ceiling_Parameters>( getCore()->GetParams(Ceiling_AutoGen::getInstance()) );

				for ( BlockVec::const_iterator block = getCore()->MyLevel->Blocks.begin(); block != getCore()->MyLevel->Blocks.end(); ++block )
				{
					if ( MyPhsx->SkipInteraction( *block ) )
						continue;
					//if (block.Core.MarkedForDeletion || !block.IsActive || !block.Core.Real) continue;
					//if (block.BlockCore.OnlyCollidesWithLowerLayers && block.Core.DrawLayer <= Core.DrawLayer)
					//    continue;

					if ( ( *block )->PreDecision( boost::static_pointer_cast<Bob>( shared_from_this() ) ) )
						continue;
					if ( !( *block )->getIsActive() )
						continue;

					// Collision check
					ColType Col = Phsx::CollisionTest( Box, ( *block )->getBox() );
					bool Overlap = false;
					if ( !( *block )->getBox()->TopOnly || (*block)->getCore()->GenData.RemoveIfOverlap )
						Overlap = Phsx::BoxBoxOverlap( Box, ( *block )->getBox() );

					if ( Col != ColType_NO_COL || Overlap )
					{
						if ( ( *block )->PostCollidePreDecision( boost::static_pointer_cast<Bob>( shared_from_this() ) ) )
							continue;

						bool Delete = false;
						( *block )->PostCollideDecision( boost::static_pointer_cast<Bob>( shared_from_this() ), Col, Overlap, Delete );

						// We're done deciding if we should delete the block or not.
						// If we should delete it, delete.
						if ( Delete )
						{
							DeleteObj( *block );
							( *block )->setIsActive( false );
						}
						// Otherwise keep it and interact with it
						else
						{
							Delete = false;

							( *block )->PostKeep( boost::static_pointer_cast<Bob>( shared_from_this() ), Col, Overlap );

							if ( Col != ColType_NO_COL )
							{
								// We changed the blocks property, so Bob may no longer be on a collision course with it. Check to see if he is before marking block as used.
								if ( !( *block )->getBox()->TopOnly || Col == ColType_TOP )
								{
									if ( ( *block )->getCore()->GenData.RemoveIfUsed )
										Delete = true;

									if ( !Delete )
									{
										//if (Col == ColType.Bottom && !block.Core.GenData.Used)
										//    Tools::Write("");

										//if (!MyPhsx.SkipInteraction(block))
											InteractWithBlock( ( *block )->getBox(), *block, Col );
										( *block )->StampAsUsed( CurPhsxStep );
										MyPhsx->LastUsedStamp = CurPhsxStep;

										( *block )->PostInteractWith( boost::static_pointer_cast<Bob>( shared_from_this() ), Col, Overlap );
										//block.PostCollidePreDecision(this);
									}
								}
							}
						}
					}
				}
			}
	}

	void Bob::InitializeInstanceFields()
	{
		InputFromKeyboard = false;

		MyCapeType = static_cast<CapeType> ( 0 );

		LightSourceFade = 1;
		LightSourceFadeVel = 0;
		Dopple = false;
		CanHaveHat = true;
		temp = 0;
		Head = 0;
		CanInteract = true;
		TargetPosition = Vector2();
		ComputerWaitAtStartLength = 0;
		PlaceDelay = 23;
		DoNotTrackOffScreen = false;
		DrawWithLevel = true;
		AffectsCamera = true;
		ControlCount = 0;
		CodeControl = false;
		CollideWithCamera = true;
		LastCeiling = 0;
		NumBoxes = 10;
		PopModifier = 1;
		IsSpriteBased = true;
		Immobile = false;
		IsPlayer = true;
		DeathCount = 0;
		KillingObject = 0;
		CameraWeight = 1;
		ManualAnimAndUpdate = false;
		ExtraShift = Vector2();
		RocketOffset = Vector2( -60, 0 );
		DoObjectInteractions = true;
	}
}
