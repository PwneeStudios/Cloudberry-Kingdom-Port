#ifndef EXPLODEBOBS
#define EXPLODEBOBS

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ExplodeBobs : public GUI_Panel
	{
	
		enum Speed
		{
			Speed_REGULAR,
			Speed_FAST
		};
	
		ExplodeBobs( int speed );
		void ExplodeBobs_Construct( int speed );

	
		int MySpeed;

	
		void SetSpeed( int speed );

		std::shared_ptr<Lambda> OnDone;
	
		void Finish();

		static int CompareBobs( const std::shared_ptr<Bob> &A, const std::shared_ptr<Bob> &B );

		int Count;
	
		int InitialDelay_MultipleBobs, Delay, InitialDelay_OneBob;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EXPLODEBOBS
