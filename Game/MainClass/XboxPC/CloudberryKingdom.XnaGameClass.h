#ifndef CLOUDBERRYKINGDOM_XNAGAMECLASS
#define CLOUDBERRYKINGDOM_XNAGAMECLASS

#include <global_header.h>

#include "Hacks/XNA/Game.h"

namespace CloudberryKingdom
{
	struct XnaGameClass : public Game, public boost::enable_shared_from_this<XnaGameClass>
	{
	
		virtual ~XnaGameClass()
		{
#ifdef BOOST_BIN
			OnDestructor( "XnaGameClass" );
#endif
		}


		boost::shared_ptr<CloudberryKingdomGame> MyGame;
	
		XnaGameClass();

		virtual bool getIsActive();

		virtual void setIsMouseVisible( bool visible );

		virtual void Initialize();

		virtual void LoadContent();

		virtual void UnloadContent();

		virtual void Update( const boost::shared_ptr<GameTime> &gameTime );

		virtual void Draw( const boost::shared_ptr<GameTime> &gameTime );

		virtual void Exit();

#if defined(WINDOWS)
	
		void SetBorder( bool Show );
#endif
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_XNAGAMECLASS
