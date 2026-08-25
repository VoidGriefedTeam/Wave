#include <THIRD_PARTY\include\nlohmann\json.hpp>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using json = nlohmann::json;

int main(int argc, char* argv[]) 
{
   if (argc < 2)
    {
        std::cout << "Usage: main.exe <file.json>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    if (!file.is_open())
    {
        std::cout << "Could not open: " << argv[1] << '\n';
        return 1;
    }
    
    json cgen;
    file >> cgen;

    std::string import = cgen["import"][0];
    std::string code = cgen["code"][0]; 
    std::string data = cgen["data"]["DATA"];

    size_t pos = code.find("DATA");

    if (pos != std::string::npos)
        code.replace(pos, 4, data);

    

}