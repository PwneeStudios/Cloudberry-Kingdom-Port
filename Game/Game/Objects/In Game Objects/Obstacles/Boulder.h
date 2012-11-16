#ifndef BOULDER
#define BOULDER

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


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Boulder : public _CircleDeath, public IBound
	{
	public:
		enum PivotLocationTypes
		{
			PivotLocationTypes_TOP_BOTTOM,
			PivotLocationTypes_LEFT_RIGHT
		};
	public:
		class BoulderTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<SpriteInfo> Ball;

			float Radius;

			std::shared_ptr<LineSpriteInfo> Chain;

		private:
			void InitializeInstanceFields();

public:
			BoulderTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	public:
		std::shared_ptr<QuadClass> MyQuad;

		float Angle, MaxAngle, Length;
		int Period, Offset;
		Vector2 PivotPoint;

		virtual void OnAttachedToBlock();

		virtual void MakeNew();

		virtual void Init( Vector2 pos, const std::shared_ptr<Level> &level );

	private:
		void SetLayers();

	public:
		Boulder( bool BoxesOnly );

		Vector2 TR_Bound();

		Vector2 BL_Bound();

		float MinY();

		float AddAngle;

		PivotLocationTypes PivotLocationType;

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
		void CalculateLength();

		virtual void Move( Vector2 shift );

		void MoveToBounded( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOULDER
