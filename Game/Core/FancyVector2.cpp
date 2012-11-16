#include <global_header.h>
namespace CloudberryKingdom
{

	std::vector<std::wstring> FancyVector2::GetViewables()
	{
		const std::wstring* tempVector[] = { _T( "RelVal" ) };
		return std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}

	const float &FancyVector2::getRelValX() const
	{
		return RelVal.X;
	}

	void FancyVector2::setRelValX( const float &value )
	{
		RelVal = Vector2( value, RelVal.Y );
	}

	const float &FancyVector2::getRelValY() const
	{
		return RelVal.Y;
	}

	void FancyVector2::setRelValY( const float &value )
	{
		RelVal = Vector2( RelVal.X, value );
	}

	const Microsoft::Xna::Framework::Vector2 &FancyVector2::getPos() const
	{
		return Update();
	}

	const float &FancyVector2::getVal() const
	{
		return getPos().X;
	}

	void FancyVector2::setVal( const float &value )
	{
		RelVal = Vector2( value, RelVal.Y );
	}

	void FancyVector2::Release()
	{
		AnimData.Release();
		Center.reset();
		ObjCenter.reset();
	}

	FancyVector2::FancyVector2()
	{
		InitializeInstanceFields();
	}

	FancyVector2::FancyVector2( const std::shared_ptr<IPos> &Center )
	{
		InitializeInstanceFields();
		this->Center = Center;
	}

	void FancyVector2::SetCenter( const std::shared_ptr<IPos> &Center )
	{
		SetCenter( Center, false );
	}

	void FancyVector2::SetCenter( const std::shared_ptr<IPos> &Center, bool UsePosAsRelPos )
	{
		if ( this->Center == Center )
			return;

		if ( !UsePosAsRelPos )
			RelVal = Update() - Center->getPos();
		this->Center = Center;
	}

	void FancyVector2::SetCenter( const std::shared_ptr<ObjectBase> &ObjCenter )
	{
		SetCenter( ObjCenter, false );
	}

	void FancyVector2::SetCenter( const std::shared_ptr<ObjectBase> &ObjCenter, bool UsePosAsRelPos )
	{
		if ( this->ObjCenter == ObjCenter )
			return;

		if ( !UsePosAsRelPos )
			RelVal = Update() - ObjCenter->getPos();
		this->ObjCenter = ObjCenter;
	}

	Microsoft::Xna::Framework::Vector2 FancyVector2::GetDest()
	{
		if ( !Playing )
			return RelVal;
		else
			return AnimData.Get( 0, AnimData.Anims[ 0 ].Data.size() - 1 );
	}

	void FancyVector2::ToAndBack( Vector2 End, int Frames )
	{
		ToAndBack( RelVal, End, Frames );
	}

	void FancyVector2::ToAndBack( Vector2 Start, Vector2 End, int Frames )
	{
		RelVal = Start;

		AnimData = AnimationData();
		AnimData.Init();
		AnimData.Set( Start, 0, 0 );
		AnimData.Set( End, 0, 1 );
		AnimData.Set( Start, 0, 2 );

		Speed = 2 / Frames;
		TimeStamp = GetCurStep();
		t = 0;
		Playing = true;
	}

	void FancyVector2::MultiLerp( int Frames, ... )
	{
		MultiLerp( Frames, false, Positions );
	}

	void FancyVector2::MultiLerpReverse( int Frames, ... )
	{
		MultiLerp( Frames, true, Positions );
	}

	void FancyVector2::MultiLerp( int Frames, bool Reverse, ... )
	{
		AnimData = AnimationData();
		AnimData.Init();

		if ( Reverse )
			for ( int i = 0; i < Positions->Length; i++ )
				AnimData.Set( Positions[ Positions->Length - 1 - i ], 0, i );
		else
			for ( int i = 0; i < Positions->Length; i++ )
				AnimData.Set( Positions[ i ], 0, i );

		Speed = 1 / Frames;
		TimeStamp = GetCurStep();
		t = 0;
		Playing = true;
	}

const LerpStyle FancyVector2::DefaultLerpStyle = LerpStyle_DECAY_PLUS_SMALL_OVERSHOOT;

	void FancyVector2::LerpTo( int EndIndex, int Frames )
	{
		LerpTo( EndIndex, Frames, DefaultLerpStyle );
	}

	void FancyVector2::LerpTo( int EndIndex, int Frames, LerpStyle Style )
	{
		LerpTo( HoldVecs[ EndIndex ], Frames, Style );
	}

	void FancyVector2::LerpTo( int StartIndex, int EndIndex, int Frames )
	{
		LerpTo( StartIndex, EndIndex, Frames, DefaultLerpStyle );
	}

	void FancyVector2::LerpTo( int StartIndex, int EndIndex, int Frames, LerpStyle Style )
	{
		LerpTo( HoldVecs[ StartIndex ], HoldVecs[ EndIndex ], Frames, Style );
	}

	void FancyVector2::LerpTo( float End, int Frames )
	{
		LerpTo( Vector2( End ), Frames, DefaultLerpStyle );
	}

	void FancyVector2::LerpTo( Vector2 End, int Frames )
	{
		LerpTo( End, Frames, DefaultLerpStyle );
	}

	void FancyVector2::LerpTo( float End, int Frames, LerpStyle Style )
	{
		LerpTo( Vector2( End ), Frames, Style );
	}

