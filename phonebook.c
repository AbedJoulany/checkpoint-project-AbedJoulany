#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

struct contact{
    char fname[31];
    char lname[31];
    char telep[15];
    char cellp[15];
    struct contact *next_fname;
};

#define TOTAL_CONTACTS 10

struct contact* A = NULL;

void clrscr(void);
void gotoxy(int x, int y);
/* insert new contact */
void insert(void);
/* delete contact */
void delet(void);
/* edit contact */
void edit(void);
/* show search options*/
void search(void);
/* search by first name */
void searchf(void);
/* search by last name */
void searchl(void);
/* search by telephone */
void searchp(void);
/* search by cell phone */
void searchc(void);
/* show all */
void list(void);
/* print the list after sort */
void list2(void);
/* funtion to show sort options */
void sort(void);
/* sort by first name */
void sortf(void);
/* sort by last name */
void sortl(void);
/* sort by telephone */
void sortp(void);
/* sort by cellphone */
void sortc(void);
/* print help*/
void help(void);
/* checking if the contact already exists */
bool check_contact_exist(struct contact** person);
/* function to read input from user*/
void read_input(char* dest, int max);
/* funtion to add new node to the list */
void insert_to_list(struct contact** head, struct contact** con);
/* free the list */
void free_list(struct contact** head);
/* function to read the file content */
void read_contacts_file(char* file_name);
/* function to ask for deletion to prevent duplicate code */
int ask_for_delete(struct contact **rear , struct contact **front , int i);
/* function to swap data */
void swap(struct contact** a, struct contact **b);

int last;

int main()
{
    int count=1;
    char n;
    read_contacts_file("/home/abed/CLionProjects/untitled/phonebookFile");
    while(count) {
        clrscr();
        printf("\n|Phone Book12<::>Home|\n");
        printf("--------------------------------------------------------------------------------\n");
        printf("Welcome to PHONE BOOK2022!\nYou have inserted ( %d ) contacts.\n\n",last);
        printf("\t[1] |--> Insert\n");
        printf("\t[2] |--> Delete\n");
        printf("\t[3] |--> Edit\n");
        printf("\t[4] |--> Search\n");
        printf("\t[5] |--> Show All\n");
        printf("\t[6] |--> Sort\n");
        printf("\t[7] |--> Help\n");
        printf("\t[8] |--> Exit\n");
        printf("\n\tPlease Enter Your Choice (1-8): ");
        n = getc(stdin);
        getc(stdin);
        switch(n) {
            case '1':
                insert();
                break;
            case '2':
                delet();
                break;
            case '3':
                edit();
                break;
            case '4':
                search();
                break;
            case '5':
                list();
                break;
            case '6':
                sort();
                break;
            case '7':
                help();
                break;
            case '8':
                free_list(&A);
                exit(1);
                break;
            default:
                printf("\nThere is no item with symbol \"%c\".Please enter a number between 1-8!\nPress any key to continue...",n);
                //getc(stdin);
                getc(stdin);
                break;
        }//End of swicth
    }
    return 0;
}//End of main function!

void insert(void)
{
    char ans='y';
    struct contact *person = NULL;
    clrscr();
    printf("\nPhone Book12<::>Insert Contacts");
    printf("\n--------------------------------------------------------------------------------");

    while(ans=='y'){

        person = (struct contact*) malloc (sizeof(struct contact));
        person->next_fname = NULL;
        printf("\n\nData of Contact %2.2d{\n",last+1);
        printf("\n\t  1-F.Name: ");
        read_input(person->fname, sizeof(person->fname));

        printf("\t  2-L.Name: ");
        read_input(person->lname, sizeof(person->lname));

        printf("\t  3-Tele.P: ");
        read_input(person->telep, sizeof(person->telep));

        printf("\t  4-Cell.P: ");
        read_input(person->cellp, sizeof(person->cellp));

        if(check_contact_exist(&person))
        {
            printf("\n|-->contact already exists!}");
            free(person);
        }
        else{
            insert_to_list(&A,&person);
            printf("\n|-->Data Recorded!}");
            last++;
        }
        printf("\n\t\t\tNext Contact?(y/n) Answer:");
        ans = getc(stdin);
        getc(stdin);
        person = NULL;
    }
    printf("\n\nYou have inserted ( %d ) contact!\nPress a key to return main page & continue program|-->",last);
    getc(stdin);
}

