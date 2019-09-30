#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include <iostream>
#include <sys/wait.h>
#include<vector>
using namespace std;
int main(int argc, char **argv) {

int fds_1[2];
int fds_2[2];
pipe(fds_1);
pipe(fds_2);
vector<pid_t> kids;

pid_t kid_1;
kid_1 = fork();
kids.push_back(kid_1);

char *var[1];
var[0]=NULL;

if (kid_1==0){

char* argvR[argc+1];
for (int args =0; args < argc; args++) {
                argvR[args] = argv[args];
                }
argvR[argc] = NULL;


close(fds_1[0]);
dup2(fds_1[1],STDOUT_FILENO);
close(fds_1[1]);
if(execv("./rgen",argvR)==-1){perror("Error");}
}

pid_t kid_2;
kid_2 = fork();
kids.push_back(kid_2);

if(kid_2==0){

close(fds_1[1]);
dup2(fds_1[0],STDIN_FILENO);
close(fds_1[0]);

close(fds_2[0]);
dup2(fds_2[1],STDOUT_FILENO);
close(fds_2[1]);

char *args_py[3];
args_py[0] = (char*)"usr/bin/python";
args_py[1] = (char*)"./a1ece650";
args_py[2] = NULL;

if(execv("/usr/bin/python", args_py)==-1){perror("Error");}

}

pid_t kid_3;
kid_3 = fork();
kids.push_back(kid_3);
if(kid_3==0){
close(fds_2[1]);
dup2(fds_2[0],STDIN_FILENO);
close(fds_2[0]);
if(execv("./a2-ece650",var)==-1){
int i=0;

}
}

pid_t kid_4;
kid_4 = fork();
kids.push_back(kid_4);

if(kid_4==0){
close(fds_2[0]);
dup2(fds_2[1],STDOUT_FILENO);
close(fds_2[1]);


while (1) {
        string line;
        getline(cin, line);
        if (line.size () > 0) {
            cout << line << endl;
	    cout.flush();
		}
    }

}

for (int i=0; i<kids.size();i++) {
        int status;
        waitpid(kids[i], &status, 0);
        kill (kids[i], SIGTERM);

    }
cout<<"Parent executed"<<endl;
return 0;
}
