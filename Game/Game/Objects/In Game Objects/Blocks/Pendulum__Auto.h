#ifndef PENDULUM__AUTO
#define PENDULUM__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	class Pendulum_Parameters : public AutoGen_Parameters
	{
	public:
		enum MotionType
		{
			MotionType_VERTICAL,
			MotionType_HORIZONTAL,
			MotionType_AA,
			MotionType_CROSS,
			MotionType_STRAIGHT,
			MotionType_CIRLCES,
			MotionType_ALL
		};
	public:
		Param Period, MaxAngle, KeepUnused, Size;

		std::vector<int> MotionLevel;
		MotionType Motion;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();

public:
		Pendulum_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class Pendulum_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<Pendulum_AutoGen> instance;
	public:
		const static std::shared_ptr<Pendulum_AutoGen> &getInstance();

	public:
		Pendulum_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef PENDULUM__AUTO
