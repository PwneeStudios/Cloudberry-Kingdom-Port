#ifndef STARTMENU_MW_PRESSSTART
#define STARTMENU_MW_PRESSSTART

#include <global_header.h>

namespace CloudberryKingdom
{
	class TitleGameData_MW;
}

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class StartMenu_MW_PressStart : public CkBaseMenu
	{
	public:
		std::shared_ptr<TitleGameData_MW> Title;
		StartMenu_MW_PressStart( const std::shared_ptr<TitleGameData_MW> &Title );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

		virtual void OnAdd();

	private:
		std::shared_ptr<EzText> Text;
		int DelayToAllowInput;
	public:
		virtual void Init();

	private:
		void SetPos();

	protected:
		virtual void MyPhsxStep();

	private:
		float t;
	protected:
		virtual void MyDraw();

	public:
		virtual void OnReturnTo();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTMENU_MW_PRESSSTART
