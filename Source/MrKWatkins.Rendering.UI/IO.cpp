#include "stdafx.h"
#include "IO.h"

namespace MrKWatkins::Rendering::UI::IO
{
	std::wstring GetPathToExecutable()
	{
		// Taken from http://stackoverflow.com/a/33613252/320508.
		std::vector<wchar_t> buffer;
		DWORD copied;
		do
		{
			buffer.resize(buffer.size() + MAX_PATH);
			copied = GetModuleFileNameW(nullptr, &buffer.at(0), static_cast<DWORD>(buffer.size()));
		} while (copied >= buffer.size());

		buffer.resize(copied);

		return std::wstring(buffer.begin(), buffer.end());
	}

	std::wstring GetPathToProjectRoot()
	{
		auto exePath = GetPathToExecutable();
		auto sourceIndex = exePath.rfind(L"\\Source");
		if (sourceIndex == -1)
		{
			throw std::runtime_error("Executable is not running from within the Source folder.");
		}

		return exePath.substr(0, sourceIndex);
	}

	std::wstring ResolveModelPath(const std::wstring& file)
	{
		return GetPathToProjectRoot() + L"\\Models\\" + file;
	}
}