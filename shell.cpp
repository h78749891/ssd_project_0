// by abin7989

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>

#define LBA_START 0
#define LBA_END 99
using namespace std;
unordered_map<string, int> findCommand;
queue<string> CommandQueue;
bool exitFlag;
enum Command
{
    write,
    read,
    Exit,
    help,
    fullwrite,
    fullread,
    erase,
    erase_range,
    testapp1,
    testapp2
};

bool errorPrint();
bool isValid_between_value(int left, int rigth, int num);
bool isValid_write_value(string num);
bool helpCommand();
bool isValid_lba_num(string num);
bool isCheck_stream(int Qsize);

bool getFile(string filePos);
bool readFile(string ssd_command, string read_file, string buf_pos);
bool writeFile(string ssd_command, string buf_pos, string buf_value);
bool command_write(string ssd_command);
bool command_read(string ssd_command, string read_file);
bool command_fullwrite(string ssd_command);
bool command_fullread(string ssd_command, string read_file);
bool command_erase(string ssd_command);

bool test_app1(string ssd_command, string read_file);
bool test_app2(string ssd_command, string read_file);
void command_init();


bool solution() {
    if (CommandQueue.empty())
        return errorPrint();
    string command = CommandQueue.front();
    CommandQueue.pop();
    auto it_c = findCommand.find(command);
    if (it_c == findCommand.end())
        return errorPrint();


    string ssd_command = "";
    //string ssd_command="C:\\Users\\711-03\\Desktop\\ojt\\";
    //string read_file = "C:\\Users\\711-03\\Desktop\\ojt\\result.txt";
    string read_file = "result.txt";
    
    if (!isCheck_stream(it_c->second))
        return errorPrint();

    switch (it_c->second)
    {
    case Command::write: //write
        return command_write(ssd_command);
    case Command::read: //read
        return command_read(ssd_command, read_file);
    case Command::help: //help
        return helpCommand();
    case Command::fullwrite: //fullwrite
        return command_fullwrite(ssd_command);
    case Command::fullread: //fullread
        return command_fullread(ssd_command, read_file);
    case Command::testapp1: //testapp1
        return test_app1(ssd_command, read_file);
    case Command::testapp2: //testapp2
        return test_app2(ssd_command, read_file);
    case Command::erase:

        break;
    case Command::erase_range:
        break;
    case Command::Exit: //Exit
        exitFlag = false;
        return false;
    default:
        return errorPrint();
    }
}

int main() {
    command_init();

    while (exitFlag) {
        string command;
        getline(cin, command);
        istringstream iss(command);
        string token;
        while (getline(iss,token,' ')) {
            CommandQueue.push(token);
        }
        solution();
    }

    return 0;

}

void command_init() {
    findCommand.insert({ "write", Command::write });
    findCommand.insert({ "read", Command::read });
    findCommand.insert({ "Exit", Command::Exit });
    findCommand.insert({ "help", Command::help });
    findCommand.insert({ "fullwrite", Command::fullwrite });
    findCommand.insert({ "fullread", Command::fullread });
    findCommand.insert({ "testapp1", Command::testapp1 });
    findCommand.insert({ "testapp2", Command::testapp2 });
    findCommand.insert({ "erase",Command::erase });
    findCommand.insert({ "erase_range",Command::erase_range });
    exitFlag = true;
}
bool readFile(string ssd_command, string read_file, string buf_pos) {
    ssd_command.append("ssd.exe R ")
        .append(buf_pos);
    if (system(ssd_command.c_str()))
        return false;
    if (!getFile(read_file))
        return false();
}
bool writeFile(string ssd_command, string buf_pos, string buf_value) {
    ssd_command.append("ssd.exe W ")
        .append(buf_pos)
        .append(" ")
        .append(buf_value).append("\n");
    if (system(ssd_command.c_str()))//ssd.exe 실행
        return false;

    return true;
}

