#ifndef TIME
#define TIME

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class StyleData;
}

namespace CloudberryKingdom
{
	class Level;
}







namespace CloudberryKingdom
{
	class BobPhsxTime : public BobPhsxNormal
	{
	private:
		enum Behavior
		{
			Behavior_PAUSE,
			Behavior_REGULAR
		};
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxTime> instance;
	public:
		const static std::shared_ptr<BobPhsxTime> &getInstance() const;

		// Instancable class
		BobPhsxTime();

		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );
		void Set( const std::shared_ptr<BobPhsx> &phsx, Vector2 modsize );

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void LandOnSomething( bool MakeReadyToJump, const std::shared_ptr<ObjectBase> &ThingLandedOn );

	private:
		Behavior CurBehavior;
		int BehaviorLength;
	public:
		virtual void GenerateInput( int CurPhsxStep );

		virtual void ModData( std::shared_ptr<Level.MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TIME
