#ifndef FIRESNAKE__AUTO
#define FIRESNAKE__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	class Firesnake_Parameters : public AutoGen_Parameters
	{
	public:
		class _Special
		{
		};
	public:
		Param Step, Period;
		VectorParam RadiiX, RadiiY;

		bool Make;

		_Special Special;

		std::vector<std::vector<unsigned long long> > Snakes;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		Firesnake_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class Firesnake_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<Firesnake_AutoGen> instance;
	public:
		const static std::shared_ptr<Firesnake_AutoGen> &getInstance();

	private:
		Firesnake_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		std::shared_ptr<Firesnake_Parameters> GetParams( const std::shared_ptr<Level> &level );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void CreateLine( const std::shared_ptr<Level> &level, Vector2 pos );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef FIRESNAKE__AUTO
