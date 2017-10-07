//
//  main.cpp
//  density-control-io
//
//  Created by sphota on 10/6/17.
//  Copyright © 2017 Intellex. All rights reserved.
//

#include <iostream>
#include "Calibrator.hpp"

int main(int argc, const char * argv[]) {

    // we use indeces as addresses, so the type is 'int'
    std::vector<int> v = {1, 2, 3,
                         11, 13,
                         19,
                         28, 29};
    
    /* page sizes */
    std::vector<int> d = {3, 2, 1, 2};
    
    // we use indeces as addresses, so the type is 'int'
    std::vector<int> v1 = {1, 2, 3, 4, 7, 9,
        11, 13, 17, 13,
        19, 25,
        28, 29, 30, 31, 32, 39};
    
    /* page sizes */
    std::vector<int> d1 = {6, 4, 2, 6};
    
    /* N = 8, M = 4, D = 6 */
    Calibrator<int, int> calibrator = Calibrator<int, int>(v, 8, 4, d, 3);
    calibrator.build();
    return 0;
}
