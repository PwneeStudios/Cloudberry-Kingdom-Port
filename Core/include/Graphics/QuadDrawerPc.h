#ifndef _QUAD_DRAWER_PC_H_
#define _QUAD_DRAWER_PC_H_

#include <ForwardDeclarations.h>
#include <memory>

/**
 * Drawer of quads.
 */
class QuadDrawerPc
{

	// Internal bits.
	struct QuadDrawerInternal *internal_;

private:

	/// No copying.
	QuadDrawerPc( const QuadDrawerPc & ) { }

	/// No assignment.
	QuadDrawerPc &operator = ( const QuadDrawerPc & ) { return *this; }

public:

	QuadDrawerPc();
	~QuadDrawerPc();

	/**
	 * @see QuadDrawer::SetEffect()
	 */
	void SetEffect( const std::shared_ptr<Effect> &effect );

	/**
	 * @see QuadDrawer::GetEffect()
	 */
	std::shared_ptr<Effect> GetEffect();

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
