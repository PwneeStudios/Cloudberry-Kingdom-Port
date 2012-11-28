#include <global_header.h>

namespace CloudberryKingdom
{

	const bool &LockableBool::getval() const
	{
		return _val;
	}

	void LockableBool::setval( const bool &value )
	{
		_val = value;
	}

	void LockableBool::InitializeInstanceFields()
	{
		_val = false;
	}

}
