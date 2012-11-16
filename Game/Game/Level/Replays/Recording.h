#ifndef RECORDING
#define RECORDING

#include <string>
#include <vector>
#include <tchar.h>

namespace CloudberryKingdom
{
	class ComputerRecording;
}

namespace CloudberryKingdom
{
	class BobLink;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class SpriteAnimGroup;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Recording
	{
		/// <summary>
		/// The file this recording was loaded from.
		/// </summary>
	public:
		std::wstring SourceFile;

		/// <summary>
		/// Returns the current working directory for where .rec files are stored.
		/// Do not save here if you wish to override a .rec file in future builds.
		/// </summary>
		static std::wstring DefaultRecordingDirectory();

		/// <summary>
		/// Returns the directory where the source .rec files are stored.
		/// Save here if you wish to override a .rec file in future builds.
		/// </summary>
		/// <returns></returns>
		static std::wstring SourceRecordingDirectory();

		/// <summary>
		/// Save the recording to a .rec file
		/// </summary>
		/// <param name="Bin">Whether the file is saved to the bin or the original project content directory.</param>
		void Save( const std::wstring &file, bool Bin );

		/// <summary>
		/// Load into the level information from a .rec file.
		/// </summary>
		void Load( const std::wstring &file );

		void Write( const std::shared_ptr<BinaryWriter> &writer );
		void Read( const std::shared_ptr<BinaryReader> &reader );

		int NumBobs;
		std::vector<ComputerRecording*> Recordings;
		int Length;

		Vector2 BoxSize;

		void Draw( const std::shared_ptr<QuadClass> &BobQuad, int Step, const std::shared_ptr<Level> &level, std::vector<SpriteAnimGroup*> AnimGroup, std::vector<BobLink*> &BobLinks );

		void ConvertToSuperSparse();

		void Release();

		Recording( int NumBobs, int Length );
		void Init( int NumBobs, int Length );

		void Record( const std::shared_ptr<Level> &level );

		void MarkEnd( const std::shared_ptr<Level> &level );
	};
}


#endif	//#ifndef RECORDING
