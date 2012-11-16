#ifndef COLORSELECT
#define COLORSELECT

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuList;
}

namespace CloudberryKingdom
{
	class CharacterSelect;
}




namespace CloudberryKingdom
{
	class ListSelectPanel : public CkBaseMenu
	{
	private:
		class OnSelectProxy : public Lambda
		{
		private:
			std::shared_ptr<ListSelectPanel> lsp;

		public:
			OnSelectProxy( const std::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	private:
		class BackProxy : public Lambda
		{
		private:
			std::shared_ptr<ListSelectPanel> lsp;

		public:
			BackProxy( const std::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	private:
		class SelectProxy : public Lambda
		{
		private:
			std::shared_ptr<ListSelectPanel> lsp;

		public:
			SelectProxy( const std::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	public:
		std::shared_ptr<MenuList> MyList;
	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
		int ClrSelectIndex;

	protected:
		virtual void ReleaseBody();

	public:
		void SetPos( Vector2 pos );

		void SetIndexViaAssociated( int index );

		int GetAssociatedIndex();

	private:
		Localization::Words Header;
		int HoldIndex;

	public:
		ListSelectPanel( int Control, Localization::Words Header, const std::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex );

	private:
		void OnSelect();

	public:
		virtual void Constructor();

		virtual void OnAdd();

	private:
		void Back();

		void Select();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef COLORSELECT
