#ifndef LAVADRIP
#define LAVADRIP

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LavaDrip : public _BoxDeath
	{

		virtual ~LavaDrip() { }
	
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
