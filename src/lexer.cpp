#include <pch.h>

struct def
{
    std::vector<std::string> code;
    std::unordered_map<std::string, std::string> data;
    std::vector<std::string> import;
};

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: main.exe <file.wave>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cout << "Could not open: " << argv[1] << '\n';
        return 1;
    }
    std::vector<std::string> words;
    std::string word;

    while (file >> word)
        words.push_back(word);

    def config;

    if (words[0].starts_with("print(\"") && words[0].ends_with("\")")) {
        config.import = {
            "<print>"
        };
        config.code = {
            "std::print(DATA);"
        };
        std::string value = words[0].substr(6, words[0].size() - 7);
        config.data["DATA"] = value;
        std::string buffer;
        auto error = glz::write_file_json(config, "output.json", buffer);
    }
    
}

