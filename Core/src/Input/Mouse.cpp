#include <Input/Mouse.h>

#if defined( CAFE ) || defined( PS3 )
#else
	#include <GL/glfw.h>
#endif

void Mouse::SetPosition( int x, int y )
{
#if defined( CAFE ) || defined( PS3 )
#else
	glfwSetMousePos( x, y );
#endif
}

MouseState Mouse::GetState()
{
	MouseState ms;

#if defined( CAFE ) || defined( PS3 )
#else
	glfwGetMousePos( &ms.X, &ms.Y );
	ms.ScrollWheelValue = glfwGetMouseWheel();

	ms.LeftButton = glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS ? ButtonState_Pressed : ButtonState_Released;
	ms.RightButton = glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS ? ButtonState_Pressed : ButtonState_Released;
#endif

	return ms;
}