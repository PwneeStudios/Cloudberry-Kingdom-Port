#ifndef CKBASEMENU
#define CKBASEMENU

#include <global_header.h>

#include "Game/Localization.h"
#include "Core/Lambdas/Lambda.h"
#include "Core/Lambdas/Lambda_1.h"

namespace CloudberryKingdom
{

	struct CkBaseMenu : public GUI_Panel
	{

		using GUI_Panel::SlideOut;
		using GUI_Panel::SlideIn;
		using GUI_Panel::Call;

	
		struct ReturnToCallerProxy : public Lambda
		{
		
			boost::shared_ptr<CkBaseMenu> cbm;

		
			ReturnToCallerProxy( const boost::shared_ptr<CkBaseMenu> &cbm );

			void Apply();
		};

	
		struct ReturnToCallerProxy1 : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<CkBaseMenu> cbm;

		
			ReturnToCallerProxy1( const boost::shared_ptr<CkBaseMenu> &cbm );

			void Apply( const boost::shared_ptr<MenuItem> &dummy );
		};

	
		struct MakeBackButtonHelper : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<CkBaseMenu> bm;

		
			MakeBackButtonHelper( const boost::shared_ptr<CkBaseMenu> &bm );

			void Apply( const boost::shared_ptr<MenuItem> &menuitem );
		};

	
		boost::shared_ptr<QuadClass> DarkBack;
	
		void MakeDarkBack();

		boost::shared_ptr<EzSound> SelectSound, BackSound;

	
		Vector2 ItemPos;
	
		Vector2 PosAdd;

		boost::shared_ptr<EzFont> ItemFont;
		float FontScale;

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

		/// <summary>
		/// Whether menu items added to the menu are given shadows
		/// </summary>
		bool ItemShadows;

		virtual void SetTextProperties( const boost::shared_ptr<EzText> &text );

		void SetSelectedTextProperties( const boost::shared_ptr<EzText> &text );

		/// <summary>
		/// Amount a menu item is shifted when selected.
		/// </summary>
		//protected Vector2 SelectedItemShift = new Vector2(-65, 0);
		Vector2 SelectedItemShift;

		virtual void AddItem( const boost::shared_ptr<MenuItem> &item );

	
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
	
		virtual void Call( const boost::shared_ptr<GUI_Panel> &child, int Delay );
		
		bool SkipCallSound;

		virtual void OnReturnTo();

		virtual void ReturnToCaller();
		virtual void ReturnToCaller( bool PlaySound );

	
		boost::shared_ptr<GUI_Panel> _RightPanel, _TopPanel;
	
		void setRightPanel( const boost::shared_ptr<GUI_Panel> &value );
		const boost::shared_ptr<GUI_Panel> &getRightPanel() const;
		void setTopPanel( const boost::shared_ptr<GUI_Panel> &value );
		const boost::shared_ptr<GUI_Panel> &getTopPanel() const;

	
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

	
		boost::shared_ptr<MenuItem> MakeBackButton();
		boost::shared_ptr<MenuItem> MakeBackButton( Localization::Words Word );

	
		static void MakeBackdrop( const boost::shared_ptr<Menu> &menu, Vector2 TR, Vector2 BL );

		static boost::shared_ptr<PieceQuad> MenuTemplate;
	
		void MakeBackdrop( Vector2 TR, Vector2 BL );

	
		static void SetBackdropProperties( const boost::shared_ptr<PieceQuad> &piecequad );

		static int DefaultMenuLayer;

		CkBaseMenu();
		boost::shared_ptr<CkBaseMenu> CkBaseMenu_Construct();
		CkBaseMenu( bool CallBaseConstructor );
		boost::shared_ptr<CkBaseMenu> CkBaseMenu_Construct( bool CallBaseConstructor );

		virtual void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CKBASEMENU
