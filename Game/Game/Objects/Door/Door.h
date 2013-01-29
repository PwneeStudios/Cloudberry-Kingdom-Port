#ifndef DOOR
#define DOOR

#include <global_header.h>

#include "Core/Lambdas/Lambda.h"
#include "Core/Lambdas/LambdaFunc.h"
#include "Core/Lambdas/LambdaFunc_1.h"
#include "Core/Lambdas/LambdaFunc_2.h"
#include "Core/Lambdas/Lambda_1.h"
#include "Core/Lambdas/Lambda_2.h"
#include "Core/Lambdas/Multicaster.h"
#include "Core/Lambdas/Multicaster_1.h"
#include "Core/Lambdas/Multicaster_2.h"

#include "Core/FancyVector2.h"
#include "Core/FancyColor.h"
#include "Core/PhsxData.h"
#include "Core/Graphics/Draw/Simple/SimpleVector.h"
#include "Core/Graphics/Draw/Simple/SimpleQuad.h"
#include "Core/WriteReadTools.h"
#include "Core/Animation/SpriteAnim.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Graphics/MainRender.h"
#include "Core/Graphics/QuadDrawer.h"
#include "Core/Graphics/Draw/Object/ObjectBox.h"
#include "Core/Graphics/Draw/Quads/BaseQuad.h"
#include "Core/Graphics/Draw/Quads/ObjectVector.h"
#include "Core/Graphics/Draw/Quads/PieceQuad.h"
#include "Core/Graphics/Draw/Quads/Quad.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/Graphics/Draw/Simple/SimpleBox.h"
#include "Core/Graphics/Draw/Simple/SimpleObject.h"

namespace CloudberryKingdom
{
	struct Door : public ILevelConnector
	{

		virtual ~Door() { }
	
		struct ShakeLambda : public Lambda
		{
		
			int Length_, Intensity_;
			bool Sound_;
			boost::shared_ptr<Door> Door_;

		
			ShakeLambda( const boost::shared_ptr<Door> &door, int Length, int Intensity, bool Sound );

			void Apply();
		};

	
		struct DoorTileInfo : public TileInfoBase
		{
		
			boost::shared_ptr<SpriteInfo> Sprite;
			bool Show;

			Vector2 SizePadding;

			Vector2 ShiftBottom;
			Vector2 ShiftStart;
			Vector2 CollisionSize;

			boost::shared_ptr<EzSound> DoorOpen;
			boost::shared_ptr<EzSound> DoorClose;

//C# TO C++ CONVERTER NOTE: The variable Sign was renamed since it is named the same as a user-defined type:
			boost::shared_ptr<SpriteInfo> Sign_Renamed;
			bool ShowSign;

		
			void InitializeInstanceFields();


			DoorTileInfo()
			{
				InitializeInstanceFields();
			}
		};

	
		boost::shared_ptr<LevelSeedData> _NextLevelSeedData;
	
		const boost::shared_ptr<LevelSeedData> &getNextLevelSeedData() const;
		void setNextLevelSeedData( const boost::shared_ptr<LevelSeedData> &value );

		boost::shared_ptr<NormalBlock> MyBackblock;

		virtual void Release();

		bool SkipPhsx;

		/// <summary>
		/// Block the door immediately after a Bob appears in it, so that the player doesn't accidently go back through.
		/// </summary>
	
		bool TemporaryBlock;

	
		bool Locked;

		boost::shared_ptr<QuadClass> MyQuad;

	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > _OnOpen;
	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > getOnOpen() const;
		void setOnOpen( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &value );

	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > _OnEnter;
	
		const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &getOnEnter() const;
		void setOnEnter( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &value );
		boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > ExtraPhsx;

	
		boost::shared_ptr<PressNote> MyPressNote;

	
		virtual void MakeNew();

		Vector2 ShiftStart;
		Vector2 ShiftBottom;
		Vector2 DoorSize;

		bool Mirror;

	
		Vector2 HitBoxPadding;

		/// <summary>
		/// Sets the door to a default type associated with the given tile set.
		/// </summary>
	
		void SetDoorType( const boost::shared_ptr<TileSet> &TileSetType, const boost::shared_ptr<Level> &level );

		Door( bool BoxesOnly );

		Vector2 GetBottom();

		Vector2 GetTop();

		/// <summary>
		/// Update the graphical display of the door to reflect whether it's locked or unlocked.
		/// </summary>
	
		void SetObjectState();

	
		void HideBobs();

		void ShowBobs();

		bool SuppressSound;

		void SetLock( bool Locked );
		void SetLock( bool Locked, bool AlwaysSet, bool PlaySound );
		void SetLock( bool Locked, bool AlwaysSet, bool PlaySound, bool Hide );

		void Update();


		void MakeNote();

		void KillNote();

	
		int ShakeStep, ShakeIntensity;
	
		void Shake( int Length, int Intensity, bool Sound );

	
		void DoShake();

		int step;
		bool shake;
		Vector2 save;
	
		virtual void PhsxStep();

	
		bool OnScreen();

	
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
		void MoveBobToHere( const boost::shared_ptr<Bob> &bob );

		/// <summary>
		/// The Bob interacting with the door.
		/// </summary>
		boost::shared_ptr<Bob> InteractingBob;

		/// <summary>
		/// The Bob activating the door.
		/// </summary>
		boost::shared_ptr<Bob> ActivatingBob;

		/// <summary>
		/// When true, when a player closes the door he is hid.
		/// </summary>
		bool HideInteractingBobOnDoorClose;

		/// <summary>
		/// How long a player has been near enough to the door to open it.
		/// </summary>
	
		int NearCount;

	
		void ClearNote();

		bool NoNote;

		/// <summary>
		/// How many frames to wait while the player is close to the door
		/// before showing a note that explains how to open the door.
		/// </summary>
	
		const int getDelayToShowNote() const;

		/// <summary> This length is used only for the first time a player opens a door. </summary>
		int _DelayToShowNote_First;
		int _DelayToShowNote_Second;
		int _DelayToShowNote_Nth;


		/// <summary>
		/// Number of times a door has been successfully operated by a player.
		/// (since the game has launched).
		/// </summary>
		static int DoorOperated;

	
		bool UsedOnce;

		/// <summary>
		/// When true the player will exit through a door automatically, without pressing anything.
		/// </summary>
		bool AutoOpen;

		static bool AllowCompControl;
		virtual void Interact( const boost::shared_ptr<Bob> &bob );

		void Do();

		void HaveBobUseDoor( const boost::shared_ptr<Bob> &bob );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

		virtual void Write( const boost::shared_ptr<BinaryWriter> &writer );

		virtual void Read( const boost::shared_ptr<BinaryReader> &reader );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef DOOR
