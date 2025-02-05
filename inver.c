#include<stdio.h>
#include"invert.h"
#include<string.h>
#include<stdlib.h>
void print_list(Slist *head)
{
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	printf("Head->");
	    while (head)		//print all elements
	    {
		    printf("%s -> ", head -> file);
		    head = head -> link;
	    }

	    printf("NULL\n");
    }
}
status display(hash *arr,int size,main_t**main_k,sub**sub_k)
{
    for(int i=0;i<size;i++)
    {
	
        main_t *temp=arr[i].hash_link;
	while(temp)
	{
		printf("[%d]\t%s\t%d\t",i,temp->word,temp->file_count);
		sub *temp_sub=temp->sub_link;
		while(temp_sub)
		{
		    printf("%s\t%d\t",temp_sub->file_name,temp_sub->word_count);
		    temp_sub=temp_sub->sub_link;
		}
		temp=temp->main_link;
	       printf("\n");
	}
    }
    printf("\n");

}
status search(hash *arr,int size,main_t**main_k,sub**sub_k)
{
    char search_word[100];
    printf("Enter the word to search in hash_table\n");
    scanf("%s",search_word);
    if(search_word[0]>=65&&search_word[0]<=90)
	search_word[0]=search_word[0]+32;
    int index=search_word[0]-97;
    main_t *temp_main=arr[index].hash_link;
    while(temp_main)
	{
	    if(strcmp(temp_main->word,search_word)==0)
	    {
		printf("[%d]\t%s\t%d\t",index,temp_main->word,temp_main->file_count);
		sub *temp_sub=temp_main->sub_link;
		while(temp_sub)
		{
		    printf("%s\t%d\t",temp_sub->file_name,temp_sub->word_count);
		    temp_sub=temp_sub->sub_link;
		}
	       printf("\n");
	       return success;
	    }
		temp_main=temp_main->main_link;
	}
    printf("word not found\n");
    return failure;
}
status save_to_file(hash *arr,int size,main_t**main_k,sub**sub_k)
{
    char back_up[100];
    printf("Enter the back_file name\n");
    scanf(" %s",back_up);
    if(!strstr(back_up,".txt"))
    {
	printf("Enter valid file_name to continue\n");
	return failure;
    }
    FILE *fptr=fopen(back_up,"w");
    if(fptr==NULL)
	return failure;
    for(int i=0;i<size;i++)
    {
	
        main_t *temp=arr[i].hash_link;
	while(temp)
	{
		fprintf(fptr,"#%d;%s;%d;",i,temp->word,temp->file_count);
		sub *temp_sub=temp->sub_link;
		while(temp_sub)
		{
		    fprintf(fptr,"%s;%d;",temp_sub->file_name,temp_sub->word_count);
		    temp_sub=temp_sub->sub_link;
		}
		fprintf(fptr,"#");
		temp=temp->main_link;
	       fprintf(fptr,"\n");
	}
    }
    fclose(fptr);
   
}
status update_data_base(Slist **sll,main_t **main_k,sub **sub_t,hash *arr,FILE *ptr)
{
    /*char file_name[100];
    printf("Enter the save file name \n");
    scanf("%s",file_name);

    FILE*ptr=fopen(file_name, "r");
    if(ptr==NULL)
    {
        printf("Error:Could not open file %s\n",file_name);
        return failure;
    }*/

    char ch=getc(ptr);
    if (ch!='#')
    {
        printf("Enter a valid save file\n");
        fclose(ptr);
        return failure;
    }

    char str[100];
    while (fscanf(ptr,"%s", str) != EOF)
    {
        char*temp=strtok(str,"#;");
        int index=temp[0]-'0';
        main_t *temp_main=arr[index].hash_link;
        main_t *new_main=malloc(sizeof(main_t));
        if (new_main==NULL)
        {
            printf("Memory allocation failed\n");
            fclose(ptr);
            return failure;
        }
        temp =strtok(NULL,";");
        strcpy(new_main->word,temp);
        temp = strtok(NULL,";");
        int count_file=atoi(temp);
        new_main->file_count=count_file;
        new_main->sub_link=NULL;
        new_main->main_link=NULL;
        int i=0;
        sub *last_sub=NULL;
        while (i<count_file)
        {
            sub *new_sub=malloc(sizeof(sub));
            if (new_sub== NULL)
            {
                printf("Memory allocation failed for sub\n");
                fclose(ptr);
                return failure;
            }

            temp=strtok(NULL,";#");
            strcpy(new_sub->file_name,temp);

            temp=strtok(NULL, ";#");
            new_sub->word_count = atoi(temp);
            new_sub->sub_link = NULL;
            if(last_sub==NULL)
            {
                new_main->sub_link=new_sub;
            } else
            {
                last_sub->sub_link=new_sub;
            }
            last_sub=new_sub;

            i++;
        }

            if (temp_main==NULL)
            {
            arr[index].hash_link=new_main;
            } else
        {
            while (temp_main->main_link!=NULL)
            {
                temp_main=temp_main->main_link;
            }
            temp_main->main_link=new_main;
        }
    }
    remove_files(sll,ptr);
    fclose(ptr);
    return success;
}
status remove_files(Slist**sll,FILE *ptr)
{
    rewind(ptr);
    char str[100];
    while (fscanf(ptr,"%s", str) != EOF)
    {
    //fscanf(ptr,"%s",str);
    char *file_name=strtok(str,";");
    file_name=strtok(NULL,";");
    file_name=strtok(NULL,";");
    int count=atoi(file_name);
    int i=0;
    while(i<count)
    {
	file_name=strtok(NULL,";#");
	//printf("%s",file_name);
	Slist *temp=*sll;
	Slist *prev=NULL;	
       while(temp)
	{
	    if(strcmp(temp->file,file_name)==0)
	    {
		if(prev==NULL)
		{
		    *sll=temp->link;
		}else
		{
		    prev->link=temp->link;
		}
		Slist *delete=temp;
		free(temp);
	    }
	    else
	    {
		prev=temp;
		temp=temp->link;
	    }
	}
	    file_name=strtok(NULL,";#");
	    i++;
    }
    }
    print_list(*sll);
}


