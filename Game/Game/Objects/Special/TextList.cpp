#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

	void TextList::Release()
	{
		ObjectBase::Release();

		Text.clear();
	}

	void TextList::MakeNew()
	{
	}

	TextList::TextList()
	{
		Text = std::vector<EzText*>();
		SetIndex( 0 );

		Alpha = 1;
	}

	void TextList::SetIndex( int index )
	{
		ContinuousIndex = Index = index;
	}

	void TextList::PhsxStep()
	{
		ContinuousIndex += .2f * ( Index - ContinuousIndex );

		if ( FadeOut )
			Alpha = __max( 0, Alpha - .03f );
	}

	void TextList::Draw()
	{
		//PhsxStep();

		for ( int i = Index - 2; i <= Index + 2; i++ )
		{
			if ( i >= 0 && i < Text.size() )
			{
				Text[ i ]->_Pos = getCore()->Data.Position - (i - ContinuousIndex) * Vector2(0, 100);
				Text[ i ]->MyFloatColor->W = Alpha *.5f * ( 2 - abs( i - ContinuousIndex ) );
				Text[ i ]->Draw( MyCam, false );
			}
		}
		Tools::Render->EndSpriteBatch();
	}

	void TextList::ShiftUp()
	{
		Index++;
		if ( Index >= Text.size() )
			Index = Text.size() - 1;
	}

	void TextList::ShiftDown()
	{
		Index--;
		if ( Index < 0 )
			Index = 0;
	}

	void TextList::Move( Vector2 shift )
	{
		getCore()->Data.Position += shift;
	}
}
