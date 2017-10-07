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
    std::vector<int> v = {1, 2, 3, 4, 7, 9,
                         11, 13, 17, 13,
                         19, 25,
                         28, 29, 30, 31, 32, 39};
    
    std::vector<int> d = {6, 4, 2, 6};
    
    Calibrator<int> calibrator = Calibrator<int>(v, 18, 4, d, 6);
    return 0;
}
