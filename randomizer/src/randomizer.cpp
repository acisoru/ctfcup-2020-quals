#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <fstream>

using namespace std;

#define N 15000

int randint(double p){
	int res = 0;
	if (!(0 <= p && p <= 1)){
		cout << "Error!" << endl;
		exit(1);
	} 
    for (int i = 0; i < N; i++){
        int tmp = rand() % 1000;
        if (tmp < p * 1000)
            res++;
    }
    return res;
}

int n = 1;

int crand(){
	n = n * 214013 + 2531011;
	return (n >> 16) & 0x7fff;
}

void csrand(int seed){
	n = seed;
}

int main(){
	srand(time(0));
	csrand(0x628c540a);

	string pass;
	cout << "Enter your data: ";
	cin >> pass;
	vector<int> data;
	for (int i = 0; i < pass.length(); i++){
		data.push_back((int)pass[i]);
	}
	for (int i = 0; i < data.size(); i++){
		double n = (double)(crand() % 1000)/1000;
		data[i] *= 1000;
		data[i] -= randint(n);
		for (int j = 0; j < 3; j++){
			data[i] += randint(n);
			data[i] -= randint(n);
		}
	}
	cout << "Data randomized. Enter file name to save it: ";
	string filename;
	cin >> filename;

	ofstream file;
	file.open(filename);
	if (file.is_open()){
		for (int i = 0; i < data.size(); i++){
			file << data[i] << " ";
		}
	} else {
		cout << "Error!" << endl;
	}
	file.close();
	return 0;
}
