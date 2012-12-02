#include <global_header.h>

namespace CloudberryKingdom
{

	float DifficultyHelper::Interp( float Level1Val, float Level10Val, float level )
	{
		return CoreMath::Lerp( Vector2( 1, Level1Val ), Vector2( 10, Level10Val ), level );
	}

	float DifficultyHelper::InterpRestrict19( float Level1Val, float Level9Val, float level )
	{
		level = CoreMath::Restrict( 1, 9, level );
		return Interp19( Level1Val, Level9Val, level );
	}

	float DifficultyHelper::Interp19( float Level1Val, float Level9Val, float level )
	{
		return CoreMath::Lerp( Vector2( 1, Level1Val ), Vector2( 9, Level9Val ), level );
	}

	Vector2 DifficultyHelper::InterpRestrict19( Vector2 Level1Val, Vector2 Level9Val, float level )
	{
		level = CoreMath::Restrict( 1, 9, level );
		return Interp19( Level1Val, Level9Val, level );
	}

	Vector2 DifficultyHelper::Interp19( Vector2 Level1Val, Vector2 Level9Val, float level )
	{
		float t = ( level - 1 ) / ( 9 - 1 );
		return Vector2::Lerp( Level1Val, Level9Val, t );
	}

	float DifficultyHelper::InterpRestrict159( float Level1Val, float Level5Val, float Level9Val, float level )
	{
		level = CoreMath::Restrict( 1, 9, level );
		return Interp159( Level1Val, Level5Val, Level9Val, level );
	}

	float DifficultyHelper::Interp159( float Level1Val, float Level5Val, float Level9Val, float level )
	{
		return Level1Val * ( level - 5 ) * ( level - 9 ) / ( ( 1 - 5 ) * ( 1 - 9 ) ) + Level5Val * ( level - 1 ) * ( level - 9 ) / ( ( 5 - 1 ) * ( 5 - 9 ) ) + Level9Val * ( level - 1 ) * ( level - 5 ) / ( ( 9 - 1 ) * ( 9 - 5 ) );
	}
}
