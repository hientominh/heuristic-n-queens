#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

pair<vector<int>,int> data;
int n;
double T;

int C(int n) {
    if(n < 2){
        return 0;
    }
    if(n == 2) {
        return 1;
    }
    return (n - 1) * n / 2;
}

void init() {
    cout << "Input n = ";
    cin >> n;
    T = n;
    srand(time(0));
    for(int i = 0; i < n; i++) {
        data.first.push_back(i);
    }
    random_shuffle(data.first.begin(), data.first.end());
    int result = 0;
    for(int i = 0 ; i < n - 1; i++) {
        for(int j = i + 1 ; j < n; j++){
            if(j - i == data.first[j] - data.first[i] || data.first[i] + i == data.first[j] + j){
                result++;
            }
        }
    }
    data.second = result;
}

int heuristic(pair<vector<int>,int> data) {
    int result = 0;
    int n = data.first.size();
    int *temp1, * temp2;
    temp1 = new int[n];
    temp2 = new int[n];
    for(int i = 0; i < n; i++) {
        temp1[i] = data.first[i] + i;
        temp2[i] = data.first[i] - i;
    }
    sort(temp1, temp1 + n);
    sort(temp2, temp2 + n);
    int i = 0;
    while(i < n-1) {
        int j = i + 1;
        int count = 1;
        while(temp1[i] == temp1[j]) {
            j++;
            count++;
        }
        result += C(count);
        i = j;
        if(j >= n) {
            break;
        }
    }
    i = 0;
    while(i < n-1) {
        int j = i + 1;
        int count = 1;
        while (temp2[i] == temp2[j]) {
            j++;
            count++;
        }
        result += C(count);
        i = j;
        if (j >= n) {
            break;
        }
    }
    delete(temp1);
    delete(temp2);
    return result;
}

void show(pair<vector<int>,int> data) {
    for(int i = 0; i < n; i++) {
        cout << data.first[i] << " ";
    }
}

void solve() {
    bool stop = false;
    srand(time(0));
    double p;
    int step = 0;
    while(T > 0) {
        if(data.second == 0){
            stop = true;
            show(data);
            break;
        }
        T *= 0.99;
        pair<vector<int>, int> next_move = data;
        swap(next_move.first[rand()%n], next_move.first[random()%n]);
        next_move.second = heuristic(next_move);
        if(next_move.second == 0) {
            stop = true;
            cout << next_move.second << endl;
            cout << "Steps: " << step << endl;
            cout << "Result: ";
            show(next_move);
            break;
        }
        int delta = next_move.second - data.second;
        if(delta < 0) {
            data = next_move;
            step++;
            cout << next_move.second << endl;
        }
        else {
            p = exp(-delta/double(T));
            if(rand()/double(RAND_MAX) < p){
                data = next_move;
                step++;
                cout << next_move.second << endl;
            }
        }
    }
    if(stop != true) {
        cout << "Failed!";
    }
}

int main() {
    clock_t start = clock();
    init();
    cout << "The first value of heuristic: " << data.second << endl;
    solve();
    clock_t  finish = clock();
    cout << endl << "Time running: " << finish - start << " micro seconds" << endl;
    return 0;
}
