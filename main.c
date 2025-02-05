#include<stdio.h>
#include"invert.h"
void create_hash(hash *arr,int size)
{
    for(int i=0;i<size;i++)
    {
	arr[i].key=i;
	arr[i].hash_link=NULL;
    }
}

int main(int argc,char *argv[])
{
    Slist *head = NULL;
    hash arr[28];
    main_t *head_main=NULL;
    sub *head_sub=NULL;
    
    if(operation(argv)==failure)
    {
	printf("Enter valid no of arguments");
	return failure;
    }
    if(Read_validate(argv,&head)==failure)
    {
	printf("Error in READ AND VALIDATION ");
	return failure;
    }
    create_hash(arr,28);
    printf("............Enter file name to update the data_base...............\n");
    char file_name[50];
    scanf("%s",file_name);
    FILE * fptr = fopen(file_name,"r");
    if(!fptr)
    {
	printf("The file is Empty create database first\n");
    }
    else
    {
    update_data_base(&head,&head_main,&head_sub,arr,fptr);
    printf("...........Updated database successfully...............\n");
    }
    char ch;
    do
    {
    printf(".....Enter the option to ceate database[Y/y] to continue.......\n");
    scanf(" %c",&ch);
    if (ch=='Y'||ch=='y')
    create_database(&head,&head_main,&head_sub,arr);
    else
	printf("Enter valid option to create data base");
    } while(ch!='Y'&&ch!='y');
    int choice;
    do{
    printf("1.Display data\n2.Search data\n3.Save to the file\n4.Exit\n");
    scanf("%d",&choice);
    switch(choice)
    {
	case 1:
	    display(arr,28,&head_main,&head_sub);
	    break;
	case 2:
	    search(arr,28,&head_main,&head_sub);
	    break;
	case 3:
	    save_to_file(arr,28,&head_main,&head_sub);
	    break;
       case 4:
           printf("EXIT FROM THE DATA BASE");
           break;	   
    }
    }
    while(choice!=4);
}
status operation(char *argv[])
{
    if(argv[1]==NULL)
    {
	return failure;
    }
}
