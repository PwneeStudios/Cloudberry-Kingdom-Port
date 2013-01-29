#include <global_header.h>

namespace CloudberryKingdom
{

	MenuToggle::MenuToggle( const boost::shared_ptr<EzFont> &Font )
	{
		InitializeInstanceFields();
	}

	boost::shared_ptr<MenuToggle> MenuToggle::MenuToggle_Construct( const boost::shared_ptr<EzFont> &Font )
	{
		MenuItem::MenuItem_Construct();

		boost::shared_ptr<EzText> text = boost::make_shared<EzText>( std::wstring( L"xxxxx" ), Font );
		MenuItem::Init( text, text->Clone() );

		return boost::static_pointer_cast<MenuToggle>( shared_from_this() );
	}

	void MenuToggle::Toggle( bool state )
	{
		MyState = state;

		if ( state )
		{
			MyText->SubstituteText( Localization::Words_On );
			MySelectedText->SubstituteText( Localization::Words_On );
		}
		else
		{
			MyText->SubstituteText( Localization::Words_Off );
			MySelectedText->SubstituteText( Localization::Words_Off );
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
