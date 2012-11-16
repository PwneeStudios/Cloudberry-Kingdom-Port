#include <global_header.h>

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	SuperCheer::CheerHelper::CheerHelper( const std::shared_ptr<GameData> &mygame, Vector2 pos )
	{
		this->mygame = mygame;
		this->pos = pos;
	}

	void SuperCheer::CheerHelper::Apply()
	{
		std::shared_ptr<Cheer> cheer = std::make_shared<Cheer>();
		cheer->Berry->setPos( cheer->Berry->getPos() + pos );
		mygame->AddGameObject( cheer );
	}

	SuperCheer::SuperCheer( int Rows )
	{
		this->Rows = Rows;
	}

	void SuperCheer::OnAdd()
	{
		GameObject::OnAdd();

		for ( int i = 0; i < Rows; i++ )
			AddWave( 24 * i );

		MyGame->Recycle->CollectObject( this );
	}

	void SuperCheer::AddWave( int Delay )
	{
		float Spread = 3400;
		int Num = 13;
		float Step = Spread / ( Num - 1 );
		float Taper = 340;
		for ( int i = 0; i < Num; i++ )
		{
			float x = Step * i - Spread / 2;
			float y = -Taper * 4 * x * x / ( Spread * Spread );
			Vector2 pos = Vector2( x, y - 130 );

			std::shared_ptr<GameData> mygame = MyGame;
			MyGame->WaitThenDo( i * 6 + Delay, std::make_shared<CheerHelper>( mygame, pos ) );
		}
	}
}
