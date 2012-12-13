#ifndef SOUNDMENU
#define SOUNDMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SoundMenu : public VerifyBaseMenu
	{
	
		struct InitOnToggleHelper : public Lambda_1<bool>
		{
		
			void Apply( const bool &state );
		};

	
		struct InitHideHelper : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SoundMenu> sm;

		
			InitHideHelper( const std::shared_ptr<SoundMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	
		struct InitCallCustomControlsHelper : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SoundMenu> sm;

		
			InitCallCustomControlsHelper( const std::shared_ptr<SoundMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &menuitem );
		};

	
		struct InitOnConfirmedIndexSelect : public Lambda
		{
		
			std::shared_ptr<MenuList> FsRezList;

		
			InitOnConfirmedIndexSelect( const std::shared_ptr<MenuList> &FsRezList );

			void Apply();
		};
	
		struct Toggle_BorderlessProxy : public Lambda_1<bool>
		{
		
			std::shared_ptr<SoundMenu> sm;

		
			Toggle_BorderlessProxy( const std::shared_ptr<SoundMenu> &sm );

			void Apply( const bool &state );
		};

	
		SoundMenu( int Control );
		void SoundMenu_Construct( int Control );

#if defined(PC_VERSION)
#endif

	
		std::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

#if defined(PC_VERSION)
		//private void AddToggle_FixedTimestep()
		//{
		//    // Header
		//    var Text = new EzText(Localization.Words.FixedTimeStep, ItemFont);
		//    SetHeaderProperties(Text);
		//    MyPile.Add(Text);
		//    Text.Pos = new Vector2(-1232.142f, -499.9359f);
		//    Text.Scale *= .9f;

		//    // Menu item
		//    var Toggle = new MenuToggle(ItemFont);
		//    Toggle.OnToggle = Toggle_FixedTimestep;

		//    Toggle.Toggle(Tools.FixedTimeStep);
		//    Toggle.PrefixText = "";
		//    AddItem(Toggle);
		//    Toggle.SetPos = new Vector2(1315.078f, -451.4125f);
		//}

		//private void Toggle_FixedTimestep(bool state)
		//{
		//    PlayerManager.SavePlayerData.ResolutionPreferenceSet = true;
		//    Tools.FixedTimeStep = state;
		//    SaveGroup.SaveAll();
		//    PlayerManager.SaveRezAndKeys();
		//}

	
		void AddToggle_Borderless();

		void Toggle_Borderless( bool state );
#endif

	
		virtual bool MenuReturnToCaller( const std::shared_ptr<Menu> &menu );

	
		void SetPosition();

	
		virtual void OnAdd();
	};
}


#endif	//#ifndef SOUNDMENU
