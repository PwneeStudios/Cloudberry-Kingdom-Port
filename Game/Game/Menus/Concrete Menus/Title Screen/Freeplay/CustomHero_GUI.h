#ifndef CUSTOMHERO_GUI
#define CUSTOMHERO_GUI

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class BobPhsxNormal;
}

namespace CloudberryKingdom
{
	class CustomLevel_GUI;
}

namespace CloudberryKingdom
{
	class PhsxSlider;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class MenuList;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class CustomHero_GUI : public CkBaseMenu
	{
	private:
		class StartTestProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			StartTestProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	private:
		class MoveBlockAndKillProxy : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			MoveBlockAndKillProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			bool Apply();
		};

	private:
		class KillBobsHelper : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			KillBobsHelper( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	private:
		class AddItemProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			AddItemProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class UpdateBaseHeroProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			UpdateBaseHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	private:
		class UpdateSizeHeroProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			UpdateSizeHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	private:
		class UpdateJumpHeroProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			UpdateJumpHeroProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	private:
		class NextProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			NextProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	private:
		class StartLevelProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			StartLevelProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	private:
		class ResetSlidersProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomHero_GUI> chGui;

		public:
			ResetSlidersProxy( const std::shared_ptr<CustomHero_GUI> &chGui );

			void Apply();
		};

	public:
		static BobPhsx::CustomPhsxData HeroPhsxData;

		static std::shared_ptr<BobPhsx> Hero;
	private:
		const std::shared_ptr<BobPhsxNormal> &getNormalHero() const;

	protected:
		std::shared_ptr<CustomLevel_GUI> CustomLevel;
	public:
		CustomHero_GUI( const std::shared_ptr<CustomLevel_GUI> &CustomLevel );

		virtual void OnAdd();

	protected:
		virtual void ReleaseBody();

	private:
		std::shared_ptr<PhsxSlider> GravitySlider, MaxSpeedSlider, AccelSlider;
		std::shared_ptr<PhsxSlider> MaxFallSpeedSlider, JumpLengthSlider, JumpAccelSlider, DoubleJumpLengthSlider, DoubleJumpAccelSlider, FrictionSlider, JetPackSlider, JetPackFuelSlider, NumJumpsSlider;
		std::shared_ptr<PhsxSlider> SizeSlider, PhasedSizeSlider, PhasedGravitySlider, PhasePeriodSlider;
		void MakeSliders();

	public:
		void StartTest();

	private:
		bool Testing;
		void TestingPhsx();

		void EndTest();

		bool MoveBlockAndKill();

		void KillBobs();

		void MakeBobPhsx();


		void CreateHeroes();

		void RemovePreviousGround();

		void CreateGround();

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	private:
		void SetSuperHeader( const std::shared_ptr<EzText> &text );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	private:
		std::shared_ptr<MenuList> MakeList();

	protected:
		virtual void AddItem( const std::shared_ptr<MenuItem> &item );

	private:
		std::shared_ptr<BobPhsx> Base, Jump, Size;

		std::shared_ptr<MenuItem> Start, Back;
		std::shared_ptr<EzText> HeroText;
		std::shared_ptr<MenuList> BaseList, JumpList, SizeList;
		std::shared_ptr<EzText> BaseHeader, JumpHeader, SizeHeader;

		void SetListItemProperties( const std::shared_ptr<MenuItem> &item );

		static int BaseListIndex;
		static int SizeListIndex;
		static int JumpListIndex;

	public:
		virtual void Init();

	private:
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

	public:
		virtual void OnReturnTo();

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CUSTOMHERO_GUI
