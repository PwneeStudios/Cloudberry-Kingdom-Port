#ifndef _QUAD_DRAWER_H_
#define _QUAD_DRAWER_H_

#include <ForwardDeclarations.h>
#include <memory>
#include <boost/shared_ptr.hpp>

// Pick the implementation we want to use.
#ifdef CAFE
	#include "QuadDrawerWiiU.h"
#elif PS3
	#include "QuadDrawerPS3.h"
#elif VITA
	#include "QuadDrawerVita.h"
#else
	#include "QuadDrawerPc.h"
#endif

/**
 * Drawer of quads.
 */
class QuadDrawer
{

	/// IMPL from the PIMPL.
#ifdef CAFE
	QuadDrawerWiiU impl_;
#elif PS3
	QuadDrawerPS3 impl_;
#elif VITA
	QuadDrawerVita impl_;
#else
	QuadDrawerPc impl_;
#endif

private:

	/// No copying.
	QuadDrawer( const QuadDrawer & ) { }

	/// No assignment.
	QuadDrawer &operator = ( const QuadDrawer & ) { return *this; }

public:

	QuadDrawer() { }
	virtual ~QuadDrawer() { }

	/// Set current effect.
	/**
	 * @param effect New effect to use.
	 */
	void SetEffect( const boost::shared_ptr<Effect> &effect )
	{
		impl_.SetEffect( effect );
	}

	/// Get current effect.
	/**
	 * @return Current effect in use by quad drawer.
	 */
	boost::shared_ptr<Effect> GetEffect()
	{
		return impl_.GetEffect();
	}

	/// Draw a simple quad.
	/**
	 * @param quad Quad to draw.
	 */
	void Draw( const SimpleQuad &quad )
	{
		impl_.Draw( quad );
	}

	/// Flush any quads that need drawing.
	void Flush()
	{
		impl_.Flush();
	}

};



#endif
