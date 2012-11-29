#ifndef EXPLODEBOBS
#define EXPLODEBOBS

#include <global_header.h>

namespace CloudberryKingdom
{
	class ExplodeBobs : public GUI_Panel
	{
	public:
		enum Speed
		{
			Speed_REGULAR,
			Speed_FAST
		};
	public:
		ExplodeBobs( int speed );

	private:
		int MySpeed;

	public:
		void SetSpeed( int speed );

		std::shared_ptr<Lambda> OnDone;
	private:
		void Finish();

		static int CompareBobs( const std::shared_ptr<Bob> &A, const std::shared_ptr<Bob> &B );

		int Count;
	public:
		int InitialDelay_MultipleBobs, Delay, InitialDelay_OneBob;
	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef EXPLODEBOBS
