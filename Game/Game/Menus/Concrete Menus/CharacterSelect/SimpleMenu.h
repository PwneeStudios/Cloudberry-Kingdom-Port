#ifndef SIMPLEMENU
#define SIMPLEMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct SimpleMenuBase : public CkBaseMenu
	{
	
		static void InitializeStatics();

	
		struct SimpleToCustomProxy : public Lambda
		{
		
			std::shared_ptr<SimpleMenuBase> smb;

		
			SimpleToCustomProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleToDoneProxy : public Lambda
		{
		
			std::shared_ptr<SimpleMenuBase> smb;

		
			SimpleToDoneProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleToBackProxy : public Lambda
		{
		
			std::shared_ptr<SimpleMenuBase> smb;

		
			SimpleToBackProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleSelect_RightProxy : public Lambda
		{
		
			std::shared_ptr<SimpleMenuBase> smb;

		
			SimpleSelect_RightProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		struct SimpleSelect_LeftProxy : public Lambda
		{
		
			std::shared_ptr<SimpleMenuBase> smb;

		
			SimpleSelect_LeftProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		std::shared_ptr<ArrowMenu> Arrows;

	
		virtual void ReleaseBody();

	
		SimpleMenuBase( int Control, const std::shared_ptr<CharacterSelect> &Parent );
		std::shared_ptr<SimpleMenuBase> SimpleMenuBase_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent );

		virtual void OnAdd();

	
		Vector2 PrevDir;
		int NoMoveCount;
		static int NoMoveDuration;

	
		void SimpleToCustom();

		void SimpleToDone();

		void SimpleToBack();

	
		void ButtonPhsx();

		/// <summary>
		/// Select the next premade stickman to the right
		/// </summary>    
	
		void SimpleSelect_Right();

		/// <summary>
		/// Select the next premade stickman to the left
		/// </summary>
		void SimpleSelect_Left();

	
		virtual void MyPhsxStep();
	};

#if defined(PC_VERSION)
	struct SimpleMenu : public SimpleMenuBase
	{
	
		SimpleMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent );
		std::shared_ptr<SimpleMenu> SimpleMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void Init();

	
		void SetPos();
	};
#else
	struct SimpleMenu : public SimpleMenuBase
	{
	
		SimpleMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent );

		virtual void Init();

	
		void SetPos();

	
		virtual void MyPhsxStep();
	};
#endif
}


#endif	//#ifndef SIMPLEMENU
