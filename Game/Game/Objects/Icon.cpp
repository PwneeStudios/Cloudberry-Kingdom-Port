#include <small_header.h>
#include "Game/Objects/Icon.h"

#include "Core/FancyVector2.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Game/Tools/Oscillate.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Tilesets/SpriteInfo.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Tilesets/TileSetInfo.h"

#include "Core/Texture/EzTextureWad.h"

namespace CloudberryKingdom
{

	void ObjectIcon::InitializeStatics()
	{
	}

	// Statics
	boost::shared_ptr<ObjectIcon> ObjectIcon::RobotIcon, ObjectIcon::PathIcon, ObjectIcon::SlowMoIcon;
	boost::shared_ptr<ObjectIcon> ObjectIcon::CheckpointIcon, ObjectIcon::RandomIcon, ObjectIcon::CustomIcon, ObjectIcon::CustomHoverIcon_Renamed;
	std::map<Upgrade, boost::shared_ptr<ObjectIcon> > ObjectIcon::UpgradeIcons;
	std::map<ObjectType, boost::shared_ptr<ObjectIcon> > ObjectIcon::ObjIcons;


	boost::shared_ptr<ObjectIcon> ObjectIcon::CreateIcon( Upgrade upgrade )
	{
		return CreateIcon( upgrade, false );
	}

	boost::shared_ptr<ObjectIcon> ObjectIcon::CreateIcon( Upgrade upgrade, bool big )
	{
		if ( UpgradeIcons.find( upgrade ) != UpgradeIcons.end() )
			return UpgradeIcons[ upgrade ]->Clone();
		else
		{
			boost::shared_ptr<CloudberryKingdom::TileInfoBase> info = TileSet::UpgradeToInfo( upgrade, TileSet::Get( std::wstring( L"castle" ) ) );

			boost::shared_ptr<PictureIcon> icon;
			if ( big && info->Icon_Big != 0 )
				icon = boost::make_shared<PictureIcon>( info->Icon_Big );
			else
				icon = boost::make_shared<PictureIcon>( info->Icon );

			icon->DisplayText = UpgradeName( upgrade );
			return icon;
		}
	}

	Localization::Words ObjectIcon::UpgradeName( Upgrade upgrade )
	{
		switch ( upgrade )
		{
			case Upgrade_BOUNCY_BLOCK:
				return Localization::Words_BouncyBlocks;
			case Upgrade_CLOUD:
				return Localization::Words_Clouds;
			case Upgrade_ELEVATOR:
				return Localization::Words_Elevators;
			case Upgrade_FALLING_BLOCK:
				return Localization::Words_FallingBlocks;
			case Upgrade_FIRE_SPINNER:
				return Localization::Words_Firespinners;
			case Upgrade_SPIKEY_GUY:
				return Localization::Words_Boulders;
			case Upgrade_PINKY:
				return Localization::Words_SpikeyGuys;
			case Upgrade_FLY_BLOB:
				return Localization::Words_FlyingBlobs;
			case Upgrade_GHOST_BLOCK:
				return Localization::Words_GhostBlocks;
			case Upgrade_LASER:
				return Localization::Words_Lasers;
			case Upgrade_MOVING_BLOCK:
				return Localization::Words_MovingBlocks;
			case Upgrade_SPIKE:
				return Localization::Words_Spikes;
			case Upgrade_FIREBALL:
				return Localization::Words_Fireballs;
			case Upgrade_FIRESNAKE:
				return Localization::Words_None;
			case Upgrade_SPIKEY_LINE:
				return Localization::Words_SpikeyLines;
			case Upgrade_SERPENT:
				return Localization::Words_Serpent;
			case Upgrade_LAVA_DRIP:
				return Localization::Words_Sludge;
			case Upgrade_PENDULUM:
				return Localization::Words_Pendulums;

			default:
				return Localization::Words_None;
		}
	}

	boost::shared_ptr<ObjectIcon> ObjectIcon::CreateIcon( ObjectType obj )
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
		UpgradeIcons = std::map<Upgrade, boost::shared_ptr<ObjectIcon> >();

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

