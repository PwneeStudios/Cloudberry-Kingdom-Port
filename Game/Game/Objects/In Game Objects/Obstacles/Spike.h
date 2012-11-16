#ifndef SPIKE
#define SPIKE

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class SimpleObject;
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
	class EzEffectWad;
}

namespace CloudberryKingdom
{
	class EzTextureWad;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;



namespace CloudberryKingdom
{
	class Spike : public _BoxDeath
	{
	public:
		class SpikeTileInfo : public TileInfoBase
		{
		public:
//C# TO C++ CONVERTER NOTE: The variable Spike was renamed since it is named the same as a user-defined type:
			std::shared_ptr<SpriteInfo> Spike_Renamed;
			std::shared_ptr<SpriteInfo> Base;

			float PeakHeight;

			float TopOffset, BottomOffset, SideOffset;

			Vector2 ObjectSize;

		private:
			void InitializeInstanceFields();

public:
			SpikeTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	private:
		static bool PeakOut;

	public:
		std::shared_ptr<SimpleObject> MyObject;

		std::shared_ptr<QuadClass> MyQuad, MyBaseQuad;

		int Dir;
		float Angle;

		int Offset, UpT, DownT, WaitT1, WaitT2;

		bool Exposed;

		void SetPeriod( int Period );

		virtual void MakeNew();

	private:
		float SetHeight;
	public:
		virtual void Init( Vector2 Pos, const std::shared_ptr<Level> &level );

		Spike( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		void SetDir( int dir );

	private:
		Vector2 unit;
	public:
		void SetAngle( float Ang );


		Spike( const std::wstring &file, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad );

		virtual void PhsxStep();

		virtual void PhsxStep2();


		void AnimStep();
		void AnimStep( bool Skip );

		void UpdateObject();

	protected:
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	public:
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		void CloneBoxObject( const std::shared_ptr<SimpleObject> &SimpleObjA, const std::shared_ptr<SimpleObject> &SimpleObjB );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef SPIKE
