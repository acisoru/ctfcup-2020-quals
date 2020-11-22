#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

#define N 15000

using namespace std;

double expected(double p){
    return p * N;
}

int n = 1;

int r(){
    n = n * 214013 + 2531011;
    return (n >> 16) & 0x7fff;
}

void s(int seed){
    n = seed;
}

int main(int argc, char *argv[]){
	if (argc != 2){
		cout << "Usage:\n./solver <filename>" << endl;
		exit(1);
	}
	s(0x628c540a);
	ifstream in(argv[1], ios::in);

	vector<int> data;
	int number;
	while (in >> number){
		data.push_back(number);
	}
	in.close();

    cout << "\nData: ";
    for (int i = 0; i < data.size(); i++){
        cout << data[i] << " ";
    }
    cout << "\nExpected: ";
    vector<int> e;
    for (int i = 0; i < data.size(); i++){
        int tmp = (int)expected((double)(r() % 1000)/1000);
        e.push_back(tmp);
        cout << tmp << " ";
    }
    cout << "\nData + expected: ";
    for (int i = 0; i < data.size(); i++){
        cout << data[i] + e[i] << " ";
    }
    cout << "\nSource text: ";
    for (int i = 0; i < data.size(); i++){
        cout << (char)round((double)(data[i] + e[i])/1000);
    }
    cout << endl;
	return 0;
}
