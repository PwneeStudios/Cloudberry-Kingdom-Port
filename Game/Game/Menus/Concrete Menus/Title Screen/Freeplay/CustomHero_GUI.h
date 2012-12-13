#ifndef CUSTOMHERO_GUI
#define CUSTOMHERO_GUI

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CustomHero_GUI : public CkBaseMenu
	{

	
		static void InitializeStatics();

	
		struct StartTestProxy : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			StartTestProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct MoveBlockAndKillProxy : public LambdaFunc<bool>
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			MoveBlockAndKillProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			bool Apply();
		};

	
		struct KillBobsHelper : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			KillBobsHelper( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct AddItemProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			AddItemProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct UpdateBaseHeroProxy : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			UpdateBaseHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct UpdateSizeHeroProxy : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			UpdateSizeHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct UpdateJumpHeroProxy : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			UpdateJumpHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct NextProxy : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			NextProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct StartLevelProxy : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			StartLevelProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct ResetSlidersProxy : public Lambda
		{
		
			std::shared_ptr<CustomHero_GUI> chGui;

		
			ResetSlidersProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		static BobPhsx::CustomPhsxData HeroPhsxData;

		static std::shared_ptr<BobPhsx> Hero;
	
		const std::shared_ptr<BobPhsxNormal> getNormalHero() const;

	
		std::shared_ptr<CustomLevel_GUI> CustomLevel;
	
		CustomHero_GUI( const std::shared_ptr<CustomLevel_GUI> &CustomLevel );
		void CustomHero_GUI_Construct( const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		std::shared_ptr<PhsxSlider> GravitySlider, MaxSpeedSlider, AccelSlider;
		std::shared_ptr<PhsxSlider> MaxFallSpeedSlider, JumpLengthSlider, JumpAccelSlider, DoubleJumpLengthSlider, DoubleJumpAccelSlider, FrictionSlider, JetPackSlider, JetPackFuelSlider, NumJumpsSlider;
		std::shared_ptr<PhsxSlider> SizeSlider, PhasedSizeSlider, PhasedGravitySlider, PhasePeriodSlider;
		void MakeSliders();

	
		void StartTest();

	
		bool Testing;
		void TestingPhsx();

		void EndTest();

		bool MoveBlockAndKill();

		void KillBobs();

		void MakeBobPhsx();


		void CreateHeroes();

		void RemovePreviousGround();

		void CreateGround();

	
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		void SetSuperHeader( const std::shared_ptr<EzText> &text );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		std::shared_ptr<MenuList> MakeList();

	
		virtual void AddItem( const std::shared_ptr<MenuItem> &item );

	
		std::shared_ptr<BobPhsx> Base, Jump, Size;

		std::shared_ptr<MenuItem> Start, Back;
		std::shared_ptr<EzText> HeroText;
		std::shared_ptr<MenuList> BaseList, JumpList, SizeList;
		std::shared_ptr<EzText> BaseHeader, JumpHeader, SizeHeader;

		void SetListItemProperties( const std::shared_ptr<MenuItem> &item );

		static int BaseListIndex;
		static int SizeListIndex;
		static int JumpListIndex;

	
		virtual void Init();

	
		void SetListActions();

		void UpdateSliders();

		//PhsxSlider GravitySlider, MaxSpeedSlider, AccelSlider;
		//PhsxSlider MaxFallSpeedSlider, JumpLengthSlider, JumpAccelSlider, DoubleJumpLengthSlider, DoubleJumpAccelSlider, FrictionSlider, JetPackSlider, JetPackFuelSlider, NumJumpsSlider;
		//PhsxSlider SizeSlider, PhasedSizeSlider, PhasedGravitySlider, PhasePeriodSlider;

		void UpdateBaseHero();

		void UpdateSizeHero();

		void UpdateJumpHero();

		void SetPos();

		std::shared_ptr<MenuItem> A, B, X, Y;
		void MakeOptionItems();

		bool AdvancedAvailable();

		void ResetAdvancedSliders();

		std::shared_ptr<MenuItem> ResetButton;

		void Next();

		void StartLevel();

		void ResetSliders();

	
		virtual void OnReturnTo();

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CUSTOMHERO_GUI
