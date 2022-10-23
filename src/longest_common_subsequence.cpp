#include <iostream>
#include <string_view>
#include <stack>
#include <vector>
#include <algorithm>

namespace recursive
{
    constexpr static auto lcs_length{[](auto const s1, auto const s2) noexcept
    {
        if (s1.empty() || s2.empty())
        {
            return 0;
        }
        else
        {
            if (s1.back() == s2.back())
            {
                return 1 + lcs_length(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() - 1));
            }
            else
            {
                return std::max(lcs_length(s1.substr(0, s1.size() - 1), s2), lcs_length(s1, s2.substr(0, s2.size() - 1)));
            }
        }
    }};


    constexpr static auto lcs_sequence{[](auto const s1, auto const s2) noexcept
    {
        if (s1.empty() || s2.empty())
        {
            return std::string{};
        }
        else
        {
            if (s1.back() == s2.back())
            {
                return  lcs_sequence(s1.substr(0, s1.size() - 1), s2.substr(0, s2.size() - 1)) + s1.back();
            }
            else
            {
                return [](auto const s1, auto const s2) noexcept
                {
                    return s1.length() > s2.length() ? s1 : s2;
                }(lcs_sequence(s1.substr(0, s1.size() - 1), s2), lcs_sequence(s1, s2.substr(0, s2.size() - 1)));
            }
        }
    }};
} // namespace recursive


namespace dynamic_programming
{
    class LCS
    {
        size_t m;
        size_t n;
        std::string_view s1;
        std::string_view s2;
        std::vector<std::vector<size_t>> cache;
        public:
            LCS(std::string_view s1, std::string_view s2) noexcept
            : m{s1.length() + 1}
            , n{s2.length() + 1}
            , s1{s1}
            , s2{s2}
            , cache(m, std::vector<size_t>(n, 0))
            {
                for (auto i{1}; i < m; ++i)
                {
                    for (auto j{1}; j < n; ++j)
                    {
                        if (s1.at(i - 1) == s2.at(j - 1))
                        {
                            cache.at(i).at(j) = cache.at(i - 1).at(j - 1) + 1;
                        }
                        else
                        {
                            cache.at(i).at(j) = std::max(cache.at(i - 1).at(j), cache.at(i).at(j - 1));
                        }
                    }
                }
            }
            size_t get_length() const noexcept
            {
                return this->cache.at(this->m - 1).at(this->n - 1);
            }

            std::string get_sequence() const noexcept
            {
                auto index{this->get_length()};
                std::string sequence(index, ' ');
                auto i{this->m - 1};
                auto j{this->n - 1};
                while (i > 0 && j > 0)
                {
                    if (this->s1.at(i - 1) == this->s2.at(j - 1))
                    {
                        sequence.at(index - 1) = this->s1.at(i - 1);
                        --i;
                        --j;
                        --index;
                    }
                    else if (this->cache.at(i - 1).at(j) > this->cache.at(i).at(j - 1))
                    {
                        --i;
                    }
                    else
                    {
                        --j;
                    }
                }
                return sequence;
            }
    };

    constexpr static auto lcs_length{[](auto const &s1, auto const &s2) noexcept
    {
        auto const m{s1.length() + 1};
        auto const n{s2.length() + 1};
        std::vector<std::vector<size_t>> cache(m, std::vector<size_t>(n, 0));
        for (auto i{1}; i < m; ++i)
        {
            for (auto j{1}; j < n; ++j)
            {
                if (s1.at(i - 1) == s2.at(j - 1))
                {
                    cache.at(i).at(j) = cache.at(i - 1).at(j - 1) + 1;
                }
                else
                {
                    cache.at(i).at(j) = std::max(cache.at(i - 1).at(j), cache.at(i).at(j - 1));
                }
            }
        }
        return cache.at(m - 1).at(n - 1);
    }};

} // namespace dynamic_programming

// not working yet
namespace using_stack
{
    constexpr static auto lcs{[](std::string_view s1, std::string_view s2) noexcept
    {
        std::stack<std::string_view> stack{};
        stack.push(s1);
        stack.push(s2);
        int acc{0};
        while (!stack.empty())
        {
            std::string_view str2{stack.top()};
            stack.pop();
            std::string_view str1{stack.top()};
            stack.pop();
            if (!(str1.empty() || str2.empty()))
            {
                if (str1.back() == str2.back())
                {
                    ++acc;
                    stack.push(std::string_view{str1.data(), str1.size() - 1});
                    stack.push(std::string_view{str2.data(), str2.size() - 1});
                }
                else
                {
                    stack.push(std::string_view{str1.data(), str1.size() - 1});
                    stack.push(std::string_view{str2});
                    stack.push(std::string_view{str1});
                    stack.push(std::string_view{str2.data(), str2.size() - 1});
                }
            }
        }
        return acc;
    }};
} // namespace using_stack

int main(int argc, char const *argv[])
{
    std::string const input1{"aabdlleog"};
    std::string const input2{"azbasdllgne"};
    std::string_view input3{"aabdlleog"};
    std::string_view input4{"azbasdllgne"};

    std::cout << std::endl;

    // Recursive
    std::cout << "recursive::lcs_length -> ";
    std::cout << recursive::lcs_length(input1, input2) << std::endl;

    std::cout << "recursive::lcs_sequence -> ";
    auto const seq1{recursive::lcs_sequence(input1, input2)};
    std::cout << "seq1 : " << seq1 << std::endl;
    std::cout << "seq1.length() : "<< seq1.length() << std::endl;
    std::cout << std::endl;

    // Dynamic Programming
    std::cout << "dynamic_programming::lcs_length -> ";
    std::cout << dynamic_programming::lcs_length(input3, input4) << std::endl;

    std::cout << "dynamic_programming::LCS" << std::endl;
    dynamic_programming::LCS lcs{input3, input4};
    std::cout << "LCS.get_length() -> " << lcs.get_length() << std::endl;
    std::cout << "LCS.get_sequence() -> " << lcs.get_sequence() << std::endl;
    std::cout << std::endl;

    // Using Stack
    // std::cout << using_stack::lcs(input3, input4) << std::endl;

    return 0;
}
