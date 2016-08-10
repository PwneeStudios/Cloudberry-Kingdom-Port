#ifndef SAVELOADSEEDMENU
#define SAVELOADSEEDMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzText.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Menus/CkBaseMenu.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyBase.h"
//#include "Game/Games/NormalGame.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/LoadSeedAs.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/SaveSeedAs.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/AlertBase.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/SavedSeedsGUI.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Tools/Tools.h"


#include "Hacks/NET/IAsyncResult.h"

namespace CloudberryKingdom
{

	struct SaveLoadSeedMenu : public VerifyBaseMenu
	{

		virtual ~SaveLoadSeedMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "SaveLoadSeedMenu" );
#endif
		}


		struct MakeSaveHelper : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<GUI_Panel> panel;
			boost::shared_ptr<PlayerData> player;

		
			MakeSaveHelper( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};
	
		struct LoadProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SaveLoadSeedMenu> slsm;

		
			LoadProxy( const boost::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		struct CopyProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SaveLoadSeedMenu> slsm;

		
			CopyProxy( const boost::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		struct LoadStringProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SaveLoadSeedMenu> slsm;

		
			LoadStringProxy( const boost::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		SaveLoadSeedMenu( int Control, bool CanLoad, bool CanSave );
		boost::shared_ptr<SaveLoadSeedMenu> SaveLoadSeedMenu_Construct( int Control, bool CanLoad, bool CanSave );

	
		bool CanLoad, CanSave;

		boost::shared_ptr<PlayerData> player;

		boost::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

	
		void SetPosition();

		static boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > MakeSave( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player );
	
		boost::shared_ptr<IAsyncResult> kyar;
		static void Save( const boost::shared_ptr<MenuItem> &_item, const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player );

		void Load( const boost::shared_ptr<MenuItem> &_item );

#ifdef WINDOWS
		void Copy( const boost::shared_ptr<MenuItem> &_item );
#endif

		void LoadString( const boost::shared_ptr<MenuItem> &_item );

	
		virtual void OnAdd();
	};
}


#endif	//#ifndef SAVELOADSEEDMENU
