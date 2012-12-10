#ifndef SCALE
#define SCALE

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxScale : public BobPhsxNormal
	{

	public:
		static void InitializeStatics();

	public:
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		// Singleton
	protected:
		virtual void InitSingleton();
	public:
		static std::shared_ptr<BobPhsxScale> instance;
	public:
		const static std::shared_ptr<BobPhsxScale> &getInstance();

		// Instancable class
		BobPhsxScale();
	};
}


#endif	//#ifndef SCALE
