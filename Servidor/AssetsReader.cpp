#include <windows.h>
#include <mutex>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <fstream>

#include "AssetsReader.h"

namespace Game
{
	constexpr const char* AssetsPath = "Data";

	// Keeps our binary open for 60 seconds.
	constexpr unsigned int MaxAllocationTime = 1000 * 60;

	// Our current salt.
	constexpr unsigned int CypherSalt = 0xDEAD0000;

	std::ifstream::pos_type LegacyFileSize(const char* FileName)
	{
		std::ifstream in(FileName, std::ifstream::ate | std::ifstream::binary);
		return in.tellg();
	}

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

		using namespace std::string_literals;

		// Perform decrypt operation.
		auto FileID = FileCRC + CypherSalt;

		// Get our file path.
		auto ErrorCode = std::error_code{ };
		auto FileBin = AssetsPath + "\\"s + std::to_string(FileID) + ".bin"s;
		auto FileSize = static_cast<unsigned int>(LegacyFileSize(FileBin.c_str()));

		if (!ErrorCode)
		{
			// Open it.
			FILE* File = nullptr;
			if (fopen_s(&File, FileBin.c_str(), "rb") == 0)
			{
				unsigned char* Memory = new unsigned char[FileSize];

				// Read from disk.
				fread_s(Memory, FileSize, sizeof(unsigned char), FileSize, File);
				fclose(File);

				// Gets our keys.
				unsigned char Keys[sizeof(FileCRC)] = { 0 };

				// Reinterpret and set.
				auto* Bytes = reinterpret_cast<unsigned char*>(&FileCRC);
				Keys[0] = Bytes[0];
				Keys[1] = Bytes[1];
				Keys[2] = Bytes[2];
				Keys[3] = Bytes[3];

				// Construct our AssetsBinary.
				Binary.Memory = Memory;

				// Basic xor decryption.
				for (size_t i = 0; i < FileSize; i++)
				{
					Binary.Memory[i] = Memory[i];
					Binary.Memory[i] ^= Keys[i % _countof(Keys)];
				}

				// Copy informations.
				Binary.Size = FileSize;
				Binary.Crc = FileCRC;
				Binary.AllocationTime = GetCurrentTime();

				// Insert to our cache.
				m_Cache.emplace_back(Binary);

				// Return success.
				return true;
			}
		}

		return false;
	}
}