bool command_write(string ssd_command) {
    string buf_pos = CommandQueue.front(); CommandQueue.pop();
    string buf_value = CommandQueue.front(); CommandQueue.pop();
    if (!(isValid_lba_num(buf_pos)))
        return errorPrint();
    if (!isValid_write_value(buf_value))
        return errorPrint();
    if (!writeFile(ssd_command, buf_pos, buf_value))
        return errorPrint();

    return true;
}
bool command_read(string ssd_command, string read_file) {
    string buf_pos = CommandQueue.front(); CommandQueue.pop();
    if (!isValid_lba_num(buf_pos))
        return errorPrint();
    if (!readFile(ssd_command, read_file,buf_pos))
        return errorPrint;

    return true;
}
bool command_fullwrite(string ssd_command) {
    string buf_value = CommandQueue.front(); CommandQueue.pop();
    string temp_ssd_command = ssd_command;
    if (!isValid_write_value(buf_value))
        return errorPrint();
    for (int i = LBA_START; i <= LBA_END; i++) {
        if (!writeFile(ssd_command, to_string(i), buf_value))
            return errorPrint();
    }
    return true;
}
bool command_fullread(string ssd_command, string read_file) {

    string temp_ssd_command = ssd_command;
    for (int i = LBA_START; i <= LBA_END; i++) {
        if (!readFile(ssd_command, read_file, to_string(i)))
            return errorPrint;
        
    }
    return true;
}

bool test_app1(string ssd_command, string read_file) {
    string buf_value = "0xAAAABBBB";
    string temp_ssd_command = ssd_command;

    if (!isValid_write_value(buf_value))
        return errorPrint();
    for (int i = LBA_START; i <= LBA_END; i++) {
        if (!writeFile(ssd_command, to_string(i), buf_value))
            return errorPrint();
    }

    for (int i = LBA_START; i <= LBA_END; i++) {
        if (!readFile(ssd_command, read_file, to_string(i)))
            return errorPrint;

    }
    return true;
}
bool test_app2(string ssd_command, string read_file) {
    string buf_value = "0xAAAABBBB";
    string temp_ssd_command = ssd_command;
    if (!isValid_write_value(buf_value))
        return errorPrint();
     
    for (int k = 0; k < 30; k++) 
        for (int i = 0; i <= 5; i++) 
            if (!writeFile(ssd_command, to_string(i), buf_value))
                return errorPrint();

    buf_value = "0x12345678";

    for (int i = 0; i <= 5; i++)
        if (!writeFile(ssd_command, to_string(i), buf_value))
            return errorPrint();

    for (int i = 0; i <= 5; i++)
        if (!readFile(ssd_command, read_file, to_string(i)))
            return errorPrint;
    return true;
}
bool command_erase(string ssd_command) {
    return true;
}

bool isCheck_stream(int Qsize) {
    switch (Qsize)
    {
    case Command::Exit:
    case Command::help:
    case Command::fullread:
    case Command::testapp1:
    case Command::testapp2:
        if (!CommandQueue.empty())
            return false;
        break;
    case Command::read:
    case Command::fullwrite:
        if (CommandQueue.size() != 1)
            return false;
        break;
    case Command::write:
        if (CommandQueue.size() != 2)
            return false;
        break;
    default:
        return false;
        break;
    }
    return true;
}

bool errorPrint() {
    cout << "INVALID COMMAND\n";
    return false;
}
bool isValid_between_value(int left, int rigth, int num) {
    if (num < left || num>rigth)
        return false;

    return true;
}
bool isValid_write_value(string num) {
    if (num.size() != 10)
        return false;
    if (num[0] != '0' || num[1] != 'x')
        return false;
    bool flag = true;
    for (int i = 2; i < 10; i++) {
        flag = false;
        if (num[i] >= 'A' && num[i] <= 'F')
            flag = true;
        else if (num[i] >= '0' && num[i] <= '9')
            flag = true;

        if (!flag)
            return false;
    }

    return true;
}
bool isValid_lba_num(string num) {
    if (!isValid_between_value(1,2,num.size()))
        return false;
    for (int i = 0; i < num.size(); i++) {
        if (num[i] < '0' || num[i]>'9')
            return false;
    }
    int tempNum = atoi(num.c_str());
    if (tempNum < LBA_START || tempNum>LBA_END)
        return false;

    return true;
}
bool helpCommand() {
    cout << "write     LBA위치에 입력값을 SSD에 작성한다. \n";
    cout << "read      LBA위치에 입력된 값을 SSD에서 가져온다. \n";
    cout << "fullwrite 모든 LBA위치에 입력값을 SSD에 작성한다. \n";
    cout << "fullread  모든 LBA위치에 입련된 값을 SSD에서 가져온다. \n";
    cout << "Exit      프로그램을 종료한다. \n";
    return true;
}
bool getFile(string filePos) {
    string line;
    ifstream file(filePos);
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << "\n";
        }
        file.close();
    }
    else {
        return false;
    }
    return true;
}
