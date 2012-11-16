#ifndef BACKGROUNDFLOATER_STATIONARY
#define BACKGROUNDFLOATER_STATIONARY

#include <global_header.h>

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class BackgroundFloaterList;
}



namespace CloudberryKingdom
{
	class BackgroundFloater_Stationary : public BackgroundFloater
	{
	public:
		BackgroundFloater_Stationary( const std::shared_ptr<Level> &level );

		virtual void PhsxStep( const std::shared_ptr<BackgroundFloaterList> &list );

		virtual void Draw();
	};
}


#endif	//#ifndef BACKGROUNDFLOATER_STATIONARY
