#ifndef SPIKEYLINE
#define SPIKEYLINE

#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
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


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{
	class SpikeyLine : public _CircleDeath, public IBound
	{
	public:
		class SpikeyLineTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<SpriteInfo> Ball;

			float Radius;

			bool Rotate;
			float RotateOffset, RotateSpeed;

		private:
			void InitializeInstanceFields();

public:
			SpikeyLineTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		int Period, Offset;
		Vector2 p1, p2;

	private:
		std::shared_ptr<QuadClass> Head;

	public:
		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

		SpikeyLine( bool BoxesOnly );

		/// <summary>
		/// Get's the specified position of the floater at time t
		/// </summary>
		/// <param name="t">The parametric time variable, t = (Step + Offset) / Period</param>
		/// <returns></returns>
		Vector2 GetPos( float t );

		virtual void PhsxStep();


	private:
		bool OffScreen;
	protected:
		virtual void DrawGraphics();

	public:
		virtual void Move( Vector2 shift );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		void MoveToBounded( Vector2 shift );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPIKEYLINE
