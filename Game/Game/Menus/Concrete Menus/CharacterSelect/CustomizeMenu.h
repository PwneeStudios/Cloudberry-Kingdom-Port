#ifndef CUSTOMIZEMENU
#define CUSTOMIZEMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CustomizeMenu : public CkBaseMenu
	{
	
		struct GoProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<CustomizeMenu> cm;

		
			GoProxy( const std::shared_ptr<CustomizeMenu> &cm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct CreateColorSelectProxy : public Lambda
		{
		
			std::shared_ptr<CustomizeMenu> cm;

		
			CreateColorSelectProxy( const std::shared_ptr<CustomizeMenu> &cm );

			void Apply();
		};

	
		std::shared_ptr<CharacterSelect> MyCharacterSelect;

	
		virtual void ReleaseBody();

	
		CustomizeMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent );
		void CustomizeMenu_Construct( int Control, const std::shared_ptr<CharacterSelect> &Parent );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void Init();

	
		void SetPos();

		void Go( const std::shared_ptr<MenuItem> &item );

		//void AddMenuItem(string Text, string Name)
		void AddMenuItem( Localization::Words Word, const std::wstring &Name );

		void MakeItems();

	
		virtual void OnAdd();

	
		virtual void MyDraw();

	
		void CreateColorSelect();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CUSTOMIZEMENU
