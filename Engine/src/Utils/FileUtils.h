#pragma once
#include "..\Core\Logger.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <filesystem>
#include <windows.h>

class FileUtils
	{
	public:
		static bool IsFileThere(std::string filePath);
		static std::string ReadFileToString(std::string filePath);
		static std::string GetCurrentDir();
		static void PrintFiles(std::string folder);
		static std::string GetFileNameFromAbsolutePath(std::string path);
		static std::string GetLastFolderNameFromAbsolutePath(std::string path);
};


