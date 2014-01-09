#include <small_header.h>
#include "Game/Games/Campaign/FadeIn.h"

#include "Game/Objects/Game Objects/GameObject.h"
#include "Game/Games/Meta Games/StringWorlds/LevelConnector.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Objects/Door/Door.h"

#include "Game/Games/GameType.h"
#include "Game/Level/Level.h"
#include "Game/Level/Make/LevelSeedData.h"

namespace CloudberryKingdom
{

	FadeInObject::ReadyProxy::ReadyProxy( const boost::shared_ptr<FadeInObject> &fio )
	{
		this->fio = fio;
	}

	void FadeInObject::ReadyProxy::Apply()
	{
		fio->Ready();
	}

	FadeInObject::EndProxy::EndProxy( const boost::shared_ptr<FadeInObject> &fio )
	{
		this->fio = fio;
	}

	void FadeInObject::EndProxy::Apply()
	{
		fio->End();
	}

	FadeInObject::FadeInObject()
	{
	}

	void FadeInObject::OnAdd()
	{
		GameObject::OnAdd();

		setPauseGame( true );

		MyGame->Black();

		// Find the initial door
		boost::shared_ptr<Door> door = boost::dynamic_pointer_cast<Door>( MyGame->MyLevel->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 != door )
		{
			for ( BobVec::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
				( *bob )->getCore()->Show = false;
		}

		MyGame->WaitThenDo( 1, boost::make_shared<ReadyProxy>( boost::static_pointer_cast<FadeInObject>( shared_from_this() ) ) );
	}

	void FadeInObject::Ready()
	{
		MyGame->WaitThenDo( 20, boost::make_shared<EndProxy>( boost::static_pointer_cast<FadeInObject>( shared_from_this() ) ) );
	}

	void FadeInObject::End()
	{
		//MyGame->FadeIn( .032f );
		MyGame->FadeIn( getMyLevel()->MyLevelSeed == 0 ? .032f : getMyLevel()->MyLevelSeed->FadeInSpeed );

		setPauseGame( false );

		Release();
	}

	void FadeInObject::MyPhsxStep()
	{
	}
}
