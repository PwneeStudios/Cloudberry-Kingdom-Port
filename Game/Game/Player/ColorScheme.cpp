#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


namespace CloudberryKingdom
{

	MenuListItem::MenuListItem( const std::shared_ptr<Object> &obj, Localization::Words word )
	{
		this->obj = obj;
		this->word = word;
	}

	int Hat::GetGuid()
	{
		return Guid;
	}

	int Hat::GetPrice()
	{
		return Price;
	}

int Cheap, Mid, Hat::Expensive = 1000;
std::shared_ptr<Hat> None, Viking, Fedora, Afro, Halo, Ghost, CheckpointHead, FallingBlockHead, BlobHead, MovingBlockHead, SpikeyHead, FallingBlock3Head, Pink, Bubble, FireHead, Horns, Cloud, NoHead, TopHat, Knight, Toad, BubbleBobble, Brain, Gosu, RobinHood, Rasta, Pumpkin, BunnyEars, Pirate, Miner, Glasses, Antlers, Arrow, Bag, Cone, Pope, Rice, Santa, Sombrero, Tiki, Hat::Wizard = 0;
std::shared_ptr<Hat> Vandyke, Beard, BigBeard, Goatee, Hat::Mustache = 0;

	std::shared_ptr<EzTexture> Hat::GetTexture()
	{
		if ( HatPicTexture != 0 )
			return HatPicTexture;
		else
		{
			std::shared_ptr<BaseQuad> quad = Prototypes::bob[ BobPhsxNormal::getInstance() ]->PlayerObject->FindQuad(QuadName);
			if ( quad != 0 )
				return quad->MyTexture;
			else
				return Fireball::EmitterTexture;
		}
	}

	void Hat::Init()
	{
		HatPicScale = Vector2::One;
		QuadName = _T( "" );
		DrawHead = true;
		DrawSelf = true;
	}

	Hat::Hat()
	{
		InitializeInstanceFields();
		HatPicScale = Vector2::One;
		HatPicShift = Vector2::Zero;
		HatPicTexture.reset();
		DrawSelf = false;
		QuadName = _T( "None" );
		DrawHead = true;

		AssociatedAward.reset();
	}

	Hat::Hat( const std::wstring &QuadName )
	{
		InitializeInstanceFields();
		HatPicScale = Vector2::One;
		HatPicShift = Vector2::Zero;
		HatPicTexture.reset();
		DrawSelf = true;
		this->QuadName = QuadName;
		DrawHead = true;

		AssociatedAward.reset();
	}

	Hat::Hat( const std::wstring &QuadName, bool DrawHead )
	{
		InitializeInstanceFields();
		HatPicScale = Vector2::One;
		HatPicShift = Vector2::Zero;
		HatPicTexture.reset();
		DrawSelf = true;
		this->QuadName = QuadName;
		this->DrawHead = DrawHead;

		AssociatedAward.reset();
	}

	Hat::Hat( const std::wstring &QuadName, bool DrawHead, bool DrawSelf )
	{
		InitializeInstanceFields();
		HatPicScale = Vector2::One;
		HatPicShift = Vector2::Zero;
		HatPicTexture.reset();
		this->QuadName = QuadName;
		this->DrawHead = DrawHead;
		this->DrawSelf = DrawSelf;

		AssociatedAward.reset();
	}

	void Hat::InitializeInstanceFields()
	{
		Guid = 0;
		AllowsFacialHair = true;
		Name = Localization::Words_NONE;
	}

	ColorScheme::FindColorLambda::FindColorLambda( Localization::Words word )
	{
		this->word = word;
	}

	bool ColorScheme::FindColorLambda::Apply( const std::shared_ptr<MenuListItem> &item )
	{
		return item->word == word;
	}

	ColorScheme::FindHatLambda::FindHatLambda( Localization::Words word )
	{
		this->word = word;
	}

	bool ColorScheme::FindHatLambda::Apply( const std::shared_ptr<Hat> &item )
	{
		return item->Name == word;
	}

	std::wstring ColorScheme::ToString()
	{
		return std::wstring::Format( _T( "\"{0}\", \"{1}\", \"{2}\", \"{3}\", \"{4}\"" ), SkinColor.Name, CapeColor.Name, CapeOutlineColor.Name, HatData->Name, BeardData->Name );
	}

