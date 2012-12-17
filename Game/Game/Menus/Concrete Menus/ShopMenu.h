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
			boost::shared_ptr<EzSound> sound;

		
			CoinSoundPlayer( float pitch );

			void Apply();
		};

	
		struct YesProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<VerifyPurchaseMenu> vpm;

		
			YesProxy( const boost::shared_ptr<VerifyPurchaseMenu> &vpm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct NoProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<VerifyPurchaseMenu> vpm;

		
			NoProxy( const boost::shared_ptr<VerifyPurchaseMenu> &vpm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		boost::shared_ptr<Buyable> buyable;
		int Cost;
		VerifyPurchaseMenu( int Control, const boost::shared_ptr<Buyable> &buyable );
		boost::shared_ptr<VerifyPurchaseMenu> VerifyPurchaseMenu_Construct( int Control, const boost::shared_ptr<Buyable> &buyable );

	
		void Yes( const boost::shared_ptr<MenuItem> &item );

		void No( const boost::shared_ptr<MenuItem> &item );

	
		virtual void MakeBackdrop();

		virtual void Init();
	};

	struct ShopMenu : public CkBaseMenu
	{
	
		struct VerifyPurchaseProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<ShopMenu> sm;

		
			VerifyPurchaseProxy( const boost::shared_ptr<ShopMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

	
		struct OnAddHelper : public LambdaFunc<bool>
		{
		
			boost::shared_ptr<ScrollBar> bar;

		
			OnAddHelper( const boost::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	
		static boost::shared_ptr<ShopMenu> ActiveShop;

	
		virtual void ReleaseBody();

	
		void VerifyPurchase( const boost::shared_ptr<MenuItem> &item );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		void SetHeaderProperties2( const boost::shared_ptr<EzText> &text );

	
		virtual void Init();

	
		void SetBankAmount();

	
		void UpdateAll();

	
		static std::wstring ClrString( boost::shared_ptr<ClrTextFx> data );

		void SetItem( const boost::shared_ptr<MenuItem> &item );


	
		static std::wstring GetString( const boost::shared_ptr<MenuItem> &item );
		static std::wstring GetString( const boost::shared_ptr<Buyable> &buyable );

	
		void MenuGo_Customize( const boost::shared_ptr<MenuItem> &item );
		void CharSelect();

		static int HatCompare( const boost::shared_ptr<Hat> &h1, const boost::shared_ptr<Hat> &h2 );

		boost::shared_ptr<EzText> Bank, BankAmount;
	
		ShopMenu();
		boost::shared_ptr<ShopMenu> ShopMenu_Construct();
	
		void MakeHeader( boost::shared_ptr<MenuItem> &Header, const std::wstring &str );


		void MakeRest();

		void MakeBack();

#if defined(PC_VERSION)
#endif

	
		virtual void OnAdd();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef SHOPMENU
