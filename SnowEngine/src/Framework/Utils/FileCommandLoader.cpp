#include "Framework/Utils/FileCommandLoader.h"
#include "Framework/Core.h"
#include "Graphics/Color.h"
#include "Math/Vector2D.h"
#include <fstream>
#include <iostream>

void FileCommandLoader::AddCommand(const Command& command)
{
	m_Commands.push_back(command);
}

bool FileCommandLoader::LoadFile(const std::string & filePath)
{
	std::ifstream inFile;
	inFile.open(filePath);
	std::string line = "";

	if (!inFile.is_open())
	{
		snw::LOG("FILE CAN NOT OPPENED AT {}", filePath);

		return false;
	}

	while (!inFile.eof())
	{
		std::getline(inFile, line);
		size_t commandPos = std::string::npos;

		if ((commandPos = line.find(":") != std::string::npos))
		{
			size_t dilimitPos = line.find_first_of(" ", commandPos);

			if (dilimitPos == std::string::npos)
			{
				dilimitPos = line.length();
			}
			else
			{
				dilimitPos -= 1;
			}

			std::string commandStr = line.substr(commandPos + 1, dilimitPos);
			dilimitPos += 1;

			for (size_t commandIndex = 0; commandIndex < m_Commands.size(); ++commandIndex)
			{
				if (commandStr == m_Commands[commandIndex].command)
				{
					if (m_Commands[commandIndex].commandType == CommandType::COMMAND_ONE_LINE)
					{
						ParseFuncParam params;
						params.dilimitPos = dilimitPos;
						params.line = line;
						params.lineNum = 0;
						m_Commands[commandIndex].parseFunc(params);
					}
					else
					{
						std::string numLines = line.substr(dilimitPos + 1);
						int totalLines = std::stoi(numLines);
						int lineNum = 0;
						while (lineNum < totalLines)
						{
							std::getline(inFile, line);

							if (line.empty())
							{
								continue;
							}
							else
							{
								ParseFuncParam params;
								params.dilimitPos = 0;
								params.line = line;
								params.lineNum = lineNum;
								m_Commands[commandIndex].parseFunc(params);
								++lineNum;
							}
						}
					}
				}
			}
		}

	}
	return true;
}

Color FileCommandLoader::ReadColor(const ParseFuncParam & params)
{
	size_t nextSpacePos = params.line.find_first_of(" ", params.dilimitPos + 1);
	uint8_t r = std::stoi(params.line.substr(params.dilimitPos, (nextSpacePos - params.dilimitPos)));

	size_t lastSpacePos = nextSpacePos;
	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
	uint8_t g = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));

	lastSpacePos = nextSpacePos;
	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
	uint8_t b = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));

	uint8_t a = std::stoi(params.line.substr(nextSpacePos + 1));

	return Color(r,g,b,a);
}

Vector2D FileCommandLoader::ReadSize(const ParseFuncParam& params)
{
	size_t nextSpacePos = params.line.find_first_of(" ", params.dilimitPos + 1);
	int width = std::stoi(params.line.substr(params.dilimitPos, nextSpacePos - params.dilimitPos));

	size_t lastSpacePos = nextSpacePos;
	nextSpacePos = params.line.find_first_of(" ", lastSpacePos + 1);
	int height = std::stoi(params.line.substr(lastSpacePos + 1, nextSpacePos - lastSpacePos));

	return Vector2D(width,height);
}

int FileCommandLoader::ReadInt(const ParseFuncParam& params)
{
	std::string intStr = params.line.substr(params.dilimitPos + 1);
	return std::stoi(intStr);
}

std::string FileCommandLoader::ReadString(const ParseFuncParam& params)
{
	return params.line.substr(params.dilimitPos + 1);
}

char FileCommandLoader::ReadChar(const ParseFuncParam& params)
{
	return params.line.substr(params.dilimitPos + 1)[0];
}
