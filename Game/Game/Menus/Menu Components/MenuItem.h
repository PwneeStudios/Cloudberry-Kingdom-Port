#ifndef MENUITEM
#define MENUITEM

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class FancyVector2;
}

namespace CloudberryKingdom
{
	class ObjectIcon;
}

namespace CloudberryKingdom
{
	class EzText;
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
	class EzFont;
}

namespace CloudberryKingdom
{
	class Camera;
}

namespace CloudberryKingdom
{
	class PlayerData;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;



namespace CloudberryKingdom
{
	//public delegate void MenuItemGo(MenuItem item);
	class MenuItem : public ViewReadWrite
	{
	public:
		int Code;
		std::wstring Name;

		bool UnaffectedByScroll;

		/// <summary>
		/// An associated object to store extra info.
		/// </summary>
		std::shared_ptr<Object> MyObject;
		int MyInt;

		virtual std::vector<std::wstring> GetViewables();

		virtual void ProcessMouseInput( Vector2 shift, bool ShiftDown );

		virtual std::wstring ToCode( const std::wstring &suffix );

		std::shared_ptr<MenuItem> Clone();

		Vector2 PosOffset, SelectIconOffset;

		std::shared_ptr<EzSound> SelectSound, SlideSound, ListScrollSound;

		std::shared_ptr<Menu> MyMenu;

		std::shared_ptr<FancyVector2> FancyPos;
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

		std::shared_ptr<ObjectIcon> Icon;
		void SetIcon( const std::shared_ptr<ObjectIcon> &Icon );

		void SubstituteText( Localization::Words text );

		void SubstituteText( const std::wstring &text );

		int TextWidth;
		std::shared_ptr<EzText> MyText, MySelectedText;

		std::shared_ptr<Lambda_1<MenuItem*> > OnClick;

	private:
		std::shared_ptr<Lambda_1<MenuItem*> > _Go;
	public:
		void setGo( const std::shared_ptr<Lambda_1<MenuItem*> > &value );
		const std::shared_ptr<Lambda_1<MenuItem*> > &getGo() const;

		std::shared_ptr<Lambda> AdditionalOnSelect;

		int Control;

		bool Selectable, FadedOut;
	protected:
		bool Selected;

		/// <summary>
		/// The previous value of Selected
		/// </summary>
	private:
		bool PrevSelected;

		bool _OverrideA;
	public:
		const bool &getOverrideA() const;
		void setOverrideA( const bool &value );

		Vector4 MySelectedColor, MyColor;
		std::shared_ptr<EzFont> MySelectedFont, MyFont;

		const std::wstring &getMyString() const;

		int MyDrawLayer;

		//public bool FixedToCamera;

		virtual void Release();

		void SetFade( bool Fade );

		virtual void FadeOut();

		virtual void FadeIn();

		MenuItem();

	private:
		void SetToDefaultColors();

	public:
		virtual Vector2 Size();

		virtual float Height();

		virtual float Width();


		/// <summary>
		/// Initialize a new MenuItem.
		/// </summary>
		MenuItem( const std::shared_ptr<EzText> &Text );
		MenuItem( const std::shared_ptr<EzText> &Text, const std::wstring &Name );
		MenuItem( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

		void ScaleText( float scale );

		/// <summary>
		/// The new style initialization function. User provides the EzText for both selected and unselected.
		/// </summary>
	protected:
		virtual void Init( const std::shared_ptr<EzText> &Text, const std::shared_ptr<EzText> &SelectedText );

	public:
		void setFixedToCamera( const bool &value );
		const bool &getFixedToCamera() const;

		void SetTextSelection( bool Selected );

		void UpdatePos();

		void DrawBackdrop( bool Selected );

		/// <summary>
		/// True when the item is on the screen.
		/// </summary>
	protected:
		const bool &getOnScreen() const;

	public:
		void DrawText( const std::shared_ptr<Camera> &cam, bool Selected );

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

	private:
		Vector2 _MyCameraZoom;
		/// <summary>
		/// The value of the camera zoom the last time this EzText was drawn
		/// </summary>
	public:
		const Vector2 &getMyCameraZoom() const;
		void setMyCameraZoom( const Vector2 &value );

		void Draw();

		bool DrawBase( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

		virtual void Draw( bool Text, const std::shared_ptr<Camera> &cam, bool Selected );

#if defined(WINDOWS)
		virtual bool HitTest();

		Vector2 Padding; //new Vector2(150, 0);
		virtual bool HitTest( Vector2 pos );

		virtual bool HitTest( Vector2 pos, Vector2 padding );
#endif

		static int ActivatingPlayer;
		static std::shared_ptr<PlayerData> GetActivatingPlayerData();


		/// <summary>
		/// Called once per frame to perform any behavior.
		/// </summary>
		/// <param name="Selected">Whether this item is selected in the menu.</param>
		virtual void PhsxStep( bool Selected );

		/// <summary>
		/// Jiggle the item. To be called when it is activated
		/// </summary>
		void DoActivationAnimation();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MENUITEM
