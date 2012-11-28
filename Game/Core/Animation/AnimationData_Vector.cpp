#include <global_header.h>

namespace CloudberryKingdom
{

bool AnimationData::RecordAll = false;

	void AnimationData::Release()
	{
		if ( Anims.size() > 0 )
			for ( int i = 0; i < static_cast<int>( Anims.size() ); i++ )
				Anims[ i ].Data.clear();
		Anims.clear();
	}

	void AnimationData::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		if ( Anims.empty() )
			writer->Write( -1 );
		else
		{
			writer->Write( static_cast<int>( Anims.size() ) );
			for ( int i = 0; i < static_cast<int>( Anims.size() ); i++ )
				WriteReadTools::WriteOneAnim( writer, Anims[ i ] );
		}
	}

	void AnimationData::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		int length = reader->ReadInt32();
		if ( length == -1 )
			Anims.clear();
		else
		{
			Anims = std::vector<OneAnim>( length );
			for ( int i = 0; i < length; i++ )
				WriteReadTools::ReadOneAnim( reader, Anims[ i ] );
		}
	}

	AnimationData::AnimationData()
	{
		Linear = false;
	}

	AnimationData::AnimationData( const AnimationData &data )
	{
		Linear = false;

		Hold = Vector2();
		Anims = std::vector<OneAnim>( data.Anims.size() );
		for ( int i = 0; i < static_cast<int>( data.Anims.size() ); i++ )
			CopyAnim( data, i );
	}

	void AnimationData::CopyAnim( const AnimationData &data, int Anim )
	{
		if ( data.Anims[ Anim ].Data.size() > 0 )
		{
			Anims[ Anim ].Data = std::vector<Vector2>( data.Anims[ Anim ].Data.size() );
			//data.Anims[ Anim ].Data.CopyTo( Anims[ Anim ].Data, 0 );
			Anims[ Anim ].Data.assign( data.Anims[ Anim ].Data.begin(), data.Anims[ Anim ].Data.end() );
		}
		else
			Anims[ Anim ].Data.clear();
	}

	void AnimationData::Init()
	{
		const OneAnim tempVector[] = { OneAnim() };
		Anims = std::vector<OneAnim>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
		Hold = Vector2();
	}

	void AnimationData::InsertFrame( int anim, int frame )
	{
		if ( anim >= static_cast<int>( Anims.size() ) )
			return;
		if ( Anims[ anim ].Data.empty() )
			return;
		if ( frame >= static_cast<int>( Anims[ anim ].Data.size() ) )
			return;

		OneAnim NewAnim = OneAnim();
		NewAnim.Data = std::vector<Vector2>( Anims[ anim ].Data.size() + 1 );
		for ( int i = 0; i < frame; i++ )
			NewAnim.Data[ i ] = Anims[ anim ].Data[ i ];
		NewAnim.Data[ frame ] = Anims[ anim ].Data[ frame ];
		for ( int i = frame + 1; i < static_cast<int>( Anims[ anim ].Data.size() ) + 1; i++ )
			NewAnim.Data[ i ] = Anims[ anim ].Data[ i - 1 ];
		Anims[ anim ] = NewAnim;
	}

	void AnimationData::DeleteFrame( int anim, int frame )
	{
		if ( anim >= static_cast<int>( Anims.size() ) )
			return;
		if ( Anims[ anim ].Data.empty() )
			return;
		if ( frame >= static_cast<int>( Anims[ anim ].Data.size() ) )
			return;

		if ( Anims[ anim ].Data.size() > 1 )
		{
			OneAnim NewAnim = OneAnim();
			NewAnim.Data = std::vector<Vector2>( Anims[ anim ].Data.size() - 1 );
			for ( int i = 0; i < frame; i++ )
				NewAnim.Data[ i ] = Anims[ anim ].Data[ i ];
			for ( int i = frame + 1; i < static_cast<int>( Anims[ anim ].Data.size() ); i++ )
				NewAnim.Data[ i - 1 ] = Anims[ anim ].Data[ i ];
			Anims[ anim ] = NewAnim;
		}
	}

	void AnimationData::AddFrame( Vector2 val, int anim )
	{
		int frame = 0;
		if ( anim >= static_cast<int>( Anims.size() ) )
			frame = 0;
		else if ( Anims[ anim ].Data.empty() )
			frame = 0;
		else
			frame = Anims[ anim ].Data.size();

		Set( val, anim, frame );
	}

	void AnimationData::Set( Vector2 val, int anim, int frame )
	{
		Vector2 Default = Vector2( -123456, -123456 );
		if ( Anims[ 0 ].Data.size() > 0 )
		{
			Default = Anims[ 0 ].Data[ 0 ];
		}

		if ( anim >= static_cast<int>( Anims.size() ) )
		{
			std::vector<OneAnim> NewAnims = std::vector<OneAnim>( anim + 1 );
			//Anims.CopyTo( NewAnims, 0 );
			NewAnims.assign( Anims.begin(), Anims.end() );
			Anims = NewAnims;
		}

		if ( Anims[ anim ].Data.empty() )
		{
			const Vector2 tempVector2[] = { Default };
			Anims[ anim ].Data = std::vector<Vector2>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );
		}
		else
			if ( frame > 0 )
				Default = Get( anim, frame - 1 );

		if ( frame >= static_cast<int>( Anims[ anim ].Data.size() ) && !(val == Default && Anims[ anim ].Data.size() <= 1) )
		{
			std::vector<Vector2> NewData = std::vector<Vector2>( frame + 1 );
			for ( int i = 0; i < frame + 1; i++ )
				NewData[ i ] = Default;
			//Anims[ anim ].Data.CopyTo( NewData, 0 );
			NewData.assign(Anims[ anim ].Data.begin(), Anims[ anim ].Data.end() );
			Anims[ anim ].Data = NewData;
		}

		if ( frame < static_cast<int>( Anims[ anim ].Data.size() ) )
			Anims[ anim ].Data[ frame ] = val;
	}

	Vector2 AnimationData::Get( int anim, int frame )
	{
		Vector2 Default = Vector2();
		if ( Anims[ 0 ].Data.size() > 0 )
			Default = Anims[ 0 ].Data[ 0 ];


		if ( anim >= static_cast<int>( Anims.size() ) )
			return Default;

		if ( Anims[ anim ].Data.empty() )
			return Default;
		else
		{
			int Length = Anims[ anim ].Data.size();
			if ( Length > 0 )
			{
				if ( frame >= Length )
					Default = Anims[ anim ].Data[ Length - 1 ];
				else if ( frame > 0 )
					Default = Get( anim, frame - 1 );
				else
					Default = Anims[ anim ].Data[ 0 ];
				//Default = Anims[anim].Data[0];
			}
			else
				return Default;
		}
		if ( frame >= static_cast<int>( Anims[ anim ].Data.size() ) || frame < 0 )
			return Default;

		return Anims[ anim ].Data[ frame ];
	}

	Vector2 AnimationData::Transfer( int DestAnim, float DestT, int DestLength, bool DestLoop, bool DestLinear, float t )
	{
		Vector2 v1 = Hold;
		Vector2 v2 = Calc( DestAnim, DestT, DestLength, DestLoop, DestLinear );

		return Vector2::Lerp( v1, v2, t );
	}

	Vector2 AnimationData::Calc( int anim, float t, int Length, bool Loop, bool Linear )
	{
		if ( Linear )
		{
			Vector2 v2, v3;
			int i = static_cast<int>( floor( t ) );
			if ( !Loop )
			{
				v2 = Get( anim, i );
				v3 = Get( anim, static_cast<int>( __min( Length, i + 1 ) ) );
			}
			else
			{
				v2 = Get( anim, i );
				if ( i + 1 <= Length )
					v3 = Get( anim, i + 1 );
				else
					v3 = Get( anim, i + 1 - Length - 1 );
			}

			return Vector2::Lerp( v2, v3, t - i );
		}
		else
		{
			Vector2 v1, v2, v3, v4;
			int i = static_cast<int>( floor( t ) );
			if ( !Loop )
			{
				v1 = Get( anim, static_cast<int>( __max( 0, i - 1 ) ) );
				v2 = Get( anim, i );
				v3 = Get( anim, static_cast<int>( __min( Length, i + 1 ) ) );
				v4 = Get( anim, static_cast<int>( __min( Length, i + 2 ) ) );
			}
			else
			{
				if ( i - 1 >= 0 )
					v1 = Get( anim, i - 1 );
				else
					v1 = Get( anim, Length );
				v2 = Get( anim, i );
				if ( i + 1 <= Length )
					v3 = Get( anim, i + 1 );
				else
					v3 = Get( anim, i + 1 - Length - 1 );
				if ( i + 2 <= Length )
					v4 = Get( anim, i + 2 );
				else
					v4 = Get( anim, i + 2 - Length - 1 );
			}

			return Vector2::CatmullRom( v1, v2, v3, v4, t - i );
		}
	}

	Vector3 AnimationData::VecAndLength( Vector2 v )
	{
		return Vector3( v.X, v.Y, v.Length() );
	}

	Vector2 AnimationData::CalcAxis( int anim, float t, int Length, bool Loop, bool Linear )
	{
		Vector3 result;
		if ( Linear )
		{
			Vector3 v2, v3;
			int i = static_cast<int>( floor( t ) );
			if ( !Loop )
			{
				v2 = VecAndLength( Get( anim, i ) );
				v3 = VecAndLength( Get( anim, static_cast<int>( __min( Length, i + 1 ) ) ) );
			}
			else
			{
				v2 = VecAndLength( Get( anim, i ) );
				if ( i + 1 <= Length )
					v3 = VecAndLength( Get( anim, i + 1 ) );
				else
					v3 = VecAndLength( Get( anim, i + 1 - Length - 1 ) );
			}

			result = Vector3::Lerp( v2, v3, t - i );
		}
		else
		{
			Vector3 v1, v2, v3, v4;
			int i = static_cast<int>( floor( t ) );
			if ( !Loop )
			{
				v1 = VecAndLength( Get( anim, static_cast<int>( __max( 0, i - 1 ) ) ) );
				v2 = VecAndLength( Get( anim, i ) );
				v3 = VecAndLength( Get( anim, static_cast<int>( __min( Length, i + 1 ) ) ) );
				v4 = VecAndLength( Get( anim, static_cast<int>( __min( Length, i + 2 ) ) ) );
			}
			else
			{
				if ( i - 1 >= 0 )
					v1 = VecAndLength( Get( anim, i - 1 ) );
				else
					v1 = VecAndLength( Get( anim, Length ) );
				v2 = VecAndLength( Get( anim, i ) );
				if ( i + 1 <= Length )
					v3 = VecAndLength( Get( anim, i + 1 ) );
				else
					v3 = VecAndLength( Get( anim, i + 1 - Length - 1 ) );
				if ( i + 2 <= Length )
					v4 = VecAndLength( Get( anim, i + 2 ) );
				else
					v4 = VecAndLength( Get( anim, i + 2 - Length - 1 ) );
			}

			result = Vector3::CatmullRom( v1, v2, v3, v4, t - i );
		}

		Vector2 v = Vector2( result.X, result.Y );
		v.Normalize();
		v *= result.Z;

		return v;
	}
}
