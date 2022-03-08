// Copyright © 2017-2022 Trust Wallet.
//
// This file is part of Trust. The full Trust copyright notice, including
// terms governing use, modification, and redistribution, is contained in the
// file LICENSE at the root of the source code distribution tree.

#pragma once

#include "Base58.h"
#include "Data.h"
#include "PublicKey.h"

#include <string>

const std::string SS58Prefix = "SS58PRE";

namespace TW {

/// Base-58-encodeed Substrate address.
class SS58Address {
  public:
    static const size_t checksumSize = 2;

    // networks 0 -- 63 are encoded in one byte (0b00LLLLLL)
    static const byte networkSimpleLimit = 0x40;
    // networks 64 -- 16383 are encoded in 2 bytes: network 0b00HHHHHH_MMLLLLLL is encoded as 0b01LLLLLL, 0bHHHHHHMM (first byte between 64 and 127)
    // https://docs.substrate.io/v3/advanced/ss58/#address-type
    static const byte networkFullLimit = 0x80;

    /// Address data consisting of one or more network byte(s) followed by the public key.
    Data bytes;

    /// Determines whether a string makes a valid address
    static bool isValid(const std::string& string, uint32_t network);

    template <typename T>
    static Data computeChecksum(const T& data);

    SS58Address() = default;

    /// Initializes an address with a string representation.
    SS58Address(const std::string& string, uint32_t network);

    /// Initializes an address with a public key and network.
    SS58Address(const PublicKey& publicKey, uint32_t network);

    /// Returns a string representation of the address.
    std::string string() const;

    /// Returns public key bytes
    Data keyBytes() const;

    // Return true and the network size (1 or 2) and network if input is valid
    static bool decodeNetwork(const Data& data, byte& networkSize, uint32_t& network);

    static bool encodeNetwork(uint32_t network, Data& data);
};

inline bool operator==(const SS58Address& lhs, const SS58Address& rhs) {
    return lhs.bytes == rhs.bytes;
}

} // namespace TW
