#pragma once
#include "CRC.h"

#include <memory>
#include <string>
#include <vector>

namespace Game
{
        struct AssetsBinary
        {
                std::shared_ptr<std::vector<unsigned char>> Buffer{ };
                unsigned int Size{ 0 };
                unsigned int Crc{ 0 };
                unsigned int AllocationTime{ 0 };

                [[nodiscard]] unsigned char* Data() noexcept
                {
                        return Buffer ? Buffer->data() : nullptr;
                }

                [[nodiscard]] const unsigned char* Data() const noexcept
                {
                        return Buffer ? Buffer->data() : nullptr;
                }
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

