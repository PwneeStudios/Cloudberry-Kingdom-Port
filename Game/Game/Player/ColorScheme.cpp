#include <global_header.h>

#include <Hacks/List.h>
#include <Hacks/String.h>

namespace CloudberryKingdom
{

	void Hat::InitializeStatics()
	{
		Hat::Cheap = 100;
		Hat::Mid = 250;
		Hat::Expensive = 1000;
	}

	// Statics
	int Hat::Cheap, Hat::Mid, Hat::Expensive;
	boost::shared_ptr<Hat> Hat::None, Hat::Viking, Hat::Fedora, Hat::Afro, Hat::Halo, Hat::Ghost, Hat::CheckpointHead, Hat::FallingBlockHead, Hat::BlobHead, Hat::MovingBlockHead, Hat::SpikeyHead, Hat::FallingBlock3Head, Hat::Pink, Hat::Bubble, Hat::FireHead, Hat::Horns, Hat::Cloud_Renamed, Hat::NoHead, Hat::TopHat, Hat::Knight, Hat::Toad, Hat::BubbleBobble, Hat::Brain, Hat::Gosu, Hat::RobinHood, Hat::Rasta, Hat::Pumpkin, Hat::BunnyEars, Hat::Pirate, Hat::Miner, Hat::Glasses, Hat::Antlers, Hat::Arrow_Renamed, Hat::Bag, Hat::Cone, Hat::Pope, Hat::Rice, Hat::Santa, Hat::Sombrero, Hat::Tiki, Hat::Wizard;
	boost::shared_ptr<Hat> Hat::Vandyke, Hat::Beard, Hat::BigBeard, Hat::Goatee, Hat::Mustache;


	MenuListItem::MenuListItem( const boost::shared_ptr<Object> &obj, Localization::Words word )
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

	boost::shared_ptr<EzTexture> Hat::GetTexture()
	{
		if ( HatPicTexture != 0 )
			return HatPicTexture;
		else
		{
			boost::shared_ptr<BaseQuad> quad = Prototypes::bob[ BobPhsxNormal::getInstance() ]->PlayerObject->FindQuad(QuadName);
			if ( quad != 0 )
				return quad->MyTexture;
			else
				return Fireball::EmitterTexture;
		}
	}

	void Hat::Init()
	{
		HatPicScale = Vector2(1);
		QuadName = std::wstring( L"" );
		DrawHead = true;
		DrawSelf = true;
	}

	Hat::Hat() :
		Guid( 0 ),
		Price( 0 ),
		DrawHead( false ),
		DrawSelf( false ),
		AllowsFacialHair( false ),
		Name( Localization::Words_None )
	{
		InitializeInstanceFields();
		HatPicScale = Vector2(1);
		HatPicShift = Vector2();
		HatPicTexture.reset();
		DrawSelf = false;
		QuadName = std::wstring( L"None" );
		DrawHead = true;

		AssociatedAward.reset();
	}

	Hat::Hat( const std::wstring &QuadName ) :
		Guid( 0 ),
		Price( 0 ),
		DrawHead( false ),
		DrawSelf( false ),
		AllowsFacialHair( false ),
		Name( Localization::Words_None )
	{
		InitializeInstanceFields();
		HatPicScale = Vector2(1);
		HatPicShift = Vector2();
		HatPicTexture.reset();
		DrawSelf = true;
		this->QuadName = QuadName;
		DrawHead = true;

		AssociatedAward.reset();
	}

	Hat::Hat( const std::wstring &QuadName, bool DrawHead ) :
		Guid( 0 ),
		Price( 0 ),
		DrawHead( false ),
		DrawSelf( false ),
		AllowsFacialHair( false ),
		Name( Localization::Words_None )
	{
		InitializeInstanceFields();
		HatPicScale = Vector2(1);
		HatPicShift = Vector2();
		HatPicTexture.reset();
		DrawSelf = true;
		this->QuadName = QuadName;
		this->DrawHead = DrawHead;

		AssociatedAward.reset();
	}

	Hat::Hat( const std::wstring &QuadName, bool DrawHead, bool DrawSelf ) :
		Guid( 0 ),
		Price( 0 ),
		DrawHead( false ),
		DrawSelf( false ),
		AllowsFacialHair( false ),
		Name( Localization::Words_None )
	{
		InitializeInstanceFields();
		HatPicScale = Vector2(1);
		HatPicShift = Vector2();
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
		Name = Localization::Words_None;
	}

	ColorScheme::FindColorLambda::FindColorLambda( Localization::Words word )
	{
		this->word = word;
	}

	bool ColorScheme::FindColorLambda::Apply( const boost::shared_ptr<MenuListItem> &item )
	{
		return item->word == word;
	}

	ColorScheme::FindHatLambda::FindHatLambda( Localization::Words word )
	{
		this->word = word;
	}

	bool ColorScheme::FindHatLambda::Apply( const boost::shared_ptr<Hat> &item )
	{
		return item->Name == word;
	}

