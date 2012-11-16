#ifndef VIDEO
#define VIDEO

#include <global_header.h>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Content
			{
				class ContentManager;
			}
		}
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Media
			{
				class Video;
			}
		}
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Media
			{
				class VideoPlayer;
			}
		}
	}
}

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class Localization;
}

namespace CloudberryKingdom
{
	class QuadClass;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;







namespace CloudberryKingdom
{
	class MainVideo
	{
	private:
		static std::shared_ptr<ContentManager> Content;

	public:
		static bool Playing;

	private:
		static std::shared_ptr<Video> CurrentVideo;
		static std::shared_ptr<VideoPlayer> VPlayer;

		static std::shared_ptr<EzTexture> VEZTexture;

		static double Duration;
		static DateTime StartTime;

		static bool CanSkip;
		static float LengthUntilUserCanSkip;

		static std::vector<Localization::SubtitleAction*> Subtitles;
		static int SubtitleIndex;
		static std::shared_ptr<QuadClass> SubtitleQuad;

	public:
		static void StartVideo_CanSkipIfWatched( const std::wstring &MovieName );

		static void StartVideo_CanSkipIfWatched_OrCanSkipAfterXseconds( const std::wstring &MovieName, float LengthUntilCanSkip );

	private:
		static void StartVideo( const std::wstring &MovieName, bool CanSkipVideo, float LengthUntilCanSkip );

		/// <summary>
		/// Returns the length of time the video has already been playing in seconds.
		/// </summary>
		/// <returns></returns>
		static double ElapsedTime();

		static bool Paused;
		static void UserInput();

		static void Subtitle();

	public:
		static bool Draw();

	private:
		static bool Cleaned;
	public:
		static void Finish();
	};
}


#endif	//#ifndef VIDEO
