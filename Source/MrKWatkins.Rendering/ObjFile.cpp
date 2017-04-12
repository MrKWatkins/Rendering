#include "stdafx.h"
#include "ObjFile.h"
#include "Triangle.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::IO
{
	Vertex::Vertex(double x, double y, double z, double w) : X{ x }, Y{ y }, Z{ z }, W{ w }
	{
	}

	Point Vertex::ToPoint() const
	{
		return Point(X, Y, Z);
	}

	VertexNormal::VertexNormal(double x, double y, double z) : X{ x }, Y{ y }, Z{ z }
	{
	}

	Vector VertexNormal::ToVector() const
	{
		return Vector(X, Y, Z).Normalize();
	}

	FaceVertex::FaceVertex(unsigned int vertexNumber, std::optional<unsigned int> vertexTextureNumber, std::optional<unsigned int> vertexNormalNumber)
		: VertexNumber { vertexNumber }, VertexTextureNumber{ vertexTextureNumber }, VertexNormalNumber{ vertexNormalNumber }
	{
	}

	Face::Face(const std::vector<FaceVertex>& vertices) : Vertices{ vertices }
	{
	}

	ObjFile::ObjFile()
	{
	}
	
	// TODO: Move to a utility namespace somewhere?
	std::vector<std::string> Split(const std::string &line, char separator = ' ', bool excludeEmpty = true)
	{
		auto stringStream = std::stringstream(line);
		auto components = std::vector<std::string>();
		std::string component;
		while (getline(stringStream, component, separator))
		{
			if (!excludeEmpty || !component.empty())
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
	
	unsigned int ToUnsignedInt(const std::string& s)
	{
		return static_cast<unsigned int>(atoi(s.c_str()));
	}

	bool ObjFile::TryParseVertex(const std::vector<std::string>& components) const
	{
		if (components[0] != "v")
		{
			return false;
		}

		if (components.size() < 4)
		{
			throw std::runtime_error("Vertex line does not have enough components.");
		}

		if (components.size() > 6)
		{
			throw std::runtime_error("Vertex line has too many components.");
		}

		auto x = ToDouble(components[1]);
		auto y = ToDouble(components[2]);
		auto z = ToDouble(components[3]);
		auto w = components.size() == 6 ? ToDouble(components[4]) : 1.0;

		vertices.push_back(Vertex(x, y, z, w));

		return true;
	}

	bool ObjFile::TryParseVertexNormal(const std::vector<std::string>& components) const
	{
		if (components[0] != "vn")
		{
			return false;
		}

		if (components.size() != 4)
		{
			throw std::runtime_error("Vertex normal line does not 4 components.");
		}

		auto x = ToDouble(components[1]);
		auto y = ToDouble(components[2]);
		auto z = ToDouble(components[3]);

		vertexNormals.push_back(VertexNormal(x, y, z));

		return true;
	}

	bool ObjFile::TryParseFace(const std::vector<std::string>& components) const
	{
		if (components[0] != "f")
		{
			return false;
		}

		std::vector<FaceVertex> faceVertices;
		for (auto f = 1; f < components.size(); f++)
		{
			auto vertexComponents = Split(components[f], '/', false);
			auto vertexNumber = ToUnsignedInt(vertexComponents[0]);
			if (vertexComponents.size() == 1)
			{
				faceVertices.push_back(FaceVertex(vertexNumber, std::optional<unsigned int>(), std::optional<unsigned int>()));
			}
			else if (vertexComponents.size() == 2)
			{
				faceVertices.push_back(FaceVertex(vertexNumber, ToUnsignedInt(vertexComponents[1]), std::optional<unsigned int>()));
			}
			else if (vertexComponents.size() == 3)
			{
				faceVertices.push_back(FaceVertex(vertexNumber, vertexComponents[1] == "" ? std::optional<unsigned int>() : ToUnsignedInt(vertexComponents[1]), ToUnsignedInt(vertexComponents[2])));
			}
		}

		faces.push_back(Face(faceVertices));

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

			auto components = Split(line);
			if (components.size() < 2)
			{
				continue;
			}

			if (objFile.TryParseVertex(components))
			{
				continue;
			}

			if (objFile.TryParseVertexNormal(components))
			{
				continue;
			}

			objFile.TryParseFace(components);
		}

		file.close();

		return objFile;
	}

	std::vector<Triangle> ObjFile::ToTriangles() const
	{
		std::vector<Triangle> triangles;
		for (auto& face : faces)
		{
			if (face.Vertices.size() != 3)
			{
				continue;
			}

			auto vertex0 = vertices[face.Vertices[0].VertexNumber - 1].ToPoint();
			auto vertex1 = vertices[face.Vertices[1].VertexNumber - 1].ToPoint();
			auto vertex2 = vertices[face.Vertices[2].VertexNumber - 1].ToPoint();

			if (!face.Vertices[0].VertexNormalNumber.has_value())
			{
				triangles.push_back(Triangle(vertex0, vertex1, vertex2));
				continue;
			}

			triangles.push_back(Triangle(
				vertex0, vertexNormals[face.Vertices[0].VertexNormalNumber.value() - 1].ToVector(),
				vertex1, vertexNormals[face.Vertices[1].VertexNormalNumber.value() - 1].ToVector(),
				vertex2, vertexNormals[face.Vertices[2].VertexNormalNumber.value() - 1].ToVector()));
		}

		return triangles;
	}
}
