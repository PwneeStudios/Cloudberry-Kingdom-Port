#ifndef MAKEDARKBOTTOM
#define MAKEDARKBOTTOM

#include <global_header.h>

namespace CloudberryKingdom
{
	class Level;
}






namespace CloudberryKingdom
{
	class MakeDarkBottom : public MakeFinalDoorVertical
	{
	public:
		MakeDarkBottom( const std::shared_ptr<Level> &level );

		virtual void Phase3();
	};
}


#endif	//#ifndef MAKEDARKBOTTOM
