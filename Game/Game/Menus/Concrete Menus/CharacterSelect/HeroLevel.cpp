#include "HeroLevel.h"
#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
#include "Game/Objects/Game Objects/GameObject.h"
#include "Core/Text/EzText.h"
#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Tools/Tools.h"
#include "Game/Tools/Resources.h"
#include "Properties/Resources.Designer.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))
using namespace Microsoft::Xna::Framework::GamerServices;
#endif

namespace CloudberryKingdom
{

	HeroLevel::HeroLevel( int Control, const std::shared_ptr<CharacterSelect> &MyCharacterSelect ) : CkBaseMenu( false )
	{
		InitializeInstanceFields();
		this->Tags += Tag_CHAR_SELECT;
		this->setControl( Control );
		this->MyCharacterSelect = MyCharacterSelect;

		Constructor();
	}

	void HeroLevel::ReleaseBody()
	{
		CkBaseMenu::ReleaseBody();

		MyCharacterSelect.reset();
	}

	void HeroLevel::Init()
	{
		CkBaseMenu::Init();

		SlideInLength = 0;
		SlideOutLength = 0;
		CallDelay = 0;
		ReturnToCallerDelay = 0;

		MyPile = std::make_shared<DrawPile>();
		EnsureFancy();

		SetHeroLevel();

		CharacterSelect::Shift( this );
	}

	void HeroLevel::SetHeroLevel()
	{
		if ( !ShowHeroLevel )
			return;

		Tools::StartGUIDraw();
		if ( MyCharacterSelect->getPlayer()->Exists )
		{
			//string name = MyCharacterSelect.Player.GetName();
			std::wstring name = _T( "Level 56" );
			Text = std::make_shared<EzText>( name, Resources::Font_Grobold42, true, true );
		}
		else
		{
			Text = std::make_shared<EzText>( _T( "ERROR" ), Resources::LilFont, true, true );
		}

		Text->Shadow = false;
		Text->PicShadow = false;

		Tools::EndGUIDraw();
	}

	void HeroLevel::InitializeInstanceFields()
	{
		ShowHeroLevel = false;
	}
}
