#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


namespace CloudberryKingdom
{

	std::vector<std::wstring> ObjectIcon::GetViewables()
	{
		return std::vector<std::wstring*> ();
	}

std::shared_ptr<ObjectIcon> RobotIcon, PathIcon, ObjectIcon::SlowMoIcon = 0;
std::shared_ptr<ObjectIcon> CheckpointIcon, RandomIcon, CustomIcon, ObjectIcon::CustomHoverIcon = 0;
std::unordered_map<Upgrade, ObjectIcon*> ObjectIcon::UpgradeIcons = 0;
std::unordered_map<ObjectType, ObjectIcon*> ObjectIcon::ObjIcons = 0;

	std::shared_ptr<ObjectIcon> ObjectIcon::CreateIcon( Upgrade upgrade )
	{
		return CreateIcon( upgrade, false );
	}

	std::shared_ptr<ObjectIcon> ObjectIcon::CreateIcon( Upgrade upgrade, bool big )
	{
		if ( UpgradeIcons.find( upgrade ) != UpgradeIcons.end() )
			return UpgradeIcons[ upgrade ]->Clone();
		else
		{
			std::shared_ptr<CloudberryKingdom::TileInfoBase> info = TileSet::UpgradeToInfo( upgrade, _T( "castle" ) );

			std::shared_ptr<PictureIcon> icon;
			if ( big && info->Icon_Big != 0 )
				icon = std::make_shared<PictureIcon>( info->Icon_Big );
			else
				icon = std::make_shared<PictureIcon>( info->Icon );

			icon->DisplayText = UpgradeName( upgrade );
			return icon;
		}
	}

	Localization::Words ObjectIcon::UpgradeName( Upgrade upgrade )
	{
		switch ( upgrade )
		{
			case Upgrade_BOUNCY_BLOCK:
				return Localization::Words_BOUNCY_BLOCKS;
			case Upgrade_CLOUD:
				return Localization::Words_CLOUDS;
			case Upgrade_ELEVATOR:
				return Localization::Words_ELEVATORS;
			case Upgrade_FALLING_BLOCK:
				return Localization::Words_FALLING_BLOCKS;
			case Upgrade_FIRE_SPINNER:
				return Localization::Words_FIRESPINNERS;
			case Upgrade_SPIKEY_GUY:
				return Localization::Words_BOULDERS;
			case Upgrade_PINKY:
				return Localization::Words_SPIKEY_GUYS;
			case Upgrade_FLY_BLOB:
				return Localization::Words_FLYING_BLOBS;
			case Upgrade_GHOST_BLOCK:
				return Localization::Words_GHOST_BLOCKS;
			case Upgrade_LASER:
				return Localization::Words_LASERS;
			case Upgrade_MOVING_BLOCK:
				return Localization::Words_MOVING_BLOCKS;
			case Upgrade_SPIKE:
				return Localization::Words_SPIKES;
			case Upgrade_FIREBALL:
				return Localization::Words_FIREBALLS;
			case Upgrade_FIRESNAKE:
				return Localization::Words_NONE;
			case Upgrade_SPIKEY_LINE:
				return Localization::Words_SPIKEY_LINES;
			case Upgrade_SERPENT:
				return Localization::Words_SERPENT;
			case Upgrade_LAVA_DRIP:
				return Localization::Words_SLUDGE;
			case Upgrade_PENDULUM:
				return Localization::Words_PENDULUMS;

			default:
				return Localization::Words_NONE;
		}
	}

	std::shared_ptr<ObjectIcon> ObjectIcon::CreateIcon( ObjectType obj )
	{
		switch ( obj )
		{
			case ObjectType_FALLING_BLOCK:
				return CreateIcon( Upgrade_FALLING_BLOCK );
			case ObjectType_MOVING_BLOCK:
				return CreateIcon( Upgrade_MOVING_BLOCK );
			case ObjectType_GHOST_BLOCK:
				return CreateIcon( Upgrade_GHOST_BLOCK );
			case ObjectType_FLYING_BLOB:
				return CreateIcon( Upgrade_FLY_BLOB );
			case ObjectType_BOUNCY_BLOCK:
				return CreateIcon( Upgrade_BOUNCY_BLOCK );
		}

		return 0;
		//return ObjIcons[obj].Clone();
	}

