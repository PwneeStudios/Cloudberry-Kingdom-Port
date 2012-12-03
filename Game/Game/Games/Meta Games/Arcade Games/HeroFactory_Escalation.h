#ifndef HEROFACTORY_ESCALATION
#define HEROFACTORY_ESCALATION

#include <global_header.h>

namespace CloudberryKingdom
{
	class Challenge_HeroFactoryEscalation : public Challenge_Escalation
	{
	public:
		static std::shared_ptr<BobPhsx> FactoryHero;

	private:
		static const std::shared_ptr<Challenge_HeroFactoryEscalation> instance;
	public:
		const static std::shared_ptr<Challenge_HeroFactoryEscalation> &getInstance();

		Challenge_HeroFactoryEscalation();

	protected:
		virtual std::shared_ptr<BobPhsx> GetHero( int i );
	};
}


#endif	//#ifndef HEROFACTORY_ESCALATION