void delet(void)
{
    char dfname_string[31],dlname_string[31];
    register int i = 0,j,find=0;
    char ch;
    struct contact* head = A,
            *front = NULL,
            *rear = NULL,
            *temp = NULL;
    clrscr();
    printf("\nPhone Book12<::>Delete Contacts");
    printf("\n--------------------------------------------------------------------------------");
    printf ("\n::Enter data of the contact that you want delete it,please:");
    printf("\n\n  ::Enter first name: ");
    read_input(dfname_string, sizeof(dfname_string));

    printf("\n  ::Enter last name: ");
    read_input(dlname_string, sizeof(dlname_string));


    if (A == NULL)
        find = 0;

    if (strcmp (dfname_string, A->fname) == 0 && strcmp (dlname_string, A->lname) == 0 ) {
        find = ask_for_delete(&A, NULL, i);
    }
    else {
        rear = A,
        front = A->next_fname;
        while (front != NULL) {
            if (strcmp(dfname_string, front->fname) == 0 && strcmp(dlname_string, front->lname) == 0)
                break;
            i++;
            rear = front;
            front = front->next_fname;
        }
        find = ask_for_delete(&rear, &front, i);
    }
    if (find==0)
        printf("\t\t\n<<This contact does not exist in this list or program can not delete it.>>");
    else if(find==1)
        printf("\t\t\n<<Target contact was successfully deleted from list!>>");
    printf("\n\n\nPress a key to return main page & continue program|-->");
    getc(stdin);
}
/* function to ask for deletion to prevent duplicate code */
int ask_for_delete(struct contact **rear , struct contact **front , int i){
    char ch;
    struct contact *temp;
    printf("\nContact was found! Details:");
    printf("\n\nCantact %2.2d{",i+1);
    printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",
           (*rear)->fname, (*rear)->lname, (*rear)->telep, (*rear)->cellp);
    printf("\n\nAre you sure you want to delete this contact?(y/n)");
    ch = getc(stdin);
    getc(stdin);
    if(ch == 'y'){
        // first node
        if (front == NULL)
        {
            temp = (*rear);
            *rear = (*rear)->next_fname;
            free(temp);
        }
        else{
            // if in middle
            if ((*front) != NULL)
                (*rear)->next_fname = (*front)->next_fname;
            free((*front));
        }
        last--;
        return  1;
    }
    else if(ch == 'n')
    {
        return 2;
    }
    return 0;
}

void edit()
{
    char dfname[31] ,dlname[31];
    register int i = 0,find=0;
    char ch;
    struct contact *head = A,
            *prev= NULL,
            *next = NULL,
            *temp =NULL;

    clrscr();
    printf("\nPhone Book12<::>Edit Contacts");
    printf("\n--------------------------------------------------------------------------------");
    printf ("\n::Enter data of the contact that you want edit it,please:");

    printf("\n\n  ::Enter first name: ");
    read_input(dfname, sizeof(dfname));
    printf("\n  ::Enter last name: ");
    read_input(dlname, sizeof(dlname));

    //208223826
    while(head != NULL)
    {
        if (strcmp (dfname, head->fname) == 0 && strcmp (dlname, head->lname) == 0 ) {
            printf("\nContact found! Details:");
            printf("\n\nCantact %2.2d{",i+1);
            printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",
                   head->fname, head->lname, head->telep, head->cellp);
            printf("\n\nDo you want edit it?(y/n) ");
            ch = getc(stdin);
            getc(stdin);
            if(ch=='y'){
                temp = (struct contact*) malloc (sizeof(struct contact));
                printf("\n::Enter NEW data for this contact...");
                printf("\n >|Enter new first name: ");
                read_input(temp->fname, sizeof(temp->fname));

                printf(" >|Enter new last name: ");
                read_input(temp->lname, sizeof(temp->lname));

                printf(" >|Enter new telephone number: ");
                read_input(temp->telep, sizeof(temp->telep));

                printf(" >|Enter new cellphone number: ");
                read_input(temp->cellp, sizeof(temp->cellp));
                if( prev == NULL)
                {
                    next = head->next_fname;
                    free(head);
                    A = next;
                }
                else if(head->next_fname == NULL)
                {
                    free(head);
                    prev->next_fname = NULL;
                }
                else{
                    next = head->next_fname;
                    free(head);
                    prev->next_fname = next;
                }

                insert_to_list(&A, &temp);
                find=1;
                break;
            }
        }
        i++;
        prev = head;
        head = head->next_fname;
    }

    if (find==0)
        printf("\t\t\n<<This contact does not exist or you chose not to Edit it.>>");
    else
        printf("\t\t\n<<Target contact was successfully updated!>>");
    printf("\n\n\n   ::Press a key to return main page & continue program|-->");
    getc(stdin);
}


