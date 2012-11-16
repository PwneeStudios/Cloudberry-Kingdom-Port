#ifndef LEVELSEEDDATA
#define LEVELSEEDDATA

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;



namespace CloudberryKingdom
{
	class LockableBool
	{
	private:
		bool _val;
	public:
		const bool &getval() const;
		void setval( const bool &value );

	private:
		void InitializeInstanceFields();

public:
		LockableBool()
		{
			InitializeInstanceFields();
		}
	};

}


#endif	//#ifndef LEVELSEEDDATA
