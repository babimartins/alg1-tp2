#include <iostream>
#include <vector>
#include "concerts.hpp"

double max(double a, double b, double c) { return std::max(std::max(a, b), c); }

Concerts maxCrossingSum(std::vector<double> arr, int l, int m, int h) {
    double sum = 0;
    double left_sum = INT_MIN;
    int left_index = m;
    for (int i = m; i >= l; i--) {
        sum = sum + arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            left_index = i;
        }
    }

    sum = 0;
    double right_sum = INT_MIN;
    int right_index = m;
    for (int i = m; i <= h; i++) {
        sum = sum + arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            right_index = i;
        }
    }

    double middle_sum = left_sum + right_sum - arr[m];
    double bigger = max(middle_sum, left_sum, right_sum);
    Concerts concerts;
    if (bigger == middle_sum) {
        concerts = { left_index, right_index, middle_sum };
    } else if (bigger == left_sum) {
        concerts = { left_index, m, left_sum };
    } else {
        concerts = { m , right_index, right_sum };
    }
    return concerts;
}

Concerts maxSubArraySum(std::vector<double> arr, int l, int r) {
    if (l > r) {
        Concerts concerts = {l, r, INT_MIN };
        return concerts;
    }

    if (l == r) {
        Concerts concerts = {l, r, arr[l] };
        return concerts;
    }

    int m = (l + r) / 2;

    Concerts left = maxSubArraySum(arr, l, m - 1);
    Concerts right = maxSubArraySum(arr, m + 1, r);
    Concerts middle = maxCrossingSum(arr, l, m, r);
    double bigger = max(middle.sum, left.sum, right.sum);

    if (bigger == middle.sum) {
        return middle;
    } else if (bigger == left.sum) {
        return left;
    } else {
        return right;
    }
}

int main() {
    int a = 0, s = 0;

    std::cin >> a >> s;
    while (a > 0 && s > 0) {
        std::vector<double> arr = std::vector<double>(s, 0);
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < s; ++j) {
                double num = 0;
                std::cin >> num;
                arr[j] += num;
            }
        }

        Concerts max_sum = maxSubArraySum(arr, 0, (arr.size()) - 1);
        printf("Left index is %d\n", max_sum.left_index + 1);
        printf("Right index is %d\n", max_sum.right_index + 1);
        printf("Maximum contiguous sum is %d\n", max_sum.sum);
        std::cin >> a >> s;
    }

    return 0;
}
