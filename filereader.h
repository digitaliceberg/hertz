#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class datFileReader
{
        public: vector<string> getList(string filename)
        {
                vector<string> image_list;
                string line;
                ifstream imageListFile(filename.c_str());
                if(imageListFile.is_open())
                {
                        while(getline(imageListFile, line))
                        {
                                image_list.insert(image_list.end(),line);
                        }
                        imageListFile.close();
                }
                else
                {
                        cout << "Error: Unable to open file" << endl;
                }
                return image_list;
        }
};

