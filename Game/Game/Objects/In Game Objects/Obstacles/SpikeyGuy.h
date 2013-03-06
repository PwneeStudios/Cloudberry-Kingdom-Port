#ifndef SPIKEYGUY
#define SPIKEYGUY

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	
	struct SpikeyGuy : public _CircleDeath
	{

		virtual ~SpikeyGuy()
		{
#ifdef BOOST_BIN
			OnDestructor( "SpikeyGuy" );
#endif
		}

	
		struct SpikeyGuyTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Ball;
			boost::shared_ptr<SpriteInfo> Base;

			boost::shared_ptr<LineSpriteInfo> Chain;

			float Radius;

			bool Rotate;
			float RotateOffset, RotateSpeed;

		
			void InitializeInstanceFields();


			SpikeyGuyTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		float Angle, MaxAngle, Length;
		int Period, Offset;
		Vector2 PivotPoint;

		int Dir;

	
		boost::shared_ptr<QuadClass> Anchor, Head;

	
		virtual void OnAttachedToBlock();

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const boost::shared_ptr<Level> &level );

		SpikeyGuy( bool BoxesOnly );

		float MinY();

		/// <summary>
		/// Get's the specified position of the floater at time t
		/// </summary>
		/// <param name="t">The parametric time variable, t = (Step + Offset) / Period</param>
		/// <returns></returns>
	
		float CorrespondingAngle;
		Vector2 GetPos( float t );

	
		virtual void PhsxStep();


	
		bool OffScreen;
	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef SPIKEYGUY
