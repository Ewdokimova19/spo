 #include <sys/msg.h>
 #include <sys/ipc.h>
 #include <sys/wait.h>
 #include <stdio.h>
 #include <math.h>
 #include <unistd.h>  
 #include <iostream>
 #include <fstream>
 
 #define MSGKEY 75  

 using namespace std;  
 
 //        \n
 
 struct mymsg{ 
	int mtype; 
	int mdata;
 }m;
 
 int msgid;  
 
int main(){
	
	struct mymsg msg;
 	int mas [10];
 	int count = 0;
 	msgid = msgget (MSGKEY, 0666 | IPC_CREAT);
 
	ifstream in("in_1.txt"); 
	for (int j = 0; j < 10; j++){
 		in >> mas[j];
 	}
	in.close(); 
	cout << "Sending numbers: ";
	for (int i = 0; i < 10; i++){
		cout <<mas[i] <<" ";
 	} 
	cout << endl;
 	for (int i = 0; i < 10; i++){
		m.mtype = 1;
		m.mdata = mas[i];
		msgsnd(msgid, &m, sizeof(struct mymsg), 0);
	}
	if(fork()==0){
		system("~/spo/6/lab6_2");
		exit(0);
	}
	wait(0);

	cout << "Reseived numders: ";
	int result[10];
	int counter = 0;
	for (int i = 0; i < 10; i ++){
		msgrcv(msgid, &m, sizeof(struct mymsg), 0, 0);
		result[i] = m.mdata;
		if (result[i] != 0){
			counter ++;
		}
	}

	if (counter != 10){
		for (int i = 0; i < 10; i++){
			if (result[i] != 0){
				cout << result[i] <<" ";
			}
		}
		cout <<endl;
	}
	else{
		cout << "No correct numbers (((" << endl;
	}
}
	