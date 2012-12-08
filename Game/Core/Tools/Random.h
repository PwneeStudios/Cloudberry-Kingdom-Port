#ifndef RANDOM
#define RANDOM

#define _USE_MATH_DEFINES
#include <global_header.h>

namespace CloudberryKingdom
{
	class Rand
	{

	public:
		int MySeed;
		Rand( int seed );

		std::shared_ptr<Random> Rnd;

		Vector2 RndPos( Vector2 BL, Vector2 TR );

		Vector2 RndVector2( float Width );

		/// <summary>
		/// Randomly returns true or false
		/// </summary>
		bool RndBool();
		bool RndBool( float Chance );

		/// <summary>
		/// Randomly chooses between 1 and -1
		/// </summary>
		/// <returns></returns>
		int RndBit();

		/// <summary>
		/// Returns a random number between a and b, inclusive
		/// </summary>
		/// <param name="a">Lower bound</param>
		/// <param name="b">Upper bound</param>
		/// <returns></returns>
		int RndInt( int a, int b );

		/// <summary>
		/// Returns a random float between 0 and 1.
		/// </summary>
		float RndFloat();

		float RndFloat( float a, float b );

		float RndFloat( float a, float b, float spacing );

		float RndFloat( Vector2 range );

		/// <summary>
		/// Returns a random direction with random magnitude between 0 and Length
		/// </summary>
		/// <param name="Length"></param>
		/// <returns></returns>
		Vector2 RndDir( float Length );

		/// <summary>
		/// Returns a random direction of length 1
		/// </summary>
		/// <returns></returns>
		Vector2 RndDir();



		int RandomSnap( int Range, int SnapPoints );

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
		/*template<typename T> where T : class
		int RndEnum();*/

		/// <summary>
		/// Scrambles the ordering of the given list in place.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="list"></param>
		template<typename T>
		void Scramble( std::vector<T> &list )
		{
			for ( int i = 0; i < static_cast<int>( list.size() ); i++ )
			{
				int j = RndInt( 0, static_cast<int>( list.size() ) - 1 );

				T temp = list[ i ];
				list[ i ] = list[ j ];
				list[ j ] = temp;
			}
		}

		template<typename T>
		T RandomItem( std::vector<T> list )
		{
			return list[ RndInt( 0, static_cast<int>( list.size() ) - 1 ) ];
		}

		template<typename T>
		T RandomItem( std::vector<T> &list )
		{
			return list[ RndInt( 0, static_cast<int>( list.size() ) - 1 ) ];
		}

		std::vector<int> RndIndex( int Length, int NumIndices, std::vector<bool> Valid );

		/// <summary>
		/// Creates a new list with the same elements in a shuffled order;
		/// </summary>
		template<typename T>
		std::vector<T> Shuffle( std::vector<T> &list )
		{
			std::vector<T> shuffled = std::vector<T>();
			std::vector<T> copy = std::vector<T>( list );

			for ( int i = 0; i < static_cast<int>( list.size() ); i++ )
			{
				// Choose an element to add to the shuffled list
				int Index = RndInt( 0, static_cast<int>( copy.size() ) - 1 );
				shuffled.push_back( copy[ Index ] );
				/*copy.Remove( copy[ Index ] );*/
				Remove( copy, copy[ Index ] );
			}

			return shuffled;
		}

		/// <summary>
		/// Returns a randomly chosen item from the items given
		/// </summary>
		template<typename T>
		T ChooseOne( std::vector<T> choices )
		{
			return choices[ RndInt( 0, choices->Length - 1 ) ];
		}

		/// <summary>
		/// Choose n elements from a list.
		/// </summary>
		template<typename T>
		std::vector<T> Choose( std::vector<T> &list, int n )
		{
			std::vector<T> chosen = std::vector<T>( list );
			for ( int i = 0; i < static_cast<int>( list.size() ) - n; i++ )
				/*chosen.RemoveAt( RndInt( 0, static_cast<int>( chosen.size() ) - 1 ) );*/
				chosen.erase( chosen.begin() + RndInt( 0, static_cast<int>( chosen.size() ) - 1 ) );

			return chosen;
		}

		template<typename T>
		T Choose( std::vector<T> &list )
		{
			return Choose( list, 1 )[ 0 ];
		}


		int Choose( std::vector<int> LevelCutoff, int Level_Renamed );

		int Choose( std::vector<float> Weights );

		int ChooseNew( int Cur, int WeightA, int WeightB );

		int ChooseNew( int Cur, int WeightA, int WeightB, int WeightC );

		int Choose2( int WeightA, int ATag, int WeightB, int BTag );

		int Choose( int WeightA, int WeightB );

		int Choose( int WeightA, int WeightB, int WeightC );

		int Choose( int WeightA, int WeightB, int WeightC, int WeightD );
	};
}


#endif	//#ifndef RANDOM
