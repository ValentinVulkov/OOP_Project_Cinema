#include "RoomManager.h"

unsigned RoomManager::nextID = 1;
MyVector<unsigned> RoomManager::freeIDs;

unsigned RoomManager::assignID() {
    // First check for recycled IDs
    if (!freeIDs.empty()) {
        unsigned id = freeIDs.back();
        freeIDs.pop_back();
        return id;
    }

    // Otherwise use and increment nextID
    return nextID++;
}

void RoomManager::releaseID(unsigned id) {
    // Validation
    if (id == 0) {
        throw InvalidIDException("Cannot release ID 0");
    }
    if (id >= nextID) {
        throw InvalidIDException("Released ID was never assigned");
    }

    // Check if this is the highest ID
    if (id == nextID - 1) {
        nextID--;
    }
    else {
        // Add to freeIDs (maintain sorted order for efficiency)
        unsigned insertPos = 0;
        while (insertPos < freeIDs.getSize() && freeIDs[insertPos] < id) {
            insertPos++;
        }

        // Check for duplicate release
        if (insertPos < freeIDs.getSize() && freeIDs[insertPos] == id) {
            throw InvalidIDException("Double release of the same ID");
        }

        freeIDs.insert(insertPos, id);
    }

    // Clean up any now-unnecessary freeIDs
    while (nextID > 1 && !freeIDs.empty() && freeIDs.back() == nextID - 1) {
        freeIDs.pop_back();
        nextID--;
    }
}
