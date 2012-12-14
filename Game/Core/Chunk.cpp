#include <global_header.h>


namespace CloudberryKingdom
{

	std::shared_ptr<Chunks> Chunks::Get( std::vector<unsigned char> Data )
	{
		return std::make_shared<Chunks>( Data, 0 );
	}

	std::shared_ptr<Chunks> Chunks::Get( std::shared_ptr<Chunk> Chunk )
	{
		return std::make_shared<Chunks>( Chunk->Buffer, 8 );
	}

	Chunks::Chunks( std::vector<unsigned char> Data, int offset ) :
		_StartPosition( offset )
	{
		_Position = 0;
		_StartPosition = 0;

		this->Data = Data;
	}

	void Chunks::StartGettingChunks()
	{
		_Position = _StartPosition;
	}

	const bool Chunks::HasChunk()
	{
		if ( _Position >= static_cast<int>( Data.size() ) )
			return false;
		else
			return true;
	}

	const std::shared_ptr<Chunk> Chunks::GetChunk()
	{
		//int Type = BitConverter::ToInt32( Data, _Position );
		//int Length = BitConverter::ToInt32( Data, _Position + 4 );
		int Type = *reinterpret_cast<int*>( &Data[_Position] );
		int Length = *reinterpret_cast<int*>( &Data[_Position + 4] );

		// FIXME: Implement exceptions?
		//if ( Type < 0 )
		//	throw std::exception( _T( "Chunk type must be non-negative. Are you loading a non-chunked file?" ) );
		//if ( Length <= 0 )
		//	throw std::exception( _T( "Chunk length must be strictly positive. Are you loading a non-chunked file?" ) );

		std::shared_ptr<Chunk> _Current = std::make_shared<Chunk>( Length );
		_Current->Copy( Data.data(), _Position, Length );
		_Current->Type = Type;
		_Current->Length = Length;

		_Position += Length;

		return _Current;
	}

	Chunk::Chunk()
	{
		InitializeInstanceFields();
		Initialize( 100 );
	}

	Chunk::Chunk( int Capacity )
	{
		InitializeInstanceFields();
		Initialize( Capacity );
	}

	void Chunk::Initialize( int Capacity )
	{
		Buffer = std::vector<unsigned char>( Capacity );
		Length = Capacity;
	}

	void Chunk::Expand()
	{
		std::vector<unsigned char> OldBuffer = Buffer;
		Buffer = std::vector<unsigned char>( OldBuffer.size() * 2 );

		for ( int i = 0; i < Position; i++ )
			Buffer[ i ] = OldBuffer[ i ];

		Length = Buffer.size();
	}

	void Chunk::SetTypeAndLength()
	{
		int Size = Position;
		Position = 0;

		Write( Type );
		Write( Size );
		/*Write( BitConverter::GetBytes( Type ) );
		Write( BitConverter::GetBytes( Size ) );*/

		Position = Size;
	}

	void Chunk::Finish( const std::shared_ptr<BinaryWriter> &writer )
	{
		SetTypeAndLength();
		writer->Write( Buffer.data(), 0, Position );
	}

	void Chunk::Finish( Chunk &ParentChunk )
	{
		SetTypeAndLength();
		ParentChunk.Write( Buffer.data(), 0, Position );
	}

	void Chunk::EnsureRoom( int Size )
	{
		// Make sure we don't write past the end of the buffer
		while ( Position + Size >= static_cast<int>( Buffer.size() ) )
			Expand();
	}

	void Chunk::Write( const unsigned char *data, int length )
	{
		EnsureRoom( length );

		// Write the bytes
		for ( int i = Position; i < Position + length; i++ )
			Buffer[ i ] = data[ i - Position ];

		Position += length;
	}

	void Chunk::Write( const unsigned char *data, int startIndex, int length )
	{
		EnsureRoom( length );

		// Write the bytes
		for ( int i = startIndex; i < startIndex + length; i++ )
			Buffer[ Position + i - startIndex ] = data[ i ];

		Position += length;
	}

