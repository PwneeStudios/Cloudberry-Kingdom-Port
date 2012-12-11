#ifndef LOADSEEDAS
#define LOADSEEDAS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuItem;
}

namespace CloudberryKingdom
{
	struct PlayerData;
}

namespace CloudberryKingdom
{
	struct GUI_TextBox;
}

namespace CloudberryKingdom
{
	struct EzText;
}




namespace CloudberryKingdom
{
	struct LoadSeedAs : public VerifyBaseMenu
	{
	
		struct LoadSeedAsOnEnterLambda : public Lambda
		{
		
			std::shared_ptr<LoadSeedAs> lsa;
		
			LoadSeedAsOnEnterLambda( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	
		struct LoadSeedAsBackLambda : public Lambda
		{
		
			std::shared_ptr<LoadSeedAs> lsa;
		
			LoadSeedAsBackLambda( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	
		struct LoadProxy1 : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<LoadSeedAs> lsa;

		
			LoadProxy1( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	
		LoadSeedAs( int Control, const std::shared_ptr<PlayerData> &Player );

	
		std::shared_ptr<PlayerData> Player;
		std::shared_ptr<GUI_TextBox> TextBox;
		std::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

		virtual void Release();

	
		void SetPosition();

	
		virtual void OnAdd();

	
		void Load( const std::shared_ptr<MenuItem> &_item );
	};
}


#endif	//#ifndef LOADSEEDAS
