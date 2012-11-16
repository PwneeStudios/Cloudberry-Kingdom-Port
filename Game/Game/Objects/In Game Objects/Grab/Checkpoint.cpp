#include "Checkpoint.h"
#include "Core/Texture/TextureOrAnim.h"
#include "Core/Sound/EzSound.h"
#include "Core/Particle Effects/Particle.h"
#include "Game/Tools/Tools.h"
#include "Game/Collision Detection/AABox.h"
#include "Core/Graphics/Draw/Simple/SimpleObject.h"
#include "Game/Level/LevelPiece.h"
#include "Game/Tools/Recycler.h"
#include "Game/Tools/Prototypes.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Collision Detection/Phsx.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

	Checkpoint::CheckpointTileInfo::CheckpointTileInfo()
	{
		InitializeInstanceFields();
		DieTemplate = std::make_shared<Particle>();
		DieTemplate->MyQuad.Init();
		DieTemplate->MyQuad.MyEffect = Tools::BasicEffect;
		DieTemplate->MyQuad.setMyTexture( Tools::Texture( _T( "Checkpoint3" ) ) );
		DieTemplate->SetSize( TextureSize.X );
		DieTemplate->SizeSpeed = Vector2( 10, 10 );
		DieTemplate->AngleSpeed = .013f;
		DieTemplate->Life = 20;
		DieTemplate->MyColor = Vector4( 1, 1, 1,.75f );
		DieTemplate->ColorVel = Vector4( 0, 0, 0, -.065f );
	}

	void Checkpoint::CheckpointTileInfo::InitializeInstanceFields()
	{
		Sprite = std::make_shared<TextureOrAnim>( _T( "Checkpoint3" ) );
		Size = Vector2( 115, 115 );
		TextureSize = Vector2( 170, 170 );
		MySound = Tools::NewSound( _T( "Checkpoint" ),.6f );
	}

	void Checkpoint::Release()
	{
		ObjectBase::Release();

		MyPiece.reset();
	}

