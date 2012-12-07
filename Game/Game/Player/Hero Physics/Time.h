#ifndef TIME
#define TIME

#include <global_header.h>

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
		const static std::shared_ptr<BobPhsxTime> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxTime> &bob );

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

		virtual void ModData( std::shared_ptr<MakeData> &makeData, const std::shared_ptr<StyleData> &Style );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TIME
