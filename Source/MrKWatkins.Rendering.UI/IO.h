#pragma once

namespace MrKWatkins::Rendering::UI::IO
{
	std::wstring GetPathToExecutable();

	std::wstring GetPathToProjectRoot();

	std::wstring ResolveModelPath(const std::wstring& file);
}