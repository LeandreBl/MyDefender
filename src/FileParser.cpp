#include <algorithm>

#include "FileParser.hpp"
#include "colors.h"

namespace Defender
{
    FileParser::FileParser(const std::string &filepath, const ParserEntry *entries, size_t count) noexcept
        : _labels(entries, entries + count), _filepath(filepath)
    {
    }

    int FileParser::findCallback(size_t lineno, const std::string &line) const noexcept
    {
        for (auto &&i : _labels)
        {
            if (line.compare(0, i.pattern.length(), i.pattern) == 0)
            {
                std::istringstream ss(line);
                ss.ignore(i.pattern.length());
                return !i.callback(lineno, line, ss);
            }
        }
        std::cerr << "Error: line: " << RED << lineno << RESET << ": invalid token." << std::endl;
        return 1;
    }

    static std::string removeExtraSpaces(const std::string &input)
    {
        std::string output;

        std::unique_copy(input.begin(), input.end(),
            std::back_insert_iterator<std::string>(output),
            [](char a, char b)
            {
                return std::isspace(a) && isspace(b);
            }
        );
        if (std::isspace(output.back()))
            output.pop_back();
        return output;
    }

    int FileParser::parse(char delimiter) const noexcept
    {
        std::ifstream file(_filepath);
        size_t lineno = 0;
        int ret = 0;

        if (file.is_open() == false)
            return -1;
        while (!file.eof())
        {
            std::string newline;
            std::getline(file, newline, delimiter);
            ++lineno;
            newline = removeExtraSpaces(newline);
            if (newline.length() == 0)
                continue;
            ret += findCallback(lineno, newline);
        }
        return ret;
    }
}