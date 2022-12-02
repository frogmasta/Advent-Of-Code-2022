/**
 * @file heap.cpp
 * @author Eric Roth
 * @brief 
 * @version 0.1
 * @date 2022-12-01
 * 
 * @copyright Copyright (c) 2022
 */

#include "heap.h"

/**
 * @brief Construct a new Heap object with specified priority function.
 * 
 * @param priority_func priority function
 */
template <typename T>
Heap<T>::Heap(std::function<bool(T, T)> priority_func) {
    higherPriority = priority_func;
    heap = std::vector<T>();
}

/**
 * @brief Return the index of the parent
 * 
 * @param idx index of child
 * @return size_t index of parent
 */
template <typename T>
size_t Heap<T>::parent(size_t idx) const {
    return (idx - 1) / 2;
}

/**
 * @brief Checks whether the index has a parent
 * 
 * @param idx index of child
 * @return bool whether the child has a parent or not
 */
template <typename T>
bool Heap<T>::hasParent(size_t idx) const {
    return (idx > 0);
}

/**
 * @brief Returns the index of the left child.
 * 
 * @param idx index of parent
 * @return size_t index of left child
 */
template <typename T>
size_t Heap<T>::leftChild(size_t idx) const {
    return idx * 2 + 1;
}

/**
 * @brief Returns the index of the right child.
 * 
 * @param idx index of parent
 * @return size_t index of right child
 */
template <typename T>
size_t Heap<T>::rightChild(size_t idx) const {
    return 2 * (idx + 1);
}

/**
 * @brief Returns if the parent has a child
 * 
 * @param idx index of the parent
 * @return bool whether it has a child or not
 */
template <typename T>
bool Heap<T>::hasChild(size_t idx) const {
    size_t left_child = leftChild(idx);

    if (left_child >= heap.size()) return false;
    return true;
}

/**
 * @brief Returns max priority child.
 * 
 * @param idx index of parent
 * @return size_t index of its maximum priority child
 */
template <typename T>
size_t Heap<T>::maxPriorityChild(size_t idx) const {
    if (!hasChild(idx)) return -1;

    size_t left_child = leftChild(idx);
    size_t right_child = rightChild(idx);

    if (right_child >= heap.size()) return left_child;

    if (higherPriority(heap.at(left_child), heap.at(right_child))) return left_child;
    else return right_child;
}

/**
 * @brief Implementation of heapify down
 * 
 * @param idx index to heapifydown
 */
template <typename T>
void Heap<T>::heapifyDown(size_t idx) {
    if (!hasChild(idx)) return;

    size_t max_child = maxPriorityChild(idx);
    if (higherPriority(heap.at(max_child), heap.at(idx))) {
        iter_swap(heap.begin() + max_child, heap.begin() + idx);
        heapifyDown(max_child);
    }
}

/**
 * @brief Implementation of heapify up
 * 
 * @param idx index to heapify up
 */
template <typename T>
void Heap<T>::heapifyUp(size_t idx) {
    if (!hasParent(idx)) return;

    size_t parent_idx = parent(idx);
    if (higherPriority(heap.at(idx), heap.at(parent_idx))) {
        iter_swap(heap.begin() + idx, heap.begin() + parent_idx);
        heapifyUp(parent_idx);
    }
}

/**
 * @brief Returns top element on the heap.
 * 
 * @return T top element on the heap
 */
template <typename T>
T Heap<T>::peek() const {
    if (!heap.empty()) return heap[0];
    return {};
}

/**
 * @brief Inserts given element into the heap
 * 
 * @param elem element to insert
 */
template <typename T>
void Heap<T>::insert(T elem) {
    heap.push_back(elem);
    heapifyUp(heap.size() - 1);
}

/**
 * @brief Remove top element from the PQ
 * 
 * @return T max priority element
 */
template <typename T>
T Heap<T>::remove() {
    T out = peek();

    iter_swap(heap.begin(), heap.end() - 1);
    heap.pop_back();
    if (heap.size() >= 1) heapifyDown(0);
    
    return out;
}