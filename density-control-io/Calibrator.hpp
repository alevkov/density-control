//
//  Calibrator.hpp
//  density-control-io
//
//  Created by sphota on 10/6/17.
//  Copyright © 2017 Intellex. All rights reserved.
//

#ifndef Calibrator_hpp
#define Calibrator_hpp

#include "includes.h"

template <typename T>
class CNode
{
 public:
    float density;
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
    
    float __density_of_range(std::pair<T, T> addr_range);
    void __build_ctree_internal(std::shared_ptr<CNode<T>> __root);
    void __build_ctree();
    
public:
    
    /* ctor */
    Calibrator
    (std::vector<T> & set, const int & N, int M, std::vector<int> & d, int D) :
    __data(set),
    __size(N),
    __page_count(M),
    __max_page_size(D),
    __sizes_of_pages(d) { }
    
    inline std::shared_ptr<CNode<T>> get_root() { return __root; };
    void build();
    void balance();
};

# pragma mark - public

template<typename T>
void Calibrator<T>::build()
{
    __build_ctree();
}

#pragma mark - private

template <typename T>
float Calibrator<T>::__density_of_range(std::pair<T, T> range)
{
    float density = -1.0;
    if (range.first == range.second) {
        return __sizes_of_pages[range.first];
    }
    
    int i = range.first;
    int sum = 0;
    int count = 0;
    for (; i <= range.second; i++) {
        count++;
        sum += __sizes_of_pages[i];
    }
    
    density = (float)sum / (float)count;
    return density;
}

template <typename T>
void Calibrator<T>::__build_ctree()
{
    std::pair<T, T> root_range = {0, __page_count - 1};
    if (!__root) {
        float density = __density_of_range(root_range);
        std::cout << density << std::endl;
        __root = std::make_shared<CNode<T>>(density);
        __root->addr_range = root_range;
    }
    __build_ctree_internal(__root);
}

template <typename T>
void Calibrator<T>::__build_ctree_internal(std::shared_ptr<CNode<T>> __root)
{
    if (__root->addr_range.first == __root->addr_range.second)
        return;
    
    std::shared_ptr<CNode<T>>
    right_child = std::make_shared<CNode<T>>(-1),
    left_child = std::make_shared<CNode<T>>(-1);
    
    left_child->addr_range.first = __root->addr_range.first;
    left_child->addr_range.second = (__root->addr_range.first + __root->addr_range.second) / 2;
    left_child->density = __density_of_range(left_child->addr_range);
    __root->left = left_child;
    
    right_child->addr_range.first = ((__root->addr_range.first + __root->addr_range.second) / 2) + 1;
    right_child->addr_range.second = __root->addr_range.second;
    right_child->density = __density_of_range(right_child->addr_range);
    __root->right = right_child;
    
    __build_ctree_internal(__root->left);
    __build_ctree_internal(__root->right);
}


#endif /* Calibrator_hpp */
