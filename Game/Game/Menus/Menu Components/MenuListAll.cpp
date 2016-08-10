#include <small_header.h>
#include "Game/Menus/Menu Components/MenuListAll.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Input/ButtonCheck.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Menu Components/MenuList.h"
#include "Game/Tools/Camera.h"

#include "Game/Menus/Menu.h"
#include "Core/Text/EzText.h"
#include "Game/Objects/Icon.h"

namespace CloudberryKingdom
{

	Brackets::Brackets()
	{
		float Size = 50;
		Br1 = boost::make_shared<QuadClass>( std::wstring( L"Edge2" ), Size, true );
		Br2 = boost::make_shared<QuadClass>( std::wstring( L"Edge2" ), Size, true );

		//float Size = 53;
		//Br1 = new QuadClass("Edge", Size, true);
		//Br2 = new QuadClass("Edge", Size, true);
	}

	void Brackets::Draw( Vector2 Center )
	{
		Br1->setDegrees( 0 );
		Br2->setDegrees( 180 );

		Br1->setPos( Vector2( -100, 120 ) + Center );
		Br2->setPos( Vector2( 100, -120 ) + Center );

		Br1->Draw();
		Br2->Draw();
	}

	void Brackets::AddToDrawPile( const boost::shared_ptr<DrawPile> &pile )
	{
		pile->Add( Br1 );
		pile->Add( Br2 );
	}

#if defined(WINDOWS)
	bool MenuListAll::HitTest( Vector2 pos, Vector2 padding )
	{
		TotalPadding = Padding + ListPadding;

		bool hit = false;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyList.begin(); item != MyList.end(); ++item )
		{
			if ( ( *item )->HitTest( pos, padding ) )
			{
				hit = true;
				LastHitItem = *item;
			}
		}

		return hit;
	}
#endif

	MenuListAll::MenuListAll()
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<MenuListAll> MenuListAll::MenuListAll_Construct()
	{
		MenuList::MenuList_Construct();

		setExpandOnGo( false );
		ClickForNextItem = false;

		return boost::static_pointer_cast<MenuListAll>( shared_from_this() );
	}

	void MenuListAll::PhsxStep( bool Selected )
	{
	#if defined(WINDOWS)
		if ( !ButtonCheck::MouseInUse )
		{
			if ( SelectedItem != 0 && CurMenuItem != SelectedItem )
				SetSelectedItem( SelectedItem );
		}
	#endif

		MenuList::PhsxStep( Selected );

	#if defined(WINDOWS)
		if ( ButtonCheck::MouseInUse )
		{
			if ( ButtonCheck::State( ControllerButtons_A, Control ).Pressed && !ButtonCheck::KeyboardGo() )
				SelectedItem = LastHitItem;

			if ( LastHitItem != 0 && CurMenuItem != LastHitItem )
				SetSelectedItem( LastHitItem );
		}
	#endif
	}

	void MenuListAll::SetIndex( int NewIndex )
	{
		MenuList::SetIndex( NewIndex );

	#if defined(WINDOWS)
		LastHitItem = CurMenuItem;

		if ( !ButtonCheck::MouseInUse )
			SelectedItem = CurMenuItem;
	#else
		SelectedItem = CurMenuItem;
	#endif
	}

	void MenuListAll::Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected )
	{
		if ( MyMenu->CurDrawLayer != MyDrawLayer || !Show )
			return;

		float Shift = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<MenuItem> >::const_iterator item = MyList.begin(); item != MyList.end(); ++item )
		{
			// The unselected text of the current menu item may not ever have been drawn,
			// so update its CameraZoom manually
			( *item )->MyText->setMyCameraZoom( getMyCameraZoom() );

			( *item )->Icon->FancyPos->RelVal.X = Shift;

			( *item )->MyMenu = MyMenu;

			//var icon = item.Icon as PictureIcon;
			//if (null != icon)
			//{
			//    if (item == CurMenuItem)
			//        icon.IconQuad.Quad.SetColor(Color.White);
			//    else
			//        icon.IconQuad.Quad.SetColor(ColorHelper.GrayColor(.8f));
			//}

			( *item )->Draw( Text, cam, Selected && ( *item ).get() == CurMenuItem.get() );

			Shift += ShiftAmount;
		}

		if ( SelectedItem == 0 )
			SelectedItem = CurMenuItem;
		Vector2 pos = SelectedItem->Icon->FancyPos->Update();
		MyBrackets->Draw( pos );

		if ( DrawBase( Text, cam, Selected ) )
			return;
	}

	void MenuListAll::InitializeInstanceFields()
	{
#if defined(WINDOWS)
		ListPadding = Vector2( 65, 0 );
		TotalPadding = Vector2();
#endif
		MyBrackets = boost::make_shared<Brackets>();
		ShiftAmount = 250;
	}
}
