#include <CloudberryKingdom.h>
#include <Core.h>

int main( int argc, char *argv[] )
{
	CloudberryKingdom game;
	Core core( game );

	return core.Run();
}
