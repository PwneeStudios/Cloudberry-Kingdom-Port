#ifndef CONTROLSCREEN
#define CONTROLSCREEN

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}





namespace CloudberryKingdom
{
	class ControlScreen : public CkBaseMenu
	{
	private:
		std::shared_ptr<QuadClass> BackgroundQuad;

	public:
		ControlScreen( int Control );

#if defined(PC_VERSION)
	private:
		std::shared_ptr<QuadClass> MakeQuad( Keys key );
#endif
	public:
		virtual void Init();

#if defined(PC_VERSION)
	private:
		void SetPos();
#endif

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CONTROLSCREEN
