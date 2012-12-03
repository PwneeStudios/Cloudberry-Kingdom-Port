#ifndef SUPER_GLOBAL_HEADER_H
#define SUPER_GLOBAL_HEADER_H

// Questions
// string formatting?
// List.Sort
// GameObjVec ObjectsToSave = GameObjVec();

// Jordan's unalphebatized shit. Suck it Oleg.
inline int Sign(int x) { return (x > 0) - (x < 0); }
inline int Sign(float x) { return (x > 0) - (x < 0); }
inline int Sign(double x) { return (x > 0) - (x < 0); }

// Things to reh-gecks.
// Math::Sign and Sign -> Sign

#include "enums.h"
#include "forward_declarations.h"

// System includes.
#include <algorithm>
#include <list>
#include <map>
#define _USE_MATH_DEFINES
#include "math.h"
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <vector>
#include <tchar.h>

#include <Hacks/Compare.h>
#include <Hacks/List.h>
#include <Hacks/Parse.h>
#include <Hacks/String.h>
#include <Hacks/Queue.h>

// Syntactic sugar
namespace CloudberryKingdom
{
	typedef std::vector<std::shared_ptr<Bob> > BobVec;
	typedef std::vector<std::shared_ptr<ObjectBase> > ObjectVec;
	typedef std::vector<std::shared_ptr<BlockBase> > BlockVec;
	typedef std::vector<std::shared_ptr<GameObject> > GameObjVec;
}

// Core library.
#include <Graphics/Color.h>
#include <Math/Vectors.h>

#include "Hacks/BinaryReader.h"
#include "Hacks/BinaryWriter.h"

class ContentManager
{

public:

	template<class T>
	std::shared_ptr<T> Load( const std::wstring &name )
	{
		return std::shared_ptr<T>();
	}

};

struct DateTime { int Time; };
class DisplayMode;

class Effect
{

public:

	std::shared_ptr<class EffectTechnique> CurrentTechnique;

	// FIXME: Implement.
	std::shared_ptr<class EffectParameter> Parameters( const std::wstring &name )
	{
		return 0;
	}

	// FIXME: Implement.
	std::shared_ptr<class EffectTechnique> Techniques( const std::wstring &name )
	{
		return 0;
	}

};

class EffectParameter
{

public:

	// FIXME: Implement everything.
	void SetValue( const Vector4 &v )
	{
	}

	void SetValue( const Matrix &m )
	{
	}

	void SetValue( const std::shared_ptr<class Texture2D> &t )
	{
	}

	void SetValue( const Vector2 &v )
	{
	}

	void SetValue( float v )
	{
	}

	float GetValueSingle()
	{
		return 0.f;
	}

};

class EffectPass
{

public:

	void Apply()
	{
	}

};

class EffectTechnique
{

public:

	std::vector<std::shared_ptr<EffectPass> > Passes;

	EffectTechnique()
	{
		Passes.resize( 1 );
	}

};

class FileReader
{

public:
	FileReader( std::wstring path );
	~FileReader(); // FIXME: make sure to close the file.

	std::wstring ReadLine();

};

class FileWriter
{

public:
	FileWriter( std::wstring path );
	~FileWriter(); // FIXME: make sure to close the file.

};

class FileStream;
class Game
{

public:

	std::shared_ptr<ContentManager> getContent()
	{
		return std::shared_ptr<ContentManager>();
	}

};

class GamePadButtons
{

public:

	ButtonState A;
	ButtonState B;
	ButtonState Back;
	ButtonState BigButton;
	ButtonState LeftShoulder;
	ButtonState LeftStick;
	ButtonState RightShoulder;
	ButtonState RightStick;
	ButtonState Start;
	ButtonState X;
	ButtonState Y;

};

class GamePadTriggers
{

public:

	float Left;
	float Right;

};

class GamePadDPad
{

public:

	ButtonState Down;
	ButtonState Left;
	ButtonState Right;
	ButtonState Up;

};

class GamePadThumbSticks
{

public:

	Vector2 Left;
	Vector2 Right;
};

class GamePadState
{
	
public:

	GamePadButtons Buttons;
	GamePadTriggers Triggers;
	GamePadDPad DPad;
	GamePadThumbSticks ThumbSticks;
};

class GamePad
{

public:

	static GamePadState GetState( PlayerIndex index )
	{
		return GamePadState();
	}

};

class GameTime;

struct Viewport { float X; float Y; float Width; float Height; float MinDepth; float MaxDepth; };

