#include <Input/Mouse.h>

#include <GL/glfw.h>

void Mouse::SetPosition( int x, int y )
{
	glfwSetMousePos( x, y );
}

MouseState Mouse::GetState()
{
	MouseState ms;

	glfwGetMousePos( &ms.X, &ms.Y );
	ms.ScrollWheelValue = glfwGetMouseWheel();

	ms.LeftButton = glfwGetMouseButton( GLFW_MOUSE_BUTTON_LEFT ) == GLFW_PRESS ? ButtonState_Pressed : ButtonState_Released;
	ms.RightButton = glfwGetMouseButton( GLFW_MOUSE_BUTTON_RIGHT ) == GLFW_PRESS ? ButtonState_Pressed : ButtonState_Released;

	return ms;
}