std::shared_ptr<EzSound> Checkpoint::MySound = 0;

	void Checkpoint::MakeNew()
	{
		Taken = TakenAnimFinished = false;

		getCore()->Init();
		getCore()->MyType = ObjectType_CHECKPOINT;
		getCore()->DrawLayer = 8;

		getCore()->ResetOnlyOnReset = true;

		MyPiece.reset();
		MyPieceIndex = -1;

		SetAnimation();
	}

	Checkpoint::Checkpoint()
	{
		Box = std::make_shared<AABox>();

		MyQuad = SimpleQuad();
		MyObject = std::make_shared<SimpleObject>( Prototypes::CheckpointObj, false );

		MakeNew();

		getCore()->BoxesOnly = false;
	}

	void Checkpoint::SetAnimation()
	{
		MyObject->Read( 0, 0 );
		MyObject->Play = true;
		MyObject->Loop = true;
		//MyObject.EnqueueAnimation(0, (float)MyLevel.Rnd.Rnd.NextDouble() * 1.5f, true);
		MyObject->EnqueueAnimation( 0, static_cast<float>( 0 ), true );
		MyObject->DequeueTransfers();
		MyObject->Update();
	}

	void Checkpoint::Revert()
	{
		Taken = false;
		ResetTakenAnim();

		MyObject->SetColor( Color( 1, 1, 1, 1 ) );
	}

	void Checkpoint::ResetTakenAnim()
	{
		TakenAnimFinished = false;
		Taken_Scale = 1;
		Taken_Alpha = 1;
	}

	void Checkpoint::Die()
	{
		Taken = true;
		ResetTakenAnim();

		if ( getCore()->MyLevel->PlayMode != 0 )
			return;

		getGame()->CheckpointGrabEvent(this);

		getInfo()->Checkpoints->MySound->Play();
	}

	void Checkpoint::Init( const std::shared_ptr<Level> &level )
	{
		ObjectBase::Init( Vector2::Zero, level );

		Box->Initialize( getCore()->Data.Position, level->getInfo()->Checkpoints->Size );

		if ( !getCore()->BoxesOnly )
		{
			MyQuad.MyEffect = Tools::BasicEffect;
			MyQuad.Set( level->getInfo()->Checkpoints->Sprite );
			MyQuad.Init();
		}

		Base.e1 = Vector2( level->getInfo()->Checkpoints->TextureSize.X, 0 );
		Base.e2 = Vector2( 0, level->getInfo()->Checkpoints->TextureSize.Y );

		Update();
	}

	void Checkpoint::AnimStep()
	{
		if ( MyObject->DestinationAnim() == 0 && MyObject->Loop )
			MyObject->PlayUpdate( 1 / 3 ); //MyAnimSpeed);
	}

	void Checkpoint::PhsxStep()
	{
		if ( !getCore()->Active )
			return;

		if ( getCore()->Data.Position.X > getCore()->MyLevel->getMainCamera()->TR.X + 350 || getCore()->Data.Position.X < getCore()->MyLevel->getMainCamera()->BL.X - 400 || getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + 350 || getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - 350 )
		{
			SkipPhsx = true;
			return;
		}

		if ( Taken && !TakenAnimFinished )
		{
			Taken_Scale += .045f;
			Taken_Alpha -= .035f;
			if ( Taken_Alpha < 0 )
			{
				ResetTakenAnim();
				TakenAnimFinished = true;
			}
		}

		AnimStep();

		Box->SetTarget( getCore()->Data.Position, Box->Current->Size );
		if ( SkipPhsx )
			Box->SwapToCurrent();

		SkipPhsx = false;
	}

	void Checkpoint::PhsxStep2()
	{
		if ( !getCore()->Active )
			return;
		if ( SkipPhsx )
			return;

		Box->SwapToCurrent();

		Update();
	}

	void Checkpoint::Update()
	{
		MyObject->Base.Origin -= MyObject->Boxes[ 0 ]->Center() - Box->Current->Center;

		MyObject->Base.e1.X = 1;
		MyObject->Base.e2.Y = 1;
		MyObject->Update();

		Vector2 CurSize = MyObject->Boxes[ 0 ]->Size() / 2;
		float Scale = Box->Current->Size.X / CurSize.X;
		if ( Taken )
			Scale *= Taken_Scale;
		MyObject->Base.e1.X = Scale;
		MyObject->Base.e2.Y = Scale;

		MyObject->Update();
	}

	void Checkpoint::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;

		getCore()->Data.Position = getCore()->StartData.Position;

		Box->SetTarget( getCore()->Data.Position, Box->Current->Size );
		Box->SwapToCurrent();

		Update();
	}

	void Checkpoint::Move( Vector2 shift )
	{
		getCore()->StartData.Position += shift;
		getCore()->Data.Position += shift;
		Box->Move( shift );
	}

	void Checkpoint::Interact( const std::shared_ptr<Bob> &bob )
	{
		if ( Taken )
			return;
		if ( !getCore()->Active )
			return;
		if ( getCore()->MyLevel->SuppressCheckpoints || getCore()->MyLevel->GhostCheckpoints )
			return;

		ColType Col = Phsx::CollisionTest( bob->Box2, Box );
		if ( Col != ColType_NO_COL )
		{
			Die();

			if ( getCore()->MyLevel->PlayMode == 0 && MyPiece != 0 )
			{
				// Track stats
				bob->getMyStats()->Checkpoints++;
				bob->getMyStats()->Score += 250;

				// Erase taken coins
				getCore()->MyLevel->KeepCoinsDead();

				// Set current level piece
				getCore()->MyLevel->SetCurrentPiece(MyPiece);

				//////Core.MyLevel.CurPiece = MyPiece;

				//////// Change piece associated with each bob
				//////int Count = 0;
				//////foreach (Bob _bob in bob.Core.MyLevel.Bobs)
				//////{                        
				//////    _bob.MyPiece = MyPiece;
				//////    _bob.MyPieceIndex = Count % MyPiece.NumBobs;

				//////    Count++;
				//////}

				// Game's checkpoint action
				getCore()->MyLevel->MyGame->GotCheckpoint(bob);

				// Kill other checkpoints
				for ( std::vector<ObjectBase*>::const_iterator obj = getCore()->MyLevel->Objects.begin(); obj != getCore()->MyLevel->Objects.end(); ++obj )
				{
					std::shared_ptr<Checkpoint> checkpoint = dynamic_cast<Checkpoint*>( *obj );
					if ( 0 != checkpoint )
						if ( checkpoint->MyPiece == MyPiece )
							checkpoint->Die();
				}
			}
		}
	}

	void Checkpoint::SetAlpha()
	{
		if ( getCore()->MyLevel->GhostCheckpoints )
		{
			if ( !GhostFaded )
			{
				MyQuad.SetColor( Color( 255, 255, 255, 90 ) );
				MyObject->SetColor( Color( 255, 255, 255, 90 ) );
				GhostFaded = true;
			}
		}
		else
		{
			if ( GhostFaded )
			{
				MyQuad.SetColor( Color( 255, 255, 255, 255 ) );
				MyObject->SetColor( Color( 255, 255, 255, 255 ) );
				GhostFaded = false;
			}

			if ( Taken )
			{
				MyObject->SetColor( Color( 1, 1, 1, Taken_Alpha ) );
			}
		}
	}

	void Checkpoint::Draw()
	{
		if ( TakenAnimFinished && !getCore()->MyLevel->GhostCheckpoints )
			return;
		if ( !getCore()->Active )
			return;
		if ( getCore()->MyLevel->SuppressCheckpoints && !getCore()->MyLevel->GhostCheckpoints )
			return;

		if ( Box->Current->BL.X > getCore()->MyLevel->getMainCamera()->TR.X + 150 || Box->Current->BL.Y > getCore()->MyLevel->getMainCamera()->TR.Y + 150 )
			return;
		if ( Box->Current->TR.X < getCore()->MyLevel->getMainCamera()->BL.X - 200 || Box->Current->TR.Y < getCore()->MyLevel->getMainCamera()->BL.Y - 150 )
			return;

		if ( Tools::DrawGraphics && !getCore()->BoxesOnly )
		{
			SetAlpha();
			//Tools.QDrawer.DrawQuad(ref MyQuad);

			MyObject->Draw( Tools::QDrawer, Tools::EffectWad );
			Tools::QDrawer->Flush();
		}
		if ( Tools::DrawBoxes )
			Box->Draw( Tools::QDrawer, Color::Bisque, 10 );
	}

	void Checkpoint::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<Checkpoint> CheckpointA = dynamic_cast<Checkpoint*>( A );

		GhostFaded = CheckpointA->GhostFaded;
		Taken = CheckpointA->Taken;

		Box->SetTarget( CheckpointA->Box->Target->Center, CheckpointA->Box->Target->Size );
		Box->SetCurrent( CheckpointA->Box->Current->Center, CheckpointA->Box->Current->Size );
	}
}
