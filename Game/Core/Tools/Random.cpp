#include <global_header.h>




namespace CloudberryKingdom
{

	Rand::Rand( int seed )
	{
		MySeed = seed;
		Rnd = std::make_shared<System::Random>( MySeed );
	}

	Microsoft::Xna::Framework::Vector2 Rand::RndPos( Vector2 BL, Vector2 TR )
	{
		return Vector2( RndFloat( BL.X, TR.X ), RndFloat( BL.Y, TR.Y ) );
	}

	Microsoft::Xna::Framework::Vector2 Rand::RndVector2( float Width )
	{
		return Vector2( RndFloat( -Width / 2, Width / 2 ), RndFloat( -Width / 2, Width / 2 ) );
	}

	bool Rand::RndBool()
	{
		return RndBool( .5f );
	}

	bool Rand::RndBool( float Chance )
	{
		float f = RndFloat();
		return f < Chance;

		//return RndFloat() < Chance;
	}

	int Rand::RndBit()
	{
		if ( Rnd->NextDouble() > ::5 )
			return 1;
		else
			return -1;
	}

	int Rand::RndInt( int a, int b )
	{
		return static_cast<int>( __min( b, RndFloat( a, b + 1 ) ) );
	}

	float Rand::RndFloat()
	{
		return RndFloat( 0, 1 );
	}

	float Rand::RndFloat( float a, float b )
	{
		float dif = b - a;
		return static_cast<float>( Rnd->NextDouble() ) * dif + a;
	}

	float Rand::RndFloat( float a, float b, float spacing )
	{
		if ( a > b )
		{
			float temp = a;
			a = b;
			b = temp;
		}

		int intervals = static_cast<int>( ( b - a ) / spacing + .5f );
		spacing = ( b - a ) / intervals;

		return a + RndInt( 0, intervals ) * spacing;
	}

	float Rand::RndFloat( Vector2 range )
	{
		return RndFloat( range.X, range.Y );
	}

	Microsoft::Xna::Framework::Vector2 Rand::RndDir( float Length )
	{
		return RndDir() * RndFloat(0, Length);
	}

	Microsoft::Xna::Framework::Vector2 Rand::RndDir()
	{
		double Angle = Rnd->NextDouble() * 2 * M_PI;
		return Vector2( static_cast<float>( cos( Angle ) ), static_cast<float>( sin( Angle ) ) );
	}

	int Rand::RandomSnap( int Range, int SnapPoints )
	{
		return RndInt( 0, SnapPoints ) * ( Range / SnapPoints );
	}

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
template<typename T> where T : class
	int Rand::RndEnum()
	{
		return RndInt( 0, Tools->Length<T>() - 1 );
	}

template<typename T>
	void Rand::Scramble( std::vector<T> &list )
	{
		for ( int i = 0; i < list.size(); i++ )
		{
			int j = RndInt( 0, list.size() - 1 );

			T temp = list[ i ];
			list[ i ] = list[ j ];
			list[ j ] = temp;
		}
	}

template<typename T>
	T Rand::RandomItem( std::vector<T> list )
	{
		return list[ RndInt( 0, list.size() - 1 ) ];
	}

template<typename T>
	T Rand::RandomItem( std::vector<T> &list )
	{
		return list[ RndInt( 0, list.size() - 1 ) ];
	}

	std::vector<int> Rand::RndIndex( int Length, int NumIndices, std::vector<bool> Valid )
	{
		std::vector<int> Indices = std::vector<int>( NumIndices );
		std::vector<bool> Taken = std::vector<bool>( Length );

		for ( int i = 0; i < NumIndices; i++ )
			Indices[ i ] = -1;

		for ( int i = 0; i < NumIndices; i++ )
		{
			int Index = 0;
			int Count = Rnd->Next( 100, 1000 );
			int j;
			for ( j = 0; j < Count; j++ )
			{
				Index = ( Index + 1 ) % Length;
				while ( ( Taken[ Index ] || !Valid[ Index ] ) && !( Tools::_AllTaken( Taken, Valid, Length ) ) )
					Index = ( Index + 1 ) % Length;
			}

			Taken[ Index ] = true;
			Indices[ i ] = Index;
		}

		return Indices;
	}

template<typename T>
	std::vector<T> Rand::Shuffle( std::vector<T> &list )
	{
		std::vector<T> shuffled = std::vector<T>();
		std::vector<T> copy = std::vector<T>( list );

		for ( int i = 0; i < list.size(); i++ )
		{
			// Choose an element to add to the shuffled list
			int Index = RndInt( 0, copy.size() - 1 );
			shuffled.push_back( copy[ Index ] );
			copy.Remove( copy[ Index ] );
		}

		return shuffled;
	}

template<typename T>
	T Rand::ChooseOne( ... )
	{
		return choices[ RndInt( 0, choices->Length - 1 ) ];
	}

template<typename T>
	std::vector<T> Rand::Choose( std::vector<T> &list, int n )
	{
		std::vector<T> chosen = std::vector<T>( list );
		for ( int i = 0; i < list.size() - n; i++ )
			chosen.RemoveAt( RndInt( 0, chosen.size() - 1 ) );

		return chosen;
	}

template<typename T>
	T Rand::Choose( std::vector<T> list )
	{
		return Choose( std::vector<T>( list ), 1 )[ 0 ];
	}

template<typename T>
	T Rand::Choose( std::vector<T> &list )
	{
		return Choose( list, 1 )[ 0 ];
	}

