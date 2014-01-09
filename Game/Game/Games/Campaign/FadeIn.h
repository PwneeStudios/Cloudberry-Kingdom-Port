#ifndef FADEIN
#define FADEIN

#include <small_header.h>

#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Objects/Door/Door.h"


namespace CloudberryKingdom
{
	struct FadeInObject : public GameObject
	{
		virtual ~FadeInObject()
		{
#ifdef BOOST_BIN
			OnDestructor( "FadeInObject" );
#endif
		}


		struct ReadyProxy : public Lambda
		{
		
			boost::shared_ptr<FadeInObject> fio;

		
			ReadyProxy( const boost::shared_ptr<FadeInObject> &fio );

			void Apply();
		};

	
		struct EndProxy : public Lambda
		{
		
			boost::shared_ptr<FadeInObject> fio;

		
			EndProxy( const boost::shared_ptr<FadeInObject> &fio );

			void Apply();
		};

	
		FadeInObject();

		virtual void OnAdd();

	
		void Ready();

		void End();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef FADEIN
