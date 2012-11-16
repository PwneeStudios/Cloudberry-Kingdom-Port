#ifndef UPDATA
#define UPDATA

#include "StyleData.h"

namespace CloudberryKingdom
{
	class Rand;
}


namespace CloudberryKingdom
{
	class VerticalData : public StyleData
	{
	public:
		enum VisualStyles
		{
			VisualStyles_PILLAR,
			VisualStyles_CASTLE
		};
	public:
		VerticalData( const std::shared_ptr<Rand> &Rnd );

		VisualStyles VisualStyle;
	};

	class UpData : public VerticalData
	{
	protected:
		virtual void CalculateKeepUnused( float JumpLevel );

	public:
		UpData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef UPDATA
