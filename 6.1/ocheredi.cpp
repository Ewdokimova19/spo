#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

struct mymsg
{
    long mtype;
    int mdata;
};

int countDigits(const char *str, char digit)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == digit)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    char inputString[100];
    std::cout << "Введите строку: ";
    std::cin.getline(inputString, sizeof(inputString)); // Используем getline для ввода строки

    int num_processes = 10; // Количество процессов (по одному на каждую цифру от 0 до 9)

    int msgid;

    if ((msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666)) == -1)
    {
        perror("msgget");
        return 1;
    }

    for (int i = 0; i < num_processes; i++)
    {
        if (fork() == 0)
        {
            int result = countDigits(inputString, '0' + i);

            struct mymsg message;
            message.mtype = i + 1; // Тип сообщения равен номеру процесса
            message.mdata = result;

            if (msgsnd(msgid, &message, sizeof(int), 0) == -1)
            {
                perror("msgsnd");
                return 1;
            }
            return 0;
        }
    }

    int digit_counts[10] = {0};

    for (int i = 0; i < num_processes; i++)
    {
        /* struct*/ mymsg message; // необязательно (не приветствуется)
        if (msgrcv(msgid, &message, sizeof(int), i + 1, 0) == -1)
        {
            perror("msgrcv");
            return 1;
        }
        digit_counts[i] = message.mdata;
    }

    std::cout << "Количество встречающихся цифр:" << std::endl;
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Цифра '" << i << "': " << digit_counts[i] << std::endl;
    }

    // Ожидание завершения всех дочерних процессов
    for (int i = 0; i < num_processes; i++)
    {
        wait(NULL);
    }

    // Удаление очереди сообщений
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
    }

    return 0;
}
