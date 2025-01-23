#pragma once
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#define path_run_time_config "../run_time_config"

#define var(x) cout << #x << " = " << x << '\n';
#define varr(x) cout << #x << " = " << x << ' ';
#define line(x) cout << x << '\n';
#define linee(x) cout << x << ' ';
#define nline cout << '\n';

namespace vec_utils
{

    template <typename T> void print_on_by_one(const std::vector<T> &vec)
    {
        for (auto &v : vec)
        {
            cout << v << "\n";
        }
    }

    template <typename T>
    bool contains(const T &value, const std::vector<T> &vec)
    {
        return std::find(vec.begin(), vec.end(), value) != vec.end();
    }

    template <typename T>
    void remove_by_value(const T &value, std::vector<T> &vec)
    {
        auto it = std::find(vec.begin(), vec.end(), value);

        if (it != vec.end())
        {
            vec.erase(it);
        }
    }
} // namespace vec_utils

int my_sum(int a, int b);

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

#define null nullptr
#define pow2(x) ((x) * (x))
#define base_0(x) (x - 1)

#define c_init(x) x(_##x)
#define cc_init(x) this->x = x;
#define member_assign(a, b, member) a.member = b.member;
#define THIS_OTHER(x) this->x = other.x;

#define add_endl(string, how_many)                                             \
    for (u16 i{}; i < how_many; i++)                                           \
        string += "\n";

#define OUTPUT_TO_FILE(path, content)                                          \
    {                                                                          \
        ofstream file(path);                                                   \
        file << content;                                                       \
        file.close();                                                          \
    }

#define FATAL_ERROR(x)                                                         \
    {                                                                          \
        const string fatal = "FATAL ERROR - " + std::to_string(__LINE__) +     \
                             " : " + __FILE__ + " -> " + x + "\n";             \
        cout << fatal;                                                         \
        exit(EXIT_FAILURE);                                                    \
    }
#define ASSERT_ER_IF_TRUE(x)                                                   \
    if (x)                                                                     \
    FATAL_ERROR(#x)
#define ASSERT_ER_IF_NULL(x)                                                   \
    if (x == null)                                                             \
    FATAL_ERROR(#x)

#define SAFETY_CHECK(x) x;

#define delay_input std::this_thread::sleep_for(std::chrono::milliseconds(50));
#define Sleep(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
