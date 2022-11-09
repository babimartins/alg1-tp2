#include <iostream>
#include <vector>
#include "concerts.hpp"
#include "max_sum.hpp"

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
