#ifndef DOWNDATA
#define DOWNDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Rand;
}


namespace CloudberryKingdom
{
	struct DownData : public VerticalData
	{
	
		virtual void CalculateKeepUnused( float JumpLevel );

	
		DownData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef DOWNDATA
