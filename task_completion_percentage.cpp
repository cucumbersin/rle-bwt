#include "task_completion_percentage.h"
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;

void backspace(int count) {
    for (int i = 0; i < count; i++)
        printf_s("\b \b");
}

void completion_percentage(double completed_parts, double total_parts) {
    static int prev_size = 0;
    backspace(prev_size);
    double buf = (completed_parts / (total_parts - 1)) * 100;
    string str = to_string(buf);
    cout << str << '%';
    prev_size = str.size() + 1;
}