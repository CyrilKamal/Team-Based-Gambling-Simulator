#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "roulette.h"
#include "rouletteMenus.h""
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CourseProjectTests
{
	TEST_CLASS(RouletteTests)
	{
	public:
		
		TEST_METHOD(T001_spinBall_1_36)		// check between range of 1-36
		{
			// act
			int ball;
			int found = 0;

			// arrange
			ball = spinBall();

			for (int i = 1; i <= 36; i++)
			{
				if (ball == i)
				{
					found = i;
					break;
				}
			}

			// assert
			Assert::AreEqual(ball, found);
		}

		TEST_METHOD(T002_checkSingleBet_20_false)		// single bet, found
		{
			// act
			BET one = { "Green", 0, 500 };
			BET two = { "Red(Single)", 3, 200 };
			BET three = { "Black(Single)", 20, 450 };
			BET four = { "Range(19 - 36)", -1, 300 };

			BET saved[] = { one, two };
			BET unsaved[] = { three, four };
			int bet = 20;
			bool result;
			bool EXPECTED = false;

			// arrange
			result = checkSingleBet(saved, unsaved, bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T003_checkSingleBet_35_true)		// single bet, not found
		{
			// act
			BET one = { "Green", 0, 500 };
			BET two = { "Red(Single)", 3, 200 };
			BET three = { "Black(Single)", 20, 450 };
			BET four = { "Range(19 - 36)", -1, 300 };

			BET saved[] = { one, two };
			BET unsaved[] = { three, four };
			int bet = 35;
			bool result;
			bool EXPECTED = true;

			// arrange
			result = checkSingleBet(saved, unsaved, bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T004_checkSingleBet_0_false)		// single bet, found - check green specifically
		{
			// act
			BET one = { "Green", 0, 500 };
			BET two = { "Red(Single)", 3, 200 };
			BET three = { "Black(Single)", 20, 450 };
			BET four = { "Range(19 - 36)", -1, 300 };

			BET saved[] = { one, two };
			BET unsaved[] = { three, four };
			int bet = 0;
			bool result;
			bool EXPECTED = false;

			// arrange
			result = checkSingleBet(saved, unsaved, bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T005_checkBetType_Range_19_36_false)		// range bet, found
		{
			// act
			BET one = { "Green", 0, 500 };
			BET two = { "Red(Single)", 3, 200 };
			BET three = { "Black(Single)", 20, 450 };
			BET four = { "Range(19 - 36)", -1, 300 };

			BET saved[] = { one, two };
			BET unsaved[] = { three, four };
			char* bet = "Range(19 - 36)";
			bool result;
			bool EXPECTED = false;

			// arrange
			result = checkBetType(saved, unsaved, bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T006_checkBetType_Range_1_12_true)		// range bet, not found
		{
			// act
			BET one = { "Green", 0, 500 };
			BET two = { "Red(Single)", 3, 200 };
			BET three = { "Black(Single)", 20, 450 };
			BET four = { "Range(19 - 36)", -1, 300 };

			BET saved[] = { one, two };
			BET unsaved[] = { three, four };
			char* bet = "Range(1 - 12)";
			bool result;
			bool EXPECTED = true;

			// arrange
			result = checkBetType(saved, unsaved, bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T007_checkBetType_Black_Group_false)		// group bet, found
		{
			// act
			BET one = { "Green", 0, 500 };
			BET two = { "Red(Single)", 3, 200 };
			BET three = { "Black(Group)", -1, 450 };
			BET four = { "Range(19 - 36)", -1, 300 };

			BET saved[] = { one, two };
			BET unsaved[] = { three, four };
			char* bet = "Black(Group)";
			bool result;
			bool EXPECTED = false;

			// arrange
			result = checkBetType(saved, unsaved, bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T008_checkBetType_Red_Group_true)		// group bet, not found
		{
			// act
			BET one = { "Green", 0, 500 };
			BET two = { "Red(Single)", 3, 200 };
			BET three = { "Black(Group)", -1, 450 };
			BET four = { "Range(19 - 36)", -1, 300 };

			BET saved[] = { one, two };
			BET unsaved[] = { three, four };
			char* bet = "Red(Group)";
			bool result;
			bool EXPECTED = true;

			// arrange
			result = checkBetType(saved, unsaved, bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T009_findColour_17_Black)		// result = black
		{
			// act
			int bet = 17;
			char* result;
			char* EXPECTED = "Black(Single)";

			// arrange
			result = findColour(bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T010_findColour_0_Green)		// result = green
		{
			// act
			int bet = 0;
			char* result;
			char* EXPECTED = "Green";

			// arrange
			result = findColour(bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T011_findColour_9_Red)		// result = red
		{
			// act
			int bet = 9;
			char* result;
			char* EXPECTED = "Red(Single)";

			// arrange
			result = findColour(bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T012_findGroupColour_0_Green)		// result = N/A
		{
			// act
			int bet = 0;
			char* result;
			char* EXPECTED = "N/A";

			// arrange
			result = findGroupColour(bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T013_findGroupColour_32_Red)		// result = red(group)
		{
			// act
			int bet = 32;
			char* result;
			char* EXPECTED = "Red(Group)";

			// arrange
			result = findGroupColour(bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}

		TEST_METHOD(T013_findGroupColour_2_Black)		// result = black(group)
		{
			// act
			int bet = 2;
			char* result;
			char* EXPECTED = "Black(Group)";

			// arrange
			result = findGroupColour(bet);

			// assert
			Assert::AreEqual(result, EXPECTED);
		}
	};
}
