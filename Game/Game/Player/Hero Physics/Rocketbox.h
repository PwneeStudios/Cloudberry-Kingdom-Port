#ifndef ROCKETBOX
#define ROCKETBOX

#include <global_header.h>

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class BlockBase;
}

namespace CloudberryKingdom
{
	class Quad;
}

namespace CloudberryKingdom
{
	class BobPhsxRocketbox : public BobPhsxBox
	{
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxRocketbox> instance;
	public:
		const static std::shared_ptr<BobPhsxRocketbox> &getInstance() const;

		// Instancable class
		BobPhsxRocketbox();

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void SideHit( ColType side, const std::shared_ptr<BlockBase> &block );

		virtual void DefaultValues();

		virtual void DoXAccel();

	private:
		std::shared_ptr<Quad> LeftWheel, RightWheel;
		float WheelAngle;
	public:
		virtual void AnimStep();

		virtual void GenerateInput( int CurPhsxStep );

		virtual void PhsxStep2();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ROCKETBOX