	void FancyVector2::LerpTo( Vector2 End, int Frames, LerpStyle Style )
	{
		LerpTo( RelVal, End, Frames, Style );
	}

	void FancyVector2::LerpTo( float Start, float End, int Frames )
	{
		LerpTo( Vector2( Start ), Vector2( End ), Frames );
	}

	void FancyVector2::LerpTo( float Start, float End, int Frames, LerpStyle Style )
	{
		LerpTo( Vector2( Start ), Vector2( End ), Frames, Style );
	}

	void FancyVector2::LerpTo( Vector2 Start, Vector2 End, int Frames )
	{
		LerpTo( Start, End, Frames, DefaultLerpStyle );
	}

	void FancyVector2::LerpTo( Vector2 Start, Vector2 End, int Frames, LerpStyle Style )
	{
		if ( Frames == 0 )
		{
			RelVal = End;
			Playing = false;
			return;
		}

		RelVal = Start;

		AnimData = AnimationData();
		AnimData.Init();

		switch ( Style )
		{
			case LerpStyle_LINEAR:
				AnimData.Set( Start, 0, 0 );
				AnimData.Set( End, 0, 1 );
				Speed = 1 / Frames;
				break;

			case LerpStyle_DECAY_PLUS_SMALL_OVERSHOOT:
				AnimData.Set( Start, 0, 0 );
				AnimData.Set( ( Start + End ) / 2, 0, 1 );
				AnimData.Set( .8f * End + .2f * Start, 0, 2 );
				AnimData.Set( .95f * End + 0.05f * Start, 0, 3 );
				AnimData.Set( 1 * End + 0 * Start, 0, 4 );
				AnimData.Set( 1 * End + 0 * Start, 0, 5 );
				Speed = 3 / Frames;
				AnimData.Linear = false;
				break;

			case LerpStyle_SIGMOID:
				AnimData.AddFrame( Start, 0 );
				AnimData.AddFrame( .07f * End + .93f * Start, 0 );
				AnimData.AddFrame( .22f * End + .78f * Start, 0 );
				AnimData.AddFrame( .5f * End + .5f * Start, 0 );
				AnimData.AddFrame( .8f * End + .2f * Start, 0 );
				AnimData.AddFrame( .95f * End + 0.05f * Start, 0 );
				AnimData.AddFrame( 1 * End + 0 * Start, 0 );
				AnimData.AddFrame( 1 * End + 0 * Start, 0 );
				Speed = 4 / Frames;
				AnimData.Linear = false;
				break;

			case LerpStyle_DECAY_NO_OVERSHOOT:
				for ( int i = 0; i < 12; i++ )
				{
					//float s = (float)Math.Pow(.5, i);
					float s = static_cast<float>( pow( .5, i ) );
					AnimData.Set( ( 1 - s ) * End + s * Start, 0, i );
				}
				AnimData.Set( 1 * End + 0 * Start, 0, 20 );
				Speed = 4 / Frames;
				AnimData.Linear = false;
				break;

			case LerpStyle_SMALL_OVERSHOOT:
				AnimData.Set( Start, 0, 0 );
				AnimData.Set( ( Start + End ) / 2, 0, 1 );
				AnimData.Set( End, 0, 2 );
				AnimData.Set( End, 0, 3 );
				AnimData.Set( End, 0, 4 );
				Speed = 2 / Frames;
				AnimData.Linear = false;
				break;
		}

		TimeStamp = GetCurStep();
		t = 0;
		Playing = true;
	}

	int FancyVector2::GetCurStep()
	{
		if ( UpdateWithGame )
		{
			if ( Tools::CurGameData != 0 )
				return Tools::CurGameData->PhsxCount;
			else
				return int::MinValue;
		}

		if ( UpdateOnPause )
			return Tools::DrawCount;
		else
			return Tools::PhsxCount;
	}

	Microsoft::Xna::Framework::Vector2 FancyVector2::Update()
	{
		return Update( Vector2::One );
	}

	Microsoft::Xna::Framework::Vector2 FancyVector2::Update( Vector2 Scale )
	{
		int CurStep = GetCurStep();

		if ( Playing && CurStep != LastUpdate )
		{
			LastUpdate = CurStep;

			int Length = AnimData.Anims[ 0 ].Data.size();

			if ( UpdateWithGame )
				t += Speed;
			else
				t = Speed * ( CurStep - TimeStamp );

			if ( Loop )
			{
				t = t % ( Length + 1 );

				RelVal = AnimData.Calc( 0, t, Length, true, AnimData.Linear );
			}
			else
			{
				if ( t > Length - 1 )
				{
					Playing = false;
					RelVal = AnimData.Get( 0, Length - 1 );
				}
				else
					RelVal = AnimData.Calc( 0, t, Length, false, AnimData.Linear );
			}
		}

		AbsVal = Scale * RelVal;
		if ( Center != 0 )
			AbsVal += Center->getPos();
		else if ( ObjCenter != 0 )
			AbsVal += ObjCenter->getPos();

		return AbsVal;
	}

	void FancyVector2::InitializeInstanceFields()
	{
		HoldVecs = std::vector<Vector2>( 5 );
		code = 0;
		LastUpdate = int::MinValue;
		Playing = false;
		Loop = false;
		UpdateOnPause = true;
		UpdateWithGame = false;
	}
}
