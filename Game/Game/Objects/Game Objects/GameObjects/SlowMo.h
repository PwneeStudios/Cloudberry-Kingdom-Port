#ifndef SLOWMO
#define SLOWMO

#include <global_header.h>

namespace CloudberryKingdom
{

	class SlowMo : public GUI_Panel
	{

	public:
		SlowMo();

	protected:
		virtual void ReleaseBody();

	private:
		int Speed;

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();

	};

}

#endif	//#ifndef SLOWMO
