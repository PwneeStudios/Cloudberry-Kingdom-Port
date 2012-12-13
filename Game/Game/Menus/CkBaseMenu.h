#ifndef CKBASEMENU
#define CKBASEMENU

#include <global_header.h>


namespace CloudberryKingdom
{
	struct CkBaseMenu : public GUI_Panel
	{
	
		struct ReturnToCallerProxy : public Lambda
		{
		
			std::shared_ptr<CkBaseMenu> cbm;

		
			ReturnToCallerProxy( const std::shared_ptr<CkBaseMenu> &cbm );

			void Apply();
		};

	
		struct ReturnToCallerProxy1 : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<CkBaseMenu> cbm;

		
			ReturnToCallerProxy1( const std::shared_ptr<CkBaseMenu> &cbm );

			void Apply( const std::shared_ptr<MenuItem> &dummy );
		};

	
		struct MakeBackButtonHelper : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<CkBaseMenu> bm;

		
			MakeBackButtonHelper( const std::shared_ptr<CkBaseMenu> &bm );

			void Apply( const std::shared_ptr<MenuItem> &menuitem );
		};

	
		std::shared_ptr<QuadClass> DarkBack;
	
		void MakeDarkBack();

		std::shared_ptr<EzSound> SelectSound, BackSound;

	
		Vector2 ItemPos;
	
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
	
		bool CallToLeft;
	
		virtual void Call( const std::shared_ptr<GUI_Panel> &child, int Delay );

		virtual void OnReturnTo();

		virtual void ReturnToCaller();
		virtual void ReturnToCaller( bool PlaySound );

	
		std::shared_ptr<GUI_Panel> _RightPanel, _TopPanel;
	
		void setRightPanel( const std::shared_ptr<GUI_Panel> &value );
		const std::shared_ptr<GUI_Panel> &getRightPanel() const;
		void setTopPanel( const std::shared_ptr<GUI_Panel> &value );
		const std::shared_ptr<GUI_Panel> &getTopPanel() const;

	
		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		PresetPos SlideInFrom;
		virtual void Show();

		virtual void SlideIn( int Frames );

	
		virtual void SlideIn_RightPanel( int Frames );

	
		virtual void SlideOut( GUI_Panel::PresetPos Preset, int Frames );

	
		virtual void SlideOut_RightPanel( GUI_Panel::PresetPos Preset, int Frames );

		PresetPos SlideOutTo;
	
		virtual void Hide();
		virtual void Hide( PresetPos pos );
		virtual void Hide( PresetPos pos, int frames );

	
		std::shared_ptr<MenuItem> MakeBackButton();
		std::shared_ptr<MenuItem> MakeBackButton( Localization::Words Word );

	
		static void MakeBackdrop( const std::shared_ptr<Menu> &menu, Vector2 TR, Vector2 BL );

		static std::shared_ptr<PieceQuad> MenuTemplate;
	
		void MakeBackdrop( Vector2 TR, Vector2 BL );

	
		static void SetBackdropProperties( const std::shared_ptr<PieceQuad> &piecequad );

		static int DefaultMenuLayer;

		CkBaseMenu();
		void CkBaseMenu_Construct();
		CkBaseMenu( bool CallBaseConstructor );
		void CkBaseMenu_Construct( bool CallBaseConstructor );

		virtual void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CKBASEMENU
