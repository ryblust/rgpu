#pragma once

namespace rgpu {

class GPUQueue final {
public:

private:
    struct GPUQueueImpl;
    GPUQueueImpl* Queue;
};

} // namespace rgpu