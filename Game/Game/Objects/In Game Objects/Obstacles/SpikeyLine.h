#ifndef SPIKEYLINE
#define SPIKEYLINE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SpikeyLine : public _CircleDeath, public IBound
	{

		virtual ~SpikeyLine() { }
	
		struct SpikeyLineTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Ball;

			float Radius;

			bool Rotate;
			float RotateOffset, RotateSpeed;

		
			void InitializeInstanceFields();


			SpikeyLineTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		int Period, Offset;
		Vector2 p1, p2;

	
		boost::shared_ptr<QuadClass> Head;

	
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		SpikeyLine( bool BoxesOnly );

		/// <summary>
		/// Get's the specified position of the floater at time t
		/// </summary>
		/// <param name="t">The parametric time variable, t = (Step + Offset) / Period</param>
		/// <returns></returns>
		Vector2 GetPos( float t );

		virtual void PhsxStep();


	
		bool OffScreen;
	
		virtual void DrawGraphics();

	
		virtual void Move( Vector2 shift );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		void MoveToBounded( Vector2 shift );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef SPIKEYLINE
