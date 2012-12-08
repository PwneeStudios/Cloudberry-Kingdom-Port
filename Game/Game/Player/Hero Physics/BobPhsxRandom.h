#ifndef BOB_PHSX_RANDOM_H
#define BOB_PHSX_RANDOM_H

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxRandom : public BobPhsx
	{
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxRandom> instance;
	public:
		static const std::shared_ptr<BobPhsxRandom> &getInstance();

		static std::shared_ptr<BobPhsx> ChooseHeroType();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxRandom> &bob );

		// Instancable class
		BobPhsxRandom();
	};
}


#endif	//#ifndef RANDOM