		UpgradeIcons.insert( std::make_pair( Upgrade_JUMP, boost::make_shared<PictureIcon>( Localization::Words_JumpDifficulty, std::wstring( L"Jump" ), Color::Orange, StandardWidth * 1.07f ) ) );
		UpgradeIcons.insert( std::make_pair( Upgrade_SPEED, boost::make_shared<PictureIcon>( Localization::Words_LevelSpeed, std::wstring( L"SpeedIcon" ), Color::Orange, StandardWidth * 1.036f ) ) );
		UpgradeIcons.insert( std::make_pair( Upgrade_CEILING, boost::make_shared<PictureIcon>( Localization::Words_Ceilings, std::wstring( L"CeilingIcon" ), Color::Orange, StandardWidth *.9f ) ) );

		ObjIcons = std::map<ObjectType, boost::shared_ptr<ObjectIcon> >();
		//ObjIcons.Add(ObjectType.FallingBlock, UpgradeIcons[Upgrade.FallingBlock]);
		//ObjIcons.Add(ObjectType.MovingBlock, UpgradeIcons[Upgrade.MovingBlock]);
		//ObjIcons.Add(ObjectType.GhostBlock, UpgradeIcons[Upgrade.GhostBlock]);
		//ObjIcons.Add(ObjectType.FlyingBlob, UpgradeIcons[Upgrade.FlyBlob]);
		//ObjIcons.Add(ObjectType.BouncyBlock, UpgradeIcons[Upgrade.BouncyBlock]);

		//CheckIcon = new PictureIcon("Check", Color.Lime, StandardWidth * .85f);
		//UncheckedIcon = new PictureIcon("Uncheck", Color.Lime, StandardWidth * .85f);

