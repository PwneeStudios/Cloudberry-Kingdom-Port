#ifndef SOUNDMENU
#define SOUNDMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SoundMenu : public VerifyBaseMenu
	{

		virtual ~SoundMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "SoundMenu" );
#endif
		}


		struct Go_ControlsProxy : public Lambda
		{

			boost::shared_ptr<SoundMenu> sm;

			Go_ControlsProxy( boost::shared_ptr<SoundMenu> sm )
			{
				this->sm = sm;
			}

			void Apply()
			{
				sm->Go_Controls();
			}

		};

		struct Go_CustomControlsProxy : public Lambda
		{

			boost::shared_ptr<SoundMenu> sm;

			Go_CustomControlsProxy( boost::shared_ptr<SoundMenu> sm )
			{
				this->sm = sm;
			}

			void Apply()
			{
				sm->Go_CustomControls();
			}

		};

		struct Go_CreditsProxy : public Lambda
		{

			boost::shared_ptr<SoundMenu> sm;

			Go_CreditsProxy( boost::shared_ptr<SoundMenu> sm )
			{
				this->sm = sm;
			}

			void Apply()
			{
				sm->Go_Credits();
			}

		};

		struct StartFadeProxy : public Lambda
		{

			boost::shared_ptr<SoundMenu> sm;

			StartFadeProxy( boost::shared_ptr<SoundMenu> sm )
			{
				this->sm = sm;
			}

			void Apply()
			{
				sm->StartFade();
			}

		};

		struct StartCreditsProxy : public Lambda
		{

			boost::shared_ptr<SoundMenu> sm;

			StartCreditsProxy( boost::shared_ptr<SoundMenu> sm )
			{
				this->sm = sm;
			}

			void Apply()
			{
				sm->StartCredits();
			}

		};


		struct AfterCreditsProxy : public Lambda
		{

			boost::shared_ptr<SoundMenu> sm;

			AfterCreditsProxy( boost::shared_ptr<SoundMenu> sm )
			{
				this->sm = sm;
			}

			void Apply()
			{
				sm->AfterCredits();
			}

		};

		

		struct InitOnToggleHelper : public Lambda_1<bool>
		{
		
			void Apply( const bool &state );
		};

	
		struct InitHideHelper : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SoundMenu> sm;

		
			InitHideHelper( const boost::shared_ptr<SoundMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		struct InitCallCustomControlsHelper : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SoundMenu> sm;

		
			InitCallCustomControlsHelper( const boost::shared_ptr<SoundMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &menuitem );
		};

	
		struct InitOnConfirmedIndexSelect : public Lambda
		{
		
			boost::shared_ptr<MenuList> FsRezList;

		
			InitOnConfirmedIndexSelect( const boost::shared_ptr<MenuList> &FsRezList );

			void Apply();
		};
	
		struct InitOnConfirmedIndexSelect_Language : public Lambda
		{
		
			boost::shared_ptr<SoundMenu> sm;
			boost::shared_ptr<MenuList> FsLanguageList;

		
			InitOnConfirmedIndexSelect_Language( const boost::shared_ptr<SoundMenu> &sm, const boost::shared_ptr<MenuList> &FsLanguageList );

			void Apply();
		};

		struct Toggle_BorderlessProxy : public Lambda_1<bool>
		{
		
			boost::shared_ptr<SoundMenu> sm;

		
			Toggle_BorderlessProxy( const boost::shared_ptr<SoundMenu> &sm );

			void Apply( const bool &state );
		};

		static bool LanguageOption;

		SoundMenu( int Control, bool LanguageOption );
		boost::shared_ptr<SoundMenu> SoundMenu_Construct( int Control, bool LanguageOption );

		Localization::Language ChosenLanguage;
	
		boost::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

		void Go_CustomControls();

		bool Fade;

		boost::shared_ptr<QuadClass> Black;
		void Go_Controls();
		void Go_Credits();
		void StartFade();
		void StartCredits();
		void AfterCredits();
		void Release();

		void ReturnToCaller();

#if defined(PC_VERSION)
		//private void AddToggle_FixedTimestep()
		//{
		//    // Header
		//    var Text = new EzText(Localization::Words_FixedTimeStep, ItemFont);
		//    SetHeaderProperties(Text);
		//    MyPile.Add(Text);
		//    Text.Pos = new Vector2(-1232.142f, -499.9359f);
		//    Text.Scale *= .9f;

		//    // Menu item
		//    var Toggle = new MenuToggle(ItemFont);
		//    Toggle.OnToggle = Toggle_FixedTimestep;

		//    Toggle.Toggle(Tools::FixedTimeStep);
		//    Toggle.PrefixText = "";
		//    AddItem(Toggle);
		//    Toggle.SetPos = new Vector2(1315.078f, -451.4125f);
		//}

		//private void Toggle_FixedTimestep(bool state)
		//{
		//    PlayerManager::SavePlayerData.ResolutionPreferenceSet = true;
		//    Tools::FixedTimeStep = state;
		//    SaveGroup.SaveAll();
		//    PlayerManager::SaveRezAndKeys();
		//}

		void AddToggle_Borderless();

		void Toggle_Borderless( bool state );
#endif

	
		virtual bool MenuReturnToCaller( const boost::shared_ptr<Menu> &menu );

	
		void SetPosition_PC();
		void SetPosition_Console();

	
		virtual void OnAdd();

		virtual void MyDraw();
	};
}


#endif	//#ifndef SOUNDMENU
