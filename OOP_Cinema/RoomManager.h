#pragma once
#include "MyVector.hpp"
#include <stdexcept>

class RoomManager {
private:
    static unsigned nextID;           
    static MyVector<unsigned> freeIDs;

public:
    // Get the next available ID
    static unsigned assignID();

    // Release an ID back to the pool
    static void releaseID(unsigned id);

    // Error class
    class InvalidIDException : public std::runtime_error {
    public:
        InvalidIDException(const char* msg) : std::runtime_error(msg) {}
    };
	~RoomManager() = default;
};