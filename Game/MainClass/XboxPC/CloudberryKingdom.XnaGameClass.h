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
