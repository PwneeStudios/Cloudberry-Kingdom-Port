#include <global_header.h>

#include <Core\Tools\Set.h>

namespace CloudberryKingdom
{

	//Waiting::Waiting( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	Waiting::Waiting( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect, bool _CanGoBack ) { }
	boost::shared_ptr<Waiting> Waiting::Waiting_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect, bool _CanGoBack )
	{
		CkBaseMenu::CkBaseMenu_Construct( false );

		this->Tags->Add( Tag_CHAR_SELECT );
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;
		this->CanGoBack = _CanGoBack;

		Constructor();

		return boost::static_pointer_cast<Waiting>( shared_from_this() );
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

		MyPile = boost::make_shared<DrawPile>();
		EnsureFancy();

		CharacterSelect::Shift( boost::static_pointer_cast<GUI_Panel>( shared_from_this() ) );
	}

    void Waiting::MyDraw()
    {
        if ( CharacterSelectManager::FakeHide )
            return;

        CkBaseMenu::MyDraw();
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
		if ( CanGoBack && CharacterSelectManager::Active && ButtonCheck::State( ControllerButtons_B, MyCharacterSelect->PlayerIndex ).Pressed )
		{
			ReturnToCaller();
		}
	}
}
