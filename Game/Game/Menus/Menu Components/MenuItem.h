#ifndef MENUITEM
#define MENUITEM

#include <global_header.h>

namespace CloudberryKingdom
{

	struct MenuItem : public boost::enable_shared_from_this<MenuItem>
	{
	
		virtual ~MenuItem()
		{
#ifdef BOOST_BIN
			OnDestructor( "MenuItem" );
#endif
		}


		static void InitializeStatics();
	
		int Code;
		std::wstring Name;

		bool UnaffectedByScroll;

		/// <summary>
		/// An associated object to store extra info.
		/// </summary>
		boost::shared_ptr<Object> MyObject;
		int MyInt;

		boost::shared_ptr<MenuItem> Clone();

		Vector2 PosOffset, SelectIconOffset;

		boost::shared_ptr<EzSound> SelectSound, SlideSound, ListScrollSound;

		boost::shared_ptr<Menu> MyMenu;

		boost::shared_ptr<FancyVector2> FancyPos;
		Vector2 Pos, SelectedPos;
		bool CustomSelectedPos;

		void SetSelectedPos( Vector2 selectedpos );

		const Vector2 &getSetPos() const;
		void setSetPos( const Vector2 &value );

		/// <summary>
		/// Whether the item oscillates when selected.
		/// </summary>
		bool SelectionOscillate;

		bool AlwaysDrawAsSelected;
		OscillateParams MyOscillateParams;

		void Shift( Vector2 shift );

		/// <summary>
		/// If true collision detection is performed against the item's icon
		/// </summary>
		bool ColWithIcon;

		boost::shared_ptr<ObjectIcon> Icon;
		void SetIcon( const boost::shared_ptr<ObjectIcon> &Icon );

		void SubstituteText( Localization::Words text );

		void SubstituteText( const std::wstring &text );

		int TextWidth;
		boost::shared_ptr<EzText> MyText, MySelectedText;

		boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > OnClick;

	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > _Go;
	
		void setGo( const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &value );
		const boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > &getGo() const;

		boost::shared_ptr<Lambda> AdditionalOnSelect;

		int Control;

		bool Selectable, FadedOut;
	
		bool Selected;

		/// <summary>
		/// The previous value of Selected
		/// </summary>
	
		bool PrevSelected;

		bool _OverrideA;
	
		const bool &getOverrideA() const;
		void setOverrideA( const bool &value );

		Vector4 MySelectedColor, MyColor;
		boost::shared_ptr<EzFont> MySelectedFont, MyFont;

		const std::wstring getMyString() const;

		int MyDrawLayer;

		//public bool FixedToCamera;

		virtual void Release();

		void SetFade( bool Fade );

		virtual void FadeOut();

		virtual void FadeIn();

		MenuItem();
		boost::shared_ptr<MenuItem> MenuItem_Construct();
	
		void SetToDefaultColors();
	
		virtual Vector2 Size();

		virtual float Height();

		virtual float Width();


		/// <summary>
		/// Initialize a new MenuItem.
		/// </summary>
		MenuItem( const boost::shared_ptr<EzText> &Text );
		MenuItem( const boost::shared_ptr<EzText> &Text, const std::wstring &Name );
		MenuItem( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

		boost::shared_ptr<MenuItem> MenuItem_Construct( const boost::shared_ptr<EzText> &Text );
		boost::shared_ptr<MenuItem> MenuItem_Construct( const boost::shared_ptr<EzText> &Text, const std::wstring &Name );
		boost::shared_ptr<MenuItem> MenuItem_Construct( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

		void ScaleText( float scale );

		/// <summary>
		/// The new style initialization function. User provides the EzText for both selected and unselected.
		/// </summary>
	
		virtual void Init( const boost::shared_ptr<EzText> &Text, const boost::shared_ptr<EzText> &SelectedText );

	
		void setFixedToCamera( const bool &value );
		const bool getFixedToCamera() const;

		void SetTextSelection( bool Selected );

		void UpdatePos();

		void DrawBackdrop( bool Selected );

		/// <summary>
		/// True when the item is on the screen.
		/// </summary>
	
		const bool getOnScreen() const;

	
		void DrawText( const boost::shared_ptr<Camera> &cam, bool Selected );

		bool GrayOutOnUnselectable;
		void GrayOut();

		void DeGrayOut();

		virtual void DoGrayOut();

		virtual void DoDeGrayOut();

		bool Show;

		void setInclude( const bool &value );

		/// <summary>
		/// If true the MenuItem jiggles when it is activated -- when the user presses (A)
		/// </summary>
		bool JiggleOnGo;

		void OnSelect();

	
		Vector2 _MyCameraZoom;
		/// <summary>
		/// The value of the camera zoom the last time this EzText was drawn
		/// </summary>
	
		const Vector2 &getMyCameraZoom() const;
		void setMyCameraZoom( const Vector2 &value );

		void Draw();

		bool DrawBase( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected );

		virtual void Draw( bool Text, const boost::shared_ptr<Camera> &cam, bool Selected );

#if defined(WINDOWS)
		virtual bool HitTest();

		Vector2 Padding; //new Vector2(150, 0);
		virtual bool HitTest( Vector2 pos );

		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

		static int ActivatingPlayer;
		static PlayerIndex ActivatingPlayerIndex();
		static boost::shared_ptr<PlayerData> GetActivatingPlayerData();


		/// <summary>
		/// Called once per frame to perform any behavior.
		/// </summary>
		/// <param name="Selected">Whether this item is selected in the menu.</param>
		virtual void PhsxStep( bool Selected );

		/// <summary>
		/// Jiggle the item. To be called when it is activated
		/// </summary>
		void DoActivationAnimation();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUITEM
