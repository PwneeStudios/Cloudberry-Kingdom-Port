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
	
		VerticalData( const boost::shared_ptr<Rand> &Rnd );

		VisualStyles VisualStyle;
	};

	struct UpData : public VerticalData
	{
	
		virtual ~UpData()
		{
#ifdef BOOST_BIN
			OnDestructor( "UpData" );
#endif
		}


		virtual void CalculateKeepUnused( float JumpLevel );

	
		UpData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	};
}


#endif	//#ifndef UPDATA
