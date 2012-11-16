#include <global_header.h>

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{

	MenuListExpand::OnSelectProxy::OnSelectProxy( const std::shared_ptr<MenuListExpand> &mle )
	{
		this->mle = mle;
	}

	void MenuListExpand::OnSelectProxy::Apply()
	{
		mle->OnSelect();
	}

	MenuListExpand::InitOnBMenuHelper::InitOnBMenuHelper( const std::shared_ptr<MenuListExpand> &mle )
	{
		this->mle = mle;
	}

	bool MenuListExpand::InitOnBMenuHelper::Apply( const std::shared_ptr<Menu> &menu )
	{
		mle->Back();
		return true;
	}

	void MenuListExpand::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyMenuList->MyMenu->Active = true;
		MyMenuList->MyMenu->NoneSelected = true;
		MyMenuList->MyMenu->PhsxStep();
		MyMenuList->MyMenu->PhsxStep();

		if ( MyMenuList->OnConfirmedIndexSelect != 0 )
			MyMenuList->OnConfirmedIndexSelect->Apply();
	}

	MenuListExpand::MenuListExpand( int Control, const std::shared_ptr<MenuList> &MyMenuList ) : CkBaseMenu( false )
	{
		InitializeInstanceFields();
		this->MyMenuList = MyMenuList;
		Constructor();
	}

	void MenuListExpand::SetItemProperties( const std::shared_ptr<MenuItem> &item )
	{
		//base.SetItemProperties(item);

		item->MySelectedText->setScale( FontScale );
	item->MyText->setScale( item->MySelectedText->getScale() );

		item->MySelectedText->MyFloatColor = ( Color( 50, 220, 50 ) ).ToVector4();

		item->getGo().reset();

	#if defined(PC_VERSION)
			item->Padding += Vector2( 0, 35 );
	#endif

			//item.SelectIconOffset = new Vector2(0, -160);
	}

	void MenuListExpand::AddItem( const std::shared_ptr<MenuItem> &item )
	{
		CkBaseMenu::AddItem( item );

	#if defined(PC_VERSION)
		item->Padding.Y -= 37;
	#endif
	}

	void MenuListExpand::OnSelect()
	{
		//MyMenuList.SetIndex(MyMenu.CurIndex);
		MyMenuList->SetIndex( MyMenu->getCurItem()->MyInt );
	}

	void MenuListExpand::Init()
	{
		CkBaseMenu::Init();

		MyPile = std::make_shared<DrawPile>();
		MyPile->FancyPos->UpdateWithGame = true;

		// Make the menu
		MyMenu = std::make_shared<Menu>( false );
		MyMenu->SlipSelect = true;
		MyMenu->Active = false;
		MyMenu->NoneSelected = true;

		setControl( this->getControl() );

		MyMenu->OnB.reset();

		MyMenu->OnB = std::make_shared<InitOnBMenuHelper>( this );

		ItemPos = Vector2( 0, 0 );
		PosAdd = Vector2( 0, -168 - 3 );
		SelectedItemShift = Vector2( 0, 0 );
		FontScale = .78f;

		float Width = 0;
		int index = 0;
		for ( std::vector<MenuItem*>::const_iterator item = MyMenuList->MyList.begin(); item != MyMenuList->MyList.end(); ++item )
		{
			index++;

			if ( !( *item )->Selectable )
				continue;

			std::shared_ptr<MenuItem> clone = ( *item )->Clone();
			clone->MyInt = index - 1;
			clone->AdditionalOnSelect = std::make_shared<OnSelectProxy>( this );
			AddItem( clone );
			clone->ScaleText( .85f );
			Vector2 size = clone->MyText->GetWorldSize();
			//clone.Shift(-size / 2);
			Width = __max( size.X, Width );

			if ( MyMenuList->AdditionalExpandProcessing != 0 )
				MyMenuList->AdditionalExpandProcessing->Apply( this, clone );
		}

		// Backdrop
		backdrop = std::make_shared<QuadClass>( _T( "score_screen_grey" ), 482 );
		//backdrop.Size = backdrop.Size * new Vector2(1f, 2.03f);
		MyMenu->CalcBounds();
		float Height = ( MyMenu->TR.Y - MyMenu->BL.Y ) / 2;
		backdrop->setSize( Vector2( Width / 2 + 88, Height + 70 ) );
		DefaultBackdropSize = backdrop->getSize();
		backdrop->Quad_Renamed->RotateUV();
		MyPile->Add( backdrop );
		MyPile->Add( backdrop );
		backdrop->setPos( Vector2( Width / 2, ( MyMenu->TR.Y + MyMenu->BL.Y ) / 2 ) );

		EnsureFancy();

		MyPile->setPos( Vector2( 0, 0 ) );
		MyMenu->FancyPos->RelVal = Vector2( 0, 0 );
	}

	void MenuListExpand::OnAdd()
	{
		CkBaseMenu::OnAdd();

		SlideIn( 0 );
	}

	void MenuListExpand::Back()
	{
		if ( Active )
		{
			SlideOutLength = 0;
			ReturnToCaller();
		}
	}

	void MenuListExpand::MyDraw()
	{
		CkBaseMenu::MyDraw();
	}

	void MenuListExpand::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
		if ( !Active )
			return;

		Count++;
		if ( Count > 4 )
			MyMenu->Active = true;
		else
		{
			MyMenu->NoneSelected = true;
			MyMenu->Active = false;
		}

	#if defined(PC_VERSION)
		if ( !Tools::CurMouseDown() )
			Back();
	#endif
	}

	void MenuListExpand::InitializeInstanceFields()
	{
		Count = 0;
	}
}
