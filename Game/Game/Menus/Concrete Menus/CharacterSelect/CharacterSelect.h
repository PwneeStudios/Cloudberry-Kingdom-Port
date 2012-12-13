#ifndef CHARACTERSELECT
#define CHARACTERSELECT

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CharacterSelect : public std::enable_shared_from_this<CharacterSelect>
	{

		static void InitializeStatics();

	
		struct RandomizeProxy : public Lambda
		{
		
			std::shared_ptr<CharacterSelect> cs;

		
			RandomizeProxy( const std::shared_ptr<CharacterSelect> &cs );

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

		std::shared_ptr<GamerTag> MyGamerTag;
		std::shared_ptr<HeroLevel> MyHeroLevel;
		std::shared_ptr<Doll> MyDoll;

		int PlayerIndex;
		const std::shared_ptr<PlayerData> getPlayer() const;

		std::vector<int> ItemIndex;
		std::vector<std::vector<std::shared_ptr<MenuListItem> > > ItemList;

	
		Vector2 Center, NormalZoomCenter;

	
		static float Width;
		static std::vector<Vector2> Centers;
		void InitCenters();

		static void Shift( const std::shared_ptr<GUI_Panel> &panel );

		void Release();

		CharacterSelect( int PlayerIndex, bool QuickJoin );

		void InitColorScheme( int PlayerIndex );

		void Randomize();

	
		int HoldCapeIndex, HoldCapeOutlineIndex;
	
		void Customize_UpdateColors();

		bool HasCustom();

		bool AvailableColorScheme( ColorScheme scheme );

		void SetIndex( int i );

	
		int FindIndex( std::vector<std::shared_ptr<MenuListItem> > &list, ClrTextFx obj );

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