	void ObjectIcon::InitIcons()
	{
		UpgradeIcons = std::unordered_map<Upgrade, ObjectIcon*>();

		float StandardWidth = 161 * 1.31f;
		//UpgradeIcons.Add(Upgrade.BouncyBlock, new PictureIcon("Bouncy blocks", "Icon_BouncyBlock1", Color.Lime, StandardWidth*.555f));
		//UpgradeIcons.Add(Upgrade.Cloud, new PictureIcon("Clouds", "Icon_Cloud3", Color.LightGray, StandardWidth*1.135f));
		//UpgradeIcons.Add(Upgrade.Elevator, new PictureIcon("Elevators", "Icon_Palette", Color.LightBlue, StandardWidth*.810f));
		//UpgradeIcons.Add(Upgrade.FallingBlock, new PictureIcon("Falling blocks", "Icon_FallingBlock1", Color.Red, StandardWidth*.555f));
		//UpgradeIcons.Add(Upgrade.FireSpinner, new PictureIcon("Fire spinners", "Icon_FireSpinner2", Color.Orange, StandardWidth*1.022f));
		//UpgradeIcons.Add(Upgrade.SpikeyGuy, new PictureIcon("Spikey guys", "Icon_Spikey", Color.LightGray, StandardWidth*.835f));
		//UpgradeIcons.Add(Upgrade.Pinky, new PictureIcon("Pinkies", "Pinky", Color.LightGray, StandardWidth*.835f));
		//UpgradeIcons.Add(Upgrade.FlyBlob, new PictureIcon("Flying blobs", "Icon_Blob", Color.Lime, StandardWidth*1.056f, new Vector2(0, -45)));
		//UpgradeIcons.Add(Upgrade.GhostBlock, new PictureIcon("Ghost blocks", "Icon_Ghost", Color.Lime, StandardWidth*1.148f, new Vector2(0, -80)));
		//UpgradeIcons.Add(Upgrade.Laser, new PictureIcon("Lasers", "Icon_Laser2", Color.Red, StandardWidth*.72f));
		//UpgradeIcons.Add(Upgrade.MovingBlock, new PictureIcon("Moving blocks", "Blue_Small", Color.LightBlue, StandardWidth*.62f));
		//UpgradeIcons.Add(Upgrade.Spike, new PictureIcon("Spikes", "Icon_Spike2", Color.LightGray, StandardWidth*.99f));
		//UpgradeIcons.Add(Upgrade.Fireball, new PictureIcon("Fireballs", "Icon_Fireball", Color.Orange, StandardWidth*.905f));
		//UpgradeIcons.Add(Upgrade.Firesnake, new PictureIcon("Firesnake", "Icon_Firesnake", Color.Orange, StandardWidth * .905f));
		//UpgradeIcons.Add(Upgrade.SpikeyLine, new PictureIcon("Spikey line", "Icon_SpikeyLine", Color.Orange, StandardWidth * .905f));

		UpgradeIcons.insert( make_pair( Upgrade_JUMP, std::make_shared<PictureIcon>( Localization::Words_JUMP_DIFFICULTY, _T( "Jump" ), Color::Orange, StandardWidth * 1.07f ) ) );
		UpgradeIcons.insert( make_pair( Upgrade_SPEED, std::make_shared<PictureIcon>( Localization::Words_LEVEL_SPEED, _T( "SpeedIcon" ), Color::Orange, StandardWidth * 1.036f ) ) );
		UpgradeIcons.insert( make_pair( Upgrade_CEILING, std::make_shared<PictureIcon>( Localization::Words_CEILINGS, _T( "CeilingIcon" ), Color::Orange, StandardWidth *.9f ) ) );

		ObjIcons = std::unordered_map<ObjectType, ObjectIcon*>();
		//ObjIcons.Add(ObjectType.FallingBlock, UpgradeIcons[Upgrade.FallingBlock]);
		//ObjIcons.Add(ObjectType.MovingBlock, UpgradeIcons[Upgrade.MovingBlock]);
		//ObjIcons.Add(ObjectType.GhostBlock, UpgradeIcons[Upgrade.GhostBlock]);
		//ObjIcons.Add(ObjectType.FlyingBlob, UpgradeIcons[Upgrade.FlyBlob]);
		//ObjIcons.Add(ObjectType.BouncyBlock, UpgradeIcons[Upgrade.BouncyBlock]);

		//CheckIcon = new PictureIcon("Check", Color.Lime, StandardWidth * .85f);
		//UncheckedIcon = new PictureIcon("Uncheck", Color.Lime, StandardWidth * .85f);

		//CheckpointIcon = new PictureIcon("Icon_Checkpoint", Color.Lime, StandardWidth * .85f);
		CheckpointIcon = std::make_shared<PictureIcon>( _T( "Icon_Checkpoint_v2" ), Color::Lime, StandardWidth *.85f );
		//RandomIcon = new PictureIcon("Unknown", Color.Lime, StandardWidth * 1.2f);
		RandomIcon = std::make_shared<PictureIcon>( _T( "HeroIcon_Random" ), Color::Lime, StandardWidth * 1.08f );
		CustomIcon = std::make_shared<PictureIcon>( _T( "HeroIcon_Custom" ), Color::Lime, StandardWidth * 1.45f );

		//RobotIcon = new PictureIcon("Robot", Color.Lime, StandardWidth * .75f);
		//PathIcon = new PictureIcon("Path", Color.Lime, StandardWidth * .75f);
		//SlowMoIcon = new PictureIcon("SlowMo", Color.Lime, StandardWidth * .75f);
		RobotIcon = std::make_shared<PictureIcon>( _T( "Powerup_Computer" ), Color::Lime, StandardWidth *.75f );
		PathIcon = std::make_shared<PictureIcon>( _T( "Powerup_Path" ), Color::Lime, StandardWidth *.75f );
		SlowMoIcon = std::make_shared<PictureIcon>( _T( "Powerup_SlowMo" ), Color::Lime, StandardWidth *.75f );
	}

