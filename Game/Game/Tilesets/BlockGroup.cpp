#include <global_header.h>

namespace CloudberryKingdom
{

	BlockGroup::BlockGroup()
	{
		Dict = std::map<int, std::vector<std::shared_ptr<PieceQuad> > >();
	}

	void BlockGroup::Add( const std::shared_ptr<PieceQuad> &piece )
	{
		Add( piece->Pillar_Width, piece );
	}

	void BlockGroup::Add( int width, const std::shared_ptr<PieceQuad> &piece )
	{
		if ( Dict.find( width ) == Dict.end() )
			Dict.insert( std::make_pair( width, std::vector<std::shared_ptr<PieceQuad> >() ) );

		Dict[ width ].push_back( piece );
	}

	std::shared_ptr<PieceQuad> BlockGroup::Choose( int width )
	{
		return Dict[ SnapWidthUp( static_cast<float>( width ) ) ][ 0 ];
	}

	std::shared_ptr<PieceQuad> BlockGroup::Choose( int width, const std::shared_ptr<Rand> &rnd )
	{
		return ListExtension::Choose( Dict[ width ], rnd );
	}

	void BlockGroup::SortWidths()
	{
		// FIXME: Check for isomorphic implementation.
		Widths.clear();
		GetKeys( Dict, Widths );
		std::sort( Widths.begin(), Widths.end() );
	}

	int BlockGroup::SnapWidthUp( float width )
	{
		return SnapWidthUp( width, Widths );
	}

	void BlockGroup::SnapWidthUp( Vector2 &size )
	{
		size.X = static_cast<float>( SnapWidthUp( size.X, Widths ) );
	}

	int BlockGroup::SnapWidthUp( float width, std::vector<int> Widths )
	{
		if ( Widths.empty() )
			return static_cast<int>( width );

		int int_width = 0;

		int_width = Widths[ Widths.size() - 1 ];
		for ( size_t i = 0; i < Widths.size(); i++ )
		{
			if ( width < Widths[ i ] )
			{
				int_width = Widths[ i ];
				break;
			}
		}

		width = static_cast<float>( int_width );

		return int_width;
	}
}
