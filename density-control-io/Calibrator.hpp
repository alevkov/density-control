//
//  Calibrator.hpp
//  density-control-io
//
//  Created by sphota on 10/6/17.
//  Copyright © 2017 Intellex. All rights reserved.
//

#ifndef Calibrator_hpp
#define Calibrator_hpp

#include <stdio.h>
#include "includes.h"

template <typename T>
class CNode
{
 public:
    uint density;
    std::pair<T, T> addr_range;
    std::shared_ptr<CNode> left, right;
    CNode(uint d) : density(d), left(nullptr), right(nullptr) {}
};

template <typename T>
class Calibrator
{
    
private:
    
    int __size;
    int __page_count;
    int __max_page_size;
    std::vector<int> __sizes_of_pages;
    std::vector<T> __data;
    std::shared_ptr<CNode<T>> __root = nullptr;
    
    int __density_of_range(std::pair<T, T> addr_range);
    void __build_ctree_internal(std::shared_ptr<CNode<T>> __root);
    void __build_ctree();
    
public:
    
    Calibrator
    (std::vector<T> & set, const int & N, int M, std::vector<int> & d, int D) :
    __data(set),
    __size(N),
    __page_count(M),
    __max_page_size(D),
    __sizes_of_pages(d) { __build_ctree(); }
    
    inline std::shared_ptr<CNode<T>> get_root() { return __root; };
    void balance();
};

template <typename T>
int Calibrator<T>::__density_of_range(std::pair<T, T> range)
{
    int density = -1;
    if (range.first == range.second) {
        return __sizes_of_pages[range.first];
    }
    
    int i = range.first;
    int sum = 0;
    for (; i <= range.second; ++i) {
        sum += __sizes_of_pages[i];
    }
    density = sum / i;
    return density;
}

template <typename T>
void Calibrator<T>::__build_ctree()
{
    std::pair<T, T> root_range = {0, __page_count - 1};
    if (!__root) {
        int density = __density_of_range(root_range);
        std::cout << density << std::endl;
        __root = std::make_shared<CNode<T>>(density);
        __root->addr_range = root_range;
    }
    __build_ctree_internal(__root);
}

template <typename T>
void Calibrator<T>::__build_ctree_internal(std::shared_ptr<CNode<T>> __root)
{
    if (__root->addr_range.first == __root->addr_range.second) {
        __root->density = __density_of_range(__root->addr_range);
        return;
    }
    
    std::shared_ptr<CNode<T>> right_child = std::make_shared<CNode<T>>(-1),
                              left_child = std::make_shared<CNode<T>>(-1);
    
    right_child->addr_range.first = __root->addr_range.first;
    right_child->addr_range.second = (__root->addr_range.first + __root->addr_range.second) / 2;
    right_child->density = __density_of_range(right_child->addr_range);
    __build_ctree_internal(right_child);
    
    left_child->addr_range.first = ((__root->addr_range.first + __root->addr_range.second) / 2) + 1;
    left_child->addr_range.second = __root->addr_range.second;
    left_child->density = __density_of_range(left_child->addr_range);
    __build_ctree_internal(left_child);
}

#endif /* Calibrator_hpp */
