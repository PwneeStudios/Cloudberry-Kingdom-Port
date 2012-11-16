#include <global_header.h>
namespace CloudberryKingdom
{

	Microsoft::Xna::Framework::Vector2 WriteReadTools::ReadVector2( const std::shared_ptr<BinaryReader> &reader )
	{
		Vector2 vec = Vector2::Zero;
		ReadVector2( reader, vec );
		return vec;
	}

	void WriteReadTools::WriteSafeIndex( const std::shared_ptr<BinaryWriter> &writer, int index )
	{
		if ( index < 0 )
			index = 0;
		writer->Write( index );
	}

	void WriteReadTools::Write( const std::shared_ptr<BinaryWriter> &writer, Vector2 v )
	{
		WriteVector2( writer, v );
	}

	void WriteReadTools::WriteOneAnim( const std::shared_ptr<BinaryWriter> &writer, OneAnim anim )
	{
		if ( anim.Data.empty() )
			writer->Write( -1 );
		else
		{
			writer->Write( anim.Data.size() );
			for ( int i = 0; i < anim.Data.size(); i++ )
				WriteVector2( writer, anim.Data[ i ] );
		}
	}

	void WriteReadTools::ReadOneAnim( const std::shared_ptr<BinaryReader> &reader, OneAnim &anim )
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

	void WriteReadTools::WriteOneAnim( const std::shared_ptr<BinaryWriter> &writer, OneAnim_Texture anim )
	{
		if ( anim.Data.empty() )
			writer->Write( -1 );
		else
		{
			writer->Write( anim.Data.size() );
			for ( int i = 0; i < anim.Data.size(); i++ )
			{
				writer->Write( anim.Data[ i ]->Name );
				writer->Write( Vector2::Zero ); // Dummy
				writer->Write( Vector2::Zero ); // Dummy
			}
		}
	}

	void WriteReadTools::ReadOneAnim( const std::shared_ptr<BinaryReader> &reader, OneAnim_Texture &anim )
	{
		int length = reader->ReadInt32();
		if ( length == -1 )
			anim.Data.clear();
		else
		{
			anim.Data = std::vector<EzTexture*>( length );
			for ( int i = 0; i < length; i++ )
			{
				std::wstring s = reader->ReadString();
				anim.Data[ i ] = Tools::Texture( s );
				reader->ReadVector2(); // Dummy
				reader->ReadVector2(); // Dummy
			}
		}
	}

	void WriteReadTools::WriteVector2( const std::shared_ptr<BinaryWriter> &writer, Vector2 vec )
	{
		writer->Write( vec.X );
		writer->Write( vec.Y );
	}

	void WriteReadTools::ReadVector3( const std::shared_ptr<BinaryReader> &reader, Vector3 &vec )
	{
		vec.X = reader->ReadSingle();
		vec.Y = reader->ReadSingle();
		vec.Z = reader->ReadSingle();
	}

	void WriteReadTools::WriteVector3( const std::shared_ptr<BinaryWriter> &writer, Vector3 vec )
	{
		writer->Write( vec.X );
		writer->Write( vec.Y );
		writer->Write( vec.Z );
	}

	void WriteReadTools::ReadVector2( const std::shared_ptr<BinaryReader> &reader, Vector2 &vec )
	{
		vec.X = reader->ReadSingle();
		vec.Y = reader->ReadSingle();
	}

	void WriteReadTools::WriteColor( const std::shared_ptr<BinaryWriter> &writer, Color clr )
	{
		writer->Write( clr.R );
		writer->Write( clr.G );
		writer->Write( clr.B );
		writer->Write( clr.A );
	}

	void WriteReadTools::ReadColor( const std::shared_ptr<BinaryReader> &reader, Color &clr )
	{
		clr.R = reader->ReadByte();
		clr.G = reader->ReadByte();
		clr.B = reader->ReadByte();
		clr.A = reader->ReadByte();
	}

	void WriteReadTools::WriteVertex( const std::shared_ptr<BinaryWriter> &writer, MyOwnVertexFormat ver )
	{
		WriteVector2( writer, ver.xy );
		WriteVector2( writer, ver.uv );
		WriteVector3( writer, Vector3( 0, 0, 0 ) );
		WriteColor( writer, ver.Color );
	}

	void WriteReadTools::ReadVertex( const std::shared_ptr<BinaryReader> &reader, MyOwnVertexFormat &ver )
	{
		ReadVector2( reader, ver.xy );
		ReadVector2( reader, ver.uv );
		Vector3 Trash = Vector3( 0, 0, 0 );
		ReadVector3( reader, Trash );
		ReadColor( reader, ver.Color );
	}

	void WriteReadTools::WritePhsxData( const std::shared_ptr<BinaryWriter> &writer, PhsxData data )
	{
		WriteVector2( writer, data.Position );
		WriteVector2( writer, data.Velocity );
		WriteVector2( writer, data.Acceleration );
	}

	void WriteReadTools::ReadPhsxData( const std::shared_ptr<BinaryReader> &reader, PhsxData &data )
	{
		ReadVector2( reader, data.Position );
		ReadVector2( reader, data.Velocity );
		ReadVector2( reader, data.Acceleration );
	}
}