class GraphicsDevice
{

public:

	std::shared_ptr<class PresentationParameters> PP;
	std::vector<std::shared_ptr<class SamplerState> > SamplerStates;
	GfxRasterizerState RasterizerState;
	GfxBlendState BlendState;
	GfxDepthStencilState DepthStencilState;

	Viewport VP;

	GraphicsDevice()
	{
		SamplerStates.resize( 3 );
	}

	void SetRenderTarget( const std::shared_ptr<class RenderTarget2D> &rt )
	{
	}

	void Clear( const Color &color)
	{
	}

	template<class T>
	void DrawUserPrimitives( GfxPrimitiveType type, const std::vector<T> &vertices, int base, int count)
	{
	}

};

class GraphicsDeviceManager;
class IAsyncResult;

class KeyboardState
{
	
public:

	bool IsKeyDown( Keys key )
	{
		return false;
	}

	std::vector<Keys> GetPressedKeys()
	{
		return std::vector<Keys>();
	}

};

class Keyboard
{

public:

	static KeyboardState GetState()
	{
		return KeyboardState();
	}

};

class Song
{

public:

	struct
	{
		double TotalSeconds;
	} Duration;

};

class MediaPlayer
{

public:

	static void Play( const std::shared_ptr<Song> &song )
	{
	}

	static void Pause()
	{
	}

	static void Resume()
	{
	}

	static void Stop()
	{
	}

	static MediaState GetState()
	{
		return MediaState_Paused;
	}

	static bool IsRepeating;

};

// Note: some of these may not be needed. Check C# Lambda-port to see.
class Path
{

public:
	
	static std::wstring Combine( std::wstring Path, std::wstring Subpath );
	static std::wstring GetDirectoryName( std::wstring Path );

};
class Directory
{

public:
	
	static std::wstring GetCurrentDirectory( );

};


class SoundEffect
{

public:

	void Play( float volume, float i, float j )
	{
	}

};

class MouseState
{

public:

	int X;
	int Y;
	int ScrollWheelValue;

	ButtonState LeftButton;
	ButtonState RightButton;
};

class Mouse
{
	
public:

	static MouseState GetState()
	{
		return MouseState();
	}

};

class Mutex
{

public:

	void Lock()
	{
	}

	void Unlock()
	{
	}

};

class Object;
class PreparingDeviceSettingsEventArgs;

class PresentationParameters
{

public:

	int BackBufferFormat;
	int DepthStencilFormat;
	int MultiSampleCount;
	int BackBufferWidth;
	int BackBufferHeight;

};

class Random
{

public:
	int Next()
	{
		// FIXME: get a random number generator!
		return 0;
	}

	int Next( int low, int high )
	{
		return 0;
	}

	double NextDouble()
	{
		return 0;
	}

};

// Can't alphabetize this :(
class Texture2D
{
public:

	int Width;

	int Height;

	Texture2D( const std::shared_ptr<GraphicsDevice> &device, int width, int height )
	{
	}

	// FIXME: Implement this.
	void Dispose() { }

	template<class T>
	void GetData( std::vector<T> &data )
	{
	}

	template<class T>
	void SetData( std::vector<T> &data )
	{
	}
};

class RenderTarget2D : public Texture2D
{

public:

	RenderTarget2D( const std::shared_ptr<GraphicsDevice> &device, int width, int height, bool mipmap, int surfaceFormat, int depthFormat, int sampleCount, bool discard ) :
		Texture2D( device, width, height )
	{
	}

};

struct Rectangle
{

public:

	int X, Y, Width, Height;

	Rectangle() : X( 0 ), Y( 0 ), Width( 0 ), Height( 0 ) { }
	Rectangle( int X, int Y, int Width, int Height ) :
		X( X ), Y( Y ), Width( Width ), Height( Height )
	{
	}

};

class SamplerState
{

public:

	GfxTextureAddressMode AddressU;
	GfxTextureAddressMode AddressV;

	SamplerState()
	{
	}

};

class SignedInEventArgs;
class Song;
class SoundEffect;

class SpriteBatch
{

public:

	void DrawString( const std::shared_ptr<class SpriteFont> &font, const std::wstring &str, const Vector2 &loc, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth )
	{
	}

	void Draw( const std::shared_ptr<class Texture2D> &texture, const Vector2 &position, Rectangle *rect, const Color &c, float rotation, const Vector2 &origin, const Vector2 &scale, SpriteEffects se, float depth )
	{
	}

	void End()
	{
	}

};

class SpriteFont
{

public:

	float Spacing;
	int LineSpacing;

	Vector2 MeasureString( const std::wstring &text )
	{
		return Vector2();
	}

};

class Stopwatch;
class StorageContainer;
class StorageDevice;
class StreamReader;
class StreamWriter;
class StringBuilder
{

public:

	operator std::wstring() const
	{
		return _T( "" );
	}

};

class Thread;

template<class A, class B>
class Tuple
{

public:
	A Item1;
	B Item2;

	Tuple( A item1, B item2 )
	{
		Item1 = item1;
		Item2 = item2;
	}

};

class Video;
class VideoPlayer;

// Cloudberry Kingdom converted files.
#include "Game/Localization.h"
#include "Core/Graphics/Draw/Simple/BasePoint.h"
#include "Core/Lambdas/Lambda.h"
#include "Core/Lambdas/LambdaFunc.h"
#include "Core/Lambdas/LambdaFunc_1.h"
#include "Core/Lambdas/LambdaFunc_2.h"
#include "Core/Lambdas/Lambda_1.h"
#include "Core/Lambdas/Lambda_2.h"
#include "Core/Lambdas/Multicaster.h"
#include "Core/Lambdas/Multicaster_1.h"
#include "Core/Lambdas/Multicaster_2.h"
#include "Game/Tools/IntVector2.h"
#include "Game/Tools/Oscillate.h"
#include "Core/Animation/AnimationData_Vector.h"
#include "Core/Animation/AnimationData_Integer.h"
#include "CloudberryKingdom.h"
#include "stringconverter.h"
#include "Core/Chunk.h"
#include "Core/FancyVector2.h"
#include "Core/FancyColor.h"
#include "Core/PhsxData.h"
#include "Core/ResolutionGroup.h"
#include "Core/Version.h"
#include "Core/Graphics/VertexFormat.h"
#include "Core/Graphics/Draw/Simple/SimpleVector.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "Core/WriteReadTools.h"
#include "Core/Animation/AnimQueue.h"
#include "Core/Graphics/Draw/Object/ObjectClass.h"
#include "Core/Animation/SpriteAnim.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Graphics/MainRender.h"
#include "Core/Graphics/QuadDrawer.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Core/Graphics/Draw/Object/ObjectBox.h"
#include "Core/Graphics/Draw/Quads/BaseQuad.h"
#include "Core/Graphics/Draw/Quads/ObjectVector.h"
#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Graphics/Draw/Quads/Quad.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Graphics/Draw/Simple/SimpleBox.h"
#include "Core/Graphics/Draw/Simple/SimpleObject.h"
#include "Core/Input/ButtonCheck.h"
#include "Core/Particle Effects/Particle.h"
#include "Core/Particle Effects/ParticleEmitter.h"
#include "Core/Particle Effects/Specific Effects/CloudberryKingdom.ParticleEffects.h"
#include "Core/Song/EzSong.h"
#include "Core/Song/EzSongWad.h"
#include "Core/Sound/EzSound.h"
#include "Core/Sound/EzSoundWad.h"
#include "Core/Text/EzFont.h"
#include "Core/Text/EzText.h"
#include "Core/Texture/CloudberryKingdom.EzTextureWad.h"
#include "Core/Texture/CoreEngine.EzTextureWad.h"
#include "Core/Texture/EzTexture.h"
#include "Core/Texture/PackedTexture.h"
#include "Core/Texture/TextureOrAnim.h"
#include "Core/Tools/ColorHelper.h"
#include "Core/Tools/CoreMath.h"
#include "Core/Tools/Random.h"
#include "Core/Tools/Set.h"
#include "Game/Video.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/Circle.h"
#include "Game/Collision Detection/FloatRectangle.h"
#include "Game/Collision Detection/Line.h"
#include "Game/Collision Detection/Phsx.h"


#include "Game/Objects/ObjectBase.h"
#include "Game/Tilesets/TileSet.h"
#include "Game/Objects/In Game Objects/Blocks/Block.h"
#include "Game/Objects/In Game Objects/Blocks/Wall.h"

#include "Game/Objects/Game Objects/GameObject.h"

#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/CkBaseMenu.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyBase.h"

