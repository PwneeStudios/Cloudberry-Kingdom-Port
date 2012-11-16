#include "Sign.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include "Game/Objects/Door/Door.h"
#include "Game/Tools/Tools.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	void Sign::MakeNew()
	{
		getCore()->Init();
		getCore()->DrawLayer = 1;
		getCore()->ResetOnlyOnReset = true;

		getCore()->EditHoldable = true;
	}

	Sign::Sign( bool BoxesOnly, const std::shared_ptr<Level> &level )
	{
		InitializeInstanceFields();
		getCore()->BoxesOnly = BoxesOnly;

		MakeNew();

		getCore()->BoxesOnly = BoxesOnly;

		std::shared_ptr<CloudberryKingdom::Door::DoorTileInfo> info = level->getInfo()->Doors;
		MyQuad = std::make_shared<QuadClass>();
		MyQuad->Set( info->Sign_Renamed );
	}

	void Sign::SetState( bool NewOnState )
	{
		OnState = NewOnState;

		if ( NewOnState )
			MyQuad->Quad_Renamed->CalcTexture( 0, 0 );
		else
			MyQuad->Quad_Renamed->CalcTexture( 0, 1 );

		Count = 1;
	}

int OffLength, Sign::OnLength = 58;

	void Sign::PhsxStep()
	{
		Count++;

		if ( !OnState && Count == OffLength )
		{
			SetState( true );
			Count = 0;
		}
		if ( OnState && Count == OnLength )
		{
			SetState( false );
			Count = 0;
		}
	}

	bool Sign::OnScreen()
	{
		if ( getCore()->BoxesOnly )
			return false;

		if ( getCore()->Data.Position.X > getCore()->MyLevel->getMainCamera()->TR.X + 150 + MyQuad->Base.e1.X || getCore()->Data.Position.Y > getCore()->MyLevel->getMainCamera()->TR.Y + 150 + MyQuad->Base.e2.Y )
			return false;
		if ( getCore()->Data.Position.X < getCore()->MyLevel->getMainCamera()->BL.X - 150 - MyQuad->Base.e1.X || getCore()->Data.Position.Y < getCore()->MyLevel->getMainCamera()->BL.Y - 500 - MyQuad->Base.e2.Y )
			return false;

		return true;
	}

	void Sign::Draw()
	{
		if ( !OnScreen() )
			return;

		if ( Tools::DrawGraphics )
		{
			if ( !getInfo()->Doors->Show || !getInfo()->Doors->ShowSign )
				return;

			float x = MyQuad->getSizeX();
			if ( getCore()->MyLevel != 0 && getCore()->MyLevel->ModZoom.X < 0 )
			{
				if ( MyQuad->Base.e1.X > 0 )
					MyQuad->setSizeX( -x );
			}
			else
			{
				if ( MyQuad->Base.e1.X < 0 )
					MyQuad->setSizeX( -x );
			}

			MyQuad->Draw();
		}
	}

	Microsoft::Xna::Framework::Vector2 Sign::GetBottom()
	{
		MyQuad->Update();
		return Vector2( getCore()->Data.Position.X, MyQuad->getBL().Y + 11.5f );
	}

	void Sign::PlaceAt( Vector2 pos )
	{
		Move( pos - GetBottom() - Vector2(0, 16) );
	}

	void Sign::Update()
	{
		MyQuad->Base.Origin = getCore()->Data.Position;
	}

	void Sign::Move( Vector2 shift )
	{
		getCore()->Data.Position += shift;
		Update();
	}

	void Sign::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;
	}

	void Sign::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		getCore()->Write(writer);

		MyQuad->Write( writer );
	}

	void Sign::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		getCore()->Read(reader);

		MyQuad->Read( reader );
	}

	void Sign::InitializeInstanceFields()
	{
		Count = 1;
		OnState = true;
	}
}
