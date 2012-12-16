#include <global_header.h>



namespace CloudberryKingdom
{

	void CkColorHelper::RegularColor( const boost::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		name->OutlineColor = ( Color( static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ) ) ).ToVector4();
	}

	void CkColorHelper::_x_x_MasochisticColor( const boost::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ) ) ).ToVector4();
		name->OutlineColor = ( Color( static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
	}

	void CkColorHelper::_x_x_HardcoreColor( const boost::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 0 ) ) ).ToVector4();
		name->OutlineColor = ( Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 10 ), static_cast<unsigned char>( 10 ) ) ).ToVector4();
	}

	void CkColorHelper::AbusiveColor( const boost::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( static_cast<unsigned char>( 248 ), static_cast<unsigned char>( 136 ), static_cast<unsigned char>( 8 ) ) ).ToVector4();
		name->OutlineColor = ( Color( static_cast<unsigned char>( 248 ), static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 8 ) ) ).ToVector4();
	}

	void CkColorHelper::UnpleasantColor( const boost::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( static_cast<unsigned char>( 44 ), static_cast<unsigned char>( 203 ), static_cast<unsigned char>( 48 ) ) ).ToVector4();
		name->OutlineColor = ( Color( static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 71 ), static_cast<unsigned char>( 0 ) ) ).ToVector4();
	}

	void CkColorHelper::_x_x_EasyColor( const boost::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( static_cast<unsigned char>( 184 ), static_cast<unsigned char>( 240 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		name->OutlineColor = ( Color( static_cast<unsigned char>( 37 ), static_cast<unsigned char>( 118 ), static_cast<unsigned char>( 158 ) ) ).ToVector4();
	}

	void CkColorHelper::_x_x_HappyBlueColor( const boost::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( static_cast<unsigned char>( 26 ), static_cast<unsigned char>( 188 ), static_cast<unsigned char>( 241 ) ) ).ToVector4();
		name->OutlineColor = ( Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
	}

	void CkColorHelper::_x_x_Red( const boost::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( Color( static_cast<unsigned char>( 228 ), static_cast<unsigned char>( 0 ), static_cast<unsigned char>( 69 ) ) ).ToVector4();
		text->OutlineColor = Color::White.ToVector4();
	}

	void CkColorHelper::GreenItem( const boost::shared_ptr<MenuItem> &item )
	{
		item->MyText->MyFloatColor = ( Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) ).ToVector4();
		item->MySelectedText->MyFloatColor = ( Color( static_cast<unsigned char>( 50 ), static_cast<unsigned char>( 220 ), static_cast<unsigned char>( 50 ) ) ).ToVector4();
	}
}
