#ifndef STARTMENU_MW_BACKPANEL
#define STARTMENU_MW_BACKPANEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class StartMenu_MW_Backpanel : public CkBaseMenu
	{
	public:
		enum State
		{
			State_NONE,
							State_SCENE_TITLE,
							State_SCENE,
							State_SCENE_BLUR,
							State_SCENE_PRINCESS,
							State_SCENE_NO_BOB_BRIGHTEN,
							State_SCENE_BLUR_DARK,
							State_SCENE_KOBBLER,
							State_SCENE_KOBBLER_BLUR
		};
	public:
		virtual void Hide( const std::shared_ptr<PresetPos> &pos, int frames );

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

		virtual void OnAdd();

		void InitialZoomIn();

	private:
		std::shared_ptr<QuadClass> Scene, Title, Title_Trim, Scene_NoBob_Blur, Scene_Blur, Scene_Princess, Scene_NoBob_Brighten, Scene_Kobbler, Scene_Kobbler_Blur;
	public:
		virtual void Init();

		void SetState( State state );
	private:
		State MyState;

		void BlackBox();

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

public:
		StartMenu_MW_Backpanel()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef STARTMENU_MW_BACKPANEL
