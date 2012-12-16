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
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			StartTestProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct MoveBlockAndKillProxy : public LambdaFunc<bool>
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			MoveBlockAndKillProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			bool Apply();
		};

	
		struct KillBobsHelper : public Lambda
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			KillBobsHelper( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct AddItemProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			AddItemProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct UpdateBaseHeroProxy : public Lambda
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			UpdateBaseHeroProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct UpdateSizeHeroProxy : public Lambda
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			UpdateSizeHeroProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct UpdateJumpHeroProxy : public Lambda
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			UpdateJumpHeroProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct NextProxy : public Lambda
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			NextProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct StartLevelProxy : public Lambda
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			StartLevelProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		struct ResetSlidersProxy : public Lambda
		{
		
			boost::shared_ptr<CustomHero_GUI> chGui;

		
			ResetSlidersProxy( const boost::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	
		static BobPhsx::CustomPhsxData HeroPhsxData;

		static boost::shared_ptr<BobPhsx> Hero;
	
		const boost::shared_ptr<BobPhsxNormal> getNormalHero() const;

	
		boost::shared_ptr<CustomLevel_GUI> CustomLevel;
	
		CustomHero_GUI( const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );
		boost::shared_ptr<CustomHero_GUI> CustomHero_GUI_Construct( const boost::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual void OnAdd();

	
		virtual void ReleaseBody();

	
		boost::shared_ptr<PhsxSlider> GravitySlider, MaxSpeedSlider, AccelSlider;
		boost::shared_ptr<PhsxSlider> MaxFallSpeedSlider, JumpLengthSlider, JumpAccelSlider, DoubleJumpLengthSlider, DoubleJumpAccelSlider, FrictionSlider, JetPackSlider, JetPackFuelSlider, NumJumpsSlider;
		boost::shared_ptr<PhsxSlider> SizeSlider, PhasedSizeSlider, PhasedGravitySlider, PhasePeriodSlider;
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

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
		void SetSuperHeader( const boost::shared_ptr<EzText> &text );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		boost::shared_ptr<MenuList> MakeList();

	
		virtual void AddItem( const boost::shared_ptr<MenuItem> &item );

	
		boost::shared_ptr<BobPhsx> Base, Jump, Size;

		boost::shared_ptr<MenuItem> Start, Back;
		boost::shared_ptr<EzText> HeroText;
		boost::shared_ptr<MenuList> BaseList, JumpList, SizeList;
		boost::shared_ptr<EzText> BaseHeader, JumpHeader, SizeHeader;

		void SetListItemProperties( const boost::shared_ptr<MenuItem> &item );

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

		boost::shared_ptr<MenuItem> A, B, X, Y;
		void MakeOptionItems();

		bool AdvancedAvailable();

		void ResetAdvancedSliders();

		boost::shared_ptr<MenuItem> ResetButton;

		void Next();

		void StartLevel();

		void ResetSliders();

	
		virtual void OnReturnTo();

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CUSTOMHERO_GUI
