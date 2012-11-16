#ifndef CKBASEMENU
#define CKBASEMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class EzFont;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class GUI_Panel;
}

namespace CloudberryKingdom
{
	class Menu;
}

namespace CloudberryKingdom
{
	class PieceQuad;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class CkBaseMenu : public GUI_Panel
	{
	protected:
		class ReturnToCallerProxy : public Lambda
		{
		private:
			std::shared_ptr<CkBaseMenu> cbm;

		public:
			ReturnToCallerProxy( const std::shared_ptr<CkBaseMenu> &cbm );

			void Apply();
		};

	protected:
		class ReturnToCallerProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<CkBaseMenu> cbm;

		public:
			ReturnToCallerProxy1( const std::shared_ptr<CkBaseMenu> &cbm );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	private:
		class MakeBackButtonHelper : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<CkBaseMenu> bm;

		public:
			MakeBackButtonHelper( const std::shared_ptr<CkBaseMenu> &bm );

			void Apply( const std::shared_ptr<MenuItem> &menuitem );
		};

	private:
		std::shared_ptr<QuadClass> DarkBack;
	protected:
		void MakeDarkBack();

		std::shared_ptr<EzSound> SelectSound, BackSound;

	public:
		Vector2 ItemPos;
	protected:
		Vector2 PosAdd;

		std::shared_ptr<EzFont> ItemFont;
		float FontScale;

		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		/// <summary>
		/// Whether menu items added to the menu are given shadows
		/// </summary>
		bool ItemShadows;

		virtual void SetTextProperties( const std::shared_ptr<EzText> &text );

		void SetSelectedTextProperties( const std::shared_ptr<EzText> &text );

		/// <summary>
		/// Amount a menu item is shifted when selected.
		/// </summary>
		//protected Vector2 SelectedItemShift = new Vector2(-65, 0);
		Vector2 SelectedItemShift;

		virtual void AddItem( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void setSlideLength( const int &value );

		virtual void Init();

		void DefaultDelays();

		void DefaultSlides();

		void Defaults();

		void NoDelays();

		void FastDelays();

		void FastSlides();

		void Fast();

		void CategoryDelays();

		/// <summary>
		/// When true this panel follows the following convention:
		/// When it calls a subpanel, this panel slides out to the left.
		/// When that subpanel returns control to this panel, this panel slides in from the left.
		/// </summary>
	protected:
		bool CallToLeft;
	public:
		virtual void Call( const std::shared_ptr<GUI_Panel> &child, int Delay );

		virtual void OnReturnTo();

		virtual void ReturnToCaller();
		virtual void ReturnToCaller( bool PlaySound );

	private:
		std::shared_ptr<GUI_Panel> _RightPanel, _TopPanel;
	protected:
		void setRightPanel( const std::shared_ptr<GUI_Panel> &value );
		const std::shared_ptr<GUI_Panel> &getRightPanel() const;
		void setTopPanel( const std::shared_ptr<GUI_Panel> &value );
		const std::shared_ptr<GUI_Panel> &getTopPanel() const;

	public:
		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	public:
		PresetPos SlideInFrom;
		virtual void Show();

		virtual void SlideIn( int Frames );

	protected:
		virtual void SlideIn_RightPanel( int Frames );

	public:
		virtual void SlideOut( GUI_Panel::PresetPos Preset, int Frames );

	protected:
		virtual void SlideOut_RightPanel( GUI_Panel::PresetPos Preset, int Frames );

		PresetPos SlideOutTo;
	public:
		virtual void Hide();
		virtual void Hide( PresetPos pos );
		virtual void Hide( PresetPos pos, int frames );

	protected:
		std::shared_ptr<MenuItem> MakeBackButton();
		std::shared_ptr<MenuItem> MakeBackButton( Localization::Words Word );

	public:
		static void MakeBackdrop( const std::shared_ptr<Menu> &menu, Vector2 TR, Vector2 BL );

		static std::shared_ptr<PieceQuad> MenuTemplate;
	protected:
		void MakeBackdrop( Vector2 TR, Vector2 BL );

	public:
		static void SetBackdropProperties( const std::shared_ptr<PieceQuad> &piecequad );

		static int DefaultMenuLayer;

		CkBaseMenu();
		CkBaseMenu( bool CallBaseConstructor );

		virtual void Draw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CKBASEMENU
