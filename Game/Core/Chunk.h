#ifndef CHUNK
#define CHUNK

#include <global_header.h>

namespace CloudberryKingdom
{
	class Chunks /*: public IEnumerable<Chunk*>*/
	{
	public:
		static std::shared_ptr<Chunks> Get( std::vector<unsigned char> Data );

	private:
		std::vector<unsigned char> Data;
	public:
		Chunks( std::vector<unsigned char> Data );

		/*std::shared_ptr<IEnumerator<Chunk*> > GetEnumerator();

		std::shared_ptr<IEnumerator> IEnumerable_GetEnumerator();*/
	};

	/*class ChunkEnumerator : public IEnumerator<Chunk*>
	{
	private:
		std::vector<unsigned char> Data;
		int Position;
		int DataLength;

	public:
		ChunkEnumerator( std::vector<unsigned char> Data );

		ChunkEnumerator( std::vector<unsigned char> Data, int Start, int DataLength );

	private:
		std::shared_ptr<Chunk> _Current;
	public:
		const std::shared_ptr<Chunk> &getCurrent() const;

		bool MoveNext();

		void Reset();

		const std::shared_ptr<Object> &getIEnumerator_Current() = IEnumerator::Current::get const;

		~ChunkEnumerator();

	private:
		void InitializeInstanceFields();
	};*/

	class Chunk /*: public IEnumerable<Chunk*>*/
	{
	public:
		int Type;
		int Length;

	private:
		std::vector<unsigned char> Buffer;
		int Position;

	public:
		Chunk();

		Chunk( int Capacity );

	private:
		void Initialize( int Capacity );

	public:
		/*std::shared_ptr<IEnumerator<Chunk*> > GetEnumerator();

		std::shared_ptr<IEnumerator> IEnumerable_GetEnumerator();*/

		/// <summary>
		/// Double the size of the buffer without losing any data.
		/// </summary>
		void Expand();

	private:
		void SetTypeAndLength();

	public:
		void Finish( const std::shared_ptr<BinaryWriter> &writer );
		void Finish( const std::shared_ptr<Chunk> &ParentChunk );

	private:
		void EnsureRoom( int Size );

	public:
		void Write( std::vector<unsigned char> Bytes );
		void Write( std::vector<unsigned char> Bytes, int StartIndex, int BytesToCopy );

		/// <summary>
		/// Copy bytes from another chunk. This will overwrite the Type and Length bytes for this chunk.
		/// </summary>
		/// <param name="Bytes">Bytes from the other chunk</param>
		/// <param name="StartIndex">StartIndex in the other chunk's buffer.</param>
		/// <param name="BytesToCopy">Number of bytes to copy from the other chunk's buffer.</param>
		void Copy( std::vector<unsigned char> Bytes, int StartIndex, int BytesToCopy );

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

		static void WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, int val );
		static void WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, bool val );
		static void WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, float val );
		static void WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, const std::wstring &val );
		static void WriteSingle( const std::shared_ptr<BinaryWriter> &writer, int type, Keys val );

		void WriteSingle( int type, int val );
		void WriteSingle( int type, bool val );
		void WriteSingle( int type, float val );
		void WriteSingle( int type, const std::wstring &val );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CHUNK
