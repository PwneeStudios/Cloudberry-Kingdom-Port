#include <global_header.h>

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

namespace CloudberryKingdom
{

	GamerTag::GamerTag( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	{
		InitializeInstanceFields();
		this->Tags += Tag_CHAR_SELECT;
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();
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

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		SetGamerTag();

		CharacterSelect::Shift( shared_from_this() );
	}

	void GamerTag::ScaleGamerTag( const std::shared_ptr<EzText> &GamerTag_Renamed )
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
			Text = std::make_shared<EzText>( name, Resources::Font_Grobold42, true, true );
			ScaleGamerTag( Text );
		}
		else
		{
			Text = std::make_shared<EzText>( _T( "ERROR" ), Resources::LilFont, true, true );
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
