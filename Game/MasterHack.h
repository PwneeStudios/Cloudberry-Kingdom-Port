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

	std::shared_ptr<GameData> GameData_Construct( const std::shared_ptr<GameData> &This );
	std::shared_ptr<ActionGameData> ActionGameData_Construct( const std::shared_ptr<ActionGameData> &This );
	std::shared_ptr<ActionGameData> ActionGameData_Construct( const std::shared_ptr<ActionGameData> &This, const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );
	std::shared_ptr<NormalGameData> NormalGameData_Construct( const std::shared_ptr<NormalGameData> &This, const std::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );
	std::shared_ptr<StringWorldGameData> StringWorldGameData_Construct( const std::shared_ptr<StringWorldGameData> &This );
	std::shared_ptr<StringWorldGameData> StringWorldGameData_Construct( const std::shared_ptr<StringWorldGameData> &This, const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed );
	std::shared_ptr<ScreenSaver> ScreenSaver_Construct( const std::shared_ptr<ScreenSaver> &This );
	std::shared_ptr<StringWorldEndurance> StringWorldEndurance_Construct( const std::shared_ptr<StringWorldEndurance> &This, const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife );
	std::shared_ptr<StringWorldTimed> StringWorldTimed_Construct( const std::shared_ptr<StringWorldTimed> &This, const std::shared_ptr<LambdaFunc_1<int, std::shared_ptr<LevelSeedData> > > &GetSeed, const std::shared_ptr<GUI_Timer> &Timer );
	std::shared_ptr<TitleGameData> TitleGameData_Construct( const std::shared_ptr<TitleGameData> &This );
	std::shared_ptr<TitleGameData_MW> TitleGameData_MW_Construct( const std::shared_ptr<TitleGameData_MW> &This );
}

#endif
