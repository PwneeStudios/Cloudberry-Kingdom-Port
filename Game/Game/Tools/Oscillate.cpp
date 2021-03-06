#include <small_header.h>
#include "Game/Tools/Oscillate.h"

#include "Game/Tools/Tools.h"


#include <Game\CloudberryKingdom\CloudberryKingdom.CloudberryKingdomGame.h>
#include <Hacks\List.h>

namespace CloudberryKingdom
{

	// Static variables
	float _oscillateparams[] = { 1.15f,.94f, 1.05f, 1 };
	std::vector<float> OscillateParams::JiggleScale = VecFromArray( _oscillateparams );


	OscillateParams::OscillateParams()
	{
		MyType = static_cast<Type>( 0 );
		w = base_value = max_addition = 0;

		Count = 0;

		UseGlobalCount = false;
		scale = 0;
		Done = false;
	}

	void OscillateParams::SetType( Type type )
	{
		SetType( type, true );
	}

	void OscillateParams::SetType( Type type, bool DoReset )
	{
		MyType = type;
		Done = false;

		if ( DoReset )
			Reset();
	}

	void OscillateParams::Set( float w, float base_value, float max_addition )
	{
		MyType = Type_OSCILLATE;
		scale = base_value;

		this->w = w;
		this->base_value = base_value;
		this->max_addition = max_addition;
	}

	void OscillateParams::Reset()
	{
		switch ( MyType )
		{
			case Type_JIGGLE:
				TargetJiggleScale = scale = base_value;
				Count = 0;
				break;

			default:
				scale = base_value;
				Count = 0;
				break;
		}
	}

	float OscillateParams::JigglePhsx()
	{
		Count++;

		float target = base_value + max_addition * 0;

		if ( Count >= 7 * static_cast<int>( JiggleScale.size() ) )
		{
			scale = TargetJiggleScale;
			Done = true;
		}
		else
		{
			scale = .5f * ( scale + JiggleScale[ Count / 7 ] * TargetJiggleScale );
			Done = false;
		}

		return scale;
	}

	float OscillateParams::GetScale_GetBig( float speed )
	{
		scale = ( 1 - speed ) * scale + speed * ( base_value + max_addition );

		return scale;
	}

	float OscillateParams::GetScale()
	{
		switch ( MyType )
		{
			case OscillateParams::Type_OSCILLATE:
				Count++;
				scale = Oscillate::GetScale_Oscillate( static_cast<float>( Count ), w, base_value, max_addition );
				break;

			case OscillateParams::Type_GET_BIG:
				Count = 0;
				//scale = GetScale_GetBig(.3f);
				//scale = GetScale_GetBig(.835f);
				break;

			case OscillateParams::Type_GET_BIG_SLOW:
				Count = 0;
				scale = GetScale_GetBig( .15f );
				break;

			case OscillateParams::Type_JIGGLE:
				scale = JigglePhsx();
				break;

			case Type_NONE:
				break;

			default:
				scale = 1;
				break;
		}

		return scale;
	}

	float Oscillate::GetAngle( float Step, float w )
	{
		return static_cast<float>( sin( .06f * w * Step ) );
	}

	float Oscillate::GetScale_Oscillate( float Step, float w, float base_value, float max_addition )
	{
		return base_value + .5f * ( max_addition + max_addition * Oscillate::GetAngle( Step, w ) );
	}
}
