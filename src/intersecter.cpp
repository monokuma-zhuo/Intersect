#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <fstream>
#include<string.h>
using namespace std;
/*struct OperatorException : public exception
{
	const char* what() const throw ()
	{
		return "Operator Exception";
	}
};
struct EndException : public exception
{
	const char* what() const throw ()
	{
		return "End Exception";
	}
};
struct DefectException : public exception
{
	const char* what() const throw ()
	{
		return "Defect Exception";
	}
};
struct NumberException : public exception
{
	const char* what() const throw ()
	{
		return "Number Exception";
	}
};
struct EdgeException : public exception
{
	const char* what() const throw ()
	{
		return "Edge Exception";
	}
};
struct LinesameException : public exception
{
	const char* what() const throw ()
	{
		return "Linesame Exception";
	}
};
struct CirclesameException : public exception
{
	const char* what() const throw ()
	{
		return "Circlesame Exception";
	}
};

char temp;
void ifex(double a) {
	if (a > 100000 || a < -100000) {
		throw EdgeException();
	}
}
double getnum(ifstream& in) {
	char temp;
	string token = "";
	temp = in.get();
	while (isspace(temp)) {
		temp = in.get();
	}
	if (!isdigit(temp)) {
		throw NumberException();
	}
	while (isdigit(temp)) {
		token = token + temp;
		temp = in.get();
	}
	double a = atoi(token.c_str());
	ifex(a);
	return a;

}*/
class Ray;
class Segment;
class Line
{
public:
	double A, B, C;
	Line() {};
	Line(double x1,double y1,double x2,double y2)
	{
		A = y2 - y1;
		B = x1 - x2;
		C = x2 * y1 - x1 * y2;
	}
	Line(double a, double b, double c) 
	{
		A = a;
		B = b;
		C = c;
	}
	pair<double,double> intersect(Line l)
	{
		double x = (l.C * B - C * l.B) / (A * l.B - B * l.A);
		double y = (C * l.A - l.C * A) / (A * l.B - B * l.A);
		pair<double, double> dot(x, y);
		return dot;
	}
	pair<pair<double, double>, int> intersect(Ray r);
	pair<pair<double, double>, int> intersect(Segment s);
	bool isteresect(Line l) 
	{
		
		if ((fabs((A * l.B - B * l.A)-(0)) < 1e-10))
		{
			
			if ((fabs((A *l.C) - (l.A * C)) < 1e-10)) {
				//throw LinesameException();
			}
			return false;
		}
		else
		{
			return true;
		}
	}
};
class Ray :public Line {
public:
	double x1, y1, x2, y2;
	Ray(double x10, double y10, double x20, double y20)
	{
		A = y20 - y10;
		B = x10 - x20;
		C = x20 * y10 - x10 * y20;
		x1 = x10;
		y1 = y10;
		x2 = x20;
		y2 = y20;
	}
};
class Segment :public Line {
public:
	double x1, y1, x2, y2;
	Segment(double x10, double y10, double x20, double y20)
	{
		A = y20 - y10;
		B = x10 - x20;
		C = x20 * y10 - x10 * y20;
		x1 = x10;
		y1 = y10;
		x2 = x20;
		y2 = y20;
	}
};
class Cycle
{
public:
	double x, y, r;
	Cycle(double x, double y, double r)
	{
		this->x = x;
		this->y = y;
		this->r = r;
	}
	bool line_cycle_pos(Line l)
	{
		double length = abs((l.A * x + l.B * y + l.C)) / (sqrt(l.A * l.A + l.B * l.B));
		if (fabs(length - r) < 1e-10) {
			return true;
		}
		else if (length > r) 
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	pair<pair<double, double>, pair<double, double>> line_cycle_instere(Line l)
	{
		if (l.A == 0) 
		{
			double y_point = -1.0 * l.C / l.B;
			double temp = sqrt((r * r - (y - y_point) * (y - y_point)));
			pair<double, double> dot1(x + temp, y_point);
			pair<double, double> dot2(x - temp, y_point);
			return make_pair(dot1, dot2);
		}
		else if (l.B == 0)
		{
			double x_point = -1.0 * l.C / l.A;
			double temp = sqrt((r * r - (x - x_point) * (x - x_point)));
			pair<double, double> dot1(x_point, y + temp);
			pair<double, double> dot2(x_point, y - temp);
			return make_pair(dot1, dot2);
		}
		else
		{
			double k = -1.0 * l.A / l.B;
			double b = -1.0 * l.C / l.B;	
			double a1 = 1.0 + k * k;
			double b1 = 2.0 * (k * b - k * y - x);
			double c1 = (b - y) * (b - y) -(r * r)+(x*x);
			double x1 = (-1.0 * b1 + sqrt(b1 * b1 - 4 * a1 * c1)) / (2.0 * a1);
			double y1 = k * x1 + b;
			double x2 = (-1.0 * b1 - sqrt(b1 * b1 - 4 * a1 * c1)) / (2.0 * a1);
			double y2 = k * x2 + b;
			pair<double, double> dot1(x1, y1);
			pair<double, double> dot2(x2, y2);
			return make_pair(dot1, dot2);
		}
	}
	pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> ray_cycle_instere(Ray l) {
		int flag1 = 0, flag2 = 0;
		if (l.A == 0)
		{
			double y_point = -1.0 * l.C / l.B;
			double temp = sqrt((r * r - (y - y_point) * (y - y_point)));
			pair<double, double> dot1(x + temp, y_point);
			pair<double, double> dot2(x - temp, y_point);
			if (l.x1 < l.x2) {
				if (x+temp >= l.x1) {
					flag1 = 1;
				}
				if (x - temp >= l.x1) {
					flag2 = 1;
				}
			}
			else if (l.x1 > l.x2) {
				if (x + temp <= l.x1) {
					flag1 = 1;
				}
				if (x - temp <= l.x1) {
					flag2 = 1;
				}
			}
			pair<int, int> dot3(flag1, flag2);
			return make_pair(make_pair(dot1, dot2), dot3);
		}
		else if (l.B == 0)
		{
			double x_point = -1.0 * l.C / l.A;
			double temp = sqrt((r * r - (x - x_point) * (x - x_point)));
			pair<double, double> dot1(x_point, y + temp);
			pair<double, double> dot2(x_point, y - temp);
			if (l.y1 < l.y2) {
				if (y + temp >= l.y1) {
					flag1 = 1;
				}
				if (y - temp >= l.y1) {
					flag2 = 1;
				}
			}
			else if (l.y1 > l.y2) {
				if (y + temp <= l.y1) {
					flag1 = 1;
				}
				if (y - temp <= l.y1) {
					flag2 = 1;
				}
			}
			pair<int, int> dot3(flag1, flag2);
			return make_pair(make_pair(dot1, dot2), dot3);
		}
		else
		{
			double k = -1.0 * l.A / l.B;
			double b = -1.0 * l.C / l.B;
			double a1 = 1.0 + k * k;
			double b1 = 2.0 * (k * b - k * y - x);
			double c1 = (b - y) * (b - y) - (r * r) + (x * x);
			double x1 = (-1.0 * b1 + sqrt(b1 * b1 - 4 * a1 * c1)) / (2.0 * a1);
			double y1 = k * x1 + b;
			double x2 = (-1.0 * b1 - sqrt(b1 * b1 - 4 * a1 * c1)) / (2.0 * a1);
			double y2 = k * x2 + b;
			pair<double, double> dot1(x1, y1);
			pair<double, double> dot2(x2, y2);
			if (l.x1 < l.x2) {
				if (x1 >= l.x1) {
					flag1 = 1;
				}
				if (x2 >= l.x1) {
					flag2 = 1;
				}
			}
			else if (l.x1 > l.x2) {
				if (x1 <= l.x1) {
					flag1 = 1;
				}
				if (x2 <= l.x1) {
					flag2 = 1;
				}
			}
			pair<int, int> dot3(flag1, flag2);
			return make_pair(make_pair(dot1, dot2), dot3);
		}
	}
	pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> segment_cycle_instere(Segment l) {
		int flag1 = 0, flag2 = 0;
		if (l.A == 0)
		{
			double y_point = -1.0 * l.C / l.B;
			double temp = sqrt((r * r - (y - y_point) * (y - y_point)));
			pair<double, double> dot1(x + temp, y_point);
			pair<double, double> dot2(x - temp, y_point);
			if (l.x1 < l.x2) {
				if (x + temp >= l.x1 && x + temp <= l.x2) {
					flag1 = 1;
				}
				if (x - temp >= l.x1 && x-temp <= l.x2 ) {
					flag2 = 1;
				}
			}
			else if (l.x1 > l.x2) {
				if (x + temp <= l.x1 && x+temp >= l.x2) {
					flag1 = 1;
				}
				if (x - temp <= l.x1 && x-temp >= l.x2) {
					flag2 = 1;
				}
			}
			pair<int, int> dot3(flag1, flag2);
			return make_pair(make_pair(dot1, dot2), dot3);
		}
		else if (l.B == 0)
		{
			double x_point = -1.0 * l.C / l.A;
			double temp = sqrt((r * r - (x - x_point) * (x - x_point)));
			pair<double, double> dot1(x_point, y + temp);
			pair<double, double> dot2(x_point, y - temp);
			if (l.y1 < l.y2) {
				if (y + temp >= l.y1 && y+temp <= l.y2) {
					flag1 = 1;
				}
				if (y - temp >= l.y1 && y-temp <= l.y2) {
					flag2 = 1;
				}
			}
			else if (l.y1 > l.y2) {
				if (y + temp <= l.y1 && y+temp >=l.y2) {
					flag1 = 1;
				}
				if (y - temp <= l.y1 && y-temp >=l.y2) {
					flag2 = 1;
				}
			}
			pair<int, int> dot3(flag1, flag2);
			return make_pair(make_pair(dot1, dot2), dot3);
		}
		else
		{
			double k = -1.0 * l.A / l.B;
			double b = -1.0 * l.C / l.B;
			double a1 = 1.0 + k * k;
			double b1 = 2.0 * (k * b - k * y - x);
			double c1 = (b - y) * (b - y) - (r * r) + (x * x);
			double x1 = (-1.0 * b1 + sqrt(b1 * b1 - 4 * a1 * c1)) / (2.0 * a1);
			double y1 = k * x1 + b;
			double x2 = (-1.0 * b1 - sqrt(b1 * b1 - 4 * a1 * c1)) / (2.0 * a1);
			double y2 = k * x2 + b;
			pair<double, double> dot1(x1, y1);
			pair<double, double> dot2(x2, y2);
			if (l.x1 < l.x2) {
				if (x1 >= l.x1 && x1 <=l.x2) {
					flag1 = 1;
				}
				if (x2 >= l.x1 && x2 <=l.x2) {
					flag2 = 1;
				}
			}
			else if (l.x1 > l.x2) {
				if (x1 <= l.x1 && x1 >=l.x2) {
					flag1 = 1;
				}
				if (x2 <= l.x1 && x2 >=l.x2) {
					flag2 = 1;
				}
			}
			pair<int, int> dot3(flag1, flag2);
			return make_pair(make_pair(dot1, dot2), dot3);
		}
	}
	bool cycle_cycel_pos(Cycle c)
	{
		double length = sqrt((c.x - x) * (c.x - x) + (c.y - y) * (c.y - y));
		if ( (x == c.x && y == c.y && r == c.r)) {
			//throw CirclesameException();
		}
		if (fabs(length - (r + c.r)) < 1e-10 || fabs(length - fabs(r - c.r)) < 1e-10) {
			return true;
		}
		else if (length > r + c.r||length<abs(r-c.r))
		{
			
			return false;
		}
		else
		{
			return true;
		}
	}
	pair<pair<double, double>, pair<double, double>> cycle_cycle_instere(Cycle c)
	{
		double D = -2.0 * x;
		double E = -2.0 * y;
		double F = (x * x) + (y * y) - (r * r);
		double D1 = -2.0 * c.x;
		double E1 = -2.0 * c.y;
		double F1 = (c.x * c.x) + (c.y * c.y) - (c.r * c.r);
		Line temp_l(D - D1, E - E1, F - F1);
		return line_cycle_instere(temp_l);
	}
};
pair<pair<double, double>, int> Line::intersect(Ray r) {
	double x = (r.C * B - C * r.B) / (A * r.B - B * r.A);
	double y = (C * r.A - r.C * A) / (A * r.B - B * r.A);
	pair<double, double> dot(x, y);
	if (r.x1 > r.x2 && r.x1 >= x) {
		pair<pair<double, double>, int> dot1(dot, 1);
		return dot1;
	}
	else if (r.x1 < r.x2 && r.x1 <= x) {
		pair<pair<double, double>, int> dot1(dot, 1);
		return dot1;
	}
	else if (r.x1 == r.x2 && r.x1 == x) {
		if (r.y1 > r.y2 && r.y1 >= y) {
			pair<pair<double, double>, int> dot1(dot, 1);
			return dot1;
		}
		else if (r.y1 < r.y2 && r.y1 <= y) {
			pair<pair<double, double>, int> dot1(dot, 1);
			return dot1;
		}
		else if (r.y1 == r.y2 && y == r.y1) {
			pair<pair<double, double>, int> dot1(dot, 1);
			return dot1;
		}
		else {
			pair<pair<double, double>, int> dot1(dot, 0);
			return dot1;
		}
	}
	else {
		pair<pair<double, double>, int> dot1(dot, 0);
		return dot1;
	}
}
pair<pair<double, double>, int> Line::intersect(Segment s) {
	double x = (s.C * B - C * s.B) / (A * s.B - B * s.A);
	double y = (C * s.A - s.C * A) / (A * s.B - B * s.A);
	pair<double, double> dot(x, y);
	if (s.x1 > s.x2) {
		if (x >= s.x2 && x <= s.x1) {
			pair<pair<double, double>, int> dot1(dot, 1);
			return dot1;
		}
		else {
			pair<pair<double, double>, int> dot1(dot, 0);
			return dot1;
		}
	}
	else if (s.x1 < s.x2) {
		if (x >= s.x1 && x <= s.x2) {
			pair<pair<double, double>, int> dot1(dot, 1);
			return dot1;
		}
		else {
			pair<pair<double, double>, int> dot1(dot, 0);
			return dot1;
		}
	}
	else {
		if (s.y1 > s.y2) {
			if (y >= s.y2 && y <= s.y1) {
				pair<pair<double, double>, int> dot1(dot, 1);
				return dot1;
			}
			else {
				pair<pair<double, double>, int> dot1(dot, 0);
				return dot1;
			}
		}
		else if (s.y1 < s.y2) {
			if (y >= s.y1 && y <= s.y2) {
				pair<pair<double, double>, int> dot1(dot, 1);
				return dot1;
			}
			else {
				pair<pair<double, double>, int> dot1(dot, 0);
				return dot1;
			}
		}
		else if (s.y1 == s.y2 && s.y1 == y) {
			pair<pair<double, double>, int> dot1(dot, 1);
			return dot1;
		}
		else {
			pair<pair<double, double>, int> dot1(dot, 0);
			return dot1;
		}
	}
}
int main(int argc,char*argv[])
{	//try
	//{
	ifstream in;
	ofstream out;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			in = ifstream(argv[i + 1]);
		}
		if (strcmp(argv[i], "-o") == 0)
		{
			out = ofstream(argv[i + 1]);
		}

	}
	
	//in = ifstream("input.txt");
	//out = ofstream("output.txt");
	char type;
	double x1, x2, y1, y2;
	double a, b, r;
	int n = 0;
	in >> n;
	vector<Line> Array_line;
	vector<Ray> Array_ray;
	vector<Segment> Array_segment;
	vector<Cycle> Array_cycle;
	set<pair<double, double>> Array_dot;
	for (int i = 0; i < n; i++) {
		
		/*if (in.eof()) {
			throw DefectException();
		}*/
		in >> type;
		
		if (type == 'L') {
			in >> x1 >> y1 >> x2 >> y2;
			/*x1 = getnum(in);
			y1 = getnum(in);
			x2 = getnum(in);
			y2 = getnum(in);*/
			Line l = Line(x1, y1, x2, y2);
			
			for (unsigned int j = 0; j < Array_line.size(); j++)
			{
				if (Array_line.at(j).isteresect(l))
				{
					Array_dot.insert(Array_line.at(j).intersect(l));
				}
			}
			for (unsigned int j = 0; j < Array_ray.size(); j++)
			{
				if (Array_ray.at(j).isteresect(l))
				{
					pair<pair<double, double>, int> dot = l.intersect(Array_ray.at(j));
					if (dot.second == 1) {
						Array_dot.insert(dot.first);
					}
				}
			}
			for (unsigned int j = 0; j < Array_segment.size(); j++)
			{
				if (Array_segment.at(j).isteresect(l))
				{
					pair<pair<double, double>, int> dot = l.intersect(Array_segment.at(j));
					if (dot.second == 1) {
						Array_dot.insert(dot.first);
					}
				}
			}
			for (unsigned int j = 0; j < Array_cycle.size(); j++) {
				if (Array_cycle.at(j).line_cycle_pos(l))
				{
					pair<pair<double, double>, pair<double, double>> dot = Array_cycle.at(j).line_cycle_instere(l);
					Array_dot.insert(dot.first);
					Array_dot.insert(dot.second);
				}
			}
			Array_line.push_back(l);
		}
		else if (type == 'R') {
			in >> x1 >> y1 >> x2 >> y2;
			/*x1 = getnum(in);
			y1 = getnum(in);
			x2 = getnum(in);
			y2 = getnum(in);*/
			Ray r = Ray(x1, y1, x2, y2);
			
			for (unsigned int j = 0; j < Array_line.size(); j++)
			{
				if (Array_line.at(j).isteresect(r))
				{
					pair<pair<double, double>, int> dot = Array_line.at(j).intersect(r);
					if (dot.second == 1) {
						Array_dot.insert(dot.first);
					}
				}
			}
			for (unsigned int j = 0; j < Array_ray.size(); j++)
			{
				if (Array_ray.at(j).isteresect(r))
				{
					pair<pair<double, double>, int> dot = r.intersect(Array_ray.at(j));
					if (dot.second == 1) {
						if (r.x1 < r.x2) {
							if (r.x1 <= dot.first.first) {
								Array_dot.insert(dot.first);
							}
						}
						else if (r.x1 > r.x2) {
							if (r.x1 >= dot.first.first) {
								Array_dot.insert(dot.first);
							}
						}
						else {
							if (r.y1 > r.y2) {
								if (r.y1 >= dot.first.second) {
									Array_dot.insert(dot.first);
								}
							}
							else if (r.y1 < r.y2) {
								if (r.y1 <= dot.first.second) {
									Array_dot.insert(dot.first);
								}
							}
						}

					}
				}
			}
			for (unsigned int j = 0; j < Array_segment.size(); j++)
			{
				if (Array_segment.at(j).isteresect(r))
				{
					pair<pair<double, double>, int> dot = r.intersect(Array_segment.at(j));
					if (dot.second == 1) {
						if (r.x1 < r.x2) {
							if (r.x1 <= dot.first.first) {
								Array_dot.insert(dot.first);
							}
						}
						else if (r.x1 > r.x2) {
							if (r.x1 >= dot.first.first) {
								Array_dot.insert(dot.first);
							}
						}
						else {
							if (r.y1 > r.y2) {
								if (r.y1 >= dot.first.second) {
									Array_dot.insert(dot.first);
								}
							}
							else if (r.y1 < r.y2) {
								if (r.y1 <= dot.first.second) {
									Array_dot.insert(dot.first);
								}
							}
						}

					}
				}
			}
			for (unsigned int j = 0; j < Array_cycle.size(); j++) {
				if (Array_cycle.at(j).line_cycle_pos(r))
				{
					pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> dot = Array_cycle.at(j).ray_cycle_instere(r);
					if (dot.second.first == 1) {
						Array_dot.insert(dot.first.first);
					}
					if (dot.second.second == 1) {
						Array_dot.insert(dot.first.second);
					}

				}
				
			}
			Array_ray.push_back(r);
		}
		else if (type == 'S') {
			in >> x1 >> y1 >> x2 >> y2;
			/*x1 = getnum(in);
			y1 = getnum(in);
			x2 = getnum(in);
			y2 = getnum(in);*/
			Segment s = Segment(x1, y1, x2, y2);
			
			for (unsigned int j = 0; j < Array_line.size(); j++)
			{
				
				if (Array_line.at(j).isteresect(s))
				{
					pair<pair<double, double>, int> dot = Array_line.at(j).intersect(s);
					if (dot.second == 1) {
						Array_dot.insert(dot.first);
					}
				}
			}
			
			for (unsigned int j = 0; j < Array_ray.size(); j++)
			{
				if (Array_ray.at(j).isteresect(s))
				{
					pair<pair<double, double>, int> dot = s.intersect(Array_ray.at(j));
					if (dot.second == 1) {
						if (s.x1 < s.x2) {
							if (s.x1 <= dot.first.first && dot.first.first <= s.x2) {
								Array_dot.insert(dot.first);
							}
						}
						else if (s.x1 > s.x2) {
							if (s.x1 >= dot.first.first && dot.first.first >= s.x2) {
								Array_dot.insert(dot.first);
							}
						}
						else {
							if (s.y1 > s.y2) {
								if (s.y1 >= dot.first.second && dot.first.second >= s.y2) {
									Array_dot.insert(dot.first);
								}
							}
							else if (s.y1 < s.y2) {
								if (s.y1 <= dot.first.second && s.y2 <= dot.first.second) {
									Array_dot.insert(dot.first);
								}
							}
						}

					}
				}
			}
			
			for (unsigned int j = 0; j < Array_segment.size(); j++)
			{
				if (Array_segment.at(j).isteresect(s))
				{
					pair<pair<double, double>, int> dot = s.intersect(Array_segment.at(j));
					if (dot.second == 1) {
						if (s.x1 < s.x2) {
							if (s.x1 <= dot.first.first && dot.first.first <= s.x2) {
								Array_dot.insert(dot.first);
							}
						}
						else if (s.x1 > s.x2) {
							if (s.x1 >= dot.first.first && dot.first.first >= s.x2) {
								Array_dot.insert(dot.first);
							}
						}
						else {
							if (s.y1 > s.y2) {
								if (s.y1 >= dot.first.second && dot.first.second >= s.y2) {
									Array_dot.insert(dot.first);
								}
							}
							else if (s.y1 < s.y2) {
								if (s.y1 <= dot.first.second && s.y2 <= dot.first.second) {
									Array_dot.insert(dot.first);
								}
							}
						}

					}
				}
			}
			
			for (unsigned int j = 0; j < Array_cycle.size(); j++) {
				if (Array_cycle.at(j).line_cycle_pos(s))
				{
					pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> dot = Array_cycle.at(j).segment_cycle_instere(s);
					if (dot.second.first == 1) {
						Array_dot.insert(dot.first.first);
					}
					if (dot.second.second == 1) {
						Array_dot.insert(dot.first.second);
					}

				}
			}
			Array_segment.push_back(s);
			
		}
		else if (type == 'C')
		{
			in >> a >> b >> r;
			/*a = getnum(in);
			b = getnum(in);
			r = getnum(in);*/
			Cycle c = Cycle(a, b, r);
			
			for (unsigned int j = 0; j < Array_line.size(); j++)
			{
				if (c.line_cycle_pos(Array_line.at(j)))
				{
					pair<pair<double, double>, pair<double, double>> dot = c.line_cycle_instere(Array_line.at(j));
					Array_dot.insert(dot.first);
					Array_dot.insert(dot.second);
				}
			}
			for (unsigned int j = 0; j < Array_ray.size(); j++)
			{
				if (c.line_cycle_pos(Array_ray.at(j)))
				{
					pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> dot = c.ray_cycle_instere(Array_ray.at(j));
					if (dot.second.first == 1) {
						Array_dot.insert(dot.first.first);
					}
					if (dot.second.second == 1) {
						Array_dot.insert(dot.first.second);
					}
				}
			}
			for (unsigned int j = 0; j < Array_segment.size(); j++)
			{
				if (c.line_cycle_pos(Array_segment.at(j)))
				{
					pair<pair<pair<double, double>, pair<double, double>>, pair<int, int>> dot = c.segment_cycle_instere(Array_segment.at(j));
					if (dot.second.first == 1) {
						Array_dot.insert(dot.first.first);
					}
					if (dot.second.second == 1) {
						Array_dot.insert(dot.first.second);
					}
				}
			}
			for (unsigned int j = 0; j < Array_cycle.size(); j++)
			{
				if (c.cycle_cycel_pos(Array_cycle.at(j)))
				{
					pair<pair<double, double>, pair<double, double>> dot = c.cycle_cycle_instere(Array_cycle.at(j));
					Array_dot.insert(dot.first);
					Array_dot.insert(dot.second);
				}
			}
			Array_cycle.push_back(c);
		}
		/*else {
		throw OperatorException();
		}*/
	}
	
	/*char tempchar;
	tempchar = in.get();
	while (isspace(tempchar)) { tempchar = in.get();; }
	if (!in.eof()) {
		throw EndException();
	}*/
	out << Array_dot.size() << endl;/*
	}
	catch(OperatorException& e)
	{
		cout << e.what() << endl;
	}
	catch (EndException& e) {
		cout << e.what() << endl;
	}
	catch (DefectException& e) {
		cout << e.what() << endl;
	}
	catch (LinesameException& e) {
		cout << e.what() << endl;
	}
	catch (CirclesameException& e) {
		cout << e.what() << endl;
	}*/
	
	
}