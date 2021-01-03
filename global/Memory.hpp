#pragma once
#include <cstring>
#include <immintrin.h>
#include <cstdint>
namespace memory
{
constexpr uint64_t SIMD512_ALIGN_LEN = 64; //byte alignment

inline uint64_t mem_align(uint64_t size, uint64_t align = SIMD512_ALIGN_LEN) __attribute__((always_inline));
inline uint64_t mem_align(uint64_t size, uint64_t align)
{
    auto s = size / align;
    return (size % align) ? (s + 1) * align : s * align;
}

template<typename T>
inline void mem_alloc(T*& p, size_t num, size_t align = SIMD512_ALIGN_LEN) __attribute__((always_inline));
template<typename T>
inline void mem_alloc(T*& p, size_t num, size_t align)
{
    p = reinterpret_cast<T*>(_mm_malloc(num * sizeof(T), align));
}


template<typename T>
inline T* mem_alloc(uint64_t size, uint64_t align = SIMD512_ALIGN_LEN) __attribute__((always_inline));
template<typename T>
inline T* mem_alloc(uint64_t size, uint64_t align)
{
    return reinterpret_cast<T*>(_mm_malloc(size * sizeof(T), align));
}

template<typename T>
inline void mem_free(T*) __attribute__((always_inline));
template<typename T>
inline void mem_free(T* p)
{
    _mm_free(p);
}

template<typename T>
inline void mem_zero(T* p, size_t num) __attribute__((always_inline));
template<typename T>
inline void mem_zero(T* p, size_t num)
{
    memset(p, 0, sizeof(T) * num);
}

template<typename T>
inline void mem_copy(T* dst, T const* src, size_t num) __attribute__((always_inline));
template<typename T>
inline void mem_copy(T* dst, T const* src, size_t num)
{
    memcpy(dst, src, sizeof(T) * num);
}
}
