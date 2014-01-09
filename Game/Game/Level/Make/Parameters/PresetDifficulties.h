#ifndef PRESETDIFFICULTIES
#define PRESETDIFFICULTIES

namespace CloudberryKingdom
{
	struct Upgrades;
}


namespace CloudberryKingdom
{
	struct PresetUpgrades
	{
	
		static boost::shared_ptr<Upgrades> GetUpgrade1();

		static boost::shared_ptr<Upgrades> GetUpgrade2();

		static boost::shared_ptr<Upgrades> GetUpgrade3();

		static boost::shared_ptr<Upgrades> GetUpgrade4();

		static boost::shared_ptr<Upgrades> GetUpgrade5();

		static boost::shared_ptr<Upgrades> GetUpgrade6();

		static boost::shared_ptr<Upgrades> GetUpgrade( int Difficulty );
	};
}


#endif	//#ifndef PRESETDIFFICULTIES
