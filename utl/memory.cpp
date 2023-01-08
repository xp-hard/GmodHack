#include "memory.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <vector>

void memory::Setup() noexcept
{
	allocKeyValuesClient = PatternScan("client.dll", "FF 52 04 85 C0 74 0C 56") + 3;
	allocKeyValuesEngine = PatternScan("engine.dll", "FF 52 04 85 C0 74 0C 56") + 3;
    insertIntoTree = PatternScan("client.dll", "56 52 FF 50 18") + 5;

    keyValuesFromString = PatternScan("client.dll", "E8 ? ? ? ? 8B 0D ? ? ? ? 83 C4 04 8B F8 8B 11") + 1;

    glowManager = PatternScan("client.dll", "0F 11 05 ? ? ? ? 83 C8 01") + 3;
}

std::uint8_t* memory::PatternScan(const char* module_name, const char* signature) noexcept
{
    const auto module_handle = GetModuleHandleA(module_name);

    if (!module_handle)
        return nullptr;

    static auto pattern_to_byte = [](const char* pattern) {
        auto bytes = std::vector<int>{};
        auto start = const_cast<char*>(pattern);
        auto end = const_cast<char*>(pattern) + std::strlen(pattern);

        for (auto current = start; current < end; ++current) {
            if (*current == '?') {
                ++current;

                if (*current == '?')
                    ++current;

                bytes.push_back(-1);
            }
            else {
                bytes.push_back(std::strtoul(current, &current, 16));
            }
        }
        return bytes;
    };

    auto dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
    auto nt_headers =
        reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

    auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
    auto pattern_bytes = pattern_to_byte(signature);
    auto scan_bytes = reinterpret_cast<std::uint8_t*>(module_handle);

    auto s = pattern_bytes.size();
    auto d = pattern_bytes.data();

    for (auto i = 0ul; i < size_of_image - s; ++i) {
        bool found = true;

        for (auto j = 0ul; j < s; ++j) {
            if (scan_bytes[i + j] != d[j] && d[j] != -1) {
                found = false;
                break;
            }
        }
        if (found)
            return &scan_bytes[i];
    }

    return nullptr;
}