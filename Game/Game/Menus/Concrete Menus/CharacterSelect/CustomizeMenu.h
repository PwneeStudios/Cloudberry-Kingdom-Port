#ifndef CUSTOMIZEMENU
#define CUSTOMIZEMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class CustomizeMenu : public CkBaseMenu
	{
	private:
		class GoProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<CustomizeMenu> cm;

		public:
			GoProxy( const std::shared_ptr<CustomizeMenu> &cm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class CreateColorSelectProxy : public Lambda
		{
		private:
			std::shared_ptr<CustomizeMenu> cm;

		public:
			CreateColorSelectProxy( const std::shared_ptr<CustomizeMenu> &cm );

			void Apply();
		};

	private:
		std::shared_ptr<CharacterSelect> MyCharacterSelect;

	protected:
		virtual void ReleaseBody();

	public:
		CustomizeMenu( int Control, const std::shared_ptr<CharacterSelect> &Parent );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void Init();

	private:
		void SetPos();

		void Go( const std::shared_ptr<MenuItem> &item );

		//void AddMenuItem(string Text, string Name)
		void AddMenuItem( Localization::Words Word, const std::wstring &Name );

		void MakeItems();

	public:
		virtual void OnAdd();

	protected:
		virtual void MyDraw();

	public:
		void CreateColorSelect();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef CUSTOMIZEMENU
