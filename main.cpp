#include<iostream>
#include<fstream>
#include<vector>
#include<array>
#include<algorithm>
#include<string>
#include<cmath>
#include<sstream>
#include<set>

using namespace std;
#define N 70
#define N_ 123
#define pi 3.1415926535898
array<long long int, 65536> All_amount;
struct coordinate
{
	double x;
	double y;
	int up;
	int down;
	double down_distance;
	double up_distance;
	double weight;
};
struct unit_dis
{
	string name1;
	string name2;
	double distance;

};
struct element
{
	int port;
	int amount;
	bool operator == (const int obj)
	{
		return port == obj;
	}
};
bool cmp(const element&A, const element&B)
{
	return A.amount > B.amount;
}
bool cmp_dis(const unit_dis&A, const unit_dis&B)
{
	return A.distance > B.distance;
}


int init_amount(string &PathName)
{
	ifstream file;

	file.open(PathName);
	if (!file)
	{
		return -1;
	}
	int amount = 0;
	int i = 0;
	while (i < 65536)
	{
		file >> amount;
		file >> amount;
		All_amount[i] += amount;
		++i;
	}
	file.close();
	return 1;
}
void algorithm(const array<int, N_>&Top_n, const string&pathname)
{
	//const int t_num = num;
	array<long long, N_ + 1> ma;
	ma[0] = 0;
	for (int i = 1; i <=N_; ++i)
	{
		ma[i] = All_amount[Top_n[i - 1]];
		All_amount[Top_n[i - 1]] = 0;
	}
	for (int i = 0; i < 65536; ++i)
	{
		ma[0] += All_amount[i];
	}

	array<long long, N_ + 1> m;
	ofstream file(pathname);

	if (!file)
	{
		cout << "cannot open!" << endl;
		return;
	}
	int S = N_+ 1;

	vector<coordinate>temp;
	while (S != 0)
	{////原代码
		/*for (int i = 0; i < S; ++i)
		{
			m[i] = ma[S - i - 1];
		}*/
		if (S == N_ + 1)
			for (int i = 0; i < S; ++i)
			{
				m[i] = ma[S - i - 1];
			}
		else
		{
			m[S - 1] = m[S] + m[0];
			for (int i = 0; i < S - 1; ++i)
			{
				m[i] = ma[S - i - 1];
			}
		}

		coordinate coo;
		coo.x = 0.0; coo.y = 0.0;
		long long M = 0;
		double sum_cos = 0.0, sum_sin = 0.0;
		for (int i = 0; i < S; ++i)
		{
			M += m[i];
			sum_cos += (double)m[i] * cos(2.0 * pi*(double)i / (double)S);
			sum_sin += (double)m[i] * sin(2.0 * pi*(double)i / (double)S);
		}

		coo.x = (double)S*sin(pi / (double)S) * sum_cos / (double)M;
		coo.y = (double)S*sin(pi / (double)S) * sum_sin / (double)M;
		temp.push_back(coo);
		--S;

	}
	for (int i = 0; i < temp.size(); ++i)
	{
		file << temp[i].x << '\t' << temp[i].y << endl;
	}
	file.close();
}
void top(array<element, 65536> &A, set<int>&setq)// const string&filename)
{
	//ifstream file(filename);
	//if (!file)
	//	return;
	sort(A.begin(), A.end(), cmp);
	for (int i = 0; i < N; ++i)
	{
		//	cout << A[i].port << " ";
			//if(!find(set(A[i]))
		setq.insert(A[i].port);
	}
}
void top_n(array<int, N_>& Top_n)
{
	ofstream file("top_n.txt");
	if (!file)
		exit(-1);
	array<element, N_>A;	
	for (int i = 0; i < N_; ++i)
	{
		A[i].amount = All_amount[Top_n[i]];
		A[i].port = Top_n[i];
	}
	sort(A.begin(), A.end(),cmp);
	for (int i = 1; i <= N_; ++i)
	{
		file << A[i-1].port <<" ";
		if (i % 5 == 0)
			file << endl;
	}
	file.close();
}
double distance(const coordinate&S, const coordinate&m)
{
	return sqrt((S.x - m.x)*(S.x - m.x) + (S.y - m.y)*(S.y - m.y));
}
int read(array<coordinate, N_ + 1>&A, const string&path)
{
	ifstream file(path);
	if (!file)
	{
		return -1;
	}
	for (int i = 0; i < N_ + 1; ++i)
		file >> A[i].x >> A[i].y;
	file.close();
	return 1;
}
void main()
{
	int name_ = 1221;
	string p_;
	ifstream file_top("top_n.txt");
	array<int, N_>top;
	for (int i = 0; i < N_; ++i)
		file_top >> top[i];
	file_top.close();
	while (name_ < 1228)
	{
		for (int i = 0;i<65536; ++i)
			All_amount[i] = 0;
		stringstream ss;
		ss << name_;
		ss >> p_;
		string filename = ".\\1221-1227_\\" + p_ + "\\4211212550.txt";
		init_amount(filename);
		ofstream file(".\\550\\" + p_ + ".txt");
		array<long long, N_ + 1> ma;
		ma[0] = 0;
		for (int i = 0; i < N_; ++i)
		{
			ma[i + 1] = All_amount[top[i]];
			All_amount[top[i]] = 0;
		}
		for (int i = 0; i < 65536; ++i)
			ma[0] += All_amount[i];
		for (int i = 0; i <= N_; ++i)
			file <<ma[i]<< endl;
		file.close();
		++name_;
	}

	//array<long long, N_ + 1> ma;
	//ifstream file_init("total_topn_amount.txt");
	//for (int i = 0; i <= N_; ++i)
	//	file_init >> ma[i];
	//file_init.close();
	//array<long long, N_ + 1> m;
	//ofstream file("total_coor.txt");

	//if (!file)
	//{
	//	cout << "cannot open!" << endl;
	//	return;
	//}
	//int S = N_ + 1;

	//vector<coordinate>temp;
	//while (S != 0)
	//{////原代码
	//	/*for (int i = 0; i < S; ++i)
	//	{
	//		m[i] = ma[S - i - 1];
	//	}*/
	//	if (S == N_ + 1)
	//		for (int i = 0; i < S; ++i)
	//		{
	//			m[i] = ma[S - i - 1];
	//		}
	//	else
	//	{
	//		m[S - 1] = m[S] + m[0];
	//		for (int i = 0; i < S - 1; ++i)
	//		{
	//			m[i] = ma[S - i - 1];
	//		}

	//	}

	//	coordinate coo;
	//	coo.x = 0.0; coo.y = 0.0;
	//	long long M = 0;
	//	double sum_cos = 0.0, sum_sin = 0.0;
	//	for (int i = 0; i < S; ++i)
	//	{
	//		M += m[i];
	//		sum_cos += (double)m[i] * cos(2.0 * pi*(double)i / (double)S);
	//		sum_sin += (double)m[i] * sin(2.0 * pi*(double)i / (double)S);
	//	}

	//	coo.x = (double)S*sin(pi / (double)S) * sum_cos / (double)M;
	//	coo.y = (double)S*sin(pi / (double)S) * sum_sin / (double)M;
	//	temp.push_back(coo);
	//	--S;

	//}
	//for (int i = 0; i < temp.size(); ++i)
	//{
	//	file << temp[i].x << '\t' << temp[i].y << endl;
	//}
	//file.close();
}

