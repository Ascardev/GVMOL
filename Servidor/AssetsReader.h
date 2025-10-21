#pragma once
#include "CRC.h"
#include <string>
#include <vector>

namespace Game
{
	struct AssetsBinary
	{
		unsigned char* Memory;
		unsigned int Size;
		unsigned int Crc;
		unsigned int AllocationTime;
	};

	class AssetsReader
	{
	public:
		AssetsReader(const AssetsReader&) = delete;
		AssetsReader& operator=(const AssetsReader&) = delete;
		~AssetsReader() = default;
		static AssetsReader& GetInstance();

	private:
		AssetsReader();

	public:
		void Update();
		bool Get(const char* FilePath, AssetsBinary& Binary);

	private:
		CRC::Table<uint32_t, (uint16_t)32U> m_LookupTable;
		std::vector<AssetsBinary> m_Cache;
	};
}
