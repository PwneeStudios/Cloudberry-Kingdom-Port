#ifndef _TUPLE_H_
#define _TUPLE_H_

template<class A, class B>
class Tuple
{

public:
	A Item1;
	B Item2;

	Tuple( A item1, B item2 )
	{
		Item1 = item1;
		Item2 = item2;
	}

};

#endif
