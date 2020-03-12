#include <iostream>


class makeAllocator
{
public:

    // explicit используется для создания явных конструкторов
    explicit makeAllocator(size_t maxSize = 1000)
    {
        if (maxSize == 0)
        {
            start_ptr = nullptr;
            current_ptr = start_ptr;
        }

        else
        {
            start_ptr = (char*)malloc(maxSize);
            current_ptr = start_ptr;
        }

        buf_size = maxSize;

    }


    char* alloc(size_t size)
    {
        if (start_ptr == nullptr)
        {
            return nullptr;
        }
        
        else if (current_ptr + size > start_ptr + buf_size)
        {
            return nullptr;
        }

        else
        {
            char *tmp = current_ptr;
            current_ptr += size;
            return tmp;
        }

    }

    void reset()
    {
        current_ptr = start_ptr;
    }

    void print_start_ptr()
    {
        std::cout << static_cast <const void *> (start_ptr) << "\n \n";
    }

    char* where_cur_ptr()
    {
        return current_ptr;
    }

    char* where_start_ptr()
    {
        return start_ptr;
    }

    void free_memory()
    {
        free(start_ptr);
    }

private:
    char *start_ptr;
    char *current_ptr;
    size_t buf_size;
};


void test(makeAllocator allocator, size_t n)
{
    allocator.print_start_ptr();            // вывели указатель на начало памяти

    auto first =  static_cast <const void *> (allocator.alloc(100));
    auto second =  static_cast <const void *> (allocator.alloc(200));

    if (first != second)
    {
        std::cout << "-----------------------------------------------------------------------------\n";
        std::cout << "Тест пройден, указатели не равны\n" << "указатель на first: " << first << "\nуказатель на second: " << second << "\n";
        std::cout << "-----------------------------------------------------------------------------\n\n";
    }


    auto more_max = static_cast <const void *> (allocator.alloc(2 * n));
    if (more_max == nullptr)
    {
        std::cout << "-----------------------------------------------------------------------------\n";
        std::cout << "Тест пройден, запрашиваемая память больше зарезервированной, вернули nullptr\n";
        std::cout << "-----------------------------------------------------------------------------\n\n";
    }

    if (allocator.where_cur_ptr() != allocator.where_start_ptr())
    {
        std::cout << "-----------------------------------------------------------------------------\n";
        std::cout << "Проверили, что start и current в данный момент не равны\n";
    }

    allocator.reset();

    if (allocator.where_cur_ptr() == allocator.where_start_ptr())
    {
        std::cout << "Тест пройден, reset корректно отработал и зарезервирвоанную память снова можно использовать\n";
        std::cout << "-----------------------------------------------------------------------------\n\n";
    }

    first = static_cast <const void *> (allocator.alloc(n - 1));
    second = static_cast <const void *> (allocator.alloc(2));
    if (second == nullptr)
    {
        std::cout << "-----------------------------------------------------------------------------\n";
        std::cout << "Тест пройден, запрашиваемая память больше зарезервированной, вернули nullptr\n";
        std::cout << "-----------------------------------------------------------------------------\n\n";
    }

    allocator.reset();
    first = static_cast <const void *> (allocator.alloc(n + 1));
    if (first == nullptr)
    {
        std::cout << "-----------------------------------------------------------------------------\n";
        std::cout << "Тест пройден, запрашиваемая память больше зарезервированной, вернули nullptr\n";
        std::cout << "-----------------------------------------------------------------------------\n\n";
    }
}


int main()
{
    size_t n;                                       // тесты были при n = 1000
    std::cout << "Размер аллокатора в байтах: ";
    std::cin >> n;
    makeAllocator allocator(n);

    test(allocator, n);
    allocator.free_memory();                       // освободили всю динамическую память

    return 0;
}
