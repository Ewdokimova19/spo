#include <iostream>
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
int msgid = msgget(key, 0);

// Если не удалось получить доступ к очереди сообщений, завершить выполнение
if (msgid < 0) {
std::cerr << "Ошибка при получении доступа к очереди сообщений" << std::endl;
return 1;
}

// Принять матрицу от первого приложения
MatrixMsg matrixMsg;
msgrcv(msgid, &matrixMsg, sizeof(matrixMsg.matrix), 1, 0);

// Вычислить суммы строк и столбцов
int rowSums[4] = {0};
int colSums[4] = {0};

for (int i = 0; i < 4; ++i) {
for (int j = 0; j < 4; ++j) {
rowSums[i] += matrixMsg.matrix[i][j];
colSums[j] += matrixMsg.matrix[i][j];
}
}

// Вывести результаты
std::cout << "Суммы строк: ";
for (int i = 0; i < 4; ++i) {
std::cout << rowSums[i] << " ";
}
std::cout << std::endl;

std::cout << "Суммы столбцов: ";
for (int j = 0; j < 4; ++j) {
std::cout << colSums[j] << " ";
}
std::cout << std::endl;

return 0;
}