#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <fstream>
#include<string.h>
using namespace std;
class Line
{
public:
	double A, B, C;
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
	bool isteresect(Line l) 
	{
		if (A * l.B - B * l.A == 0)
		{
			return false;
		}
		else
		{
			return true;
		}
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
		if (length > r) 
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
	bool cycle_cycel_pos(Cycle c)
	{
		double length = sqrt((c.x - x) * (c.x - x) + (c.y - y) * (c.y - y));
		if (length > r + c.r||length<abs(r-c.r))
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
int main(int argc,char*argv[])
{	
	ifstream in;
	ofstream out;
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-i") == 0)
		{
			in = ifstream(argv[i+1]);
		}
		if (strcmp(argv[i], "-o") == 0)
		{
			out = ofstream(argv[i+1]);
		}
		
	}
	char type;
	double x1, x2, y1, y2;
	double a, b, r;
	int n;
	in >> n;
	vector<Line> Array_line;
	vector<Cycle> Array_cycle;
	set<pair<double, double>> Array_dot;
	for (int i = 0; i < n; i++) {
		in >> type;
		if (type == 'L') {
			in >> x1 >> y1 >> x2 >> y2;
			Line l = Line(x1, y1, x2, y2);
			Array_line.push_back(l);
			for (unsigned int j = 0; j < Array_line.size()-1; j++)
			{
				if (Array_line.at(j).isteresect(l))
				{
					Array_dot.insert(Array_line.at(j).intersect(l));
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
		}
		if (type == 'C')
		{
			in >> a >> b >> r;
			Cycle c = Cycle(a, b, r);
			Array_cycle.push_back(c);
			for (unsigned int j = 0; j < Array_line.size(); j++)
			{
				if (c.line_cycle_pos(Array_line.at(j)))
				{
					pair<pair<double, double>, pair<double, double>> dot = c.line_cycle_instere(Array_line.at(j));
					Array_dot.insert(dot.first);
					Array_dot.insert(dot.second);
				}
			}
			for (unsigned int j = 0; j < Array_cycle.size() - 1; j++)
			{
				if (c.cycle_cycel_pos(Array_cycle.at(j)))
				{
					pair<pair<double, double>, pair<double, double>> dot = c.cycle_cycle_instere(Array_cycle.at(j));
					Array_dot.insert(dot.first);
					Array_dot.insert(dot.second);
				}
			}
		}
	}
	out << Array_dot.size() << endl;
	
}


