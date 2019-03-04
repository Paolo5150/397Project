#include "Core/Core.h"


void main()
{
	Logger::Initialize(); // Initialize before anything so it can be used immediately.
	Core::Instance().Initialize();
	Core::Instance().Run();
	Core::Instance().Shutdown();


}