	std::wstring ColorScheme::ToString()
	{
		return Format( _T( "\"%d\", \"%d\", \"%d\", \"%d\", \"%d\"" ), SkinColor->Name, CapeColor->Name, CapeOutlineColor->Name, HatData->Name, BeardData->Name );
	}

	int ColorScheme::IndexOf( std::vector<boost::shared_ptr<MenuListItem> > &list, const boost::shared_ptr<ClrTextFx> &clr )
	{
		int index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<MenuListItem> >::const_iterator item = list.begin(); item != list.end(); ++item )
		{
			if ( boost::static_pointer_cast<ClrTextFx>( ( *item )->obj ) == clr )
				return index;
			index++;
		}
		return -1;
	}

	int ColorScheme::IndexOf( std::vector<boost::shared_ptr<Hat> > &list, const boost::shared_ptr<Hat> &hat )
	{
		int index = 0;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<Hat> >::const_iterator _hat = list.begin(); _hat != list.end(); ++_hat )
		{
			if ( *_hat == hat )
				return index;
			index++;
		}
		return -1;
	}

	void ColorScheme::WriteChunk_0( const boost::shared_ptr<BinaryWriter> &writer )
	{
		boost::shared_ptr<Chunk> chunk = boost::make_shared<Chunk>();
		chunk->Type = 0;

		boost::shared_ptr<ClrTextFx> clr;

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

	void ColorScheme::ReadChunk_0( const boost::shared_ptr<Chunk> &chunk )
	{
		int index;

		// FIXME: Check all the try/catches.
		/*try
		{*/
			index = chunk->ReadInt();
			BeardData = ColorSchemeManager::BeardInfo[ index ];
		/*}
		catch ( ... )
		{
			BeardData = ColorSchemeManager::BeardInfo[ 0 ];
		}*/

		/*try
		{*/
			index = chunk->ReadInt();
			SkinColor = boost::static_pointer_cast<ClrTextFx>( ColorSchemeManager::ColorList[ index ]->obj );
		/*}
		catch ( ... )
		{
			SkinColor = boost::static_pointer_cast<ClrTextFx>( ColorSchemeManager::ColorList[ 0 ]->obj );
		}*/

		/*try
		{*/
			index = chunk->ReadInt();
			CapeColor = boost::static_pointer_cast<ClrTextFx>( ColorSchemeManager::CapeColorList[ index ]->obj );
		/*}
		catch ( ... )
		{
			CapeColor = boost::static_pointer_cast<ClrTextFx>( ColorSchemeManager::CapeColorList[ 0 ]->obj );
		}*/

		/*try
		{*/
			index = chunk->ReadInt();
			CapeOutlineColor = boost::static_pointer_cast<ClrTextFx>( ColorSchemeManager::CapeOutlineColorList[ index ]->obj );
		/*}
		catch ( ... )
		{
			CapeOutlineColor = boost::static_pointer_cast<ClrTextFx>( ColorSchemeManager::CapeOutlineColorList[ 0 ]->obj );
		}*/

		/*try
		{*/
			index = chunk->ReadInt();
			HatData = ColorSchemeManager::HatInfo[ index ];
		/*}
		catch ( ... )
		{
			HatData = ColorSchemeManager::HatInfo[ 0 ];
		}*/
	}

	void ColorScheme::Init()
	{
		HatData = Hat::None;
		BeardData = Hat::None;
	}

	ColorScheme::ColorScheme()
	{
		SkinColor = boost::make_shared<ClrTextFx>();
		CapeColor = boost::make_shared<ClrTextFx>();
		CapeOutlineColor = boost::make_shared<ClrTextFx>();
		HatData = Hat::None;
		BeardData = Hat::Vandyke;
	}

	ColorScheme::ColorScheme( Localization::Words skincolor, Localization::Words capecolor, Localization::Words capeoutlinecolor, Localization::Words hatname, Localization::Words beardname )
	{
		SkinColor = boost::static_pointer_cast<ClrTextFx>( Tools::Find( ColorSchemeManager::ColorList,
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<MenuListItem>, bool> >( boost::make_shared<FindColorLambda>( skincolor ) ) )->obj );
		CapeColor = boost::static_pointer_cast<ClrTextFx>( Tools::Find( ColorSchemeManager::CapeColorList,
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<MenuListItem>, bool> >( boost::make_shared<FindColorLambda>( capecolor ) ) )->obj );
		CapeOutlineColor = boost::static_pointer_cast<ClrTextFx>( Tools::Find( ColorSchemeManager::CapeOutlineColorList,
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<MenuListItem>, bool> >( boost::make_shared<FindColorLambda>( capeoutlinecolor ) ) )->obj );
		HatData = Tools::Find( ColorSchemeManager::HatInfo,
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<Hat>, bool> >( boost::make_shared<FindHatLambda>( hatname ) ) );
		BeardData = Tools::Find( ColorSchemeManager::BeardInfo,
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<Hat>, bool> >( boost::make_shared<FindHatLambda>( beardname ) ) );

		if ( HatData == 0 )
			HatData = Hat::None;
		if ( BeardData == 0 )
			BeardData = Hat::Vandyke;
	}
}