status Read_validate(char *argv[],Slist **head)
{
    FILE *fptr=NULL;
    for(int i=1;argv[i]!=0;i++)
    {

      fptr=NULL;
	if(strstr(argv[i],".txt")==NULL)
	{
	    printf("%s:The file does not contain .txt\n",argv[i]);
	   return failure;
	}
	if((fptr=fopen(argv[i],"r"))==NULL)
	{
	    printf("%s:Error:The file you provided is not found\n",argv[i]);
	    continue;
	}
	char ch;
	if((ch=getc(fptr))==EOF)
	{
	    printf("%s:Error:the file is empty\n",argv[i]);
            fclose(fptr);
	    continue;
	}
	int flag=0;
	for(int j=0;j<i;j++)
	{
	    if(strcmp(argv[i],argv[j])==0)
	    {
		printf("%s:Error:DUPLICATE file is found\n",argv[i]);
               fclose(fptr);
		flag=1;
		break;
	    }
	
	}
	if(flag==1)
	    continue;
        printf("%s:Added to list successfully\n",argv[i]);
	Slist *new=malloc(sizeof(Slist));
	if(new==NULL)
	    return failure;
	strcpy(new->file,argv[i]);
	new->link=NULL;
    if(*head==NULL)
    {
	*head=new;
    }
    else
    {
    Slist *temp=*head;
    while(temp->link)
    {
	temp=temp->link;
    }
    temp->link=new;
    fclose(fptr);
    }
    }
    print_list(*head);
}
status create_database(Slist **sll,main_t **main_k,sub **sub_t,hash *arr)
{
    FILE *ptr;
    Slist *temp=*sll;
    if(*sll==NULL)
    {
	printf("..............The Files you provided is already created database.............\n");
	return failure;
    }
    while(temp)
    {
        ptr=fopen(temp->file,"r");
        if(ptr==NULL)
            return failure;
            char ch;
        while(!feof(ptr))
        {
            char str[100];
            int k=0;
            while((ch=getc(ptr))!=' '&&ch!='\n'&&ch!=EOF)
            {
                str[k]=ch;
                k++;
            }
            if(k==0)
                continue;
            str[k]=0;
            //ch=getc(ptr);
            k=0;
            if(str[0]>=65&&str[0]<=90)
                str[0]=str[0]+32;
            else
                str[0]=str[0];
            int index=str[0]-97;
            int flag=0;
            main_t *temp_hash=arr[index].hash_link;
            if(temp_hash==NULL)
            {
                main_t *new=malloc(sizeof(main_t));
                if(new==NULL)
                    return failure;
                new->file_count=1;;
                strcpy(new->word,str);
                new->main_link=NULL;
                new->sub_link=NULL;
                sub *new1=malloc(sizeof(sub));
                if(new1==NULL)
                    return failure;
                strcpy(new1->file_name,temp->file);
                new1->word_count=1;
                new1->sub_link=NULL;
                new->sub_link=new1;
		arr[index].hash_link=new;
            }
            else
            {
                while(temp_hash)
                {
                    if(strcmp(temp_hash->word,str)==0)
                    {
                        sub *new1=malloc(sizeof(sub));
                        if(new1==NULL)
                            return failure;
                        new1->word_count=1;
			strcpy(new1->file_name,temp->file);
                        new1->sub_link=NULL;
                        int flag1=0;
                        sub *next=temp_hash->sub_link;
                        sub *prev=NULL;
                        while(next)
                        {
                            if(strcmp(next->file_name,temp->file)==0)
                            {
                                next->word_count++;
                                flag1=1;
                                break;
                            }
                            prev=next;
                            next=next->sub_link;
                        }
                        if(flag1==0)
                        {
                            if(prev)
                                prev->sub_link=new1;
                            else
                                temp_hash->sub_link=new1;

                            temp_hash->file_count++;
                        }
                        flag=1;
                        break;
                    }
		    if(temp_hash->main_link==NULL)
			break;
                    temp_hash=temp_hash->main_link;
                }
                if(flag==0)
                {
                main_t *new=malloc(sizeof(main_t));
                if(new==NULL)
                    return failure;
                new->file_count=1;;
                strcpy(new->word,str);
                new->main_link=NULL;
                new->sub_link=NULL;
                sub *new1=malloc(sizeof(sub));
                if(new1==NULL)
                    return failure;
                strcpy(new1->file_name,temp->file);
                new1->word_count=1;
                new1->sub_link=NULL;
                new->sub_link=new1;
                temp_hash->main_link=new;
                }
            }
        }
    printf("Succesfully created data_base: %s\n",temp->file);
    fclose(ptr);
    temp=temp->link;
    }
}
