#ifndef _MASTER_HACK_H_
#define _MASTER_HACK_H_

#include <forward_declarations.h>

#include <memory>

#include <Core/Lambdas/LambdaFunc_1.h>

struct GraphicsDevice;
struct PresentationParameters;

namespace CloudberryKingdom
{

	void Bob_PostConstruct( const std::shared_ptr<Bob> &This, const std::shared_ptr<BobPhsx> &type, bool boxesOnly );

	void Awardment_PostConstruct( const std::shared_ptr<Awardment> &This );

	void Quad_PostConstruct( const std::shared_ptr<Quad> &This, const std::shared_ptr<Quad> &quad, bool DeepClone );

	void ObjectClass_PostConstruct( const std::shared_ptr<ObjectClass> &This, const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture );
	void ObjectClass_PostConstruct_3params( const std::shared_ptr<ObjectClass> &This, const std::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone );

	void GameData_Construct( const std::shared_ptr<GameData> &This );
	void ActionGameData_Construct( const std::shared_ptr<ActionGameData> &This );
	void ActionGameData_Construct( const std::shared_ptr<ActionGameData> &This, const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );
	void NormalGameData_Construct( const std::shared_ptr<NormalGameData> &This, const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );
	void StringWorldGameData_Construct( const std::shared_ptr<StringWorldGameData> &This );
	void StringWorldGameData_Construct( const std::shared_ptr<StringWorldGameData> &This, const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed );
	void ScreenSaver_Construct( const std::shared_ptr<ScreenSaver> &This );
	void StringWorldEndurance_Construct( const std::shared_ptr<StringWorldEndurance> &This, const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife );
	void StringWorldTimed_Construct( const std::shared_ptr<StringWorldTimed> &This, const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_Timer> &Timer );
	void TitleGameData_Construct( const std::shared_ptr<TitleGameData> &This );
	void TitleGameData_MW_Construct( const std::shared_ptr<TitleGameData_MW> &This );
}

#endif
