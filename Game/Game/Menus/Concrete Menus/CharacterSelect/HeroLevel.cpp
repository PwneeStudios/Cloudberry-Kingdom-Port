#include <global_header.h>

namespace CloudberryKingdom
{

	//HeroLevel::HeroLevel( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	HeroLevel::HeroLevel( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) :
		ShowHeroLevel( 0 )
	{
	}
	std::shared_ptr<HeroLevel> HeroLevel::HeroLevel_Construct( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) 
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		InitializeInstanceFields();
		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();

		return std::static_pointer_cast<HeroLevel>( shared_from_this() );
	}

	void HeroLevel::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void HeroLevel::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		SetHeroLevel();

		CharacterSelect::Shift( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	void HeroLevel::SetHeroLevel()
	{
		if ( !ShowHeroLevel )
			return;

		Tools::StartGUIDraw();
		if ( MyCharacterSelect->getPlayer()->Exists )
		{
			//string name = MyCharacterSelect.Player.GetName();
			std::wstring name = _T( "Level 56" );
			Text = std::make_shared<EzText>( name, Resources::Font_Grobold42, true, true );
		}
		else
		{
			Text = std::make_shared<EzText>( _T( "ERROR" ), Resources::LilFont, true, true );
		}

		Text->Shadow = false;
		Text->PicShadow = false;

		Tools::EndGUIDraw();
	}

	void HeroLevel::InitializeInstanceFields()
	{
		ShowHeroLevel = false;
	}
}
