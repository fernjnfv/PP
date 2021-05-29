#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

void algorithm();
void UnitTEST();
void backup();
void Full_unit_test();
void simple_test()

string s, first_param, second_param;

bool parse_string(string& path, const string& key, const string& str){
      string::const_iterator it = std::search(str.begin(), str.end(), key.begin(), key.end());
      if ( it == str.end() ) return false;

      std::advance(it, key.length());

      while ( *it++ != '=' ) {}
      while ( *++it == ' ' ) {}

      path.assign(it, str.end());
      return true;
   }

void config_read()
{
    string temp;
    ifstream file("E:/tst.conf");
    while ( !file.eof() ) {
             getline(file, temp);
             if ( !temp.size() || temp[0] == '#' ) continue;
             if ( std::find(temp.begin(), temp.end(), '\r') != temp.end() ) {
                temp.erase(std::remove(temp.begin(), temp.end(), '\r'), temp.end());
             }
             if ( parse_string(first_param, "start_UT", temp) ) {
                break;
             }
             if ( parse_string(second_param, "Backup", temp) ) {
                break;
             }

          }
    file.close();
}
int main() {
    config_read();
    simple_test();
    if(first_param == "true")
        Full_unit_test();
    algorithm();
    if(second_param == "true")
        backup();
}

void simple_test()
{
    string answer,str;
    streambuf* backup;
    streambuf* backup1;
    backup = std::cin.rdbuf();
    backup1 = std::cout.rdbuf();
    ifstream ifs("E:/Simple_test.txt");
    ifstream ifs_ans("E:/Simple_test_answer.txt");
    int iter=1;
    while(!ifs_ans.eof())
    {
        cin.rdbuf(ifs.rdbuf());
        string bf;
        ostringstream str_buf(bf);
        streambuf* x = cout.rdbuf(str_buf.rdbuf());
        cout.rdbuf(str_buf.rdbuf());
        algorithm();
        getline(ifs_ans, answer);
        str = str_buf.str();
        cin.rdbuf(backup);
        cout.rdbuf(backup1);
        if(str.compare(answer))
            cout << "find error in " << iter << " Simple_test.";
        iter++;
    }

    ifs.close();
}

void Full_unit_test()
{
    ifstream ifs_ans("E:/Backup.txt");
    string s = "";
    string answer,str;
    streambuf* backup;
    streambuf* backup1;
    backup = std::cin.rdbuf();
    backup1 = std::cout.rdbuf();
    stringstream  str_buf;
    str_buf <<"0 0 0 0 0 0 0";
    cin.rdbuf(str_buf.rdbuf());
    cout.rdbuf(ifs_ans.rdbuf());
    int iter =1;
    for(double a = 0; a < 3; a+=0.1)
    {
        for(double b = 0; b < 3; b+=0.5)
        {
            for(double c = 0; c < 3; c+=0.5)
            {
                for(double d = 0; d < 3; d+=0.5)
                {
                    for(double e = 0; e < 3; e+=0.5)
                    {
                        for(double f = 0; f < 3; f+=0.5)
                        {
                            s = to_string(a) +" " + to_string(b) + " " + to_string(c) +
                                    " " + to_string(d) + " " + to_string(e) + " " + to_string(f);
                            str_buf << s;
                            string bf;
                            ostringstream str_buf(bf);
                            cout.rdbuf(str_buf.rdbuf());
                            algorithm();
                            str = str_buf.str();
                            getline(ifs_ans, answer);
                            cout.rdbuf(backup1);
                            if(str.compare(answer))
                                cout << "find error in " << iter << " Simple_test.";
                            iter++;
                        }
                    }
                }
            }
        }
    }
    cin.rdbuf(backup);
    cout << "finish UT";
}

