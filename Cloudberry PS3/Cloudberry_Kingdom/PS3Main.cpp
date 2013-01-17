#include <iostream>

#include <Utility/Log.h>

namespace boost
{
	void throw_exception(std::exception const & e)
	{
		LOG.Write( e.what() );
	}
}

int main(int argc, char *argv)
{
	std::cout << "Hello, world!" << std::endl;

	return 0;
}
