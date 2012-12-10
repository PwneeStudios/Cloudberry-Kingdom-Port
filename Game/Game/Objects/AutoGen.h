#ifndef AUTOGEN
#define AUTOGEN

#include <global_header.h>

namespace CloudberryKingdom
{
	class AutoGen_Parameters : public std::enable_shared_from_this<AutoGen_Parameters>
	{
		/// <summary>
		/// Whether to intelligently spread out the period offsets of placed obstacles
		/// </summary>
	public:
		int ChooseOffset( int Period, const std::shared_ptr<Rand> &Rnd );

		int EnforceOffset( int offset, int period );

		/// <summary>
		/// How many objects have been created
		/// </summary>
		int Counter;

		std::shared_ptr<PieceSeedData> PieceSeed;
		Param FillWeight;

		/// <summary>
		/// The difficulty level of the bounding box around the computer.
		/// </summary>
		Param BobWidthLevel;

		/// <summary>
		/// Whether the obstacle should toggle Masochistic mode.
		/// </summary>
		bool Masochistic;

		/// <summary>
		/// Number of possible emit angles.
		/// </summary>
		int NumAngles;

		/// <summary>
		/// Number of possible periods.
		/// </summary>
		int NumPeriods;

		/// <summary>
		/// Number of possible period offsets for each period. If -1 then all offsets are allowed.
		/// </summary>
		int NumOffsets;

		/// <summary>
		/// Whether to do the default Stage 2 PreFill
		/// </summary>
		bool DoStage2Fill;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

		void SetVal( Vector2 &val, Vector2 newval );

		void SetVal( float &val, float newval );

		void SetVal( int &val, int newval );

	private:
		void InitializeInstanceFields();

public:
		AutoGen_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	class AutoGen : public std::enable_shared_from_this<AutoGen>
	{
	public:
		virtual std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

		virtual std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );
		virtual std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

		bool Do_WeightedPreFill_1, Do_PreFill_1, Do_PreFill_2, Do_ActiveFill_1, Do_ActiveFill_2;
		virtual void PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
		virtual void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
		virtual void ActiveFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
		virtual void Cleanup_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
		virtual void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef AUTOGEN
