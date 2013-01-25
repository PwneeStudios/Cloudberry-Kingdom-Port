#include <global_header.h>

#include "Hacks/List.h"

namespace CloudberryKingdom
{

	MenuList::ExpandProxy1::ExpandProxy1( const boost::shared_ptr<MenuList> &ml )
	{
		this->ml = ml;
	}

	void MenuList::ExpandProxy1::Apply( const boost::shared_ptr<MenuItem> &dummy )
	{
		ml->Expand();
	}

	std::vector<std::wstring> MenuList::GetViewables()
	{
		std::wstring tempVector[] = { std::wstring( L"RightArrowOffset" ), std::wstring( L"LeftArrowOffset" ), std::wstring( L"Pos" ), std::wstring( L"SelectedPos" ), std::wstring( L"!MyMenu" ) };
		return VecFromArray( tempVector );
	}

	const bool &MenuList::getExpandOnGo() const
	{
		return _ExpandOnGo;
	}

	void MenuList::setExpandOnGo( const bool &value )
	{
		_ExpandOnGo = value;
		if ( _ExpandOnGo )
			OnClick = boost::static_pointer_cast<Lambda_1<boost::shared_ptr<MenuItem> > >(
				boost::make_shared<ExpandProxy1>(
					boost::static_pointer_cast<MenuList>( shared_from_this() )
				)
			);
		else
			OnClick.reset();
	}

	void MenuList::Expand()
	{
		if ( MyMenuListExpand == 0 || MyMenuListExpand->getCore()->Released )
		{
			MyMenuListExpand = MakeMagic( MenuListExpand, ( this->Control,
				boost::static_pointer_cast<MenuList>( shared_from_this() ) )
			);
			Tools::CurGameData->AddGameObject( MyMenuListExpand );
			MyMenu->Active = false;

			float Width = MyText->GetWorldWidth() / 2;
			if ( MyExpandPos == Vector2() )
				MyMenuListExpand->Pos->RelVal = Pos + PosOffset - MyMenu->FancyPos->AbsVal + Vector2( -Width, 120 );
			else
				MyMenuListExpand->Pos->RelVal = MyExpandPos;
		}
	}

    void MenuList::Release()
    {
        MenuItem::Release();

        MyMenuListExpand = 0;
    }

#if defined(WINDOWS)
	bool MenuList::HitTest( Vector2 pos, Vector2 padding )
	{
		//TotalPadding = padding + Padding + ListPadding;
		TotalPadding = Padding + ListPadding;

		//return base.HitTest(pos, TotalPadding) || LeftArrow.HitTest(pos, TotalPadding) || RightArrow.HitTest(pos, TotalPadding);
		return MenuItem::HitTest( pos, padding ) || ( HoldSelected && ( LeftArrow_Selected->HitTest( pos, TotalPadding ) || RightArrow_Selected->HitTest( pos, TotalPadding ) ) );

		/*
		if (HoldSelected)
		    return base.HitTest(pos, TotalPadding) || LeftArrow.HitTest(pos, TotalPadding) || RightArrow.HitTest(pos, TotalPadding);
		else
		    return base.HitTest(pos, TotalPadding) || LeftArrow_Selected.HitTest(pos, TotalPadding) || RightArrow_Selected.HitTest(pos, TotalPadding);
		 */
	}
#endif

	void MenuList::FadeIn()
	{
		MenuItem::FadeIn();

		LeftArrow->Quad_Renamed.SetColor( Color( 1.f, 1.f, 1.f, 1.f ) );
		RightArrow->Quad_Renamed.SetColor( Color( 1.f, 1.f, 1.f, 1.f ) );
	}

	void MenuList::FadeOut()
	{
		MenuItem::FadeOut();

		LeftArrow->Quad_Renamed.SetColor( Color( 1, 1, 1,.3f ) );
		RightArrow->Quad_Renamed.SetColor( Color( 1, 1, 1,.3f ) );
	}

