#ifndef CLOUDBERRYKINGDOM
#define CLOUDBERRYKINGDOM

#include <global_header.h>

namespace CloudberryKingdom
{
	class CloudberryKingdomGame;
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class GameTime;
		}
	}
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Threading;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Windows::Forms;

using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Audio;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::GamerServices;
using namespace Microsoft::Xna::Framework::Graphics;
using namespace Microsoft::Xna::Framework::Input;
using namespace Microsoft::Xna::Framework::Media;










namespace Forms = System::Windows::Forms;

namespace CloudberryKingdom
{
	class XnaGameClass : public Game
	{
	private:
		std::shared_ptr<CloudberryKingdomGame> MyGame;

	public:
		XnaGameClass();

	protected:
		virtual void Initialize();

		virtual void LoadContent();

		virtual void UnloadContent();

		virtual void Update( const std::shared_ptr<GameTime> &gameTime );

		virtual void Draw( const std::shared_ptr<GameTime> &gameTime );

#if defined(WINDOWS)
	public:
		void SetBorder( bool Show );
#endif
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM
