#include <small_header.h>
#include "Game/Objects/In Game Objects/BaseClasses/_Obstacle.h"

#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/AutoGen.h"
#include "Game/Tools/Tools.h"

#include "Game/Level/Level.h"
#include "Game/Tools/Camera.h"

namespace CloudberryKingdom
{

	const Vector2 &_Obstacle::getPhsxCutoff() const
	{
		return getCore()->BoxesOnly ? PhsxCutoff_BoxesOnly : PhsxCutoff_Playing;
	}

	void _Obstacle::MakeNew()
	{
		ObjectBase::MakeNew();

		getCore()->Init();
		getCore()->GenData.OverlapWidth = 60;

		getCore()->SkippedPhsx = true;
		getCore()->ContinuousEnabled = true;
	}

	void _Obstacle::Die()
	{
	}

	void _Obstacle::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;

		getCore()->Data = getCore()->StartData;
	}

	void _Obstacle::PhsxStep()
	{
		ObjectBase::PhsxStep();

		getCore()->PosFromParentOffset();

		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getPos(), getPhsxCutoff()) )
		{
			getCore()->SkippedPhsx = true;
			getCore()->WakeUpRequirements = true;
			return;
		}
		getCore()->SkippedPhsx = false;

		ActivePhsxStep();
	}

	void _Obstacle::Draw()
	{
		if ( getCore()->SkippedPhsx )
			return;

		if ( Tools::DrawGraphics && getCore()->MyLevel->PlayMode == 0 )
		{
			DrawGraphics();
		}

		if ( Tools::DrawBoxes )
		{
			DrawBoxes();
		}
	}

	void _Obstacle::Construct( bool BoxesOnly ) { }
	void _Obstacle::DrawGraphics() { }
	void _Obstacle::DrawBoxes() { }
	void _Obstacle::ActivePhsxStep() { }

	void _Obstacle::InitializeInstanceFields()
	{
		PhsxCutoff_Playing = Vector2( 200, 200 );
		PhsxCutoff_BoxesOnly = Vector2( -150, 200 );
	}

}
