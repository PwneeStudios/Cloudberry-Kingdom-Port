#include <small_header.h>
#include "Game/Tilesets/BlockGroup.h"

#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Tools/Random.h"
#include "Game/Tools/Tools.h"


#include <Hacks\List.h>
#include <Hacks\Dict.h>

namespace CloudberryKingdom
{

	BlockGroup::BlockGroup()
	{
		Dict = std::map<int, std::vector<boost::shared_ptr<PieceQuad> > >();
	}

	void BlockGroup::Add( const boost::shared_ptr<PieceQuad> &piece )
	{
		Add( piece->Pillar_Width, piece );
	}

	void BlockGroup::Add( int width, const boost::shared_ptr<PieceQuad> &piece )
	{
		if ( Dict.find( width ) == Dict.end() )
			Dict.insert( std::make_pair( width, std::vector<boost::shared_ptr<PieceQuad> >() ) );

		Dict[ width ].push_back( piece );
	}

	boost::shared_ptr<PieceQuad> BlockGroup::Choose( int width )
	{
		return Dict[ SnapWidthUp( static_cast<float>( width ) ) ][ 0 ];
	}

	boost::shared_ptr<PieceQuad> BlockGroup::Choose( int width, const boost::shared_ptr<Rand> &rnd )
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
