#ifndef CHARACTERSELECT
#define CHARACTERSELECT

#include <global_header.h>

namespace CloudberryKingdom
{
	class GamerTag;
}

namespace CloudberryKingdom
{
	class HeroLevel;
}

namespace CloudberryKingdom
{
	class Doll;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class MenuListItem;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Vector2;
		}
	}
}

namespace CloudberryKingdom
{
	class GUI_Panel;
}








#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif



namespace CloudberryKingdom
{
	class CharacterSelect
	{
	public:
		class RandomizeProxy : public Lambda
		{
		private:
			std::shared_ptr<CharacterSelect> cs;

		public:
			RandomizeProxy( const std::shared_ptr<CharacterSelect> &cs );

			void Apply();
		};

	public:
		enum SelectState
		{
			SelectState_BEGINNING,
			SelectState_SELECTING,
			SelectState_WAITING
		};
	public:
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
		const std::shared_ptr<PlayerData> &getPlayer() const;

		std::vector<int> ItemIndex;
		std::vector<std::vector<MenuListItem*> > ItemList;

	private:
		Vector2 Center, NormalZoomCenter;

	public:
		static float Width;
		static std::vector<Vector2> Centers;
		void InitCenters();

		static void Shift( const std::shared_ptr<GUI_Panel> &panel );

		void Release();

		CharacterSelect( int PlayerIndex, bool QuickJoin );

		void InitColorScheme( int PlayerIndex );

		void Randomize();

	private:
		int HoldCapeIndex, HoldCapeOutlineIndex;
	public:
		void Customize_UpdateColors();

		bool HasCustom();

		bool AvailableColorScheme( ColorScheme scheme );

		void SetIndex( int i );

	private:
		int FindIndex( std::vector<MenuListItem*> &list, ClrTextFx obj );

		/// <summary>
		/// Find the indices that would reproduce the current color scheme.
		/// </summary>
		void CopyIndicesFromColorScheme();

	public:
		void PhsxStep();

		void Draw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CHARACTERSELECT
