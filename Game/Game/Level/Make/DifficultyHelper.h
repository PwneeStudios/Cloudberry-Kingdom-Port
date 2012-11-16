#ifndef DIFFICULTYHELPER
#define DIFFICULTYHELPER













namespace CloudberryKingdom
{
	class DifficultyHelper
	{
	public:
		static float Interp( float Level1Val, float Level10Val, float level );
		static float InterpRestrict19( float Level1Val, float Level9Val, float level );
		static float Interp19( float Level1Val, float Level9Val, float level );
		static Vector2 InterpRestrict19( Vector2 Level1Val, Vector2 Level9Val, float level );
		static Vector2 Interp19( Vector2 Level1Val, Vector2 Level9Val, float level );
		static float InterpRestrict159( float Level1Val, float Level5Val, float Level9Val, float level );
		static float Interp159( float Level1Val, float Level5Val, float Level9Val, float level );
	};
}


#endif	//#ifndef DIFFICULTYHELPER
