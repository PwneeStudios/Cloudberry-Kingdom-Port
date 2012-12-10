#ifndef SPIKE
#define SPIKE

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	struct Spike : public _BoxDeath
	{

	 static void InitializeStatics();

	
		struct SpikeTileInfo : public TileInfoBase
		{
		
//C# TO C++ CONVERTER NOTE: The variable Spike was renamed since it is named the same as a user-defined type:
			std::shared_ptr<SpriteInfo> Spike_Renamed;
			std::shared_ptr<SpriteInfo> Base;

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

	
		std::shared_ptr<SimpleObject> MyObject;

		std::shared_ptr<QuadClass> MyQuad, MyBaseQuad;

		int Dir;
		float Angle;

		int Offset, UpT, DownT, WaitT1, WaitT2;

		bool Exposed;

		void SetPeriod( int Period );

		virtual void MakeNew();

	
		float SetHeight;
	
		virtual void Init( Vector2 Pos, const std::shared_ptr<Level> &level );

		Spike( bool BoxesOnly );

		virtual void Construct( bool BoxesOnly );

		void SetDir( int dir );

	
		Vector2 unit;
	
		void SetAngle( float Ang );


		Spike( const std::wstring &file, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad );

		virtual void PhsxStep();

		virtual void PhsxStep2();


		void AnimStep();
		void AnimStep( bool Skip );

		void UpdateObject();

	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

	
		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Interact( const std::shared_ptr<Bob> &bob );

		void CloneBoxObject( const std::shared_ptr<SimpleObject> &SimpleObjA, const std::shared_ptr<SimpleObject> &SimpleObjB );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );
	};
}


#endif	//#ifndef SPIKE
