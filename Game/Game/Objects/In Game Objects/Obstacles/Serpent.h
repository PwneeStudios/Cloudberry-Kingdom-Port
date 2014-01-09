#ifndef SERPENT
#define SERPENT

#include <small_header.h>

//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_BoxDeath.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/Serpent__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	struct Serpent : public _BoxDeath
	{

		virtual ~Serpent()
		{
#ifdef BOOST_BIN
			OnDestructor( "Serpent" );
#endif
		}

	
		struct SerpentTileInfo : public TileInfoBase
		{
		
//C# TO C++ CONVERTER NOTE: The variable Serpent was renamed since it is named the same as a user-defined type:
			boost::shared_ptr<SpriteInfo> Serpent_Renamed;
			boost::shared_ptr<SpriteInfo> Fish;
			Vector2 BoxSize;

		
			void InitializeInstanceFields();


			SerpentTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		boost::shared_ptr<QuadClass> MyQuad, MyFish;

		int Offset, UpT, DownT, WaitT1, WaitT2;

		Vector2 Start, End;

		bool Exposed;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		Serpent( bool BoxesOnly );

		void SetPeriod( int Period );

	
		virtual void ActivePhsxStep();

	
		void AnimStep();
		void AnimStep( bool Skip );

	
		virtual void DrawGraphics();

	
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef SERPENT
