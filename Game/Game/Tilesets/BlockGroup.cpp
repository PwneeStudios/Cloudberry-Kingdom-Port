#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;


namespace CloudberryKingdom
{

	BlockGroup::BlockGroup()
	{
		Dict = std::unordered_map<int, std::vector<PieceQuad*> >();
	}

	void BlockGroup::Add( const std::shared_ptr<PieceQuad> &piece )
	{
		Add( piece->Pillar_Width, piece );
	}

	void BlockGroup::Add( int width, const std::shared_ptr<PieceQuad> &piece )
	{
		if ( !Dict.find( width ) != Dict.end() )
			Dict.insert( make_pair( width, std::vector<PieceQuad*>() ) );

		Dict[ width ].push_back( piece );
	}

	std::shared_ptr<PieceQuad> BlockGroup::Choose( int width )
	{
		return Dict[ SnapWidthUp( width ) ][ 0 ];
	}

	std::shared_ptr<PieceQuad> BlockGroup::Choose( int width, const std::shared_ptr<Rand> &rnd )
	{
		return Dict[ width ].Choose( rnd );
	}

	void BlockGroup::SortWidths()
	{
		std::shared_ptr<std::vector<void*> > list = Dict.Keys::ToList();
		list->Sort();
		Widths = list->ToArray();
	}

	int BlockGroup::SnapWidthUp( float width )
	{
		return SnapWidthUp( width, Widths );
	}

	void BlockGroup::SnapWidthUp( Vector2 &size )
	{
		size.X = SnapWidthUp( size.X, Widths );
	}

	int BlockGroup::SnapWidthUp( float width, std::vector<int> Widths )
	{
		if ( Widths.empty() )
			return static_cast<int>( width );

		int int_width = 0;

		int_width = Widths[ Widths.size() - 1 ];
		for ( int i = 0; i < Widths.size(); i++ )
		{
			if ( width < Widths[ i ] )
			{
				int_width = Widths[ i ];
				break;
			}
		}

		width = int_width;

		return int_width;
	}
}
