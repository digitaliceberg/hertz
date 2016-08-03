#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <fstream>
#include "commands.h"

using namespace std;

int debugcout(string str)
{
        int debug_status = 1;
        if(debug_status)
        {
                cout << "DEBUG: " << str << endl;
        }
        return 0;
}


void ReplaceStringInPlace(string& subject, const string& search, const string& replace)
{
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos)
    {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

string LowerCaseString(string str)
{
        transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
}

string DeleteSpecialChar(string str)
{
	static const string arr[] = {"?","!","."};
	vector<string> specials (arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for(int i =0; i < specials.size(); i++)
		ReplaceStringInPlace(str, specials[i], "");
	return str;
}

vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

string sentence_replace(const map<string,string>& map, string str) {
	for(std::map<string,string>::const_iterator it = map.begin(); it != map.end(); it++)
	{
		ReplaceStringInPlace(str, it->first, it->second);
        }
        return str;
}

string vec_assemble(vector<string> vec)
{
	string str;
	for(int i = 0; i< vec.size(); i++)
	{
	str += vec[i];
	if(i < vec.size()-1)
		str += " ";
	}
	return str;
}

string word_replace(const map<string,string>& map, vector<string> vec)
{
	string str;
	for(std::map<string,string>::const_iterator it = map.begin(); it != map.end(); it++)
	{
		for(int i = 0; i < vec.size(); i++)
		{
			if(vec[i] == it->first)
				ReplaceStringInPlace(vec[i], it->first, it->second);
		}
	}
	str = vec_assemble(vec);
	return str;
}

string FormatToReadable(map<string,string> words, map<string,string> vocab,string str)
{
	if(str.substr(0,1) == " ")
		str.erase(0,1);
        ReplaceStringInPlace(str, "'s", " is");
        ReplaceStringInPlace(str, "'re", " are");
        ReplaceStringInPlace(str, "'ll", " will");
	str = DeleteSpecialChar(str);
	str = LowerCaseString(str);
	str = word_replace(vocab,split(str, ' '));
	str = sentence_replace(words,str);
        return str;
}

map<string,string> DatFileLoader(string filename)
{
        map<string,string> ParsedFile;
        string line;
        ifstream myfile(filename.c_str());
        if (myfile.is_open())
        {
                while(getline(myfile,line))
                {
                        vector<string> x = split(line, '|');
			vector<string> question = split(x[0], ':');
			for(int i =0; i < question.size(); i++)
			{
                        ParsedFile[question[i]] = x[1];
			}
                }
                myfile.close();
        }
        else debugcout("Unable to open dat file");
        return ParsedFile;
}


string answer_parse(string str)
{
	vector<string> answers = split(str, ':');
	int random_answer = rand()%answers.size();
	string parsed_answer = answers[random_answer];
	return parsed_answer;
}

string CheckForCommands(string str)
{
	vector<string> answers = split(str, '^');
	if(answers[0] == "+command+")
	{
			if(answers[1] == "time")
				str = formatted_time();
			else if(answers[1] == "version")
				str = ai_version();
			else
				str = answers[1] + " is not a valid command.";
	}
	return str;
}

unsigned int hash(const char* s, unsigned int seed = 0)
{
    unsigned int hash = seed;
    while (*s)
    {
        hash = hash * 101  +  *s++;
    }
    return hash;
}
