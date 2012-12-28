#include <global_header.h>

#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	//GamerTag::GamerTag( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	GamerTag::GamerTag( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) :
		ShowGamerTag( false )
	{
	}
	boost::shared_ptr<GamerTag> GamerTag::GamerTag_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect )
	{
		InitializeInstanceFields();

		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();

		return boost::static_pointer_cast<GamerTag>( shared_from_this() );
	}

	void GamerTag::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void GamerTag::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		SetGamerTag();

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	void GamerTag::ScaleGamerTag( const boost::shared_ptr<EzText> &GamerTag_Renamed )
	{
		GamerTag_Renamed->setScale( GamerTag_Renamed->getScale() * 850 / GamerTag_Renamed->GetWorldWidth() );

		float Height = GamerTag_Renamed->GetWorldHeight();
		float MaxHeight = 380;
		if ( Height > MaxHeight )
			GamerTag_Renamed->setScale( GamerTag_Renamed->getScale() * MaxHeight / Height );
	}

	void GamerTag::SetGamerTag()
	{
		if ( !ShowGamerTag )
			return;

		Tools::StartGUIDraw();
		if ( MyCharacterSelect->getPlayer()->Exists )
		{
			std::wstring name = MyCharacterSelect->getPlayer()->GetName();
			Text = boost::make_shared<EzText>( name, Resources::Font_Grobold42, true, true );
			ScaleGamerTag( Text );
		}
		else
		{
			Text = boost::make_shared<EzText>( std::wstring( L"ERROR" ), Resources::LilFont, true, true );
		}

		Text->Shadow = false;
		Text->PicShadow = false;

		Tools::EndGUIDraw();
	}

	void GamerTag::InitializeInstanceFields()
	{
		ShowGamerTag = false;
	}
}