	MenuList::MenuList() :
		ClickForNextItem( false ),
		DoIndexWrapping( false ),
		DrawArrowsWhenUnselected( false ),
		DelayCount( 0 ),
		ListIndex( 0 ),
		CustomArrow( false ),
		LastIncrDir( 0 ),
		HoldSelected( false ),
		Center( false )
	{
		InitializeInstanceFields();
	}
	boost::shared_ptr<MenuList> MenuList::MenuList_Construct()
	{
		MenuItem::MenuItem_Construct();

		MenuItem::Init( 0, 0 );

		return boost::static_pointer_cast<MenuList>( shared_from_this() );
	}

	void MenuList::InitializeArrows()
	{
		Vector2 Size;

		RightArrow = boost::make_shared<QuadClass>();
		RightArrow->Quad_Renamed.setMyTexture( Menu::DefaultMenuInfo::MenuRightArrow_Texture );
		Size = Menu::DefaultMenuInfo::MenuArrow_Size;
		RightArrow->Base.e1 *= Size.X;
		RightArrow->Base.e2 *= Size.Y;

		LeftArrow = boost::make_shared<QuadClass>();
		LeftArrow->Quad_Renamed.setMyTexture( Menu::DefaultMenuInfo::MenuLeftArrow_Texture );
		Size = Menu::DefaultMenuInfo::MenuArrow_Size;
		LeftArrow->Base.e1 *= Size.X;
		LeftArrow->Base.e2 *= Size.Y;

		RightArrow_Selected = boost::make_shared<QuadClass>();
		RightArrow_Selected->Quad_Renamed.setMyTexture( Menu::DefaultMenuInfo::MenuRightArrow_Selected_Texture );
		Size = Menu::DefaultMenuInfo::MenuArrow_Selected_Size;
		RightArrow_Selected->Base.e1 *= Size.X;
		RightArrow_Selected->Base.e2 *= Size.Y;

		LeftArrow_Selected = boost::make_shared<QuadClass>();
		LeftArrow_Selected->Quad_Renamed.setMyTexture( Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Texture );
		Size = Menu::DefaultMenuInfo::MenuArrow_Selected_Size;
		LeftArrow_Selected->Base.e1 *= Size.X;
		LeftArrow_Selected->Base.e2 *= Size.Y;
	}

	float MenuList::Height()
	{
		return MyText->GetWorldHeight();
	}

	float MenuList::Width()
	{
		return 0;
	}

	void MenuList::AddItem( const boost::shared_ptr<MenuItem> &item, const boost::shared_ptr<Object> &obj )
	{
		MyList.push_back( item );
		ObjDict.insert( std::make_pair( item, obj ) );
	}

	boost::shared_ptr<MenuItem> MenuList::GetListItem()
	{
		return MyList[ ListIndex ];
	}

	const boost::shared_ptr<Object> &MenuList::getCurObj()
	{
		return ObjDict[ CurMenuItem ];
	}

	const bool MenuList::getOnFirstIndex() const
	{
		return ListIndex == 0 && !DoIndexWrapping;
	}

	const bool MenuList::getOnLastIndex() const
	{
		return ListIndex == MyList.size() - 1 && !DoIndexWrapping;
	}

	bool MenuList::ValidIndex( int index )
	{
		return MyList[ index ]->Selectable;
	}

	void MenuList::SetSelectedItem( const boost::shared_ptr<MenuItem> &item )
	{
		SetIndex( IndexOf( MyList, item ) );
	}

	void MenuList::SetIndex( int NewIndex )
	{
		if ( DoIndexWrapping )
		{
			if ( NewIndex < 0 )
				NewIndex = MyList.size() - 1;
			if ( NewIndex >= static_cast<int>( MyList.size() ) )
				NewIndex = 0;
		}
		else
		{
			CoreMath::Restrict( 0, MyList.size() - 1, NewIndex );
		}

		int HoldIndex = ListIndex;
		ListIndex = NewIndex;

		// Check new index is valid
		if ( !ValidIndex( ListIndex ) )
		{
			//if (HoldIndex == ListIndex) return;
			if ( LastIncrDir == 0 )
				return;
			if ( getOnLastIndex() || getOnFirstIndex() )
				ListIndex = HoldIndex;
			else if ( LastIncrDir != 0 )
				SetIndex( LastIncrDir + ListIndex );
			return;
		}
		LastIncrDir = 0;

		CurMenuItem = MyList[ ListIndex ];
		CurMenuItem->MyOscillateParams.Reset();

		MyText = CurMenuItem->MyText;
		MySelectedText = CurMenuItem->MySelectedText;

		if ( OnIndexSelect != 0 )
			OnIndexSelect->Apply();

		if ( MyMenuListExpand == 0 && OnConfirmedIndexSelect != 0 )
			OnConfirmedIndexSelect->Apply();

		CurMenuItem->OnSelect();
	}

