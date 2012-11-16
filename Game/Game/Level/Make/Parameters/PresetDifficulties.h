#ifndef PRESETDIFFICULTIES
#define PRESETDIFFICULTIES

namespace CloudberryKingdom
{
	class Upgrades;
}


namespace CloudberryKingdom
{
	class PresetUpgrades
	{
	public:
		static std::shared_ptr<Upgrades> GetUpgrade1();

		static std::shared_ptr<Upgrades> GetUpgrade2();

		static std::shared_ptr<Upgrades> GetUpgrade3();

		static std::shared_ptr<Upgrades> GetUpgrade4();

		static std::shared_ptr<Upgrades> GetUpgrade5();

		static std::shared_ptr<Upgrades> GetUpgrade6();

		static std::shared_ptr<Upgrades> GetUpgrade( int Difficulty );
	};
}


#endif	//#ifndef PRESETDIFFICULTIES
