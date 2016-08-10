#ifndef SPIKE
#define SPIKE

#define _USE_MATH_DEFINES
#include <small_header.h>

//#include "Core/Effects/EzEffectWad.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Graphics/Draw/Simple/SimpleObject.h"
//#include "Core/Texture/EzTextureWad.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Collision Detection/AABox.h"
//#include "Game/Collision Detection/Phsx.h"
//#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
//#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/In Game Objects/BaseClasses/_BoxDeath.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Objects/In Game Objects/Obstacles/Spike__Auto.h"
//#include "Game/Tilesets/SpriteInfo.h"
//#include "Game/Tools/Prototypes.h"
//#include "Game/Tools/Recycler.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{
	struct Spike : public _BoxDeath
	{

		virtual ~Spike()
		{
#ifdef BOOST_BIN
			OnDestructor( "Spike" );
#endif
		}


		static void InitializeStatics();

	
		struct SpikeTileInfo : public TileInfoBase
		{
		
//C# TO C++ CONVERTER NOTE: The variable Spike was renamed since it is named the same as a user-defined type:
			boost::shared_ptr<SpriteInfo> Spike_Renamed;
			boost::shared_ptr<SpriteInfo> Base;

			float PeakHeight;

			float TopOffset, BottomOffset, SideOffset;

			Vector2 ObjectSize;

		
			void InitializeInstanceFields();


			SpikeTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		static bool PeakOut;

	
		boost::shared_ptr<SimpleObject> MyObject;

		boost::shared_ptr<QuadClass> MyQuad, MyBaseQuad;

		int Dir;
		float Angle;

		int Offset, UpT, DownT, WaitT1, WaitT2;

		bool Exposed;

		void SetPeriod( int Period );

		virtual void MakeNew();

	
		float SetHeight;
	
		virtual void Init( Vector2 Pos, const boost::shared_ptr<Level> &level );

		Spike( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		void SetDir( int dir );

	
		Vector2 unit;
	
		void SetAngle( float Ang );


		Spike( const std::wstring &file, const boost::shared_ptr<EzEffectWad> &EffectWad, const boost::shared_ptr<EzTextureWad> &TextureWad );

		virtual void PhsxStep();

		virtual void PhsxStep2();


		void AnimStep();
		void AnimStep( bool Skip );

		void UpdateObject();

	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		void CloneBoxObject( const boost::shared_ptr<SimpleObject> &SimpleObjA, const boost::shared_ptr<SimpleObject> &SimpleObjB );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );
	};

}


#endif	//#ifndef SPIKE
