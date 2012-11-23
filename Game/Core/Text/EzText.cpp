#include <global_header.h>



namespace CloudberryKingdom
{

#if defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getGo()
	{
		return Tools::TextureWad->FindByName( _T( "Enter_Key" ) );
	}
#endif

#if defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getBack()
	{
		return Tools::TextureWad->FindByName( _T( "Esc_Key" ) );
	}
#endif

#if defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getX()
	{
	return ButtonString::KeyToTexture( ButtonCheck::SlowMoToggle_Secondary );
	//return Tools.TextureWad.FindByName("Xbox_X");
	}
#endif

#if defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getLeftRight()
	{
		return Tools::TextureWad->FindByName( _T( "LeftRight_Key" ) );
	}
#endif

#if defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getLeftBumper()
	{
		return ButtonString::KeyToTexture( ButtonCheck::ReplayPrev_Secondary );
	}
#endif

#if defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getRightBumper()
	{
		return ButtonString::KeyToTexture( ButtonCheck::ReplayNext_Secondary );
	}
#endif

#if ! defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getGo()
	{
		return Tools::TextureWad->FindByName( _T( "Xbox_A" ) );
	}
#endif

#if ! defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getBack()
	{
		return Tools::TextureWad->FindByName( _T( "Xbox_B" ) );
	}
#endif

#if ! defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getX()
	{
		return Tools::TextureWad->FindByName( _T( "Xbox_X" ) );
	}
#endif

#if ! defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getLeftRight()
	{
		return Tools::TextureWad->FindByName( _T( "Xbox_Dir" ) );
	}
#endif

#if ! defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getLeftBumper()
	{
		return Tools::TextureWad->FindByName( _T( "Xbox_LB" ) );
	}
#endif

#if ! defined(PC_VERSION)
	const std::shared_ptr<EzTexture> &ButtonTexture::getRightBumper()
	{
		return Tools::TextureWad->FindByName( _T( "Xbox_RB" ) );
	}
#endif

#if defined(PC_VERSION)
std::map<Keys, std::wstring> ButtonString::KeyToString = 0;
#endif

#if defined(PC_VERSION)
	void ButtonString::Init()
	{
		KeyToString = std::map<Keys, std::wstring>();

		KeyToString.insert( make_pair( Keys_None, _T( "None" ) ) );

		KeyToString.insert( make_pair( Keys_A, _T( "A" ) ) );
		KeyToString.insert( make_pair( Keys_B, _T( "B" ) ) );
		KeyToString.insert( make_pair( Keys_C, _T( "C" ) ) );
		KeyToString.insert( make_pair( Keys_D, _T( "D" ) ) );
		KeyToString.insert( make_pair( Keys_E, _T( "E" ) ) );
		KeyToString.insert( make_pair( Keys_F, _T( "F" ) ) );
		KeyToString.insert( make_pair( Keys_G, _T( "G" ) ) );
		KeyToString.insert( make_pair( Keys_H, _T( "H" ) ) );
		KeyToString.insert( make_pair( Keys_I, _T( "I" ) ) );
		KeyToString.insert( make_pair( Keys_J, _T( "J" ) ) );
		KeyToString.insert( make_pair( Keys_K, _T( "K" ) ) );
		KeyToString.insert( make_pair( Keys_L, _T( "L" ) ) );
		KeyToString.insert( make_pair( Keys_M, _T( "M" ) ) );
		KeyToString.insert( make_pair( Keys_N, _T( "N" ) ) );
		KeyToString.insert( make_pair( Keys_O, _T( "O" ) ) );
		KeyToString.insert( make_pair( Keys_P, _T( "P" ) ) );
		KeyToString.insert( make_pair( Keys_Q, _T( "Q" ) ) );
		KeyToString.insert( make_pair( Keys_R, _T( "R" ) ) );
		KeyToString.insert( make_pair( Keys_S, _T( "S" ) ) );
		KeyToString.insert( make_pair( Keys_T, _T( "T" ) ) );
		KeyToString.insert( make_pair( Keys_U, _T( "U" ) ) );
		KeyToString.insert( make_pair( Keys_V, _T( "V" ) ) );
		KeyToString.insert( make_pair( Keys_W, _T( "W" ) ) );
		KeyToString.insert( make_pair( Keys_X, _T( "X" ) ) );
		KeyToString.insert( make_pair( Keys_Y, _T( "Y" ) ) );
		KeyToString.insert( make_pair( Keys_Z, _T( "Z" ) ) );

		KeyToString.insert( make_pair( Keys_Enter, _T( "Enter" ) ) );
		KeyToString.insert( make_pair( Keys_Space, _T( "Space" ) ) );
		KeyToString.insert( make_pair( Keys_Back, _T( "Backspace" ) ) );
		KeyToString.insert( make_pair( Keys_Escape, _T( "Esc" ) ) );

		//KeyToString.Add(Keys.OemPeriod, ".");
		//KeyToString.Add(Keys.OemComma, ",");
		//KeyToString.Add(Keys.OemBackslash, "\\");
		//KeyToString.Add(Keys.OemQuestion, "?");
		//KeyToString.Add(Keys.OemOpenBrackets, "[");
		//KeyToString.Add(Keys.OemCloseBrackets, "]");

		//KeyToString.Add(Keys.RightControl, "R Cntrl");
		//KeyToString.Add(Keys.LeftControl, "L Cntrl");
		//KeyToString.Add(Keys.RightAlt, "R Alt");
		//KeyToString.Add(Keys.LeftAlt, "L Alt");
		//KeyToString.Add(Keys.RightShift, "R Shift");
		//KeyToString.Add(Keys.LeftShift, "L Shift");
	}
#endif

#if defined(PC_VERSION)
	void ButtonString::SetKeyFromString( Keys &key, const std::wstring &str )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::map<Keys, std::wstring>::const_iterator pair = KeyToString.begin(); pair != KeyToString.end(); ++pair )
		{
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( str, ( *pair )->Value, true ) == 0 )
			{
				key = ( *pair )->Key;
				return;
			}
		}
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::KeyToTexture( Keys key )
	{
		std::wstring str;
		try
		{
			str = KeyToString[ key ] + _T( "_Key" );
		}
		catch ( ... )
		{
			str = _T( "White" );
		}

		return str;
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Back( int size )
	{
		return _T( "" );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Go( int size )
	{
		return _T( "" );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Backspace( int size )
	{
		return std::wstring::Format( _T( "{{p{1},{0},?}}{{s70,0}}" ), size, KeyToTexture( Keys::Back ) );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Enter( int size )
	{
		return std::wstring::Format( _T( "{{p{1},{0},?}}{{s70,0}}" ), size, KeyToTexture( Keys::Enter ) );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::X( int size )
	{
		return std::wstring::Format( _T( "{{p{1},{0},?}}{{s15,0}}" ), size, KeyToTexture( ButtonCheck::SlowMoToggle_Secondary ) );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Y( int size )
	{
		return std::wstring::Format( _T( "{{p{1},{0},?}}{{s15,0}}" ), size, KeyToTexture( ButtonCheck::Help_KeyboardKey->KeyboardKey ) );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::LeftRight( int size )
	{
		return std::wstring::Format( _T( "{{pLeftRight_Key,{0},?}}{{s15,0}}" ), size );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::LeftBumper( int size )
	{
		return std::wstring::Format( _T( "{{p{1},{0},?}}{{s15,0}}" ), size, KeyToTexture( ButtonCheck::ReplayPrev_Secondary ) );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::RightBumper( int size )
	{
		return std::wstring::Format( _T( "{{p{1},{0},?}}{{s15,0}}" ), size, KeyToTexture( ButtonCheck::ReplayNext_Secondary ) );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Up( int size )
	{
		return std::wstring::Format( _T( "{{pUp_Key,{0},?}}{{s15,0}}" ), size );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Jump( int size )
	{
		return std::wstring::Format( _T( "{{pUp_Key,{0},?}}{{s15,0}}" ), size );
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::KeyStr( Keys key, int size )
	{
		if ( key == Keys::Enter || key == Keys::Space )
			size = static_cast<int>( 2.0083f * size );

		switch ( key )
		{
			//case Keys.Space:
			//    return string.Format("{{pSpace_Key,{0},?}}{{s15,0}}", size * BackScale);
			//case Keys.Enter:
			//    return string.Format("{{pEnter_Key,{0},?}}{{s15,0}}", size * BackScale);
			default:
				return std::wstring::Format( _T( "{{p{0},{1},?}}{{s15,0}}" ), ButtonString::KeyToTexture( key ), size );
		}
	}
#endif

#if defined(PC_VERSION)
	std::wstring ButtonString::Go_Controller( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_A,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	void ButtonString::Init()
	{
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::Back( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_B,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::Go( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_A,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::X( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_X,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::Y( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_Y,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::LeftRight( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_Dir,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::LeftBumper( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_LB,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::RightBumper( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_RB,{0},?}}" ), size );
	}
#endif

#if ! defined(PC_VERSION)
	std::wstring ButtonString::Jump( int size )
	{
		return std::wstring::Format( _T( "{{pXbox_A,{0},?}}" ), size );
	}
#endif

	std::vector<std::wstring> EzText::GetViewables()
	{
		const std::wstring* tempVector[] = { _T( "Name" ), _T( "MyString" ), _T( "Code" ), _T( "FancyPos" ), _T( "_Pos" ), _T( "Shadow" ), _T( "PicShadow" ), _T( "ShadowOffset" ), _T( "ShadowColor" ), _T( "ShadowScale" ), _T( "Alpha" ), _T( "MyColor" ), _T( "MyFloatColor" ) };
		return std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}

	std::wstring EzText::GetConstructorString()
	{
		return std::wstring::Format( _T( "new EzText(\"{0}\", ItemFont)" ), MyString );
	}

	void EzText::ProcessMouseInput( Vector2 shift, bool ShiftDown )
	{
		if ( ShiftDown )
			setScale( getScale() + (shift.X + shift.Y) *.00003f );
		else
			setPos( getPos() + shift );
	}

	std::wstring EzText::ColorToMarkup( int r, int g, int b )
	{
		return ColorToMarkup( r, g, b, 0, 0 );
	}

	std::wstring EzText::ColorToMarkup( int r, int g, int b, int shift )
	{
		return ColorToMarkup( r, g, b, shift, 0 );
	}

	std::wstring EzText::ColorToMarkup( int r, int g, int b, int shift, const std::wstring &bit )
	{
		return ColorToMarkup( Color( r, g, b ), shift, bit );
	}

	std::wstring EzText::ColorToMarkup( Color clr )
	{
		return ColorToMarkup( clr, 0, 0 );
	}

	std::wstring EzText::ColorToMarkup( Color clr, int shift )
	{
		return ColorToMarkup( clr, shift, 0 );
	}

	std::wstring EzText::ColorToMarkup( Color clr, int shift, const std::wstring &bit )
	{
		if ( bit != _T( "" ) )
		{
			return ColorToMarkup( clr, shift ) + bit + ColorToMarkup( Color::White, shift );
		}

		std::wstring str = std::wstring::Format( _T( "{{c{0},{1},{2},{3}}}" ), clr.R, clr.G, clr.B, clr.A );
		if ( shift != 0 )
		{
			std::wstring shiftstr = std::wstring::Format( _T( "{{s{0},0}}" ), shift );
			str += shiftstr;
		}

		return str;
	}

	bool EzText::HitTest( Vector2 pos )
	{
		return HitTest( pos, Vector2::Zero );
	}

	bool EzText::HitTest( Vector2 pos, Vector2 padding )
	{
		CalcBounds();
		if ( pos.X > TR.X + padding.X )
			return false;
		if ( pos.X < BL.X - padding.X )
			return false;
		if ( pos.Y > TR.Y + padding.Y )
			return false;
		if ( pos.Y < BL.Y - padding.Y )
			return false;

		return true;
	}

	void EzText::SubstituteText( const std::wstring &text )
	{
		Bits[ 0 ]->str = text;
		Bits[ 0 ]->builder_str.reset();
		TextWidth -= Bits[ 0 ]->size->X;
		Bits[ 0 ]->size = MyFont->Font->MeasureString( text );
		TextWidth += Bits[ 0 ]->size->X;
	}

	void EzText::SubstituteText( const std::shared_ptr<StringBuilder> &text )
	{
		Bits[ 0 ]->builder_str = text;
		TextWidth -= Bits[ 0 ]->size->X;
		Bits[ 0 ]->size = MyFont->Font->MeasureString( text );
		TextWidth += Bits[ 0 ]->size->X;
	}

	void EzText::SubstituteText( Localization::Words word )
	{
		Tools::Warning();
		SubstituteText( Localization::WordString( word ) );
	}

	void EzText::AppendText( const std::wstring &text )
	{
		SubstituteText( Bits[ 0 ]->str + text );
	}

	void EzText::AppendText( wchar_t character )
	{
		SubstituteText( Bits[ 0 ]->str + character );
	}

	std::wstring EzText::FirstString()
	{
		if ( Bits.empty() )
			return _T( "" );
		else
			return Bits[ 0 ]->str;
	}

	void EzText::MakeFancyPos()
	{
		if ( FancyPos != 0 )
			FancyPos->Release();
		FancyPos = std::make_shared<FancyVector2>();
		FancyPos->RelVal = _Pos;
		;
	}

	const Microsoft::Xna::Framework::Vector2 &EzText::getPos() const
	{
		if ( FancyPos == 0 )
			return _Pos;
		else
			return FancyPos->RelVal;
	}

	void EzText::setPos( const Vector2 &value )
	{
		if ( FancyPos == 0 )
			_Pos = value;
		else
			FancyPos->RelVal = value;
	}

	const float &EzText::getX() const
	{
		if ( FancyPos == 0 )
			return _Pos.X;
		else
			return FancyPos->RelVal.X;
	}

	void EzText::setX( const float &value )
	{
		if ( FancyPos == 0 )
			_Pos.X = value;
		else
			FancyPos->setRelValX( value );
	}

	const float &EzText::getY() const
	{
		if ( FancyPos == 0 )
			return _Pos.Y;
		else
			return FancyPos->RelVal.Y;
	}

	void EzText::setY( const float &value )
	{
		if ( FancyPos == 0 )
			_Pos.Y = value;
		else
			FancyPos->setRelValY( value );
	}

	void EzText::setScale( const float &value )
	{
		_Scale = value;
	}

	const float &EzText::getScale() const
	{
		return _Scale;
	}

	void EzText::Release()
	{
		if ( FancyPos != 0 )
			FancyPos->Release();
			FancyPos.reset();
	}

	std::shared_ptr<EzText> EzText::Clone()
	{
		std::shared_ptr<EzText> clone = std::make_shared<EzText>( MyString, MyFont,TextBoxWidth, Centered, YCentered, LineHeightMod );
		clone->MyFloatColor = MyFloatColor;
		clone->OutlineColor = OutlineColor;
		return clone;
	}

	EzText::EzText( Localization::Words word )
	{
		InitializeInstanceFields();
		MyFont = Resources::Font_Grobold42;
		Init( Localization::WordString( word ) );
	}

	EzText::EzText( Localization::Words word, const std::shared_ptr<EzFont> &font )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( Localization::WordString( word ) );
	}

	EzText::EzText( Localization::Words word, const std::shared_ptr<EzFont> &font, const std::wstring &Name )
	{
		InitializeInstanceFields();
		this->Name = Name;
		MyFont = font;
		Init( Localization::WordString( word ) );
	}

	EzText::EzText( Localization::Words word, const std::shared_ptr<EzFont> &font, bool Centered )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( Localization::WordString( word ), 10000, Centered, false, 1 );
	}

	EzText::EzText( Localization::Words word, const std::shared_ptr<EzFont> &font, bool Centered, bool YCentered )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( Localization::WordString( word ), 10000, Centered, YCentered, 1 );
	}

	EzText::EzText( Localization::Words word, const std::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( Localization::WordString( word ), Width, Centered, YCentered, 1 );
	}

	EzText::EzText( Localization::Words word, const std::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered, float LineHeightMod )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( Localization::WordString( word ), Width, Centered, YCentered, LineHeightMod );
	}

	EzText::EzText( const std::wstring &str )
	{
		InitializeInstanceFields();
		MyFont = Resources::Font_Grobold42;
		Init( str );
	}

	EzText::EzText( const std::wstring &str, const std::shared_ptr<EzFont> &font )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( str );
	}

	EzText::EzText( const std::wstring &str, const std::shared_ptr<EzFont> &font, const std::wstring &Name )
	{
		InitializeInstanceFields();
		this->Name = Name;
		MyFont = font;
		Init( str );
	}

	EzText::EzText( const std::wstring &str, const std::shared_ptr<EzFont> &font, bool Centered )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( str, 10000, Centered, false, 1 );
	}

	EzText::EzText( const std::wstring &str, const std::shared_ptr<EzFont> &font, bool Centered, bool YCentered )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( str, 10000, Centered, YCentered, 1 );
	}

	EzText::EzText( const std::wstring &str, const std::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( str, Width, Centered, YCentered, 1 );
	}

	EzText::EzText( const std::wstring &str, const std::shared_ptr<EzFont> &font, float Width, bool Centered, bool YCentered, float LineHeightMod )
	{
		InitializeInstanceFields();
		MyFont = font;
		Init( str, Width, Centered, YCentered, LineHeightMod );
	}

	void EzText::CheckForLineEnd( Vector2 TextSize )
	{
		LineHeight = __max( LineHeight, TextSize.Y );
		if ( TextSize.X + loc.X > TextBoxWidth && loc.X != 0 )
		{
			loc.X = 0;
			loc.Y += LineHeight;
			LineHeight = 0;
		}
	}

	std::wstring EzText::ColorToCode( Color clr )
	{
		return std::wstring::Format( _T( "{{c{0}, {1}, {2}, {3}}}" ), clr.R, clr.G, clr.B, clr.A );
	}

	void EzText::Parse( const std::wstring &str )
	{
		wchar_t c = str[ 1 ];

		int Comma1, Comma2, Comma3;
		std::wstring WidthString, HeightString;
		switch ( c )
		{
			case L'p':
				Parse_Type = ParseData_PIC;

//C# TO C++ CONVERTER TODO TASK: There is no direct native C++ equivalent to the .NET String 'Split' method:
				std::vector<std::wstring> string_bits = str.Split( L',' );

				Comma1 = str.find( _T( "," ) );
				Comma2 = str.find( _T( "," ), Comma1 + 1 );

				Parse_PicName = str.substr( 2, Comma1 - 2 );
				WidthString = string_bits[ 1 ];
				HeightString = string_bits[ 2 ];

				AsPaint = false;
				if ( string_bits.size() > 3 )
				{
					Parse_PicShift = Vector2( float::Parse( string_bits[ 3 ] ), float::Parse( string_bits[ 4 ] ) ) * Tools::TheGame->Resolution.LineHeightMod;
					if ( string_bits.size() > 5 )
						AsPaint = int::Parse( string_bits[ 5 ] ) > 0;
				}
				else
					Parse_PicShift = Vector2::Zero;

				Vector2 size;
				std::shared_ptr<EzTexture> texture = Tools::TextureWad->FindByName( Parse_PicName );
				float ratio = static_cast<float>( texture->Width ) / static_cast<float>( texture->Height );

				// 's' scale the texture
				if ( WidthString.find( L's' ) != string::npos )
				{
					size = Vector2( texture->Width, texture->Height );
					size *= float::Parse( HeightString );
				}
				// '?' calculates that number from the texture height/width ratio
				else if ( WidthString.find( L'?' ) != string::npos )
				{
					size = Vector2( 0, float::Parse( HeightString ) );
					size.X = size.Y * ratio;
				}
				else if ( HeightString.find( L'?' ) != string::npos )
				{
					size = Vector2( float::Parse( WidthString ), 0 );
					size.Y = size.X / ratio;
				}
				else
					size = Vector2( float::Parse( WidthString ), float::Parse( HeightString ) );
				Parse_PicSize = size * Tools::TheGame->Resolution.LineHeightMod;
				break;

			// Blank space
			case L's':
				Parse_Type = ParseData_PIC;
				Parse_PicName = _T( "Transparent" );

				Comma1 = str.find( _T( "," ) );

				WidthString = str.substr( 2, Comma1 - 2 );
				HeightString = str.substr( Comma1 + 1 );
				Parse_PicSize = Vector2( float::Parse( WidthString ), float::Parse( HeightString ) );
				Parse_PicSize *= Tools::TheGame->Resolution.LineHeightMod;
				break;

			case L'c':
				Parse_Type = ParseData_COLOR;

				Comma1 = str.find( _T( "," ) );
				Comma2 = str.find( _T( "," ), Comma1 + 1 );
				Comma3 = str.find( _T( "," ), Comma2 + 1 );

				std::wstring RString = str.substr( 2, Comma1 - 2 );
				std::wstring GString = str.substr( Comma1 + 1, Comma2 - 1 - Comma1 );
				std::wstring BString = str.substr( Comma2 + 1, Comma3 - 1 - Comma2 );
				std::wstring AString = str.substr( Comma3 + 1 );

				Parse_Color = Color( unsigned char::Parse( RString ), unsigned char::Parse( GString ), unsigned char::Parse( BString ), unsigned char::Parse( AString ) );
				break;
		}
	}

	int EzText::GetLineEnd( const std::wstring &str )
	{
		int EndIndex = 0;
		int NewEndIndex;
		int BracketIndex, SpaceIndex, DelimiterIndex;

		bool ReachedEnd = false;
		while ( !ReachedEnd )
		{
			BracketIndex = str.find( _T( "}" ), EndIndex );
			SpaceIndex = str.find( _T( " " ), EndIndex );
			DelimiterIndex = str.find( L'\n', EndIndex );
			if ( BracketIndex == -1 && SpaceIndex == -1 )
			{
				NewEndIndex = str.length();
				ReachedEnd = true;
			}
			else if ( BracketIndex == -1 )
				NewEndIndex = SpaceIndex + 1;
			else if ( SpaceIndex == -1 )
				NewEndIndex = BracketIndex + 1;
			else
				NewEndIndex = BracketIndex + 1;

			if ( DelimiterIndex >= 0 && DelimiterIndex < NewEndIndex )
			{
				NewEndIndex = DelimiterIndex;
				ReachedEnd = true;
			}

			float width = StringSize( str.substr( 0, NewEndIndex ) ).X;
			if ( width > TextBoxWidth && EndIndex > 0 )
				return EndIndex;
			else
				EndIndex = NewEndIndex;
		}

		return EndIndex;
	}

	Microsoft::Xna::Framework::Vector2 EzText::StringSize( const std::wstring &str )
	{
		MyFont->FixFont();

		Vector2 Size = Vector2::Zero;
		int BeginBracketIndex, EndBracketIndex;
		bool flag = false;

		while ( !flag )
		{
			BeginBracketIndex = str.find( _T( "{" ), 0 );
			if ( BeginBracketIndex >= 0 )
			{
				EndBracketIndex = str.find( _T( "}" ), 0 );
				std::wstring PicStr = str.substr( BeginBracketIndex, EndBracketIndex - BeginBracketIndex );
				Parse( PicStr );
				str = str.erase( BeginBracketIndex, EndBracketIndex - BeginBracketIndex + 1 );

				if ( Parse_Type == ParseData_PIC )
				{
					Size.X += Parse_PicSize.X;
					Size.Y = __max( Size.Y, Parse_PicSize.Y );
				}
			}
			else
				flag = true;
		}

		Vector2 TextSize = MyFont->Font->MeasureString( str );
		TextSize.Y *= Tools::TheGame->Resolution.LineHeightMod;

		Size.X += TextSize.X;
		Size.Y = __max( Size.Y, TextSize.Y );

		return Size;
	}

	float EzText::AddLine( const std::wstring &str, float StartX, float StartY, int LineNumber )
	{
		MyFont->FixFont();

		Vector2 loc = Vector2( StartX, 0 );
		float LineHeight = MyFont->Font->MeasureString( _T( " " ) )->Y;
		int BeginBracketIndex, EndBracketIndex;

		bool FirstElement = true;

		while ( str.length() > 0 )
		{
			BeginBracketIndex = str.find( _T( "{" ), 0 );
			if ( BeginBracketIndex == 0 )
			{
				EndBracketIndex = str.find( _T( "}" ), 0 );
				std::wstring PicStr = str.substr( BeginBracketIndex, EndBracketIndex - BeginBracketIndex );
				Parse( PicStr );
				str = str.erase( BeginBracketIndex, EndBracketIndex - BeginBracketIndex + 1 );

				// Parse picture info
				if ( Parse_Type == ParseData_PIC )
				{
					std::shared_ptr<EzTextPic> pic = std::make_shared<EzTextPic>();
					pic->LineNumber = LineNumber;

					if ( !FirstElement )
						Parse_PicShift.X -= .25f * Parse_PicSize.X;

					pic->tex = Tools::TextureWad->FindByName( Parse_PicName );

					float y = .5f * Tools::TheGame->Resolution.LineHeightMod * MyFont->LineSpacing - .5f * Parse_PicSize.Y + StartY;
					pic->rect = Rectangle( static_cast<int>( loc.X + Parse_PicShift.X ), static_cast<int>( y + loc.Y + Parse_PicShift.Y ), static_cast<int>( Parse_PicSize.X ), static_cast<int>( Parse_PicSize.Y ) );
					pic->size = Parse_PicSize;
					pic->AsPaint = AsPaint;

					Pics.push_back( pic );

					loc.X += Parse_PicSize.X / 2;
					LineHeight = __max( LineHeight, Parse_PicSize.Y *.9f );
				}

				// Parse color info
				if ( Parse_Type == ParseData_COLOR )
				{
					CurColor = Parse_Color;
					loc.X += .35f * MyFont->Font->Spacing;
				}
			}
			// Parse text info
			else
			{
				int i;
				if ( BeginBracketIndex < 0 )
					i = str.length();
				else
					i = BeginBracketIndex;

				std::shared_ptr<EzTextBit> bit = std::make_shared<EzTextBit>();
				bit->LineNumber = LineNumber;
				bit->clr = CurColor;
				bit->str = str.substr( 0, i );
				str = str.erase( 0, i );

				bit->size = MyFont->Font->MeasureString( bit->str );
				bit->size.Y *= Tools::TheGame->Resolution.LineHeightMod;

				bit->loc = loc + Vector2( 0, StartY );
				Bits.push_back( bit );

				loc.X += bit->size.X;
				LineHeight = __max( LineHeight, bit->size.Y *.9f );
			}

			FirstElement = false;
		}

		return LineHeight;
	}

	Microsoft::Xna::Framework::Vector2 EzText::GetWorldSize()
	{
		return Vector2( GetWorldWidth(), GetWorldHeight() );
	}

	float EzText::GetWorldHeight()
	{
		return getScale() * GetWorldFloat(Height);
	}

	float EzText::GetWorldWidth()
	{
		return getScale() * GetWorldFloat(TextWidth);
	}

	float EzText::GetWorldWidth( const std::wstring &str )
	{
		return getScale() * GetWorldFloat(MyFont->Font->MeasureString(str)->X);
	}

	const Microsoft::Xna::Framework::Vector2 &EzText::getMyCameraZoom() const
	{
		return _MyCameraZoom;
	}

	void EzText::setMyCameraZoom( const Vector2 &value )
	{
		_MyCameraZoom = value;
	}

	Microsoft::Xna::Framework::Vector2 EzText::GetWorldVector( Vector2 v )
	{
		return GetWorldVector( v, getMyCameraZoom() );
	}

	float EzText::GetWorldFloat( float interval )
	{
		return GetWorldFloat( interval, getMyCameraZoom() );
	}

	float EzText::GetWorldFloat( float interval, Vector2 zoom )
	{
		return GetWorldVector( Vector2( interval, 0 ), zoom ).X;
	}

	Microsoft::Xna::Framework::Vector2 EzText::GetWorldVector( Vector2 v, Vector2 zoom )
	{
		Vector2 vec2 = v;
		Vector2 vec1 = Vector2( 0, 0 );
		vec1 = Tools::ToWorldCoordinates( vec1, Tools::CurLevel->getMainCamera(), zoom );
		vec2 = Tools::ToWorldCoordinates( vec2, Tools::CurLevel->getMainCamera(), zoom );

		return ( vec2 - vec1 ) * Tools::TheGame->Resolution.LineHeightMod;
	}

	Microsoft::Xna::Framework::Vector2 EzText::GetGUIVector( Vector2 v )
	{
		Vector2 vec2 = v;
		Vector2 vec1 = Vector2( 0, 0 );
		vec1 = Tools::ToGUICoordinates( vec1, Tools::CurLevel->getMainCamera() );
		vec2 = Tools::ToGUICoordinates( vec2, Tools::CurLevel->getMainCamera() );

		return ( vec2 - vec1 ) * Tools::TheGame->Resolution.LineHeightMod;
	}

	void EzText::Init( const std::wstring &str )
	{
		Init( str, 10000, false, false, 1 );
	}

	void EzText::Init( const std::wstring &str, float Width, bool Centered, bool YCentered, float LineHeightMod )
	{
		this->LineHeightMod = LineHeightMod;
		this->Centered = Centered;
		this->YCentered = YCentered;

		TextBoxWidth = Width;

		MyString = str;

		MyColor = Color::White;
		MyFloatColor = Vector4( 1, 1, 1, 1 );

		Bits = std::vector<EzTextBit*>();
		Pics = std::vector<EzTextPic*>();

		loc = Vector2::Zero;
		LineHeight = 0;

		int i = 0;

		TextWidth = 0;
		float y = 0;
		int LineNumber = 0;
		CurColor = Color::White;
		while ( str.length() > 0 )
		{
			i = GetLineEnd( str );
//C# TO C++ CONVERTER NOTE: The variable Line was renamed since it is named the same as a user-defined type:
			std::wstring Line_Renamed = str.substr( 0, i );
			if ( Line_Renamed.length() > 0 && Line_Renamed[ Line_Renamed.length() - 1 ] == L' ' )
				Line_Renamed = Line_Renamed.erase( Line_Renamed.length() - 1, 1 );
			Vector2 Size = StringSize( Line_Renamed );
			LineSizes[ LineNumber ] = Size;

			float x = -Size.X / 2;
			TextWidth = __max( TextWidth, Size.X );
			y += LineHeightMod * AddLine( Line_Renamed, x, y, LineNumber );

			str = str.erase( 0, i );
			if ( str.length() > 0 && str[ 0 ] == L' ' )
				str = str.erase( 0, 1 );
			if ( str.length() > 0 && str[ 0 ] == L'\n' )
				str = str.erase( 0, 1 );

			LineNumber++;
		}

		Height = y;


		if ( YCentered )
		{
			for ( std::vector<EzTextBit*>::const_iterator bit = Bits.begin(); bit != Bits.end(); ++bit )
				( *bit )->loc.Y -= Height / 2;
			for ( std::vector<EzTextPic*>::const_iterator pic = Pics.begin(); pic != Pics.end(); ++pic )
				( *pic )->rect.Y -= static_cast<int>( Height / 2 );
		}

		if ( !Centered )
		{
			for ( std::vector<EzTextBit*>::const_iterator bit = Bits.begin(); bit != Bits.end(); ++bit )
				( *bit )->loc.X += LineSizes[ ( *bit )->LineNumber ].X / 2 * Tools::TheGame->Resolution.LineHeightMod;
			for ( std::vector<EzTextPic*>::const_iterator pic = Pics.begin(); pic != Pics.end(); ++pic ) // * Tools.TheGame.Resolution.LineHeightMod);
				( *pic )->rect.X += static_cast<int>( LineSizes[ ( *pic )->LineNumber ].X / 2 );
		}
		else
		{
			for ( std::vector<EzTextPic*>::const_iterator pic = Pics.begin(); pic != Pics.end(); ++pic )
				( *pic )->rect.X = static_cast<int>( ( getScale() * (*pic)->rect.X - getPos().X + (*pic)->rect.Width / 2 ) * Tools::TheGame->Resolution.LineHeightMod + getPos().X - (*pic)->rect.Width / 2 );
		}
	}

	void EzText::Center()
	{
		setPos( Vector2( getPos().X - .5f * GetWorldWidth(), getPos().Y ) );
	}

	void EzText::Draw( const std::shared_ptr<Camera> &cam )
	{
		Draw( cam, true );
	}

	void EzText::Draw( const std::shared_ptr<Camera> &cam, bool EndBatch )
	{
		Alpha += AlphaVel;

		setMyCameraZoom( cam->getZoom() );

		if ( !Show )
			return;

		// Scale if the parent this text is attached to is scaled
		float HoldScale = getScale();
		float HoldAlpha = Alpha;
		if ( ParentScaling != Vector2::One )
		{
			setScale( getScale() * ParentScaling.X );
		}
		if ( ParentAlpha != 1 )
			Alpha *= ParentAlpha;

		if ( RightJustify )
			JustificationShift = Vector2( -GetWorldWidth(), 0 );

		if ( FancyPos != 0 )
			_Pos = FancyPos->Update( ParentScaling );

		PicColor = Color::Black;
		if ( Shadow )
		{
			// Note: never end the SpriteBatch for drawing a shadow,
			// since we will always be drawing the non-shadow part afterward

			float _HoldScale = getScale();
			setScale( getScale() * ShadowScale );

			_Pos -= ShadowOffset;
			if ( MyFont->OutlineFont != 0 || OutlineColor.W == 0 )
				_Draw( cam, false, PicShadow, MyFont->OutlineFont, ShadowColor.ToVector4() );
			_Draw( cam, false, false, MyFont->Font, ShadowColor.ToVector4() );
			_Pos += ShadowOffset;

			setScale( _HoldScale );
		}
		PicColor = Color::White;

		if ( !ColorizePics )
		{
			PicColor = Color::White;
		}

		if ( MyFont->OutlineFont != 0 && OutlineColor.W != 0 )
			_Draw( cam, false, true, MyFont->OutlineFont, OutlineColor );
		_Draw( cam, EndBatch, true, MyFont->Font, MyFloatColor );

		// Draw box outline
		if ( Tools::DrawBoxes )
		{
			CalcBounds();
			Tools::QDrawer->DrawBox( BL, TR, Color::Black, 5 );
		}

		// Revert the scaling if this text is attached to something
		if ( ParentScaling != Vector2::One )
		{
			setScale( HoldScale );
		}
		if ( ParentAlpha != 1 )
			Alpha = HoldAlpha;
	}

bool EzText::ZoomWithCamera_Override = false;

	void EzText::_Draw( const std::shared_ptr<Camera> &cam, bool EndBatch, bool DrawPics, const std::shared_ptr<SpriteFont> &font, Vector4 color )
	{
		if ( MyFloatColor.W <= 0 )
			return;

		MyFont->FixFont();

		MyColor.R = Tools::FloatToByte( color.X );
		MyColor.G = Tools::FloatToByte( color.Y );
		MyColor.B = Tools::FloatToByte( color.Z );
		MyColor.A = Tools::FloatToByte( color.W * Alpha );

		float ZoomMod = 1;
		if ( ZoomWithCam || ZoomWithCamera_Override )
			ZoomMod = getMyCameraZoom().X / .001f;

		Vector2 Position = _Pos + JustificationShift;
		if ( FixedToCamera )
			Position += cam->Data.Position;
		Vector2 Loc = Tools::ToScreenCoordinates( Position, cam, Tools::EffectWad->ModZoom );

		Tools::StartSpriteBatch();
		for ( std::vector<EzTextBit*>::const_iterator bit = Bits.begin(); bit != Bits.end(); ++bit )
		{
			Color textcolor = ColorHelper::PremultiplyAlpha( Color( MyColor.ToVector4() * (*bit)->clr.ToVector4() ) );

			if ( ( *bit )->builder_str != 0 )
				Tools::Render->MySpriteBatch->DrawString( font, ( *bit )->builder_str, getScale() * (*bit)->loc*ZoomMod + Loc, textcolor, 0, (*bit)->size * Tools::TheGame->Resolution.TextOrigin, Vector2(Tools::TheGame->Resolution.LineHeightMod, Tools::TheGame->Resolution.LineHeightMod) * getScale()*ZoomMod, SpriteEffects::None, 1 );
			else
				Tools::Render->MySpriteBatch->DrawString( font, ( *bit )->str, getScale() * (*bit)->loc * ZoomMod + Loc, textcolor, Angle, (*bit)->size * Tools::TheGame->Resolution.TextOrigin, Vector2(Tools::TheGame->Resolution.LineHeightMod, Tools::TheGame->Resolution.LineHeightMod) * getScale() * ZoomMod, SpriteEffects::None, 1 );
		}
		if ( DrawPics )
			for ( std::vector<EzTextPic*>::const_iterator pic = Pics.begin(); pic != Pics.end(); ++pic )
			{
				Color piccolor = PicColor;
				piccolor.A = Tools::FloatToByte( Alpha * piccolor.A / 255 );

				piccolor = ColorHelper::PremultiplyAlpha( piccolor );

				Vector2 pos = Loc + getScale() * ZoomMod * Vector2((*pic)->rect.X, (*pic)->rect.Y);
				Vector2 scale = getScale() * ZoomMod * Vector2((*pic)->rect.Width / static_cast<float>((*pic)->tex->Width), (*pic)->rect.Height / static_cast<float>((*pic)->tex->Height));

				if ( ( *pic )->AsPaint )
				{
					Tools::Render->EndSpriteBatch();
					Tools::StartSpriteBatch( true );
				}
				Tools::Render->MySpriteBatch->Draw( ( *pic )->tex->getTex(), pos, 0, piccolor, 0, Vector2::Zero, scale, SpriteEffects::None, 0 );
				if ( ( *pic )->AsPaint )
				{
					Tools::Render->EndSpriteBatch();
					Tools::StartSpriteBatch();
				}
			}

		if ( EndBatch )
			Tools::Render->EndSpriteBatch();
	}

	void EzText::CalcBounds()
	{
		TR = Vector2( -100000000, -100000000 );
		BL = Vector2( 100000000, 100000000 );

		Vector2 Loc = _Pos;

		for ( std::vector<EzTextBit*>::const_iterator bit = Bits.begin(); bit != Bits.end(); ++bit )
		{
			Vector2 loc, size;

			loc = GetWorldVector( ( *bit )->loc );
			size = GetWorldVector( ( *bit )->size );

			Vector2 bit_TR = getScale() * loc + Loc;
			bit_TR.X += 1 * getScale() * size.X;
			bit_TR.Y += .25f * getScale() * size.Y;
			Vector2 bit_BL = getScale() * loc + Loc;
			bit_BL.Y += .75f * getScale() * size.Y;

			TR = Vector2::Max( TR, bit_TR );
			BL = Vector2::Min( BL, bit_BL );
		}

		for ( std::vector<EzTextPic*>::const_iterator pic = Pics.begin(); pic != Pics.end(); ++pic )
		{
			Vector2 loc = GetWorldVector( Vector2( ( *pic )->rect.X, ( *pic )->rect.Y ) );
			Vector2 size = Vector2( ( *pic )->rect.Width, ( *pic )->rect.Height );
			size = GetWorldVector( size );

			Vector2 bit_TR = getScale() * loc + Loc;
			bit_TR.X += 1 * getScale() * size.X;
			bit_TR.Y += .25f * getScale() * size.Y;
			Vector2 bit_BL = getScale() * loc + Loc;
			bit_BL.Y += .75f * getScale() * size.Y;

			TR = Vector2::Max( TR, bit_TR );
			BL = Vector2::Min( BL, bit_BL );
		}
	}

	void EzText::InitializeInstanceFields()
	{
		Name = _T( "" );
		Layer = 0;
		ParentScaling = Vector2::One;
		ParentAlpha = 1;
		OutlineColor = Color::Black.ToVector4();
		Shadow = false;
		PicShadow = true;
		ShadowOffset = Vector2::Zero;
		ShadowColor = Color::Black;
		ShadowScale = 1;
		Alpha = 1;
		AlphaVel = 0;
		_Scale = 1;
		RightJustify = false;
		CurColor = Color::White;
		_MyCameraZoom = Vector2( .001f,.001f );
		LineHeightMod = 1;
		LineSizes = std::vector<Vector2>( 20 );
		Show = true;
		Angle = 0;
		ZoomWithCam = false;
	}
}
