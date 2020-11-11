#include <iostream>
#include <cmath>
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
using namespace std;

struct point {
    double x, y, f;
};

double func(double x,double y)
{
    return -sqrt(log(1 + x * x + y * y));
}

bool comparator(point& p1, point& p2) {
    return (p1.f > p2.f);
}

point gen_point(point& p1, point& p2) {
    point buf;
    buf.x = p1.x;
    buf.y = p2.y;
    buf.f = func(buf.x, buf.y);
    return buf;
}

vector<point> gen_population(vector<point>& population) {
    vector<point> buf(4);
    if (population[0].f == population[1].f) {
        buf[0] = gen_point(population[0], population[2]);
        buf[1] = gen_point(population[2], population[0]);
        buf[2] = gen_point(population[0], population[3]);
        buf[3] = gen_point(population[3], population[0]);
    }
    else {
        double p = rand() / RAND_MAX;
        buf[0] = gen_point(population[0], population[1]);
        buf[1] = gen_point(population[1], population[0]);
        int i, l;
        if (p - 0.5 <= 0) {
            i = 2;
            l = 0;
        }
        else {
            i = 1;
            l = 2;
        }
        buf[2] = gen_point(population[l], population[i]);
        buf[3] = gen_point(population[i], population[l]);
    }
    return buf;
}

double get_mid(vector<point>& pop) {
    double sum = 0;
    for (auto i : pop) {
        sum += i.f;
    }
    return sum / 4;
}

void print_population(vector<point>& pop, int n) {
    cout << "N = " << n << " Middle = " << get_mid(pop) << " Maximum = " << pop[0].f << endl;
    for (auto i : pop) {
        cout << "x = " << i.x << " y = " << i.y << " f =" << i.f << endl;
    }
}

int main(){
    int N = 4;
    int a = -1, b = 1;
    srand(time(NULL));
    vector<point> population(4);
    for (int i = 0; i < N; i++) {
        point poi;
        poi.x = (double)(a + rand() * 1. / RAND_MAX * (b - a));
        poi.y = (double)(a + rand() * 1. / RAND_MAX * (b - a));
        poi.f = func(poi.x, poi.y);
        population[i] = poi;
    }
    sort(population.begin(), population.end(), comparator);
    print_population(population, 0); 
    for (int i = 1; i < 50; i++) {
        double ver = rand() / RAND_MAX;
        if (ver - 0.4 <= 0) {
            point p;
            p.x = (double)(population[0].x + (a + rand() * 1. / RAND_MAX * (b - a)))/2;
            population[0] = gen_point(population[0], p);
            p.y = (double)(population[1].y + (a + rand() * 1. / RAND_MAX * (b - a)))/2;
            population[1] = gen_point(p, population[1]);
            p.x = (double)(population[2].x + (a + rand() * 1. / RAND_MAX * (b - a)))/2;
            population[2] = gen_point(population[2], p);
            p.y = (double)(population[3].y + (a + rand() * 1. / RAND_MAX * (b - a))) / 2;
            population[3] = gen_point(p, population[3]);
        }
        sort(population.begin(), population.end(), comparator);
        vector<point> new_p = gen_population(population);
        population = new_p;
        print_population(population, i);
    }
    return 0;
}
