#include "MenuToggle.h"
#include "Core/Text/EzFont.h"
#include "Core/Text/EzText.h"
#include "Game/Localization.h"
#include "Core/Lambdas/Lambda_1.h"
#include "Core/Input/ButtonCheck.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

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
