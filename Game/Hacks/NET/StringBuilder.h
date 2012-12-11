#ifndef _STRINGBUILDER_H_
#define _STRINGBUILDER_H_

struct StringBuilder
{



	StringBuilder( const std::wstring &str )
	{
	}

	StringBuilder( int Capacity, int MaxCapacity )
	{
		// FIXME
	}

	operator std::wstring() const
	{
		// FIXME
		return _T( "" );
	}

	void Append( const wchar_t &c )
	{
		// FIXME
	}

	void setLength( int length )
	{
		// FIXME: this should affect the string. length == 0 should make the string equal to "".
	}

	int getLength()
	{
		return 0;
	}

	std::wstring ToString()
	{
		return _T( "" );
		// FIXME: implement
	}

	void Remove( int offset, int length )
	{
	}

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
