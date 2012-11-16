#include <global_header.h>






namespace CloudberryKingdom
{

	void Multicaster::Apply()
	{
		for ( std::vector<Lambda*>::const_iterator L = MyList.begin(); L != MyList.end(); ++L )
			( *L )->Apply();
	}

	void Multicaster::Clear()
	{
		MyList.clear();
	}

	void Multicaster::Add( const std::shared_ptr<Lambda> &L )
	{
		MyList.push_back( L );
	}

	void Multicaster::Remove( const std::shared_ptr<Lambda> &L )
	{
	}

	void Multicaster::InitializeInstanceFields()
	{
		MyList = std::vector<Lambda*>();
	}
}
