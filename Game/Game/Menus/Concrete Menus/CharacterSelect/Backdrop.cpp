#include <global_header.h>

namespace CloudberryKingdom
{

	CharSelectBackdrop::CharSelectBackdrop() : CkBaseMenu()
	{
		//Core.DrawLayer += 1;
	}

	void CharSelectBackdrop::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( 0 );
	}

	void CharSelectBackdrop::SlideOut( const PresetPos &Preset, int Frames )
	{
		if ( Frames != 0 )
			Frames = 20;
		CkBaseMenu::SlideOut( PresetPos_RIGHT, Frames );
	}

	void CharSelectBackdrop::SetItemProperties( const std::shared_ptr<MenuItem> &item )
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

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		std::shared_ptr<QuadClass> Backdrop = std::make_shared<QuadClass>( _T( "CharSelect" ), 1778.f );
		MyPile->Add( Backdrop, _T( "Backdrop" ) );

		//var Backdrop = new QuadClass("CharSelect_Backdrop", 1778);
		//MyPile.Add(Backdrop, "Backdrop");
		//var Frame = new QuadClass("CharSelect_Frame", 1778);
		//MyPile.Add(Frame, "Frame");

		SetPos();
	}

	void CharSelectBackdrop::SetPos()
	{
	}
}
