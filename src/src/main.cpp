#include <iostream>
#include <cstdio>
#include <queue>
#include "Core.h"
#include "Node.h"
#include "MyIO.h"
#include "Checker.h"
#include "Generator.h"
#include "Const.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    //int argc = 3;
    //char* argv[256] = {(char*)"hw.exe", (char*)"-n", (char*)"tf.txt"};
    char head = '\0';
    char tail = '\0';
    bool enable_n = false;
    bool enable_w = false;
    bool enable_m = false;
    bool enable_c = false;
    bool enable_h = false;
    bool enable_t = false;
    bool enable_r = false;
    /* 参数读取 */
    int ptr = 1;
    while (ptr < argc - 1) {
        char* arg = argv[ptr];
        //cout << arg[1] << endl;
        if (arg[0] == '-') {
            switch (arg[1])
            {
            case 'n': {
                if (enable_n) {
                    cout << "duplicate arg: n" << endl;
                    return 0;
                }
                enable_n = true;
                break;
            }
            case 'w': {
                if (enable_w) {
                    cout << "duplicate arg: w" << endl;
                    return 0;
                }
                enable_w = true;
                break;
            }
            case 'm': {
                if (enable_m) {
                    cout << "duplicate arg: m" << endl;
                    return 0;
                }
                enable_m = true;
                break;
            }
            case 'c': {
                if (enable_c) {
                    cout << "duplicate arg: c" << endl;
                    return 0;
                }
                enable_c = true;
                break;
            }
            case 'h': {
                if (enable_h) {
                    cout << "duplicate arg: h" << endl;
                    return 0;
                }
                enable_h = true;
                // 其后紧跟的参数必须为字母，否则报错
                ptr++;
                if ((ptr > argc - 1) || argv[ptr][0] < 'a' || argv[ptr][0] > 'z') {
                    cout << "wrong head" << endl;
                    return 0;
                }
                else {
                    head = argv[ptr][0];
                }
                break;
            }
            case 't': {
                if (enable_t) {
                    cout << "duplicate arg: t" << endl;
                    return 0;
                }
                enable_t = true;
                ptr++;
                if ((ptr > argc - 1) || argv[ptr][0] < 'a' || argv[ptr][0] > 'z') {
                    cout << "wrong tail" << endl;
                    return 0;
                }
                else {
                    tail = argv[ptr][0];
                }
                break;
            }
            case 'r': {
                if (enable_r) {
                    cout << "duplicate arg: r" << endl;
                    return 0;
                }
                enable_r = true;
                break;
            }
            default:
                cout << "unknown arg" << endl;
                return 0;
            }
        }
        else {
            cout << "wrong arg" << endl;
            return 0;
        }
        ptr++;
    }
    //最后一个参数为文件名
    char* filename = argv[argc - 1];
    Checker* checker = new Checker();
    /*参数检查*/
    //n,m为独立应用
    if (enable_n) {
        if (enable_m || enable_w || enable_c || enable_h || enable_t || enable_r) {
            cout << "can not use -n with others" << endl;
            return 0;
        }
    }
    if (enable_m) {
        if (enable_n || enable_w || enable_c || enable_h || enable_t || enable_r) {
            cout << "can not use -m with others" << endl;
            return 0;
        }
    }
    // w与c互斥
    if (enable_w) {
        if (enable_c) {
            cout << "can not use -w with -c" << endl;
            return 0;
        }
    }
    // 必须保证至少有一个输出
    if (!enable_n && !enable_m && !enable_w && !enable_c) {
        cout << "arg has no output" << endl;
        return 0;
    }
    /* 实例化IO */
    MyIO* io = new MyIO(filename);

    /* 读取文件 */
    io->read_file();

    /* 获取输入的单词 */
    char* input[10000];
    int len = io->get_all_words(input);
    
    Generator* generator = new Generator(input, len);
    if (enable_r) {
        generator->build_words();
    }
    else {
        generator->build_nodes();
    }

    /* 环路检测 */
    checker->setup(input, len);
    if (!enable_r) {
        if (!checker->judge_circle()) {
            cout << "has circle" << endl;
            return 0;
        }
    }
    generator->clear();

    /* 计算 */
    Core* core = new Core();
    char* result[MAX_CHAIN_ALL_SIZE] = {NULL};
    int result_len = 0;
    if (enable_n) {
        result_len = core->gen_chains_all(input, len, result);
    }
    if (enable_m) {
        result_len = core->gen_chain_word_unique(input, len, result);
    }
    if (enable_c) {
        result_len = core->gen_chain_char(input, len, result, head, tail, enable_r);
    }
    if (enable_w) {   
        result_len = core->gen_chain_word(input, len, result, head, tail, enable_r);
    }
    if (result_len == 0) {
        cout << "no valid word chain" << endl;
        return 0;
    }
    if (result_len > 20000) {
        cout << "exceed max length 20000" << endl;
        cout << result_len << endl;
        return 0;
    }

    /* 输出 */
    io->write_file(!enable_n, result, result_len);
}