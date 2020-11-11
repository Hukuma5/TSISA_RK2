#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <algorithm>
#include <time.h>

double func(double x, double y) {
    return -sqrt(log(1 + x * x + y * y));
}

struct Point {
    double x, y;
    double fit;
};

double sr_value(const std::vector<Point>& v) {
    double res = 0.0;
    for (const auto& a : v) {
        res += a.fit;
    }
    return res / 4;
}

void print_results(const std::vector<Point>& v, size_t n) {
    std::cout << "N = " << n << " Average = " << sr_value(v) << " Max = " << v[0].fit << std::endl;
    for (const auto& a : v) {
        std::cout << "x = " << a.x << " y = " << a.y << " fit = " << a.fit << std::endl;
    }
}

bool ComparePoint(const Point& p1, const Point& p2) {
    return p1.fit > p2.fit;
};

int main() {
    std::vector<Point> population;
    population.resize(4);
    std::mt19937 gen(time(NULL));
    std::uniform_real_distribution<double> dis(-1.1, 1.1);
    std::uniform_real_distribution<double> dis_mut(-5, 5);
    std::uniform_real_distribution<double> ver(0, 1);
    int n = 50;
    double p_mut = 0.40;

    for (auto i = 0; i < population.size(); i++) {
        Point poi;
        poi.x = dis(gen);
        poi.y = dis(gen);
        poi.fit = func(poi.x, poi.y);
        population[i] = poi;
    }

    std::sort(population.begin(), population.end(), ComparePoint);
    print_results(population, 0);
    for (auto i = 1; i <= n; i++) {
        for (auto j = 0; j < population.size(); j++) {
            auto p = ver(gen);
            if (p_mut > p) {
                population[j].x = fmod(population[j].x * dis_mut(gen), 1);
                population[j].y = fmod(population[j].y * dis_mut(gen), 1);
                population[j].fit = func(population[j].x, population[j].y);
            }
        }
        std::sort(population.begin(), population.end(), ComparePoint);
        std::vector<Point> new_population;
        new_population.resize(4);
        size_t z;
        if (population[0].fit >= population[1].fit) {
            z = 1;
        }
        else {
            z = 2;
        }
        new_population[0].x = population[0].x;
        new_population[0].y = population[z].y;
        new_population[0].fit = func(new_population[0].x, new_population[0].y);

        new_population[1].x = population[z].x;
        new_population[1].y = population[0].y;
        new_population[1].fit = func(new_population[1].x, new_population[1].y);

        new_population[2].x = population[0].x;
        new_population[2].y = population[z + 1].y;
        new_population[2].fit = func(new_population[2].x, new_population[2].y);

        new_population[3].x = population[z + 1].x;
        new_population[3].y = population[0].y;
        new_population[3].fit = func(new_population[3].x, new_population[3].y);

        std::sort(new_population.begin(), new_population.end(), ComparePoint);
        population = new_population;
        print_results(population, i);
    }
    return 0;
}
