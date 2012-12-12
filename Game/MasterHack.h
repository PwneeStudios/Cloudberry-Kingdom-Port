#ifndef _MASTER_HACK_H_
#define _MASTER_HACK_H_

#include <forward_declarations.h>

#include <memory>

struct GraphicsDevice;
struct PresentationParameters;

namespace CloudberryKingdom
{

	void Awardment_PostConstruct( const std::shared_ptr<Awardment> &This );

	void Quad_PostConstruct( const std::shared_ptr<Quad> &This, const std::shared_ptr<Quad> &quad, bool DeepClone );

	void ObjectClass_PostConstruct( const std::shared_ptr<ObjectClass> &This, const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture );
	void ObjectClass_PostConstruct_3params( const std::shared_ptr<ObjectClass> &This, const std::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone );

}

#endif
