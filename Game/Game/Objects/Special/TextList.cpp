#include <global_header.h>

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

	TextList::TextList() :
		Index( 0 ),
		ContinuousIndex( 0 ),
		FadeOut( 0 ),
		Alpha( 0 )
	{
		Text = std::vector<EzText*>();
		SetIndex( 0 );

		Alpha = 1;
	}

	void TextList::SetIndex( int index )
	{
		Index = index;
		ContinuousIndex = static_cast<float>( Index );
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
			if ( i >= 0 && i < static_cast<int>( Text.size() ) )
			{
				Text[ i ]->_Pos = getCore()->Data.Position - (i - ContinuousIndex) * Vector2(0, 100);
				Text[ i ]->MyFloatColor.W = Alpha *.5f * ( 2 - fabs( i - ContinuousIndex ) );
				Text[ i ]->Draw( MyCam, false );
			}
		}
		Tools::Render->EndSpriteBatch();
	}

	void TextList::ShiftUp()
	{
		Index++;
		if ( Index >= static_cast<int>( Text.size() ) )
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
