#ifndef JETMAN
#define JETMAN

#include "Normal.h"
#include "../Core/Tools/Set.h"
#include <tchar.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class ObjectClass;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobPhsxJetman : public BobPhsxNormal
	{
	public:
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		static void SetJetmanObject( const std::shared_ptr<ObjectClass> &obj );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxJetman> instance;
	public:
		const static std::shared_ptr<BobPhsxJetman> &getInstance() const;

		// Instancable class
		BobPhsxJetman();
	};
}


#endif	//#ifndef JETMAN
