#ifndef _MASTER_HACK_H_
#define _MASTER_HACK_H_

#include <forward_declarations.h>

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>

#include <Core/Lambdas/LambdaFunc_1.h>

struct GraphicsDevice;
struct PresentationParameters;

namespace CloudberryKingdom
{

	void MenuList_PostConstruct( const boost::shared_ptr<MenuList> &This );

	void Bob_PostConstruct( const boost::shared_ptr<Bob> &This, const boost::shared_ptr<BobPhsx> &type, bool boxesOnly );

	void Awardment_PostConstruct( const boost::shared_ptr<Awardment> &This );

	void Quad_PostConstruct( const boost::shared_ptr<Quad> &This, const boost::shared_ptr<Quad> &quad, bool DeepClone );

	void ObjectClass_PostConstruct( const boost::shared_ptr<ObjectClass> &This, const boost::shared_ptr<QuadDrawer> &Drawer, const boost::shared_ptr<GraphicsDevice> &device, const boost::shared_ptr<PresentationParameters> &pp, int Width, int Height, const boost::shared_ptr<EzEffect> &BaseEffect, const boost::shared_ptr<EzTexture> &BaseTexture );
	void ObjectClass_PostConstruct_3params( const boost::shared_ptr<ObjectClass> &This, const boost::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone );

	boost::shared_ptr<GameData> GameData_Construct( const boost::shared_ptr<GameData> &This );
	boost::shared_ptr<ActionGameData> ActionGameData_Construct( const boost::shared_ptr<ActionGameData> &This );
	boost::shared_ptr<ActionGameData> ActionGameData_Construct( const boost::shared_ptr<ActionGameData> &This, const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );
	boost::shared_ptr<NormalGameData> NormalGameData_Construct( const boost::shared_ptr<NormalGameData> &This, const boost::shared_ptr<LevelSeedData> &LevelSeed, bool MakeInBackground );
	boost::shared_ptr<StringWorldGameData> StringWorldGameData_Construct( const boost::shared_ptr<StringWorldGameData> &This );
	boost::shared_ptr<StringWorldGameData> StringWorldGameData_Construct( const boost::shared_ptr<StringWorldGameData> &This, const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed );
	boost::shared_ptr<ScreenSaver> ScreenSaver_Construct( const boost::shared_ptr<ScreenSaver> &This );
	boost::shared_ptr<StringWorldEndurance> StringWorldEndurance_Construct( const boost::shared_ptr<StringWorldEndurance> &This, const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_LivesLeft> &Gui_LivesLeft, int NextLife );
	boost::shared_ptr<StringWorldTimed> StringWorldTimed_Construct( const boost::shared_ptr<StringWorldTimed> &This, const boost::shared_ptr<LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> > > &GetSeed, const boost::shared_ptr<GUI_Timer> &Timer );
	boost::shared_ptr<TitleGameData> TitleGameData_Construct( const boost::shared_ptr<TitleGameData> &This );
	boost::shared_ptr<TitleGameData_MW> TitleGameData_MW_Construct( const boost::shared_ptr<TitleGameData_MW> &This );
}

#endif