		//CheckpointIcon = new PictureIcon("Icon_Checkpoint", Color.Lime, StandardWidth * .85f);
		CheckpointIcon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"Icon_Checkpoint_v2" ) ), Color::Lime, StandardWidth *.85f );
		//RandomIcon = new PictureIcon("Unknown", Color.Lime, StandardWidth * 1.2f);
		RandomIcon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"HeroIcon_Random" ) ), Color::Lime, StandardWidth * 1.08f );
		CustomIcon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"HeroIcon_Custom" ) ), Color::Lime, StandardWidth * 1.45f );

		//RobotIcon = new PictureIcon("Robot", Color.Lime, StandardWidth * .75f);
		//PathIcon = new PictureIcon("Path", Color.Lime, StandardWidth * .75f);
		//SlowMoIcon = new PictureIcon("SlowMo", Color.Lime, StandardWidth * .75f);
		RobotIcon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"Powerup_Computer" ) ), Color::Lime, StandardWidth *.75f );
		PathIcon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"Powerup_Path" ) ), Color::Lime, StandardWidth *.75f );
		SlowMoIcon = boost::make_shared<PictureIcon>( Tools::Texture( std::wstring( L"Powerup_SlowMo" ) ), Color::Lime, StandardWidth *.75f );
	}

	const Vector2 &ObjectIcon::getPos() const
	{
		return FancyPos->RelVal;
	}

	void ObjectIcon::setPos( const Vector2 &value )
	{
		FancyPos->RelVal = value;
	}

	ObjectIcon::ObjectIcon() :
		Flipped( false ),
		DisplayText( Localization::Words_None ),
		PrevSetRatio( 0 )
	{
		InitializeInstanceFields();
		MyOscillateParams.Set( 2, 1.02f,.215f );

		Backdrop = boost::make_shared<QuadClass>( boost::shared_ptr<FancyVector2>(), true );
		Backdrop->SetToDefault();
		Backdrop->setTextureName( std::wstring( L"Icon_Backdrop" ) );
		Backdrop->ScaleYToMatchRatio( 210 );
	}

	ObjectIcon::~ObjectIcon()
	{
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

	boost::shared_ptr<ObjectIcon> ObjectIcon::Clone( IconScale ScaleType )
	{
		boost::shared_ptr<ObjectIcon> icon = boost::make_shared<ObjectIcon>();

		icon->DisplayText = DisplayText;

		return icon;
	}

	boost::shared_ptr<ObjectIcon> ObjectIcon::Clone()
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
		FancyPos = boost::make_shared<FancyVector2>();
		PrevSetRatio = 1;
	}

	std::vector<std::wstring> PictureIcon::GetViewables()
	{
		return std::vector<std::wstring> ();
	}

	PictureIcon::PictureIcon( const boost::shared_ptr<SpriteInfo> &info ) :
		NormalWidth( 0 )
	{
		IconQuad = boost::make_shared<QuadClass>( FancyPos, true );
		IconQuad->Set( info );

		IconQuad->Quad_Renamed.Playing = false;

		if ( IconQuad->Quad_Renamed.TextureAnim == 0 )
			IconTexture = IconQuad->Quad_Renamed.getMyTexture();
		else
			IconTexture = IconQuad->Quad_Renamed.TextureAnim->Anims[ 0 ].Data[ 0 ];

		this->DisplayText = Localization::Words_None;
		this->NormalWidth = 161 * 1.31f * info->Size.X / 62;
	}

	PictureIcon::PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width ) :
		NormalWidth( 0 )
	{
		this->DisplayText = DisplayText;
		Init( Tools::TextureWad->FindByName( IconTextureString ), BarColor, Width );
	}

	PictureIcon::PictureIcon( Localization::Words DisplayText, const std::wstring &IconTextureString, Color BarColor, float Width, Vector2 HitPadding ) :
		NormalWidth( 0 )
	{
		this->DisplayText = DisplayText;
		this->HitPadding = HitPadding;
		Init( Tools::TextureWad->FindByName( IconTextureString ), BarColor, Width );
	}

	PictureIcon::PictureIcon( const std::wstring &IconTextureString, Color BarColor, float Width ) :
		NormalWidth( 0 )
	{
		Init( Tools::TextureWad->FindByName( IconTextureString ), BarColor, Width );
	}

	PictureIcon::PictureIcon( const boost::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width ) :
		NormalWidth( 0 )
	{
		Init( IconTexture, BarColor, Width );
	}

	void PictureIcon::Init( const boost::shared_ptr<EzTexture> &IconTexture, Color BarColor, float Width )
	{
		this->IconTexture = IconTexture;
		this->BarColor = BarColor;
		this->NormalWidth = Width;

		IconQuad = boost::make_shared<QuadClass>( FancyPos, true );
		IconQuad->SetToDefault();
		IconQuad->Quad_Renamed.setMyTexture( IconTexture );
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
			IconQuad->Quad_Renamed.SetColor( bColor( 100, 100, 100 ) );
		else
			IconQuad->Quad_Renamed.SetColor( Color::White );
	}

	boost::shared_ptr<ObjectIcon> PictureIcon::Clone( IconScale ScaleType )
	{
		float width = NormalWidth;
		if ( ScaleType == IconScale_WIDGET )
			width *= .3f;
		if ( ScaleType == IconScale_NEARLY_FULL )
			width *= .9f;

		boost::shared_ptr<PictureIcon> icon = boost::make_shared<PictureIcon>( IconTexture, BarColor, width );
		icon->DisplayText = DisplayText;
		icon->IconQuad->Quad_Renamed.v0 = IconQuad->Quad_Renamed.v0;
		icon->IconQuad->Quad_Renamed.v1 = IconQuad->Quad_Renamed.v1;
		icon->IconQuad->Quad_Renamed.v2 = IconQuad->Quad_Renamed.v2;
		icon->IconQuad->Quad_Renamed.v3 = IconQuad->Quad_Renamed.v3;

		icon->HitPadding = HitPadding;

		return boost::static_pointer_cast<ObjectIcon>( icon );
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
		return std::vector<std::wstring> ();
	}

	CustomHoverIcon::CustomHoverIcon()
	{
		YQuad = boost::make_shared<QuadClass>( FancyPos, true );
		YQuad->SetToDefault();
		YQuad->setTextureName( std::wstring( L"Xbox_Y" ) );
		YQuad->ScaleYToMatchRatio( 60 );
		YQuad->setPos( Vector2( 60, 0 ) );

		GearQuad = boost::make_shared<QuadClass>( FancyPos, true );
		GearQuad->SetToDefault();
		GearQuad->setTextureName( std::wstring( L"Gears" ) );
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
