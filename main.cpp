#include<iostream>
#include<fstream>

using namespace std;

int main(int argc, char** argv)
{
    //Declare an input file stream
    ifstream fileIn;
    //Open file with name sampleInput.txt
    fileIn.open("sampleInput.txt");
    string line;
    while (getline(fileIn, line)) //save the line in string "line"
    {
        cout << line << endl;
    }
}