#include "Game/Games/GameType.h"
#include "Game/Games/ActionGame.h"
#include "Game/Games/CampaignHelper.h"
#include "Game/Games/NormalGame.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld.h"
#include "Game/Games/ScreenSaver.h"
#include "Game/Games/ToDoItem.h"
#include "Game/Games/TutorialHelper.h"
#include "Game/Games/Campaign/LevelSequence.h"
#include "Game/Games/Campaign/CampaignSequence.h"
#include "Game/Games/Campaign/FadeIn.h"
#include "Game/Games/Meta Games/Challenges/Challenge_Base.h"
#include "Game/Games/Meta Games/Arcade Games/Escalate/Escalation.h"
#include "Game/Games/Meta Games/Arcade Games/HeroFactory_Escalation.h"
#include "Game/Games/Meta Games/Arcade Games/Escalate/Escalation_Tutorial.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/CoinMod.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Rush.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush 2/HeroRush2_Tutorial.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Time Crisis/TimeCrisis_Tutorial.h"
#include "Game/Games/Meta Games/Challenges/_Regular.h"
#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld_Endurance.h"
#include "Game/Games/Meta Games/StringWorlds/StringWorld_Timed.h"
#include "Game/Level/ClosingCircle.h"
#include "Game/Level/LevelPiece.h"
#include "Game/Level/Make/LockableBool.h"
#include "Game/Level/Make/ComputerRecording.h"
#include "Game/Level/Make/DifficultyGroups.h"
#include "Game/Level/Make/DifficultyHelper.h"
#include "Game/Level/Make/Generators.h"
#include "Game/Level/Make/LevelSeedData.h"
#include "Game/Level/Make/PieceSeedData.h"
#include "Game/Level/Make/MakePiece/MakeThing.h"
#include "Game/Level/Make/MakePiece/MakeSingle/MakeFinalDoor.h"
#include "Game/Level/Make/MakePiece/MakeSingle/MakeFinalDoor_Float.h"
#include "Game/Level/Make/MakePiece/MakeVertical/MakeFinalDoor.h"
#include "Game/Level/Make/MakePiece/MakeVertical/MakeDarkBottom.h"
#include "Game/Level/Make/Parameters/LevelGenData.h"
#include "Game/Level/Make/Parameters/Param.h"
#include "Game/Level/Make/Parameters/PresetDifficulties.h"
#include "Game/Level/Make/Parameters/RandomDifficulty.h"
#include "Game/Level/Make/Parameters/Upgrades.h"
#include "Game/Level/Make/Parameters/StyleData/StyleData.h"
#include "Game/Level/Make/Parameters/StyleData/BigData.h"
#include "Game/Level/Make/Parameters/StyleData/UpData.h"
#include "Game/Level/Make/Parameters/StyleData/DownData.h"
#include "Game/Level/Make/Parameters/StyleData/OneScreenData.h"
#include "Game/Level/Make/Parameters/StyleData/SingleData.h"
#include "Game/Level/Make/Tools/Tunnel.h"
#include "Game/Level/Replays/Recording.h"
#include "Game/Level/Replays/ReplayGUI.h"
#include "Game/Level/Replays/SwarmBundle.h"
#include "Game/Level/Replays/SwarmRecord.h"
#include "Game/Menus/Menu.h"
#include "Game/Menus/LongMenu.h"
#include "Game/Menus/MiniMenu.h"
#include "Game/Menus/Concrete Menus/ShopMenu.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/ArrowMenu.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/Backdrop.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/ColorSelect.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/CustomizeMenu.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/Doll.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/GamerTag.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/HeroLevel.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/JoinText.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/SignInChoiceMenu.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/SimpleMenu.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/Waiting.h"
#include "Game/Menus/Concrete Menus/Help/HelpBlurb.h"
#include "Game/Tools/EzStorage.h"
#include "Game/Player/PlayerManager.h"
#include "Game/Menus/Concrete Menus/Help/HelpMenu.h"
#include "Game/Menus/Concrete Menus/Help/HintBlurb.h"
#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/InGameStartMenu.h"
#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/ControlScreen.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/CustomControls.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/LoadSeedAs.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/SaveLoadSeedMenu.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Sub Menus/SaveSeedAs.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/AlertBase.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyDeleteSeeds.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyQuitLevel.h"
#include "Game/Menus/Concrete Menus/InGameStartMenus/Verify/VerifyRemove.h"
#include "Game/Menus/Concrete Menus/Loading Screen/ILoadingScreen.h"
#include "Game/Menus/Concrete Menus/Loading Screen/Loading.h"
#include "Game/Menus/Concrete Menus/Loading Screen/LoadingScreen.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreDatabase.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreEntry.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreList.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreScreen.h"
#include "Game/Menus/Concrete Menus/Score Screens/StatsScreen.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Backpanel.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Black.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomLevel_GUI.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_CustomLevel.h"
#include "Game/Menus/Concrete Menus/Title Screen/Sub Menus/VerifyQuitGame.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Exit.h"
#include "Game/Menus/Concrete Menus/Title Screen/Sub Menus/SoundMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_Options.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu_MW_PressStart.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGameBase.h"
#include "Game/Menus/Concrete Menus/Title Screen/TitleGame_MW.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartLevelMenu.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/StartMenu_MW_Arcade.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/Doll.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/HeroSelectOptions.h"
#include "Game/Menus/Concrete Menus/Title Screen/Arcade/Hero Select/StartMenu_MW_HeroSelect.h"
#include "Game/Player/Hero Physics/Base.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomHero_GUI.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomUpgrades_GUI.h"
#include "Game/Menus/Menu Components/MenuSliderBase.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/LengthSlider.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/SavedSeedsGUI.h"
#include "Game/Menus/Concrete Menus/Title Screen/Story/StartMenu_MW_Campaign.h"
#include "Game/Menus/Concrete Menus/Title Screen/Story/StartMenu_MW_Cinematics.h"
#include "Game/Menus/Menu Components/MenuList.h"
#include "Game/Menus/Menu Components/MenuListAll.h"
#include "Game/Menus/Menu Components/MenuListExpand.h"
#include "Game/Menus/Menu Components/MenuSlider.h"
#include "Game/Menus/Menu Components/MenuScrollBar.h"
#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/PhsxSlider.h"
#include "Game/Menus/Menu Components/MenuSliderNoSlide.h"
#include "Game/Menus/Menu Components/MenuToggle.h"
#include "Game/Menus/Menu Components/ScrollBar.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Objects/IBounded.h"
#include "Game/Objects/Icon.h"
#include "Game/Objects/IPrepareToDraw.h"
#include "Game/Player/Buyable.h"
#include "Game/Player/ClrTextFx.h"
#include "Game/Player/ColorScheme.h"
#include "Game/Objects/Bob/BobInput.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/Bob/BobLink.h"
#include "Game/Objects/Door/Door.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Text.h"
#include "Game/Objects/Door/PressNote.h"
#include "Game/Objects/Game Objects/Template_GameObject.h"
#include "Game/Objects/Game Objects/GameObjects/Cheer.h"
#include "Game/Objects/Game Objects/GameObjects/CoinScoreMultiplierObject.h"
#include "Game/Objects/Game Objects/GameObjects/DoorIcon.h"
#include "Game/Objects/Game Objects/GameObjects/ExplodeBobs.h"
#include "Game/Objects/Game Objects/GameObjects/Guide.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Blobs.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Level.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Lives.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_LivesLeft.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Multiplier.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_NextLife.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Score.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_TextBox.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Base.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer.h"
#include "Game/Objects/Game Objects/GameObjects/GUI_Timer_Simple.h"
#include "Game/Objects/Game Objects/GameObjects/LevelTitle.h"
#include "Game/Objects/Game Objects/GameObjects/Listener.h"
#include "Game/Objects/Game Objects/GameObjects/MultiplierUp.h"
#include "Game/Objects/Game Objects/GameObjects/NewHero.h"
#include "Game/Objects/Game Objects/GameObjects/PerfectScoreObject.h"
#include "Game/Objects/Game Objects/GameObjects/Region.h"
#include "Game/Objects/Game Objects/GameObjects/Rumble.h"
#include "Game/Objects/Game Objects/GameObjects/SlowMo.h"
#include "Game/Objects/Game Objects/GameObjects/SuperCheer.h"
#include "Game/Objects/Game Objects/GameObjects/TimerWarning.h"
#include "Game/Objects/Game Objects/GameObjects/End/GameOverPanel.h"
#include "Game/Objects/Game Objects/GameObjects/End/HighScorePanel.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Obstacle.h"
#include "Game/Objects/In Game Objects/BaseClasses/_Death.h"
#include "Game/Objects/In Game Objects/BaseClasses/_BoxDeath.h"
#include "Game/Objects/In Game Objects/BaseClasses/_CircleDeath.h"
#include "Game/Objects/In Game Objects/BaseClasses/_LineDeath.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock.h"
#include "Game/Objects/In Game Objects/Blocks/BouncyBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Ceiling__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Conveyor.h"
#include "Game/Objects/In Game Objects/Blocks/Conveyor__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/FallingBlock.h"
#include "Game/Objects/In Game Objects/Blocks/FallingBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/GhostBlock.h"
#include "Game/Objects/In Game Objects/Blocks/GhostBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Lava.h"
#include "Game/Objects/In Game Objects/Blocks/Lava_Castle.h"
#include "Game/Objects/In Game Objects/Blocks/MovingBlock.h"
#include "Game/Objects/In Game Objects/Blocks/MovingBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/MovingPlatform.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlock.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlockDraw.h"
#include "Game/Objects/In Game Objects/Blocks/NormalBlock__Auto.h"
#include "Game/Objects/In Game Objects/Blocks/Pendulum.h"
#include "Game/Objects/In Game Objects/Blocks/Pendulum__Auto.h"
#include "Game/Objects/In Game Objects/Grab/Checkpoint.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"
#include "Game/Objects/In Game Objects/Grab/Coin.h"
#include "Game/Objects/In Game Objects/Grab/Coin__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter.h"
#include "Game/Objects/In Game Objects/Obstacles/BlockEmitter__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Boulder.h"
#include "Game/Objects/In Game Objects/Obstacles/Boulder__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Cloud.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Firesnake.h"
#include "Game/Objects/In Game Objects/Obstacles/Cloud__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Fireball__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Firesnake__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/FireSpinner.h"
#include "Game/Objects/In Game Objects/Obstacles/FireSpinner__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob.h"
#include "Game/Objects/In Game Objects/Obstacles/FlyingBlob__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Laser.h"
#include "Game/Objects/In Game Objects/Obstacles/Laser__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/LavaDrip.h"
#include "Game/Objects/In Game Objects/Obstacles/LavaDrip__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Serpent.h"
#include "Game/Objects/In Game Objects/Obstacles/Serpent__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Spike.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyGuy__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine.h"
#include "Game/Objects/In Game Objects/Obstacles/SpikeyLine__Auto.h"
#include "Game/Objects/In Game Objects/Obstacles/Spike__Auto.h"
#include "Game/Objects/Special/Arrow.h"
#include "Game/Objects/Special/ZoneTrigger.h"
#include "Game/Objects/Special/CameraZone.h"
#include "Game/Objects/Special/TextFloat.h"
#include "Game/Objects/Special/TextList.h"
#include "Game/Player/Cape.h"
#include "Game/Player/ColorSchemeManager.h"
#include "Game/Player/PlayerData.h"
#include "Game/Player/SavedSeeds.h"
#include "Game/Player/Stats.h"
#include "Game/Player/Awardments/Awardment.h"
#include "Game/Player/Awardments/AwardmentMessage.h"
#include "Game/Player/Hero Physics/Normal.h"
#include "Game/Player/Hero Physics/Big.h"
#include "Game/Player/Hero Physics/BobPhsxCharSelect.h"
#include "Game/Player/Hero Physics/Bouncy.h"
#include "Game/Player/Hero Physics/Box.h"
#include "Game/Player/Hero Physics/Double.h"
#include "Game/Player/Hero Physics/Invert.h"
#include "Game/Player/Hero Physics/Jetman.h"
#include "Game/Player/Hero Physics/Meat.h"
#include "Game/Player/Hero Physics/Random.h"
#include "Game/Player/Hero Physics/Rocketbox.h"
#include "Game/Player/Hero Physics/Scale.h"
#include "Game/Player/Hero Physics/Small.h"
#include "Game/Player/Hero Physics/Spaceship.h"
#include "Game/Player/Hero Physics/Time.h"
#include "Game/Player/Hero Physics/Wheel.h"
#include "Game/Tilesets/BlockGroup.h"
#include "Game/Tilesets/SpriteInfo.h"
#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Castle.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Cave.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Cloud.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Forest.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Hills.h"
#include "Game/Tilesets/Backgrounds/_Code/_code_Sea.h"
#include "Game/Tilesets/Tilesets/CloudberryKingdom.TileSets.h"
#include "Game/Tools/Camera.h"
#include "Game/Tools/CkColorHelper.h"
#include "Game/Tools/EzReader.h"
#include "Game/Tools/Globals.h"
#include "Game/Tools/Prototypes.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Resources.h"
#include "Game/Tools/Tools.h"
#include "Game/Tools/Unset.h"
#include "Game/Tools/WrappedFloat.h"
#include "MainClass/XboxPC/CloudberryKingdom.XnaGameClass.h"
#include "MainClass/XboxPC/MainClass.h"

#include "Game/Tilesets/TileSetInfo.h"

#endif
