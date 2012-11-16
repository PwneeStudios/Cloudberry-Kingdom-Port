#ifndef SOUNDMENU
#define SOUNDMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class MenuList;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Menu;
}




namespace CloudberryKingdom
{
	class SoundMenu : public VerifyBaseMenu
	{
	private:
		class InitOnToggleHelper : public Lambda_1<bool>
		{
		public:
			void Apply( bool state );
		};

	private:
		class InitHideHelper : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SoundMenu> sm;

		public:
			InitHideHelper( const std::shared_ptr<SoundMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	private:
		class InitCallCustomControlsHelper : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SoundMenu> sm;

		public:
			InitCallCustomControlsHelper( const std::shared_ptr<SoundMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &menuitem );
		};

	private:
		class InitOnConfirmedIndexSelect : public Lambda
		{
		private:
			std::shared_ptr<MenuList> FsRezList;

		public:
			InitOnConfirmedIndexSelect( const std::shared_ptr<MenuList> &FsRezList );

			void Apply();
		};
	private:
		class Toggle_BorderlessProxy : public Lambda_1<bool>
		{
		private:
			std::shared_ptr<SoundMenu> sm;

		public:
			Toggle_BorderlessProxy( const std::shared_ptr<SoundMenu> &sm );

			void Apply( bool state );
		};

	public:
		SoundMenu( int Control );

#if defined(PC_VERSION)
#endif

	private:
		std::shared_ptr<EzText> HeaderText;
	public:
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

	private:
		void AddToggle_Borderless();

		void Toggle_Borderless( bool state );
#endif

	public:
		virtual bool MenuReturnToCaller( const std::shared_ptr<Menu> &menu );

	private:
		void SetPosition();

	public:
		virtual void OnAdd();
	};
}


#endif	//#ifndef SOUNDMENU
