#include <small_header.h>
#include "Game/Menus/Concrete Menus/CharacterSelect/Backdrop.h"

#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Menus/CkBaseMenu.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Tools/Tools.h"

#include "Core/Text/EzText.h"

namespace CloudberryKingdom
{

	//CharSelectBackdrop::CharSelectBackdrop() : CkBaseMenu()
	CharSelectBackdrop::CharSelectBackdrop() { }
	boost::shared_ptr<CharSelectBackdrop> CharSelectBackdrop::CharSelectBackdrop_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();
		//Core.DrawLayer += 1;

		return boost::static_pointer_cast<CharSelectBackdrop>( shared_from_this() );
	}

	void CharSelectBackdrop::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( 0 );
	}

	void CharSelectBackdrop::SlideOut( PresetPos Preset, int Frames )
	{
		if ( Frames != 0 )
			Frames = 20;
		CkBaseMenu::SlideOut( PresetPos_RIGHT, Frames );
	}

	void CharSelectBackdrop::SetItemProperties( const boost::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::SetItemProperties( item );

		item->MySelectedText->Shadow = item->MyText->Shadow = false;
	}

	void CharSelectBackdrop::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	void CharSelectBackdrop::Init()
	{
		 CkBaseMenu::Init();

		CallDelay = ReturnToCallerDelay = 0;

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		boost::shared_ptr<QuadClass> Backdrop = boost::make_shared<QuadClass>( std::wstring( L"CharSelect" ), 1778.f );
		MyPile->Add( Backdrop, std::wstring( L"Backdrop" ) );

		//var Backdrop = new QuadClass("CharSelect_Backdrop", 1778);
		//MyPile.Add(Backdrop, "Backdrop");
		//var Frame = new QuadClass("CharSelect_Frame", 1778);
		//MyPile.Add(Frame, "Frame");

		SetPos();
	}

    void CharSelectBackdrop::MyDraw()
    {
        if ( CharacterSelectManager::FakeHide )
            return;

        CkBaseMenu::MyDraw();
    }

	void CharSelectBackdrop::SetPos()
	{
	}
}
