#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestUtils.h"
#include <string>
#include <locale>
#include <codecvt>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

bool containsPosition(std::vector<Position> list, Position position)
{
	return std::find(list.begin(), list.end(), position) != list.end();
}

void TestUtils::AssertPositions(std::vector<Position> positions, std::vector<bool> exspectedPositions)
{
	for (int x = 0; x < 8; x++)
	{
		for (int y = 0; y < 8; y++)
		{
			int index = x + (7 - y) * 8;
			Position pos{ x, y };
			if (exspectedPositions[index])
			{
				std::wstring message{ L"Missing position " + std::to_wstring(pos.x) + L", " + std::to_wstring(pos.y) };
				Assert::IsTrue(containsPosition(positions, pos), message.c_str());
			}
			else
			{
				std::wstring message{ L"Invalid position " + std::to_wstring(pos.x) + L", " + std::to_wstring(pos.y) };
				Assert::IsFalse(containsPosition(positions, pos), message.c_str());
			}
		}
	}
}
