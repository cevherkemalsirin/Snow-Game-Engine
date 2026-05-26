#pragma once

#include <functional>
#include <vector>
#include <string>


class Color;
class Vector2D;

enum class CommandType
{
	COMMAND_ONE_LINE = 0,
	COMMAND_MULTI_LINE,

};

struct ParseFuncParam {
	std::string line;
	size_t dilimitPos;
	uint32_t lineNum;
};

using ParseFunction = std::function<void(const ParseFuncParam & params)>;

struct Command
{
	CommandType commandType = CommandType::COMMAND_ONE_LINE;
	std::string command = "";
	ParseFunction parseFunc = nullptr;
};


class FileCommandLoader
{
public:
	void AddCommand(const Command& command);
	bool LoadFile(const std::string& filePath);

	static Color ReadColor(const ParseFuncParam& params);
	static Vector2D ReadSize(const ParseFuncParam& params);
	static int ReadInt(const ParseFuncParam& params);
	static std::string ReadString(const ParseFuncParam& params);
	static char ReadChar(const ParseFuncParam& params);


private:
	std::vector<Command> m_Commands;
};