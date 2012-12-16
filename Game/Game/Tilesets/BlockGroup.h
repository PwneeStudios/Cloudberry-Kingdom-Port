#ifndef BLOCKGROUP
#define BLOCKGROUP

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BlockGroup
	{
	
		std::map<int, std::vector<boost::shared_ptr<PieceQuad> > > Dict;
		std::vector<int> Widths;

		BlockGroup();

		void Add( const boost::shared_ptr<PieceQuad> &piece );

		void Add( int width, const boost::shared_ptr<PieceQuad> &piece );

		boost::shared_ptr<PieceQuad> Choose( int width );

		boost::shared_ptr<PieceQuad> Choose( int width, const boost::shared_ptr<Rand> &rnd );

		void SortWidths();

		int SnapWidthUp( float width );
		void SnapWidthUp( Vector2 &size );

		static int SnapWidthUp( float width, std::vector<int> Widths );
	};
}


#endif	//#ifndef BLOCKGROUP
