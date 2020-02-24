#include<iostream>
#include<fstream>
#include<cmath>
#include <time.h>

using namespace std;

//implement a trim function from the web
//http://www.martinbroadhurst.com/how-to-trim-a-stdstring.html
std::string &ltrim(std::string &str, const std::string &chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

std::string &rtrim(std::string &str, const std::string &chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

std::string &trim(std::string &str, const std::string &chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

int main(int argc, char** argv)
{
    srand(time(NULL)); //to reset rand(), to prevent getting the same random number
    //http://www.cplusplus.com/forum/beginner/8388/
    //Declare an input file stream
    ifstream fileIn;
    string fileName = "";
    string line = "";
    int lineLengthSum = 0;
    int lineCount = 0;
    bool hasFilename = false;
    int count_A = 0, count_T = 0, count_C = 0, count_G = 0, count_AA = 0, count_AT = 0, count_AC = 0, count_AG = 0, count_TA = 0, count_TT = 0, count_TC = 0, count_TG = 0, count_CA = 0, count_CT = 0, count_CC = 0, count_CG = 0, count_GA = 0, count_GT = 0, count_GC = 0, count_GG = 0;

    //check if teh user gives a filename
    //http://www.cplusplus.com/forum/general/1796/
    if (argc > 1)
    {
        hasFilename = true;
        fileName = argv[1];
        cout << "fileName: " << fileName << endl;
    }

    //Open file with fileName
    fileIn.open(fileName);

    //to check if the file exists
    if (!fileIn)
    {
        cout << "The file does not exist." << endl;
        exit(1); //if the file is not there, return an error
    }

    while (getline(fileIn, line)) //save the line in string "line"
    {
        for (int i = 0; i < trim(line).length(); ++i)
        {
            line[i] = tolower(line[i]);
            if(line[i] == 'a')
            {
                count_A += 1;
            }
            else if(line[i] == 't')
            {
                count_T += 1;
            }
            else if(line[i] == 'c')
            {
                count_C += 1;
            }
            else if(line[i] == 'g')
            {
                count_G += 1;
            }
        }

        lineCount += 1;
        lineLengthSum += trim(line).length();//add each line length to the total length
        cout << line << endl;
    }

    double mean = lineLengthSum / (double)lineCount;
    fileIn.close();//close reading the file first
    fileIn.open(fileName);
    double temp_variance = 0;
    double variance = 0;

    //calculate the cariance
    while (getline(fileIn, line))
    {
        for(int i = 0; i < trim(line).length(); i += 2)
        {
            line[i] = tolower(line[i]);
            line[i+1] = tolower(line[i+1]);
            if (line[i] == 'a')
            {
                cout << "there is an a" << endl;
                if ((i < trim(line).length() - 1) && (line[i + 1] == 'a'))
                    count_AA += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 't'))
                    count_AT += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'c'))
                    count_AC += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'g'))
                    count_AG += 1;
            }
            else if (line[i] == 't')
            {
                cout << "there is an t" << endl;
                if ((i < trim(line).length() - 1) && (line[i + 1] == 'a'))
                    count_TA += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 't'))
                    count_TT += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'c'))
                    count_TC += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'g'))
                    count_TG += 1;
            }
            else if (line[i] == 'c')
            {
                cout << "there is an c" << endl;
                if ((i < trim(line).length() - 1) && (line[i + 1] == 'a'))
                    count_CA += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 't'))
                    count_CT += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'c'))
                    count_CC += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'g'))
                    count_CG += 1;
            }
            else if (line[i] == 'g')
            {
                cout << "there is an g" << endl;
                if ((i < trim(line).length() - 1) && (line[i + 1] == 'a'))
                    count_GA += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 't'))
                    count_GT += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'c'))
                    count_GC += 1;
                else if ((i < trim(line).length() - 1) && (line[i + 1] == 'g'))
                    count_GG += 1;
            }
        }

        temp_variance += abs(mean - trim(line).length()) * abs(mean - trim(line).length());
    }

    fileIn.close();

    variance = temp_variance / lineCount;
    
    cout << "Total line length sum: " << lineLengthSum << endl;
    cout << "The mean of the length: " << mean << endl;
    cout << "The varianece of the length: " << variance << endl;
    cout << "The satndard deviation of the length: " << sqrt(variance) << endl;
    cout << "The probability of A: " << count_A / (double)lineLengthSum << endl;
    cout << "The probability of T: " << count_T / (double)lineLengthSum << endl;
    cout << "The probability of C: " << count_C / (double)lineLengthSum << endl;
    cout << "The probability of G: " << count_G / (double)lineLengthSum << endl;
    cout << "The probability of AA: " << (double)count_AA / (lineLengthSum/2) << endl;
    cout << "The probability of AT: " << (double)count_AT / (lineLengthSum / 2) << endl;
    cout << "The probability of AC: " << (double)count_AC / (lineLengthSum / 2) << endl;
    cout << "The probability of AG: " << (double)count_AG / (lineLengthSum / 2) << endl;
    cout << "The probability of TA: " << (double)count_TA / (lineLengthSum / 2) << endl;
    cout << "The probability of TT: " << (double)count_TT / (lineLengthSum / 2) << endl;
    cout << "The probability of TC: " << (double)count_TC / (lineLengthSum / 2) << endl;
    cout << "The probability of TG: " << (double)count_TG / (lineLengthSum / 2) << endl;
    cout << "The probability of CA: " << (double)count_CA / (lineLengthSum / 2) << endl;
    cout << "The probability of CT: " << (double)count_CT / (lineLengthSum / 2) << endl;
    cout << "The probability of CC: " << (double)count_CC / (lineLengthSum / 2) << endl;
    cout << "The probability of CG: " << (double)count_CG / (lineLengthSum / 2) << endl;
    cout << "The probability of GA: " << (double)count_GA / (lineLengthSum / 2) << endl;
    cout << "The probability of GT: " << (double)count_GT / (lineLengthSum / 2) << endl;
    cout << "The probability of GC: " << (double)count_GC / (lineLengthSum / 2) << endl;
    cout << "The probability of GG: " << (double)count_GG / (lineLengthSum / 2) << endl;

    //Write all the stats to an output file
    //http://www.cplusplus.com/doc/tutorial/files/
    ofstream fileOut;
    fileOut.open("peterchen.txt");

    fileOut << "Name: Haifan(Peter) Chen\n";
    fileOut << "Student ID: 2326305\n";
    fileOut << "Class: Data Structure - 01\n\n\n";

    fileOut << "The Sum of the length of the DNA strings is: " << lineLengthSum << "\n";
    fileOut << "The Mean of the length of the DNA strings is: " << mean << "\n";
    fileOut << "The variance of the length of the DNA strings is: " << variance << "\n";
    fileOut << "The Standard Deviation of the length of the DNA stings is: " << sqrt(variance) << "\n\n";
    fileOut << "Here is the relative probability of each nucleotide: " << "\n\n";
    fileOut << "A:     " << count_A / (double)lineLengthSum << "\n";
    fileOut << "C:     " << count_C / (double)lineLengthSum << "\n";
    fileOut << "T:     " << count_T / (double)lineLengthSum << "\n";
    fileOut << "G:     " << count_G / (double)lineLengthSum << "\n\n";
    fileOut << "Here is the relative probability of each nucleotide bigram: " << "\n\n";
    fileOut << "AA:     " << (double)count_AA / (lineLengthSum / 2) << "\n";
    fileOut << "AC:     " << (double)count_AC / (lineLengthSum / 2) << "\n";
    fileOut << "AT:     " << (double)count_AT / (lineLengthSum / 2) << "\n";
    fileOut << "AG:     " << (double)count_AG / (lineLengthSum / 2) << "\n";

    fileOut << "CA:     " << (double)count_CA / (lineLengthSum / 2) << "\n";
    fileOut << "CC:     " << (double)count_CC / (lineLengthSum / 2) << "\n";
    fileOut << "CT:     " << (double)count_CT / (lineLengthSum / 2) << "\n";
    fileOut << "CG:     " << (double)count_CG / (lineLengthSum / 2) << "\n";

    fileOut << "TA:     " << (double)count_TA / (lineLengthSum / 2) << "\n";
    fileOut << "TC:     " << (double)count_TC / (lineLengthSum / 2) << "\n";
    fileOut << "TT:     " << (double)count_TT / (lineLengthSum / 2) << "\n";
    fileOut << "TG:     " << (double)count_TG / (lineLengthSum / 2) << "\n";

    fileOut << "GA:     " << (double)count_GA / (lineLengthSum / 2) << "\n";
    fileOut << "GC:     " << (double)count_GC / (lineLengthSum / 2) << "\n";
    fileOut << "GT:     " << (double)count_GT / (lineLengthSum / 2) << "\n";
    fileOut << "GG:     " << (double)count_GG / (lineLengthSum / 2) << "\n";

    double temp_arr[1000];
    double new_Sum = 0;
    double a = 0.0, b = 0.0, c = 0.0, d = 0.0;

    for(int i=0; i<1000; ++i)
    {
        a = rand() / (double)RAND_MAX;
        b = rand() / (double)RAND_MAX;
        c = sqrt(-2.0 * log(a)) * cos(2.0 * M_PI * b);
        d = sqrt(variance) * c + mean;

        temp_arr[i] = d;
        new_Sum += d;
    }

    int temp_variance2 = 0;

    cout << "Mean: " << new_Sum / 1000.0 << endl;

    for (int i = 0; i < 1000; ++i)
    {
        temp_variance2 += abs((new_Sum / 1000.0) - temp_arr[i]) * abs((new_Sum / 1000.0) - temp_arr[i]);
    }
    cout << "Variance: " << temp_variance2/1000.0 << endl;
    cout << "Standard deviation: " << sqrt(temp_variance2/1000.0) << endl;
}