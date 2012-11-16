#include "Arrow.h"
#include "Core/Graphics/Draw/Simple/SimpleObject.h"
#include "Game/Tools/Prototypes.h"
#include "Game/Tools/Tools.h"
#include "Core/Tools/CoreMath.h"

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	Arrow::Arrow()
	{
		InitializeInstanceFields();
		this->PreventRelease = false;
		MyObject = std::make_shared<SimpleObject>( Prototypes::ArrowObj, false );
		SetScale( 800 );
		SetAnimation();
	}

	void Arrow::SetOrientation( Orientation orientation )
	{
		if ( orientation == Orientation_LEFT )
			MyOrientation = 1;
		else
			MyOrientation = -1;

		SetScale( Scale );
	}

	void Arrow::SetScale( float Scale )
	{
		this->Scale = Scale;
		MyObject->Base.e1 = Vector2( Scale, 0 );
		MyObject->Base.e2 = Vector2( 0, Scale * MyOrientation );
	}

	void Arrow::SetAnimation()
	{
		MyObject->Read( 0, 0 );
		MyObject->Play = true;
		MyObject->Loop = true;
		MyObject->EnqueueAnimation( 0, static_cast<float>( Tools::GlobalRnd->Rnd->NextDouble() ) * 1.5f, true );
		MyObject->DequeueTransfers();
		MyObject->Update();
	}

	void Arrow::AnimStep()
	{
		if ( MyObject->DestinationAnim() == 0 && MyObject->Loop )
			MyObject->PlayUpdate( 1 / 6.7f );
	}

	void Arrow::MyPhsxStep()
	{
		AnimStep();
	}

	void Arrow::PointTo( Vector2 pos )
	{
		PointToPos = pos;
		CoreMath::PointxAxisTo( MyObject->Base, getCore()->Data.Position - PointToPos );
		MyObject->Base.e2 *= MyOrientation;
	}

	void Arrow::Update()
	{
		MyObject->Base.Origin = getCore()->Data.Position;

		MyObject->Update();
	}

	void Arrow::MyDraw()
	{
		if ( !getCore()->MyLevel->getMainCamera()->OnScreen(getCore()->Data.Position, 600) )
			return;

		if ( Tools::DrawGraphics )
		{
			Update();
			MyObject->Draw( Tools::QDrawer, Tools::EffectWad );
		}
	}

	void Arrow::Move( Vector2 shift )
	{
		getCore()->Data.Position += shift;
	}

	void Arrow::InitializeInstanceFields()
	{
		MyOrientation = 1;
	}
}
