#ifndef UPDATA
#define UPDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct VerticalData : public StyleData
	{
	
		enum VisualStyles
		{
			VisualStyles_PILLAR,
			VisualStyles_CASTLE
		};
	
		VerticalData( const std::shared_ptr<Rand> &Rnd );

		VisualStyles VisualStyle;
	};

	struct UpData : public VerticalData
	{
	
		virtual void CalculateKeepUnused( float JumpLevel );

	
		UpData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef UPDATA
