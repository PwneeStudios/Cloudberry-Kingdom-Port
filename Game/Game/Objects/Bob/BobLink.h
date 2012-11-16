#ifndef BOBLINK
#define BOBLINK

#include <global_header.h>

namespace CloudberryKingdom
{
	class Bob;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace Microsoft::Xna::Framework::Input;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobLink
	{
	public:
		int _j, _k;
		std::shared_ptr<Bob> j, k;
		float L, a_in, a_out, MaxForce;

		void Release();

		BobLink();

		const bool &getInactive() const;

		void Draw();

		void Draw( Vector2 p1, Vector2 p2 );

		void PhsxStep( const std::shared_ptr<Bob> &bob );

		void Connect( const std::shared_ptr<Bob> &bob1, const std::shared_ptr<Bob> &bob2 );
	};
}


#endif	//#ifndef BOBLINK
