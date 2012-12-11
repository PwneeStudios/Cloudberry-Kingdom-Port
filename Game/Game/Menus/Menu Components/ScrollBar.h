#ifndef SCROLLBAR
#define SCROLLBAR

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ScrollBar : public CkBaseMenu
	{
	
		struct ScrollBarReleaseLambda : public Lambda
		{
		
			std::shared_ptr<ScrollBar> sb;
		
			ScrollBarReleaseLambda( const std::shared_ptr<ScrollBar> &sb );

			void Apply();
		};

	
		struct SliderSetProxy : public Lambda
		{
		
			std::shared_ptr<ScrollBar> Sb;

		
			SliderSetProxy( const std::shared_ptr<ScrollBar> &sb );

			void Apply();
		};

	
		struct SliderGetLambda : public LambdaFunc<float>
		{
		
			std::shared_ptr<ScrollBar> sb;
		
			SliderGetLambda( const std::shared_ptr<ScrollBar> &sb );

			float Apply();
		};

	
		std::shared_ptr<LongMenu> AttachedMenu;
		std::shared_ptr<GUI_Panel> Parent;

	
		virtual void ReleaseBody();

	
		ScrollBar( const std::shared_ptr<LongMenu> &AttachedMenu, const std::shared_ptr<GUI_Panel> &Parent );

	
		std::shared_ptr<MenuSlider> slider;
	
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
