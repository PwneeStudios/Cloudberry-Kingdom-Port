#ifndef _QUAD_DRAWER_VITA_H_
#define _QUAD_DRAWER_VITA_H_

#include <ForwardDeclarations.h>
#include <memory>
#include <boost/shared_ptr.hpp>

/**
 * Drawer of quads.
 */
class QuadDrawerVita
{

	// Internal bits.
	struct QuadDrawerInternal *internal_;

private:

	/// No copying.
	QuadDrawerVita( const QuadDrawerVita & ) { }

	/// No assignment.
	QuadDrawerVita &operator = ( const QuadDrawerVita & ) { return *this; }

public:

	QuadDrawerVita();
	~QuadDrawerVita();

	/**
	 * @see QuadDrawer::SetEffect()
	 */
	void SetEffect( const boost::shared_ptr<Effect> &effect );

	/**
	 * @see QuadDrawer::GetEffect()
	 */
	boost::shared_ptr<Effect> GetEffect();

	/**
	 * @see QuadDrawer::Draw()
	 */
	void Draw( const SimpleQuad &quad );

	/**
	 * @see QuadDrawer::Flush()
	 */
	void Flush();

};

#endif
