#ifndef COLORSCHEME
#define COLORSCHEME

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuListItem
	{
	
		std::shared_ptr<Object> obj;
		Localization::Words word;

		MenuListItem( const std::shared_ptr<Object> &obj, Localization::Words word );
	};

	struct Hat : public Buyable
	{

	
		static void InitializeStatics();

	
		int GetGuid();
		int GetPrice();

		int Guid;

		static int Cheap, Mid, Expensive;

		static std::shared_ptr<Hat> None, Viking, Fedora, Afro, Halo, Ghost, CheckpointHead, FallingBlockHead, BlobHead, MovingBlockHead, SpikeyHead, FallingBlock3Head, Pink, Bubble, FireHead, Horns, Cloud_Renamed, NoHead, TopHat, Knight, Toad, BubbleBobble, Brain, Gosu, RobinHood, Rasta, Pumpkin, BunnyEars, Pirate, Miner, Glasses, Antlers, Arrow_Renamed, Bag, Cone, Pope, Rice, Santa, Sombrero, Tiki, Wizard;

		static std::shared_ptr<Hat> Vandyke, Beard, BigBeard, Goatee, Mustache;

		int Price;

		std::wstring QuadName;
		std::shared_ptr<EzTexture> HatPicTexture;
		bool DrawHead, DrawSelf;
		Vector2 HatPicScale, HatPicShift;

		bool AllowsFacialHair;

		Localization::Words Name;

		std::shared_ptr<Awardment> AssociatedAward;

		std::shared_ptr<EzTexture> GetTexture();

		void Init();

		Hat();

		Hat( const std::wstring &QuadName );

		Hat( const std::wstring &QuadName, bool DrawHead );

		Hat( const std::wstring &QuadName, bool DrawHead, bool DrawSelf );

	
		void InitializeInstanceFields();
	};

	struct ColorScheme
	{
	
		struct FindColorLambda : public LambdaFunc_1<std::shared_ptr<MenuListItem> , bool>
		{
		
			Localization::Words word;
		
			FindColorLambda( Localization::Words word );

			bool Apply( const std::shared_ptr<MenuListItem> &item );
		};

	
		struct FindHatLambda : public LambdaFunc_1<std::shared_ptr<Hat> , bool>
		{
		
			Localization::Words word;
		
			FindHatLambda( Localization::Words word );

			bool Apply( const std::shared_ptr<Hat> &item );
		};

	
		virtual std::wstring ToString();

	
		int IndexOf( std::vector<std::shared_ptr<MenuListItem> > &list, const std::shared_ptr<ClrTextFx> &clr );

		int IndexOf( std::vector<std::shared_ptr<Hat> > &list, const std::shared_ptr<Hat> &hat );


	
		void WriteChunk_0( const std::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_0( const std::shared_ptr<Chunk> &chunk );

		std::shared_ptr<ClrTextFx> SkinColor, CapeColor, CapeOutlineColor;
		std::shared_ptr<Hat> HatData, BeardData;

		void Init();

		ColorScheme();
		ColorScheme( Localization::Words skincolor, Localization::Words capecolor, Localization::Words capeoutlinecolor, Localization::Words hatname, Localization::Words beardname );
	};
}


#endif	//#ifndef COLORSCHEME
