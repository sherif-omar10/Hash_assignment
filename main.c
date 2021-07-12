#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10


struct student Newstudent(struct student x); //create new student
unsigned long hashfunction(char* name);  // get the index
void insertstudent(); //insert new student to the table
void search(char* Name); //search by name
void del(char* Name); //delete by name
void print();
void init();

struct student
{
    int id;
    char* name[100];
    int day , month , year;
    int score;
};
struct node
{
    struct student data;
    struct node *next;
};


//int main()
//{   init();
//    int option;
//    char* Name[100];
//    do{
//        printf("------------------------------------------\n");
//        printf("Type 1 to insert student.\n");
//        printf("Type 2 to search for a student.\n");
//        printf("Type 3 to remove student.\n");
//        printf("Type 4 to list the hash table.\n");
//        printf("Option: ");
//        scanf("%d", &option);
//        switch(option)
//        {
//            case 1:
//                insertstudent();
//                break;
//            case 2:
//                printf("enter name of student to search: ");
//                scanf("%s",&Name );
//                search(Name);
//                break;
//            case 3:
//                printf("enter name of student to remove: ");
//                scanf("%s",&Name );
//                del(Name);
//                break;
//            case 4:
//                print();
//                break;
//        }
//    }
//    while(option>0);
//
//}


struct student Newstudent(struct student x)
{

    printf("\n\tName:");
    fflush(stdin);
    scanf("%s",x.name);
    //fgets((x.name),sizeof(x.name),stdin);
    fflush(stdin);
    printf("\tID: ");
    scanf("%d", &(x.id));
    printf("\tYear Of Birth: ");
    scanf("%d", &(x.year));
    printf("\tMonth Of Birth: ");
    scanf("%d", &(x.month));
    printf("\tDay Of Birth: ");
    scanf("%d", &(x.day));
    printf("\tScore Of Last Year: ");
    scanf("%d", &(x.score));

    //for(int i=0;i<strlen(x.name);i++)
    //printf("the name is %c\n",x.name[i]);
    //printf("length %d\n",strlen(x.name));
    //printf("the name is %s\n",x.name);
    return x;
}

unsigned long hashfunction (char* name)  // the used function to get the index
{
    unsigned long i = 0;
    int j=0;
    for (j=0; name[j]; j++)
    {  if(name[j]!='\n')
            i += name[j];
    }
    //printf("sum=%d\n",i);
    return i % N;
}

struct node* hash_table[N];

void init()
{
    int i;
    for(i = 0; i < N; i++)
        hash_table[i] = NULL;
}

