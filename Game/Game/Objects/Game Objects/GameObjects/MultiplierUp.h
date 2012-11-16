#ifndef MULTIPLIERUP
#define MULTIPLIERUP

#include "GUI_Panel.h"

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class MultiplierUp : public GUI_Panel
	{
	public:
		virtual void OnAdd();

	private:
		std::shared_ptr<EzText> text;
	public:
		MultiplierUp();
		MultiplierUp( Vector2 shift, float scale, bool perma );

	private:
		bool Perma;
		void Init( Vector2 shift, float scale, bool perma );

		int Count;
	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef MULTIPLIERUP
