#pragma once

#include <cstdint>
#include <memory>
namespace binary
{

class BigBinary;

class BigBinaryImpl
{
friend class BigBinary;
public:
    explicit BigBinaryImpl(uint64_t, uint64_t align = 8);
    BigBinaryImpl() = delete;
    BigBinaryImpl(const BigBinaryImpl&) = delete;
    ~BigBinaryImpl();
private:
    uint64_t* ptr;
    uint64_t  bitSize;
    uint64_t  byteSize;
    uint64_t  size;
};

class BigBinary
{
public:
    explicit BigBinary(uint64_t, uint64_t align = 8);
    BigBinary() = delete;
    BigBinary(const BigBinary&) = default;
    uint64_t const* data() {return pimpl->ptr;}
    uint8_t const* c_str() {return reinterpret_cast<uint8_t*>(pimpl->ptr);}
    uint64_t getSize() {return pimpl->size;}
    uint64_t getByteSize() {return pimpl->byteSize;}
    uint64_t getBitSize() {return pimpl->bitSize;}
    //warning
    //align last cell as full
    //if you want to set 6 bit in byte you should set 2 most sign bits as zero
    void set(uint64_t*, uint64_t, uint64_t, uint64_t align = 8);
    void zero();
private:
    std::shared_ptr<BigBinaryImpl> pimpl;
};
}