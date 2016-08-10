#include <small_header.h>
#include "Game/Menus/MiniMenu.h"

#include "Core/Input/ButtonCheck.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Menus/Menu.h"
#include "Game/Tools/Tools.h"

#include "Game/Tools/Camera.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Level/Level.h"

namespace CloudberryKingdom
{

	const int MiniMenu::getBottomItem() const
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
			if ( i >= static_cast<int>( Items.size() ) )
				break;

			boost::shared_ptr<MenuItem> item = Items[ i ];

			item->setSetPos( Vector2() );
			item->PosOffset = getPos() + Shift * static_cast<float>(i - TopItem);

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
