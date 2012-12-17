#ifndef MAKEDARKBOTTOM
#define MAKEDARKBOTTOM

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Level;
}

namespace CloudberryKingdom
{
	struct MakeDarkBottom : public MakeFinalDoorVertical
	{
	
		MakeDarkBottom( const boost::shared_ptr<Level> &level );

		virtual void Phase3();
	};
}


#endif	//#ifndef MAKEDARKBOTTOM
