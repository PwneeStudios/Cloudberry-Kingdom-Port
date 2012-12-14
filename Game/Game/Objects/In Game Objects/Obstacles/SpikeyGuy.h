#ifndef SPIKEYGUY
#define SPIKEYGUY

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct SpikeyGuy : public _CircleDeath
	{
	
		struct SpikeyGuyTileInfo : public TileInfoBase
		{
		
			std::shared_ptr<SpriteInfo> Ball;
			std::shared_ptr<SpriteInfo> Base;

			std::shared_ptr<LineSpriteInfo> Chain;

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

	
		std::shared_ptr<QuadClass> Anchor, Head;

	
		virtual void OnAttachedToBlock();

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

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

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPIKEYGUY
