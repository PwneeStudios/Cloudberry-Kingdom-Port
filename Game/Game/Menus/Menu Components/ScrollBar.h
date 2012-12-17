#ifndef SCROLLBAR
#define SCROLLBAR

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ScrollBar : public CkBaseMenu
	{
	
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
