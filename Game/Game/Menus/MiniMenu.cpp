#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	const int &MiniMenu::getBottomItem() const
	{
		return TopItem + ItemsToShow - 1;
	}

	void MiniMenu::setBottomItem( const int &value )
	{
		TopItem = value + 1 - ItemsToShow;
		if ( TopItem < 0 )
			TopItem = 0;
	}

	MiniMenu::MiniMenu()
	{
		InitializeInstanceFields();
		Init();
	}

	void MiniMenu::SelectItem( int Index )
	{
		Menu::SelectItem( Index );
	}

	void MiniMenu::PhsxStep()
	{
		Menu::PhsxStep();

		if ( SkipPhsx )
		{
			SkipPhsx = false;
			return;
		}
	}

	void MiniMenu::DrawText( int Layer )
	{
		setMyCameraZoom( Tools::getCurCamera()->getZoom() );
		if ( !Show )
			return;

		CurDrawLayer = Layer;

		// Update index bounds
		if ( CurIndex < TopItem )
			TopItem = CurIndex;
		if ( CurIndex > getBottomItem() )
			setBottomItem( CurIndex );

		// Draw item text
		for ( int i = TopItem; i <= getBottomItem(); i++ )
		{
			if ( i >= Items.size() )
				break;

			std::shared_ptr<MenuItem> item = Items[ i ];

			item->setSetPos( Vector2::Zero );
			item->PosOffset = getPos() + Shift * (i - TopItem);

			item->Draw( true, Tools::CurLevel->getMainCamera(), DrawItemAsSelected(item) );
		}
	}

	void MiniMenu::InitializeInstanceFields()
	{
		ItemsToShow = 5;
		TopItem = 0;
		Shift = Vector2( 0, -80 );
	}
}
