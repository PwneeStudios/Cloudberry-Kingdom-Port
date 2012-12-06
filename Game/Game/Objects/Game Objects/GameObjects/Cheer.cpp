#include <global_header.h>

namespace CloudberryKingdom
{

	Cheer::Cheer()
	{
		InitializeInstanceFields();
		MyPile->FancyPos->UpdateWithGame = true;

		Berry = std::make_shared<QuadClass>();
		Berry->SetToDefault();
		Berry->setTextureName( _T( "cb_enthusiastic" ) );
		Berry->Scale( 300 );
		Berry->ScaleYToMatchRatio();

		Berry->setPos( Vector2( 0, -1250 ) );
		MyPile->Add( Berry );

		//MyPile.Pos = new Vector2(315, 775);
	}

	void Cheer::OnAdd()
	{
		GameObject::OnAdd();

		Berry->FancyPos->ToAndBack( Berry->getPos() + Vector2(0, 550), 53 );
		//Berry.FancyPos.ToAndBack(new Vector2(0, 700), 90);
	}

	void Cheer::MyDraw()
	{
		// No cheers =(
		return;

		if ( !getCore()->Show || getCore()->MyLevel->SuppressCheckpoints )
			return;

		std::shared_ptr<Level> level = getCore()->MyLevel;
		MyPile->FancyPos->SetCenter( level->getMainCamera(), true );
		MyPile->FancyPos->Update();

		MyPile->Draw();
	}

	void Cheer::MyPhsxStep()
	{
		if ( !Berry->FancyPos->Playing )
			MyGame->Recycle->CollectObject( shared_from_this() );
	}

	void Cheer::InitializeInstanceFields()
	{
		MyPile = std::make_shared<DrawPile>();
	}
}
