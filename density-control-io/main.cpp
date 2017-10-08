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

    std::vector<int> v = {1, 2, 3,
                         11, 13,
                         19,
                         28, 29};
    /* page sizes */
    std::vector<int> d = {3, 2, 1, 2};
    int D = 3;
    
    /* we use indeces as addresses, so the type is 'int' */
    std::vector<int> v1 = {1, 2, 3, 4, 7, 9,
        11, 13, 17, 13,
        19, 25,
        28, 29, 30, 31, 32, 39};
    std::vector<int> d1 = {6, 4, 2, 6};
    int D1 = 6;
    
    /**
     D - d = 1 (minimum page size)
     2 + 0
     2 + (1 + 1 - 1)(1) = 3
     2 + (2 + 1 - 1)(1) = 4
     */
    
    std::vector<int> file = v;
    std::vector<int> page_sizes = d;
    int max_per_page = D;
    
    Calibrator<int, int> calibrator = Calibrator<int, int>(file, (int)file.size(), (int)page_sizes.size(), page_sizes, max_per_page);
    calibrator.build();
    
    return 0;
}
