#ifndef STARTMENU_MW_BLACK
#define STARTMENU_MW_BLACK

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}




namespace CloudberryKingdom
{
	class StartMenu_MW_Black : public CkBaseMenu
	{
	public:
		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

		virtual void OnAdd();

		StartMenu_MW_Black();

	private:
		std::shared_ptr<QuadClass> Black;
	public:
		virtual void Init();

	private:
		void BlackBox();

	public:
		void SlideFromRight();

	protected:
		virtual void MyPhsxStep();

	public:
		virtual void OnReturnTo();
	};
}


#endif	//#ifndef STARTMENU_MW_BLACK
