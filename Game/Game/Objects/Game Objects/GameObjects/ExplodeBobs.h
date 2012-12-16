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
		boost::shared_ptr<ExplodeBobs> ExplodeBobs_Construct( int speed );

	
		int MySpeed;

	
		void SetSpeed( int speed );

		boost::shared_ptr<Lambda> OnDone;
	
		void Finish();

		static int CompareBobs( const boost::shared_ptr<Bob> &A, const boost::shared_ptr<Bob> &B );

		int Count;
	
		int InitialDelay_MultipleBobs, Delay, InitialDelay_OneBob;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EXPLODEBOBS
