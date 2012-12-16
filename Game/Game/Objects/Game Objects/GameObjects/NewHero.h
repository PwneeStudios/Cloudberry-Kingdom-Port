#ifndef NEWHERO
#define NEWHERO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct NewHero : public GUI_Panel
	{
		virtual void OnAdd();

		boost::shared_ptr<EzText> text;
		NewHero( const std::wstring &str );
		boost::shared_ptr<NewHero> NewHero_Construct( const std::wstring &str );
		NewHero( const std::wstring &str, Vector2 shift, float scale, bool perma );
		boost::shared_ptr<NewHero> NewHero_Construct( const std::wstring &str, Vector2 shift, float scale, bool perma );

		static boost::shared_ptr<NewHero> HeroTitle( const std::wstring &str );

	
		bool Perma;
		void Init( const std::wstring &str, Vector2 shift, float scale, bool perma );

		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NEWHERO
