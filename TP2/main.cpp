#include <iostream>
#include <vector>

int max(int a, int b, int c) { return std::max(std::max(a, b), c); }

std::vector<int> maxCrossingSum(std::vector<int> arr, int l, int m, int h) {
    int sum = 0;
    int left_sum = INT_MIN;
    int left_index = m;
    for (int i = m; i >= l; i--) {
        sum = sum + arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            left_index = i;
        }
    }

    sum = 0;
    int right_sum = INT_MIN;
    int right_index = m;
    for (int i = m; i <= h; i++) {
        sum = sum + arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            right_index = i;
        }
    }

    int middle_sum = left_sum + right_sum - arr[m];
    int bigger = max(middle_sum, left_sum, right_sum);
    std::vector<int> indexes;
    if (bigger == middle_sum) {
        indexes = { left_index, right_index, middle_sum };
    } else if (bigger == left_sum) {
        indexes = { left_index, m, left_sum };
    } else {
        indexes = { m , right_index, right_sum };
    }
    return indexes;
}

std::vector<int> maxSubArraySum(std::vector<int> arr, int l, int h) {
    if (l > h) {
        std::vector<int> indexes = { l, h, INT_MIN };
        return indexes;
    }

    if (l == h) {
        std::vector<int> indexes = { l, h, arr[l] };
        return indexes;
    }

    int m = (l + h) / 2;

    std::vector<int> left = maxSubArraySum(arr, l, m - 1);
    std::vector<int> right = maxSubArraySum(arr, m + 1, h);
    std::vector<int> middle = maxCrossingSum(arr, l, m, h);
    int bigger = max(middle[2], left[2], right[2]);

    if (bigger == middle[2]) {
        return middle;
    } else if (bigger == left[2]) {
        return left;
    } else {
        return right;
    }
}

int main() {
    int a = 0, s = 0;

    std::cin >> a >> s;
    while (a > 0 && s > 0) {
        std::vector<int> arr = std::vector<int>(s, 0);
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < s; ++j) {
                int num = 0;
                std::cin >> num;
                arr[j] += num;
            }
        }

        std::vector<int> max_sum = maxSubArraySum(arr, 0, (arr.size()) - 1);
        printf("Left index is %d\n", max_sum[0] + 1);
        printf("Right index is %d\n", max_sum[1] + 1);
        printf("Maximum contiguous sum is %d\n", max_sum[2]);
    }

    return 0;
}
