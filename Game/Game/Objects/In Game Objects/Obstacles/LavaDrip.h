#ifndef LAVADRIP
#define LAVADRIP

#include <small_header.h>

//#include "Core/Tools/CoreMath.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_BoxDeath.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/LavaDrip__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct LavaDrip : public _BoxDeath
	{

		virtual ~LavaDrip()
		{
#ifdef BOOST_BIN
			OnDestructor( "LavaDrip" );
#endif
		}

	
		struct LavaDripTileInfo : public TileInfoBase
		{
		
//C# TO C++ CONVERTER NOTE: The variable Line was renamed since it is named the same as a user-defined type:
			boost::shared_ptr<LineSpriteInfo> Line_Renamed;
			Vector2 BoxSize;

		
			void InitializeInstanceFields();


			LavaDripTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		int Offset, DownT, WaitT, PeakT;

		Vector2 Start, End;

		bool Exposed;

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		LavaDrip( bool BoxesOnly );

		int Period;
		void SetPeriod( float speed );

	
		virtual void ActivePhsxStep();

	
		void AnimStep();
		void AnimStep( bool Skip );

	
		virtual void DrawGraphics();

	
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef LAVADRIP
