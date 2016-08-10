#ifndef _CODE_FOREST
#define _CODE_FOREST

#include <small_header.h>

namespace CloudberryKingdom
{
	struct Background_Forest : public BackgroundTemplate
	{

		virtual ~Background_Forest()
		{
#ifdef BOOST_BIN
			OnDestructor( "Background_Forest" );
#endif
		}


		Background_Forest( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

	struct Background_ForestSnow : public BackgroundTemplate
	{
	
		virtual ~Background_ForestSnow()
		{
#ifdef BOOST_BIN
			OnDestructor( "Background_ForestSnow" );
#endif
		}


		Background_ForestSnow( const std::wstring &Name );

		virtual void Code( const boost::shared_ptr<Background> &b );

	};

}


#endif	//#ifndef _CODE_FOREST
