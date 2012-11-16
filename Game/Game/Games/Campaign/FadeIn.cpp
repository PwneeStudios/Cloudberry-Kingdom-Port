#include <global_header.h>

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{

	FadeInObject::ReadyProxy::ReadyProxy( const std::shared_ptr<FadeInObject> &fio )
	{
		this->fio = fio;
	}

	void FadeInObject::ReadyProxy::Apply()
	{
		fio->Ready();
	}

	FadeInObject::EndProxy::EndProxy( const std::shared_ptr<FadeInObject> &fio )
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
		std::shared_ptr<Door> door = dynamic_cast<Door*>( MyGame->MyLevel->FindIObject( LevelConnector::StartOfLevelCode ) );
		if ( 0 != door )
		{
			for ( std::vector<Bob*>::const_iterator bob = MyGame->MyLevel->Bobs.begin(); bob != MyGame->MyLevel->Bobs.end(); ++bob )
				( *bob )->getCore()->Show = false;
		}

		MyGame->WaitThenDo( 1, std::make_shared<ReadyProxy>( this ) );
	}

	void FadeInObject::Ready()
	{
		MyGame->WaitThenDo( 20, std::make_shared<EndProxy>( this ) );
	}

	void FadeInObject::End()
	{
		MyGame->FadeIn( .032f );

		setPauseGame( false );

		Release();
	}

	void FadeInObject::MyPhsxStep()
	{
	}
}
