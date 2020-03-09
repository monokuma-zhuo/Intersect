#include "pch.h"
#include "CppUnitTest.h"
#include "../intersect/intersect.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace InteresectTestUnit
{
	TEST_CLASS(InteresectTestUnit)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Line l1(1, 0, 0, 1);
			Line l2(0, 0, 2, 2);
			pair<double, double> dot = l1.intersect(l2);
			Assert::AreEqual(dot.first, 0.5);
			Assert::AreEqual(dot.second, 0.5);
		}
		TEST_METHOD(TestMethod2)
		{
			Line l1(1, 0, 0, 1);
			Line l2(2, 0, 0, 2);
			bool interesect = l1.isteresect(l2);
			Assert::AreEqual(interesect, false);
		}
		TEST_METHOD(TestMethod3)
		{
			Cycle c1(0, 0, 1);
			Cycle c2(3, 0, 1);
			bool flag = c1.cycle_cycel_pos(c2);
			Assert::AreEqual(flag, false);
		}
		TEST_METHOD(TestMethod4)
		{
			Cycle c1(0, 0, 1);
			Cycle c2(2, 0, 1);
			pair<pair<double, double>, pair<double, double>> dot = c1.cycle_cycle_instere(c2);
			Assert::AreEqual(dot.first.first,1.0);
			Assert::AreEqual(dot.first.second, 0.0);
			Assert::AreEqual(dot.second.first, 1.0);
			Assert::AreEqual(dot.second.second, 0.0);
		}
		TEST_METHOD(TestMethod5)
		{
			Cycle c1(0, 0, 1);
			Cycle c2(1, 1, 1);
			pair<pair<double, double>, pair<double, double>> dot = c1.cycle_cycle_instere(c2);
			Assert::AreEqual(dot.first.first, 1.0);
			Assert::AreEqual(dot.first.second, 0.0);
			Assert::AreEqual(dot.second.first, 0.0);
			Assert::AreEqual(dot.second.second, 1.0);
		}
		TEST_METHOD(TestMethod6)
		{
			Cycle c1(0, 0, 2);
			Cycle c2(1, 0, 1);
			pair<pair<double, double>, pair<double, double>> dot = c1.cycle_cycle_instere(c2);
			Assert::AreEqual(dot.first.first, 2.0);
			Assert::AreEqual(dot.first.second, 0.0);
			Assert::AreEqual(dot.second.first, 2.0);
			Assert::AreEqual(dot.second.second, 0.0);
		}
		TEST_METHOD(TestMethod7)
		{
			Cycle c1(0, 0, 2);
			Cycle c2(0, 0, 1);
			bool result = c1.cycle_cycel_pos(c2);
			Assert::AreEqual(result, false);
		}
		TEST_METHOD(TestMethod8)
		{
			Cycle c(0, 0, 1);
			Line l(2, 0, 2, 1);
			bool result = c.line_cycle_pos(l);
			Assert::AreEqual(result, false);
		}
		TEST_METHOD(TestMethod9)
		{
			Cycle c(0, 0, 1);
			Line l(0, 1, 1, 1);
			pair<pair<double, double>, pair<double, double>> dot = c.line_cycle_instere(l);
			Assert::AreEqual(dot.first.first, 0.0);
			Assert::AreEqual(dot.first.second, 1.0);
			Assert::AreEqual(dot.second.first, 0.0);
			Assert::AreEqual(dot.second.second, 1.0);
			
		}
		TEST_METHOD(TestMethod10)
		{
			Cycle c(0, 0, 1);
			Line l(1, 0, 0, 1);
			pair<pair<double, double>, pair<double, double>> dot = c.line_cycle_instere(l);
			Assert::AreEqual(dot.first.first, 1.0);
			Assert::AreEqual(dot.first.second, 0.0);
			Assert::AreEqual(dot.second.first, 0.0);
			Assert::AreEqual(dot.second.second, 1.0);

		}
	};
}
