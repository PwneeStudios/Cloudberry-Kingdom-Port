#ifndef SAVESEEDAS
#define SAVESEEDAS

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
	class SaveSeedAs : public VerifyBaseMenu
	{
	private:
		class SaveProxy : public Lambda_1<MenuItem*>
		{
		private:
			std::shared_ptr<SaveSeedAs> ssa;

		public:
			SaveProxy( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply( const std::shared_ptr<MenuItem> &_item );
		};

	private:
		class OnOkProxy : public Lambda
		{
		private:
			std::shared_ptr<SaveSeedAs> ssa;

		public:
			OnOkProxy( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	private:
		class SaveSeedAsOnEscapeLambda : public Lambda
		{
		private:
			std::shared_ptr<SaveSeedAs> ssa;
		public:
			SaveSeedAsOnEscapeLambda( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};

	private:
		class SaveSeedAsOnEnterLambda : public Lambda
		{
		private:
			std::shared_ptr<SaveSeedAs> ssa;
		public:
			SaveSeedAsOnEnterLambda( const std::shared_ptr<SaveSeedAs> &ssa );

			void Apply();
		};
	public:
		SaveSeedAs( int Control, const std::shared_ptr<PlayerData> &Player );

	private:
		std::shared_ptr<PlayerData> Player;
		std::shared_ptr<GUI_TextBox> TextBox;
		std::shared_ptr<EzText> HeaderText;
	public:
		virtual void Init();

	private:
		void Save( const std::shared_ptr<MenuItem> &_item );

	public:
		virtual void OnReturnTo();

	private:
		void OnOk();

	public:
		virtual void Release();

	private:
		void SetPosition();

	public:
		virtual void OnAdd();

	};
}


#endif	//#ifndef SAVESEEDAS
