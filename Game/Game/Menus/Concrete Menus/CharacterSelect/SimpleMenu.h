#ifndef SIMPLEMENU
#define SIMPLEMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/ArrowMenu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CustomizeMenu.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/Waiting.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Player/ColorSchemeManager.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct SimpleMenuBase : public CkBaseMenu
	{

		virtual ~SimpleMenuBase()
		{
#ifdef BOOST_BIN
			OnDestructor( "SimpleMenuBase" );
#endif
		}

	
		static void InitializeStatics();

	
		struct SimpleToCustomProxy : public Lambda
		{
		
			boost::shared_ptr<SimpleMenuBase> smb;

		
			SimpleToCustomProxy( const boost::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleToDoneProxy : public Lambda
		{
		
			boost::shared_ptr<SimpleMenuBase> smb;

		
			SimpleToDoneProxy( const boost::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleToBackProxy : public Lambda
		{
		
			boost::shared_ptr<SimpleMenuBase> smb;

		
			SimpleToBackProxy( const boost::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleSelect_RightProxy : public Lambda
		{
		
			boost::shared_ptr<SimpleMenuBase> smb;

		
			SimpleSelect_RightProxy( const boost::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleSelect_LeftProxy : public Lambda
		{
		
			boost::shared_ptr<SimpleMenuBase> smb;

		
			SimpleSelect_LeftProxy( const boost::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		boost::shared_ptr<ArrowMenu> Arrows;

	
		virtual void ReleaseBody();

	
		SimpleMenuBase( int Control, const boost::shared_ptr<CharacterSelect> &Parent );
		boost::shared_ptr<SimpleMenuBase> SimpleMenuBase_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent );

		virtual void OnAdd();

	
		Vector2 PrevDir;
		int NoMoveCount;
		static int NoMoveDuration;

	
		void SimpleToCustom();

		void SimpleToDone();

		void SimpleToBack();

	
		void ButtonPhsx();

		/// <summary>
		/// Select the next premade stickman to the right
		/// </summary>    
	
		void SimpleSelect_Right();

		/// <summary>
		/// Select the next premade stickman to the left
		/// </summary>
		void SimpleSelect_Left();

	
		virtual void MyPhsxStep();
	};

#if defined(PC_VERSION)
	struct SimpleMenu : public SimpleMenuBase
	{
	
		virtual ~SimpleMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "SimpleMenu" );
#endif
		}


		SimpleMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent );
		boost::shared_ptr<SimpleMenu> SimpleMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void Init();

	
		void SetPos();
	};
#else
	struct SimpleMenu : public SimpleMenuBase
	{

		virtual ~SimpleMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "SimpleMenu" );
#endif
		}

	
		SimpleMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent );
		boost::shared_ptr<SimpleMenu> SimpleMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent );

		virtual void Init();

	
		void SetPos();

	
		virtual void MyPhsxStep();
	};
#endif
}


#endif	//#ifndef SIMPLEMENU