	const Microsoft::Xna::Framework::Vector2 &ObjectIcon::getPos() const
	{
		return FancyPos->RelVal;
	}

	void ObjectIcon::setPos( const Vector2 &value )
	{
		FancyPos->RelVal = value;
	}

	ObjectIcon::ObjectIcon()
	{
		InitializeInstanceFields();
		MyOscillateParams.Set( 2, 1.02f,.215f );

		Backdrop = std::make_shared<QuadClass>( 0, true );
		Backdrop->SetToDefault();
		Backdrop->setTextureName( _T( "Icon_Backdrop" ) );
		Backdrop->ScaleYToMatchRatio( 210 );
	}

	void ObjectIcon::SetShadow( Color color )
	{
	}

	void ObjectIcon::SetShadow( bool Shadow )
	{
	}

	void ObjectIcon::Fade( bool fade )
	{
	}

	std::shared_ptr<ObjectIcon> ObjectIcon::Clone( IconScale ScaleType )
	{
		std::shared_ptr<ObjectIcon> icon = std::make_shared<ObjectIcon>();

		icon->DisplayText = DisplayText;

		return icon;
	}

	std::shared_ptr<ObjectIcon> ObjectIcon::Clone()
	{
		return Clone( IconScale_FULL );
	}

	void ObjectIcon::SetScale( float Ratio )
	{
		PrevSetRatio = Ratio;
	}

	void ObjectIcon::Draw( bool Selected )
	{
		FancyPos->Update();
		Backdrop->setPos( FancyPos->AbsVal );
		//Backdrop.Draw();
	}

#if defined(WINDOWS)
	bool ObjectIcon::HitTest( Vector2 pos )
	{
		return false;
	}
#endif

	void ObjectIcon::InitializeInstanceFields()
	{
		Flipped = false;
		FancyPos = std::make_shared<FancyVector2>();
		PrevSetRatio = 1;
	}

	std::vector<std::wstring> PictureIcon::GetViewables()
	{
		return std::vector<std::wstring*> ();
	}

	PictureIcon::PictureIcon( const std::shared_ptr<SpriteInfo> &info )
	{
		IconQuad = std::make_shared<QuadClass>( FancyPos, true );
		IconQuad->Set( info );

		IconQuad->Quad_Renamed->Playing = false;

		if ( IconQuad->Quad_Renamed->TextureAnim == 0 )
			IconTexture = IconQuad->Quad_Renamed->MyTexture;
		else
			IconTexture = IconQuad->Quad_Renamed->TextureAnim->Anims[ 0 ]->Data[ 0 ];

		this->DisplayText = Localization::Words_NONE;
		this->NormalWidth = 161 * 1.31f * info->Size.X / 62;
	}