	void MenuList::IncrementIndex( int Increment )
	{
		if ( Increment > 0 )
		{
			LastIncrDir = 1;
			ListIndex++;
		}
		else
		{
			LastIncrDir = -1;
			ListIndex--;
		}

		SetIndex( ListIndex );

		DelayCount = SelectDelay;
	}

#if defined(WINDOWS)
	boost::shared_ptr<QuadClass> MenuList::GetSelectedArrow()
	{
		if ( !HoldSelected )
			return 0;

		Vector2 MousePos = Tools::MouseGUIPos( getMyCameraZoom() );

		float Center = ( RightArrow_Selected->getTR().X + LeftArrow_Selected->getBL().X ) / 2;
		if ( RightArrow_Selected->HitTest( MousePos, TotalPadding ) )
		//if (MousePos.X > RightArrow_Selected.BL.X - 200)
			return RightArrow_Selected;
		if ( LeftArrow_Selected->HitTest( MousePos, TotalPadding ) )
		//else if (MousePos.X < LeftArrow_Selected.TR.X + 200)
			return LeftArrow_Selected;
		else
			return 0;
	}
#endif

	void MenuList::PhsxStep( bool Selected )
	{
		MenuItem::PhsxStep( Selected );

        if (MyMenuListExpand != 0 && MyMenuListExpand->getCore()->Released)
            MyMenuListExpand.reset();

		HoldSelected = Selected;
		int CurIndex = ListIndex;

		Vector2 Dir = Vector2();
		if ( Selected )
		{
			Dir = Vector2();
			if ( Control < 0 )
				Dir = ButtonCheck::GetMaxDir( Control );
			else
				Dir = ButtonCheck::GetDir( Control );
		}

		if ( DelayCount > 0 )
		{
			DelayCount--;

			float Sensitivity = ButtonCheck::ThresholdSensitivity;
			if ( fabs( Dir.X ) < Sensitivity / 2 )
				DelayCount -= 3;
		}
		else
		{
			if ( Selected )
			{
	#if defined(WINDOWS)
				if ( ButtonCheck::MouseInUse && ClickForNextItem )
					if ( ButtonCheck::State( ControllerButtons_A, Control ).Pressed && !ButtonCheck::KeyboardGo() )
					{
						boost::shared_ptr<QuadClass> SelectedArrow = GetSelectedArrow();
						if ( SelectedArrow == RightArrow_Selected )
							IncrementIndex( 1 );
						else if ( SelectedArrow == LeftArrow_Selected )
							IncrementIndex( -1 );
						else
							IncrementIndex( 1 );
					}
	#endif

				float Sensitivity = ButtonCheck::ThresholdSensitivity;
				if ( fabs( Dir.X ) > Sensitivity )
				{
					IncrementIndex( ::Sign( Dir.X ) );
				}
			}
		}

		if ( CurIndex != ListIndex )
			if ( ListScrollSound != 0 )
				ListScrollSound->Play();
	}

