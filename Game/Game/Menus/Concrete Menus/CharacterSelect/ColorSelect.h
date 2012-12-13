#ifndef COLORSELECT
#define COLORSELECT

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ListSelectPanel : public CkBaseMenu
	{
	
		struct OnSelectProxy : public Lambda
		{
		
			std::shared_ptr<ListSelectPanel> lsp;

		
			OnSelectProxy( const std::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	
		struct BackProxy : public Lambda
		{
		
			std::shared_ptr<ListSelectPanel> lsp;

		
			BackProxy( const std::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	
		struct SelectProxy : public Lambda
		{
		
			std::shared_ptr<ListSelectPanel> lsp;

		
			SelectProxy( const std::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	
		std::shared_ptr<MenuList> MyList;
	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;
		int ClrSelectIndex;

	
		virtual void ReleaseBody();

	
		void SetPos( Vector2 pos );

		void SetIndexViaAssociated( int index );

		int GetAssociatedIndex();

	
		Localization::Words Header;
		int HoldIndex;

	
		ListSelectPanel( int Control, Localization::Words Header, const std::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex );
		void ListSelectPanel_Construct( int Control, Localization::Words Header, const std::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex );

	
		void OnSelect();

	
		virtual void Constructor();

		virtual void OnAdd();

	
		void Back();

		void Select();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef COLORSELECT
