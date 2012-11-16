#ifndef LEVELTITLE
#define LEVELTITLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class LevelTitle : public GUI_Panel
	{
	public:
		virtual void OnAdd();



		std::shared_ptr<EzText> text;
		LevelTitle( const std::wstring &str );
		LevelTitle( const std::wstring &str, Vector2 shift, float scale, bool perma );

		static std::shared_ptr<LevelTitle> HeroTitle( const std::wstring &str );

	private:
		bool Perma;
		void Init( const std::wstring &str, Vector2 shift, float scale, bool perma );

		int Count;
	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LEVELTITLE
