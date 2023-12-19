#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct MatrixMsg {
long mtype;
int matrix[4][4];
};

int main() {
// Создать ключ с использованием ftok
key_t key = ftok("mykeyfile", 'A');

// Получить доступ к очереди сообщений
int msgid = msgget(key, IPC_CREAT | 0666);

// Если не удалось получить доступ к очереди сообщений, завершить выполнение
if (msgid < 0) {
std::cerr << "Ошибка при получении доступа к очереди сообщений" << std::endl;
return 1;
}

// Считать матрицу из файла
std::ifstream inputFile("matrix.txt");
if (!inputFile.is_open()) {
std::cerr << "Ошибка при открытии файла" << std::endl;
return 1;
}

MatrixMsg matrixMsg;
matrixMsg.mtype = 1; // Тип сообщения для второго приложения

for (int i = 0; i < 4; ++i) {
for (int j = 0; j < 4; ++j) {
inputFile >> matrixMsg.matrix[i][j];
}
}

// Отправить матрицу в очередь сообщений
if (msgsnd(msgid, &matrixMsg, sizeof(matrixMsg.matrix), 0) == 0) {
std::cout << "Матрица успешно отправлена." << std::endl;
} else {
std::cerr << "Ошибка при отправке матрицы." << std::endl;
}

return 0;
}