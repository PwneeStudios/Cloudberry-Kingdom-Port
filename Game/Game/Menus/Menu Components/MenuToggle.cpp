#include <global_header.h>

namespace CloudberryKingdom
{

	MenuToggle::MenuToggle( const std::shared_ptr<EzFont> &Font )
	{
		InitializeInstanceFields();
		std::shared_ptr<EzText> text = std::make_shared<EzText>( _T( "xxxxx" ), Font );
		MenuItem::Init( text, text->Clone() );
	}

	void MenuToggle::Toggle( bool state )
	{
		MyState = state;

		if ( state )
		{
			MyText->SubstituteText( Localization::Words_ON );
			MySelectedText->SubstituteText( Localization::Words_ON );
		}
		else
		{
			MyText->SubstituteText( Localization::Words_OFF );
			MySelectedText->SubstituteText( Localization::Words_OFF );
		}
	}

	void MenuToggle::PhsxStep( bool Selected )
	{
		MenuItem::PhsxStep( Selected );

		if ( !Selected )
			return;

		if ( ButtonCheck::State( ControllerButtons_A, Control ).Pressed )
		{
			Toggle( !MyState );

			if ( OnToggle != 0 )
				OnToggle->Apply( MyState );
		}
	}

	void MenuToggle::InitializeInstanceFields()
	{
		MyState = false;
	}
}
