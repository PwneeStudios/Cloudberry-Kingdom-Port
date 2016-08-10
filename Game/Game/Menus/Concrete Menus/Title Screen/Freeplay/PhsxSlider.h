#ifndef PHSXSLIDER
#define PHSXSLIDER

#include <small_header.h>

#include "Game/Localization.h"
//#include "Core/Text/EzFont.h"
//#include "Core/Text/EzText.h"
//#include "Game/Menus/Menu Components/MenuItem.h"
#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Menus/Concrete Menus/Title Screen/Freeplay/CustomHero_GUI.h"
#include "Game/Menus/Menu Components/MenuSlider.h"
//#include "Game/Tools/WrappedFloat.h"


namespace CloudberryKingdom
{
	struct PhsxSlider : public MenuSlider
	{
	
		virtual ~PhsxSlider()
		{
#ifdef BOOST_BIN
			OnDestructor( "PhsxSlider" );
#endif
		}


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
		boost::shared_ptr<PhsxSlider> PhsxSlider_Construct( Localization::Words word, BobPhsx::CustomData type );
	
		bool _State;
	
		void setState( const bool &value );

		const bool &getState() const;

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef PHSXSLIDER