	void MenuList::Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected )
	{
		if ( MyMenu->CurDrawLayer != MyDrawLayer || !Show || ( MyMenuListExpand != 0 && !MyMenuListExpand->getCore()->Released ) )
			return;

		MenuItem::Draw( false, cam, Selected );

		// The unselected text of the current menu item may not ever have been drawn,
		// so update its CameraZoom manually
		CurMenuItem->MyText->setMyCameraZoom( getMyCameraZoom() );

		float Width = MyText->GetWorldWidth() / 2;
		Vector2 ItemPos = Pos + PosOffset;
		if ( Center )
			ItemPos.X -= Width;
		CurMenuItem->PosOffset = ItemPos;

		CurMenuItem->MyMenu = MyMenu;
		if ( !Selectable && GrayOutOnUnselectable )
			CurMenuItem->DoGrayOut();
		CurMenuItem->Draw( Text, cam, Selected );
		if ( !Selectable && GrayOutOnUnselectable )
			CurMenuItem->DoDeGrayOut();
		if ( MyMenuListExpand == 0 )
			CurMenuItem->MyMenu.reset();
		else
			CurMenuItem->MyMenu = MyMenuListExpand->MyMenu;


		if ( !Text )
		{
			if ( !Selected )
			{
				if ( !CustomArrow )
				{
					RightArrow->Base.Origin = ItemPos + Vector2( 2*Width + RightArrow->Base.e1.X, 0 ) + Menu::DefaultMenuInfo::MenuRightArrow_Offset + cam->Data.Position;
					LeftArrow->Base.Origin = ItemPos - Vector2( LeftArrow->Base.e1.X, 0 ) + Menu::DefaultMenuInfo::MenuLeftArrow_Offset + cam->Data.Position;
				}
				else
				{
					RightArrow->Base.Origin = ItemPos + Vector2( 2*Width + RightArrow->Base.e1.X, 0 ) + RightArrowOffset + cam->Data.Position;
					LeftArrow->Base.Origin = ItemPos - Vector2( LeftArrow->Base.e1.X, 0 ) + LeftArrowOffset + cam->Data.Position;
				}

				if ( DrawArrowsWhenUnselected )
				{
					if ( !getOnLastIndex() )
						RightArrow->Draw();
					if ( !getOnFirstIndex() )
						LeftArrow->Draw();
				}
			}
			else
			{
				if ( !CustomArrow )
				{
					RightArrow_Selected->Base.Origin = ItemPos + Vector2( 2 * Width + RightArrow_Selected->Base.e1.X, 0 ) + Menu::DefaultMenuInfo::MenuRightArrow_Selected_Offset;
					LeftArrow_Selected->Base.Origin = ItemPos - Vector2( LeftArrow_Selected->Base.e1.X, 0 ) + Menu::DefaultMenuInfo::MenuLeftArrow_Selected_Offset;
				}
				else
				{
					RightArrow_Selected->Base.Origin = ItemPos + Vector2( 2*Width + RightArrow_Selected->Base.e1.X, 0 ) + RightArrowOffset;
					LeftArrow_Selected->Base.Origin = ItemPos - Vector2( LeftArrow_Selected->Base.e1.X, 0 ) + LeftArrowOffset;
				}

	#if defined(WINDOWS)
				// Highlight selected arrow
				boost::shared_ptr<QuadClass> arrow = 0;
				if ( ButtonCheck::MouseInUse )
				{
					Vector2 mouse = Tools::MouseGUIPos( getMyCameraZoom() );
					arrow = GetSelectedArrow();

					if ( arrow != 0 )
					{
						arrow->Scale( 1.25f );
					}
				}
	#endif

				if ( !getOnLastIndex() )
					RightArrow_Selected->Draw();
				if ( !getOnFirstIndex() )
					LeftArrow_Selected->Draw();

	#if defined(PC_VERSION)
				if ( arrow != 0 )
				{
					arrow->Scale( 1.f / 1.25f );
				}
	#endif
			}
		}
	}

	void MenuList::InitializeInstanceFields()
	{
		_ExpandOnGo = false;
		MyExpandPos = Vector2();
		DrawArrowsWhenUnselected = false;
#if defined(WINDOWS)
		ListPadding = Vector2( 65, 0 );
		TotalPadding = Vector2();
#endif
		ObjDict = std::map<boost::shared_ptr<MenuItem>, boost::shared_ptr<Object> >();
		DoIndexWrapping = true;
		LastIncrDir = 0;
		ClickForNextItem = true;
		Center = true;
	}
}
