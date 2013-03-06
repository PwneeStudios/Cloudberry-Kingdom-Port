#ifndef HEROFACTORY_ESCALATION
#define HEROFACTORY_ESCALATION

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_HeroFactoryEscalation : public Challenge_Escalation
	{
	
		virtual ~Challenge_HeroFactoryEscalation()
		{
#ifdef BOOST_BIN
			OnDestructor( "Challenge_HeroFactoryEscalation" );
#endif
		}


		static boost::shared_ptr<BobPhsx> FactoryHero;

	
		static boost::shared_ptr<Challenge_HeroFactoryEscalation> instance;
	
		const static boost::shared_ptr<Challenge_HeroFactoryEscalation> &getInstance();

		Challenge_HeroFactoryEscalation();

	
		virtual boost::shared_ptr<BobPhsx> GetHero( int i );
	};
}


#endif	//#ifndef HEROFACTORY_ESCALATION