	int Rand::Choose( std::vector<int> LevelCutoff, int Level_Renamed )
	{
		std::vector<float> Weights = std::vector<float>( LevelCutoff.size() );
		for ( int i = 0; i < LevelCutoff.size(); i++ )
		{
			if ( Level_Renamed >= LevelCutoff[ i ] )
				Weights[ i ] = 1;
			else
				Weights[ i ] = 0;
		}

		return Choose( Weights );
	}

	int Rand::Choose( std::vector<float> Weights )
	{
		double rnd = Rnd->NextDouble() * Weights.Sum() *.999f; // .98f;
		float AddedWeight = 0;
		for ( int i = 0; i < Weights.size(); i++ )
		{
			AddedWeight += Weights[ i ];
			if ( rnd < AddedWeight )
				return i;
		}

		return Weights.size() - 1;
	}

	int Rand::ChooseNew( int Cur, int WeightA, int WeightB )
	{
		if ( Cur == 0 && WeightB <= 0 )
			return 0;
		if ( Cur == 1 && WeightA <= 0 )
			return 1;

		if ( Cur == 0 )
			return 1;
		if ( Cur == 1 )
			return 0;

		return 0;
	}

	int Rand::ChooseNew( int Cur, int WeightA, int WeightB, int WeightC )
	{
		if ( Cur == 0 && WeightB <= 0 && WeightC <= 0 )
			return 0;
		if ( Cur == 1 && WeightA <= 0 && WeightC <= 0 )
			return 1;
		if ( Cur == 2 && WeightA <= 0 && WeightB <= 0 )
			return 2;

		if ( Cur == 0 && WeightB == 0 )
			return 2;
		if ( Cur == 0 && WeightC == 0 )
			return 1;
		if ( Cur == 1 && WeightA == 0 )
			return 2;
		if ( Cur == 1 && WeightC == 0 )
			return 0;
		if ( Cur == 2 && WeightA == 0 )
			return 1;
		if ( Cur == 2 && WeightB == 0 )
			return 0;


		if ( Cur == 0 )
			return Choose2( WeightB, 1, WeightC, 2 );
		if ( Cur == 1 )
			return Choose2( WeightA, 0, WeightC, 2 );
		if ( Cur == 2 )
			return Choose2( WeightA, 0, WeightB, 1 );

		return -1;
	}

	int Rand::Choose2( int WeightA, int ATag, int WeightB, int BTag )
	{
		int choice = Choose( WeightA, WeightB );
		if ( choice == 0 )
			return ATag;
		if ( choice == 1 )
			return BTag;

		return -1;
	}

	int Rand::Choose( int WeightA, int WeightB )
	{
		int n = Rnd->Next( 0, WeightA + WeightB );
		if ( n < WeightA )
			return 0;
		else
			return 1;
	}

	int Rand::Choose( int WeightA, int WeightB, int WeightC )
	{
		int n = Rnd->Next( 0, WeightA + WeightB + WeightC );
		if ( n < WeightA )
			return 0;
		else if ( n < WeightA + WeightB )
			return 1;
		else
			return 2;
	}

	int Rand::Choose( int WeightA, int WeightB, int WeightC, int WeightD )
	{
		int n = Rnd->Next( 0, WeightA + WeightB + WeightC + WeightD );
		if ( n < WeightA )
			return 0;
		else if ( n < WeightA + WeightB )
			return 1;
		else if ( n < WeightA + WeightB + WeightC )
			return 2;
		else
			return 3;
	}
}
