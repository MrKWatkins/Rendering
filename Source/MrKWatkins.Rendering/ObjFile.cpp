#include "stdafx.h"
#include "ObjFile.h"
#include "Triangle.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering
{
	ObjFile::ObjFile()
	{
	}

	ObjFile ObjFile::Load(const std::wstring& path)
	{
		ObjFile objFile;

		std::string line;
		std::ifstream file(path);
		if (!file.is_open())
		{
			// TODO: Include path in exception method - requires converting a wstring to string.
			throw std::invalid_argument("File not found.");
		}

		while (getline(file, line))
		{
		}

		file.close();

		return objFile;
	}
}
