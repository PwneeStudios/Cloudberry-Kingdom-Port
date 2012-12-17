#ifndef CUSTOMCONTROLS
#define CUSTOMCONTROLS

#include <global_header.h>

namespace CloudberryKingdom
{

#if defined(PC_VERSION)
	struct ControlItem : public MenuItem
	{
	
		boost::shared_ptr<QuadClass> MyQuad;
		Keys MyKey;
		boost::shared_ptr<Lambda_1<Keys> > SetSecondaryKey;
		boost::shared_ptr<Lambda_1<boost::shared_ptr<ControlItem> > > Reset;

		ControlItem( Localization::Words description, Keys key );

		void SetKey( Keys key );

		void SetQuad();
	};

	struct CustomControlsMenu : public CkBaseMenu
	{
	
		struct ResetProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<CustomControlsMenu> ccm;

		
			ResetProxy( const boost::shared_ptr<CustomControlsMenu> &ccm );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		struct KeyQuickspawn_KeyboardKey : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyHelp_KeyboardKey : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyLeft_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyRight_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyUp_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyDown_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyReplayPrev_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyReplayNext_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeyReplayToggle_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct KeySlowMoToggle_Secondary : public Lambda_1<Keys>
		{
		
			void Apply( const Keys &key );
		};

	
		struct ResetQuickspawn_KeyboardKey : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetHelp_KeyboardKey : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetLeft_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetRight_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetUp_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetDown_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetReplayPrev_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetReplayNext_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetReplayToggle_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct ResetSlowMoToggle_Secondary : public Lambda_1<boost::shared_ptr<ControlItem> >
		{
		
			void Apply( const boost::shared_ptr<ControlItem> &_item );
		};

	
		struct InitOnButtonHelper : public LambdaFunc_1<boost::shared_ptr<Menu> , bool>
		{
		
			boost::shared_ptr<CustomControlsMenu> ccm;

		
			InitOnButtonHelper( const boost::shared_ptr<CustomControlsMenu> &ccm );

			bool Apply( const boost::shared_ptr<Menu> &_m );
		};

	
		static Color SecondaryKeyColor;
	
		virtual void ReleaseBody();

	
		void Save();

	
		virtual void SetTextProperties( const boost::shared_ptr<EzText> &text );

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		virtual void AddItem( const boost::shared_ptr<MenuItem> &item );

	
		CustomControlsMenu();
		boost::shared_ptr<CustomControlsMenu> CustomControlsMenu_Construct();

	
		boost::shared_ptr<QuadClass> Backdrop;
	
		virtual void MakeBackdrop();

		void MakeInstructions();

	
		void Reset( const boost::shared_ptr<MenuItem> &_item );

		void MakeBack();



	
		virtual void Init();

	
		void SetPos();

		void ItemSetup();

	
		virtual void MyPhsxStep();
	};
#endif
}


#endif	//#ifndef CUSTOMCONTROLS
