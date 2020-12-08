#pragma once

#include <cstdint>
// #include <list>
// namespace buffer
// {

// void allocate(void*, uint64_t numOfBlock, uint8_t memAligned = 64);
// void release(void*);

// void createManager(uint64_t, const char*);

// struct MemoryDescriptor
// {
//     void*    ptr;
//     uint64_t numOfBlock;
//     uint8_t  memAligned;
// };

// class MemoryManager
// {

// friend void createManager(uint64_t, const char*);

// public:
//     MemoryManager() = delete;
//     MemoryManager(MemoryManager const&) = delete;
// private:
//     MemoryManager(uint64_t, const char*);
//     uint64_t* memory;
//     std::list<MemoryDescriptor> descs;
// };

// }