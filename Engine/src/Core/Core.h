#pragma once
class Core
{
public:
	static Core& Instance()
	{
		std::cout << "asd";
	}
	void Initialize();
	void Run();
	void Shutdown();


	~Core();
	bool IsRunning();
	//Window& GetWindow();
	//Application& GetRunningApplication();

private:


	Core();



	bool m_isRunning;

	Core& operator=(Core& other) = delete;
	Core(Core& other) = delete;



};