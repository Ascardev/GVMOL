#include <string>
#include <fstream>
#include "smType.h"

smFileLoader::smFileLoader(const std::string& FilePath)
{
	std::ifstream File(FilePath, std::ifstream::ate | std::ifstream::binary);

	m_FileName = FilePath;
	m_FileSize = 0;
	m_FileBuffer = nullptr;
	m_Offset = 0;
	m_ManageMemory = true;

	if (File.is_open())
	{
		m_FileSize = static_cast<int>(File.tellg());
		File.seekg(0, std::ifstream::beg);
		m_FileBuffer = new char[m_FileSize];
		File.read(m_FileBuffer, m_FileSize);
		File.close();
	}
	else
	{
		char Message[256] = { 0 };
		sprintf_s(Message, "[Client] : Could not open file( %s ).", FilePath.c_str());
		throw std::runtime_error(Message);
	}
}

smFileLoader::smFileLoader(char* Buffer, int Size)
{
	m_FileName = "Custom from Assets";
	m_FileSize = Size;
	m_FileBuffer = Buffer;
	m_Offset = 0;
	m_ManageMemory = false;
}

smFileLoader::~smFileLoader()
{
	if (m_FileBuffer && m_ManageMemory)
		delete[] m_FileBuffer;
}

void smFileLoader::Seek(int Position)
{
	m_Offset = Position;
}

void smFileLoader::Read(void* Buffer, int TypeSize, int Count)
{
	if (m_Offset + (TypeSize * Count) > m_FileSize)
	{
		char Message[256] = { 0 };
		sprintf_s(Message, "[Client] : Could not read %d bytes of file( %s ).", TypeSize * Count, m_FileName.c_str());
		throw std::runtime_error(Message);
	}

	memcpy(Buffer, &m_FileBuffer[m_Offset], TypeSize * Count);
	m_Offset += TypeSize * Count;
}

char* smFileLoader::GetBuffer()
{
	return m_FileBuffer;
}

int smFileLoader::GetSize()
{
	return m_FileSize;
}