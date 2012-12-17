#ifndef SERPENT
#define SERPENT

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Serpent : public _BoxDeath
	{
	
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
