#include "Core/Core.h"


void main()
{

	Core::Instance().Initialize();
	Core::Instance().Run();
	Core::Instance().Shutdown();


}