void search(void)
{
    char ch;
    clrscr();
    printf("\nPhone Book12<::>$earch Contacts");
    printf("\n--------------------------------------------------------------------------------");
    printf("\nChoose search type,please:\n\n");
    printf("\t[1] |--> Search by first name\n");
    printf("\t[2] |--> Search by last name\n");
    printf("\t[3] |--> Search by phone number\n");
    printf("\t[4] |--> Search by cellphone number\n");
    printf("\t[5] |--> Main Menu\n");
    printf("\n\t::Enter a number (1-5): ");
    ch = getc(stdin);
    getc(stdin);
    printf("\n--------------------------------------------------------------------------------");
    switch(ch) {
        case '1':
            searchf();
            break;
        case '2':
            searchl();
            break;
        case '3':
            searchp();
            break;
        case '4':
            searchc();
            break;
        case '5':
        default:
            return;
    }
}

void searchf(void)
{
    struct contact *head = A;
    char fname[31];
    register int i = 0,find=0;
    printf("Enter a first name to search:");
    read_input(fname,sizeof(fname));
    // running for last !!!!!!

    while(head != NULL)
    {
        if(strcmp(fname, head->fname) == 0) {
            find=1;
            break;
        }
        head = head->next_fname;
        i++;
    }

    if(find==0)
        printf("\t\n<<Not Find!There is no contact with this name in phone book.>>");
    else {
        printf("\t\n<<Target contact found! Details:>>");
        printf("\n\nCantact %2.2d{",i+1);
        printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",
               head->fname, head->lname, head->telep, head->cellp);
    }
    printf("\nPress a key to search another contact.");
    getc(stdin);
    search();
}

void searchl(void)
{
    struct contact *head = A;
    char lname[31];
    register int i = 0,find=0;
    printf("\n::Enter a last name to search:");
    read_input(lname, sizeof(lname[31]));
    while(head != NULL)
    {
        if(strcmp(lname, head->lname) == 0) {
            find=1;
            break;
        }
        head = head->next_fname;
        i++;
    }
    if(find==0)
        printf("\t\n<<Not Find!There is not contact with tish name in phone book.>>");
    else {
        printf("\t\n<<Target contact found! Details:>>");
        printf("\n\nCantact %2.2d{",i+1);
        printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",
               head->fname, head->lname, head->telep, head->cellp);
    }
    printf("\nPress a key to search another contact.");
    getc(stdin);
    search();
}

void searchp(void)
{
    struct contact *head = A;
    char phone[31];
    int i = 0,find=0;
    printf("\n::Enter a phone number to search:");
    read_input(phone, sizeof(phone));
    while(head != NULL)
    {
        if(strcmp(phone, head->telep) == 0) {
            find=1;
            break;
        }
        head = head->next_fname;
        i++;
    }
    if(find==0)
        printf("\t\n<<Not Found!There is not contact with tish phone number  in phone book.>>");
    else{
        printf("\t\n<<Target contact found! Details:>>");
        printf("\n\nCantact %2.2d{",i+1);
        printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",
               head->fname, head->lname, head->telep, head->cellp);
    }
    printf("\nPress a key to search another contact.");
    getc(stdin);
    search();
}

void searchc(void)
{
    struct contact *head = NULL;
    char phone[31];
    int i = 0,find=0;
    printf("\n::Enter a cellphone number to search:");
    read_input(phone, sizeof(phone));

    while(head != NULL)
    {
        if(strcmp(phone, head->cellp) == 0) {
            find=1;
            break;
        }
        head = head->next_fname;
        i++;
    }
    if(find==0)
        printf("\t\n<<Not Find!There is not contact with tish cellphone number in phone book.>>");
    else {
        printf("\t\n<<Target contact found! Details:>>");
        printf("\n\nCantact %2.2d{",i+1);
        printf("\n\t   F.Name:%s\n\t   L.name:%s\n\t   Tele.P:%s\n\t   Cell.P:%s\n\t   }",
               head->fname, head->lname, head->telep, head->cellp);
    }
    printf("\nPress a key to search another contact.");
    getc(stdin);
    search();
}

void sort(void)
{
    char ch;
    clrscr();
    printf("\nPhone Book12<::>$earch Contacts");
    printf("\n--------------------------------------------------------------------------------");
    printf("\nChoose sort type,please:\n\n");
    printf("\t[1] |--> Sort by first name\n");
    printf("\t[2] |--> Sort by last name\n");
    printf("\t[3] |--> Sort by phone number\n");
    printf("\t[4] |--> Sort by cellphone number\n");
    printf("\t[5] |--> Main Menu\n");
    printf("\n\t::Enter a number (1-5): ");
    ch = getc(stdin);
    getc(stdin);
    printf("\n--------------------------------------------------------------------------------");
    switch(ch){
        case '1':
            sortf();
            break;
        case '2':
            sortl();
            break;
        case '3':
            sortp();
            break;
        case '4':
            sortc();
        case '5':
        default:
            return ;
    }
}

