#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include<string.h>
#include <pwd.h>
#include<time.h>

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
    // printf("%s",home);

    char *str1 = (char*)malloc(100 * sizeof(char*));    
    char **cmd_arg = (char**)malloc(50*sizeof(char**));
    char **command_list = (char**)malloc(330*sizeof(char**));
    do
    {
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
                //showing wrong stuff for other dir
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

                else if(!strcmp(cmd_arg[1],"-l") || !strcmp(cmd_arg[1],"-la") || !strcmp(cmd_arg[1],"-al") )
                {
                    char perm[11];
                    struct stat status;
                    stat(uspath, &status);

                    DIR *cwd;
                    struct dirent *dir_struct;
                    if(cmd_arg[2] == NULL)
                        cwd = opendir(".");
                    else
                        cwd = opendir(cmd_arg[2]);
                    if (cwd)
                    {
                        while ((dir_struct = readdir(cwd)) != NULL)
                        {

                            
                            homey = getcwd(homey,4096);
                            
                        
                    

                            strcat(homey,"/");
                            strcat(homey,dir_struct->d_name);
                            // printf("%s\n",homey);


                            stat(homey,&status);
                            
                            if(!strcmp(cmd_arg[1],"-l"))
                            {   
                                if(strcmp(dir_struct->d_name,".") && strcmp(dir_struct->d_name,".."))
                                {
                                    if(S_ISDIR(status.st_mode)) perm[0] = 'd';
                                    else perm[0] = '-';
                                    
                                    if(status.st_mode & S_IRUSR) perm[1] = 'r';
                                    else perm[1] = '-';
                                    
                                    if(status.st_mode & S_IWUSR) perm[2] = 'w';
                                    else perm[2] = '-';
                                    
                                    if(status.st_mode & S_IXUSR) perm[3] = 'x';
                                    else perm[3] = '-';
                                    
                                    if(status.st_mode & S_IRGRP) perm[4] = 'r';
                                    else perm[4] = '-';

                                    if(status.st_mode & S_IWGRP) perm[5] = 'w';
                                    else perm[5] = '-';

                                    if(status.st_mode & S_IXGRP) perm[6] = 'x';
                                    else perm[6] = '-';

                                    if(status.st_mode & S_IROTH) perm[7] = 'r';
                                    else perm[7] = '-';

                                    if(status.st_mode & S_IWOTH) perm[8] = 'w';
                                    else perm[8] = '-';

                                    if(status.st_mode & S_IXOTH) perm[9] = 'x';
                                    else perm[9] = '-';

                                    struct passwd *pws;
                                    struct passwd *pwr;
                                    pws = getpwuid(status.st_uid);
                                    pwr = getpwuid(status.st_gid);
                                    char *userid = pws->pw_name;
                                    char *groupid = pwr->pw_name;
                                    
                                    char result[100];
                                    time_t t;
                                    t = status.st_ctime;
                                    strftime(result, sizeof(result), "%b %d %I:%M",localtime(&t));
                                    printf("%s %ld %s %s %ld %s %s\n",perm,status.st_nlink,userid,groupid,status.st_size,result,dir_struct->d_name);
                                }
                            }
                            else
                            {
                                if(S_ISDIR(status.st_mode)) perm[0] = 'd';
                                else perm[0] = '-';
                                
                                if(status.st_mode & S_IRUSR) perm[1] = 'r';
                                else perm[1] = '-';
                                
                                if(status.st_mode & S_IWUSR) perm[2] = 'w';
                                else perm[2] = '-';
                                
                                if(status.st_mode & S_IXUSR) perm[3] = 'x';
                                else perm[3] = '-';
                                
                                if(status.st_mode & S_IRGRP) perm[4] = 'r';
                                else perm[4] = '-';

                                if(status.st_mode & S_IWGRP) perm[5] = 'w';
                                else perm[5] = '-';

                                if(status.st_mode & S_IXGRP) perm[6] = 'x';
                                else perm[6] = '-';

                                if(status.st_mode & S_IROTH) perm[7] = 'r';
                                else perm[7] = '-';

                                if(status.st_mode & S_IWOTH) perm[8] = 'w';
                                else perm[8] = '-';

                                if(status.st_mode & S_IXOTH) perm[9] = 'x';
                                else perm[9] = '-';

                                struct passwd *pws;
                                struct passwd *pwr;
                                pws = getpwuid(status.st_uid);
                                pwr = getpwuid(status.st_gid);
                                char *userid = pws->pw_name;
                                char *groupid = pwr->pw_name;
                                
                                char result[100];
                                time_t t;
                                t = status.st_ctime;
                                strftime(result, sizeof(result), "%b %d %I:%M",localtime(&t));
                                printf("%s %ld %s %s %ld %s %s\n",perm,status.st_nlink,userid,groupid,status.st_size,result,dir_struct->d_name);
                            }                            
                            
                        }    
                    }
                    closedir(cwd);   
                }
                else
                {
                    DIR *cwd;
                    struct dirent *dir_struct;
                    cwd = opendir(cmd_arg[1]);
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
                
             }
        }
        
    }
    while(strcmp(cmd_arg[0],"quit"));
}