#ifndef SPIKEYGUY
#define SPIKEYGUY

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class LineSpriteInfo;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}






namespace CloudberryKingdom
{
	class SpikeyGuy : public _CircleDeath
	{
	public:
		class SpikeyGuyTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<SpriteInfo> Ball;
			std::shared_ptr<SpriteInfo> Base;

			std::shared_ptr<LineSpriteInfo> Chain;

			float Radius;

			bool Rotate;
			float RotateOffset, RotateSpeed;

		private:
			void InitializeInstanceFields();

public:
			SpikeyGuyTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		float Angle, MaxAngle, Length;
		int Period, Offset;
		Vector2 PivotPoint;

		int Dir;

	private:
		std::shared_ptr<QuadClass> Anchor, Head;

	public:
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
	private:
		float CorrespondingAngle;
		Vector2 GetPos( float t );

	public:
		virtual void PhsxStep();


	private:
		bool OffScreen;
	protected:
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	public:
		virtual void Move( Vector2 shift );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPIKEYGUY
