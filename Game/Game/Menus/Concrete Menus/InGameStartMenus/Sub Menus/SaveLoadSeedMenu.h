#ifndef SAVELOADSEEDMENU
#define SAVELOADSEEDMENU

#include <global_header.h>

#include "Hacks/NET/IAsyncResult.h"

namespace CloudberryKingdom
{

	struct SaveLoadSeedMenu : public VerifyBaseMenu
	{
#if defined(WINDOWS)
	
		struct MakeSaveHelper : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<GUI_Panel> panel;
			std::shared_ptr<PlayerData> player;

		
			MakeSaveHelper( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};
#else
	
		struct SaveLoadSeedsMakeSaveLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<PlayerData> player;
		
			SaveLoadSeedsMakeSaveLambda( const std::shared_ptr<PlayerData> &player );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};
#endif

	
		struct LoadProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SaveLoadSeedMenu> slsm;

		
			LoadProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	
		struct CopyProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SaveLoadSeedMenu> slsm;

		
			CopyProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	
		struct LoadStringProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SaveLoadSeedMenu> slsm;

		
			LoadStringProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	
		SaveLoadSeedMenu( int Control, bool CanLoad, bool CanSave );
		std::shared_ptr<SaveLoadSeedMenu> SaveLoadSeedMenu_Construct( int Control, bool CanLoad, bool CanSave );

	
		bool CanLoad, CanSave;

		std::shared_ptr<PlayerData> player;

		std::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

	
		void SetPosition();

#if defined(WINDOWS)
	
		static std::shared_ptr<Lambda_1<std::shared_ptr<MenuItem> > > MakeSave( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );

	
		std::shared_ptr<IAsyncResult> kyar;
		static void Save( const std::shared_ptr<MenuItem> &_item, const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );
#else
	
		static std::shared_ptr<Lambda_1<std::shared_ptr<MenuItem> > > MakeSave( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );

	
		static std::shared_ptr<IAsyncResult> kyar;
		static std::shared_ptr<PlayerData> _player;
		static void Save( const std::shared_ptr<MenuItem> &_item, const std::shared_ptr<PlayerData> &activeplayer );

		static void OnKeyboardComplete( const std::shared_ptr<IAsyncResult> &ar );
#endif

		void Load( const std::shared_ptr<MenuItem> &_item );

#if defined(WINDOWS)

		void Copy( const std::shared_ptr<MenuItem> &_item );
#endif

		void LoadString( const std::shared_ptr<MenuItem> &_item );

	
		virtual void OnAdd();
	};
}


#endif	//#ifndef SAVELOADSEEDMENU
