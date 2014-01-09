#ifndef LEADERBOARDVIEW
#define LEADERBOARDVIEW

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Input/ButtonCheck.h"
//#include "Core/Text/EzText.h"
//#include "Core/Tools/ColorHelper.h"
#include "Core/Tools/CoreMath.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
//#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Menus/Menu Components/MenuList.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


//#include <Hacks/SignedInGamer.h>
#include <Game/Player/Leaderboard.h>

namespace CloudberryKingdom
{

	struct LeaderboardView;
	struct LeaderboardItem;

	struct LeaderboardGUI : CkBaseMenu
	{

		struct ViewGamerProxy : public Lambda
		{

			boost::shared_ptr<LeaderboardGUI> lb;

			ViewGamerProxy( boost::shared_ptr<LeaderboardGUI> lb )
			{
				this->lb = lb;
			}

			void Apply()
			{
				lb->ViewGamer();
			}

		};

		struct SwitchViewProxy : public Lambda
		{

			boost::shared_ptr<LeaderboardGUI> lb;

			SwitchViewProxy( boost::shared_ptr<LeaderboardGUI> lb )
			{
				this->lb = lb;
			}

			void Apply()
			{
				lb->SwitchView();
			}

		};

		struct SwitchSortProxy : public Lambda
		{

			boost::shared_ptr<LeaderboardGUI> lb;

			SwitchSortProxy( boost::shared_ptr<LeaderboardGUI> lb )
			{
				this->lb = lb;
			}

			void Apply()
			{
				lb->SwitchSort();
			}

		};

		virtual ~LeaderboardGUI()
		{
#ifdef BOOST_BIN
			OnDestructor( "LeaderboardGUI" );
#endif
		}


		using CkBaseMenu::SlideOut;
		using CkBaseMenu::SlideIn;
		using CkBaseMenu::Call;

        LeaderboardType CurrentType;
        LeaderboardSortType CurrentSort;
        Message CurrentMessage;

        static std::wstring LeaderboardType_ToString( LeaderboardType type );

        static std::wstring LeaderboardSortType_ToString( LeaderboardSortType type );

        boost::shared_ptr<LeaderboardView> CurrentView;



        int LeaderboardInex;
        boost::shared_ptr<Challenge> CurrentChallenge;
        boost::shared_ptr<BobPhsx> Hero;

        int DelayCount_LeftRight, MotionCount_LeftRight;
        static const int SelectDelay = 18;

        boost::shared_ptr<TitleGameData_MW> Title;
        LeaderboardGUI( boost::shared_ptr<TitleGameData_MW> Title, int Control );
		boost::shared_ptr<LeaderboardGUI> LeaderboardGUI_Construct( boost::shared_ptr<TitleGameData_MW> Title, int Control );

        void Init();

        boost::shared_ptr<EzText> LoadingText, NotRanked, NotRankedFriends;
        int LoadingCount;
        std::wstring LoadingStr0, LoadingStr1, LoadingStr2, LoadingStr3;

		void UpdateLoadingText();

        void UpdateMessages();

        void ViewGamer();

        LeaderboardType Incr( LeaderboardType type );

        LeaderboardSortType Incr( LeaderboardSortType type );

        void SwitchView();

        void SwitchSort();

        void UpdateView();

        void SetIndex( int index );

		void ChangeLeaderboard( int Direction );

		void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

        void SetTextProperties( const boost::shared_ptr<EzText> &text );

        void SetSelectedTextProperties( const boost::shared_ptr<EzText> &text );

        void OnAdd();

        void Release();

        static boost::shared_ptr<QuadClass> TL, Offset_GamerTag, Offset_Val, ItemShift;
        static boost::shared_ptr<HsvQuad> Highlight;

        int ToMake_Id;
        int DelayToMake;

        void MyPhsxStep();

        void MyDraw();

        void SetPos();

	};

    struct LeaderboardView
    {

		static const int EntriesPerPage = 17;
        int TotalEntries;

        bool Loading;

        int Index;
        int Start;
        int End() { return CoreMath::RestrictVal( 0, TotalEntries, Start + EntriesPerPage ); }

        std::map<int, LeaderboardItem> &getItems();

		boost::shared_ptr<Leaderboard> MyLeaderboard;

        LeaderboardView( int Id, LeaderboardType CurrentType );

        void IncrIndex( int change );

		void UpdateBounds();

        int DelayCount_UpDown, MotionCount_UpDown;
        static const int SelectDelay = 11;

        void PhsxStep( int Control );

		void LeaderboardView::ViewGamer();
		void LeaderboardView::SetType( LeaderboardType type );

		void Draw( Vector2 Pos, float alpha );
		void DrawList( float alpha, Vector2 CurPos, float Shift );
		void DrawDict( float alpha, Vector2 CurPos, float Shift );

	};

}

#endif // LEADERBOARDVIEW