	PictureIcon::PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width )
	{
		this->DisplayText = DisplayText;
		Init( Tools::TextureWad->FindByName( IconTextureString ), BarColor, Width );
	}

	PictureIcon::PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width, Vector2 HitPadding )
	{
		this->DisplayText = DisplayText;
		this->HitPadding = HitPadding;
		Init( Tools::TextureWad->FindByName( IconTextureString ), BarColor, Width );
	}

	PictureIcon::PictureIcon( const std::wstring &IconTextureString, Color BarColor, float Width )
	{
		Init( Tools::TextureWad->FindByName( IconTextureString ), BarColor, Width );
	}

	PictureIcon::PictureIcon( const std::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width )
	{
		Init( IconTexture, BarColor, Width );
	}

	void PictureIcon::Init( const std::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width )
	{
		this->IconTexture = IconTexture;
		this->BarColor = BarColor;
		this->NormalWidth = Width;

		IconQuad = std::make_shared<QuadClass>( FancyPos, true );
		IconQuad->SetToDefault();
		IconQuad->Quad_Renamed->MyTexture = IconTexture;
		IconQuad->ScaleYToMatchRatio( Width );

		IconQuad->Shadow = true;
		IconQuad->ShadowColor = Color( .2f,.2f,.2f, 1 );
		IconQuad->ShadowOffset = Vector2( 12, 12 );
	}

	void PictureIcon::SetShadow( Color color )
	{
		ObjectIcon::SetShadow( color );

		IconQuad->ShadowColor = color;
	}

	void PictureIcon::SetShadow( bool Shadow )
	{
		ObjectIcon::SetShadow( Shadow );

		IconQuad->Shadow = Shadow;
	}

	void PictureIcon::Fade( bool fade )
	{
		ObjectIcon::Fade( fade );

		if ( fade )
			IconQuad->Quad_Renamed->SetColor( Color( 100, 100, 100 ) );
		else
			IconQuad->Quad_Renamed->SetColor( Color::White );
	}

	std::shared_ptr<ObjectIcon> PictureIcon::Clone( IconScale ScaleType )
	{
		float width = NormalWidth;
		if ( ScaleType == IconScale_WIDGET )
			width *= .3f;
		if ( ScaleType == IconScale_NEARLY_FULL )
			width *= .9f;

		std::shared_ptr<PictureIcon> icon = std::make_shared<PictureIcon>( IconTexture, BarColor, width );
		icon->DisplayText = DisplayText;
		icon->IconQuad->Quad_Renamed->v0 = IconQuad->Quad_Renamed->v0;
		icon->IconQuad->Quad_Renamed->v1 = IconQuad->Quad_Renamed->v1;
		icon->IconQuad->Quad_Renamed->v2 = IconQuad->Quad_Renamed->v2;
		icon->IconQuad->Quad_Renamed->v3 = IconQuad->Quad_Renamed->v3;

		icon->HitPadding = HitPadding;

		return static_cast<ObjectIcon*>( icon );
	}

	void PictureIcon::SetScale( float Ratio )
	{
		ObjectIcon::SetScale( Ratio );

		IconQuad->Scale( Ratio * NormalWidth / IconQuad->getSize().X );
	}

	void PictureIcon::Draw( bool Selected )
	{
		ObjectIcon::Draw( Selected );

		if ( Selected )
		{
			Vector2 HoldSize = IconQuad->getSize();
			IconQuad->Scale( MyOscillateParams.GetScale() );
			//IconQuad.Scale(Oscillate.GetScale(SelectCount, 2f, 1.02f, .215f));
			IconQuad->Draw();
			IconQuad->setSize( HoldSize );
		}
		else
		{
			// Flip if level is flipped
			if ( Flipped )
			{
				if ( IconQuad->Base.e1.X > 0 )
					IconQuad->setSizeX( IconQuad->getSizeX() * -1 );
			}

			IconQuad->Draw();
			MyOscillateParams.Reset();
		}
	}

#if defined(WINDOWS)
	bool PictureIcon::HitTest( Vector2 pos )
	{
		return IconQuad->HitTest( pos, HitPadding ) || ObjectIcon::HitTest( pos );
	}
#endif

	std::vector<std::wstring> CustomHoverIcon::GetViewables()
	{
		return std::vector<std::wstring*> ();
	}

	CustomHoverIcon::CustomHoverIcon()
	{
		YQuad = std::make_shared<QuadClass>( FancyPos, true );
		YQuad->SetToDefault();
		YQuad->setTextureName( _T( "Xbox_Y" ) );
		YQuad->ScaleYToMatchRatio( 60 );
		YQuad->setPos( Vector2( 60, 0 ) );

		GearQuad = std::make_shared<QuadClass>( FancyPos, true );
		GearQuad->SetToDefault();
		GearQuad->setTextureName( _T( "Gears" ) );
		GearQuad->ScaleYToMatchRatio( 82 );
		GearQuad->setPos( Vector2( -60.55469f, -16.66663f ) );
	}

	void CustomHoverIcon::Draw( bool Selected )
	{
		ObjectIcon::Draw( Selected );

		YQuad->Draw();
		GearQuad->Draw();
	}
}
