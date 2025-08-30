#include <iostream>
#include <vector>
#include <cstddef> 
#include <type_traits>
#include <algorithm> 

template<typename T, size_t NumBlocks>
class FixedAllocator {
private:
    struct Node { Node* next; };

    // Ensure each block is big enough for T and Node and aligned for T
    using Storage = std::aligned_storage_t<
        (std::max)(sizeof(T), sizeof(Node)),
        alignof(T)
    >;

    Node* m_free_list_head = nullptr;
    std::vector<Storage> m_memory_pool;

public:
    FixedAllocator() : m_memory_pool(NumBlocks) {

        char* start = reinterpret_cast<char*>(m_memory_pool.data()); // char because it is of one byte
        std::size_t stride = sizeof(Storage);
        m_free_list_head = reinterpret_cast<Node*>(start);

        Node* current = m_free_list_head;
        for (size_t i = 0; i < NumBlocks - 1; ++i) {
            char* next_addr = start + (i + 1) * stride;
            current->next = reinterpret_cast<Node*>(next_addr);
            current = current->next;
        }
        current->next = nullptr;
    }

    T* allocate() {
        if (!m_free_list_head) return nullptr;
        Node* head = m_free_list_head;
        m_free_list_head = head->next;
        return reinterpret_cast<T*>(head);
    }

    void deallocate(T* ptr) {
        if (!ptr) return;
        Node* node = reinterpret_cast<Node*>(ptr);
        node->next = m_free_list_head;
        m_free_list_head = node;
    }
};



