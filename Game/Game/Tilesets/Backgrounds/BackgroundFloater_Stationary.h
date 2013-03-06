﻿#ifndef BACKGROUNDFLOATER_STATIONARY
#define BACKGROUNDFLOATER_STATIONARY

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BackgroundFloater_Stationary : public BackgroundFloater
	{

		virtual ~BackgroundFloater_Stationary()
		{
#ifdef BOOST_BIN
			OnDestructor( "BackgroundFloater_Stationary" );
#endif
		}


		BackgroundFloater_Stationary( const boost::shared_ptr<Level> &level );

		virtual void PhsxStep( const boost::shared_ptr<BackgroundFloaterList> &list );

		virtual void Draw();

	};

}


#endif	//#ifndef BACKGROUNDFLOATER_STATIONARY
