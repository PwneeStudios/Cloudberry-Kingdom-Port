#ifndef MENU
#define MENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class LambdaFunc_1;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class InstancePlusName;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class FancyVector2;
}

namespace CloudberryKingdom
{
	class PieceQuad;
}

namespace CloudberryKingdom
{
	class LambdaFunc;
}











namespace CloudberryKingdom
{
	class Cast
	{
	private:
		class ToMenuHelper1 : public LambdaFunc_1<Menu*, bool>
		{
		private:
			std::shared_ptr<Lambda_1<MenuItem*> > a;

		public:
			ToMenuHelper1( const std::shared_ptr<Lambda_1<MenuItem*> > &a );

			bool Apply( const std::shared_ptr<Menu> &dummy );
		};

	private:
		class LambdaWrapper : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<Lambda> a;

		public:
			LambdaWrapper( const std::shared_ptr<Lambda> &a );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	private:
		class Lambda_1Wrapper : public Lambda
		{
		private:
			std::shared_ptr<Lambda_1<Menu*> > a;

		public:
			Lambda_1Wrapper( const std::shared_ptr<Lambda_1<Menu*> > &a );

			void Apply();
		};

	private:
		class ToMenuHelper : public LambdaFunc_1<Menu*, bool>
		{
		private:
			std::shared_ptr<Lambda> a;

		public:
			ToMenuHelper( const std::shared_ptr<Lambda> &a );

			bool Apply( const std::shared_ptr<Menu> &dummy );
		};

	public:
		static std::shared_ptr<LambdaFunc_1<Menu*, bool> > ToMenu( const std::shared_ptr<Lambda> &a );

		static std::shared_ptr<LambdaFunc_1<Menu*, bool> > ToMenu( const std::shared_ptr<Lambda_1<MenuItem*> > &a );

		static std::shared_ptr<Lambda_1<MenuItem*> > ToItem( const std::shared_ptr<Lambda> &a );

		static std::shared_ptr<Lambda> ToAction( const std::shared_ptr<Lambda_1<Menu*> > &a );
	};

	class Menu : public ViewReadWrite, public IViewableList
	{
	private:
		class FindItemByNameLambda : public LambdaFunc_1<MenuItem*, bool>
		{
		private:
			std::wstring name;
		public:
			FindItemByNameLambda( const std::wstring &name );

			bool Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class DefaultOnBProxy : public LambdaFunc_1<Menu*, bool>
		{
		public:
			bool Apply( const std::shared_ptr<Menu> &menu );
		};

	public:
		class DefaultMenuInfo
		{
		public:
			static Vector4 SelectedNextColor;
			static Vector4 SelectedBackColor;
			static Vector4 UnselectedNextColor;
			static Vector4 UnselectedBackColor;

			static std::shared_ptr<EzSound> Menu_UpDown_Sound;
			static std::shared_ptr<EzSound> Menu_Select_Sound;
			static std::shared_ptr<EzSound> Menu_Slide_Sound;
			static std::shared_ptr<EzSound> Menu_ListScroll_Sound;
			static std::shared_ptr<EzSound> Menu_Back_Sound;
			static int Menu_Slide_SoundDelay;

			static std::shared_ptr<EzTexture> MenuRightArrow_Texture;
			static std::shared_ptr<EzTexture> MenuLeftArrow_Texture;
			static Vector2 MenuRightArrow_Offset;
			static Vector2 MenuLeftArrow_Offset;
			static Vector2 MenuArrow_Size;
			static Vector4 MenuArrow_Color;

			static std::shared_ptr<EzTexture> MenuRightArrow_Selected_Texture;
			static std::shared_ptr<EzTexture> MenuLeftArrow_Selected_Texture;
			static Vector2 MenuRightArrow_Selected_Offset;
			static Vector2 MenuLeftArrow_Selected_Offset;
			static Vector2 MenuArrow_Selected_Size;
			static Vector4 MenuArrow_Selected_Color;

			static std::shared_ptr<EzTexture> SliderBack_Texture;
			static Vector2 SliderBack_Size;
			static std::shared_ptr<EzTexture> Slider_Texture;
			static Vector2 Slider_StartPos;
			static Vector2 Slider_EndPos;
			static Vector2 Slider_Size;
		};

	public:
		virtual std::vector<std::wstring> GetViewables();

		virtual std::wstring CopyToClipboard( const std::wstring &suffix );

