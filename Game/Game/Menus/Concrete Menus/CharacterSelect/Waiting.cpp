#include <global_header.h>

namespace CloudberryKingdom
{

	//Waiting::Waiting( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	Waiting::Waiting( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) { }
	std::shared_ptr<Waiting> Waiting::Waiting_Construct( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();

		return std::static_pointer_cast<Waiting>( shared_from_this() );
	}

	void Waiting::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void Waiting::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		if ( MyCharacterSelect->QuickJoin )
			MyCharacterSelect->Join = true;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		CharacterSelect::Shift( std::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

	void Waiting::MyPhsxStep()
	{
		CkBaseMenu::MyPhsxStep();

		if ( !Active )
			return;
		MyCharacterSelect->MyState = CharacterSelect::SelectState_WAITING;
		MyCharacterSelect->MyDoll->ShowBob = true;
		MyCharacterSelect->MyGamerTag->ShowGamerTag = true;
		MyCharacterSelect->MyHeroLevel->ShowHeroLevel = true;

		// Check for back.
		if ( ButtonCheck::State( ControllerButtons_B, MyCharacterSelect->PlayerIndex ).Pressed )
		{
			ReturnToCaller();
		}
	}
}
