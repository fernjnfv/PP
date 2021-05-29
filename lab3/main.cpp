#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>
constexpr auto SIZE = 16;

const std::string points[SIZE] = { "msk_AP","msk_TS","msk_WH","mzh_TS",
"mzh_WH","zvn_WH","NN_AP","NN_TS", "NN_WH","dzr_TS","dzr_WH",
"vlg_AP","vlg_TS","vlg_WH","kam_TS","kam_WH" };

const std::map<std::string, int> towns = {
    {"Moscow", 2},
    {"Mozhaisk", 4},
    {"Zvenigorod", 5},
    {"Nizhniy Novgorod", 8},
    {"Dzerzhinsk", 10},
    {"Volgograd", 13},
    {"Kamishin", 15} };

const std::map<std::string, int> table = {
    {"msk", 0},
    {"mzh", 1},
    {"zvn", 2},
    {"NN", 3},
    {"dzr", 4},
    {"vlg", 5},
    {"kam", 6} };

const std::tuple<int, int, double> tableCost[21] = {
    {500, 300, 100},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {0, 0, 0},
    {100, 60, 50},
    {500, 300, 100},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {200, 100, 500},
    {100, 60, 50},
    {500, 300, 100},
    {200, 100, 500},
    {100, 60, 50},
    {0, 0, 0},
    {200, 100, 500},
    {100, 60, 50} };

const int matrixDist[SIZE][SIZE] = {
{0, 20, 30, 108, 110, 65, 398, 0, 0, 0, 0, 926, 0, 0, 0, 0},
{20, 0, 10, 98, 100, 55, 0, 415, 0, 483, 0, 0, 937, 0, 1204, 0},
{30, 10, 0, 108, 110, 65, 0, 0, 430, 0, 390, 0, 0, 652, 0, 1234},
{108, 98, 108, 0, 5, 0, 0, 0, 0, 581, 0, 0, 1035, 0, 1302, 0},
{110, 100, 110, 5, 0, 78, 0, 0, 540, 0, 500, 0, 0 ,1062, 0, 1344},
{65, 55, 65, 0, 78, 0, 0, 0, 495, 0, 455, 0, 0, 1017, 0, 1299},
{398, 0, 0, 0, 0, 0, 0, 19, 23, 0, 26, 828, 0, 0, 0, 0},
{0, 415, 0, 0, 0, 0 ,19, 0, 4, 32, 0, 0, 840, 0, 919, 0},
{0, 0, 430, 0, 540, 495, 23, 4, 0, 0, 40, 0, 0, 849, 0, 1010},
{0, 483, 0, 581, 0, 0, 0, 32, 0, 0, 4, 0, 872, 0, 951, 0},
{0, 0, 390, 0, 500, 455, 26, 0, 40, 4, 0, 0, 0, 889, 0, 1050},
{926, 0, 0, 0, 0 ,0 ,828, 0, 0 ,0 ,0, 0, 15, 16, 0, 285},
{0, 937, 0, 1035, 0, 0, 0, 840, 0, 872, 0, 15, 0, 2, 257, 281},
{0, 0, 952, 0, 1062, 1017, 0, 0, 849, 0, 889, 16, 2, 0, 0 ,282},
{0, 1204, 0, 1302, 0, 0, 0, 919, 0, 951, 0, 0, 257, 0, 0, 2},
{0, 0, 1234, 0, 1344, 1299, 0, 0, 1010, 0, 1050, 285, 281, 282, 2, 0} };

//В данной лабораторной Использутся паторны проектирования: Фабричный метод, Стратегии, Мост
enum Type { Turbo, Standart, Economy };

//Паттерн Фабричный метод
class transport
{
protected:
    int Speed;
    int Volume;
    double Price;
    int distance;
public:
    virtual ~transport(){};
    virtual double sumCost(int mass, int dist)
    {
        return (mass / Volume) * sumTime(dist) * Price;
    }
    virtual double sumTime(int dist)
    {
        return dist / Speed;
    }
    virtual int getDistance()
    {
        return this->distance;
    }
};

class Train: public transport
{
    public:
    Train()
    {
        this->Price = 200;
        this->Speed = 100;
        this->Volume = 500;
        this->distance = 0;
    }

