#ifndef PHSXSLIDER
#define PHSXSLIDER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct PhsxSlider : public MenuSlider
	{
	
		struct PhsxDataSetter : public Lambda
		{
		
			BobPhsx::CustomData MyType;
			boost::shared_ptr<WrappedFloat> MyFloat;

		
			PhsxDataSetter( BobPhsx::CustomData MyType, const boost::shared_ptr<WrappedFloat> &MyFloat );

			void Apply();
		};

	
		virtual std::vector<std::wstring> GetViewables();

		static boost::shared_ptr<EzFont> Font;
		static boost::shared_ptr<Lambda_1<boost::shared_ptr<MenuItem> > > Process;

	
		BobPhsx::CustomData MyType;

	
		PhsxSlider( Localization::Words word, BobPhsx::CustomData type );

	
		bool _State;
	
		void setState( const bool &value );

		const bool &getState() const;

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PHSXSLIDER
