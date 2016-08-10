#ifndef MENU
#define MENU

#include <small_header.h>

//#include "Core/FancyVector2.h"
//#include "Core/Graphics/Draw/Quads/PieceQuad.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Sound/EzSound.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct Cast
	{
	
		struct ToMenuHelper1 : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > a;

		
			ToMenuHelper1( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a );

			bool Apply( const boost::shared_ptr<Menu> &dummy );
		};

	
		struct LambdaWrapper : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<Lambda> a;

		
			LambdaWrapper( const boost::shared_ptr<Lambda> &a );

			void Apply( const boost::shared_ptr<MenuItem> &dummy );
		};

	
		struct Lambda_1Wrapper : public Lambda
		{
		
			boost::shared_ptr<Lambda_1<boost::shared_ptr<Menu> > > a;

		
			Lambda_1Wrapper( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Menu> > > &a );

			void Apply();
		};

		struct Lambda_1Wrapper_MenuItem : public Lambda
		{
		
			boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > a;
		
			Lambda_1Wrapper_MenuItem( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a );

			void Apply();
		};
	
		struct ToMenuHelper : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<Lambda> a;

		
			ToMenuHelper( const boost::shared_ptr<Lambda> &a );

			bool Apply( const boost::shared_ptr<Menu> &dummy );
		};

	
		static boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Menu> , bool> > ToMenu( const boost::shared_ptr<Lambda> &a );

		static boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Menu> , bool> > ToMenu( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a );

		static boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > ToItem( const boost::shared_ptr<Lambda> &a );

		static boost::shared_ptr<Lambda> ToAction( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Menu> > > &a );

		static boost::shared_ptr<Lambda> ToAction( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &a );
	};

	struct Menu : public boost::enable_shared_from_this<Menu>
	{

		virtual ~Menu()
		{
#ifdef BOOST_BIN
			OnDestructor( "Menu" );
#endif
		}

	
		struct FindItemByNameLambda : public LambdaFunc_1<boost::shared_ptr<MenuItem> , bool>
		{
		
			std::wstring name;
		
			FindItemByNameLambda( const std::wstring &name );

			bool Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct DefaultOnBProxy : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			bool Apply( const boost::shared_ptr<Menu> &menu );
		};

	
		struct DefaultMenuInfo
		{
		
			static Vector4 SelectedNextColor;
			static Vector4 SelectedBackColor;
			static Vector4 SelectedXColor;
			static Vector4 SelectedYColor;
			static Vector4 UnselectedNextColor;
			static Vector4 UnselectedBackColor;
			static Vector4 UnselectedXColor;
			static Vector4 UnselectedYColor;

			static void SetNext( boost::shared_ptr<MenuItem> item);
			static void SetBack( boost::shared_ptr<MenuItem> item);
			static void SetX( boost::shared_ptr<MenuItem> item);
			static void SetY( boost::shared_ptr<MenuItem> item);

			static boost::shared_ptr<EzSound> Menu_UpDown_Sound;
			static boost::shared_ptr<EzSound> Menu_Select_Sound;
			static boost::shared_ptr<EzSound> Menu_Slide_Sound;
			static boost::shared_ptr<EzSound> Menu_ListScroll_Sound;
			static boost::shared_ptr<EzSound> Menu_Back_Sound;
			static int Menu_Slide_SoundDelay;

			static boost::shared_ptr<EzTexture> MenuRightArrow_Texture;
			static boost::shared_ptr<EzTexture> MenuLeftArrow_Texture;
			static Vector2 MenuRightArrow_Offset;
			static Vector2 MenuLeftArrow_Offset;
			static Vector2 MenuArrow_Size;
			static Vector4 MenuArrow_Color;

			static boost::shared_ptr<EzTexture> MenuRightArrow_Selected_Texture;
			static boost::shared_ptr<EzTexture> MenuLeftArrow_Selected_Texture;
			static Vector2 MenuRightArrow_Selected_Offset;
			static Vector2 MenuLeftArrow_Selected_Offset;
			static Vector2 MenuArrow_Selected_Size;
			static Vector4 MenuArrow_Selected_Color;

			static boost::shared_ptr<EzTexture> SliderBack_Texture;
			static Vector2 SliderBack_Size;
			static boost::shared_ptr<EzTexture> Slider_Texture;
			static Vector2 Slider_StartPos;
			static Vector2 Slider_EndPos;
			static Vector2 Slider_Size;
		};

	

		boost::shared_ptr<MenuItem> FindItemByName( const std::wstring &name );

		/// <summary>
		/// Layer of the menu, used in DrawPiles
		/// </summary>
		int Layer;

		boost::shared_ptr<QuadClass> SelectIcon;

		Vector2 PosOffset;
		boost::shared_ptr<FancyVector2> FancyPos;
		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );

		bool FixedToCamera;

		boost::shared_ptr<EzSound> UpDownSound, SelectSound, BackSound, SlideSound, ListScrollSound;
		bool ReadyToPlaySound;

		bool SkipPhsx;

		boost::shared_ptr<Menu> ParentMenu;

	
		int _Control;
	
		const int &getControl() const;
		void setControl( const int &value );

		std::vector<boost::shared_ptr<MenuItem> > Items;
		int CurIndex;

		const boost::shared_ptr<MenuItem> getCurItem() const;

		int SelectDelay;
	
		int DelayCount;
		int MotionCount;

	
		boost::shared_ptr<PieceQuad> MyPieceQuad, MyPieceQuadTemplate;
		boost::shared_ptr<PieceQuad> MyPieceQuad2, MyPieceQuadTemplate2;
		Vector2 BackdropShift;


		/// <summary>
		/// Called when the player presses (B) while the menu is active.
		/// Should return true if the menu phsx step should be ended immediately after executing the delegate.
		/// </summary>
		boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<Menu> , bool> > OnA, OnB, OnX, OnStart;
		boost::shared_ptr<Lambda> OnSelect, OnY;

		Vector2 TR, BL;

		int CurDrawLayer;

		int OnA_AutoTimerLength, OnA_AutoTimerCount;

		bool Released;
		void Release();
		void Release( bool ReleaseParents );

		void ClearList();

		Menu();
		Menu( bool FixedToCamera );

	
		void Init();

	
		static bool DefaultOnB( const boost::shared_ptr<Menu> &menu );

		bool HasSelectedThisStep;

		/// <summary>
		/// If true the menu will wrap from top to bottom or vis a versa when selecting.
		/// </summary>
		bool WrapSelect;

		void SelectItem( const boost::shared_ptr<MenuItem> &item );

		virtual void SelectItem( int Index );

		/// <summary>
		/// If true then items can only be interacted with via the mouse,
		/// including both selection and activation of items
		/// </summary>
		bool MouseOnly;

		/// <summary>
		/// If true then while the mouse button is down a new menu item can be selected.
		/// </summary>
		bool SlipSelect;

		/// <summary>
		/// When true the current selected item is not highlighted or treated differently than unselected items.
		/// </summary>
		bool NoneSelected;
		bool AlwaysSelected;

		/// <summary>
		/// When true and no item is currently selected, the last activated item will be selected.
		/// This supplements the behavior of NoneSelected
		/// </summary>
		bool ShowLastActivated;

		/// <summary>
		/// The index of the last item to be activated.
		/// </summary>
		int LastActivatedItem;
	
		int ActiveTimeStamp;

		/// <summary>
		/// When false all Phsx associated with the menu is paused.
		/// </summary>
	
		bool Active;

		/// <summary>
		/// When true the menu's back command can be activated by clicking outside the menu's active area.
		/// </summary>
		//public bool CheckForOutsideClick = true;
		bool CheckForOutsideClick;

		/// <summary>
		/// When true the menu can modify the mouse cursor show the back icon (when outside the menu's box).
		/// </summary>
		bool AffectsOutsideMouse;

		/// <summary>
		/// Add a delegate that should return true if this menu should NOT go back when the user clicks
		/// </summary>
		boost::shared_ptr<LambdaFunc<bool> > AdditionalCheckForOutsideClick;

	
		bool CheckForBackFromOutsideClick();

