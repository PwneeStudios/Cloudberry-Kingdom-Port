#ifndef ANIMATIONDATA_VECTOR
#define ANIMATIONDATA_VECTOR

#include "../Core/Tools/Set.h"
#include <cmath>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Vector2;
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Audio;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework::Input;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class OneAnim
	{
	public:
		std::vector<Vector2> Data;
	};
	class AnimationData
	{
		/// <summary>
		/// If false, only changing values are recorded
		/// </summary>
	public:
		static bool RecordAll;

		std::vector<OneAnim> Anims;

		bool Linear;

		Vector2 Hold;

		void Release();

		void Write( const std::shared_ptr<BinaryWriter> &writer );

		void Read( const std::shared_ptr<BinaryReader> &reader );

		AnimationData( AnimationData data );

		void CopyAnim( AnimationData data, int Anim );

		//public AnimationData()
		void Init();

		void InsertFrame( int anim, int frame );

		void DeleteFrame( int anim, int frame );

		void AddFrame( Vector2 val, int anim );
		void Set( Vector2 val, int anim, int frame );

		Vector2 Get( int anim, int frame );

		Vector2 Transfer( int DestAnim, float DestT, int DestLength, bool DestLoop, bool DestLinear, float t );

		Vector2 Calc( int anim, float t, int Length, bool Loop, bool Linear );

	private:
		Vector3 VecAndLength( Vector2 v );
	public:
		Vector2 CalcAxis( int anim, float t, int Length, bool Loop, bool Linear );
	};
}


#endif	//#ifndef ANIMATIONDATA_VECTOR
