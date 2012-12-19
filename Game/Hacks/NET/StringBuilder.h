#ifndef _STRINGBUILDER_H_
#define _STRINGBUILDER_H_

#include <vector>
#include <string>

struct StringBuilder
{

	std::vector<wchar_t> buffer;

	StringBuilder( const std::wstring &str );

	StringBuilder( int Capacity, int MaxCapacity );

	operator std::wstring() const;

	void Append( const wchar_t &c );

	void setLength( int length );

	int getLength();

	std::wstring ToString() const;

	void Remove( int offset, int length );

	/// <summary>
	/// The maximum number of digits an integer can be
	/// </summary>
	static const int max_digits = 15;

	/// <summary>
	/// A working array to store digits of an integer
	/// </summary>
	std::vector<long long> digits;

	/// <summary>
	/// Clear the working array to allow for a new number to be constructed
	/// </summary>
	void ClearDigits();
	
	/// <summary>
	/// Returns the index of the last digit of the number being constructed
	/// </summary>
	/// <returns></returns>
	int LastDigit();

	/// <summary>
	/// The characters associated with each possible digit
	/// </summary>
	static std::vector<wchar_t> digit_char;

	/// <summary>
	/// Takes the digits from a number (already stored in a work array)
	/// and adds them to a StringBuilder
	/// </summary>
	void DigitsToString( int NumDigits );

	/// <summary>
	/// Add a string representation of a number to a StringBuilder
	/// </summary>
	void Add( long long num );

	/// <summary>
	/// Add a string representation of a number to a StringBuilder
	/// </summary>
	/// <param name="MinDigits">The minimum number of digits used in the string.
	/// The string is padded with zeros to the left if needed.</param>
	void Add( long long num, int MinDigits );

};

#endif
