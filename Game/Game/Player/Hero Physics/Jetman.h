#ifndef JETMAN
#define JETMAN

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxJetman : public BobPhsxNormal
	{

	public:
		static void InitializeStatics();

	public:
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		static void SetJetmanObject( const std::shared_ptr<ObjectClass> &obj );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static std::shared_ptr<BobPhsxJetman> instance;
	public:
		const static std::shared_ptr<BobPhsxJetman> &getInstance();

		// Instancable class
		BobPhsxJetman();
	};
}


#endif	//#ifndef JETMAN
