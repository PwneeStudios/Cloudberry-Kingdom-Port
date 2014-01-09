#include <small_header.h>
#include "Game/Menus/Concrete Menus/Help/HelpBlurb.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"


namespace CloudberryKingdom
{

	HelpBlurb::SetText_ActionHelper::SetText_ActionHelper( const boost::shared_ptr<HelpBlurb> &hb, Localization::Words Word )
	{
		this->hb = hb;
		this->Word = Word;
	}

	void HelpBlurb::SetText_ActionHelper::Apply()
	{
		hb->SetText( Word );
	}

	HelpBlurb::HelpBlurb() { }
	boost::shared_ptr<HelpBlurb> HelpBlurb::HelpBlurb_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		MyPile = boost::make_shared<DrawPile>();

		boost::shared_ptr<QuadClass> Berry = boost::make_shared<QuadClass>();
		Berry->SetToDefault();
		Berry->setTextureName( std::wstring( L"cb_surprised" ) );
		Berry->Scale( 625 );
		Berry->ScaleYToMatchRatio();

		Berry->setPos( Vector2( 1422, -468 ) );
		MyPile->Add( Berry );

		return boost::static_pointer_cast<HelpBlurb>( shared_from_this() );
	}

	void HelpBlurb::Init()
	{
		CkBaseMenu::Init();

		SlideInFrom = SlideOutTo = PresetPos_RIGHT;
	}

	boost::shared_ptr<Lambda> HelpBlurb::SetText_Action( Localization::Words Word )
	{
		return boost::make_shared<SetText_ActionHelper>( boost::static_pointer_cast<HelpBlurb>( shared_from_this() ), Word );
	}

	void HelpBlurb::SetText( Localization::Words Word )
	{
		// Erase previous text
		MyPile->MyTextList.clear();

		// Add the new text
		boost::shared_ptr<EzText> Text = boost::make_shared<EzText>( Word, ItemFont, 800.f, false, false, .575f );
		Text->setPos( Vector2( -139.4445f, 536.1113f ) );
		Text->setScale( Text->getScale() * .74f );
		MyPile->Add( Text );
	}
}
