#ifndef RECORDING
#define RECORDING

#include <small_header.h>

//#include "Core/Animation/SpriteAnim.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
//#include "Core/Tools/CoreMath.h"
//#include "Game/Level/Make/ComputerRecording.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Bob/BobLink.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"
//#include "Game/Player/Hero Physics/Spaceship.h"
//#include "Game/Tools/Globals.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct Recording
	{
		/// <summary>
		/// The file this recording was loaded from.
		/// </summary>
	
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

		void Write( const boost::shared_ptr<BinaryWriter> &writer );
		void Read( const boost::shared_ptr<BinaryReader> &reader );

		int NumBobs;
		std::vector<boost::shared_ptr<ComputerRecording> > Recordings;
		int Length;

		void Draw( const boost::shared_ptr<QuadClass> &BobQuad, int Step, const boost::shared_ptr<Level> &level, std::vector<boost::shared_ptr<SpriteAnimGroup> > AnimGroup, std::vector<boost::shared_ptr<BobLink> > &BobLinks );

		void ConvertToSuperSparse( int Step );

		void Release();

		Recording( int NumBobs, int Length );
		void Init( int NumBobs, int Length );

		void Record( const boost::shared_ptr<Level> &level );

		void MarkEnd( const boost::shared_ptr<Level> &level );
	};
}


#endif	//#ifndef RECORDING
