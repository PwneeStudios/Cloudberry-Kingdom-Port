#ifndef BOUNCY
#define BOUNCY

#include <global_header.h>

namespace CloudberryKingdom
{

	struct BobPhsxBouncy : public BobPhsxNormal
	{
	
		static void InitializeStatics();

		// Singleton
	
		virtual void InitSingleton();
	
		static boost::shared_ptr<BobPhsxBouncy> instance;
	
		const static boost::shared_ptr<BobPhsxBouncy> &getInstance();

		virtual boost::shared_ptr<BobPhsx> Clone();
		void CopyTo( const boost::shared_ptr<BobPhsxBouncy> &bob );

		// Instancable struct
	
		bool InitializedAnim;

	
		BobPhsxBouncy();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		boost::shared_ptr<EzSound> DullSound;

		virtual void DefaultValues();

		virtual void DuckingPhsx();

		virtual void UpdateReadyToJump();

		//float FakeVel = 0;
	
		float SuperBounce;
		int SuperBounceGraceCount;
		int SuperBounceGrace;
	
		void PlayJumpSound();

		virtual void Jump();

		virtual void AnimStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOUNCY
