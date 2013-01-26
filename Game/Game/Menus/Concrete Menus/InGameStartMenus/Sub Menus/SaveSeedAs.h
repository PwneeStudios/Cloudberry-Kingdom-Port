#ifndef SAVESEEDAS
#define SAVESEEDAS

#include <global_header.h>

namespace CloudberryKingdom
{

	struct SaveSeedAs : public VerifyBaseMenu
	{

		virtual ~SaveSeedAs() { }
	
		struct SaveProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;

		
			SaveProxy( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply( const boost::shared_ptr<MenuItem> &_item );
		};

	
		struct OnOkProxy : public Lambda
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;

		
			OnOkProxy( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	
		struct SaveSeedAsOnEscapeLambda : public Lambda
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;
		
			SaveSeedAsOnEscapeLambda( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	
		struct SaveSeedAsOnEnterLambda : public Lambda
		{
		
			boost::shared_ptr<SaveSeedAs> ssa;
		
			SaveSeedAsOnEnterLambda( const boost::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};
	
		SaveSeedAs( int Control, const boost::shared_ptr<PlayerData> &Player );
		boost::shared_ptr<SaveSeedAs> SaveSeedAs_Construct( int Control, const boost::shared_ptr<PlayerData> &Player );

	
		boost::shared_ptr<PlayerData> Player;
		boost::shared_ptr<GUI_TextBox> TextBox;
		boost::shared_ptr<EzText> HeaderText;
	
		virtual void Init();

	
		void Save( const boost::shared_ptr<MenuItem> &_item );

	
		virtual void OnReturnTo();

	
		void OnOk();

	
		virtual void Release();

	
		void SetPosition();

	
		virtual void OnAdd();

	};
}


#endif	//#ifndef SAVESEEDAS
