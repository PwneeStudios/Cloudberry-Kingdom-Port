#ifndef HEROFACTORY_ESCALATION
#define HEROFACTORY_ESCALATION

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Challenge_HeroFactoryEscalation : public Challenge_Escalation
	{
	
		static std::shared_ptr<BobPhsx> FactoryHero;

	
		static std::shared_ptr<Challenge_HeroFactoryEscalation> instance;
	
		const static std::shared_ptr<Challenge_HeroFactoryEscalation> &getInstance();

		Challenge_HeroFactoryEscalation();

	
		virtual std::shared_ptr<BobPhsx> GetHero( int i );
	};
}


#endif	//#ifndef HEROFACTORY_ESCALATION
