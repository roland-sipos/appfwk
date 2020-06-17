#include <vector>
#include <chrono>
#include <iostream>
#include <memory>

struct Entity
{
    int i;
    float f;
    unsigned int u;
};

int main(int argc, char const *argv[])
{

    size_t buf_size = 100000;
    {
        std::vector<Entity> buf(buf_size);
        Entity x = {356, 0.15, 0xfff};

        auto start = std::chrono::steady_clock::now();
        for (size_t i(0); i<buf_size; ++i) {
            new (&buf[i]) Entity(x) ;
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "Placement new: elapsed time : " << elapsed_seconds.count() << "s\n";
    }

    {
        std::vector<std::unique_ptr<Entity>> buf(buf_size);

        auto start = std::chrono::steady_clock::now();
        for (size_t i(0); i<buf_size; ++i) {
            buf[i] = std::move(std::make_unique<Entity>());
        }
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        std::cout << "New: elapsed time           : " << elapsed_seconds.count() << "s\n";
    }



    /* code */
    return 0;
}