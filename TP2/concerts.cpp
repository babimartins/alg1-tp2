#include "concerts.hpp"

Concerts::Concerts() {
    left_index = 0;
    right_index = 0;
    sum = 0;
}

Concerts::Concerts(int l, int r, double s) {
    left_index = l;
    right_index = r;
    sum = s;
}
