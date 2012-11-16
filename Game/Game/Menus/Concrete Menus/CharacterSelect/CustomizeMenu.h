#ifndef CUSTOMIZEMENU
#define CUSTOMIZEMENU

#include "../Game/Menus/CkBaseMenu.h"
#include "../Core/Lambdas/Lambda_1.h"
#include "../Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "../Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomUpgrades_GUI.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Game/Localization.h"
#include <string>
#include <vector>
#include <tchar.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class CharacterSelect;
}


using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class CustomizeMenu : public CkBaseMenu
	{
	private:
		class GoProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<CustomizeMenu> cm;

		public:
			GoProxy( const std::shared_ptr<CustomizeMenu> &cm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class CreateColorSelectProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomizeMenu> cm;

		public:
			CreateColorSelectProxy( const std::shared_ptr<CustomizeMenu> &cm );

			void Apply();
		};

	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;

	protected:
		virtual void ReleaseBody();

	public:
		CustomizeMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void Init();

	private:
		void SetPos();

		void Go( const std::shared_ptr<MenuItem> &item );

		//void AddMenuItem(string Text, string Name)
		void AddMenuItem( Localization::Words Word, const std::wstring &Name );

		void MakeItems();

	public:
		virtual void OnAdd();

	protected:
		virtual void MyDraw();

	public:
		void CreateColorSelect();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CUSTOMIZEMENU
