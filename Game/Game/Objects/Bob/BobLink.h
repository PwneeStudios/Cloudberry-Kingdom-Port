#ifndef BOBLINK
#define BOBLINK

#include <small_header.h>

//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct BobLink : public boost::enable_shared_from_this<BobLink>
	{

	
		int _j, _k;
		boost::shared_ptr<Bob> j, k;
		float L, a_in, a_out, MaxForce;

		void Release();

		BobLink();

		const bool getInactive() const;

		void Draw();

		void Draw( Vector2 p1, Vector2 p2 );

		void PhsxStep( const boost::shared_ptr<Bob> &bob );

		void Connect( const boost::shared_ptr<Bob> &bob1, const boost::shared_ptr<Bob> &bob2 );
	};
}


#endif	//#ifndef BOBLINK