	int ColorScheme::IndexOf( std::vector<MenuListItem*> &list, ClrTextFx clr )
	{
		int index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<MenuListItem*>::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( static_cast<ClrTextFx>( ( *item )->obj ) == clr )
				return index;
			index++;
		}
		return -1;
	}

	int ColorScheme::IndexOf( std::vector<Hat*> &list, const std::shared_ptr<Hat> &hat )
	{
		int index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<Hat*>::const_iterator _hat = list.begin(); _hat != list.end(); ++_hat )
		{
			if ( *_hat == hat )
				return index;
			index++;
		}
		return -1;
	}

	void ColorScheme::WriteChunk_0( const std::shared_ptr<BinaryWriter> &writer )
	{
		std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
		chunk->Type = 0;

		ClrTextFx clr;

		chunk->Write( abs( IndexOf( ColorSchemeManager::BeardInfo, BeardData ) ) );

		clr = SkinColor;
		chunk->Write( abs( IndexOf( ColorSchemeManager::ColorList, clr ) ) );

		clr = CapeColor;
		chunk->Write( abs( IndexOf( ColorSchemeManager::CapeColorList, clr ) ) );

		clr = CapeOutlineColor;
		chunk->Write( abs( IndexOf( ColorSchemeManager::CapeOutlineColorList, clr ) ) );

		chunk->Write( abs( IndexOf( ColorSchemeManager::HatInfo, HatData ) ) );

		chunk->Finish( writer );
	}

	void ColorScheme::ReadChunk_0( const std::shared_ptr<Chunk> &chunk )
	{
		int index;

		try
		{
			index = chunk->ReadInt();
			BeardData = ColorSchemeManager::BeardInfo[ index ];
		}
		catch ( ... )
		{
			BeardData = ColorSchemeManager::BeardInfo[ 0 ];
		}

		try
		{
			index = chunk->ReadInt();
			SkinColor = static_cast<ClrTextFx>( ColorSchemeManager::ColorList[ index ]->obj );
		}
		catch ( ... )
		{
			SkinColor = static_cast<ClrTextFx>( ColorSchemeManager::ColorList[ 0 ]->obj );
		}

		try
		{
			index = chunk->ReadInt();
			CapeColor = static_cast<ClrTextFx>( ColorSchemeManager::CapeColorList[ index ]->obj );
		}
		catch ( ... )
		{
			CapeColor = static_cast<ClrTextFx>( ColorSchemeManager::CapeColorList[ 0 ]->obj );
		}

		try
		{
			index = chunk->ReadInt();
			CapeOutlineColor = static_cast<ClrTextFx>( ColorSchemeManager::CapeOutlineColorList[ index ]->obj );
		}
		catch ( ... )
		{
			CapeOutlineColor = static_cast<ClrTextFx>( ColorSchemeManager::CapeOutlineColorList[ 0 ]->obj );
		}

		try
		{
			index = chunk->ReadInt();
			HatData = ColorSchemeManager::HatInfo[ index ];
		}
		catch ( ... )
		{
			HatData = ColorSchemeManager::HatInfo[ 0 ];
		}
	}

	void ColorScheme::Init()
	{
		HatData = Hat::None;
		BeardData = Hat::None;
	}

	ColorScheme::ColorScheme( Localization::Words skincolor, Localization::Words capecolor, Localization::Words capeoutlinecolor, Localization::Words hatname, Localization::Words beardname )
	{
		SkinColor = static_cast<ClrTextFx>( Tools::Find( ColorSchemeManager::ColorList, std::make_shared<FindColorLambda>( skincolor ) )->obj );
		CapeColor = static_cast<ClrTextFx>( Tools::Find( ColorSchemeManager::CapeColorList, std::make_shared<FindColorLambda>( capecolor ) )->obj );
		CapeOutlineColor = static_cast<ClrTextFx>( Tools::Find( ColorSchemeManager::CapeOutlineColorList, std::make_shared<FindColorLambda>( capeoutlinecolor ) )->obj );
		HatData = Tools::Find( ColorSchemeManager::HatInfo, std::make_shared<FindHatLambda>( hatname ) );
		BeardData = Tools::Find( ColorSchemeManager::BeardInfo, std::make_shared<FindHatLambda>( beardname ) );

		if ( HatData == 0 )
			HatData = Hat::None;
		if ( BeardData == 0 )
			BeardData = Hat::Vandyke;
	}
}
