#ifndef LOADSEEDAS
#define LOADSEEDAS

#include <global_header.h>

namespace CloudberryKingdom
{

	struct LoadSeedAs : public VerifyBaseMenu
	{

		virtual ~LoadSeedAs()
		{
#ifdef BOOST_BIN
			OnDestructor( "LoadSeedAs" );
#endif
		}

	
		struct LoadSeedAsOnEnterLambda : public Lambda
		{
		
			boost::shared_ptr<LoadSeedAs> lsa;
		
			LoadSeedAsOnEnterLambda( const boost::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	
		struct LoadSeedAsBackLambda : public Lambda
		{
		
			boost::shared_ptr<LoadSeedAs> lsa;
		
			LoadSeedAsBackLambda( const boost::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	
		struct LoadProxy1 : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<LoadSeedAs> lsa;

		
			LoadProxy1( const boost::shared_ptr<LoadSeedAs> &lsa );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		LoadSeedAs( int Control, const boost::shared_ptr<PlayerData> &Player );
		boost::shared_ptr<LoadSeedAs> LoadSeedAs_Construct( int Control, const boost::shared_ptr<PlayerData> &Player );

	
		boost::shared_ptr<PlayerData> Player;
		boost::shared_ptr<GUI_TextBox> TextBox;
		boost::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

		virtual void Release();

	
		void SetPosition();

	
		virtual void OnAdd();

	
		void Load( const boost::shared_ptr<MenuItem> &_item );
	};
}


#endif	//#ifndef LOADSEEDAS
