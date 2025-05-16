#include <cstdio>
#include <algorithm>
#include <cstring>
#include <random>
#include <chrono>
using namespace std;
mt19937 rng(chrono::system_clock::now().time_since_epoch().count());
// shuffle(begin, end, rng)
// normal_distribution<double> N_distr(mean, std)
typedef pair<int, int> pr;
typedef long long ll;
const int MAXN=2e5+5;
int n;
int K, _K;  // sub, subsub
int _n;
inline void file_op(){
	static char cmd[100];
	sprintf(cmd, "data/name%d-%d.in", K, _K); // change the name;
	freopen(cmd, "w", stdout);
}

void Print(){
	fclose(stdout);
	return ;
}

void Gen1(){
	n = _n;
	return ;
}

void Sub1(){
	_n=18;
	K++;  //K=1;
	for(_K=1; _K<=10; _K++){
		file_op();
		Gen1();
		Print();
	}
	return ;
}

int main(){
	Sub1();
	return 0;
}
