#ifndef MAKETHING
#define MAKETHING

namespace CloudberryKingdom
{
	class MakeThing
	{
	public:
		MakeThing();

		virtual void Phase1();
		virtual void Phase2();
		virtual void Phase3();
		virtual void Cleanup();
	};
}


#endif	//#ifndef MAKETHING
