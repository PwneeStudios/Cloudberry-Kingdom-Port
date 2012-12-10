#ifndef BOB
#define BOB

#include <global_header.h>

namespace CloudberryKingdom
{
	class Bob : public ObjectBase
	{

	public:
		static void InitializeStatics();

	public:
		class BobMove
		{
		public:
			BobMove()
			{
				MaxTargetY = MinTargetY = 0;
				Copy = 0;
				InvertDirX = false;
			}

			float MaxTargetY, MinTargetY;

			int Copy;

			/// <summary>
			/// If true the x acceleration is inverted
			/// </summary>
			bool InvertDirX;

			void Init();
		};

	public:
		float LightSourceFade, LightSourceFadeVel;
		void ResetLightSourceFade();
		void SetLightSourceToFade();
		void SetLightSourceToFadeIn();
	private:
		void DoLightSourceFade();

	public:
		bool Dopple;
		Vector2 LastPlacedCoin;

		static bool AllExplode;
		static bool ShowCorpseAfterExplode;

		std::shared_ptr<BobPhsx> MyHeroType;

		bool FadingIn;
		float Fade;

		void SetToFadeIn();

		static int ImmortalLength;
		int ImmortalCountDown;
		bool Moved;

		ColorScheme MyColorScheme;

		int HeldObjectIteration;

		bool CanHaveCape, CanHaveHat;
		std::shared_ptr<BobPhsx> MyObjectType;

		float NewY, NewVel, Xvel;

		virtual void Release();

		void SetObject( const std::shared_ptr<ObjectClass> &obj, bool boxesOnly );

		void SetColorScheme( ColorScheme scheme );

		Vector2 CapeWind, Wind;

		std::shared_ptr<Hat> MyHat;
		CapeType MyCapeType;
		std::shared_ptr<Cape> MyCape;
		bool ShowCape;
		Color InsideColor;

	private:
		std::shared_ptr<ObjectVector> temp;
		std::shared_ptr<Quad> Head;

	public:
		std::vector<std::shared_ptr<BobLink> > MyBobLinks;

		int SideHitCount;

		bool CanInteract;

		BobMove MoveData;

		int Count_ButtonA;
		BobInput CurInput, PrevInput;
		std::shared_ptr<BobPhsx> MyPhsx;

		/// <summary>
		/// Whether the computer wants to land on a potential block (For PlayMode == 2)
		/// </summary>
		bool WantsToLand;

		/// <summary>
		/// Whether the computer would be willing to land but prefers not to.
		/// </summary>
		bool WantsToLand_Reluctant;

		Vector2 TargetPosition;

		float GroundSpeed;

		bool ComputerWaitAtStart;
		int ComputerWaitAtStartLength;

		bool SaveNoBlock;
		int PlaceDelay;
		int PlaceTimer;

		bool Immortal, DoNotTrackOffScreen;

		bool TopCol, BottomCol;

		std::shared_ptr<FancyVector2> FancyPos;
//C# TO C++ CONVERTER NOTE: The variable CharacterSelect was renamed since it is named the same as a user-defined type:
		bool CompControl, CharacterSelect_Renamed, CharacterSelect2, Cinematic, DrawWithLevel, AffectsCamera;
		int IndexOffset;

		int ControlCount;

		/// <summary>
		/// A callback called when the Bob lands on something.
		/// </summary>
		std::shared_ptr<Lambda> OnLand;

		/// <summary>
		/// A callback called when the Bob reaches his jump apex.
		/// </summary>
		std::shared_ptr<Lambda> OnApexReached;


		bool CodeControl;
		std::shared_ptr<Lambda_1<int> > ControlFunc;
		std::shared_ptr<Lambda_1<int> > CinematicFunc;
		std::shared_ptr<Lambda> OnAnimFinish;

		void SetCodeControl();

		std::shared_ptr<LevelPiece> MyPiece;

		/// <summary>
		/// Which start position in the current level piece this Bob belongs to
		/// </summary>
		int MyPieceIndex;

		/// <summary>
		/// If more than one Bob belongs to the same start position, this is the Bobs' ordering
		/// </summary>
		int MyPieceIndexOffset;
		std::shared_ptr<ComputerRecording> MyRecord;


		bool Dying, Dead, FlamingCorpse;

		bool BoxesOnly;

		bool ScreenWrap, ScreenWrapToCenter, CollideWithCamera;

		std::shared_ptr<EzSound> JumpSound, DieSound;
		static std::shared_ptr<EzSound> JumpSound_Default, DieSound_Default;

		PlayerIndex MyPlayerIndex;
		const std::shared_ptr<PlayerData> getMyPlayerData() const;


		bool TryPastTop;


		std::shared_ptr<ObjectClass> PlayerObject;

		std::shared_ptr<BlockBase> LastCeiling;
	private:
		Vector2 LastCoinPos;

	public:
		int MinFall, MinDrop;

		bool MakingLava, MakingCeiling;

		std::shared_ptr<AABox> Box, Box2;

		Vector2 Feet();

		/// <summary>
		/// A list of boxes to allow for different difficulty levels for different obstacles.
		/// </summary>
	private:
		std::vector<std::shared_ptr<AABox> > Boxes;
		int NumBoxes;

	public:
		std::shared_ptr<AABox> GetBox( int DifficultyLevel );

		/// <summary>
		/// A collision box corresponding to the normal size of Box2 during actual gameplay.
		/// </summary>
		std::shared_ptr<AABox> RegularBox2;

		static std::vector<std::shared_ptr<BobPhsx> > HeroTypes;

