#ifndef HEROFACTORY_ESCALATION
#define HEROFACTORY_ESCALATION

#include "Escalate/Escalation.h"

namespace CloudberryKingdom
{
	class BobPhsx;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Challenge_HeroFactoryEscalation : public Challenge_Escalation
	{
	public:
		static std::shared_ptr<BobPhsx> FactoryHero;

	private:
		static const std::shared_ptr<Challenge_HeroFactoryEscalation> instance;
	public:
		const static std::shared_ptr<Challenge_HeroFactoryEscalation> &getInstance() const;

	protected:
		Challenge_HeroFactoryEscalation();

		virtual std::shared_ptr<BobPhsx> GetHero( int i );
	};
}


#endif	//#ifndef HEROFACTORY_ESCALATION
