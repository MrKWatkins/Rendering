#pragma once
#include "Triangle.h"

using namespace MrKWatkins::Rendering::Geometry;

namespace MrKWatkins::Rendering::IO
{
	class Vertex
	{
		friend class ObjFile;

		Vertex(double x, double y, double z, double w);
		friend Vertex::Vertex(double x, double y, double z, double w);
	public:
		const double X;
		const double Y;
		const double Z;
		const double W;

		Point ToPoint() const;
	};

	class VertexNormal
	{
		friend class ObjFile;

		VertexNormal(double x, double y, double z);
		friend VertexNormal::VertexNormal(double x, double y, double z);
	public:
		const double X;
		const double Y;
		const double Z;

		Vector ToVector() const;
	};

	class FaceVertex
	{
		friend class ObjFile;

		FaceVertex(unsigned int vertexNumber, std::optional<unsigned int> vertexTextureNumber, std::optional<unsigned int> vertexNormalNumber);
		friend FaceVertex::FaceVertex(unsigned int vertexNumber, std::optional<unsigned int> vertexTextureNumber, std::optional<unsigned int> vertexNormalNumber);
	public:
		const unsigned int VertexNumber;
		const std::optional<unsigned int> VertexTextureNumber;
		const std::optional<unsigned int> VertexNormalNumber;
	};

	class Face
	{
		friend class ObjFile;

		explicit Face(const std::vector<FaceVertex>& vertices);
		friend Face::Face(const std::vector<FaceVertex>& vertices);
	public:
		const std::vector<FaceVertex> Vertices;
	};

	// TODO: Probably shouldn't be copyable.
	class ObjFile
	{
		mutable std::vector<Vertex> vertices;
		mutable std::vector<VertexNormal> vertexNormals;
		mutable std::vector<Face> faces;

		ObjFile();

		bool TryParseVertex(const std::vector<std::string>& components) const;
		bool TryParseVertexNormal(const std::vector<std::string>& components) const;
		bool TryParseFace(const std::vector<std::string>& components) const;
	public:

		const std::vector<Vertex>& Vertices() const noexcept { return vertices; }
		const std::vector<VertexNormal>& VertexNormals() const noexcept { return vertexNormals; }
		const std::vector<Face>& Faces() const noexcept { return faces; }

		static ObjFile Load(const std::wstring& path);

		std::vector<Triangle> ToTriangles() const;
	};
}
