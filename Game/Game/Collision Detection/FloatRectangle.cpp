#include "FloatRectangle.h"
#include "Core/WriteReadTools.h"
#include "Game/Tools/Tools.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	FloatRectangle::FloatRectangle()
	{
	}

	FloatRectangle::FloatRectangle( Vector2 center, Vector2 size )
	{
		Set( center, size );
	}

	void FloatRectangle::Clone( const std::shared_ptr<FloatRectangle> &A )
	{
		Center = A->Center;
		Size = A->Size;
		TR = A->TR;
		BL = A->BL;
	}

	void FloatRectangle::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		WriteReadTools::WriteVector2( writer, TR );
		WriteReadTools::WriteVector2( writer, BL );
		WriteReadTools::WriteVector2( writer, Center );
		WriteReadTools::WriteVector2( writer, Size );

		// Trash =(
		WriteReadTools::WriteVector2( writer, Vector2::Zero );
		WriteReadTools::WriteVector2( writer, Vector2::Zero );
		writer->Write( false );
		writer->Write( false );
	}

	void FloatRectangle::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		WriteReadTools::ReadVector2( reader, TR );
		WriteReadTools::ReadVector2( reader, BL );
		WriteReadTools::ReadVector2( reader, Center );
		WriteReadTools::ReadVector2( reader, Size );

		// Trash =(
		Vector2 trash = Vector2::Zero;
		WriteReadTools::ReadVector2( reader, trash );
		WriteReadTools::ReadVector2( reader, trash );
		reader->ReadBoolean();
		reader->ReadBoolean();
	}

	float FloatRectangle::BoxSize()
	{
		return Tools::BoxSize( TR, BL );
	}

	Microsoft::Xna::Framework::Vector2 FloatRectangle::TL()
	{
		return Vector2( BL.X, TR.Y );
	}

	Microsoft::Xna::Framework::Vector2 FloatRectangle::BR()
	{
		return Vector2( TR.X, BL.Y );
	}

	Microsoft::Xna::Framework::Rectangle FloatRectangle::GetIntRectangle()
	{
		return Rectangle( static_cast<int>( Center.X - Size.X ), static_cast<int>( Center.Y - Size.Y ), 2 * static_cast<int>( Size.X ), 2 * static_cast<int>( Size.Y ) );
	}

	void FloatRectangle::Set( Vector2 center, Vector2 size )
	{
		Center = center;
		Size = size;

		CalcBounds();
	}

	void FloatRectangle::CalcBounds()
	{
		TR = Center + Size;
		BL = Center - Size;
	}

	void FloatRectangle::FromBounds()
	{
		Center = ( TR + BL ) / 2;
		Size = ( TR - BL ) / 2;
	}

	void FloatRectangle::Scale( float scale )
	{
		Size *= scale;
		CalcBounds();
	}
}
