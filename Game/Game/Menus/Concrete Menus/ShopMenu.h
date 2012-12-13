#ifndef SHOPMENU
#define SHOPMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	struct VerifyPurchaseMenu : public VerifyBaseMenu
	{
	
		struct CoinSoundPlayer : public Lambda
		{
		
			float pitch;
			std::shared_ptr<EzSound> sound;

		
			CoinSoundPlayer( float pitch );

			void Apply();
		};

	
		struct YesProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<VerifyPurchaseMenu> vpm;

		
			YesProxy( const std::shared_ptr<VerifyPurchaseMenu> &vpm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct NoProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<VerifyPurchaseMenu> vpm;

		
			NoProxy( const std::shared_ptr<VerifyPurchaseMenu> &vpm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		std::shared_ptr<Buyable> buyable;
		int Cost;
		VerifyPurchaseMenu( int Control, const std::shared_ptr<Buyable> &buyable );
		void VerifyPurchaseMenu_Construct( int Control, const std::shared_ptr<Buyable> &buyable );

	
		void Yes( const std::shared_ptr<MenuItem> &item );

		void No( const std::shared_ptr<MenuItem> &item );

	
		virtual void MakeBackdrop();

		virtual void Init();
	};

	struct ShopMenu : public CkBaseMenu
	{
	
		struct VerifyPurchaseProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<ShopMenu> sm;

		
			VerifyPurchaseProxy( const std::shared_ptr<ShopMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	
		struct OnAddHelper : public LambdaFunc<bool>
		{
		
			std::shared_ptr<ScrollBar> bar;

		
			OnAddHelper( const std::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	
		static std::shared_ptr<ShopMenu> ActiveShop;

	
		virtual void ReleaseBody();

	
		void VerifyPurchase( const std::shared_ptr<MenuItem> &item );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		void SetHeaderProperties2( const std::shared_ptr<EzText> &text );

	
		virtual void Init();

	
		void SetBankAmount();

	
		void UpdateAll();

	
		static std::wstring ClrString( std::shared_ptr<ClrTextFx> data );

		void SetItem( const std::shared_ptr<MenuItem> &item );


	
		static std::wstring GetString( const std::shared_ptr<MenuItem> &item );
		static std::wstring GetString( const std::shared_ptr<Buyable> &buyable );

	
		void MenuGo_Customize( const std::shared_ptr<MenuItem> &item );
		void CharSelect();

		static int HatCompare( const std::shared_ptr<Hat> &h1, const std::shared_ptr<Hat> &h2 );

		std::shared_ptr<EzText> Bank, BankAmount;
	
		ShopMenu();
		void ShopMenu_Construct();
	
		void MakeHeader( std::shared_ptr<MenuItem> &Header, const std::wstring &str );


		void MakeRest();

		void MakeBack();

#if defined(PC_VERSION)
#endif

	
		virtual void OnAdd();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef SHOPMENU
