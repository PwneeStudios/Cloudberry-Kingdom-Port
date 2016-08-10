#ifndef SCROLLBAR
#define SCROLLBAR

#include <small_header.h>

//#include "Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/LongMenu.h"
//#include "Game/Menus/Menu Components/MenuSlider.h"
//#include "Game/Menus/Menu Components/MenuScrollBar.h"
//#include "Game/Tools/Tools.h"
//#include "Game/Tools/WrappedFloat.h"


namespace CloudberryKingdom
{
	struct ScrollBar : public CkBaseMenu
	{

		virtual ~ScrollBar()
		{
#ifdef BOOST_BIN
			OnDestructor( "ScrollBar" );
#endif
		}


		struct ScrollBarReleaseLambda : public Lambda
		{
		
			boost::shared_ptr<ScrollBar> sb;
		
			ScrollBarReleaseLambda( const boost::shared_ptr<ScrollBar> &sb );

			void Apply();
		};

	
		struct SliderSetProxy : public Lambda
		{
		
			boost::shared_ptr<ScrollBar> Sb;

		
			SliderSetProxy( const boost::shared_ptr<ScrollBar> &sb );

			void Apply();
		};

	
		struct SliderGetLambda : public LambdaFunc<float>
		{
		
			boost::shared_ptr<ScrollBar> sb;
		
			SliderGetLambda( const boost::shared_ptr<ScrollBar> &sb );

			float Apply();
		};

	
		boost::shared_ptr<LongMenu> AttachedMenu;
		boost::shared_ptr<GUI_Panel> Parent;

	
		virtual void ReleaseBody();

	
		ScrollBar( const boost::shared_ptr<LongMenu> &AttachedMenu, const boost::shared_ptr<GUI_Panel> &Parent );
		boost::shared_ptr<ScrollBar> ScrollBar_Construct( const boost::shared_ptr<LongMenu> &AttachedMenu, const boost::shared_ptr<GUI_Panel> &Parent );

	
		boost::shared_ptr<MenuSlider> slider;
	
		virtual void Init();

	
		float Height;

		float SliderGet();

		void SliderSet();

	
		virtual void MyPhsxStep();

	
		const Vector2 &getBarPos() const;
		void setBarPos( const Vector2 &value );

	
		virtual void MyDraw();

	
		virtual void OnAdd();
	};
}


#endif	//#ifndef SCROLLBAR
