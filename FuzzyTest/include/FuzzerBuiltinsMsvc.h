// SPDX-FileCopyrightText: 2023 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef LLVM_FUZZER_BUILTINS_MSVC_H
#define LLVM_FUZZER_BUILTINS_MSVC_H

#include "FuzzerDefs.h"

#if LIBFUZZER_MSVC
#include <intrin.h>
#include <cstdint>
#include <cstdlib>

// __builtin_return_address() cannot be compiled with MSVC. Use the equivalent
// from <intrin.h>
#define GET_CALLER_PC() _ReturnAddress()

namespace fuzzer {

inline uint8_t  Bswap(uint8_t x)  { return x; }
// Use alternatives to __builtin functions from <stdlib.h> and <intrin.h> on
// Windows since the builtins are not supported by MSVC.
inline uint16_t Bswap(uint16_t x) { return _byteswap_ushort(x); }
inline uint32_t Bswap(uint32_t x) { return _byteswap_ulong(x); }
inline uint64_t Bswap(uint64_t x) { return _byteswap_uint64(x); }

// The functions below were mostly copied from
// compiler-rt/lib/builtins/int_lib.h which defines the __builtin functions used
// outside of Windows.
inline uint32_t Clzll(uint64_t X) {
  unsigned long LeadZeroIdx = 0;

#if !defined(_M_ARM) && !defined(_M_X64)
  // Scan the high 32 bits.
  if (_BitScanReverse(&LeadZeroIdx, static_cast<unsigned long>(X >> 32)))
    return static_cast<int>(63 - (LeadZeroIdx + 32)); // Create a bit offset from the MSB.
  // Scan the low 32 bits.
  if (_BitScanReverse(&LeadZeroIdx, static_cast<unsigned long>(X)))
    return static_cast<int>(63 - LeadZeroIdx);

#else
  if (_BitScanReverse64(&LeadZeroIdx, X)) return 63 - LeadZeroIdx;
#endif
  return 64;
}

inline uint32_t Clz(uint32_t X) {
  unsigned long LeadZeroIdx = 0;
  if (_BitScanReverse(&LeadZeroIdx, X)) return 31 - LeadZeroIdx;
  return 32;
}

inline int Popcountll(unsigned long long X) {
#if !defined(_M_ARM) && !defined(_M_X64)
  return __popcnt(X) + __popcnt(X >> 32);
#else
  return __popcnt64(X);
#endif
}

}  // namespace fuzzer

#endif  // LIBFUZER_MSVC
#endif  // LLVM_FUZZER_BUILTINS_MSVC_H
