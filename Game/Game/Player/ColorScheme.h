#ifndef COLORSCHEME
#define COLORSCHEME

#include <small_header.h>

//#include "Core/Chunk.h"
//#include "Core/Graphics/Draw/Quads/BaseQuad.h"
#include "Game/Localization.h"
//#include "Core/Texture/EzTexture.h"
#include "Game/Player/Buyable.h"
//#include "Game/Player/ClrTextFx.h"
//#include "Game/Objects/In Game Objects/Obstacles/CloudberryKingdom.Fireball.h"
//#include "Game/Player/ColorSchemeManager.h"
//#include "Game/Player/Awardments/Awardment.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Tools/Prototypes.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct MenuListItem
	{
	
		boost::shared_ptr<Object> obj;
		Localization::Words word;

		MenuListItem( const boost::shared_ptr<Object> &obj, Localization::Words word );
	};

	struct Hat : public Buyable
	{

	
		static void InitializeStatics();

	
		int GetGuid();
		int GetPrice();

		int Guid;

		static int Cheap, Mid, Expensive;

		static boost::shared_ptr<Hat> None, Viking, Fedora, Afro, Halo, Ghost, CheckpointHead, FallingBlockHead, BlobHead, MovingBlockHead, SpikeyHead, FallingBlock3Head, Pink, Bubble, FireHead, Horns, Cloud_Renamed, NoHead, TopHat, Knight, Toad, BubbleBobble, Brain, Gosu, RobinHood, Rasta, Pumpkin, BunnyEars, Pirate, Miner, Glasses, Antlers, Arrow_Renamed, Bag, Cone, Pope, Rice, Santa, Sombrero, Tiki, Wizard;

		static boost::shared_ptr<Hat> Vandyke, Beard, BigBeard, Goatee, Mustache;

		int Price;

		std::wstring QuadName;
		boost::shared_ptr<EzTexture> HatPicTexture;
		bool DrawHead, DrawSelf;
		Vector2 HatPicScale, HatPicShift;

		bool AllowsFacialHair;

		Localization::Words Name;

		boost::shared_ptr<Awardment> AssociatedAward;

		boost::shared_ptr<EzTexture> GetTexture();

		void Init();

		Hat();

		Hat( const std::wstring &QuadName );

		Hat( const std::wstring &QuadName, bool DrawHead );

		Hat( const std::wstring &QuadName, bool DrawHead, bool DrawSelf );

	
		void InitializeInstanceFields();
	};

	struct ColorScheme
	{
	
		struct FindColorLambda : public LambdaFunc_1<boost::shared_ptr<MenuListItem> , bool>
		{
		
			Localization::Words word;
		
			FindColorLambda( Localization::Words word );

			bool Apply( const boost::shared_ptr<MenuListItem> &item );
		};

	
		struct FindHatLambda : public LambdaFunc_1<boost::shared_ptr<Hat> , bool>
		{
		
			Localization::Words word;
		
			FindHatLambda( Localization::Words word );

			bool Apply( const boost::shared_ptr<Hat> &item );
		};

	
		std::wstring ToString();

	
		int IndexOf( std::vector<boost::shared_ptr<MenuListItem> > &list, const boost::shared_ptr<ClrTextFx> &clr );

		int IndexOf( std::vector<boost::shared_ptr<Hat> > &list, const boost::shared_ptr<Hat> &hat );


	
		void WriteChunk_0( const boost::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_0( const boost::shared_ptr<Chunk> &chunk );

		boost::shared_ptr<ClrTextFx> SkinColor, CapeColor, CapeOutlineColor;
		boost::shared_ptr<Hat> HatData, BeardData;

		void Init();

		ColorScheme();
		ColorScheme( Localization::Words skincolor, Localization::Words capecolor, Localization::Words capeoutlinecolor, Localization::Words hatname, Localization::Words beardname );
	};
}


#endif	//#ifndef COLORSCHEME