void backup()
{
    ofstream ifs_ans("E:/Backup.txt");
    string s = "";
    streambuf* backup;
    streambuf* backup1;
    backup = std::cin.rdbuf();
    backup1 = std::cout.rdbuf();
    stringstream  str_buf;
    str_buf <<"0 0 0 0 0 0 0";
    cin.rdbuf(str_buf.rdbuf());
    cout.rdbuf(ifs_ans.rdbuf());
    for(double a = 0; a < 3; a+=0.1)
    {
        for(double b = 0; b < 3; b+=0.5)
        {
            for(double c = 0; c < 3; c+=0.5)
            {
                for(double d = 0; d < 3; d+=0.5)
                {
                    for(double e = 0; e < 3; e+=0.5)
                    {
                        for(double f = 0; f < 3; f+=0.5)
                        {
                            s = to_string(a) +" " + to_string(b) + " " + to_string(c) +
                                    " " + to_string(d) + " " + to_string(e) + " " + to_string(f);
                            str_buf << s;
                            algorithm();
                            cout << endl;
                        }
                    }
                }
            }
        }
    }
    cin.rdbuf(backup);
    cout.rdbuf(backup1);
    cout << "finish backup";
}

void algorithm()
{
    double a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    if ((a == 0) && (b == 0) && (c == 0) && (d == 0) && (e == 0) && (f == 0))
    {
        cout << '5';
    }
    else if ((a * d - c * b != 0) && ((e * d - b * f != 0) || (a * f - c * e != 0)))
    {
        double y = (a * f - c * e) / (a * d - c * b);
        double x = (d * e - b * f) / (d * a - b * c);
        cout << "2 " << x << ' ' << y;
    }
    else if (((a * d - c * b == 0) && ((e * d - b * f != 0) || (a * f - c * e != 0))) ||
        (a == 0 && c == 0 && e / b != f / d) ||
        (b == 0 && d == 0 && e / a != f / c) ||
        (a == 0 && b == 0 && c == 0 && d == 0 && (e / f > 0)))
    {
        if (((a == 0 && b == 0 && e == 0 && d != 0 && c == 0) ||
            (c == 0 && d == 0 && f == 0 && b != 0 && a == 0)))
        {
            double y;
            if (b == 0)
                y = f / d;
            else if (d == 0)
                y = e / b;
            else if (e == 0 || f == 0)
                y = 0;
            cout << "4" << ' ' << y;
        }
        else if (((a == 0 && b == 0 && e == 0 && c != 0 && d == 0) ||
            (c == 0 && d == 0 && f == 0 && a != 0 && b == 0)))
        {
            double x;
            if (a == 0)
                x = f / c;
            else if (c == 0)
                x = e / a;
            else if (e == 0 || f == 0)
                x = 0;
            cout << "3" << ' ' << x;
        }
        else
            cout << '0';
    }
    else if (a == 0 && c == 0)
    {
        double y;
        if (e == 0)
            y = f / d;
        else if (f == 0)
            y = e / b;
        else
            y = e / b;
        cout << "4" << ' ' << y;
    }
    else if (b == 0 && d == 0)
    {
        double x;
        if (e == 0)
            x = f / c;
        else if (f == 0)
            x = e / a;
        else
            x = e / a;
        cout << "3" << ' ' << x;
    }
    else if (b == 0 && e == 0)
    {
        double k, n;
        k = -c / d;
        n = f / d;
        cout << "1" << ' ' << k << ' ' << n;
    }
    else if (d == 0 && f == 0)
    {
        double k, n;
        k = -a / b;
        n = e / b;
        cout << "1" << ' ' << k << ' ' << n;
    }
    else if (a == 0 && e == 0)
    {
        double k, n;
        k = -d / c;
        n = f / c;
        cout << "1" << ' ' << k << ' ' << n;
    }
    else if (c == 0 && f == 0)
    {
        double k, n;
        k = -b / a;
        n = e / a;
        cout << "1" << ' ' << k << ' ' << n;
    }
    else if ((a / b == c / d))
    {
        double k, n;
        k = -c / d;
        n = f / d;
        cout << "1" << ' ' << k << ' ' << n;
    }
    else
    {
        cout << "Are you kidding me?";
    }
    //return 0;
}
