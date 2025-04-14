#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"
typedef struct Task
{
    char description[50];
    int completed;
} Task;

typedef struct ToDoList
{
    char title[50];
    Task tasks[10];
    int totalTasks;
} ToDoList;

ToDoList myList;

void displayList()
{
    printf("-=%s %s %s=-\n", AC_RED, myList.title, AC_NORMAL);
    
    for (int i = 0; i < myList.totalTasks; i++)
    {
        if (myList.tasks[i].completed == 1)
        {
            printf("%s[%sx%s] %s%s%s\n", AC_BLUE, AC_GREEN,AC_BLUE,AC_YELLOW,myList.tasks[i].description,AC_NORMAL);
        }
        else
        {
            printf("%s[%s %s] %s%s%s\n", AC_BLUE, AC_GREEN,AC_BLUE,AC_YELLOW,myList.tasks[i].description,AC_NORMAL);
        }
    }
    
}

int allTasksCompleted()
{
    for (int i = 0; i < myList.totalTasks; i++)
    {
        if (!myList.tasks[i].completed)
            return 0;
    }
    return 1;
}

void completeTask(int taskIndex)
{
    if (taskIndex >= 0 && taskIndex < myList.totalTasks)
    {
        myList.tasks[taskIndex].completed = 1;
        printf("sarcina completata\n");
    }
    else
    {
        printf("index invalid.\n");
    }
}

void read_file()
{
    FILE *file = fopen("tasks.txt", "r");
    if (!file)
    {
        printf("nu sa putut deschide fisierul.\n");
        return;
    }

    fscanf(file, " %[^\n]", myList.title);
    myList.totalTasks = 0;
    while (myList.totalTasks < 10 && fscanf(file, " %[^\n,],%d",myList.tasks[myList.totalTasks].description,&myList.tasks[myList.totalTasks].completed) == 2)
    {
        
        myList.totalTasks++;
    }
    fclose(file);
}
void write_if_completed()
{
    FILE *file;
    if (allTasksCompleted() && myList.totalTasks > 0)
    {
        printf("\ntoate sarcinile au fost finalizate. lista va fi stearsa.\n");
        myList.totalTasks = 0;
        file = fopen("tasks.txt", "w");
        fprintf(file, "%s\n", myList.title);
        fclose(file);
    }
}
void check_choice(int choice)
{
    if (choice == 1 && myList.totalTasks > 0)
    {
        int index;
        printf("numarul sarcinii (1-%d): ", myList.totalTasks);
        scanf("%d", &index);
        completeTask(index - 1);
        printf("Scriu in fisier...\n");
    }
    else if (choice == 2)
    {
        printf("sa iesit din cod");
        exit(1);
    }
    else
    {
        printf("optiune invalida.\n");
    }
}

void write_file(){
    
    FILE* file = fopen("tasks.txt", "w");
    if (!file)
    {
        printf("nu pot scrie in fisier.\n");
        return;
    }
    
    fprintf(file, "%s\n", myList.title);
    
    for (int i = 0; i < myList.totalTasks; i++)
    {
        
        fprintf(file, "%s,%d\n", myList.tasks[i].description, myList.tasks[i].completed);
        
    }
    fclose(file);
    printf("scriere finalizata.\n");
}

int main()
{
    
    int choice;
    FILE *file;
    read_file();
    while (1)
    {
        displayList();
        write_file();
        write_if_completed();
        printf("\n1. completeaza o sarcina\n2. exit\nalege: ");
        scanf("%d", &choice);
        check_choice(choice);
    }
    return 0;
}