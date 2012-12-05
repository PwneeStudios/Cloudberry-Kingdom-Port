#ifndef COLORSCHEME
#define COLORSCHEME

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuListItem
	{
	public:
		std::shared_ptr<void> obj;
		Localization::Words word;

		MenuListItem( const std::shared_ptr<void> &obj, Localization::Words word );
	};

	class Hat : public Buyable
	{
	public:
		int GetGuid();
		int GetPrice();

		int Guid;

		static int Cheap, Mid, Expensive;

//C# TO C++ CONVERTER NOTE: The variable Cloud was renamed since it is named the same as a user-defined type:
//C# TO C++ CONVERTER NOTE: The variable Arrow was renamed since it is named the same as a user-defined type:
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

	private:
		void InitializeInstanceFields();
	};

	class ColorScheme
	{
	private:
		class FindColorLambda : public LambdaFunc_1<std::shared_ptr<MenuListItem> , bool>
		{
		private:
			Localization::Words word;
		public:
			FindColorLambda( Localization::Words word );

			bool Apply( const std::shared_ptr<MenuListItem> &item );
		};

	private:
		class FindHatLambda : public LambdaFunc_1<std::shared_ptr<Hat> , bool>
		{
		private:
			Localization::Words word;
		public:
			FindHatLambda( Localization::Words word );

			bool Apply( const std::shared_ptr<Hat> &item );
		};

	public:
		virtual std::wstring ToString();

	private:
		int IndexOf( std::vector<std::shared_ptr<MenuListItem> > &list, ClrTextFx clr );

		int IndexOf( std::vector<std::shared_ptr<Hat> > &list, const std::shared_ptr<Hat> &hat );


	public:
		void WriteChunk_0( const std::shared_ptr<BinaryWriter> &writer );

		void ReadChunk_0( const std::shared_ptr<Chunk> &chunk );

		std::shared_ptr<ClrTextFx> SkinColor, CapeColor, CapeOutlineColor;
		std::shared_ptr<Hat> HatData, BeardData;

		void Init();

		ColorScheme( Localization::Words skincolor, Localization::Words capecolor, Localization::Words capeoutlinecolor, Localization::Words hatname, Localization::Words beardname );
	};
}


#endif	//#ifndef COLORSCHEME
