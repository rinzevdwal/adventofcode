#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <optional>
#include <vector>
#include <numeric>

int main()
{
    std::filesystem::path file{"input.txt"};
    std::ifstream src{file};
    if (!src.is_open())
    {
        std::cerr << "Failed to open " << file;
        return 1;
    }

    std::string input{std::istreambuf_iterator<char>{src}, std::istreambuf_iterator<char>{}};
    if(input.back() != '\n')
    {
        input += '\n';
    }

    std::optional<char> first{std::nullopt};
    std::optional<char> last{std::nullopt};
    std::vector<int> result{};
    for (char c : input)
    {
        if (c == '\n')
        {
            std::string strNumber{first.value()};
            strNumber += last.value();

            int number{atoi(strNumber.c_str())};
            result.push_back(number);

            first = std::nullopt;
            last = std::nullopt;
        }
        else if (std::isdigit(c))
        {
            if (!first.has_value())
            {
                first = c;
                last = c;
            }
            else
            {
                last = c;
            }
        }
    }

    int sum{ std::accumulate(result.begin(), result.end(), 0) };
    std::cout << "the result is: " << sum << "\n";

    return 0;
}