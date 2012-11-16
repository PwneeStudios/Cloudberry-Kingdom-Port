#ifndef OSCILLATE
#define OSCILLATE

#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class OscillateParams
	{
	public:
		enum Type
		{
			Type_NONE,
			Type_OSCILLATE,
			Type_GET_BIG,
			Type_GET_BIG_SLOW,
			Type_JIGGLE
		};

	public:
		Type MyType;
		void SetType( Type type );
		void SetType( Type type, bool DoReset );

		float w, base_value, max_addition;

		int Count;

		bool UseGlobalCount;

		/// <summary>
		/// Dummy variable for internal use.
		/// </summary>
	private:
		float scale;

	public:
		void Set( float w, float base_value, float max_addition );

	private:
		float TargetJiggleScale;
	public:
		void Reset();

		/// <summary>
		/// If the current animation is not infinite (looped) then this variable is true
		/// when the animation finishes.
		/// </summary>
		bool Done;

		//static float[] JiggleScale = { 1.25f, .9f, 1.08f, 1f };
	private:
		static std::vector<float> JiggleScale;
		float JigglePhsx();

		float GetScale_GetBig( float speed );

	public:
		float GetScale();
	};

	class Oscillate
	{
	public:
		static float GetAngle( float Step, float w );

		static float GetScale_Oscillate( float Step, float w, float base_value, float max_addition );
	};
}


#endif	//#ifndef OSCILLATE
