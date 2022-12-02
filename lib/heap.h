/**
 * @file heap.h
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 */
#pragma once 

#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

/**
 * Simple Heap data structure implemented for Advent of Code.
 */
template <typename T>
class Heap {
    public:
        Heap(std::function<bool(T, T)> priority_func);

        T peek() const;
        void insert(T elem);
        T remove();
    private:
        std::function<bool(T, T)> higherPriority;
        std::vector<T> heap;

        size_t parent(size_t idx) const;
        bool hasParent(size_t idx) const;
        size_t leftChild(size_t idx) const;
        size_t rightChild(size_t idx) const;
        bool hasChild(size_t idx) const;
        size_t maxPriorityChild(size_t idx) const;

        void heapifyDown(size_t idx);
        void heapifyUp(size_t idx);
};

#include "heap.tpp" 