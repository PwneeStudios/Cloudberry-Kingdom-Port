#ifndef NORMALBLOCK__AUTO
#define NORMALBLOCK__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct NormalBlock_Parameters : public AutoGen_Parameters
	{
	
		Param KeepUnused;

		/// <summary>
		/// Whether to make normal blocks or not. Doesn't affect other fill weights.
		/// </summary>
		bool Make;

		bool CustomWeight;

		std::shared_ptr<Wall> MyWall;
		std::shared_ptr<Wall> SetWall( LevelGeometry geometry );

		/// <summary>
		/// Whether to do the standard Stage1Fill. False when certain special fills are set.
		/// </summary>
		bool DoStage1Fill, DoInitialPlats, DoFinalPlats;

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		NormalBlock_Parameters()
		{
			InitializeInstanceFields();
		}
	};

	struct NormalBlock_AutoGen : public AutoGen
	{
	
		static const std::shared_ptr<NormalBlock_AutoGen> instance;
	
		const static std::shared_ptr<NormalBlock_AutoGen> &getInstance();

	
		NormalBlock_AutoGen();

	
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

	
		void MakeWall( const std::shared_ptr<Level> &level );

		std::shared_ptr<NormalBlock_Parameters> GetParams( const std::shared_ptr<Level> &level );

	
		void PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );
		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );
	};
}


#endif	//#ifndef NORMALBLOCK__AUTO
