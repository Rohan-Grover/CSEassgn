#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
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

    int x=2,m=0,r=0;
    // get tilda
    char *homey = (char*)malloc(4096 * sizeof(char*));
    char *uspath = (char*)malloc(4096 * sizeof(char*));
    uspath = getcwd(uspath,4096);
    char *home = uspath;
    printf("%s",home);

    char *str1 = (char*)malloc(100 * sizeof(char*));    
    char **cmd_arg = (char**)malloc(50*sizeof(char**));

    do
    {
        prompt();
        for(int i=0;i<50;++i)
            cmd_arg[i] = NULL;
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
                    // printf("YEET");
                    if(cmd_arg[1][1] == '\0' )
                        chdir(home);

                
                    else
                    {
                        char *ptr1 = cmd_arg[1];
                        ptr1 += 1;
                        homey = home;
                        strcat(homey,ptr1);
                        chdir(homey); 
                    }
                }
                
                else
                {
                    chdir(cmd_arg[1]);
                }

            }

             if(strcmp(cmd_arg[0],"ls")==0)
             {
                
                if(cmd_arg[1] == NULL)
                {
                    DIR *cwd;
                    struct dirent *dir_struct;
                    cwd = opendir(".");
                    if (cwd)
                    {
                        while ((dir_struct = readdir(cwd)) != NULL)
                        {
                            if(strcmp(dir_struct->d_name,".") && strcmp(dir_struct->d_name,".."))
                                printf("%s\n", dir_struct->d_name);
                        }
                        closedir(cwd);
                    }
                }

                else if(!strcmp(cmd_arg[1],"-a"))
                {
                    DIR *cwd;
                    struct dirent *dir_struct;
                    cwd = opendir(".");
                    if (cwd)
                    {
                        while ((dir_struct = readdir(cwd)) != NULL)
                        {
                            printf("%s\n", dir_struct->d_name);
                        }
                        closedir(cwd);
                    }
                }

                else if(!strcmp(cmd_arg[1],"-l"))
                {
                    char perm[11];
                    struct stat status;
                    stat(uspath, &status);
                    // printf("%d",S_ISDIR(status.st_mode));

                    DIR *cwd;
                    struct dirent *dir_struct;
                    cwd = opendir(".");
                    if (cwd)
                    {
                        while ((dir_struct = readdir(cwd)) != NULL)
                        {
                            homey = getcwd(homey,4096);

                            strcat(homey,"/");
                            strcat(homey,dir_struct->d_name);

                            // printf("%s\n",homey);

                            stat(homey,&status);
                            

                            if(strcmp(dir_struct->d_name,".") && strcmp(dir_struct->d_name,".."))
                            {
                                if(S_ISDIR(status.st_mode)) perm[0] = 'd';
                                else perm[0] = '-';
                                printf("%s ",perm);
                                printf("%s\n", dir_struct->d_name);
                            }
                        }    
                    }
                        closedir(cwd);   
                }
             }
        }
            
    


      
    
    }
    while(strcmp(cmd_arg[0],"quit"));
}