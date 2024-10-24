#ifndef Q3_H
#define Q3_H

#include <iostream>
#include <queue>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>
#include <vector>

namespace q3
{
    struct Flight
    {
        std::string flight_number;
        size_t duration;
        size_t connections;
        size_t connection_times;
        size_t price;
    };
    static auto compare{[](Flight a, Flight b)
                        { return (a.duration + a.connection_times + 3 * a.price) > (b.duration + b.connection_times + 3 * b.price); }};

    static auto gather_flights(std::string filename)
    {
        std::priority_queue<Flight, std::vector<Flight>, decltype(compare)>
            flights{compare};
        std::stringstream filestream{};
        std::ifstream file(filename);
        filestream << file.rdbuf();
        std::string filetxt{filestream.str()}, time{};
        std::regex model(R"(\d+\- \w+\:(\w+)\ - \w+\:(\d+\h\d*\m*)\ - \w+\:(\d+)\ - \w+\:(\d+\h\d*\m*)\,?(\d*\h*\d*\m*)\,?(\d*\h*\d*\m*) - \w+\:(\d+))"), model2(R"((\d+)\h(\d+)?\m?)");
        std::smatch find, find2;
        while (std::regex_search(filetxt, find, model))
        {
            Flight fli{};
            fli.flight_number = find[1];

            fli.duration = 0;
            time = find[2];
            if (!time.empty())
            {
                std::regex_search(time, find2, model2);
                fli.duration += std::stoi(find2[1]) * 60;
                std::string min{find2[2]};
                if (!min.empty())
                    fli.duration += std::stoi(min);
            }

            fli.connections = std::stoi(find[3]);

            fli.connection_times = 0;
            time = find[4];
            if (!time.empty())
            {
                std::regex_search(time, find2, model2);
                fli.connection_times += std::stoi(find2[1]) * 60;
                std::string min{find2[2]};
                if (!min.empty())
                    fli.connection_times += std::stoi(min);
            }
            time = find[5];
            if (!time.empty())
            {
                std::regex_search(time, find2, model2);
                fli.connection_times += std::stoi(find2[1]) * 60;
                std::string min{find2[2]};
                if (!min.empty())
                    fli.connection_times += std::stoi(min);
            }
            time = find[6];
            if (!time.empty())
            {
                std::regex_search(time, find2, model2);
                fli.connection_times += std::stoi(find2[1]) * 60;
                std::string min{find2[2]};
                if (!min.empty())
                    fli.connection_times += std::stoi(min);
            }
            fli.price = std::stoi(find[7]);
            flights.push(fli);
            filetxt = find.suffix().str();
        }
        return flights;
    }
}
#endif // Q3_H