#ifndef CHARACTERSELECT
#define CHARACTERSELECT

#include <small_header.h>

//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
//#include "Game/Player/Buyable.h"
//#include "Game/Player/ClrTextFx.h"
//#include "Game/Games/GameType.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/Doll.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/GamerTag.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/HeroLevel.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/JoinText.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/Waiting.h"
//#include "Game/Player/PlayerManager.h"
#include "Game/Player/ColorScheme.h"
//#include "Game/Player/ColorSchemeManager.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tools/Unset.h"


namespace CloudberryKingdom
{

	struct CharacterSelect : public boost::enable_shared_from_this<CharacterSelect>
	{

		static void InitializeStatics();

	
		struct RandomizeProxy : public Lambda
		{
		
			boost::shared_ptr<CharacterSelect> cs;

		
			RandomizeProxy( const boost::shared_ptr<CharacterSelect> &cs );

			void Apply();
		};

	
		enum SelectState
		{
			SelectState_BEGINNING,
			SelectState_SELECTING,
			SelectState_WAITING
		};
	
		SelectState MyState;

		bool Join;

		/// <summary>
		/// True if the character select has been brought up mid game
		/// </summary>
		bool QuickJoin;

		boost::shared_ptr<GamerTag> MyGamerTag;
		boost::shared_ptr<HeroLevel> MyHeroLevel;
		boost::shared_ptr<Doll> MyDoll;

		int PlayerIndex;
		const boost::shared_ptr<PlayerData> getPlayer() const;

		std::vector<int> ItemIndex;
		std::vector<std::vector<boost::shared_ptr<MenuListItem> > > ItemList;

	
		Vector2 Center, NormalZoomCenter;

	
		static float Width;
		static std::vector<Vector2> Centers;
		void InitCenters();

		static void Shift( const boost::shared_ptr<GUI_Panel> &panel );

		void Release();

		bool Fake;
		CharacterSelect( int PlayerIndex, bool QuickJoin );

		void InitColorScheme( int PlayerIndex );

		void Randomize();

	
		int HoldCapeIndex, HoldCapeOutlineIndex;
	
		void Customize_UpdateColors();

		bool HasCustom();

		bool AvailableColorScheme( ColorScheme scheme );

		void SetIndex( int i );

	
		int FindIndex( std::vector<boost::shared_ptr<MenuListItem> > &list, ClrTextFx obj );

		/// <summary>
		/// Find the indices that would reproduce the current color scheme.
		/// </summary>
		void CopyIndicesFromColorScheme();

	
		void PhsxStep();

		void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CHARACTERSELECT
