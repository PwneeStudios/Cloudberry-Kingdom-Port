#ifndef SHOPMENU
#define SHOPMENU

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzSound;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class Buyable;
}

namespace CloudberryKingdom
{
	class ScrollBar;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Hat;
}



namespace CloudberryKingdom
{
	class VerifyPurchaseMenu : public VerifyBaseMenu
	{
	private:
		class CoinSoundPlayer : public Lambda
		{
		private:
			float pitch;
			std::shared_ptr<EzSound> sound;

		public:
			CoinSoundPlayer( float pitch );

			void Apply();
		};

	private:
		class YesProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<VerifyPurchaseMenu> vpm;

		public:
			YesProxy( const std::shared_ptr<VerifyPurchaseMenu> &vpm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class NoProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<VerifyPurchaseMenu> vpm;

		public:
			NoProxy( const std::shared_ptr<VerifyPurchaseMenu> &vpm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	public:
		std::shared_ptr<Buyable> buyable;
		int Cost;
		VerifyPurchaseMenu( int Control, const std::shared_ptr<Buyable> &buyable );

	private:
		void Yes( const std::shared_ptr<MenuItem> &item );

		void No( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void MakeBackdrop();

		virtual void Init();
	};

	class ShopMenu : public CkBaseMenu
	{
	private:
		class VerifyPurchaseProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<ShopMenu> sm;

		public:
			VerifyPurchaseProxy( const std::shared_ptr<ShopMenu> &sm );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class OnAddHelper : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<ScrollBar> bar;

		public:
			OnAddHelper( const std::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	public:
		static std::shared_ptr<ShopMenu> ActiveShop;

	protected:
		virtual void ReleaseBody();

	private:
		void VerifyPurchase( const std::shared_ptr<MenuItem> &item );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		void SetHeaderProperties2( const std::shared_ptr<EzText> &text );

	public:
		virtual void Init();

	private:
		void SetBankAmount();

	public:
		void UpdateAll();

	private:
		static std::wstring ClrString( ClrTextFx data );

		void SetItem( const std::shared_ptr<MenuItem> &item );


	public:
		static std::wstring GetString( const std::shared_ptr<MenuItem> &item );
		static std::wstring GetString( const std::shared_ptr<Buyable> &buyable );

	private:
		void MenuGo_Customize( const std::shared_ptr<MenuItem> &item );
		void CharSelect();

		static int HatCompare( const std::shared_ptr<Hat> &h1, const std::shared_ptr<Hat> &h2 );

		std::shared_ptr<EzText> Bank, BankAmount;
	public:
		ShopMenu();

	private:
		void MakeHeader( const std::shared_ptr<MenuItem> &Header, const std::wstring &str );


		void MakeRest();

		void MakeBack();

#if defined(PC_VERSION)
#endif

	public:
		virtual void OnAdd();

	protected:
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef SHOPMENU
