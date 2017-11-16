#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 51
typedef struct e
{
    char *name;
    char id[18];
    char date[10];
    int salary;
    struct e *next;
    struct e *prev;
} Employee;

FILE *openFile(char *, char *);
Employee *load(FILE *);
Employee *createInsert(char[MAX],char[17],char[10],int);
void display(Employee *);
void find(Employee *,char *,char *);
int main(int argc, char *argv[])
{
    FILE *fp;
    Employee *head;
    if(argc!=4)
    {
        printf("error in passing command line parameters!\n");
        exit(0);
    }
    fp=openFile(argv[1],"r");
    head=load(fp);
    /*display(head);*/
    find(head,argv[2],argv[3]);

    return 0;
}
FILE *openFile(char *fn, char *mode)
{
    FILE *fp;
    fp=fopen(fn,mode);
    if(fp==NULL)
    {
        printf("error in opening file!\n");
        exit(0);
    }
    return fp;
}
Employee *load(FILE *fp)
{
    Employee *head,*newE;
    char name[MAX], id[17],date[10];
    int salary;
    head=NULL;
    while(fscanf(fp,"%s %s %s %d",name,id,date,&salary)!=EOF)
    {
        newE=createInsert(name,id,date,salary);
        if(head==NULL)
        {
            newE->next=NULL;
            newE->prev=NULL;
            head=newE;
        }
        else
        {
            newE->next=head;
            head->prev=newE;
            newE->prev=NULL;
            head=newE;
        }
    }
    return head;
}

Employee *createInsert(char name[MAX],char id[18],char date[10],int salary)
{
    Employee *newE;
    newE=(Employee *)malloc(sizeof(Employee));
    if(newE==NULL)
    {
        printf("Not enough space for new element allocation!\n");
        exit(0);
    }
    newE->name=(char *)malloc((strlen(name)+1)*sizeof(char));
    if(newE==NULL)
    {
        printf("Not enough space for new element's name allocation!\n");
        exit(0);
    }
    strcpy(newE->name,name);
    strcpy(newE->id,id);
    strcpy(newE->date,date);
    newE->salary=salary;
    newE->next=NULL;
    newE->prev=NULL;
    return newE;
}
void display(Employee *head)
{
    while(head!=NULL)
    {
        printf("%s %s %s %d \n",head->name,head->id,head->date,head->salary);
        head=head->next;
    }
    return;
}

void find(Employee *head,char *wanted,char *movement)
{
    int i;
    while(head!=NULL)
    {
        if(strcmp(wanted,head->name)==0)
        {
            printf("%s %s %d \n",head->name,head->date,head->salary);
            break;
        }
        else
        {
            head=head->next;
        }
    }
    for(i=0; i<strlen(movement); i++)
    {
        if(movement[i]=='+')
        {
            if(head->next!=NULL){
                head=head->next;
                printf("%s %s %s %d \n",head->name,head->id,head->date,head->salary);
            }else{
                printf("%s %s %s %d \n",head->name,head->id,head->date,head->salary);
            }
        }
        else if(movement[i]=='-')
        {
            if(head->prev!=NULL){
                head=head->prev;
                printf("%s %s %s %d \n",head->name,head->id,head->date,head->salary);
            }else{
                printf("%s %s %s %d \n",head->name,head->id,head->date,head->salary);
            }
        }
    }
    return;
}
