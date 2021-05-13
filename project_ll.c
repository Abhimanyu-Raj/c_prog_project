#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// creating structure for node
struct pass
{
    int ticket;
    char name[20];
    int age;
    char date[20];
    char timer[20];
    char pickup[20];
    char dest[20];
    struct pass *prev;
    struct pass *next;
};
typedef struct pass node;
node *first=NULL, *last=NULL;
int num=1;
/*---------function to create node dynamically and receive user input for data-------*/
void pass_detail()
{
    int a,c;
    char b[20],d[20],e[20],f[20],g[20];
    printf("enter passenger %d details: ticket number, name, age, date, time, pickup_location, Destination\n(enter detail in sequence with one space apart)\n", num);
    scanf("%d %s %d %s %s %s %s", &a,b,&c,d,e,f,g);
    node *new=(node *)malloc(sizeof(node));
    if (first==NULL)
    {
        new->ticket=a;
        strcpy(new->name, b);
        new->age=c;
        strcpy(new->date, d);
        strcpy(new->timer, e);
        strcpy(new->pickup, f);
        strcpy(new->dest, g);
        new->prev=NULL;
        new->next=NULL;
        first=last=new;
    }
    else
    {
        new->ticket=a;
        strcpy(new->name, b);
        new->age=c;
        strcpy(new->date, d);
        strcpy(new->timer, e);
        strcpy(new->pickup, f);
        strcpy(new->dest, g);
        new->prev=last;
        new->next=NULL;
        last->next=new;
        last=new;
    }
    num++;
}
/*------bubble sort function to sort ticket numbers (called in Display function)-----*/
void bubble_sort(int arr1[], int MAX_SIZE) {
    int i, j, a, t;

    for (i = 1; i < MAX_SIZE; i++) 
    {
        for (j = 0; j < MAX_SIZE - 1; j++) 
        {
            if (arr1[j] > arr1[j + 1]) 
            {
                t = arr1[j];
                arr1[j] = arr1[j + 1];
                arr1[j + 1] = t;
            }
        }
    }
}
/*------function to display data of all present nodes(called in display function)------*/
void print_node(int arr[],int i,FILE *fp1, int mode)
{
    int j=0;
    fprintf(fp1, "======passenger details as sorted by ticket no====\n");
    for(j=0;j<i;j++)
    {
        node *temp=first;
        while(temp->ticket!=arr[j])
        {
            temp=temp->next;
        }
        if(mode==0)
            fprintf(fp1, "passenger ticket no=%d name=%s age=%d date=%s time=%s pickup location=%s Destination=%s\n", temp->ticket, temp->name, temp->age, temp->date, temp->timer, temp->pickup, temp->dest);
        else
        {
            fwrite(&(temp->ticket), sizeof(temp->ticket),1,fp1);
            fwrite(&(temp->name), sizeof(temp->name),1,fp1);
            fwrite(&(temp->age), sizeof(temp->age),1,fp1);
            fwrite(&(temp->date), sizeof(temp->date),1,fp1);
            fwrite(&(temp->timer), sizeof(temp->timer),1,fp1);
            fwrite(&(temp->pickup), sizeof(temp->pickup),1,fp1);
            fwrite(&(temp->dest), sizeof(temp->dest),1,fp1);
        }
    }        
}
/*-----function to Display all node data in sorted form by ticket number------*/
void display_all_sorted(FILE *fp1, int mode)
{
    node *temp=first;
    if((first==NULL) && (last==NULL))
    {
        printf("no data to show\n");
    }
    else
    {
        int i=0,j=0;
        while(temp!=NULL)
        {
            i++;
            temp=temp->next;
        }
        temp=first;
        int arr[i];
        for(j=0;j<i;j++)
        {
            arr[j]=temp->ticket;
            temp=temp->next;
        }
        bubble_sort(arr,i);
        print_node(arr,i,fp1,mode);
    }
}
/*-----function to Display node by ticket number provided by user--*/
void display_tick()
{
    int key;
    printf("enter the ticket number\n");
    scanf("%d", &key);
    node *temp=first;
    while(temp->ticket!=key)
    {
        temp=temp->next;
    }
    printf("===========selected passenger details are:===========\n");
    fprintf(stdout,"passenger ticket no=%d name=%s age=%d date=%s time=%s pickup location=%s Destination=%s\n", temp->ticket, temp->name, temp->age, temp->date, temp->timer, temp->pickup, temp->dest);
    
}
/*-----function to Delete a node by ticket number provided by user--*/
void delete_tick()
{
    int key;
    printf("enter the ticket no. of passenger to be deleted\n");
    scanf("%d",&key);
    node *temp=first;
    while(temp->ticket!=key)
    {
        temp=temp->next;
    }
    if (temp->prev==NULL)
    {
        first=temp->next;
        first->prev=NULL;
        free(temp);
        printf("Message: passemger detail with ticket no %d is deleted\n", key);
    }
    else if(temp->next==NULL)
    {
        last=temp->prev;
        last->next=NULL;
        free(temp);
        printf("Message: passemger detail with ticket no %d is deleted\n", key);
    }
    else if((temp->prev!=NULL) && (temp->next!=NULL))
    {
        temp->prev->next=temp->next;
        temp->next->prev=temp->prev;
        free(temp);
        printf("Message: passemger detail with ticket no %d is deleted\n", key);
    }
    else
    {
        printf("ticket entered is not found\n");
    }
}
/*----function to copy node data to text file in text form---*/
void write_text()
{
    FILE *fp= fopen("refer.txt", "w+");
    if (fp==NULL)
    {
        printf("file not found\n");
        exit(9);
    }
    display_all_sorted(fp,0);
    printf("passenger details are transfered to file 'refer.txt'. it can be seen after program exit.\npress 0 to exit or other options to continue\n");
}
/*----function to copy node data to text file in binary form---*/
void write_bin()
{
    FILE *fp2=fopen("refer2.txt", "w+");
    if(fp2==NULL)
    {
        printf("file not found\n");
        exit(9);
    }
    display_all_sorted(fp2,1);
    printf("passenger details are transfered to file 'refer2.txt'. it can be seen after program exit.\npress 0 to exit or other options to continue\n");
}
/*------function to delete all nodes deleting all passenger's details----*/
void delete_all()
{
    node *temp=NULL, *temp1=NULL;
    while(first!=NULL)
    {
        temp=first;
        first=temp->next;
        free(temp);
        last=NULL;
    }
    printf("Message: all passenger details have been deleted\n");
}
/*----main function using Switch to display menu options and calling functions based on selection----*/
int main()
{
    int i=1;
    int choice;
    while(i!=0)
    {
        printf("\nSelect choice from below menu:\n");
        printf("1. Enter passenger detail\t2. Display by ticket no.\t3. Display all\n4. Delete by ticket no.\t5. Delete all\t6.Save details in text file\t7. Save details as binary text\n0. Press 0 to exit\n");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            {   
                pass_detail();
                break;
            }
            case 2:
            {   
                display_tick();
                break;
            }
            case 3:
            {   
                display_all_sorted(stdout,0);
                break;
            }
            case 4:
            {   
                delete_tick();
                break;
            }
            case 5:
            {   
                delete_all();
                break;
            }
            case 6:
            {   
                write_text();
                break;
            }
            case 7:
            {   
                write_bin();
                break;
            }
            case 0:
            {
                i=0;
                break;
            }
            default:
            {
                printf("error: entered choice is not from menu\n");
                break;
            }
        }
    }
    return 0;
}


