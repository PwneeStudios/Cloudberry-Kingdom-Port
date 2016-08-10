#ifndef BUYABLE
#define BUYABLE

namespace CloudberryKingdom
{

	struct Buyable : public Object
	{

		virtual ~Buyable()
		{
#ifdef BOOST_BIN
			OnDestructor( "Buyable" );
#endif
		}


		virtual int GetGuid() = 0;
		virtual int GetPrice() = 0;

	};

}

#endif