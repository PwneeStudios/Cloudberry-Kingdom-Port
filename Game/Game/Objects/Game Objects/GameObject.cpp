#include "GameObject.h"
#include "Core/Tools/Set.h"
#include "Core/Lambdas/Multicaster.h"
#include "Game/Games/GameType.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	GameObject::OnCameraChangeProxy::OnCameraChangeProxy( const std::shared_ptr<GameObject> &go )
	{
		this->go = go;
	}

	void GameObject::OnCameraChangeProxy::Apply()
	{
		go->OnCameraChange();
	}

	GameObject::AddGameObjectToCoreHelper::AddGameObjectToCoreHelper( const std::shared_ptr<GameObject> &obj )
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
				getCore()->MyLevel->MyGame->WaitThenDo(0, std::make_shared<AddGameObjectToCoreHelper>(this));

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

		if ( OnRelease != 0 )
			OnRelease->Apply();
		OnRelease.reset();

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

	GameObject::GameObject()
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

		std::shared_ptr<Level> level = getCore()->MyLevel;

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
			getCore()->MyLevel->OnCameraChange->Add(std::make_shared<OnCameraChangeProxy>(this));
	}

	void GameObject::OnCameraChange()
	{
	}

	void GameObject::InitializeInstanceFields()
	{
		Tags = std::make_shared<Set<Tag> >();
		PreventRelease = false;
		PauseOnPause = false;
		OnRelease = std::make_shared<Multicaster>();
		HideOnReplay = false;
		PauseOnReplay = false;
		AutoDraw = true;
		SkipPhsx = 0;
	}
}
