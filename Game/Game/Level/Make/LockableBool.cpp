#include <small_header.h>
#include "Game/Level/Make/LockableBool.h"

#include "Core/PhsxData.h"
#include "Game/Localization.h"
#include "Game/Objects/Game Objects/GameObjects/ChapterTitle.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Core/Particle Effects/ParticleEmitter.h"
#include "Core/Song/EzSong.h"
#include "Core/Tools/CoreMath.h"
#include "Core/Tools/Random.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Objects/In Game Objects/Blocks/Wall.h"
#include "Game/Games/GameType.h"
#include "Game/Games/ActionGame.h"
#include "Game/Games/NormalGame.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
#include "Game/Games/Campaign/FadeIn.h"
#include "Game/Games/Campaign/CampaignSequence.h"
#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/Parameters/RandomDifficulty.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreScreen.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/Door/Door.h"
#include "Game/Objects/Game Objects/GameObjects/LevelTitle.h"
#include "Game/Objects/Game Objects/GameObjects/NewHero.h"
#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
#include "Game/Objects/In Game Objects/Grab/Checkpoint.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Player/ColorSchemeManager.h"
#include "Game/Player/Stats.h"
#include "Game/Player/Hero Physics/Normal.h"
#include "Game/Player/Hero Physics/Double.h"
#include "Game/Player/Hero Physics/Jetman.h"
#include "Game/Player/Hero Physics/Meat.h"
#include "Game/Player/Hero Physics/BobPhsxRandom.h"
#include "Game/Player/Hero Physics/Rocketbox.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Tools.h"
#include "Game/Tilesets/TileSetInfo.h"


namespace CloudberryKingdom
{

	const bool &LockableBool::getval() const
	{
		return _val;
	}

	void LockableBool::setval( const bool &value )
	{
		_val = value;
	}

	void LockableBool::InitializeInstanceFields()
	{
		_val = false;
	}

}
