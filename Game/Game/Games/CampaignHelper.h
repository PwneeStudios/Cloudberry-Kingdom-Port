#ifndef CAMPAIGNHELPER
#define CAMPAIGNHELPER

#include <string>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Color;
		}
	}
}

namespace CloudberryKingdom
{
	class Localization;
}


using namespace Microsoft::Xna::Framework;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

namespace CloudberryKingdom
{
	class CampaignHelper
	{
	public:
		static std::wstring GetName( int difficulty );
		static std::vector<Color> DifficultyColor;
		static std::vector<Localization::Words> DifficultyNames;
	};
}


#endif	//#ifndef CAMPAIGNHELPER
