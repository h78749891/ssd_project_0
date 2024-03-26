#include <iostream>
#include <fstream>
#include <cstring>

#define ROW_LENGTH 12
#define DEFAULT_SIZE 100

using namespace std;

struct Memory {
string fNandName;
string fResultName;
fstream fNand;
ofstream fResult;
int size;
char readBuffer[ROW_LENGTH];
char writeBuffer[ROW_LENGTH];

Memory(int size) : fNandName("nand.txt"), fResultName("result.txt"), fNand(), fResult(), size(size) {
setReadBuffer("0x00000000");
readBuffer[ROW_LENGTH - 1] = '\0';
setWriteBuffer("0x00000000");
writeBuffer[ROW_LENGTH - 1] = '\0';
if (!validate()) {
reconstruct();
}
}
~Memory() {
}
bool validate() {
fNand.open(fNandName);
fNand.seekg(0, ios::beg);
for (int colIt = 0; colIt < size; ++colIt) {
string str;
fNand >> str;
if (str.empty()) {
fNand.close();
return false;
}
}
fNand.close();
return true;
}
void reconstruct() {
setWriteBuffer("0x00000000");
for (int it = 0; it < size; ++it) {
write(it);
}
}
void write(int row) {
fNand.open(fNandName);
fNand.seekp(row * ROW_LENGTH, ios::beg);
fNand << writeBuffer << '\n';
fNand.close();
}
void read(int row) {
fNand.open(fNandName);
fNand.seekg(row * ROW_LENGTH, ios::beg);
fNand >> readBuffer;
fNand.close();
}
void setReadBuffer(const char* data) {
for (int dataIt = 0; dataIt < ROW_LENGTH - 1; ++dataIt) {
readBuffer[dataIt] = data[dataIt];
}
}
void setWriteBuffer(const char* data) {
for (int dataIt = 0; dataIt < ROW_LENGTH - 1; ++dataIt) {
writeBuffer[dataIt] = data[dataIt];
}
}
void printResult(int row) {
fResult.open(fResultName);
fResult << "R " << row << ' ' << readBuffer << '\n';
fResult.close();
}
};

int main(int argc, char* argv[]) {
Memory ssd(DEFAULT_SIZE);
if (argc < 2) { return 0; }
else if (argc == 3 && !strcmp(argv[1], "R")) {
int rowToRead = atoi(argv[2]);
ssd.read(rowToRead);
ssd.printResult(rowToRead);
}
else if (argc = 4 && !strcmp(argv[1], "W")) {
int rowToRead = atoi(argv[2]);
ssd.setWriteBuffer(argv[3]);
ssd.write(rowToRead);
}
return 0;
}
