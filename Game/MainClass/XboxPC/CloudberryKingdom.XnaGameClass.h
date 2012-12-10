#ifndef CLOUDBERRYKINGDOM_XNAGAMECLASS
#define CLOUDBERRYKINGDOM_XNAGAMECLASS

#include <global_header.h>

#include "Hacks/XNA/Game.h"

namespace CloudberryKingdom
{
	class XnaGameClass : public Game, public std::enable_shared_from_this<XnaGameClass>
	{
	private:
		std::shared_ptr<CloudberryKingdomGame> MyGame;

	public:
		XnaGameClass();

		virtual bool getIsActive();
		virtual void setIsMouseVisible( bool visible );

		virtual void Initialize();

		virtual void LoadContent();

		virtual void UnloadContent();

		virtual void Update( const std::shared_ptr<GameTime> &gameTime );

		virtual void Draw( const std::shared_ptr<GameTime> &gameTime );

		virtual void Exit();

#if defined(WINDOWS)
	public:
		void SetBorder( bool Show );
#endif
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_XNAGAMECLASS
