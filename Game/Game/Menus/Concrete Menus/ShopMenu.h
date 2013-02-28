#ifndef SHOP_MENU_H
#define SHOP_MENU_H

#include <global_header.h>

namespace CloudberryKingdom
{
	struct SmallErrorMenu : public VerifyBaseMenu
	{
	
		virtual ~SmallErrorMenu() { }

		Localization::Words Word;

		SmallErrorMenu( Localization::Words Word );
		boost::shared_ptr<SmallErrorMenu> SmallErrorMenu_Construct( Localization::Words Word );
	
		virtual void MakeBackdrop();

		virtual void Init();

		virtual void MyPhsxStep();

		virtual void SetPos();

	};

	struct UpSellMenu : public VerifyBaseMenu
	{
	
		Localization::Words Word;
		boost::shared_ptr<QuadClass> Black;

		struct YesProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<UpSellMenu> sm;
		
			YesProxy( const boost::shared_ptr<UpSellMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );

		};
	
		struct NoProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<UpSellMenu> sm;
		
			NoProxy( const boost::shared_ptr<UpSellMenu> &sm );

			void Apply( const boost::shared_ptr<MenuItem> &item );

		};

		UpSellMenu( Localization::Words Word, int Control );
		boost::shared_ptr<UpSellMenu> UpSellMenu_Construct( Localization::Words Word, int Control );
	
		virtual void MakeBackdrop();

		virtual void Init();
		virtual void MyPhsxStep();
		virtual void SetPos();

	};

}


#endif	//#ifndef SHOP_MENU_H
