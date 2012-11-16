#ifndef DOWNDATA
#define DOWNDATA

#include "UpData.h"

namespace CloudberryKingdom
{
	class Rand;
}


namespace CloudberryKingdom
{
	class DownData : public VerticalData
	{
	protected:
		virtual void CalculateKeepUnused( float JumpLevel );

	public:
		DownData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef DOWNDATA