    Train(std::tuple<int, int, double> tuple, int dist)
    {
        this->Price = std::get<0>(tuple);
        this->Speed = std::get<1>(tuple);
        this->Volume = std::get<2>(tuple);
        this->distance = dist;
    }
};

class Car:public transport
{
    public:
    Car()
    {
        this->Price = 100;
        this->Speed = 60;
        this->Volume = 50;
        this->distance = 0;
    }

    Car(std::tuple<int, int, double> tuple, int dist)
    {
        this->Price = std::get<0>(tuple);
        this->Speed = std::get<1>(tuple);
        this->Volume = std::get<2>(tuple);
        this->distance = dist;
    }
};

class Plane:public transport
{
    public:
    Plane()
    {
        this->Price = 500;
        this->Speed = 300;
        this->Volume = 100;
        this->distance = 0;
    }

    Plane(std::tuple<int, int, double> tuple, int dist)
    {
        this->Price = std::get<0>(tuple);
        this->Speed = std::get<1>(tuple);
        this->Volume = std::get<2>(tuple);
        this->distance = dist;
    }
};

class Creator {
public:
  virtual ~Creator(){};
  virtual transport* factoryMethod() = 0;
  virtual transport* factoryMethod(std::tuple<int, int, double> tuple, int dist) = 0;
};

class Train_creator:  Creator
{
public:
  transport* factoryMethod()
  {return new Train();}

  transport* factoryMethod(std::tuple<int, int, double> tuple, int dist)
  {return new Train(tuple,dist);}
};

class Car_creator:  Creator
{
public:
  transport* factoryMethod()
  {return new Car();}

  transport* factoryMethod(std::tuple<int, int, double> tuple, int dist)
  {return new Car(tuple,dist);}
};

class Plane_creator:  Creator
{
public:
  transport* factoryMethod()
  {return new Plane();}

  transport* factoryMethod(std::tuple<int, int, double> tuple, int dist)
  {return new Plane(tuple,dist);}
};


class Track
{
    double cost;
    double time;
    int volume;
public:
    Track();
    Track(std::vector<transport>&, int);
    double getCost();
    ~Track();
};

Track::Track()
{
    this->cost = 0;
    this->time = 0;
    this->volume = 0;
}
//Паттерн мост
Track::Track(std::vector<transport>& objects, int volume) {
    for (transport& trans : objects) {
        cost += trans.sumCost(volume, trans.getDistance());
        time += trans.sumTime(trans.getDistance());
    }
}

double Track::getCost()
{
    return this->cost;
}


Track::~Track()
{

}

//Паттерн Стратегии

class Strategy
{
public:
    virtual ~Strategy() {}
    virtual Track use(int* path, int volume) = 0;
};

class Strategy_1: public Strategy
{
public:
    Track use(int* path, int volume){
        std::vector <transport> transport_vec;
        Car_creator car_maker;

        transport *car1 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[0]]))
            {
                car1 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
            }
        }
        transport_vec.push_back(*car1);
        Track track = Track(transport_vec, volume);
        return track;
    }
};

class Strategy_2: public Strategy
{
public:
    Track use(int* path, int volume){
        std::vector <transport> transport_vec;
        Car_creator car_maker;
        Train_creator train_maker;
        Plane_creator plane_maker;

        transport *car1 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[0]]))
            {
                car1 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
            }
        }

        transport *car2 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[2]]))
            {
                car2 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
            }
        }

        transport *train1 = train_maker.factoryMethod();
        transport *plane1 = plane_maker.factoryMethod();
        Track track = Track();
        transport_vec.push_back(*car1);
        transport_vec.push_back(*car2);

        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[1]]) && points[path[1]].find("TS"))
            {
                train1 = train_maker.factoryMethod(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
                transport_vec.push_back(*train1);
                track = Track(transport_vec, volume);
            }

            if ((*it).first.find(points[path[1]]) && points[path[1]].find("AP"))
            {
                plane1 = plane_maker.factoryMethod(tableCost[(*it).second * 3], matrixDist[path[1]][path[2]]);
                transport_vec.push_back(*plane1);
                track = Track(transport_vec, volume);
            }
        }

        return track;
    }
};

