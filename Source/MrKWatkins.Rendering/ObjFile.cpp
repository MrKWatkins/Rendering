#include "stdafx.h"
#include "ObjFile.h"
#include "Triangle.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::IO
{
	ObjFile::ObjFile()
	{
	}

	// TODO: Move to a utility namespace somewhere?
	std::vector<std::string> SplitLine(const std::string &line)
	{
		auto stringStream = std::stringstream(line);
		auto components = std::vector<std::string>();
		std::string component;
		while (getline(stringStream, component, ' '))
		{
			if (!component.empty())
			{
				components.push_back(component);
			}
		}
		return components;
	}

	// From https://isocpp.org/wiki/faq/misc-technical-issues#convert-string-to-num.
	double ToDouble(const std::string& s)
	{
		std::istringstream i(s);
		double x;
		if (!(i >> x))
		{
			throw std::runtime_error("Could not convert " + s + " to a double.");
		}
		return x;
	}

	bool TryParseVertex(const std::vector<std::string>& components, std::vector<Point>& vertices)
	{
		if (components[0] != "v")
		{
			return false;
		}

		if (components.size() < 4)
		{
			throw std::runtime_error("Vertex line does not have enough components.");
		}

		// TODO: Remove the temporary scaling.
		auto point = Point(ToDouble(components[1]) / 100 + 0.5, ToDouble(components[2]) / 100 + 0.5, ToDouble(components[3]) / 100 + 2.0);
		vertices.push_back(point);

		return true;
	}

	bool TryParseFace(const std::vector<std::string>& components, const std::vector<Point>& vertices, std::vector<Triangle>& triangles)
	{
		if (components[0] != "f")
		{
			return false;
		}

		if (components.size() != 4)
		{
			throw std::runtime_error("Only triangular faces are supported.");
		}

		auto corner1 = vertices[atoi(components[1].c_str()) - 1];
		auto corner2 = vertices[atoi(components[2].c_str()) - 1];
		auto corner3 = vertices[atoi(components[3].c_str()) - 1];

		triangles.push_back(Triangle(corner1, corner2, corner3));

		return true;
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

		std::vector<Point> vertices;

		while (getline(file, line))
		{
			if (line.empty() || line[0] == '#')
			{
				continue;
			}

			auto components = SplitLine(line);
			if (components.size() < 2)
			{
				continue;
			}

			if (TryParseVertex(components, vertices))
			{
				continue;
			}

			TryParseFace(components, vertices, objFile.triangles);
		}

		file.close();

		return objFile;
	}
}