#ifndef SET
#define SET

#include <global_header.h>

namespace CloudberryKingdom
{
	template<typename T>
	struct Set// : public IEnumerable, public IEnumerable<T>
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

		//std::shared_ptr<Set<T> > operator + ( T item )
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

		/*std::shared_ptr<IEnumerator> IEnumerable_GetEnumerator()
		{
			return dict.Keys->GetEnumerator();
		}
		std::shared_ptr<IEnumerator<T> > GetEnumerator()
		{
			return dict.Keys->GetEnumerator();
		}*/

		T Choose( const std::shared_ptr<Rand> &Rnd )
		{
			// FIXME: Please don't do this -_-
			int i = Rnd->RndInt( 0, dict.size() - 1 );
			std::map<T, bool>::iterator itr = dict.begin();
			while( i > 0 )
				++itr;
			return itr->first;
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
		}
	};
}


#endif	//#ifndef SET
