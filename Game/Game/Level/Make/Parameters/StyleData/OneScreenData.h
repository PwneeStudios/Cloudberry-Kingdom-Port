#ifndef ONESCREENDATA
#define ONESCREENDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	class OneScreenData : public StyleData
	{
	public:
		Vector2 CamShift;

		OneScreenData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	private:
		void InitializeInstanceFields();
	};
}

#endif	//#ifndef ONESCREENDATA
