#include "stdafx.h"
#include "TestUtils.h"
#include <string>
#include <locale>
#include <codecvt>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool containsPosition(std::vector<Position> list, Position position)
{
	return std::find(list.begin(), list.end(), position) != list.end();
}

const wchar_t* toWideStr(std::string str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wstring =  converter.from_bytes(str);
	return wstring.c_str();
}

void TestUtils::AssertPositions(std::vector<Position> positions, std::vector<bool> exspectedPositions)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			int index = x + y * 8;
			Position pos{ x, y };
			if (exspectedPositions[index])
			{
				Assert::IsTrue(containsPosition(positions, pos), toWideStr("Missing position " + Position::toString(pos) ) );
			}
			else
			{
				Assert::IsFalse(containsPosition(positions, pos), toWideStr("Invalid position " + Position::toString(pos) ) );
			}
		}
	}
}