void sortf(void)
{
    struct contact * curr = A;
    struct contact *next = NULL;
    while (curr && curr->next_fname)
    {

        next = curr->next_fname;
        while (next)
        {
            if (strcmp(curr->fname, next->fname) >0)
            {
                swap(&next, &curr);
            }
            next = next->next_fname;
        }
        curr = curr->next_fname;
    }

    printf("\nplease wait... .Contacts will be sorted by first names.");
    list2();
    printf("\n   ::Press any key to sort contact by another form... ");
    getc(stdin);
    sort();
}

void sortl(void)
{
    struct contact * curr = A;
    struct contact *next = NULL;
    while (curr && curr->next_fname)
    {

        next = curr->next_fname;
        while (next)
        {
            if (strcmp(curr->lname, next->lname) >0)
            {
                swap(&next, &curr);
            }
            next = next->next_fname;
        }
        curr = curr->next_fname;
    }
    printf("\nplease wait... .Contacts will be sorted by last names.");
    list2();
    printf("\n   ::Press any key to sort contact by another form... ");
    getc(stdin);
    sort();
}
void sortp(void)
{
    struct contact * curr = A;
    struct contact *next = NULL;
    while (curr && curr->next_fname)
    {

        next = curr->next_fname;
        while (next)
        {
            if (strcmp(curr->telep, next->telep) >0)
            {
                swap(&next, &curr);
            }
            next = next->next_fname;
        }
        curr = curr->next_fname;
    }
    printf("\nplease wait... .Contacts will be sorted by telephone numbers.");
    list2();
    printf("\n   ::Press any key to sort contact by another form... ");
    getc(stdin);
    sort();
}
void sortc(void)
{
    struct contact * curr = A;
    struct contact *next = NULL;
    while (curr && curr->next_fname)
    {

        next = curr->next_fname;
        while (next)
        {
            if (strcmp(curr->cellp, next->cellp) >0)
            {
                swap(&next, &curr);
            }
            next = next->next_fname;
        }
        curr = curr->next_fname;
    }
    printf("\nPlease wait... .Contacts will be sort by cellphone numbers.");
    list2();
    printf("\n   ::Press any key to sort contact by another form... ");
    getc(stdin);
    sort();
}

void list()
{
    struct contact* head = A;
    register int i = 0;
    clrscr();
    printf("\nPhone Book12<::>All Contacts List");
    printf("\n--------------------------------------------------------------------------------");
    gotoxy(1,4);
    printf("Row");
    gotoxy(9,4);
    printf("First Name");
    gotoxy(27,4);
    printf("Last Name");
    gotoxy(44,4);
    printf("Telephone");
    gotoxy(60,4);
    printf("Cellphone");
    printf("\n--------------------------------------------------------------------------------");

    while(head != NULL)
    {
        gotoxy(1,i+6);
        printf("%3.3d",i+1);
        gotoxy(9,i+6);
        printf("%s", head->fname);
        gotoxy(28,i+6);
        printf("%s", head->lname);
        gotoxy(44,i+6);
        printf("%s", head->telep);
        gotoxy(60,i+6);
        printf("%s", head->cellp);

        i++;
        head = head->next_fname;
    }

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t    **********End Of list!**********");
    printf("\n\n\n   ::Press a key to return main page & continue program.|-->");
    getc(stdin);
}

void list2(void)
{
    struct contact* head = A;
    register int i =0;
    printf("\n--------------------------------------------------------------------------------");
    gotoxy(1,18);
    printf("Row");
    gotoxy(9,18);
    printf("First Name");
    gotoxy(27,18);
    printf("Last Name");
    gotoxy(44,18);
    printf("Telephone");
    gotoxy(60,18);
    printf("Cellphone");
    printf("\n--------------------------------------------------------------------------------");

    while(head != NULL)
    {
        gotoxy(1,i+21);
        printf("%3.3d",i+1);
        gotoxy(9,i+21);
        printf("%s", head->fname);
        gotoxy(27,i+21);
        printf("%s", head->lname);
        gotoxy(44,i+21);
        printf("%s", head->telep);
        gotoxy(60,i+21);
        printf("%s", head->cellp);

        i++;
        head = head->next_fname;
    }

    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    printf("\n\t\t    **********End Of list!**********");
}

