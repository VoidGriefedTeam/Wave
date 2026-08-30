// Copyright © 2026  VoidGriefedTeam

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>

#include <lexer.hpp>
#include <generator.hpp>
#include <translator.hpp>
#include <filesystem>
#include <CLI11/CLI.hpp>
#include <print>
#include <fstream>
#define FMT_HEADER_ONLY
#include <fmt/color.h>
#include <fmt/format.h>

#ifdef _WIN32
std::string find_msvc()
{
    std::string command =
        "vswhere.exe -latest -products * "
        "-requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 "
        "-property installationPath";

    FILE* pipe = _popen(command.c_str(), "r");

    if (!pipe)
        return "";

    char buffer[512];
    std::string result;

    if (fgets(buffer, sizeof(buffer), pipe))
        result = buffer;

    _pclose(pipe);

    if (!result.empty() && result.back() == '\n')
        result.pop_back();

    return result;
}
#endif

int main(int argc, char* argv[])
{
    CLI::App app{"Wave compiler"};
    std::string input;
    std::string output;
    bool build = false;

    app.add_option("input", input, "Input .wave file")->required();
    app.add_option("-o,--output", output, "Output .cpp file");
    app.add_flag("--build", build, "Build the generated code");

    CLI11_PARSE(app, argc, argv);
    
    std::ifstream file(input);
    if (!file.is_open())
    {
        std::println("[Wave] Error: Could not open {}.wave", input);
        return 1;
    }

    if (output.empty())
    {
        output = std::filesystem::path(input).stem().string() + ".cpp";
    }
    std::println("[Wave] parsing...");
    std::vector<std::string> words = parse(file); // parse lines in the wave source code

    std::println("[Wave] extracting...");
    extdat data = extract(words); // extract data from parenthesis

    std::println("[Wave] translating...");
    ret translated = translate(data); // translate the extracted data

    std::println("[Wave] generating c++ file...");
    std::string filename = std::filesystem::path(input).stem().string();

    generate_code(translated, output); // generate the code into a .cpp file

    if (build) 
    {
        std::println("[Wave] building exe...");
        std::println("[Wave] Detecting OS");
        #ifdef _WIN32
        std::println("[Wave] OS:Windows");
        std::system("\"C:\\Program Files (x86)\\Microsoft Visual Studio\\Installer\\vswhere.exe\" -latest -products * -version [18.0,19.0) -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath > vs.txt");
        std::ifstream vs("vs.txt");
        std::string path;
        std::getline(vs, path);

        if (path.empty())
        {
            fmt::print(fg(fmt::color::yellow), "[Wave] Error: MSVC was not found.\n");
            std::println("[Wave] Install MSVC Build Tools 2026? [Y/n]");
            char answer;
            std::cin >> answer;
            if (answer == 'y' || answer == 'Y')
            {
                std::system("winget install Microsoft.VisualStudio.BuildTools --force --override \"--wait --passive --add Microsoft.VisualStudio.Workload.NativeDesktop --includeRecommended\"");
                path = find_msvc();
            }
            else
            {
                fmt::print(fg(fmt::color::red),"Build cancelled.\n");
                return 1;
            }
            
        }

        std::string command = "call \"" + path + "\\Common7\\Tools\\VsDevCmd.bat\" && cl /std:c++latest \"" + output + "\" /Fe:\"" + std::filesystem::path(output).replace_extension(".exe").string() + "\"";
        std::system(command.c_str());


        #elif defined(__linux__)
        std::println("[Wave]OS:Linux");
        if (std::system("g++ --version > /dev/null 2>&1") != 0)
        {
            fmt::print(fg(fmt::color::yellow), "[Wave] Error: g++ was not found.\n");
            std::println("Install g++? [Y/n]");
            char a;
            std::cin >> a;
            if (a == 'y' || a == 'Y')
            {
                if (std::system("command -v apt-get > /dev/null 2>&1") == 0)
                {
                    std::system("sudo apt-get install g++");
                }
                else if (std::system("command -v dnf > /dev/null 2>&1") == 0)
                {
                    std::system("sudo dnf install gcc-c++");
                }
                else if (std::system("command -v pacman > /dev/null 2>&1") == 0)
                {
                    std::system("sudo pacman -S gcc");
                }
                else if (std::system("command -v zypper > /dev/null 2>&1") == 0)
                {
                    std::system("sudo zypper install gcc-c++");
                }
                else
                {
                    std::println("[Wave] Error: Could not detect a supported package manager.");
                    return 1;
                }
            }
            else
            {
                fmt::print(fg(fmt::color::red), "[Wave] Build Failed.\n");
                return 1;
            }

        }

        std::system(("g++ -std=c++23 \"" + output + "\" -o \"" +
    std::filesystem::path(output).replace_extension("").string() +
    "\"").c_str());

        #else
        std::print("[Wave] Sorry! OS unsupported");
        #endif
    }
}