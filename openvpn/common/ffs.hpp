//    OpenVPN -- An application to securely tunnel IP networks
//               over a single port, with support for SSL/TLS-based
//               session authentication and key exchange,
//               packet encryption, packet authentication, and
//               packet compression.
//
//    Copyright (C) 2012-2017 OpenVPN Technologies, Inc.
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU Affero General Public License Version 3
//    as published by the Free Software Foundation.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU Affero General Public License for more details.
//
//    You should have received a copy of the GNU Affero General Public License
//    along with this program in the COPYING file.
//    If not, see <http://www.gnu.org/licenses/>.

#ifndef OPENVPN_COMMON_FFS_H
#define OPENVPN_COMMON_FFS_H

// find_first_set: find the one-based position of the first 1 bit in
// a word (scanning from least significant bit to most significant)

// find_last_set: find the one-based position of the last 1 bit in
// a word (scanning from most significant bit to least significant)

namespace openvpn {

#if defined(__GNUC__)

  inline int find_first_set(unsigned int v)
  {
    if (!v)
      return 0;
    return __builtin_ffs(v);
  }

  inline int find_last_set(unsigned int v)
  {
    if (!v)
      return 0;
    return 32 - __builtin_clz(v);
  }

#elif defined(_MSC_VER)

#include <intrin.h>

  inline int find_first_set(unsigned int x)
  {
    if (!x)
      return 0;
    unsigned int r = 0;
    _BitScanForward((unsigned long *)&r, x);
    return r + 1;
  }

  inline int find_last_set(unsigned int x)
  {
    if (!x)
      return 0;
    unsigned int r = 0;
    _BitScanReverse((unsigned long *)&r, x);
    return r + 1;
  }

#else
#error no find_first_set / find_last_set implementation for this platform
#endif

  template <typename T>
  inline bool is_pow2(const T v)
  {
    return v && find_first_set(v) == find_last_set(v);
  }

  template <typename T>
  inline int log2(const T v)
  {
    return find_last_set(v) - 1;
  }

} // namespace openvpn

#endif // OPENVPN_COMMON_FFS_H