void help(void)
{
    clrscr();
    gotoxy(26,1);
    printf("--------------------------");
    gotoxy(26,2);
    printf("|Welcome To Phone Book12!|");
    gotoxy(26,3);
    printf("--------------------------");
    gotoxy(1,5);
    printf("PhoneBook12>>[Help & Instructions] \n");
    printf("--------------------------------------------------------------------------------\n");
    printf("\nAbout Phonebook12\n *Version: 2.5\n *Valence: 50 Contacts(MAX)\n  *By: Morteza Zakeri (2011-12)");
    printf("\n\nThis program allows you to have a list of your contacts.\nIt also allows you to have your listing added or deleted from your list.\nOther features of this program include:\nSearch,edit,sort & list.\n\n   ::Press a key to return main page & continue program.|-->");
    getc(stdin);
}

void clrscr()
{
    system("clear");
}

void gotoxy(int x, int y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}
/* checking if the contact already exists */
bool check_contact_exist(struct contact** person)
{
    struct contact* head = A;
    while(head != NULL)
    {
        if(strcmp((*person)->fname, head->fname) == 0 &&
           strcmp((*person)->lname, head->lname) == 0 &&
           strcmp((*person)->telep, head->telep) == 0 &&
           strcmp((*person)->cellp, head->cellp) == 0)
            return true;
        head = head->next_fname;
    }
    return false;
}
/* function to read input from user*/
void read_input(char* dest, int max)
{
    char *string = NULL;
    size_t len= max;
    size_t len_size=0;
    string = (char*) malloc(max * sizeof(char));
    len_size = getline(&string,&len,stdin);
    if(string[len_size - 1] == '\n'){
        string[len_size - 1] = '\0';
        len_size--;
    }
    if(len_size >= max)
    {
        string[len_size -1] = '\0';
    }
    strcpy(dest, string);
    free(string);
}
/* funtion to add new node to the list */
void insert_to_list(struct contact** head, struct contact** con) {

    struct contact *rear = NULL,
            *node = *con,
            *front = NULL;

    //If linked list is empty
    if (*head == NULL )
    {
        *head = node;
        (*head)->next_fname = NULL;
        //node = NULL;
        return;
    }
    else if (strcmp((*con)->fname, (*head)->fname) <= 0 ) {
        node->next_fname = *head ;
        *head = node;
    }
    else {
        rear = *head;
        front = rear->next_fname;
        while (front != NULL && strcmp(front->fname, node->fname) <= 0) {
            rear = front;
            front = front->next_fname;
        }
        rear->next_fname = node;
        node->next_fname = front;
    }
}
/* free the list */
void free_list(struct contact** head) {
    struct contact *temp = NULL;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next_fname;
        free(temp);
    }
}
/* function to read the file content */
void read_contacts_file(char *file_name) {
    struct contact *person = NULL;
    FILE *fp;
    char * line = NULL;
    char * pch;
    size_t len = 0;
    size_t len_size;

    fp = fopen(file_name, "r");

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    // reading line then split
    while ((len_size = getline(&line, &len, fp)) != -1) {
        person = (struct contact*) malloc(sizeof(struct contact));
        person->next_fname = NULL;
        // must check after strtok
        pch = strtok (line,"\t");
        strcpy(person->fname, pch);
        pch = strtok (NULL, "\t");
        strcpy(person->lname, pch);
        pch = strtok (NULL, "\t");
        strcpy(person->telep, pch);
        pch = strtok (NULL, "\t");
        strcpy(person->cellp, pch);

        insert_to_list(&A, &person);
        last++;
    }

    fclose(fp);
    if (line)
        free(line);
}
/* function to swap data */
void swap(struct contact **a, struct contact **b) {
    char fname[31];
    char lname[31];
    char telep[15];
    char cellp[15];
    // temp = a
    strcpy(fname,(*a)->fname);
    strcpy(lname,(*a)->lname);
    strcpy(telep,(*a)->telep);
    strcpy(cellp,(*a)->cellp);
    // a = b
    strcpy((*a)->fname,(*b)->fname);
    strcpy((*a)->lname,(*b)->lname);
    strcpy((*a)->telep, (*b)->telep);
    strcpy((*a)->cellp, (*b)->cellp);
    // b = temp
    strcpy((*b)->fname,fname);
    strcpy((*b)->lname,lname);
    strcpy((*b)->telep, telep);
    strcpy((*b)->cellp, cellp);
}

