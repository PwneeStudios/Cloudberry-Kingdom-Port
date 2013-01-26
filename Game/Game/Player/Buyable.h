#ifndef BUYABLE
#define BUYABLE

namespace CloudberryKingdom
{

	struct Buyable : public Object
	{

		virtual ~Buyable() { }

		virtual int GetGuid() = 0;
		virtual int GetPrice() = 0;

	};

}

#endif