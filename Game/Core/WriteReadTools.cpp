#include <small_header.h>
#include "Core/WriteReadTools.h"

#include "Core/PhsxData.h"
#include "Core/Animation/AnimationData_Integer.h"
#include "Core/Animation/AnimationData_Vector.h"
#include "Core/Graphics/VertexFormat.h"
#include "Core/Texture/EzTexture.h"
#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	Vector2 WriteReadTools::ReadVector2( const boost::shared_ptr<BinaryReader> &reader )
	{
		Vector2 vec;
		ReadVector2( reader, vec );
		return vec;
	}

	void WriteReadTools::WriteSafeIndex( const boost::shared_ptr<BinaryWriter> &writer, int index )
	{
		if ( index < 0 )
			index = 0;
		writer->Write( index );
	}

	void WriteReadTools::Write( const boost::shared_ptr<BinaryWriter> &writer, Vector2 v )
	{
		WriteVector2( writer, v );
	}

	void WriteReadTools::WriteOneAnim( const boost::shared_ptr<BinaryWriter> &writer, OneAnim anim )
	{
		if ( anim.Data.empty() )
			writer->Write( -1 );
		else
		{
			writer->Write( static_cast<int>( anim.Data.size() ) );
			for ( size_t i = 0; i < anim.Data.size(); i++ )
				WriteVector2( writer, anim.Data[ i ] );
		}
	}

	void WriteReadTools::ReadOneAnim( const boost::shared_ptr<BinaryReader> &reader, OneAnim &anim )
	{
		int length = reader->ReadInt32();
		if ( length == -1 )
			anim.Data.clear();
		else
		{
			anim.Data = std::vector<Vector2>( length );
			for ( int i = 0; i < length; i++ )
				ReadVector2( reader, anim.Data[ i ] );
		}
	}

	void WriteReadTools::WriteOneAnim( const boost::shared_ptr<BinaryWriter> &writer, OneAnim_Texture anim )
	{
		if ( anim.Data.empty() )
			writer->Write( -1 );
		else
		{
			writer->Write( static_cast<int>( anim.Data.size() ) );
			for ( size_t i = 0; i < anim.Data.size(); i++ )
			{
				writer->Write( anim.Data[ i ]->Name );
				writer->Write( Vector2() ); // Dummy
				writer->Write( Vector2() ); // Dummy
			}
		}
	}

	void WriteReadTools::ReadOneAnim( const boost::shared_ptr<BinaryReader> &reader, OneAnim_Texture &anim )
	{
		int length = reader->ReadInt32();
		if ( length == -1 )
			anim.Data.clear();
		else
		{
			anim.Data = std::vector<boost::shared_ptr<EzTexture> >( length );
			for ( int i = 0; i < length; i++ )
			{
				std::wstring s = reader->ReadString();
				anim.Data[ i ] = Tools::Texture( s );
				reader->ReadVector2(); // Dummy
				reader->ReadVector2(); // Dummy
			}
		}
	}

	void WriteReadTools::WriteVector2( const boost::shared_ptr<BinaryWriter> &writer, Vector2 vec )
	{
		writer->Write( vec.X );
		writer->Write( vec.Y );
	}

	void WriteReadTools::ReadVector3( const boost::shared_ptr<BinaryReader> &reader, Vector3 &vec )
	{
		vec.X = reader->ReadSingle();
		vec.Y = reader->ReadSingle();
		vec.Z = reader->ReadSingle();
	}

	void WriteReadTools::WriteVector3( const boost::shared_ptr<BinaryWriter> &writer, Vector3 vec )
	{
		writer->Write( vec.X );
		writer->Write( vec.Y );
		writer->Write( vec.Z );
	}

	void WriteReadTools::ReadVector2( const boost::shared_ptr<BinaryReader> &reader, Vector2 &vec )
	{
		vec.X = reader->ReadSingle();
		vec.Y = reader->ReadSingle();
	}

	void WriteReadTools::WriteColor( const boost::shared_ptr<BinaryWriter> &writer, Color clr )
	{
		writer->Write( clr.R );
		writer->Write( clr.G );
		writer->Write( clr.B );
		writer->Write( clr.A );
	}

	void WriteReadTools::ReadColor( const boost::shared_ptr<BinaryReader> &reader, Color &clr )
	{
		clr.R = reader->ReadByte();
		clr.G = reader->ReadByte();
		clr.B = reader->ReadByte();
		clr.A = reader->ReadByte();
	}

	void WriteReadTools::WriteVertex( const boost::shared_ptr<BinaryWriter> &writer, MyOwnVertexFormat ver )
	{
		WriteVector2( writer, ver.xy );
		WriteVector2( writer, ver.uv );
		WriteVector3( writer, Vector3( 0, 0, 0 ) );
		WriteColor( writer, ver.TheColor );
	}

	void WriteReadTools::ReadVertex( const boost::shared_ptr<BinaryReader> &reader, MyOwnVertexFormat &ver )
	{
		ReadVector2( reader, ver.xy );
		ReadVector2( reader, ver.uv );
		Vector3 Trash = Vector3( 0, 0, 0 );
		ReadVector3( reader, Trash );
		ReadColor( reader, ver.TheColor );
	}

	void WriteReadTools::WritePhsxData( const boost::shared_ptr<BinaryWriter> &writer, PhsxData data )
	{
		WriteVector2( writer, data.Position );
		WriteVector2( writer, data.Velocity );
		WriteVector2( writer, data.Acceleration );
	}

	void WriteReadTools::ReadPhsxData( const boost::shared_ptr<BinaryReader> &reader, PhsxData &data )
	{
		ReadVector2( reader, data.Position );
		ReadVector2( reader, data.Velocity );
		ReadVector2( reader, data.Acceleration );
	}
}
