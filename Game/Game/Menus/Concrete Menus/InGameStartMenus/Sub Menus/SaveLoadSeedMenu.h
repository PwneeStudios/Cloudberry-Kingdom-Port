#ifndef SAVELOADSEEDMENU
#define SAVELOADSEEDMENU

#include <global_header.h>

#include "Hacks/NET/IAsyncResult.h"

namespace CloudberryKingdom
{

	struct SaveLoadSeedMenu : public VerifyBaseMenu
	{
#if defined(WINDOWS)
	
		struct MakeSaveHelper : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<GUI_Panel> panel;
			boost::shared_ptr<PlayerData> player;

		
			MakeSaveHelper( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};
#else
	
		struct SaveLoadSeedsMakeSaveLambda : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<PlayerData> player;
		
			SaveLoadSeedsMakeSaveLambda( const boost::shared_ptr<PlayerData> &player );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};
#endif

	
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

#if defined(WINDOWS)
	
		static boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > MakeSave( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player );

	
		boost::shared_ptr<IAsyncResult> kyar;
		static void Save( const boost::shared_ptr<MenuItem> &_item, const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player );
#else
	
		static boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > MakeSave( const boost::shared_ptr<GUI_Panel> &panel, const boost::shared_ptr<PlayerData> &player );

	
		static boost::shared_ptr<IAsyncResult> kyar;
		static boost::shared_ptr<PlayerData> _player;
		static void Save( const boost::shared_ptr<MenuItem> &_item, const boost::shared_ptr<PlayerData> &activeplayer );

		static void OnKeyboardComplete( const boost::shared_ptr<IAsyncResult> &ar );
#endif

		void Load( const boost::shared_ptr<MenuItem> &_item );

#if defined(WINDOWS)

		void Copy( const boost::shared_ptr<MenuItem> &_item );
#endif

		void LoadString( const boost::shared_ptr<MenuItem> &_item );

	
		virtual void OnAdd();
	};
}


#endif	//#ifndef SAVELOADSEEDMENU
