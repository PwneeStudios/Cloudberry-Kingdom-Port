#ifndef SCROLLBAR
#define SCROLLBAR

#include <global_header.h>

namespace CloudberryKingdom
{
	class LongMenu;
}

namespace CloudberryKingdom
{
	class GUI_Panel;
}

namespace CloudberryKingdom
{
	class MenuSlider;
}




namespace CloudberryKingdom
{
	class ScrollBar : public CkBaseMenu
	{
	private:
		class ScrollBarReleaseLambda : public Lambda
		{
		private:
			std::shared_ptr<ScrollBar> sb;
		public:
			ScrollBarReleaseLambda( const std::shared_ptr<ScrollBar> &sb );

			void Apply();
		};

	private:
		class SliderSetProxy : public Lambda
		{
		private:
			std::shared_ptr<ScrollBar> Sb;

		public:
			SliderSetProxy( const std::shared_ptr<ScrollBar> &sb );

			void Apply();
		};

	private:
		class SliderGetLambda : public LambdaFunc<float>
		{
		private:
			std::shared_ptr<ScrollBar> sb;
		public:
			SliderGetLambda( const std::shared_ptr<ScrollBar> &sb );

			float Apply();
		};

	private:
		std::shared_ptr<LongMenu> AttachedMenu;
		std::shared_ptr<GUI_Panel> Parent;

	public:
		virtual std::wstring CopyToClipboard( const std::wstring &suffix );

		virtual void ProcessMouseInput( Vector2 shift, bool ShiftDown );

	protected:
		virtual void ReleaseBody();

	public:
		ScrollBar( const std::shared_ptr<LongMenu> &AttachedMenu, const std::shared_ptr<GUI_Panel> &Parent );

	private:
		std::shared_ptr<MenuSlider> slider;
	public:
		virtual void Init();

	private:
		float Height;

		float SliderGet();

		void SliderSet();

	protected:
		virtual void MyPhsxStep();

	public:
		const Vector2 &getBarPos() const;
		void setBarPos( const Vector2 &value );

	protected:
		virtual void MyDraw();

	public:
		virtual void OnAdd();
	};
}


#endif	//#ifndef SCROLLBAR
