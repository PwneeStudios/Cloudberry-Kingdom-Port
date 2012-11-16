#include "CkColorHelper.h"
#include "Core/Text/EzText.h"
#include "Game/Menus/Menu Components/MenuItem.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void CkColorHelper::RegularColor( const std::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( 255, 255, 255 ) ).ToVector4();
		name->OutlineColor = ( Color( 0, 0, 0 ) ).ToVector4();
	}

	void CkColorHelper::_x_x_MasochisticColor( const std::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( 0, 0, 0 ) ).ToVector4();
		name->OutlineColor = ( Color( 0, 255, 255 ) ).ToVector4();
	}

	void CkColorHelper::_x_x_HardcoreColor( const std::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( 0, 0, 0 ) ).ToVector4();
		name->OutlineColor = ( Color( 255, 10, 10 ) ).ToVector4();
	}

	void CkColorHelper::AbusiveColor( const std::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( 248, 136, 8 ) ).ToVector4();
		name->OutlineColor = ( Color( 248, 0, 8 ) ).ToVector4();
	}

	void CkColorHelper::UnpleasantColor( const std::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( 44, 203, 48 ) ).ToVector4();
		name->OutlineColor = ( Color( 0, 71, 0 ) ).ToVector4();
	}

	void CkColorHelper::_x_x_EasyColor( const std::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( 184, 240, 255 ) ).ToVector4();
		name->OutlineColor = ( Color( 37, 118, 158 ) ).ToVector4();
	}

	void CkColorHelper::_x_x_HappyBlueColor( const std::shared_ptr<EzText> &name )
	{
		name->MyFloatColor = ( Color( 26, 188, 241 ) ).ToVector4();
		name->OutlineColor = ( Color( 255, 255, 255 ) ).ToVector4();
	}

	void CkColorHelper::_x_x_Red( const std::shared_ptr<EzText> &text )
	{
		text->MyFloatColor = ( Color( 228, 0, 69 ) ).ToVector4();
		text->OutlineColor = Color::White.ToVector4();
	}

	void CkColorHelper::GreenItem( const std::shared_ptr<MenuItem> &item )
	{
		item->MyText->MyFloatColor = ( Color( 255, 255, 255 ) ).ToVector4();
		item->MySelectedText->MyFloatColor = ( Color( 50, 220, 50 ) ).ToVector4();
	}
}
