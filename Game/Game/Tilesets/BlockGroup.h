#ifndef BLOCKGROUP
#define BLOCKGROUP

#include <global_header.h>

namespace CloudberryKingdom
{
	class PieceQuad;
}

namespace CloudberryKingdom
{
	class Rand;
}













namespace CloudberryKingdom
{
	class BlockGroup
	{
	public:
		std::unordered_map<int, std::vector<PieceQuad*> > Dict;
		std::vector<int> Widths;

		BlockGroup();

		void Add( const std::shared_ptr<PieceQuad> &piece );

		void Add( int width, const std::shared_ptr<PieceQuad> &piece );

		std::shared_ptr<PieceQuad> Choose( int width );

		std::shared_ptr<PieceQuad> Choose( int width, const std::shared_ptr<Rand> &rnd );

		void SortWidths();

		int SnapWidthUp( float width );
		void SnapWidthUp( Vector2 &size );

		static int SnapWidthUp( float width, std::vector<int> Widths );
	};
}


#endif	//#ifndef BLOCKGROUP
