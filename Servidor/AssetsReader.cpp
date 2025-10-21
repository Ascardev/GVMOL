#include <windows.h>
#include <mutex>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <fstream>
#include <array>
#include <filesystem>
#include <limits>

#include "AssetsReader.h"

namespace Game
{
	constexpr const char* AssetsPath = "Data";

	// Keeps our binary open for 60 seconds.
	constexpr unsigned int MaxAllocationTime = 1000 * 60;

	// Our current salt.
	constexpr unsigned int CypherSalt = 0xDEAD0000;

	AssetsReader& AssetsReader::GetInstance()
	{
		static AssetsReader Instance;
		return Instance;
	}

	AssetsReader::AssetsReader() : m_LookupTable(CRC::CRC_32().MakeTable())
	{
	}

	void AssetsReader::Update()
	{
		static unsigned int s_LastCheckTime = 0;

		auto CurrentTime = GetCurrentTime();

		if (s_LastCheckTime < CurrentTime)
		{
			auto ErasePredicate = [CurrentTime](AssetsBinary& Binary)
			{
				if (Binary.AllocationTime + MaxAllocationTime < CurrentTime)
				{
					delete[] Binary.Memory;
					return true;
				}

				return false;
			};

			// Our check time is every 10 seconds to avoid overhead.
			s_LastCheckTime = CurrentTime + 10 * 1000;

			// Erase by predicate.
			m_Cache.erase(std::remove_if(m_Cache.begin(), m_Cache.end(), ErasePredicate), m_Cache.end());
		}
	}

	bool AssetsReader::Get(const char* FilePath, AssetsBinary& Binary)
	{
		std::string FileLower = FilePath;
		std::transform(FileLower.begin(), FileLower.end(), FileLower.begin(), ::tolower);

		auto FileCRC = CRC::Calculate(FileLower.data(), FileLower.size(), m_LookupTable);

		// Check on our cache.
		{
			for (auto& Bin : m_Cache)
			{
				if (Bin.Crc == FileCRC)
				{
					Bin.AllocationTime = GetCurrentTime();

					// Copy to output.
					Binary = Bin;
					return true;
				}
			}
		}

                namespace fs = std::filesystem;
                using namespace std::string_literals;

                // Perform decrypt operation.
                const auto FileID = FileCRC + CypherSalt;

                // Get our file path.
                const auto FilePathResolved = fs::path{ AssetsPath } / (std::to_string(FileID) + ".bin");

                std::error_code ErrorCode{ };
                const auto FileSizeOnDisk = fs::file_size(FilePathResolved, ErrorCode);
                if (ErrorCode || FileSizeOnDisk == 0)
                {
                        return false;
                }

                if (FileSizeOnDisk > static_cast<uintmax_t>(std::numeric_limits<unsigned int>::max()))
                {
                        return false;
                }

                std::ifstream Input(FilePathResolved, std::ios::binary);
                if (!Input)
                {
                        return false;
                }

                const auto FileSize = static_cast<unsigned int>(FileSizeOnDisk);
                std::vector<unsigned char> Buffer(FileSize);

                if (!Input.read(reinterpret_cast<char*>(Buffer.data()), static_cast<std::streamsize>(Buffer.size())))
                {
                        return false;
                }

                std::array<unsigned char, sizeof(FileCRC)> Keys{ };
                const auto* Bytes = reinterpret_cast<unsigned char*>(&FileCRC);
                std::copy(Bytes, Bytes + Keys.size(), Keys.begin());

                auto Memory = std::make_unique<unsigned char[]>(Buffer.size());

                for (size_t i = 0; i < Buffer.size(); ++i)
                {
                        Memory[i] = Buffer[i] ^ Keys[i % Keys.size()];
                }

                Binary.Memory = Memory.release();
                Binary.Size = FileSize;
                Binary.Crc = FileCRC;
                Binary.AllocationTime = GetCurrentTime();

                m_Cache.emplace_back(Binary);

                return true;
        }
}
