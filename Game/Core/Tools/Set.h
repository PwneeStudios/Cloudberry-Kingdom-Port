#ifndef SET
#define SET

#include <map>


#ifdef DEBUG
#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>
#endif

namespace CloudberryKingdom
{

	template<typename T>
	struct Set
	{
	
		std::map<T, bool> dict;

		const int &getCount() const
		{
			return dict.size();
		}

		bool Has( T item )
		{
			return dict.find( item ) != dict.end();
		}

		bool operator []( T item )
		{
			return dict.find( item ) != dict.end();
		}

		//boost::shared_ptr<Set<T> > operator + ( T item )
		//{
		//	if ( !this->dict.find( item ) != this->dict.end() )
		//		this->dict.insert( make_pair( item, true ) );

		//	return this;
		//}

		void Add( const T &item )
		{
			if ( dict.find( item ) == this->dict.end() )
				dict.insert( std::make_pair( item, true ) );
		}

		T Choose( const boost::shared_ptr<Rand> &Rnd )
		{
			int i = Rnd->RndInt( 0, dict.size() - 1 );
			
			typename std::map<T, bool>::const_iterator itr = dict.begin();
			int count = 0;
			while ( count < i )
			{
				++itr;
				++count;
			}
			
			return itr->first;
			//return (*(itr + i)).first;
		}

		bool Contains( T item )
		{
			if ( item == 0 )
				return true;
			else
				return dict.find( item ) != dict.end();
		}


	
		void InitializeInstanceFields()
		{
			dict = std::map<T, bool>();
		}


		Set()
		{
			InitializeInstanceFields();

/*#if defined(DEBUG)
			CloudberryKingdomGame::_count++;
			std::cout << CloudberryKingdomGame::_count << std::endl;
#endif*/
		}

		~Set()
		{
/*#if defined(DEBUG)
			CloudberryKingdomGame::_count--;
			std::cout << CloudberryKingdomGame::_count << std::endl;
#endif*/
		}

	};

}


#endif	//#ifndef SET
