#ifndef SAVESEEDAS
#define SAVESEEDAS

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyBase.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/AlertBase.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/SavedSeedsGUI.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_TextBox.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct SaveSeedAs : public VerifyBaseMenu
	{

		virtual ~SaveSeedAs()
		{
#ifdef BOOST_BIN
			OnDestructor( "SaveSeedAs" );
#endif
		}

	
		struct SaveProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;

		
			SaveProxy( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		struct OnOkProxy : public Lambda
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;

		
			OnOkProxy( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	
		struct SaveSeedAsOnEscapeLambda : public Lambda
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;
		
			SaveSeedAsOnEscapeLambda( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	
		struct SaveSeedAsOnEnterLambda : public Lambda
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;
		
			SaveSeedAsOnEnterLambda( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};
	
		SaveSeedAs( int Control, const boost::shared_ptr<PlayerData> &Player );
		boost::shared_ptr<SaveSeedAs> SaveSeedAs_Construct( int Control, const boost::shared_ptr<PlayerData> &Player );

	
		boost::shared_ptr<PlayerData> Player;
		boost::shared_ptr<GUI_TextBox> TextBox;
		boost::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

	
		void Save( const boost::shared_ptr<MenuItem> &_item );

	
		virtual void OnReturnTo();

	
		void OnOk();

	
		virtual void Release();

	
		void SetPosition();

	
		virtual void OnAdd();

	};
}


#endif	//#ifndef SAVESEEDAS
