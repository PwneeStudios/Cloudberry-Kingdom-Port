#ifndef SAVELOADSEEDMENU
#define SAVELOADSEEDMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class GUI_Panel;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}




//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{
	class SaveLoadSeedMenu : public VerifyBaseMenu
	{
	private:
		class MakeSaveHelper : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<GUI_Panel> panel;
			std::shared_ptr<PlayerData> player;

		public:
			MakeSaveHelper( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	private:
		class SaveLoadSeedsMakeSaveLambda : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<PlayerData> player;
		public:
			SaveLoadSeedsMakeSaveLambda( const std::shared_ptr<PlayerData> &player );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class LoadProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SaveLoadSeedMenu> slsm;

		public:
			LoadProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	private:
		class CopyProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SaveLoadSeedMenu> slsm;

		public:
			CopyProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	private:
		class LoadStringProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SaveLoadSeedMenu> slsm;

		public:
			LoadStringProxy( const std::shared_ptr<SaveLoadSeedMenu> &slsm );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	public:
		SaveLoadSeedMenu( int Control, bool CanLoad, bool CanSave );

	private:
		bool CanLoad, CanSave;

		std::shared_ptr<PlayerData> player;

		std::shared_ptr<EzText> HeaderText;
	public:
		virtual void Init();

	private:
		void SetPosition();

#if defined(WINDOWS)
	public:
		static std::shared_ptr<Lambda_1<MenuItem*> > MakeSave( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );

	private:
		std::shared_ptr<IAsyncResult> kyar;
		static void Save( const std::shared_ptr<MenuItem> &_item, const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );
#else
	public:
		static std::shared_ptr<Lambda_1<MenuItem*> > MakeSave( const std::shared_ptr<GUI_Panel> &panel, const std::shared_ptr<PlayerData> &player );

	private:
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

	public:
		virtual void OnAdd();
	};
}


#endif	//#ifndef SAVELOADSEEDMENU
