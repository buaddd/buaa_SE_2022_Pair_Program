#include "MyIO.h"
using namespace std;


MyIO::MyIO(string readPath) {
    MyIO::readPath = readPath;
    MyIO::writePath = "solution.txt";
}

//���뵥�ʣ�ȥ�أ�������Ӧ������
void MyIO::read_file() {
    ifstream in(MyIO::readPath);
    string filename;
    string line;
    //unordered_set<string>words;
    if (in) // �и��ļ�
    {
        while (getline(in, line)) // line�в�����ÿ�еĻ��з�
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
    else // �ļ����쳣
    {
        cout << "no such file" << endl;
    }
    in.close();
}

//���
void MyIO::write_file(bool toFile, char** result, int length) {
    if (!toFile) {  //������ն�
        cout << length <<endl;
        for (int i = 0; i < length; i++) {
            cout << result[i] << endl;
        }
    }
    else {  //������ļ�
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