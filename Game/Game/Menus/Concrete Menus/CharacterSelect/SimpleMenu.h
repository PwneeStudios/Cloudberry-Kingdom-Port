#ifndef SIMPLEMENU
#define SIMPLEMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class ArrowMenu;
}

namespace CloudberryKingdom
{
	class MenuItem;
}






namespace CloudberryKingdom
{
	class SimpleMenuBase : public CkBaseMenu
	{
	protected:
		class SimpleToCustomProxy : public Lambda
		{
		private:
			std::shared_ptr<SimpleMenuBase> smb;

		public:
			SimpleToCustomProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	protected:
		class SimpleToDoneProxy : public Lambda
		{
		private:
			std::shared_ptr<SimpleMenuBase> smb;

		public:
			SimpleToDoneProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	protected:
		class SimpleToBackProxy : public Lambda
		{
		private:
			std::shared_ptr<SimpleMenuBase> smb;

		public:
			SimpleToBackProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	public:
		class SimpleSelect_RightProxy : public Lambda
		{
		private:
			std::shared_ptr<SimpleMenuBase> smb;

		public:
			SimpleSelect_RightProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	public:
		class SimpleSelect_LeftProxy : public Lambda
		{
		private:
			std::shared_ptr<SimpleMenuBase> smb;

		public:
			SimpleSelect_LeftProxy( const std::shared_ptr<SimpleMenuBase> &smb );

			void Apply();
		};

	protected:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
	private:
		std::shared_ptr<ArrowMenu> Arrows;

	protected:
		virtual void ReleaseBody();

	public:
		SimpleMenuBase( int Control, const std::shared_ptr<CharacterSelect> &Parent );

		virtual void OnAdd();

	private:
		Vector2 PrevDir;
		int NoMoveCount;
		static int NoMoveDuration;

	public:
		void SimpleToCustom();

		void SimpleToDone();

		void SimpleToBack();

	private:
		void ButtonPhsx();

		/// <summary>
		/// Select the next premade stickman to the right
		/// </summary>    
	public:
		void SimpleSelect_Right();

		/// <summary>
		/// Select the next premade stickman to the left
		/// </summary>
		void SimpleSelect_Left();

	protected:
		virtual void MyPhsxStep();
	};

#if defined(PC_VERSION)
	class SimpleMenu : public SimpleMenuBase
	{
	public:
		SimpleMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void Init();

	private:
		void SetPos();
	};
#else
	class SimpleMenu : public SimpleMenuBase
	{
	public:
		SimpleMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent );

		virtual void Init();

	private:
		void SetPos();

	protected:
		virtual void MyPhsxStep();
	};
#endif
}


#endif	//#ifndef SIMPLEMENU
