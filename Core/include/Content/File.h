/**
 * @file
 *
 * Cross platform file.
 */
#ifndef _FILE_H_
#define _FILE_H_

#include <string>

/**
 * File IO interface.
 */
class File
{

public:

	/// Read a file into a string.
	/**
	 * @param path Path to file.
	 * @param[out] str Output string.
	 * @return True on success and false on failure.
	 */
	static bool ReadAsString( const std::string &path, std::string &str );

};

#endif
