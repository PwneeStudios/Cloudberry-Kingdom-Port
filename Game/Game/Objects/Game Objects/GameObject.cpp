#include <small_header.h>
#include "Game/Objects/Game Objects/GameObject.h"

#include "Core/Tools/Set.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Games/GameType.h"
#include "Game/Objects/In Game Objects/Grab/MakeData.h"
#include "Game/Level/Level.h"


#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	GameObject::OnCameraChangeProxy::OnCameraChangeProxy( const boost::shared_ptr<GameObject> &go )
	{
		this->go = go;
	}

	void GameObject::OnCameraChangeProxy::Apply()
	{
		go->OnCameraChange();
	}

	GameObject::AddGameObjectToCoreHelper::AddGameObjectToCoreHelper( const boost::shared_ptr<GameObject> &obj )
	{
		this->obj = obj;
	}

	void GameObject::AddGameObjectToCoreHelper::Apply()
	{
		obj->getCore()->MyLevel->MyGame->AddGameObject(obj);
	}

	bool GameObject::AttemptToReAdd()
	{
		if ( MyGame == 0 )
			if ( getCore()->MyLevel->MyGame != 0 )
				getCore()->MyLevel->MyGame->WaitThenDo(0, boost::make_shared<AddGameObjectToCoreHelper>( boost::static_pointer_cast<GameObject>( shared_from_this() ) ) );

		return MyGame == 0;
	}

	void GameObject::setSoftPause( const bool &value )
	{
		_SoftPause = value;

		AffectGameSoftPause();
	}

	const bool &GameObject::getSoftPause() const
	{
		return _SoftPause;
	}

	void GameObject::setPauseGame( const bool &value )
	{
		_PauseGame = value;

		AffectGamePause();
	}

	const bool &GameObject::getPauseGame() const
	{
		return _PauseGame;
	}

	void GameObject::setPauseLevel( const bool &value )
	{
		_PauseLevel = value;

		AffectLevelPause();
	}

	const bool &GameObject::getPauseLevel() const
	{
		return _PauseLevel;
	}

	void GameObject::AffectGameSoftPause()
	{
		if ( MyGame == 0 )
			return;

		if ( getSoftPause() )
			MyGame->SoftPause = true;
		else
			MyGame->UpdateSoftPause();
	}

	void GameObject::AffectGamePause()
	{
		if ( MyGame == 0 )
			return;

		if ( getPauseGame() )
			MyGame->PauseGame = true;
		else
			MyGame->UpdateGamePause();
	}

	void GameObject::AffectLevelPause()
	{
		if ( MyGame == 0 )
			return;

		if ( getPauseLevel() )
			MyGame->PauseLevel = true;
		else
			MyGame->UpdateLevelPause();
	}

	void GameObject::ForceRelease()
	{
		ReleaseBody();
	}

	void GameObject::Release()
	{
		if ( !PreventRelease && !getCore()->Released )
			ReleaseBody();
	}

	void GameObject::ReleaseBody()
	{
		ObjectBase::Release();

		if ( OnRelease != 0 ) OnRelease->Apply(); OnRelease.reset();

		MyGame.reset();

		getCore()->Active = false;
		getCore()->MarkedForDeletion = true;
	}

	void GameObject::MakeNew()
	{
		getCore()->Init();
		getCore()->DrawLayer = 10;

		getCore()->IsGameObject = true;

		getCore()->RemoveOnReset = false;
		getCore()->ResetOnlyOnReset = true;
	}

	GameObject::GameObject() :
		PreventRelease( false ),
		PauseOnPause( false ),
		_SoftPause( false ),
		_PauseGame( false ),
		_PauseLevel( false ),
		HideOnReplay( false ),
		PauseOnReplay( false ),
		AutoDraw( false ),
		SkipPhsx( 0 )
	{
		InitializeInstanceFields();
		MakeNew();
	}

	void GameObject::Init()
	{
	}

	void GameObject::ManualDraw()
	{
		MyDraw();
	}

	void GameObject::Draw()
	{
		if ( !AutoDraw )
			return;

		if ( HideOnReplay && ( getCore()->MyLevel->Replay || getCore()->MyLevel->Watching ) )
			return;

		if ( getCore()->Released )
			return;

		MyDraw();
	}

	void GameObject::MyDraw()
	{
	}

	void GameObject::PhsxStep()
	{
		if ( SkipPhsx > 0 )
		{
			SkipPhsx--;
			return;
		}

		boost::shared_ptr<Level> level = getCore()->MyLevel;

		if ( PauseOnReplay && ( level->Replay || level->Watching ) )
			return;

		MyPhsxStep();
	}

	void GameObject::MyPhsxStep()
	{
	}

	void GameObject::OnAdd()
	{
		AffectGamePause();

		if ( getCore()->MyLevel != 0 )
		{
			boost::shared_ptr<Multicaster> mc = getCore()->MyLevel->OnCameraChange;
			mc->Add( boost::make_shared<OnCameraChangeProxy>( boost::static_pointer_cast<GameObject>( shared_from_this() ) ) );

			// Go over list of lambdas in multicaster and remove all lambdas associated with removed or null game objects.
			std::vector<boost::shared_ptr<Lambda> > NewList;
			for ( std::vector<boost::shared_ptr<Lambda> >::const_iterator item = mc->MyList.begin(); item != mc->MyList.end(); ++item )
			{
				boost::shared_ptr<OnCameraChangeProxy> occp = boost::dynamic_pointer_cast<OnCameraChangeProxy>( *item );
				if ( 0 != occp )
				{
					if ( occp->go != 0 && occp->go->CoreData != 0 && !occp->go->CoreData->Released )
						NewList.push_back( occp );
				}
			}
			mc->MyList = NewList;
		}
	}

	void GameObject::OnCameraChange()
	{
	}

	void GameObject::InitializeInstanceFields()
	{
		Tags = boost::make_shared<Set<Tag> >();
		PreventRelease = false;
		PauseOnPause = false;
		OnRelease = boost::make_shared<Multicaster>();
		HideOnReplay = false;
		PauseOnReplay = false;
		AutoDraw = true;
		SkipPhsx = 0;
	}
}
