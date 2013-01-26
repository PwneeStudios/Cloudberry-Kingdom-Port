#ifndef CUSTOMIZEMENU
#define CUSTOMIZEMENU

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CustomizeMenu : public CkBaseMenu
	{

		virtual ~CustomizeMenu() { }
	
		struct GoProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<CustomizeMenu> cm;

		
			GoProxy( const boost::shared_ptr<CustomizeMenu> &cm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct CreateColorSelectProxy : public Lambda
		{
		
			boost::shared_ptr<CustomizeMenu> cm;

		
			CreateColorSelectProxy( const boost::shared_ptr<CustomizeMenu> &cm );

			void Apply();
		};

	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;

	
		virtual void ReleaseBody();

	
		CustomizeMenu( int Control, const boost::shared_ptr<CharacterSelect> &Parent );
		boost::shared_ptr<CustomizeMenu> CustomizeMenu_Construct( int Control, const boost::shared_ptr<CharacterSelect> &Parent );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void Init();

	
		void SetPos();

		void Go( const boost::shared_ptr<MenuItem> &item );

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
