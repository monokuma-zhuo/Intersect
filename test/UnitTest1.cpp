#include "pch.h"
#include "CppUnitTest.h"
#include"..//Intersection2/intersecter.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestCorrectness)
		{
			set<pair<double, double>> Array_dot;
			Line l1 = Line(-1, 4, 5, 2);
			Cycle c1 = Cycle(3, 3, 3);
			Ray r1 = Ray(2, 5, -1, 2);
			Segment s1 = Segment(2, 4, 3, 2);
			pair<pair<double, double>, int> dot1 = l1.intersect(r1);
			if (dot1.second == 1) {
				Array_dot.insert(dot1.first);
			}
			dot1 = l1.intersect(s1);
			if (dot1.second == 1) {
				Array_dot.insert(dot1.first);
			}
			pair<pair<double, double>, pair<double, double>> dot2 = c1.line_cycle_instere(l1);
			Array_dot.insert(dot2.first);
			Array_dot.insert(dot2.second);
			pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> dot3 = c1.ray_cycle_instere(r1);
			if (dot3.second.first == 1) {
				Array_dot.insert(dot3.first.first);
			}
			if (dot3.second.second == 1) {
				Array_dot.insert(dot3.first.second);
			}
			dot1 = r1.intersect(s1);
			if (dot1.second == 1) {
				if (r1.x1 < r1.x2) {
					if (r1.x1 <= dot1.first.first) {
						Array_dot.insert(dot1.first);
					}
				}
				else if (r1.x1 > r1.x2) {
					if (r1.x1 >= dot1.first.first) {
						Array_dot.insert(dot1.first);
					}
				}
				else {
					if (r1.y1 > r1.y2) {
						if (r1.y1 >= dot1.first.second) {
							Array_dot.insert(dot1.first);
						}
					}
					else if (r1.y1 < r1.y2) {
						if (r1.y1 <= dot1.first.second) {
							Array_dot.insert(dot1.first);
						}
					}
				}

			}
			Assert::AreEqual(5, (int)Array_dot.size());
		}
		TEST_METHOD(Testnodelr)
		{
			Line l1 = Line(0, 0, 1, 1);
			Ray r1 = Ray(1, 0, 2, 0);
			pair<pair<double, double>, int> dot1 = l1.intersect(r1);
			Assert::AreEqual(0, (int)dot1.first.first);
			Assert::AreEqual(0, (int)dot1.first.second);
			Assert::AreEqual(0, (int)dot1.second);

			
		}
		TEST_METHOD(Testnodels)
		{
			Line l1 = Line(0, 0, 1, 1);
			Segment r1 =Segment(1, 0, 2, 0);
			pair<pair<double, double>, int> dot1 = l1.intersect(r1);
			Assert::AreEqual(0, (int)dot1.first.first);
			Assert::AreEqual(0, (int)dot1.first.second);
			Assert::AreEqual(0, (int)dot1.second);

		}
		TEST_METHOD(Testnodecr)
		{
			Cycle c1 = Cycle(0, 0, 1);
			Ray r1 = Ray(1, 0, 2, 0);
			pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> dot3 = c1.ray_cycle_instere(r1);
			Assert::AreEqual(1, (int)dot3.first.first.first);
			Assert::AreEqual(0, (int)dot3.first.first.second);
			Assert::AreEqual(-1, (int)dot3.first.second.first);
			Assert::AreEqual(0, (int)dot3.first.second.second);
			Assert::AreEqual(1, (int)dot3.second.first);
			Assert::AreEqual(0, (int)dot3.second.second);
		}
		TEST_METHOD(Testnodecs)
		{
			Cycle c1 = Cycle(0, 0, 1);
			Segment r1 = Segment(1, 0, 2, 0);
			pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> dot3 = c1.segment_cycle_instere(r1);
			Assert::AreEqual(1, (int)dot3.first.first.first);
			Assert::AreEqual(0, (int)dot3.first.first.second);
			Assert::AreEqual(-1, (int)dot3.first.second.first);
			Assert::AreEqual(0, (int)dot3.first.second.second);
			Assert::AreEqual(1, (int)dot3.second.first);
			Assert::AreEqual(0, (int)dot3.second.second);
		}
		TEST_METHOD(TestAequals0)
		{
			Line l1 = Line(0, 0, 1, 1);
			Ray r1 = Ray(1, 0, 2, 0);
			pair<pair<double, double>, int> dot1 = l1.intersect(r1);
			Assert::AreEqual(0, (int)dot1.first.first);
			Assert::AreEqual(0, (int)dot1.first.second);
			Assert::AreEqual(0, (int)dot1.second);
		}
		TEST_METHOD(TestBequals0)
		{
			Line l1 = Line(0, 0, 0, 1);
			Ray r1 = Ray(1, 0, 0, 0);
			pair<pair<double, double>, int> dot1 = l1.intersect(r1);
			Assert::AreEqual(0, (int)dot1.first.first);
			Assert::AreEqual(0, (int)dot1.first.second);
			Assert::AreEqual(1, (int)dot1.second);
		}
	};
}
