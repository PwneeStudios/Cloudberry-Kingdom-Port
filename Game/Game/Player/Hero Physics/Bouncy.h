#ifndef BOUNCY
#define BOUNCY

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsxBouncy : public BobPhsxNormal
	{
		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxBouncy> instance;
	public:
		const static std::shared_ptr<BobPhsxBouncy> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxBouncy> &bob );

		// Instancable class
	private:
		bool InitializedAnim;

	public:
		BobPhsxBouncy();

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void DefaultValues();

		virtual void DuckingPhsx();

		virtual void UpdateReadyToJump();

		//float FakeVel = 0;
	private:
		float SuperBounce;
		int SuperBounceGraceCount;
		int SuperBounceGrace;
	public:
		virtual void Jump();

		virtual void AnimStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOUNCY
