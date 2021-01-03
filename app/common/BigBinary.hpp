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
    static constexpr uint64_t sizeOfPiece = sizeof(*ptr);
};

class BigBinary
{
public:
    explicit BigBinary(uint64_t, uint64_t align = 8);
    BigBinary() = delete;
    BigBinary(const BigBinary&) = default;
    uint64_t const* data() const {return pimpl->ptr;}
    uint8_t const* c_str() const {return reinterpret_cast<uint8_t*>(pimpl->ptr);}
    uint64_t getSize() const {return pimpl->size;}
    uint64_t getByteSize() const {return pimpl->byteSize;}
    uint64_t getBitSize() const {return pimpl->bitSize;}
    //warning
    //align last cell as full
    //if you want to set 6 bit in byte you should set 2 most sign bits as zero
    void set(uint64_t const*, uint64_t, uint64_t, uint64_t align = 8);
    void set(uint64_t, uint64_t, uint64_t, uint64_t align = 8);
    void zero();
private:
    std::shared_ptr<BigBinaryImpl> pimpl;
};
}