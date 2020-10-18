#include "pch.h"
#include "../Stack/arr_stack.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StackTest
{
	TEST_CLASS(StackTest)
	{
	public:
		
		TEST_METHOD(TestEmpty) {
			Stack<int> s;
			Assert::IsTrue(s.empty());
		}

		TEST_METHOD(TestPushBackStackNotEmpty) {
			Stack<int> s;
			s.push_back(1);
			Assert::IsFalse(s.empty());
		}

		TEST_METHOD(TestPushBackSingleValue) {
			Stack<int> s;
			s.push_back(1);
			Assert::AreEqual(s.getTop(), 1);
		}

		TEST_METHOD(TestPushBackTwoValues) {
			Stack<int> s;
			s.push_back(1);
			s.push_back(2);
			Assert::AreEqual(s.getTop(), 2);
		}

		TEST_METHOD(TestPushPopSingleValue) {
			Stack<int> s;
			s.push_back(1);
			Assert::AreEqual(s.getTop(), 1);
			s.pop_back();
			Assert::IsTrue(s.empty());
		}

		TEST_METHOD(TestPushTwoPopOneValue) {
			Stack<int> s;
			s.push_back(1);
			s.push_back(2);
			Assert::AreEqual(s.getTop(), 2);
			s.pop_back();
			Assert::IsFalse(s.empty());
			Assert::AreEqual(s.getTop(), 1);
		}

		TEST_METHOD(TestPushTwoValuesSize) {
			Stack<int> s;
			s.push_back(1);
			s.push_back(2);
			Assert::AreEqual(s.getSize(), 2);
		}
	};
}
