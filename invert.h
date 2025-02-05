typedef struct node
{
    char file[100];
    struct node *link;
}Slist;

typedef enum
{
    success,
    failure
}status;
typedef struct main_node
{
    int file_count;
    char word[100];
    struct main_node *main_link;
    struct sub_node *sub_link;
}main_t;

typedef struct sub_node
{
    int word_count;
    char file_name[100];
    struct sub_node *sub_link;
}sub;

typedef struct hash_table
{
    int key;
    struct main_node *hash_link;
}hash;
    
status operation(char *argv[]);

status Read_validate(char *argv[],Slist **);
status create_database(Slist **,main_t **,sub **,hash *);
status display(hash *,int ,main_t**,sub**);
status search(hash *,int ,main_t**,sub**);
status save_to_file(hash *,int ,main_t**,sub**);
status update_data_base(Slist **sll,main_t **main_k,sub **sub_t,hash *arr,FILE *);
status remove_files(Slist**,FILE *);