void insertstudent()
{
    struct student y;
    struct node *newNode = (struct node* )malloc(sizeof(struct node));
    newNode->data = Newstudent(y);
    newNode->next = NULL;

    //calculate the index
    unsigned long index = hashfunction(newNode->data.name);
    printf("\n\tIndex=%d\n",index);

    //check if table[index] is empty
    if(hash_table[index] == NULL)
        hash_table[index] = newNode;
        //collision
    else
    {
        //add the node at the end of table[index].
        struct node *temp = hash_table[index];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

void search(char* Name)
{
    int flag;
    unsigned long index = hashfunction(Name);
    struct node *temp = hash_table[index];
    //for(int i=0;i<strlen(Name);i++)
    //printf("the name is %c\n",Name[i]);
    //printf("length %d\n",strlen(Name));
    while(temp)
    {
        if( (strcmp(temp->data.name , Name) == 0) )
        {
            printf("\n\tThis name is found\n");
            flag=1;
        }
        temp = temp->next;
    }
    if(!flag)
        printf("This name is not found\n");
}



void del(char* Name)
{
    int flag;
    unsigned long index = hashfunction(Name);
    struct node *temp = hash_table[index];
    struct node *current;
    if(temp != NULL)
    {
        if( strcmp(temp->data.name, Name) == 0)
        {
            current = temp;
            temp = temp->next;
            free(current);
            printf("\n\tDeleted Succesfully\n");
            flag=1;
        }
        else
        {
            while(temp->next)
            {
                if( strcmp(temp->next->data.name, Name) == 0)
                {
                    current = temp->next;
                    temp->next = temp->next->next;
                    free(current);
                    printf("Deleted Succesfully\n");
                    flag=1;
                }
                temp = temp->next;
            }
        }
    }
    if(!flag)
        printf("Couldn't Delete\n");

}

void print()
{
    int i;

    for(i = 0; i < N; i++)
    {
        struct node *temp = hash_table[i];
        printf("\thash[%d]-->",i);
        while(temp)
        {
            printf("%s -->",temp->data.name);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

//________________________________________________________________________

int BD_hashfunction(int day,int month,int year)
{
    return (day+month+year)%N;
}


int BD_linear_insert(int indx)
{
    int cur_indx=indx;

    if(hash_table[cur_indx]==NULL)
        return cur_indx;
    else
        cur_indx=(cur_indx+1)%N;

    while(cur_indx!=indx && hash_table[cur_indx]!=NULL)
        cur_indx=(cur_indx+1)%N;

    if(cur_indx==indx)
        return -1;

    return cur_indx;
}

int BD_quadratic_insert(int indx)
{
    int cur_indx=indx;
    int step=1;

    if(hash_table[indx]==NULL)
        return cur_indx;
    else
    {
        cur_indx = (cur_indx + step*step) % N;
        step++;
    }

    while(cur_indx!=indx && hash_table[cur_indx]!=NULL)
    {
        cur_indx = (cur_indx + step*step) % N;
        step++;
    }

    if(cur_indx==indx)
        return -1;

    return cur_indx;
}

// typ = 1 for linear
// typ = 2 for quadratic
int BD_common_insert(int typ)
{
    struct student y;
    struct node *newNode = (struct node* )malloc(sizeof(struct node));
    newNode->data = Newstudent(y);
    newNode->next = NULL;

    //calculate the index
    unsigned long index = BD_hashfunction(newNode->data.day,newNode->data.month,newNode->data.year);

    if(typ==1)
        index=BD_linear_insert(index);
    else
        index=BD_quadratic_insert(index);

    if(index==-1)
    {
        printf("Hashtable Full\n");
        return -1;
    }
    else{
        printf("\n\tIndex=%d\n", index);
        hash_table[index]=newNode;
    }

    return index;
}


int isfound(int indx,int day,int month ,int year)
{
    return hash_table[indx]->data.day==day &&
            hash_table[indx]->data.month==month &&
                    hash_table[indx]->data.year==year;
}

int BD_linear_search(int indx,int day,int month ,int year)
{
    int cur_indx=indx;

    if(hash_table[cur_indx]==NULL)
        return -1;

    if(isfound(cur_indx,day,month,year))
        return cur_indx;
    else
        cur_indx=(cur_indx+1)%N;

    while(cur_indx!=indx && hash_table[cur_indx]!=NULL && !isfound(cur_indx,day,month,year))
        cur_indx=(cur_indx+1)%N;

    if(hash_table[cur_indx]!=NULL && isfound(cur_indx,day,month,year))
        return cur_indx;
    else
        return -1;
}

int BD_quadratic_search(int indx,int day,int month,int year)
{
    int cur_indx=indx;
    int step=1;

    if(hash_table[cur_indx]==NULL)
        return -1;

    if(isfound(cur_indx,day,month,year))
        return cur_indx;
    else
    {
        cur_indx = (cur_indx + step*step) % N;
        step++;
    }


    while(cur_indx!=indx && hash_table[cur_indx]!=NULL && !isfound(cur_indx,day,month,year))
    {
        cur_indx = (cur_indx + step*step) % N;
        step++;
    }

    if(hash_table[cur_indx]!=NULL && isfound(cur_indx,day,month,year))
        return cur_indx;
    else
        return -1;
}

// typ = 1 for linear
// typ = 2 for quadratic
int BD_common_search(int typ,int day,int month,int year)
{
    //calculate the index
    int index = BD_hashfunction(day,month,year);

    if(typ==1)
        index=BD_linear_search(index,day,month,year);
    else
        index=BD_quadratic_search(index,day,month,year);

    if(index==-1)
    {
        printf("Not foundl\n");
        return -1;
    }
    else{
        printf("\n\tFound at Index=%d\n", index);
    }

    return index;
}
int BD_del(int indx,int day,int month,int year)
{
    int flag;
    int cur_indx=indx;
    unsigned long index = BD_hashfunction(day,month,year);
    struct node *temp = hash_table[index];
    struct node *current;
    if(temp != NULL)
    {
        if(isfound(cur_indx,day,month,year))
        {
            current = temp;
            temp = temp->next;
            free(current);
            printf("\n\tDeleted Succesfully\n");
            flag=1;
        }
        else
        {
            while(temp->next)
            {
                if(isfound(cur_indx,day,month,year))
                {
                    current = temp->next;
                    temp->next = temp->next->next;
                    free(current);
                    printf("Deleted Succesfully\n");
                    flag=1;
                }
                temp = temp->next;
            }
        }
    }
    if(!flag)
        printf("Couldn't Delete\n");

}
void BD_common_del(int typ,int day,int month,int year)
{
    //calculate the index

    int index = BD_hashfunction(day,month,year);
    if(typ==1)
        index=BD_del(index,day,month,year);
    else
        index=BD_del(index,day,month,year);


}
void intro()
{
	printf("\n\tCairo University");
	printf("\n\tFaculty of Engineering");
	printf("\n\tElectronics and Communications Engineering Department 2nd Year \n\n\n");
	printf("\t\t\t\t\t\t   \"ASSIGNMENT #2\"\n\n" );
    printf( "\t\t\t\t\t************************************\n");
	printf( "\t\t\t\t\tCoded By :\n\n" );
	printf( "\t\t\t\t\tSHERIF OMAR BKHEIT\tSEC:2\tBN:31\n\n" );
	printf("\t\t\t\t\tYASMIN YOSRI SADEK\tSEC:4\tBN:46\n\n" );
	printf( "\t\t\t\t\tYOMNA AHMED MOHAMED\tSEC:4\tBN:48\n\n" );
	printf( "\t\t\t\t\t************************************");
	printf("\n\n\n\tPress Enter To Continue\n\n");
	getc(stdin);
}
int main()
{
int option;
   char* Name[100];
   int day,month,year;
    intro();
    init();

char c;
	do
	{
		printf( "\n\n\n\tMAIN MENU");
		printf( "\n\n\t1.  MAPPING USING STUDENT NAME");
		printf( "\n\n\t2.  MAPPING USING STUDENT BIRTHDAY (LINEAR PROPING)");
		printf( "\n\n\t3.  MAPPING USING STUDENT BIRTHDAY (QUADRATIC PROPING)");
		printf( "\n\n\t4.  EXIT");
		printf( "\n\n\tPlease Select Your Option (1-4)\t ");
		c = _getche();
		switch (c)
		{
case '1'://NAME
{ do{
        printf( "\n\n\n\t  MAPPING USING STUDENT NAME MENU\n");
        printf("\n\t(1)  INSERT A STUDENT");
        printf("\n\t(2)  SEARCH FOR A STUDENT");
        printf("\n\t(3)  REMOVE A STUDENT");
        printf("\n\t(4)  LIST THE HASH TABLE\n");
        printf("\n\n\tOption: ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                insertstudent();
                break;
            case 2:
                printf("\n\tEnter Name Of Student To Search : ");
                scanf("%s",&Name );
                search(Name);
                break;
            case 3:
                printf("\n\tEnter Name Of Student To Remove : ");
                scanf("%s",&Name );
                del(Name);
                break;
            case 4:
                print();
                break;
        }
    }while(option>0);
    break;}
case '2'://BIRTHDAY LINEAR
{ do{
        printf( "\n\n\n\t  MAPPING USING STUDENT BIRTHDAY (LINEAR PROPING) MENU\n");
        printf("\n\t(1)  INSERT A STUDENT");
        printf("\n\t(2)  SEARCH FOR A STUDENT");
        printf("\n\t(3)  REMOVE A STUDENT");
        printf("\n\t(4)  LIST THE HASH TABLE\n");
        printf("\n\n\tOption: ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                BD_common_insert(1);
                break;
            case 2:
                printf("\n\tEnter Birthday Of Student To Search : ");
                scanf("%d %d %d",&year,&month,&day);
    BD_common_search(1,day,month,year);
                break;
            case 3:
                printf("\n\tEnter Birthday Of Student To Remove : ");
                scanf("%d %d %d",&year,&month,&day);
                BD_common_del(1,day,month,year);
                break;
            case 4:
                print();
                break;
        }
    }while(option>0);
    break;}

case '3'://BIRTHDAY QUADRATIC
{ do{
        printf( "\n\n\n\t  MAPPING USING STUDENT BIRTHDAY (QUADRATIC PROPING) MENU\n");
        printf("\n\t(1)  INSERT A STUDENT");
        printf("\n\t(2)  SEARCH FOR A STUDENT");
        printf("\n\t(3)  REMOVE A STUDENT");
        printf("\n\t(4)  LIST THE HASH TABLE\n");

        printf("\n\n\tOption: ");
        scanf("%d", &option);
        switch(option)
        {
            case 1:
                BD_common_insert(2);
                break;
            case 2:
                printf("\n\tEnter Birthday Of Student To Search : ");
                scanf("%d %d %d",&year,&month,&day);
    BD_common_search(2,day,month,year);
                break;
            case 3:
                printf("\n\tEnter Birthday Of Student To Remove : ");
                scanf("%d %d %d",&year,&month,&day);
                BD_common_del(2,day,month,year);
                break;
            case 4:
                print();
                break;
        }
    }while(option>0);
    break;}


case '4':
			break;
		default:printf("\a");
		}
	} while (c != '4');


return 0;
}

