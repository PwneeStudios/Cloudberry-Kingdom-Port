#ifndef LOADSEEDAS
#define LOADSEEDAS

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class GUI_TextBox;
}

namespace CloudberryKingdom
{
	class EzText;
}









namespace CloudberryKingdom
{
	class LoadSeedAs : public VerifyBaseMenu
	{
	private:
		class LoadSeedAsOnEnterLambda : public Lambda
		{
		private:
			std::shared_ptr<LoadSeedAs> lsa;
		public:
			LoadSeedAsOnEnterLambda( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	private:
		class LoadSeedAsBackLambda : public Lambda
		{
		private:
			std::shared_ptr<LoadSeedAs> lsa;
		public:
			LoadSeedAsBackLambda( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply();
		};

	private:
		class LoadProxy1 : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<LoadSeedAs> lsa;

		public:
			LoadProxy1( const std::shared_ptr<LoadSeedAs> &lsa );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	public:
		LoadSeedAs( int Control, const std::shared_ptr<PlayerData> &Player );

	private:
		std::shared_ptr<PlayerData> Player;
		std::shared_ptr<GUI_TextBox> TextBox;
		std::shared_ptr<EzText> HeaderText;
	public:
		virtual void Init();

		virtual void Release();

	private:
		void SetPosition();

	public:
		virtual void OnAdd();

	private:
		void Load( const std::shared_ptr<MenuItem> &_item );
	};
}


#endif	//#ifndef LOADSEEDAS
