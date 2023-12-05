 #include <iostream>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <sys/wait.h>
 #include <unistd.h>
 
#include <cstring>
#include <string>

// using namespace std;

enum class MenuAction { doCmd, runScript, doTask, exit };


void displayMenu() {
    std::cout << "Menu\n"
                << "0 - doCmd\n"
                << "1 - runScript\n"
                << "2 - doTask\n"
                << "3 - exit\n";
}

void doCmd() {
    auto status = 0;
    if (fork() == 0){
        char cmd [256];
        std::cout << "Enter shell cmd : \n";
        std::cin.clear();
        std::cin >> cmd;
        std::cout << std::endl;
        system(cmd);
        exit(0);
    }
    wait(&status);
}

void runScript() {
    auto status = 0;

    if (fork() == 0) {
        system("~/spo/lab1.sh");
        exit(0);
    }
    wait(&status);
}

void doTask() {
    auto status = 0;
    if (fork() == 0) {
        auto pid = 0;
        std::cout << "Enter pid the process you want to kill:\n";
        std::cin >> pid;
        kill(pid, SIGKILL);
        exit(0);
    }   
     wait(&status);   
}

int main()
{
    auto choice = 0;
    do {
        displayMenu();
        std::cout << "Enter your choice:\n";
        std::cin >> choice;
   
        switch (static_cast<MenuAction>(choice)) {
            case MenuAction::doCmd:
                doCmd(); break;
            case MenuAction::runScript:
                runScript(); break;
            case MenuAction:: doTask:
                doTask(); break;
            case MenuAction::exit:
                exit(0); break;
            default:
                std::cout << "Invalid input\n"; break;
            }
    }   while (true);       
}

  



 









