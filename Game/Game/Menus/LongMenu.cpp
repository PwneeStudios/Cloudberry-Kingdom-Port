#include <global_header.h>

namespace CloudberryKingdom
{

	LongMenu::LongMenu()
	{
		InitializeInstanceFields();
		Init();
	}

	void LongMenu::SelectItem( int Index )
	{
		Menu::SelectItem( Index );
	}

	void LongMenu::PhsxStep()
	{
		Menu::PhsxStep();

		if ( SkipPhsx )
		{
			SkipPhsx = false;
			return;
		}

	#if defined(PC_VERSION)
		if ( !ButtonCheck::MouseInUse )
			Scroll();
	#else
		Scroll();
	#endif
	}

	float LongMenu::Height()
	{
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
			( *item )->UpdatePos();

		int HoldIndex = CurIndex;
		Vector2 HoldPos = FancyPos->RelVal;

		CurIndex = Items.size() - 1;
		SuperScroll();

		float height = FancyPos->RelVal.Y;

		CurIndex = HoldIndex;
		FancyPos->RelVal = HoldPos;

		return height;
	}

	void LongMenu::SuperScroll()
	{
		for ( int i = 0; i < 120 + 120; i++ )
			Scroll();
	}

	void LongMenu::FastScroll()
	{
		for ( int i = 0; i < 5; i++ )
			Scroll();
	}

	void LongMenu::Scroll()
	{
		//// Lock unaffected
		//foreach (MenuItem item in Items)
		//    if (item.UnaffectedByScroll)
		//        item.Selectable = false;

		//if (Items[CurIndex].UnaffectedByScroll) return;
		boost::shared_ptr<MenuItem> LastItem = Items[ 0 ];
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = Items.begin(); item != Items.end(); ++item )
			if ( !( *item )->UnaffectedByScroll && ( *item )->Selectable )
				LastItem = *item;
		//LastItem = Items[Items.Count - 1];


		// Scroll menu as needed
		float min = __min( Items[CurIndex]->MyText->getPos().Y, CurIndex > 0 ? Items[CurIndex - 1]->MyText->getPos().Y : 100000 );
		if ( min < Tools::CurLevel->getMainCamera()->getPos().Y + 300 )
		{
			FancyPos->setRelValY( FancyPos->getRelValY() + OffsetStep );
			if ( LastItem->Pos.Y + FancyPos->RelVal.Y > -Tools::getCurCamera()->GetHeight() / 2 + MaxBottomSpace )
				FancyPos->setRelValY( -LastItem->Pos.Y - Tools::getCurCamera()->GetHeight() / 2 + MaxBottomSpace );
		}
		if ( min > Tools::CurLevel->getMainCamera()->getPos().Y - 300 )
			FancyPos->setRelValY( FancyPos->getRelValY() - OffsetStep );

		if ( FancyPos->RelVal.Y < 0 )
			FancyPos->setRelValY( 0 );

		//// Unlock unaffected
		//foreach (MenuItem item in Items)
		//    if (item.UnaffectedByScroll)
		//        item.Selectable = true;
	}

	void LongMenu::InitializeInstanceFields()
	{
		Offset = 0;
		OffsetStep = 50;
		MaxBottomSpace = 500;
	}
}
