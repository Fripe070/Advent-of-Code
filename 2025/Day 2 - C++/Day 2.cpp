#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cerr << "Could not read file." << std::endl;
        return 1;
    }

    unsigned long long answerP1 = 0;
    unsigned long long answerP2 = 0;

    std::string line;
    while (std::getline(file, line, ','))
    {
        size_t i = 0;
        for (; i < line.length(); i++)
            if (line[i] == '-')
                break;

        if (i == line.length())
        {
            std::cerr << "Invalid line format: " << line << std::endl;
            continue;
        }
        const unsigned long long num1str = std::stoull(line.substr(0, i));
        const unsigned long long num2str = std::stoull(line.substr(i + 1));
        for (size_t n = num1str; n <= num2str; n++)
        {
            const std::string digits = std::to_string(n);
            {
                const auto splitIndex = digits.length() / 2;
                if (digits.substr(0, splitIndex) == digits.substr(splitIndex))
                    answerP1 += n;
            }
            {
                const double sqrt = std::sqrt(digits.length());
                for (size_t x = 1; x < digits.length(); x++)
                {
                    if (digits.length() % x != 0)
                        continue;
                    std::ostringstream subString;
                    for (size_t i = 0; i < digits.length() / x; i++)
                        subString << digits.substr(0, x);
                    if (subString.str() == digits)
                    {
                        answerP2 += n;
                        break;
                    }
                }
            }
        }
    }

    std::cout << "Part 1's answer: " << answerP1 << std::endl;
    std::cout << "Part 2's answer: " << answerP2 << std::endl;
    return 0;
}
