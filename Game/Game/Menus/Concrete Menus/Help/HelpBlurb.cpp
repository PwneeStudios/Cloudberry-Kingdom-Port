#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{

	HelpBlurb::SetText_ActionHelper::SetText_ActionHelper( const std::shared_ptr<HelpBlurb> &hb, Localization::Words Word )
	{
		this->hb = hb;
		this->Word = Word;
	}

	void HelpBlurb::SetText_ActionHelper::Apply()
	{
		hb->SetText( Word );
	}

	HelpBlurb::HelpBlurb()
	{
		MyPile = std::make_shared<DrawPile>();

		std::shared_ptr<QuadClass> Berry = std::make_shared<QuadClass>();
		Berry->SetToDefault();
		Berry->setTextureName( _T( "cb_surprised" ) );
		Berry->Scale( 625 );
		Berry->ScaleYToMatchRatio();

		Berry->setPos( Vector2( 1422, -468 ) );
		MyPile->Add( Berry );
	}

	void HelpBlurb::Init()
	{
		CkBaseMenu::Init();

		SlideInFrom = SlideOutTo = PresetPos_RIGHT;
	}

	std::shared_ptr<Lambda> HelpBlurb::SetText_Action( Localization::Words Word )
	{
		return std::make_shared<SetText_ActionHelper>( this, Word );
	}

	void HelpBlurb::SetText( Localization::Words Word )
	{
		// Erase previous text
		MyPile->MyTextList.clear();

		// Add the new text
		std::shared_ptr<EzText> Text = std::make_shared<EzText>( Word, ItemFont, 800, false, false,.575f );
		Text->setPos( Vector2( -139.4445f, 536.1113f ) );
		Text->setScale( Text->getScale() * .74f );
		MyPile->Add( Text );
	}
}
