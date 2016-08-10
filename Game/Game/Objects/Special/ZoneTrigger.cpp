#include <small_header.h>
#include "Game/Objects/Special/ZoneTrigger.h"

#include "Game/Collision Detection/AABox.h"
#include "Game/Collision Detection/Phsx.h"
#include "Game/Objects/ObjectBase.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Tools/Recycler.h"

#include "Game/Collision Detection/FloatRectangle.h"

namespace CloudberryKingdom
{

	void ZoneTrigger::MakeNew()
	{
		getCore()->Init();
		getCore()->MyType = ObjectType_ZONE_TRIGGER;
	}

	ZoneTrigger::ZoneTrigger()
	{
		Box = boost::make_shared<AABox>();

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

	void ZoneTrigger::Interact( const boost::shared_ptr<Bob> &bob )
	{
		if ( MyContainsEvent == 0 )
			return;

		if ( !getCore()->Active )
			return;
		bool Overlap = Phsx::BoxBoxOverlap( bob->Box, Box );
		if ( Overlap )
			MyContainsEvent->Apply( boost::static_pointer_cast<ZoneTrigger>( shared_from_this() ) );
	}

	void ZoneTrigger::Draw()
	{
		//if (Tools::DrawBoxes && Core.Active)
		//    Box.Draw(Tools::QDrawer, Color.Teal, 30);
	}

	void ZoneTrigger::Clone( const boost::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		boost::shared_ptr<ZoneTrigger> TriggerA = boost::dynamic_pointer_cast<ZoneTrigger>( A );
		Box->Initialize( TriggerA->Box->Current->Center, TriggerA->Box->Current->Size );
		MyContainsEvent = TriggerA->MyContainsEvent;
	}

	void ZoneTrigger::Release()
	{
		Box.reset();
		MyContainsEvent.reset();

		ObjectBase::Release();
	}
}