class Strategy_3: public Strategy
{
public:
    Track use(int* path, int volume){
        std::vector <transport> transport_vec;
        Car_creator car_maker;
        Train_creator train_maker;
        Plane_creator plane_maker;

        transport *car1 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[0]]))
            {
                car1 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
            }
        }

        transport *train1 = train_maker.factoryMethod();
        transport *plane1 = plane_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[1]]) && points[path[1]].find("TS"))
            {
                train1 = train_maker.factoryMethod(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
            }
            if ((*it).first.find(points[path[1]]) && points[path[1]].find("AP"))
            {
                plane1 = plane_maker.factoryMethod(tableCost[(*it).second * 3], matrixDist[path[1]][path[2]]);
            }
        }

        transport *car2 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[2]]))
            {
                car2 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
            }
        }

        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[3]]) && points[path[3]].find("AP"))
            {
                plane1 = train_maker.factoryMethod(tableCost[(*it).second * 3], matrixDist[path[3]][path[4]]);
            }
            if ((*it).first.find(points[path[3]]) && points[path[3]].find("TS"))
            {
                train1 = plane_maker.factoryMethod(tableCost[(*it).second * 3 + 1], matrixDist[path[3]][path[4]]);
            }
        }

        transport *car3 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[4]]))
            {
                car3 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[4]][path[5]]);
            }
        }
        transport_vec.push_back(*car1);
        transport_vec.push_back(*car2);
        transport_vec.push_back(*car3);
        transport_vec.push_back(*train1);
        transport_vec.push_back(*plane1);
        Track track = Track(transport_vec, volume);
        return track;
    }
};

class Strategy_4: public Strategy
{
public:
    Track use(int* path, int volume){
        std::vector <transport> transport_vec;
        Car_creator car_maker;
        Train_creator train_maker;
        Plane_creator plane_maker;

        transport *car1 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[0]]))
            {
                car1 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[0]][path[1]]);
            }
        }

        transport *train1 = train_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[1]]))
            {
                train1 = train_maker.factoryMethod(tableCost[(*it).second * 3 + 1], matrixDist[path[1]][path[2]]);
            }
        }

        transport *car2 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[2]]))
            {
                car2 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[2]][path[3]]);
            }
        }

        transport *plane1 = plane_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[3]]))
            {
                plane1 = plane_maker.factoryMethod(tableCost[(*it).second * 3], matrixDist[path[3]][path[4]]);
            }
        }

        transport *car3 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[4]]))
            {
                car3 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[4]][path[5]]);
            }
        }

        transport *train2 = train_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[5]]))
            {
                train2 = train_maker.factoryMethod(tableCost[(*it).second * 3 + 1], matrixDist[path[5]][path[6]]);
            }
        }

        transport *car4 = car_maker.factoryMethod();
        for (auto it = table.begin(); it != table.end(); it++)
        {
            if ((*it).first.find(points[path[6]]))
            {
                car4 = car_maker.factoryMethod(tableCost[(*it).second * 3 + 2], matrixDist[path[6]][path[7]]);
            }
        }

        transport_vec.push_back(*car1);
        transport_vec.push_back(*car2);
        transport_vec.push_back(*car3);
        transport_vec.push_back(*car4);
        transport_vec.push_back(*train1);
        transport_vec.push_back(*train2);
        transport_vec.push_back(*plane1);

        Track track = Track(transport_vec, volume);

        return track;
    }
};

class Context
{
protected:
    Strategy* operation;

public:
    virtual ~Context() {}
    virtual Track useStrategy(int* path, int volume) = 0;
    virtual void setStrategy(Strategy* v) = 0;
};

class Context_for_order: public Context
{
public:
    Track useStrategy(int* path, int volume)
    {
        operation->use(path,volume);
    }

    void setStrategy(Strategy* o)
    {
        operation = o;
    }
};


class Order
{
    double cost;
    int volume;
    std::string startPoint;
    std::string finishPoint;
    enum::Type type;
    Track track;

    Context_for_order context;

    Strategy_1 strat_1;
    Strategy_2 strat_2;
    Strategy_3 strat_3;
    Strategy_4 strat_4;
public:
    Order();
    Order(Type, std::string, std::string, int);
    ~Order();
    int decr(std::string);
    int** matrixUpd(Type);
    int* optim(int**, int, int);
    Track best(std::string, std::string, Type, int);
};





