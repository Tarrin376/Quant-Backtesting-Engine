#ifndef CSV_WRITER_H
#define CSV_WRITER_H

#include <functional>
#include <string_view>
#include <string>
#include <array>
#include <fstream>
#include <sstream>
#include <cstdint>

template <typename T, std::size_t N>
class CSVWriter {
public:
    using Row = std::array<std::string, N>;
    using FormatterFn = std::function<const Row(const T&)>;

    CSVWriter(const std::string& fileName, const Row& csvHeaders, const FormatterFn formatter) : 
        _writer{ _prefix + fileName },
        _csvHeaders{ csvHeaders },
        _formatter{ formatter } {}

    void write(const T& data) {
        if (!_formatter) {
            return;
        }

        if (_isFirstLine) {
            _writer << toCSVString(_csvHeaders);
            _isFirstLine = false;
        }

        _writer << toCSVString(_formatter(data));
    }

    std::string toCSVString(const Row& values) {
        std::stringstream ss{};

        for (std::size_t i = 0; i < N; i++) {
            ss << values[i];
            if (i < N - 1) {
                ss << ',';
            }
        }

        ss << '\n';
        return ss.str();
    }

private:
    const std::string _prefix{ "../results/" };
    const Row _csvHeaders{};
    const FormatterFn _formatter{};

    std::ofstream _writer{};
    bool _isFirstLine{ true };
};

#endif