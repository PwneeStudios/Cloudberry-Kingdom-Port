#ifndef SMALL
#define SMALL

#include "Normal.h"
#include "../Core/Tools/Set.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobPhsxSmall : public BobPhsxNormal
	{
	public:
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxSmall> instance;
	public:
		const static std::shared_ptr<BobPhsxSmall> &getInstance() const;

		// Instancable class
		BobPhsxSmall();
	};
}


#endif	//#ifndef SMALL
