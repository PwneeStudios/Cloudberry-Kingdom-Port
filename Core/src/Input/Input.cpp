#include <Input/Input.h>

template<> Input *Singleton< Input >::singleton_ = 0;

Input &Input::GetSingleton()
{
	assert( singleton_ );
	return *singleton_;
}
