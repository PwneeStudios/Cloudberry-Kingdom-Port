#ifndef UPGRADES
#define UPGRADES

#include <global_header.h>

namespace CloudberryKingdom
{
	// Stores the level of each obstacles
	// CalcGenData translates this into actual parameters
	struct Upgrades : public boost::enable_shared_from_this<Upgrades>
	{

	
		static void InitializeStatics();

	
		std::vector<float> UpgradeLevels;

		Upgrades();

		Upgrades( const boost::shared_ptr<Upgrades> &u );

	
		void Initialize();


	
		void CopyFrom( const boost::shared_ptr<Upgrades> &u );

		/// <summary>
		/// Access the specified upgrade level
		/// </summary>
		/// <param name="upgrade">The specified upgrade type</param>
		float &Get( int upgrade );

		/// <summary>
		/// Set every upgrade to level 0
		/// </summary>
		void Zero();

		static int MaxBobWidth;
		void CalcGenData( const boost::shared_ptr<LevelGenData> &GenData, const boost::shared_ptr<StyleData> &Style );
	};
}


#endif	//#ifndef UPGRADES
