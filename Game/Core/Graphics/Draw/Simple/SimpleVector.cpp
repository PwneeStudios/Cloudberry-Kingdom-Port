#include <global_header.h>




namespace CloudberryKingdom
{

	void SimpleVector::RotateRight()
	{
		Tools::Swap( Pos.X, Pos.Y );
		Tools::Swap( Vertex.uv.X, Vertex.uv.X );
	}

	void SimpleVector::RotateLeft()
	{
		RotateRight();
		Pos.X *= -1;
		Vertex.uv.X *= -1;
	}

	void SimpleVector::Release()
	{
		AnimData.Release();
	}

const std::wstring* tempVector[] = { _T( "Pos" ), _T( "Vertex" ) };
std::vector<std::wstring> SimpleVector::_bits_to_save = std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );

	void SimpleVector::WriteCode( const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer )
	{
		Tools::WriteFieldsToCode( *this, prefix, writer, _bits_to_save );
	}

	void SimpleVector::Write( const std::shared_ptr<StreamWriter> &writer )
	{
		Tools::WriteFields( *this, writer, _bits_to_save );
	}

	void SimpleVector::Read( const std::shared_ptr<StreamReader> &reader )
	{
		*this = static_cast<SimpleVector>( Tools::ReadFields( *this, reader ) );
	}
}
