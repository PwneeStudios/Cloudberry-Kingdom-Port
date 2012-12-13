#include <global_header.h>

namespace CloudberryKingdom
{

	void StartMenu_MW_Black::SlideIn( int Frames )
	{
		CkBaseMenu::SlideIn( 0 );
	}

	void StartMenu_MW_Black::SlideOut( const PresetPos &Preset, int Frames )
	{
		CkBaseMenu::SlideOut( Preset, 0 );
	}

	void StartMenu_MW_Black::OnAdd()
	{
		CkBaseMenu::OnAdd();
	}

	StartMenu_MW_Black::StartMenu_MW_Black() : CkBaseMenu() { }
	std::shared_ptr<StartMenu_MW_Black> StartMenu_MW_Black::StartMenu_MW_Black_Construct()
	{
		CkBaseMenu::CkBaseMenu_Construct();

		getCore()->DrawLayer++;
	}

	void StartMenu_MW_Black::Init()
	{
		 CkBaseMenu::Init();

		MyPile = std::make_shared<DrawPile>();

		EnsureFancy();

		//Black = new QuadClass("BlackSwipe");
		Black = std::make_shared<QuadClass>( _T( "BlackSwipe_Vertical" ) );
		Black->ScaleXToMatchRatio( 1000 );
		Black->setSizeX( Black->getSizeX() * 1.35f );
		MyPile->Add( Black, _T( "Black" ) );

		MyPile->setAlpha( 0 );

		BlackBox();
	}

	void StartMenu_MW_Black::BlackBox()
	{

	}

	void StartMenu_MW_Black::SlideFromRight()
	{
		MyPile->setAlpha( 1 );

		float scale = 1.3f;
		Black->setSizeX( 4700 * scale );
		Black->setPos( Vector2( 9500 * scale, 0 ) );
		Black->FancyPos->LerpTo( Vector2( -6500 * scale, 0 ), 50 );
	}

	void StartMenu_MW_Black::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();
	}

	void StartMenu_MW_Black::OnReturnTo()
	{
		CkBaseMenu::OnReturnTo();
	}
}
