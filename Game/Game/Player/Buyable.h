#ifndef BUYABLE
#define BUYABLE

namespace CloudberryKingdom
{

	class Buyable : public Object
	{

	public:
		virtual ~Buyable() { }

		virtual int GetGuid() = 0;
		virtual int GetPrice() = 0;

	};

}

#endif