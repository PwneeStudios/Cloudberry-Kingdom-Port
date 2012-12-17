#ifndef LEVELTITLE
#define LEVELTITLE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct LevelTitle : public GUI_Panel
	{
	
		virtual void OnAdd();

		boost::shared_ptr<EzText> text;
		LevelTitle( const std::wstring &str );
		boost::shared_ptr<LevelTitle> LevelTitle_Construct( const std::wstring &str );
		LevelTitle( const std::wstring &str, Vector2 shift, float scale, bool perma );
		boost::shared_ptr<LevelTitle> LevelTitle_Construct( const std::wstring &str, Vector2 shift, float scale, bool perma );

		static boost::shared_ptr<LevelTitle> HeroTitle( const std::wstring &str );

	
		bool Perma;
		void Init( const std::wstring &str, Vector2 shift, float scale, bool perma );

		int Count;
	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LEVELTITLE
