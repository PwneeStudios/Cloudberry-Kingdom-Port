#include "global_header.h"

#include "Hacks/XNA/MediaPlayer.h"

/// <summary>
/// String Builder
/// </summary>
void StringBuilder::ClearDigits()
{
	for ( int i = 0; i < max_digits; i++ )
		digits[ i ] = 0;
}

int StringBuilder::LastDigit()
{
	for ( int i = max_digits - 1; i >= 0; i-- )
		if ( StringBuilder::digits[ i ] > 0 )
			return i;
	return 0;
}

const wchar_t tempVector[] = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' };
std::vector<wchar_t> StringBuilder::digit_char = std::vector<wchar_t>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );

void StringBuilder::DigitsToString( int NumDigits )
{
	for ( int i = NumDigits - 1; i >= 0; i-- )
		Append( digit_char[ static_cast<unsigned int>( digits[ i ] ) ] );
}

void StringBuilder::Add( long long num )
{
	Add( num, 1 );
}

void StringBuilder::Add( long long num, int MinDigits )
{
	if ( num < 0 )
	{
		Append( L'-' );
		num *= -1;
	}

	ClearDigits();

	for ( int i = max_digits - 1; i >= 0; i-- )
	{
		double Pow = pow( 10.0, i );
		long long _pow = static_cast<long long>( floor( Pow + 0.5 ) );
		long long digit = num / _pow;
		digits[ i ] = digit;
		num -= _pow * digit;
	}

	int DigitsToAppend = __max( LastDigit() + 1, MinDigits );
	DigitsToString( DigitsToAppend );
}

// FIXME: Move to MediaPlayer.cpp. If we ever aren't lazy fucks.
bool MediaPlayer::IsRepeating = false;
float MediaPlayer::Volume = 1;