Order::Order()
{
    this->cost = 0;
    this->volume = 0;
    this->startPoint = "";
    this->finishPoint = "";
    this->track = Track();
    this->type = Type::Economy;
}

Order::Order(Type deliv, std::string startP, std::string finishP, int vol)
{
    this->startPoint = startP;
    this->finishPoint = finishP;
    type = deliv;
    this->track = best(startP, finishP, deliv, vol);
    this->cost = track.getCost();
    this->volume = vol;
}

Order::~Order()
{

}

Track Order::best(std::string startP, std::string finishP, Type deliv, int volume)
{
    int start = decr(startP);
    int finish = decr(finishP);
    int** mat = new int*[SIZE];
    for (int i = 0; i < SIZE; i++)
        mat[i] = new int[SIZE];
    mat = matrixUpd(deliv);
    int* path = new int[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        path[i] = -1;
    }
    path = optim(mat, start, finish);
    int count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (path[i] != -1)
        {
            count++;
        }
        else
        {
            break;
        }
    }
    switch (count)
    {
    case 1:
    {
        context.setStrategy(&strat_1);
        return context.useStrategy(path, volume);

    }
    case 3:
    {
        context.setStrategy(&strat_2);
        return context.useStrategy(path, volume);

    }
    case 5:
    {
        context.setStrategy(&strat_2);
        return context.useStrategy(path, volume);


    }

    case 7:
    {
        context.setStrategy(&strat_2);
        return context.useStrategy(path, volume);

    }
    }
}

int** Order::matrixUpd(Type type)
{
    int** matrix = new int*[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        matrix[i] = new int[SIZE];
        for (int j = 0; j < SIZE; j++)
        {
            matrix[i][j] = matrixDist[i][j];
        }
    }
    switch (type)
    {
    case Economy:
        for (int i = 0; i < SIZE; i++)
        {
            if (points[i].find("TS"))
                for (int j = 0; j < SIZE; j++)
                    matrix[i][j] = 99999;
        }
    case Standart:
        for (int i = 0; i < SIZE; i++)
        {
            if (points[i].find("AP"))
                for (int j = 0; j < SIZE; j++)
                    matrix[i][j] = 99999;
        }
    case Turbo:
        for (int i = 0; i < SIZE; i++)
        {
            for (int j = 0; j < SIZE; j++)
                if (matrix[i][j] == 0)
                    matrix[i][j] = 99999;
        }
    }
    return matrix;
}

int* Order::optim(int** arr, int beginPoint, int endPoint)
{
    int* d = new int[SIZE];
    int* v = new int[SIZE];
    int temp, minindex, min;
    int begin_index = beginPoint;

    for (int i = 0; i < SIZE; i++)
    {
        d[i] = 99999;
        v[i] = 1;
    }
    d[begin_index] = 0;

    do {
        minindex = 99999;
        min = 99999;
        for (int i = 0; i < SIZE; i++)
        {
            if ((v[i] == 1) && (d[i] < min))
            {
                min = d[i];
                minindex = i;
            }
        }

        if (minindex != 99999)
        {
            for (int i = 0; i < SIZE; i++)
            {
                if (arr[minindex][i] > 0)
                {
                    temp = min + arr[minindex][i];
                    if (temp < d[i])
                    {
                        d[i] = temp;
                    }
                }
            }
            v[minindex] = 0;
        }
    } while (minindex < 99999);

    int* ver = new int[SIZE];
    int end = endPoint;
    ver[0] = end;
    int k = 1;
    int weight = d[end];

    while (end != begin_index)
    {
        for (int i = 0; i < SIZE; i++)
            if (arr[end][i] != 0)
            {
                int temp = weight - arr[end][i];
                if (temp == d[i])
                {
                    weight = temp;
                    end = i;
                    ver[k] = i + 1;
                    k++;
                }
            }
    }
    for (int i = 0; i < k / 2; i++)
        std::swap(ver[i], ver[k - 1 - i]);
    delete[] d, v;
    return ver;
}

int Order::decr(std::string str)
{
    for (auto it = towns.begin(); it != towns.end(); it++)
    {
        if (str._Equal((*it).first))
            return (*it).second;
    }
    return -1;
}
