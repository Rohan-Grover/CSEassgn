#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

// char *home;
char *uspath;
int prompt()
{
    char *usname = (char*)malloc(64 * sizeof(char*));
    char *ushost = (char*)malloc(64 * sizeof(char*));
    // char *uspath = (char*)malloc(4096 * sizeof(char*));

    
    usname = getenv("USER");
    uspath = getcwd(uspath,4096);
    gethostname(ushost, 64); 

    printf("\n%s@%s:%s$ ",usname,ushost,uspath);

}
int main(){

    int x=2,m=0;
    // get tilda

    char *uspath = (char*)malloc(4096 * sizeof(char*));
    uspath = getcwd(uspath,4096);
    char *home = uspath;
    printf("%s",home);

    char *str1 = (char*)malloc(100 * sizeof(char*));    

    do
    {
        prompt();
        size_t buf_siz = 32;
        char* token = "a";
        char *buf = (char*)malloc(64* sizeof(char*));   
        char **command_list = (char**)malloc(330*sizeof(char**));
        ssize_t and = getline(&buf,&buf_siz,stdin);
        if(buf[and-1] == '\n')
            buf[and-1] = '\0';

        int i=0;
        while(strcmp(buf,""))
        {
            char **saveptr = malloc(sizeof(char**));
            __strtok_r(buf, ";", saveptr);
            // printf("%s\n", buf);
            command_list[i++] = buf;
            buf = *saveptr;
        }   

        char **cmd_arg = (char**)malloc(50*sizeof(char**));

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
            
            if(strcmp(cmd_arg[0],"echo")==0)
            {
                for(int j = 1;cmd_arg[j]!=NULL;++j)
                {
                    printf("%s",cmd_arg[j]);
                }
                    
            }

            if(strcmp(cmd_arg[0],"cd")==0)
            {
                if(cmd_arg[1] == NULL)
                    chdir(home);
                else if(cmd_arg[1][0] == '~')
                {
                    if(cmd_arg[1][1] == '\0' )
                        chdir(home);

                
                    // else
                    // {
                    //     chdir(home);
                    //     for(int j = 2; cmd_arg[1][j] != '0';++j)
                    //     {
                    //         strcat(str1,cmd_arg[1][j]);
                    //         chdir(str1);
                    //     }
                    // }
                }
                
                else
                {
                    chdir(cmd_arg[1]);
                }

                
            }
        }

    


      
    
    }
    while(x--);
}