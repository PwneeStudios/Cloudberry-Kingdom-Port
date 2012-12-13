#include <global_header.h>

namespace CloudberryKingdom
{

	void ArrowMenu::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	//ArrowMenu::ArrowMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent, const std::shared_ptr<SimpleMenuBase> &MySimple ) : CkBaseMenu( false )
	ArrowMenu::ArrowMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent, const std::shared_ptr<SimpleMenuBase> &MySimple ) { }
	std::shared_ptr<ArrowMenu> ArrowMenu::ArrowMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent, const std::shared_ptr<SimpleMenuBase> &MySimple )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = Parent;
		this->MySimple = MySimple;

		Constructor();
		MyMenu->AffectsOutsideMouse = false;

		return std::static_pointer_cast<ArrowMenu>( shared_from_this() );
	}

	void ArrowMenu::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );

		MyMenu->MouseOnly = true;

		MyMenu->OnB.reset();
		std::shared_ptr<MenuItem> item;

		// The distance between the two arrows
		float SeparationWidth = 300;

		// Left/Right arros
		Vector2 padding = Vector2( 0, 80 );

		// Left arrow
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( _T( "{pcharmenu_larrow_1,70,?}" ), ItemFont ) );
		item->AlwaysDrawAsSelected = true;
		item->setGo( Cast::ToItem( std::make_shared<SimpleMenuBase::SimpleSelect_LeftProxy>( MySimple ) ) );
		ItemPos = Vector2( -SeparationWidth, 250 );
		AddItem( item );

		// Right arrow
		item = std::make_shared<MenuItem>( std::make_shared<EzText>( _T( "{pcharmenu_rarrow_1,70,?}" ), ItemFont ) );
		item->AlwaysDrawAsSelected = true;
		item->setGo( Cast::ToItem( std::make_shared<SimpleMenuBase::SimpleSelect_RightProxy>( MySimple ) ) );
		ItemPos = Vector2( SeparationWidth, 250 );
		AddItem( item );

		EnsureFancy();

		MyMenu->FancyPos->RelVal = Vector2( -62.5f, -15 + 250 );
		CharacterSelect::Shift( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	void ArrowMenu::MyDraw()
	{
		CkBaseMenu::MyDraw();
	}

	void ArrowMenu::OnAdd()
	{
		CkBaseMenu::OnAdd();

		SlideOut( PresetPos_BOTTOM, 0 );
	}

	void ArrowMenu::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;


	}
}
