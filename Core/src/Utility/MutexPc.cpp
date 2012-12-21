#include <Utility/Mutex.h>

#include <GL/glfw.h>

struct MutexInternal
{
	GLFWmutex M;
};

Mutex::Mutex() :
	internal_( new MutexInternal )
{
	internal_->M = glfwCreateMutex();
}

Mutex::~Mutex()
{
	glfwDestroyMutex( internal_->M );
	delete internal_;
}

void Mutex::Lock()
{
	glfwLockMutex( internal_->M );
}

void Mutex::Unlock()
{
	glfwUnlockMutex( internal_->M );
}
