#ifndef CHUNK
#define CHUNK

#include <global_header.h>

#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"

namespace CloudberryKingdom
{
	struct Chunks /*: public IEnumerable<Chunk*>*/
	{
	
		static boost::shared_ptr<Chunks> Get( std::vector<unsigned char> Data );
		static boost::shared_ptr<Chunks> Get( boost::shared_ptr<Chunk> Chunk );

	
		std::vector<unsigned char> Data;

		int _Position;
		int _StartPosition;

	
		Chunks( std::vector<unsigned char> Data, int offset );

		void StartGettingChunks();
		const bool HasChunk();
		const boost::shared_ptr<Chunk> GetChunk();

		/*boost::shared_ptr<IEnumerator<Chunk*> > GetEnumerator();

		boost::shared_ptr<IEnumerator> IEnumerable_GetEnumerator();*/
	};

	/*struct ChunkEnumerator : public IEnumerator<Chunk*>
	{
	
		std::vector<unsigned char> Data;
		int Position;
		int DataLength;

	
		ChunkEnumerator( std::vector<unsigned char> Data );

		ChunkEnumerator( std::vector<unsigned char> Data, int Start, int DataLength );

	
		boost::shared_ptr<Chunk> _Current;
	
		const boost::shared_ptr<Chunk> &getCurrent() const;

		bool MoveNext();

		void Reset();

		const boost::shared_ptr<Object> &getIEnumerator_Current() = IEnumerator::Current::get const;

		~ChunkEnumerator();

	
		void InitializeInstanceFields();
	};*/

	struct Chunk /*: public IEnumerable<Chunk*>*/
	{
	
		int Type;
		int Length;

	
		std::vector<unsigned char> Buffer;
		int Position;

	
		Chunk();

		Chunk( int Capacity );

	
		void Initialize( int Capacity );

	
		/*boost::shared_ptr<IEnumerator<Chunk*> > GetEnumerator();

		boost::shared_ptr<IEnumerator> IEnumerable_GetEnumerator();*/

		/// <summary>
		/// Double the size of the buffer without losing any data.
		/// </summary>
		void Expand();

	
		void SetTypeAndLength();

	
		void Finish( const boost::shared_ptr<BinaryWriter> &writer );
		void Finish( Chunk &ParentChunk );

	
		void EnsureRoom( int Size );

	
		void Write( const unsigned char *data, int length );
		void Write( const unsigned char *data, int startIndex, int length );

		/// <summary>
		/// Copy bytes from another chunk. This will overwrite the Type and Length bytes for this chunk.
		/// </summary>
		/// <param name="data">Bytes from the other chunk</param>
		/// <param name="StartIndex">StartIndex in the other chunk's buffer.</param>
		/// <param name="BytesToCopy">Number of bytes to copy from the other chunk's buffer.</param>
		void Copy( const unsigned char *data, int StartIndex, int BytesToCopy );

		void Write( bool val );
		void Write( int val );
		void Write( float val );
		void Write( const std::wstring &val );

		bool ReadBool();
		int ReadInt();
		float ReadFloat();
		std::wstring ReadString();

		void ReadSingle( bool &val );
		void ReadSingle( int &val );
		void ReadSingle( float &val );
		void ReadSingle( std::wstring &val );
		void ReadSingle( Keys &val );

		static void WriteSingle( const boost::shared_ptr<BinaryWriter> &writer, int type, int val );
		static void WriteSingle( const boost::shared_ptr<BinaryWriter> &writer, int type, bool val );
		static void WriteSingle( const boost::shared_ptr<BinaryWriter> &writer, int type, float val );
		static void WriteSingle( const boost::shared_ptr<BinaryWriter> &writer, int type, const std::wstring &val );
		static void WriteSingle( const boost::shared_ptr<BinaryWriter> &writer, int type, Keys val );

		void WriteSingle( int type, int val );
		void WriteSingle( int type, bool val );
		void WriteSingle( int type, float val );
		void WriteSingle( int type, const std::wstring &val );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CHUNK
