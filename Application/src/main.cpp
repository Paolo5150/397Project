#include "Core/Core.h"
#include "Bullet\btBulletCollisionCommon.h"
#include "Bullet\btBulletDynamicsCommon.h"


void main()
{

	//FreeConsole();
	Core::Instance().Initialize();
	Core::Instance().Run();
	Core::Instance().Shutdown();

	system("pause");
}
