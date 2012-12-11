#ifndef FIRESNAKE__AUTO
#define FIRESNAKE__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Firesnake_Parameters : public AutoGen_Parameters
	{
	
		struct _Special
		{
		};
	
		Param Step, Period;
		VectorParam RadiiX, RadiiY;

		bool Make;

		_Special Special;

		std::vector<std::vector<unsigned long long> > Snakes;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Firesnake_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct Firesnake_AutoGen : public AutoGen
	{
	
		static std::shared_ptr<Firesnake_AutoGen> instance;
	
		const static std::shared_ptr<Firesnake_AutoGen> &getInstance();

	
		Firesnake_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		std::shared_ptr<Firesnake_Parameters> GetParams( const std::shared_ptr<Level> &level );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void CreateLine( const std::shared_ptr<Level> &level, Vector2 pos );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FIRESNAKE__AUTO
