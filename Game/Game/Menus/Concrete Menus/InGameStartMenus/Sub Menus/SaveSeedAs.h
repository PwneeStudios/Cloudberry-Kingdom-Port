#ifndef SAVESEEDAS
#define SAVESEEDAS

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
	struct SaveSeedAs : public VerifyBaseMenu
	{
	
		struct SaveProxy : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		
			std::shared_ptr<SaveSeedAs> ssa;

		
			SaveProxy( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	
		struct OnOkProxy : public Lambda
		{
		
			std::shared_ptr<SaveSeedAs> ssa;

		
			OnOkProxy( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	
		struct SaveSeedAsOnEscapeLambda : public Lambda
		{
		
			std::shared_ptr<SaveSeedAs> ssa;
		
			SaveSeedAsOnEscapeLambda( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	
		struct SaveSeedAsOnEnterLambda : public Lambda
		{
		
			std::shared_ptr<SaveSeedAs> ssa;
		
			SaveSeedAsOnEnterLambda( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};
	
		SaveSeedAs( int Control, const std::shared_ptr<PlayerData> &Player );

	
		std::shared_ptr<PlayerData> Player;
		std::shared_ptr<GUI_TextBox> TextBox;
		std::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

	
		void Save( const std::shared_ptr<MenuItem> &_item );

	
		virtual void OnReturnTo();

	
		void OnOk();

	
		virtual void Release();

	
		void SetPosition();

	
		virtual void OnAdd();

	};
}


#endif	//#ifndef SAVESEEDAS
