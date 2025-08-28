# Custom-Fixed-Size-Allocator
* **Day 3: Custom Fixed-Size Allocator.** In HFT, heap allocations (`new`, `delete`) are a major source of non-deterministic latency. Create a memory pool that pre-allocates a large chunk of memory and vends fixed-size blocks from it. This avoids calling the OS for memory on the critical path.
