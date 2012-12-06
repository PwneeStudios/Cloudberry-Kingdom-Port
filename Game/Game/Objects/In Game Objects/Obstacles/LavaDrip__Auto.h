#ifndef LAVADRIP__AUTO
#define LAVADRIP__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	class LavaDrip_Parameters : public AutoGen_Parameters
	{
	public:
		float LavaDripStepCutoff;
		Param LavaDripStep, Speed;
		VectorParam Length;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		LavaDrip_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class LavaDrip_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<LavaDrip_AutoGen> instance;
	public:
		const static std::shared_ptr<LavaDrip_AutoGen> &getInstance();

	public:
		LavaDrip_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef LAVADRIP__AUTO
