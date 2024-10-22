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
#include <chrono>  // �ޤJ chrono �w�ӭp��ɶ�

using namespace std;
using namespace std::chrono;  // �ϥ� chrono �R�W�Ŷ�

long long recur_count = 0;  // �p�ƻ��j����
long long nonr_count = 0;   // �p�ƫD���j�B�J��

// ���j����
int recur(int m, int n) {
    recur_count++;  // �C�����j�p�ƾ� +1
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return recur(m - 1, 1);
    else
        return recur(m - 1, recur(m, n - 1));
}

// �D���j����
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
        nonr_count++;  // �C���D���j�B�J�ƭp�ƾ� +1
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
        cout << "�п�J��Ӿ�� m �M n: ";
        cin >> m >> n;

        if (cin.fail()) {
            cout << "�S��" << endl;
            cin.clear();  // �M�����~���A
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // �������X�k��J
            continue;
        }

        // ���m�p�ƾ�
        recur_count = 0;
        nonr_count = 0;

        // �p�⻼�j���������G�ô��q�ɶ�
        auto start_recur = high_resolution_clock::now();
        int recur_result = recur(m, n);
        auto end_recur = high_resolution_clock::now();
        auto duration_recur = duration_cast<microseconds>(end_recur - start_recur);

        // ��X���j���G�P�p��
        cout << "Recursive: " << recur_result << endl;
        cout << "���j�������檺���j����: " << recur_count << endl;
        cout << "���j�����B��ɶ�: " << duration_recur.count() << " �L��" << endl;

        // �p��D���j���������G�ô��q�ɶ�
        auto start_nonr = high_resolution_clock::now();
        int nonr_result = nonr(m, n);
        auto end_nonr = high_resolution_clock::now();
        auto duration_nonr = duration_cast<microseconds>(end_nonr - start_nonr);

        // ��X�D���j���G�P�p��
        cout << "Nonrecursive: " << nonr_result << endl;
        cout << "�D���j�������檺�B�J��: " << nonr_count << endl;
        cout << "�D���j�����B��ɶ�: " << duration_nonr.count() << " �L��" << endl;

        cout << "=====================" << endl;
    }
}
