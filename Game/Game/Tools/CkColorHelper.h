#ifndef CKCOLORHELPER
#define CKCOLORHELPER

namespace CloudberryKingdom
{
	struct EzText;
}

namespace CloudberryKingdom
{
	struct MenuItem;
}




namespace CloudberryKingdom
{
	struct CkColorHelper
	{
	
		static void RegularColor( const boost::shared_ptr<EzText> &name );

		static void _x_x_MasochisticColor( const boost::shared_ptr<EzText> &name );

		static void _x_x_HardcoreColor( const boost::shared_ptr<EzText> &name );

		static void AbusiveColor( const boost::shared_ptr<EzText> &name );

		static void UnpleasantColor( const boost::shared_ptr<EzText> &name );

		static void _x_x_EasyColor( const boost::shared_ptr<EzText> &name );

		static void _x_x_HappyBlueColor( const boost::shared_ptr<EzText> &name );

		static void _x_x_Red( const boost::shared_ptr<EzText> &text );

		static void GreenItem( const boost::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef CKCOLORHELPER
