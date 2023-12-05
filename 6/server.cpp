 #include <sys/msg.h>
 #include <sys/ipc.h>
 #include <sys/wait.h>
 #include <unistd.h>
 
 #include <iostream>
 #include <cstring>
 #include <cstdlib>
 #include <vector> 

 #define MSGKEY 75

 using namespace std; 

 // | \n

 struct mymsg{
	int mtype;
	int mdata;
 } m;

 int msgid; 

 int main(){

	msgid = msgget(MSGKEY, 0666 | IPC_CREAT);

	srand(unsigned(time(0)));
	int number = 1 + rand() % (10-1+1); 
	cout << "Random number for square-check = " << number << endl;

	cout << "Received numbers: ";
	int counter = 0;
	int getted[10]; 
	for (int i = 0; i < 10; i++){
		msgrcv(msgid, &m, sizeof(struct mymsg), 0, 0); 
		if (m.mdata == number*number){
			getted[i] = m.mdata;
			cout << m.mdata <<" ";
		}
		else{
			getted[i] = 0;
			counter ++;
		}
	}

	if (counter == 10){
		cout << "no correct numbers" << endl;
	}
	else{
		cout << endl;
	}

	for (int i = 0; i < 10; i++){
		m.mtype = 1;
		m.mdata = getted[i];
		msgsnd(msgid, &m, sizeof (struct mymsg), 0);
	}
 }