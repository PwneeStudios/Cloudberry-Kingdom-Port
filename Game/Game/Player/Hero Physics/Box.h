#ifndef BOX
#define BOX

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsxBox : public BobPhsxNormal
	{

	
		static void InitializeStatics();

		// Singleton
	
		virtual void InitSingleton();
	
		static std::shared_ptr<BobPhsxBox> instance;
	
		const static std::shared_ptr<BobPhsxBox> &getInstance();

		virtual std::shared_ptr<BobPhsx> Clone();
		void CopyTo( const std::shared_ptr<BobPhsxBox> &bob );

		// Instancable struct
	
		bool InitializedAnim;

	
		BobPhsxBox();

		virtual void DefaultValues();

		virtual void Init( const std::shared_ptr<Bob> &bob );

		virtual void DuckingPhsx();

	
		virtual void ParentDoXAccel();
	
		virtual void DoXAccel();

	
		virtual void ParentGenerateInput( int CurPhsxStep );
	
		virtual void GenerateInput( int CurPhsxStep );

	
		int StandAnim, JumpAnim, DuckAnim;
		//int StandAnim = 0, JumpAnim = 2, DuckAnim = 3;

	
		virtual void AnimStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOX
