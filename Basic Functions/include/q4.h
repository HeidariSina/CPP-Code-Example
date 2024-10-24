#ifndef Q4_H
#define Q4_H
#include <numeric>

namespace q4
{
    struct Vector2D
    {
        double x{};
        double y{};
    };

    struct Sensor
    {
        Vector2D pos;
        double accuracy;
    };
    static Vector2D kalman_filter(std::vector<Sensor> sensors)
    {
        Vector2D vec{};
        double sumsOfAccuracy{std::accumulate(sensors.begin(), sensors.end(), 0.0, [](double sum, Sensor s)
                                              { return sum + s.accuracy; })};
        vec.y = std::accumulate(sensors.begin(), sensors.end(), 0.0, [](double sum, Sensor s)
                                { return sum + s.pos.y * s.accuracy; }) /
                sumsOfAccuracy;
        vec.x = std::accumulate(sensors.begin(), sensors.end(), 0.0, [](double sum, Sensor s)
                                { return sum + s.pos.x * s.accuracy; }) /
                sumsOfAccuracy;

        return vec;
    }
}

#endif // Q4_H