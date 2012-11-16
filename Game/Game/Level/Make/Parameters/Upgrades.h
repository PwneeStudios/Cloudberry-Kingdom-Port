#ifndef UPGRADES
#define UPGRADES

#include "../Game/Objects/AutoGen.h"
#include "../Game/Tools/Globals.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "../Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "../Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "../Core/Text/EzText.h"
#include <cmath>

namespace CloudberryKingdom
{
	class LevelGenData;
}

namespace CloudberryKingdom
{
	class StyleData;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	// Stores the level of each obstacles
	// CalcGenData translates this into actual parameters
	class Upgrades
	{
	public:
		std::vector<float> UpgradeLevels;

		Upgrades();

		Upgrades( const std::shared_ptr<Upgrades> &u );

	private:
		void Initialize();


	public:
		void CopyFrom( const std::shared_ptr<Upgrades> &u );

		/// <summary>
		/// Access the specified upgrade level
		/// </summary>
		/// <param name="upgrade">The specified upgrade type</param>
		float &operator []( Upgrade upgrade );

		/// <summary>
		/// Set every upgrade to level 0
		/// </summary>
		void Zero();

		static int MaxBobWidth;
		void CalcGenData( const std::shared_ptr<LevelGenData> &GenData, const std::shared_ptr<StyleData> &Style );
	};
}


#endif	//#ifndef UPGRADES
