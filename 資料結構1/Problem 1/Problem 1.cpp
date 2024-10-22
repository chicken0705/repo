#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <chrono>  // 引入 chrono 庫來計算時間

using namespace std;
using namespace std::chrono;  // 使用 chrono 命名空間

long long recur_count = 0;  // 計數遞迴次數
long long nonr_count = 0;   // 計數非遞迴步驟數

// 遞迴版本
int recur(int m, int n) {
    recur_count++;  // 每次遞迴計數器 +1
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return recur(m - 1, 1);
    else
        return recur(m - 1, recur(m, n - 1));
}

// 非遞迴版本
int nonr(int m, int n) {
    int* index = new int[m + 1];
    int* value = new int[m + 1];
    index[0] = 0;
    value[0] = 1;

    for (int i = 1; i <= m; i++) {
        index[i] = -1;
        value[i] = 1;
    }

    while (index[m] != n) {
        nonr_count++;  // 每次非遞迴步驟數計數器 +1
        index[0] = value[1];
        value[0] = index[0] + 1;
        int i = 1;

        while (value[i] == index[i - 1] && i <= m) {
            index[i] = index[i] + 1;
            value[i] = value[i - 1];
            i++;
        }
    }
    int result = value[m];
    delete[] index;
    delete[] value;
    return result;
}

int main() {
    int m, n;

    while (true) {
        cout << "請輸入兩個整數 m 和 n: ";
        cin >> m >> n;

        if (cin.fail()) {
            cout << "沒有" << endl;
            cin.clear();  // 清除錯誤狀態
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // 忽略不合法輸入
            continue;
        }

        // 重置計數器
        recur_count = 0;
        nonr_count = 0;

        // 計算遞迴版本的結果並測量時間
        auto start_recur = high_resolution_clock::now();
        int recur_result = recur(m, n);
        auto end_recur = high_resolution_clock::now();
        auto duration_recur = duration_cast<microseconds>(end_recur - start_recur);

        // 輸出遞迴結果與計數
        cout << "Recursive: " << recur_result << endl;
        cout << "遞迴版本執行的遞迴次數: " << recur_count << endl;
        cout << "遞迴版本運行時間: " << duration_recur.count() << " 微秒" << endl;

        // 計算非遞迴版本的結果並測量時間
        auto start_nonr = high_resolution_clock::now();
        int nonr_result = nonr(m, n);
        auto end_nonr = high_resolution_clock::now();
        auto duration_nonr = duration_cast<microseconds>(end_nonr - start_nonr);

        // 輸出非遞迴結果與計數
        cout << "Nonrecursive: " << nonr_result << endl;
        cout << "非遞迴版本執行的步驟數: " << nonr_count << endl;
        cout << "非遞迴版本運行時間: " << duration_nonr.count() << " 微秒" << endl;

        cout << "=====================" << endl;
    }
}