		/// <summary>
		/// How many time the bob has popped something without hitting the ground.
		/// </summary>
		int PopModifier;

		Bob( const std::shared_ptr<BobPhsx> &type, bool boxesOnly );

		bool IsSpriteBased;
		Bob( const std::wstring &file, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad );
		Bob( const std::wstring &file, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, const std::shared_ptr<BobPhsx> &MyHeroType, bool AllowHats );
		Bob( const std::shared_ptr<ObjectClass> &obj, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, const std::shared_ptr<BobPhsx> &MyHeroType, bool AllowHats );
	private:
		void LoadFromFile( const std::wstring &file, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, const std::shared_ptr<BobPhsx> &HeroType );
		void _Load( const std::shared_ptr<ObjectClass> &obj, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, const std::shared_ptr<BobPhsx> &HeroType );

	public:
		void SwitchHero( const std::shared_ptr<BobPhsx> &hero );

		/// <summary>
		/// When true the player can not move.
		/// </summary>
		bool Immobile;

		void SetHeroPhsx( const std::shared_ptr<BobPhsx> &type );

		void MakeCape( CapeType CapeType );

		void Init( bool BoxesOnly, PhsxData StartData, const std::shared_ptr<GameData> &game );

		/// <summary>
		/// Whether this Bob is a player.
		/// </summary>
		bool IsPlayer;

		/// <summary>
		/// Get the player data associated with this Bob.
		/// If the Bob isn't controlled by a player return null.
		/// </summary>
		/// <returns></returns>
		std::shared_ptr<PlayerData> GetPlayerData();

		bool GiveStats();

		const std::shared_ptr<PlayerStats> &getMyStats() const;

		const std::shared_ptr<PlayerStats> &getMyTempStats() const;

		/// <summary>
		/// The number of frames since the player has died.
		/// </summary>
	private:
		int DeathCount;

	public:
		std::shared_ptr<ObjectBase> KillingObject;
		static std::map<BobDeathType, Localization::Words> BobDeathNames;

		/// <summary>
		/// Kill the player.
		/// </summary>
		/// <param name="DeathType">The type of death.</param>
		/// <param name="ForceDeath">Whether to force the players death, ignoring immortality.</param>
		/// <param name="DoAnim">Whether to do the death animation.</param>
		void Die( BobDeathType DeathType, bool ForceDeath, bool DoAnim );
		void Die( BobDeathType DeathType );
		void Die( BobDeathType DeathType, const std::shared_ptr<ObjectBase> &KillingObject );
		void Die( BobDeathType DeathType, const std::shared_ptr<ObjectBase> &KillingObject, bool ForceDeath, bool DoAnim );

		/// <summary>
		/// Whether we can kill the current player.
		/// The player must be player controlled and not already dead.
		/// </summary>
		const bool getCanDie() const;

		/// <summary>
		/// Whether we can finish a current level.
		/// The player must be player controlled and not already dead.
		/// </summary>
		const bool getCanFinish() const;

		void DyingPhsxStep();

		void CheckForScreenWrap();
		float CameraWeight, CameraWeightSpeed;

		void GetPlayerInput();

		void GetRecordedInput( int Step );

	private:
		void RecordInput( int Step );

	public:
		void AnimStep();

		/// <summary>
		///// When true the call to AnimAndUpdate must be done manually.
		/// </summary>
		bool ManualAnimAndUpdate;
		void AnimAndUpdate();

		/// <summary>
		/// The position of the stickman object
		/// </summary>
		const Vector2 &getObjectPos() const;

		Vector2 ExtraShift;
		void UpdateObject();

		void UpdateColors();

		static bool GuideActivated;
	private:
		static std::shared_ptr<QuadClass> GuideQuad;
		void InitGuideQuad();

		static int GuideLength;
		static float Guide_h;
		void DrawGuidePiece( int Step, std::vector<Vector2> Loc, int i );

		void InitSectionDraw();
		void DrawSection( int Step, std::vector<Vector2> Loc );

		void DrawGuide();

		/// <summary>
		/// Whether the player is visible on the screen.
		/// </summary>
	public:
		bool IsVisible();

	private:
		std::shared_ptr<QuadClass> Rocket;
	public:
		Vector2 RocketOffset;
	private:
		void DrawTheRocket();

	public:
		Vector2 GetScale();

		virtual void Draw();

		virtual void Move( Vector2 shift );

		void InteractWithBlock( const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block, ColType Col );

	private:
		void UpdateGroundSpeed( const std::shared_ptr<AABox> &box, const std::shared_ptr<BlockBase> &block );

	public:
		void InitBoxesForCollisionDetect();

		void UpdateCape();

		void CorePhsxStep();

		void DollPhsxStep();

		/// <summary>
		/// Whether to do object interactions.
		/// </summary>
		bool DoObjectInteractions;

		virtual void PhsxStep();

		/// <summary>
		/// Calculate all interactions between the player and every IObject in the level.
		/// </summary>
	private:
		void ObjectInteractions();

		/// <summary>
		/// Update the list of AABox boxes used by the computer when creating the level.
		/// </summary>
		void UpdateBoxList();

	public:
		void DeleteObj( const std::shared_ptr<ObjectBase> &obj );

		std::shared_ptr<Ceiling_Parameters> CeilingParams;
		/// <summary>
		/// Calculate all interactions between the player and every Block in the level.
		/// </summary>
	private:
		void BlockInteractions();

		void OldBlockInteractions();

		void NewBlockInteractions();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BOB
