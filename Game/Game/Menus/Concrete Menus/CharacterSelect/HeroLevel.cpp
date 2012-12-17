#include <global_header.h>

namespace CloudberryKingdom
{

	//HeroLevel::HeroLevel( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	HeroLevel::HeroLevel( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) :
		ShowHeroLevel( 0 )
	{
	}
	boost::shared_ptr<HeroLevel> HeroLevel::HeroLevel_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) 
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( false );
		
		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();

		return boost::static_pointer_cast<HeroLevel>( shared_from_this() );
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

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		SetHeroLevel();

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
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
			Text = boost::make_shared<EzText>( name, Resources::Font_Grobold42, true, true );
		}
		else
		{
			Text = boost::make_shared<EzText>( _T( "ERROR" ), Resources::LilFont, true, true );
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
