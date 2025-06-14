#include <utility>
#include <stdexcept>
#include <iostream>
#pragma once

template <typename T>
class MyVector {
	static constexpr size_t INITIAL_CAPACITY = 8;

	T* data = nullptr;
	size_t capacity = 0;
	size_t size = 0;

	void copyFrom(const MyVector<T>& other);
	void free();
	void moveFrom(MyVector<T>&& other);
	void resize(size_t newCapacity);

public:
	MyVector();
	MyVector(size_t n);
	MyVector(size_t n, const T& elem);
	MyVector(const MyVector<T>& other);
	MyVector(MyVector<T>&& other) noexcept;
	MyVector<T>& operator=(const MyVector<T>& other);
	MyVector<T>& operator=(MyVector<T>&& other) noexcept;
	~MyVector();

	void push_back(const T& elem);
	void push_back(T&& elem);
	void pop_back();
	void insert(size_t idx, const T& elem);
	void insert(size_t idx, T&& elem);
	void erase(size_t idx);

	T& operator[](size_t idx);
	const T& operator[](size_t idx) const;
	T& at(size_t idx);  // Always bounds-checked version
	const T& at(size_t idx) const;

	void shrink_to_fit();
	void clear();

	const T& front() const;
	T& front();
	const T& back() const;
	T& back();

	bool empty() const;
	size_t getSize() const;
	size_t getCapacity() const;
};

template<typename T>
void MyVector<T>::copyFrom(const MyVector<T>& other)
{
	// Initialize to safe defaults first
	data = nullptr;
	size = 0;
	capacity = 0;

	// Handle empty vector case
	if (other.size == 0) {
		capacity = INITIAL_CAPACITY;
		data = new T[capacity];
		return;
	}

	// Copy size and ensure minimum capacity
	size = other.size;
	capacity = other.capacity;
	if (capacity < size) {
		capacity = size;  // Ensure capacity is at least size
	}
	if (capacity == 0) {
		capacity = INITIAL_CAPACITY;
	}

	// Allocate memory
	data = new T[capacity];

	// Copy elements safely
	if (other.data != nullptr) {
		for (size_t i = 0; i < size; i++) {
			data[i] = other.data[i];
		}
	}
}


