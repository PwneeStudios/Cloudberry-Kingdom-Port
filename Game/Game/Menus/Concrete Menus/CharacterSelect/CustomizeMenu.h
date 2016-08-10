#ifndef CUSTOMIZEMENU
#define CUSTOMIZEMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Player/Buyable.h"
//#include "Game/Player/ClrTextFx.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/ColorSelect.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/Waiting.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Player/ColorScheme.h"
//#include "Game/Player/ColorSchemeManager.h"
//#include "Game/Tools/Resources.h"


namespace CloudberryKingdom
{

	struct CustomizeMenu : public CkBaseMenu
	{

		virtual ~CustomizeMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "CustomizeMenu" );
#endif
		}

	
		struct GoProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<CustomizeMenu> cm;

		
			GoProxy( const boost::shared_ptr<CustomizeMenu> &cm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct CreateColorSelectProxy : public Lambda
		{
		
			boost::shared_ptr<CustomizeMenu> cm;

		
			CreateColorSelectProxy( const boost::shared_ptr<CustomizeMenu> &cm );

			void Apply();
		};

	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;

	
		virtual void ReleaseBody();

	
		CustomizeMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent );
		boost::shared_ptr<CustomizeMenu> CustomizeMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void Init();

	
		void SetPos();

		void Go( const boost::shared_ptr<MenuItem> &item );

		//void AddMenuItem(string Text, string Name)
		void AddMenuItem( Localization::Words Word, const std::wstring &Name );

		void MakeItems();

	
		virtual void OnAdd();

	
		virtual void MyDraw();

	
		void CreateColorSelect();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CUSTOMIZEMENU
