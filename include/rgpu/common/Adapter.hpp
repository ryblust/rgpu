#pragma once

#include <cstdint>

namespace rgpu {

struct AdapterInfo final {
    const std::uint32_t VendorID;
    const std::uint32_t DeviceID;
};

} // namespace rgpu