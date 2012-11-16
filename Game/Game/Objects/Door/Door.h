#ifndef DOOR
#define DOOR

#include "../Game/Games/Meta Games/StringWorlds/LevelConnector.h"
#include "../Game/Objects/ObjectBase.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Game/Tilesets/TileSet.h"
#include "Sign.h"
#include <vector>
#include <cmath>
#include <tchar.h>

namespace CloudberryKingdom
{
	class SpriteInfo;
}

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class LevelSeedData;
}

namespace CloudberryKingdom
{
	class NormalBlock;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class PressNote;
}

namespace CloudberryKingdom
{
	class TileSet;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Door : public ObjectBase, public ILevelConnector
	{
	public:
		class ShakeLambda : public Lambda
		{
		private:
			int Length_, Intensity_;
			bool Sound_;
			std::shared_ptr<Door> Door_;

		public:
			ShakeLambda( const std::shared_ptr<Door> &door, int Length, int Intensity, bool Sound );

			void Apply();
		};

	public:
		class DoorTileInfo : public TileInfoBase
		{
		public:
			std::shared_ptr<SpriteInfo> Sprite;
			bool Show;

			Vector2 SizePadding;

			Vector2 ShiftBottom;
			Vector2 ShiftStart;
			Vector2 CollisionSize;

			std::shared_ptr<EzSound> DoorOpen;
			std::shared_ptr<EzSound> DoorClose;

//C# TO C++ CONVERTER NOTE: The variable Sign was renamed since it is named the same as a user-defined type:
			std::shared_ptr<SpriteInfo> Sign_Renamed;
			bool ShowSign;

		private:
			void InitializeInstanceFields();

public:
			DoorTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	private:
		std::shared_ptr<LevelSeedData> _NextLevelSeedData;
	public:
		const std::shared_ptr<LevelSeedData> &getNextLevelSeedData() const;
		void setNextLevelSeedData( const std::shared_ptr<LevelSeedData> &value );

		std::shared_ptr<NormalBlock> MyBackblock;

		virtual void Release();

		bool SkipPhsx;

		/// <summary>
		/// Block the door immediately after a Bob appears in it, so that the player doesn't accidently go back through.
		/// </summary>
	private:
		bool TemporaryBlock;

	public:
		bool Locked;

		std::shared_ptr<QuadClass> MyQuad;

	private:
		std::shared_ptr<Lambda_1<Door*> > _OnOpen;
	public:
		const std::shared_ptr<Lambda_1<Door*> > &getOnOpen() const;
		void setOnOpen( const std::shared_ptr<Lambda_1<Door*> > &value );

	private:
		std::shared_ptr<Lambda_1<Door*> > _OnEnter;
	public:
		const std::shared_ptr<Lambda_1<Door*> > &getOnEnter() const;
		void setOnEnter( const std::shared_ptr<Lambda_1<Door*> > &value );
		std::shared_ptr<Lambda_1<Door*> > ExtraPhsx;

	private:
		std::shared_ptr<PressNote> MyPressNote;

	public:
		virtual void MakeNew();

		Vector2 ShiftStart;
		Vector2 ShiftBottom;
		Vector2 DoorSize;

		bool Mirror;

	private:
		Vector2 HitBoxPadding;

		/// <summary>
		/// Sets the door to a default type associated with the given tile set.
		/// </summary>
	public:
		void SetDoorType( const std::shared_ptr<TileSet> &TileSetType, const std::shared_ptr<Level> &level );

		Door( bool BoxesOnly );

		Vector2 GetBottom();

		Vector2 GetTop();

		/// <summary>
		/// Update the graphical display of the door to reflect whether it's locked or unlocked.
		/// </summary>
	private:
		void SetObjectState();

	public:
		void HideBobs();

		void ShowBobs();

		bool SuppressSound;

		void SetLock( bool Locked );
		void SetLock( bool Locked, bool AlwaysSet, bool PlaySound );
		void SetLock( bool Locked, bool AlwaysSet, bool PlaySound, bool Hide );

		void Update();


		void MakeNote();

		void KillNote();

	private:
		int ShakeStep, ShakeIntensity;
	public:
		void Shake( int Length, int Intensity, bool Sound );

	private:
		void DoShake();

		int step;
		bool shake;
		Vector2 save;
	public:
		virtual void PhsxStep();

	private:
		bool OnScreen();

	public:
		virtual void Draw();

		/// <summary>
		/// Moves the foot of the door to the specified position.
		/// </summary>
		/// <param name="pos"></param>
		void PlaceAt( Vector2 pos );

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		void MoveBobs();

		bool MoveFeet;
		void MoveBobToHere( const std::shared_ptr<Bob> &bob );

		/// <summary>
		/// The Bob interacting with the door.
		/// </summary>
		std::shared_ptr<Bob> InteractingBob;

		/// <summary>
		/// The Bob activating the door.
		/// </summary>
		std::shared_ptr<Bob> ActivatingBob;

		/// <summary>
		/// When true, when a player closes the door he is hid.
		/// </summary>
		bool HideInteractingBobOnDoorClose;

		/// <summary>
		/// How long a player has been near enough to the door to open it.
		/// </summary>
	private:
		int NearCount;

	public:
		void ClearNote();

		bool NoNote;

		/// <summary>
		/// How many frames to wait while the player is close to the door
		/// before showing a note that explains how to open the door.
		/// </summary>
	private:
		const int &getDelayToShowNote() const;

		/// <summary> This length is used only for the first time a player opens a door. </summary>
		int _DelayToShowNote_First;
		int _DelayToShowNote_Second;
		int _DelayToShowNote_Nth;


		/// <summary>
		/// Number of times a door has been successfully operated by a player.
		/// (since the game has launched).
		/// </summary>
		static int DoorOperated;

	public:
		bool UsedOnce;

		/// <summary>
		/// When true the player will exit through a door automatically, without pressing anything.
		/// </summary>
		bool AutoOpen;

		static bool AllowCompControl;
		virtual void Interact( const std::shared_ptr<Bob> &bob );

		void Do();

		void HaveBobUseDoor( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const std::shared_ptr<BinaryReader> &reader );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef DOOR
