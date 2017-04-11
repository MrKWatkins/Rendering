#include "stdafx.h"
#include "Object.h"

namespace MrKWatkins::Rendering::Scene
{
	static int nextId;

	Object::Object(std::unique_ptr<Geometry::Solid>&& solid, const std::shared_ptr<Textures::Texture> texture) : id{ nextId++ }, solid{ move(solid) }, texture{ texture }
	{
	}

	bool Object::operator==(const Object& other) const
	{
		return id == other.id;
	}

	bool Object::operator!=(const Object& other) const
	{
		return id != other.id;
	}

	Material Object::GetMaterialAtPoint(const Point& point) const
	{
		return texture->GetMaterialAtPoint(point);
	}
}
