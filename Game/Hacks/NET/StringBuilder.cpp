#include "StringBuilder.h"

#include <Hacks\List.h>

StringBuilder::StringBuilder( const std::wstring &str )
{
	buffer.reserve( 100 );
	digits = std::vector<long long>( max_digits );
}

StringBuilder::StringBuilder( int Capacity, int MaxCapacity )
{
	buffer.reserve( MaxCapacity );
	digits = std::vector<long long>( max_digits );
}

StringBuilder::operator std::wstring() const
{
	return ToString();
}

void StringBuilder::Append( const wchar_t &c )
{
	buffer.push_back( c );
}

void StringBuilder::setLength( int length )
{
	if ( length == 0 )
		buffer.clear();
}

int StringBuilder::getLength()
{
	return buffer.size();
}

std::wstring StringBuilder::ToString() const
{
	return std::wstring( buffer.begin(), buffer.end() );
}

void StringBuilder::Remove( int offset, int length )
{
	buffer.erase( buffer.begin() + offset, buffer.begin() + offset + length );
}

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

wchar_t tempVector[] = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9' };
std::vector<wchar_t> StringBuilder::digit_char = VecFromArray( tempVector );

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