		virtual void ProcessMouseInput( Vector2 shift, bool ShiftDown );

		std::shared_ptr<MenuItem> FindItemByName( const std::wstring &name );

		void GetChildren( std::vector<InstancePlusName*> &ViewableChildren );

		/// <summary>
		/// Layer of the menu, used in DrawPiles
		/// </summary>
		int Layer;

		std::shared_ptr<QuadClass> SelectIcon;

		Vector2 PosOffset;
		std::shared_ptr<FancyVector2> FancyPos;
		const Vector2 &getPos() const;
		void setPos( const Vector2 &value );

		bool FixedToCamera;

		std::shared_ptr<EzSound> UpDownSound, SelectSound, BackSound, SlideSound, ListScrollSound;
		bool ReadyToPlaySound;

		bool SkipPhsx;

		std::shared_ptr<Menu> ParentMenu;

	private:
		int _Control;
	public:
		const int &getControl() const;
		void setControl( const int &value );

		std::vector<MenuItem*> Items;
		int CurIndex;

		const std::shared_ptr<MenuItem> &getCurItem() const;

		int SelectDelay;
	private:
		int DelayCount;
		int MotionCount;

	public:
		std::shared_ptr<PieceQuad> MyPieceQuad, MyPieceQuadTemplate;
		std::shared_ptr<PieceQuad> MyPieceQuad2, MyPieceQuadTemplate2;
		Vector2 BackdropShift;


		/// <summary>
		/// Called when the player presses (B) while the menu is active.
		/// Should return true if the menu phsx step should be ended immediately after executing the delegate.
		/// </summary>
		std::shared_ptr<LambdaFunc_1<Menu*, bool> > OnA, OnB, OnX, OnStart;
		std::shared_ptr<Lambda> OnSelect, OnY;

		Vector2 TR, BL;

		int CurDrawLayer;

		int OnA_AutoTimerLength, OnA_AutoTimerCount;

		bool Released;
		void Release();
		void Release( bool ReleaseParents );

		void ClearList();

		Menu();
		Menu( bool FixedToCamera );

	protected:
		void Init();

	public:
		static bool DefaultOnB( const std::shared_ptr<Menu> &menu );

		bool HasSelectedThisStep;

		/// <summary>
		/// If true the menu will wrap from top to bottom or vis a versa when selecting.
		/// </summary>
		bool WrapSelect;

		void SelectItem( const std::shared_ptr<MenuItem> &item );

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
	private:
		int ActiveTimeStamp;

		/// <summary>
		/// When false all Phsx associated with the menu is paused.
		/// </summary>
	public:
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
		std::shared_ptr<LambdaFunc<bool> > AdditionalCheckForOutsideClick;

	private:
		bool CheckForBackFromOutsideClick();

#if defined(PC_VERSION)
	public:
		bool HitTest();
		bool HitTest( Vector2 HitPadding );
#endif
	private:
		bool outside;
	public:
		virtual void PhsxStep();

		void ArrangeItems( float Spacing, Vector2 Center );



		void SetBoundary();
		void SetBoundary( Vector2 Padding );
		void SetBoundary( Vector2 TR_Padding, Vector2 BL_Padding );

		void CalcBounds();

	private:
		static int SortByHeightMethod( const std::shared_ptr<MenuItem> &item1, const std::shared_ptr<MenuItem> &item2 );

	public:
		void SortByHeight();

		void ResetPieces();

		void DrawNonText( int Layer );

		void DrawNonText2();

		virtual void DrawText( int Layer );

		/// <summary>
		/// Whether an item should be drawn as selected or not.
		/// </summary>
	protected:
		bool DrawItemAsSelected( const std::shared_ptr<MenuItem> &item );

		/// <summary>
		/// The index of the item to be drawn as selected
		/// </summary>
	private:
		const int &getApparentCurIndex() const;

		Vector2 _MyCameraZoom;
		/// <summary>
		/// The value of the camera zoom the last time this menu was drawn
		/// </summary>
	public:
		const Vector2 &getMyCameraZoom() const;
		void setMyCameraZoom( const Vector2 &value );

		//bool _Show = true;
		//public bool Show { get { return _Show; } set { _Show = value; } }
		bool Show;

		virtual void Draw();

		void Add( const std::shared_ptr<MenuItem> &item );
		void Add( const std::shared_ptr<MenuItem> &item, int index );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENU
