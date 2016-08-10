#ifndef HERO_DOLL_H
#define HERO_DOLL_H

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Player/PlayerManager.h"
//#include "Game/Player/Hero Physics/Base.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Player/Cape.h"
//#include "Game/Player/PlayerData.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/BobPhsxCharSelect.h"
//#include "Game/Tools/Camera.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct HeroDoll : public CkBaseMenu
	{
	
		virtual ~HeroDoll()
		{
#ifdef BOOST_BIN
			OnDestructor( "HeroDoll" );
#endif
		}


		HeroDoll( int Control );
		boost::shared_ptr<HeroDoll> HeroDoll_Construct( int Control );

	
		virtual void ReleaseBody();

	
		boost::shared_ptr<Bob> MyDoll;
		virtual void Init();

		virtual void OnAdd();

	
		boost::shared_ptr<PlayerData> player;
	
		void MakeHeroDoll( const boost::shared_ptr<BobPhsx> &hero );

	
		void SetPos();

	
		void SetPhsx();

		void UpdateColorScheme();

	
		virtual void MyPhsxStep();

	
		void DrawBob();

	
		virtual void MyDraw();
	};
}


#endif	//#ifndef DOLL
