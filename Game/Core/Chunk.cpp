#include <global_header.h>


namespace CloudberryKingdom
{

	std::shared_ptr<Chunks> Chunks::Get( std::vector<unsigned char> Data )
	{
		return std::make_shared<Chunks>( Data );
	}

	Chunks::Chunks( std::vector<unsigned char> Data )
	{
		this->Data = Data;
	}

	std::shared_ptr<IEnumerator<Chunk*> > Chunks::GetEnumerator()
	{
		return std::make_shared<ChunkEnumerator>( Data );
	}

	std::shared_ptr<IEnumerator> Chunks::IEnumerable_GetEnumerator()
	{
		return std::make_shared<ChunkEnumerator>( Data );
	}

	ChunkEnumerator::ChunkEnumerator( std::vector<unsigned char> Data )
	{
		InitializeInstanceFields();
		this->Data = Data;
		DataLength = Data.size();
	}

	ChunkEnumerator::ChunkEnumerator( std::vector<unsigned char> Data, int Start, int DataLength )
	{
		InitializeInstanceFields();
		this->Data = Data;
		this->Position = Start;
		this->DataLength = DataLength;
	}

	const std::shared_ptr<Chunk> &ChunkEnumerator::getCurrent() const
	{
		return _Current;
	}

	bool ChunkEnumerator::MoveNext()
	{
		if ( Position >= DataLength )
			return false;

		int Type = BitConverter::ToInt32( Data, Position );
		int Length = BitConverter::ToInt32( Data, Position + 4 );

		if ( Type < 0 )
			throw std::exception( _T( "Chunk type must be non-negative. Are you loading a non-chunked file?" ) );
		if ( Length <= 0 )
			throw std::exception( _T( "Chunk length must be strictly positive. Are you loading a non-chunked file?" ) );

		_Current = std::make_shared<Chunk>( Length );
		_Current->Copy( Data, Position, Length );
		_Current->Type = Type;
		_Current->Length = Length;

		Position += Length;

		return true;
	}

	void ChunkEnumerator::Reset()
	{
		Position = 0;
		_Current.reset();
	}

	const std::shared_ptr<Object> &ChunkEnumerator::getIEnumerator_Current() const
	{
		return getCurrent();
	}

	ChunkEnumerator::~ChunkEnumerator()
	{
		InitializeInstanceFields();
		return;
	}

	void ChunkEnumerator::InitializeInstanceFields()
	{
		Position = 0;
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

	std::shared_ptr<IEnumerator<Chunk*> > Chunk::GetEnumerator()
	{
		return std::make_shared<ChunkEnumerator>( Buffer, 8, Length );
	}

	std::shared_ptr<IEnumerator> Chunk::IEnumerable_GetEnumerator()
	{
		return std::make_shared<ChunkEnumerator>( Buffer, 8, Length );
	}

	void Chunk::Expand()
	{
		std::vector<unsigned char> OldBuffer = Buffer;
		Buffer = std::vector<unsigned char>( OldBuffer.Length * 2 );

		for ( int i = 0; i < Position; i++ )
			Buffer[ i ] = OldBuffer[ i ];

		Length = Buffer.size();
	}

	void Chunk::SetTypeAndLength()
	{
		int Size = Position;
		Position = 0;

		Write( BitConverter::GetBytes( Type ) );
		Write( BitConverter::GetBytes( Size ) );

		Position = Size;
	}

	void Chunk::Finish( const std::shared_ptr<BinaryWriter> &writer )
	{
		SetTypeAndLength();
		writer->Write( Buffer, 0, Position );
	}

	void Chunk::Finish( const std::shared_ptr<Chunk> &ParentChunk )
	{
		SetTypeAndLength();
		ParentChunk->Write( Buffer, 0, Position );
	}

	void Chunk::EnsureRoom( int Size )
	{
		// Make sure we don't write past the end of the buffer
		while ( Position + Size >= Buffer.size() )
			Expand();
	}

	void Chunk::Write( std::vector<unsigned char> Bytes )
	{
		EnsureRoom( Bytes.size() );

		// Write the bytes
		for ( int i = Position; i < Position + Bytes.size(); i++ )
			Buffer[ i ] = Bytes[ i - Position ];

		Position += Bytes.size();
	}

	void Chunk::Write( std::vector<unsigned char> Bytes, int StartIndex, int BytesToCopy )
	{
		EnsureRoom( BytesToCopy );

		for ( int i = StartIndex; i < StartIndex + BytesToCopy; i++ )
			Buffer[ Position + i - StartIndex ] = Bytes[ i ];

		Position += BytesToCopy;
	}

	void Chunk::Copy( std::vector<unsigned char> Bytes, int StartIndex, int BytesToCopy )
	{
		Position = 0;
		EnsureRoom( BytesToCopy );

		Position = 8;

		for ( int i = StartIndex; i < StartIndex + BytesToCopy; i++ )
			Buffer[ i - StartIndex ] = Bytes[ i ];
	}

	void Chunk::Write( bool val )
	{
		Write( BitConverter::GetBytes( val ) );
	}

	void Chunk::Write( int val )
	{
		Write( BitConverter::GetBytes( val ) );
	}

	void Chunk::Write( float val )
	{
		Write( BitConverter::GetBytes( val ) );
	}

	void Chunk::Write( const std::wstring &val )
	{
		int StringLength = System::Text::Encoding::UTF8->GetByteCount( val );

		Write( StringLength );
		Write( System::Text::Encoding::UTF8->GetBytes( val ) );
	}

	bool Chunk::ReadBool()
	{
		bool val = BitConverter::ToBoolean( Buffer, Position );
		Position += 1;

		return val;
	}

	int Chunk::ReadInt()
	{
		int val = BitConverter::ToInt32( Buffer, Position );
		Position += 4;

		return val;
	}

	float Chunk::ReadFloat()
	{
		float val = BitConverter::ToSingle( Buffer, Position );
		Position += 4;

		return val;
	}

	std::wstring Chunk::ReadString()
	{
		int StringLength = ReadInt();
		std::shared_ptr<std::wstring> val = System::Text::Encoding::UTF8->GetString( Buffer, Position, StringLength );

		Position += StringLength;

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

		chunk->Finish( this );
	}

	void Chunk::WriteSingle( int type, bool val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( this );
	}

	void Chunk::WriteSingle( int type, float val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( this );
	}

	void Chunk::WriteSingle( int type, const std::wstring &val )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = type;

		chunk->Write( val );

		chunk->Finish( this );
	}

	void Chunk::InitializeInstanceFields()
	{
		Type = -1;
		Length = 0;
		Position = 4 + 4;
	}
}