	void Chunk::Copy( const unsigned char *data, int StartIndex, int BytesToCopy )
	{
		Position = 0;
		EnsureRoom( BytesToCopy );

		Position = 8;

		for ( int i = StartIndex; i < StartIndex + BytesToCopy; i++ )
			Buffer[ i - StartIndex ] = data[ i ];
	}

	void Chunk::Write( bool val )
	{
		Write( reinterpret_cast<unsigned char *>( &val ), sizeof( bool ) );
		//Write( BitConverter::GetBytes( val ) );
	}

	void Chunk::Write( int val )
	{
		Write( reinterpret_cast<unsigned char *>( &val ), sizeof( int ) );
		//Write( BitConverter::GetBytes( val ) );
	}

	void Chunk::Write( float val )
	{
		Write( reinterpret_cast<unsigned char *>( &val ), sizeof( float ) );
		//Write( BitConverter::GetBytes( val ) );
	}

	void Chunk::Write( const std::wstring &val )
	{
		int StringLength = val.size();
		Write( StringLength );
		Write( reinterpret_cast<const unsigned char *>( val.c_str() ), StringLength * sizeof( wchar_t ) );
		//int StringLength = System::Text::Encoding::UTF8->GetByteCount( val );

		//Write( StringLength );
		//Write( System::Text::Encoding::UTF8->GetBytes( val ) );
	}

	bool Chunk::ReadBool()
	{
		bool val = *reinterpret_cast<bool *>( &Buffer[ Position ] );
		Position += sizeof( bool );
		//bool val = BitConverter::ToBoolean( Buffer, Position );
		//Position += 1;

		return val;
	}

	int Chunk::ReadInt()
	{
		int val = *reinterpret_cast<int *>( &Buffer[ Position ] );
		Position += sizeof( int );
		//int val = BitConverter::ToInt32( Buffer, Position );
		//Position += 4;

		return val;
	}

	float Chunk::ReadFloat()
	{
		float val = *reinterpret_cast<float *>( &Buffer[ Position ] );
		Position += sizeof( float );
		//float val = BitConverter::ToSingle( Buffer, Position );
		//Position += 4;

		return val;
	}

	std::wstring Chunk::ReadString()
	{
		int StringLength = ReadInt();
		const wchar_t *start = reinterpret_cast<const wchar_t *>(&Buffer[Position]);
		std::wstring val(start, start + StringLength);
		Position += StringLength * sizeof(wchar_t);
		//std::shared_ptr<std::wstring> val = System::Text::Encoding::UTF8->GetString( Buffer, Position, StringLength );

		//Position += StringLength;

		return val;
	}

	void Chunk::ReadSingle( bool &val )
	{
		val = ReadBool();
	}

	void Chunk::ReadSingle( int &val )
	{
		val = ReadInt();
	}

	void Chunk::ReadSingle( float &val )
	{
		val = ReadFloat();
	}

	void Chunk::ReadSingle( std::wstring &val )
	{
		val = ReadString();
	}

	void Chunk::ReadSingle( Keys &val )
	{
		val = static_cast<Keys>( ReadInt() );
	}

	void Chunk::WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, int val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( writer );
	}

	void Chunk::WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, bool val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( writer );
	}

	void Chunk::WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, float val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( writer );
	}

	void Chunk::WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, const std::wstring &val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( writer );
	}

	void Chunk::WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, Keys val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( static_cast<int>( val ) );

		chunk->Finish( writer );
	}

	void Chunk::WriteSingle( int type, int val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( *this );
	}

	void Chunk::WriteSingle( int type, bool val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( *this );
	}

	void Chunk::WriteSingle( int type, float val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( *this );
	}

	void Chunk::WriteSingle( int type, const std::wstring &val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( *this );
	}

	void Chunk::InitializeInstanceFields()
	{
		Type = -1;
		Length = 0;
		Position = 4 + 4;
	}
}