#if defined(PC_VERSION)
	
		bool HitTest();
		bool HitTest( Vector2 HitPadding );
#endif
	
		bool outside;
	
		virtual void PhsxStep();

		void ArrangeItems( float Spacing, Vector2 Center );

		void SetBoundary();
		void SetBoundary( Vector2 Padding );
		void SetBoundary( Vector2 TR_Padding, Vector2 BL_Padding );

		void CalcBounds();

	
		static int SortByHeightMethod( const boost::shared_ptr<MenuItem> &item1, const boost::shared_ptr<MenuItem> &item2 );

	
		void SortByHeight();

		void ResetPieces();

		void DrawNonText( int Layer );

		void DrawNonText2();

		virtual void DrawText( int Layer );

		/// <summary>
		/// Whether an item should be drawn as selected or not.
		/// </summary>
	
		bool DrawItemAsSelected( const boost::shared_ptr<MenuItem> &item );

		/// <summary>
		/// The index of the item to be drawn as selected
		/// </summary>
	
		const int getApparentCurIndex() const;

		Vector2 _MyCameraZoom;
		/// <summary>
		/// The value of the camera zoom the last time this menu was drawn
		/// </summary>
	
		const Vector2 &getMyCameraZoom() const;
		void setMyCameraZoom( const Vector2 &value );

		//bool _Show = true;
		//public bool Show { get { return _Show; } set { _Show = value; } }
		bool Show;

		virtual void Draw();

		void Add( const boost::shared_ptr<MenuItem> &item );
		void Add( const boost::shared_ptr<MenuItem> &item, int index );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENU
