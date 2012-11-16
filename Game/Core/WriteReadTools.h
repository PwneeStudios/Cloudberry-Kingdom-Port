#ifndef WRITEREADTOOLS
#define WRITEREADTOOLS

#include <global_header.h>

using namespace Microsoft::Xna::Framework;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class WriteReadTools
	{
	public:
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static Vector2 ReadVector2(this BinaryReader reader)
		static Vector2 ReadVector2( const std::shared_ptr<BinaryReader> &reader );

		/// <summary>
		/// Writes the index, ensuring non-negativity.
		/// </summary>
//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void WriteSafeIndex(this BinaryWriter writer, int index)
		static void WriteSafeIndex( const std::shared_ptr<BinaryWriter> &writer, int index );

//C# TO C++ CONVERTER TODO TASK: Extension methods are not available in C++:
//ORIGINAL LINE: public static void Write(this BinaryWriter writer, Vector2 v)
		static void Write( const std::shared_ptr<BinaryWriter> &writer, Vector2 v );

		static void WriteOneAnim( const std::shared_ptr<BinaryWriter> &writer, OneAnim anim );

		static void ReadOneAnim( const std::shared_ptr<BinaryReader> &reader, OneAnim &anim );

		static void WriteOneAnim( const std::shared_ptr<BinaryWriter> &writer, OneAnim_Texture anim );

		static void ReadOneAnim( const std::shared_ptr<BinaryReader> &reader, OneAnim_Texture &anim );


		static void WriteVector2( const std::shared_ptr<BinaryWriter> &writer, Vector2 vec );

		static void ReadVector3( const std::shared_ptr<BinaryReader> &reader, Vector3 &vec );

		static void WriteVector3( const std::shared_ptr<BinaryWriter> &writer, Vector3 vec );

		static void ReadVector2( const std::shared_ptr<BinaryReader> &reader, Vector2 &vec );

		static void WriteColor( const std::shared_ptr<BinaryWriter> &writer, Color clr );

		static void ReadColor( const std::shared_ptr<BinaryReader> &reader, Color &clr );

		static void WriteVertex( const std::shared_ptr<BinaryWriter> &writer, MyOwnVertexFormat ver );

		static void ReadVertex( const std::shared_ptr<BinaryReader> &reader, MyOwnVertexFormat &ver );

		static void WritePhsxData( const std::shared_ptr<BinaryWriter> &writer, PhsxData data );

		static void ReadPhsxData( const std::shared_ptr<BinaryReader> &reader, PhsxData &data );
	};
}


#endif	//#ifndef WRITEREADTOOLS
