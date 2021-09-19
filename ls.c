#include "headers.h"

void printDetails(char *path, char *dName)
{
    struct stat details;
    if (stat(path, &details) == -1)
        return;

    printf((S_ISDIR(details.st_mode)) ? "d" : "-");
    printf((details.st_mode & S_IRUSR) ? "r" : "-");
    printf((details.st_mode & S_IWUSR) ? "w" : "-");
    printf((details.st_mode & S_IXUSR) ? "x" : "-");
    printf((details.st_mode & S_IRGRP) ? "r" : "-");
    printf((details.st_mode & S_IWGRP) ? "w" : "-");
    printf((details.st_mode & S_IXGRP) ? "x" : "-");
    printf((details.st_mode & S_IROTH) ? "r" : "-");
    printf((details.st_mode & S_IWOTH) ? "w" : "-");
    printf((details.st_mode & S_IXOTH) ? "x" : "-");

    printf("%2ld", details.st_nlink);

    struct passwd *pw = getpwuid(details.st_uid);
    printf("%7s", pw->pw_name);

    struct group *gr = getgrgid(details.st_gid);
    printf("%7s", gr->gr_name);

    printf("%12ld", details.st_size);

    struct tm lastModified, currentTime;
    time_t now = time(0);

    char date[20];
    localtime_r(&details.st_mtime, &lastModified);
    localtime_r(&now, &currentTime);

    if ((lastModified.tm_year == currentTime.tm_year) && (lastModified.tm_mon >= (currentTime.tm_mon - 6)))
        strftime(date, 20, "%b %d %H:%M", localtime(&(details.st_ctime)));
    else
        strftime(date, 20, "%b %d  %Y", localtime(&(details.st_ctime)));

    printf("%13s", date);
    printf("  %-35s\n", dName);
}

void getFiles(int count, char *directory, int lFlag, int aFlag)
{
    DIR *mydir;
    struct dirent *myfile;

    struct stat stats;
    lstat(directory, &stats);

    int file = 1;
    if ((mydir = opendir(directory)) == NULL)
    {
        if(access(directory, F_OK))
        {
            printf("%s: Cannot be accessed\n", directory);
            return;
        }

        else
            file = 0;
    }

    if(file)
    {
        int block = 0;
        char dName[1000];

        while ((myfile = readdir(mydir)))
        {
            if (myfile->d_name[0] == '.' && !aFlag)
                continue;

            sprintf(dName, "%s/%s", directory, myfile->d_name);
            lstat(dName, &stats);
            
            block += stats.st_blocks;
        }

        if (lFlag)
            printf("total %u\n", block / 2);

        mydir = opendir(directory);

        while ((myfile = readdir(mydir)) != NULL)
        {
            char path[1000];
            sprintf(path, "%s/%s", directory, myfile->d_name);

            if (!aFlag && (myfile->d_name)[0] == '.')
                continue;

            if (lFlag)
                printDetails(path, myfile->d_name);

            else
                printf("%s ", myfile->d_name);
        }

        if (!lFlag)
            printf("\n");

        closedir(mydir);
    }

    else if(lFlag)
        printDetails(directory, directory);

    else
        printf("%s\n", directory);
    
}

void ls(int len, char **argv)
{
    int aFlag = 0, lFlag = 0, count = 0;
    char *directories[len];

    for (int i = 1; i < len; i++)
    {
        int length = strlen(argv[i]);

        if(length && argv[i][0] == '-')
        {
            for(int j = 0; j < length; j++)
            {
                if(argv[i][j]=='l')
                    lFlag = 1;
                if(argv[i][j]=='a')
                    aFlag = 1;
            }
        }
        
        else 
        {
            if(strcmp(argv[i], "~") == 0)
                directories[count] = home;

            else if (strcmp(argv[i], ""))
                directories[count] = argv[i];
                
            count++;
        }
    }

    if (count == 0)
        directories[0] = ".";

    for(int i = 0; i < count + 1; i++)
    {
        if (i == count && i != 0)
            break;

        if (count > 1)
            printf("%s:\n", directories[i]);

        getFiles(count, directories[i], lFlag, aFlag);

        if (count > 1)
            printf("\n");
    }
}