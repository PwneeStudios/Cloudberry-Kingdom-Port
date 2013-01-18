#ifndef _QUAD_DRAWER_PS3_H_
#define _QUAD_DRAWER_PS3_H_

#include <ForwardDeclarations.h>
#include <memory>
#include <boost/shared_ptr.hpp>

/**
 * Drawer of quads.
 */
class QuadDrawerPS3
{

	// Internal bits.
	struct QuadDrawerInternal *internal_;

private:

	/// No copying.
	QuadDrawerPS3( const QuadDrawerPS3 & ) { }

	/// No assignment.
	QuadDrawerPS3 &operator = ( const QuadDrawerPS3 & ) { return *this; }

public:

	QuadDrawerPS3();
	~QuadDrawerPS3();

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