template<typename T>
void MyVector<T>::moveFrom(MyVector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;

	// Clear other object
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

template<typename T>
void MyVector<T>::resize(size_t newCapacity)
{
	// Ensure minimum capacity - never allow 0
	if (newCapacity < INITIAL_CAPACITY) {
		newCapacity = INITIAL_CAPACITY;
	}

	// If requesting smaller capacity, don't shrink below current size
	if (newCapacity < size) {
		newCapacity = (size < INITIAL_CAPACITY) ? INITIAL_CAPACITY : size;
	}

	// If capacity is already correct, no need to resize
	if (newCapacity == capacity) {
		return;
	}

	// Allocate new memory - guaranteed to be at least INITIAL_CAPACITY
	T* newData = new T[newCapacity];

	// Copy existing elements safely - only if we have valid data and elements
	if (data != nullptr && size > 0) {
		for (size_t i = 0; i < size; i++) {
			newData[i] = std::move(data[i]);
		}
	}

	// Clean up old memory
	delete[] data;

	// Update members - capacity is guaranteed to be >= INITIAL_CAPACITY
	data = newData;
	capacity = newCapacity;
}

// Also consider updating your free() method to maintain minimum capacity:
template<typename T>
void MyVector<T>::free()
{
	delete[] data;
	data = nullptr;
	size = 0;
	capacity = INITIAL_CAPACITY; // You might want to keep this as INITIAL_CAPACITY instead
}

template<typename T>
MyVector<T>::MyVector()
{
	size = 0;
	capacity = INITIAL_CAPACITY;
	data = new T[capacity];
}

template<typename T>
MyVector<T>::MyVector(size_t n)
{
	size = n;
	capacity = (n == 0) ? INITIAL_CAPACITY : n;
	data = new T[capacity]{};
}

template<typename T>
MyVector<T>::MyVector(size_t n, const T& elem)
{
	size = n;
	capacity = (n == 0) ? INITIAL_CAPACITY : n;
	data = new T[capacity];

	for (size_t i = 0; i < size; i++) {
		data[i] = elem;
	}
}

template<typename T>
MyVector<T>::MyVector(const MyVector<T>& other)
{
	copyFrom(other);
}

template<typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept
{
	moveFrom(std::move(other));
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
MyVector<T>::~MyVector()
{
	free();
}

template<typename T>
void MyVector<T>::push_back(const T& elem)
{
	if (size >= capacity) {
		size_t newCapacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
		resize(newCapacity);
	}
	data[size] = elem;
	size++;
}

template<typename T>
void MyVector<T>::push_back(T&& elem)
{
	if (size >= capacity) {
		size_t newCapacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
		resize(newCapacity);
	}
	data[size] = std::move(elem);
	size++;
}

template<typename T>
void MyVector<T>::pop_back()
{
	if (size > 0) {
		size--;
	}
}

template<typename T>
void MyVector<T>::insert(size_t idx, const T& elem)
{
	if (idx > size) {
		throw std::out_of_range("Insert index out of range");
	}

	if (size >= capacity) {
		size_t newCapacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
		resize(newCapacity);
	}

	// Shift elements right
	for (size_t i = size; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[idx] = elem;
	size++;
}

template<typename T>
void MyVector<T>::insert(size_t idx, T&& elem)
{
	if (idx > size) {
		throw std::out_of_range("Insert index out of range");
	}

	if (size >= capacity) {
		size_t newCapacity = (capacity == 0) ? INITIAL_CAPACITY : capacity * 2;
		resize(newCapacity);
	}

	// Shift elements right
	for (size_t i = size; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}

	data[idx] = std::move(elem);
	size++;
}

template<typename T>
void MyVector<T>::erase(size_t idx)
{
	if (idx >= size) {
		throw std::out_of_range("Erase index out of range");
	}

	// Shift elements left
	for (size_t i = idx; i < size - 1; i++) {
		data[i] = std::move(data[i + 1]);
	}
	size--;
}

// ALWAYS bounds-checked operator[]
template<typename T>
T& MyVector<T>::operator[](size_t idx)
{
	if (idx >= size) {
		throw std::out_of_range("MyVector index out of range");
	}
	return data[idx];
}

template<typename T>
const T& MyVector<T>::operator[](size_t idx) const
{
	if (idx >= size) {
		throw std::out_of_range("MyVector index out of range");
	}
	return data[idx];
}

// Explicit bounds-checked access
template<typename T>
T& MyVector<T>::at(size_t idx)
{
	if (idx >= size) {
		throw std::out_of_range("MyVector index out of range");
	}
	return data[idx];
}

template<typename T>
const T& MyVector<T>::at(size_t idx) const
{
	if (idx >= size) {
		throw std::out_of_range("MyVector index out of range");
	}
	return data[idx];
}

template<typename T>
void MyVector<T>::shrink_to_fit()
{
	if (size == 0) {
		resize(INITIAL_CAPACITY);
	}
	else {
		resize(size);
	}
}

template<typename T>
void MyVector<T>::clear()
{
	size = 0;
}

template<typename T>
const T& MyVector<T>::front() const
{
	if (size == 0) {
		throw std::out_of_range("MyVector is empty");
	}
	return data[0];
}

template<typename T>
T& MyVector<T>::front()
{
	if (size == 0) {
		throw std::out_of_range("MyVector is empty");
	}
	return data[0];
}

template<typename T>
const T& MyVector<T>::back() const
{
	if (size == 0) {
		throw std::out_of_range("MyVector is empty");
	}
	return data[size - 1];
}

template<typename T>
T& MyVector<T>::back()
{
	if (size == 0) {
		throw std::out_of_range("MyVector is empty");
	}
	return data[size - 1];
}

template<typename T>
bool MyVector<T>::empty() const
{
	return size == 0;
}

template<typename T>
size_t MyVector<T>::getSize() const
{
	return size;
}

template<typename T>
size_t MyVector<T>::getCapacity() const
{
	return capacity;
}