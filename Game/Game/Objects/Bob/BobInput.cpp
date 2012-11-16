#include "BobInput.h"

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

	void BobInput::Clean()
	{
		A_Button = B_Button = false;
		xVec = Vector2::Zero;
	}

	void BobInput::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		writer->Write( A_Button );
		writer->Write( B_Button );
		writer->Write( xVec );
	}

	void BobInput::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		A_Button = reader->ReadBoolean();
		B_Button = reader->ReadBoolean();
		xVec = reader->ReadVector2();
	}
}
