#include "ZoneTrigger.h"
#include "Core/Lambdas/Lambda_1.h"
#include "Game/Collision Detection/AABox.h"
#include "Game/Tools/Recycler.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Collision Detection/Phsx.h"

using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

	void ZoneTrigger::MakeNew()
	{
		getCore()->Init();
		getCore()->MyType = ObjectType_ZONE_TRIGGER;
	}

	ZoneTrigger::ZoneTrigger()
	{
		Box = std::make_shared<AABox>();

		MakeNew();
	}

	void ZoneTrigger::Init( Vector2 center, Vector2 size )
	{
		getCore()->Data.Position = center;
		Box->Initialize( center, size );
	}

	void ZoneTrigger::Update()
	{
	}

	void ZoneTrigger::Reset( bool BoxesOnly )
	{
		getCore()->Active = true;
	}

	void ZoneTrigger::Move( Vector2 shift )
	{
		getCore()->Data.Position += shift;
		Box->Move( shift );
	}

	void ZoneTrigger::Interact( const std::shared_ptr<Bob> &bob )
	{
		if ( MyContainsEvent == 0 )
			return;

		if ( !getCore()->Active )
			return;
		bool Overlap = Phsx::BoxBoxOverlap( bob->Box, Box );
		if ( Overlap )
			MyContainsEvent->Apply( this );
	}

	void ZoneTrigger::Draw()
	{
		//if (Tools.DrawBoxes && Core.Active)
		//    Box.Draw(Tools.QDrawer, Color.Teal, 30);
	}

	void ZoneTrigger::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		std::shared_ptr<ZoneTrigger> TriggerA = dynamic_cast<ZoneTrigger*>( A );
		Box->Initialize( TriggerA->Box.Current->Center, TriggerA->Box.Current->Size );
		MyContainsEvent = TriggerA->MyContainsEvent;
	}
}
