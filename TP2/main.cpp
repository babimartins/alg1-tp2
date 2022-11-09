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
    int friends_num = 0, concerts_num = 0;

    std::cin >> friends_num >> concerts_num;
    while (friends_num > 0 && concerts_num > 0) {
        std::vector<double> concerts_rates = std::vector<double>(concerts_num, 0);
        for (int i = 0; i < friends_num; ++i) {
            for (int j = 0; j < concerts_num; ++j) {
                double rate = 0;
                std::cin >> rate;
                concerts_rates[j] += rate;
            }
        }

        Concerts max_sum = maxSubArraySum(concerts_rates, 0, (concerts_rates.size()) - 1);
        std::cout << max_sum.left_index + 1 << " " << max_sum.right_index + 1 << std::endl;
        std::cin >> friends_num >> concerts_num;
    }

    return 0;
}
