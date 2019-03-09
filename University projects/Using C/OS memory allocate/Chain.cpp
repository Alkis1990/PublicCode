#include "Chain.h"

#include <iostream>

using namespace std;

void Chain::make(int min, int max) {
    number_of_buckets = 0;
    bucket = NULL;
    
    this->min = min;
    this->max = max;
    number_of_bits = (4096/max);
    number_of_bytes = number_of_bits/8;
    
    if (number_of_bytes == 0) {
        number_of_bytes = 1;
    }
    
    cout << "Chain created from " << min << " to " << max << " (" << number_of_bits << " bits)" << endl;
}
