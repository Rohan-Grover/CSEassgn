#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string.h>
#include <pwd.h>
#include<time.h>
#include<sys/wait.h> 
#include<fcntl.h> 
#include "file.h"
  
int prompt()
{
    char *usname = (char*)malloc(64 * sizeof(char*));
    char *ushost = (char*)malloc(64 * sizeof(char*));

    
    usname = getenv("USER");
    uspath = getcwd(uspath,4096);
    gethostname(ushost, 64); 

    printf("\n%s@%s:%s$ ",usname,ushost,uspath);

}
void handle_sigchld(int sig) 
{ 
    int stats;
    pid_t cpid = waitpid(-1,&stats,WNOHANG);
    if (WIFEXITED(stats))
    { 
        for(int i = 0; i<=count;++i)
        {
            if(abc[i].pid == cpid)
            {
                printf("%s with pid %d exited normally \n",abc[i].job, cpid); 
                abc[i].pid = 0;
                strcpy(abc[i].job,"");
            }
        }
    }
} 
int main(){
    count=0,flag=0;
    x=2;
    m=0;
    r=0;
    homey = (char*)malloc(4096 * sizeof(char*));
    uspath = (char*)malloc(4096 * sizeof(char*));
    buffer = (char*)malloc(4096 * sizeof(char*));
    buffers = (char*)malloc(4096 * sizeof(char*));
    uspath = getcwd(uspath,4096);
    home = uspath;

    str1 = (char*)malloc(100 * sizeof(char*));    
    cmd_arg = (char**)malloc(50*sizeof(char**));
    command_list = (char**)malloc(330*sizeof(char**));
    saveptr = malloc(sizeof(char**));
    saveptrs = malloc(sizeof(char**));
    do
    {
        signal(SIGCHLD, handle_sigchld);
        prompt();
        for(int i=0;i<50;++i)
            cmd_arg[i] = NULL;
        size_t buf_siz = 32;
        char* token = "a";
        char *buf = (char*)malloc(64* sizeof(char*));   
        ssize_t and = getline(&buf,&buf_siz,stdin);
        if(buf[and-1] == '\n')
            buf[and-1] = '\0';

        int i=0;
        while(strcmp(buf,""))
        {
            __strtok_r(buf, ";", saveptr);
            command_list[i++] = buf;
            buf = *saveptr;
        }  
         


        for(int i =0;command_list[i]!= NULL;++i)
        {
            m=0;
            buf = command_list[i];
            while(strcmp(buf,""))
            {
                char **saveptr = malloc(sizeof(char**));
                __strtok_r(buf, " ", saveptr);
                cmd_arg[m++] = buf;
                buf = *saveptr;
            }


            if(strcmp(cmd_arg[0],"pwd")==0)
            {
                uspath = getcwd(uspath,4096);
                printf("%s",uspath);
            }
            
            else if(strcmp(cmd_arg[0],"echo")==0)
            {
                for(int j = 1;cmd_arg[j]!=NULL;++j)
                {
                    printf("%s",cmd_arg[j]);
                }
                    
            }

            else if(strcmp(cmd_arg[0],"cd")==0)
            {
               cd();

            }

            else if(strcmp(cmd_arg[0],"ls")==0)
            {
                ls();
            }

            else if(strcmp(cmd_arg[0],"pinfo")==0)
            {
                pinfo(); 
            }
            else if(strcmp(cmd_arg[0],"setenv")==0)
            {
                if(cmd_arg[1] == NULL)
                {
                    printf("Not enough command line arguments\n");
                    continue;
                }
                else if(cmd_arg[3] != NULL)
                {
                    printf("Too many arguments\n");
                    continue;
                }

                else
                {
                    //changing according to will
                    if(cmd_arg[2] == NULL)
                        setenv(cmd_arg[1], "", 1);
                    else
                        setenv(cmd_arg[1], cmd_arg[2], 1);

                }
            }
            else if(strcmp(cmd_arg[0],"unsetenv")==0)
            {
                if(cmd_arg[1] == NULL)
                {
                    printf("Not enough command line arguments\n");
                    continue;
                }
                else
                {
                    //changing according to will
                    unsetenv(cmd_arg[1]);
                }
            }
            else if(strcmp(cmd_arg[0],"jobs")==0)
            {
                joba();
            }
            else if(strcmp(cmd_arg[0],"kjob")==0)
            {
                counta =1;
                for(int l = 0; l<count;++l)
                {
                    if(abc[l].pid != 0)
                    {
                        if(atoi(cmd_arg[1]) == counta)
                        {
                            kill(abc[l].pid,atoi(cmd_arg[2]));
                            abc[l].pid = 0;
                            strcpy(abc[l].job,"");   
                        }
                        counta++;
                    }
                }
            }
            else if(strcmp(cmd_arg[0],"overkill")==0)
            {
                for(int l = 0; l<count;++l)
                {
                    if(abc[l].pid != 0)
                    {
                        kill(abc[l].pid,9);
                        abc[l].pid = 0;
                        strcpy(abc[l].job,"");
                    }
                }
            }


            else
            {
                if(cmd_arg[1]!=NULL && strcmp(cmd_arg[1],"&\n"))
                {
                    if ((pid = fork()) == 0)
                    {
                        execvp(cmd_arg[0],cmd_arg);
                        
                    }
                    else
                    {
                        abc[count].pid=pid;
                        // printf()
                        strcpy(abc[count].job,cmd_arg[0]);
                        count++;
                        if(count == 1000)
                            count = 0;
                    }   
                    
                
                }
                else
                {
                    if(fork() == 0)
                       execvp(cmd_arg[0],cmd_arg);
                    else
                        wait(NULL);
                }
            
            }
            
            
        }
        continue; 
        
    }
    while(strcmp(cmd_arg[0],"quit"));
}