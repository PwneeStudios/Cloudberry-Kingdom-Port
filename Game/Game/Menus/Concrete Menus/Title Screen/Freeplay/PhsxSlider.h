#ifndef PHSXSLIDER
#define PHSXSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{
	class WrappedFloat;
}

namespace CloudberryKingdom
{
	class EzFont;
}

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class EzText;
}






namespace CloudberryKingdom
{
	class PhsxSlider : public MenuSlider
	{
	private:
		class PhsxDataSetter : public Lambda
		{
		private:
			BobPhsx::CustomData MyType;
			std::shared_ptr<WrappedFloat> MyFloat;

		public:
			PhsxDataSetter( BobPhsx::CustomData MyType, const std::shared_ptr<WrappedFloat> &MyFloat );

			void Apply();
		};

	public:
		virtual std::vector<std::wstring> GetViewables();

		static std::shared_ptr<EzFont> Font;
		static std::shared_ptr<Lambda_1<MenuItem*> > Process;

	private:
		BobPhsx::CustomData MyType;

	public:
		PhsxSlider( Localization::Words word, BobPhsx::CustomData type );

	private:
		bool _State;
	public:
		void setState( const bool &value );

		const bool &getState() const;

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PHSXSLIDER
