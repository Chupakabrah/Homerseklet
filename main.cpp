#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

void openFile(const string inFnev, const string  outFnev, ifstream &in, ofstream &out);
void AVG(ifstream &in, ofstream &out);
void readF(const string inFnev, ifstream &in);

double fRand(double fMin, double fMax);

int main()
{
    srand(time(NULL));
    string inF;
    string outF;
    char c;
    int dbF, napSzam;
    double minHo, maxHo, r;

    do
    {
        cout << "Fajl db - szam: ";
        cin >> dbF;
        cout << "Napok szama: ";
        cin >> napSzam;
        cout << "Min homerseklet: ";
        cin >> minHo;
        cout << "Max homerseklet: ";
        cin >> maxHo;


        for(int i = 1; i <= dbF; ++i)
        {
            ofstream create;
            string fNev =
                inF = "txtFiles/" + to_string(i) + ".txt";
            create.open(inF);
            for(int i = 0; i < napSzam; ++i)
            {
                r = fRand(minHo,  maxHo);
                create << r << " ";
            }
            create.close();
        }

        for(int i = 1; i <= dbF; ++i)
        {
            ifstream in;
            ofstream out;
            inF = "txtFiles/" + to_string(i) + ".txt";
            outF = "txtFiles/" + to_string(i) + "_result.txt";
            openFile(inF,outF,in,out);
            AVG(in,out);
        }
        cout << endl;

        for(int i = 1; i <= dbF; ++i)
        {
            ifstream adatok;
            ifstream eredmeny;
            inF = "txtFiles/" + to_string(i) + ".txt";
            outF = "txtFiles/" + to_string(i) + "_result.txt";

            readF(inF, adatok);
            readF(outF, eredmeny);
            cout << endl;
        }

        cout << "Adatok elmentve!\n";
        cout << "Ujra futtassam? (I/N): ";
        cin >> c;
        cout << endl;
    }
    while(c != 'n' && c != 'N');


    return 0;
}

void openFile(const string inFnev, const string  outFnev, ifstream &in, ofstream &out)
{
    in.open(inFnev.c_str());
    if(in.fail()) cout << "Hiba!\n";

    out.open(outFnev.c_str());
    if(out.fail()) cout << "Hiba!\n";
}

void AVG(ifstream &in, ofstream &out)
{
    //a1 = eu[0] a2 = eu[1]
    //s1,s2 = sum
    //c1,c2 = napok
    double eu[2];
    double sum = 0.0, val;
    int napok = 0;

    in >> val;
    while(!in.fail() && val >= 0)
    {
        sum += val;
        napok++;
        in >> val;
    }

    eu[0] = ceil(sum / napok * 100) / 100;

    sum = 0.0;
    napok = 0;

    while(!in.fail())
    {
        sum += val;
        napok++;
        in >> val;
    }

    eu[1] = ceil(sum / napok * 100) / 100;

    if(eu[0] != eu[0]) // a1 = NAN?
    {
        out << "Az elso adat fagypont alatti!\nUtani: " << eu[1] << "C";
    }
    else if(eu[1] != eu[1]) // a2 = NAN?
    {
        out << "Elotti: " << eu[0] << "C\nNem volt fagypont alatti adat!";
    }
    else
    {
        out << "Elotti: " << eu[0] << "C\nUtani: " << eu[1] << "C";
    }

    in.close();
    out.close();
}

void readF(const string inFnev, ifstream &in)
{
    in.open(inFnev.c_str());
    if(in.fail()) cout << "Hiba!\n";

    string line;

    while(getline(in,line))
    {
        cout << line << endl;
    }
    in.close();
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    double x = ceil((fMin + f * (fMax - fMin)) * 100.0) / 100;
    return x;
}
