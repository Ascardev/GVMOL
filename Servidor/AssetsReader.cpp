#include <windows.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cstring>
#include <fstream>
#include <limits>
#include <memory>
#include <string>
#include <utility>
#include <vector>

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

                const auto CurrentTime = GetCurrentTime();

                if (s_LastCheckTime < CurrentTime)
                {
                        auto ErasePredicate = [CurrentTime](const AssetsBinary& Binary)
                        {
                                return (Binary.AllocationTime + MaxAllocationTime) < CurrentTime;
                        };

                        // Our check time is every 10 seconds to avoid overhead.
                        s_LastCheckTime = CurrentTime + 10 * 1000;

                        // Erase by predicate.
                        const auto FirstExpired = std::remove_if(m_Cache.begin(), m_Cache.end(), ErasePredicate);
                        m_Cache.erase(FirstExpired, m_Cache.end());
                }
        }

	bool AssetsReader::Get(const char* FilePath, AssetsBinary& Binary)
	{
                if (FilePath == nullptr)
                {
                        return false;
                }

                const auto Now = GetCurrentTime();

                std::string FileLower = FilePath;
                std::transform(FileLower.begin(), FileLower.end(), FileLower.begin(), [](unsigned char Ch) -> char
                {
                        return static_cast<char>(std::tolower(Ch));
                });

		auto FileCRC = CRC::Calculate(FileLower.data(), FileLower.size(), m_LookupTable);

                // Check on our cache.
                for (auto& Bin : m_Cache)
                {
                        if (Bin.Crc == FileCRC)
                        {
                                Bin.AllocationTime = Now;
                                Bin.Size = static_cast<unsigned int>(Bin.Buffer ? Bin.Buffer->size() : 0);

                                Binary = Bin;
                                Binary.Size = static_cast<unsigned int>(Binary.Buffer ? Binary.Buffer->size() : 0);
                                return true;
                        }
                }

                // Perform decrypt operation.
                const auto FileID = FileCRC + CypherSalt;

                // Resolve our legacy on-disk location.
                const std::string FilePathResolved = std::string(AssetsPath) + "\\" + std::to_string(FileID) + ".bin";

                std::ifstream Input(FilePathResolved, std::ios::binary | std::ios::ate);
                if (!Input)
                {
                        return false;
                }

                const auto FileSizeOnDisk = static_cast<std::streamoff>(Input.tellg());
                if (FileSizeOnDisk <= 0)
                {
                        return false;
                }

                Input.seekg(0, std::ios::beg);

                if (FileSizeOnDisk > static_cast<std::streamoff>(std::numeric_limits<unsigned int>::max()))
                {
                        return false;
                }

                const auto FileSize = static_cast<unsigned int>(FileSizeOnDisk);
                auto Memory = std::make_shared<std::vector<unsigned char>>(FileSize);

                if (!Input.read(reinterpret_cast<char*>(Memory->data()), static_cast<std::streamsize>(Memory->size())))
                {
                        return false;
                }

                std::array<unsigned char, sizeof(FileCRC)> Keys{ };
                std::memcpy(Keys.data(), &FileCRC, Keys.size());

                for (size_t i = 0; i < Memory->size(); ++i)
                {
                        (*Memory)[i] ^= Keys[i % Keys.size()];
                }

                AssetsBinary Result;
                Result.Buffer = std::move(Memory);
                Result.Size = FileSize;
                Result.Crc = FileCRC;
                Result.AllocationTime = Now;

                Binary = Result;
                Binary.Size = static_cast<unsigned int>(Binary.Buffer ? Binary.Buffer->size() : 0);
                m_Cache.emplace_back(std::move(Result));

                return true;
        }
}
