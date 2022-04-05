#include "MyIO.h"
using namespace std;


MyIO::MyIO(string readPath) {
    MyIO::readPath = readPath;
    MyIO::writePath = "solution.txt";
}

//读入单词，去重，构建对应的数组
void MyIO::read_file() {
    ifstream in(MyIO::readPath);
    string filename;
    string line;
    //unordered_set<string>words;
    if (in) // 有该文件
    {
        while (getline(in, line)) // line中不包括每行的换行符
        {
            //cout << line << endl;
            int length = 0;
            int pos = 0;
            for (int i = 0; i < line.size(); i++) {
                if (line[i] <= 'z' && line[i] >= 'a' || line[i] <= 'Z' && line[i] >= 'A') {
                    length++;
                }
                else {
                    if (length > 1) {
                        string str = line.substr(pos, length);
                        transform(str.begin(), str.end(), str.begin(), ::tolower);
                        words.insert(str);
                    }
                    length = 0;
                    pos = i + 1;
                }
            }
            if (length > 1) {
                string str = line.substr(pos, length);
                transform(str.begin(), str.end(), str.begin(), ::tolower);
                words.insert(str);
            }
        }
    }
    else // 文件名异常
    {
        cout << "no such file" << endl;
    }
    in.close();
}

//输出
void MyIO::write_file(bool toFile, char** result, int length) {
    if (!toFile) {  //输出到终端
        cout << length <<endl;
        for (int i = 0; i < length; i++) {
            cout << result[i] << endl;
        }
    }
    else {  //输出到文件
        std::ofstream out(MyIO::writePath);
        //cout << length << endl;
        for (int i = 0; i < length; i++) {
            //cout << result[i] << endl;
            out << result[i] << endl;
        }
    }
}

int MyIO::get_all_words(char** input) {
    unordered_set<string>::iterator it;
    int ptr = 0;
    for (it = words.begin(); it != words.end(); it++) {
        char* c = (char*)((*it).c_str());
        input[ptr] = c;
        ptr++;
    }
    return ptr;
}