//this is the main project file:
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

//          criminal database in the files are made by Ritesh Harihar

void clrscr()
{
    system("@cls||clear");
}
//      made by Ritesh Harihar
struct date{                //date structure
int d, m, y;
};


//      made by Ritesh Harihar
struct police{              //police structure

char police_code[10];

char incharge[100];

char area[100];

int staff;

int no_of_criminals;

struct police* next;

struct criminal* cr;

};


//          made by Ritesh Harihar
struct criminal{            //criminal structure

char name[100];

int crime_code;

int criminalno;

char caseincharge[100];

int tenure;

struct date admit;

struct date release;

struct criminal* next;
};



struct police* p = NULL;        //police station head declared globally


//          made by Shriyam Tripathi
void newcriminal(char pcode[], char n[], int crimecode,  int criminaln, char incharge[], int t, int d1, int d2, int m1, int m2, int y1, int y2){        //function to add new criminal

if(p==NULL){

    printf("The police station does not exist!!");
    return;
}
else{

    struct police* temp=p;

    while(temp!=NULL && strcmp(temp->police_code, pcode)!=0)
        temp = temp->next;
    if(temp==NULL){

    printf("The police station does not exist!!");
    return;
    }
    else{

        temp->no_of_criminals++;
        struct criminal* c =(struct criminal*)malloc(sizeof(struct criminal));
        strcpy(c->name, n);
        c->crime_code = crimecode;
        c->criminalno = criminaln;
        strcpy(c->caseincharge, incharge);
        c->tenure = t;
        c->admit.d = d1; c->admit.m = m1; c->admit.y = y1; c->release.d = d2; c->release.m = m2; c->release.y = y2;
        c->next = NULL;
        struct criminal* temp1 = temp->cr;

        if(temp1==NULL){

            temp->cr = c;
            return;
        }
        else{

        while(temp1->next!=NULL)
            temp1 = temp1->next;
        temp1->next = c;
        return;
        }
    }
}
}

//      made by Ritesh Harihar
void newpolicestation(char pcode[], char inchrg[], char a[], int s){        //function to add new police station

struct police* p1 = (struct police*)malloc(sizeof(struct police));
strcpy(p1->police_code, pcode);
strcpy(p1->incharge, inchrg);
strcpy(p1->area, a);
p1->staff=s;
p1->no_of_criminals = 0;
p1->next = NULL;
p1->cr = NULL;

if(p==NULL){

    p=p1;
    return;
}
else{

    struct police* temp =p;

    while(temp->next!=NULL)
        temp = temp->next;
    temp->next = p1;
    return;
}
}


//          made by Shriyam tripathi
void load_data(){                                       //function to load data from the files into the linked lists

FILE *f = fopen("files/policestations.txt", "r");
char pcode[10], inchargef[100], inchargel[100], area[100];
int staff;

while(!feof(f)){

    fscanf(f, "%s %s %s %s %d\n", pcode, inchargef, inchargel, area, &staff);
    strcat(inchargef, " ");
    strcat(inchargef, inchargel);
    newpolicestation(pcode, inchargef, area, staff);
}
fclose(f);


struct police* temp = p;

char loc[100]= "files/", namef[100], namel[100];
int crimec, criminalno, t, d1, d2, m1, m2, y1, y2;

while(temp!=NULL){

    strcat(loc, temp->police_code);
    strcat(loc, ".txt");
    f = fopen(loc, "r");
    while(!feof(f)){
    fscanf(f, "%s %s %d %d %s %s %d %d %d %d %d %d %d\n", namef, namel, &crimec, &criminalno, inchargef, inchargel, &t, &d1, &m1, &y1, &d2, &m2, &y2);
    strcat(inchargef, " ");
    strcat(namef, " ");
    strcat(inchargef, inchargel);
    strcat(namef, namel);
    newcriminal(temp->police_code, namef, crimec, criminalno, inchargef, t, d1, d2, m1, m2, y1, y2);
    }

    fclose(f);
    strcpy(loc, "files/");
    temp = temp->next;
}

}

//          made by Shriyam tripathi
void update_data(){         //updates the information in the files

struct police* p1 = p;

FILE *f = fopen("files/policestations.txt", "w");

while(p1!=NULL){
    fprintf(f, "%s %s %s %d\n", p1->police_code, p1->incharge, p1->area, p1->staff);
    p1 = p1->next;
}

fclose(f);
p1= p;

char fname[100]="files/";
struct criminal *temp=NULL;

while(p1!=NULL){
    temp = p1->cr;
    strcat(fname, p1->police_code);
    strcat(fname, ".txt");
    f = fopen(fname, "w");

    while(temp!=NULL){
        fprintf(f, "%s %d %d %s %d %d %d %d %d %d %d\n", temp->name, temp->crime_code, temp->criminalno, temp->caseincharge,  temp->tenure, temp->admit.d, temp->admit.m, temp->admit.y, temp->release.d, temp->release.m, temp->release.y);
        temp = temp->next;
    }

    fclose(f);
    p1 = p1->next;
    strcpy(fname, "files/");

}
}

//      made by Ritesh Harihar
void printall(){

struct police *temp = p;
struct criminal *c =NULL;

while(temp!=NULL){

    printf("%s %s %s %d %d\n\n", temp->police_code, temp->incharge, temp->area, temp->staff, temp->no_of_criminals);
    c =temp->cr;
    while(c!=NULL){
        printf("%s %d %d %s %d %d %d %d %d %d %d\n\n", c->name, c->crime_code, c->criminalno, c->caseincharge, c->tenure, c->admit.d, c->admit.m, c->admit.y, c->release.d, c->release.m, c->release.y);
        c =c->next;
    }
    temp = temp->next;

}
}

//          made by Namish Aggarwal
int searchpolice(char pcode[]){

struct police* temp = p;

if(strcmp(p->police_code, pcode)==0)
    return 1;
else{

    while(temp->next!=NULL){
        temp = temp->next;
        if(strcmp(temp->police_code, pcode)==0)
            return 1;
    }

    return 0;
}
}

//      made by Namish Aggarwal
int searchcriminal(int crimeno){

struct police *temp = p;
struct criminal *temp2 = NULL;

while(temp!=NULL){

    temp2 = temp->cr;

    while(temp2!=NULL){
        if(temp2->criminalno== crimeno)
            return 1;
        temp2 = temp2->next;
    }

    temp = temp->next;
}

return 0;
}

//          made by Namish Aggarwal
void deletecriminal(int crimeno){

struct police* temp = p;
struct criminal* temp2 = NULL;

while(temp!=NULL){

    temp2 = temp->cr;

    if(temp2->criminalno==crimeno){

        temp->cr = temp->cr->next;

        printf("1 criminal record with crime number %d deleted successfully!!\n", crimeno);
        return;
    }
    else{

    while(temp2->next!=NULL){

        if(temp2->next->criminalno==crimeno){

            temp2->next = temp2->next->next;

            printf("1 criminal record with crime number %d deleted successfully!!\n", crimeno);
            return;
        }
        temp2 = temp2->next;
    }

    }
    temp = temp->next;
}


printf("Criminal with crime number %d does not exists!!", crimeno);
return;
}

//          made by Namish Aggarwal
void deletepolice(char policecode[]){

struct police* ptr = p;

if(strcmp(p->police_code, policecode)==0){

    p = p->next;

    printf("Police Station with police code %s deleted successfully!!\n", policecode);
    return;
}
else
while(ptr->next!=NULL){
    if(strcmp(ptr->next->police_code, policecode)==0){

        ptr->next = ptr->next->next;

        printf("Police Station with police code %s deleted successfully!!\n", policecode);
        return;
    }
    ptr = ptr->next;

}

printf("Police Station with police code %s does not exists!!\n", policecode);

return;
}


//          made by Eshan dhawan

void edit()
{
printf("ENTER \n 1 to edit police station \n 2 to edit any criminal\'s info ");
int ch;
ch=0;
char nname[100];
int number;
scanf("%d",&ch);
int repeat;
switch (ch)
{
case 1:
printf("enter the police station code  of the police station whose details you want to edit \n ");
char polcode[30];
scanf("%s",polcode);
struct police *station;
int polche;
polche=searchpolice(polcode);
if(polche==0)
{

    printf("police station not found\n ");

}
else
{
    do
    {
        struct police* temp = p;

if(strcmp(p->police_code, polcode)==0)
    station=p;
else{

    while(temp->next!=NULL){
        temp = temp->next;
        if(strcmp(temp->police_code, polcode)==0)
            station=p;
    }}

    printf("ENTER \n 2 to change the station incharge \n 3 to change the area covered \n 4to change the number of staff recruited \n 5 change the capacity of criminals that can be stationed  ");
    int change;
    scanf("%d",&change);
    switch(change)
    {


    case 2:
         printf("enter the new name of the station incharge ");

        gets(nname);
        strcpy(nname,station->incharge);
        break;
    case 3:
         printf("enter the new area to be covered ");

        gets(nname);
        strcpy(nname,station->area);
        break;
    case 4:
         printf("enter the new number of staff in the  station ");

        scanf("%d",&number);
         station->staff = number;
         break ;
    case 5:
        printf("enter the new number of criminals in the station ");

        scanf("%d",&number);
         station->no_of_criminals = number;
         break ;
    default :
        printf("option not found");
        break;

    }

     printf("enter 1 to edit any detail else any thing to exit");

    scanf("%d",&repeat);

    } while(repeat==1);
    }

break;




case 2:
    printf("enter the criminal number of the criminal you want to search");
    int crim_no;
    scanf("%d",&crim_no);
     struct criminal *person;
     int checri;
     checri=searchcriminal(crim_no);
     if(checri==0)
     {
         printf("criminal not found");

     }

else
{
    struct police *temp = p;
struct criminal *temp2 = NULL;

while(temp!=NULL){

    temp2 = temp->cr;

    while(temp2!=NULL){
        if(temp2->criminalno== crim_no)
            person=temp2;
        temp2 = temp2->next;
    }


    do
    {
    printf("ENTER\n 1 to change name of criminal \n 2 to change the case incharge \n 3 to change the crime code \n 4 to change the tenure and change the date to relese of the criminal  ");
    int change;
    scanf("%d",&change);
    switch(change)
    {

    case 1:
        printf("enter the new name of the criminal ");
            gets(nname);
        strcpy(nname,person->name);
        break;
    case 2:
         printf("enter the new name of the case incharge ");

        gets(nname);
        strcpy(nname,person->caseincharge);
        break;
    case 3:
         printf("enter the new crime code ");

        scanf("%d",&number);
         person->crime_code = number;
         break ;
    case 4:
         printf("enter the new tenure ");

        scanf("%d",&number);
         person->tenure = number;
         struct date relese;
         printf("enter the date of relese");
         scanf("%d%d%d",relese.d,relese.m,relese.y);
         person->release=relese;
         break ;

    default :
        printf("option not found");
        break;

    }

     printf("enter 1 to edit any detail else any thing to exit");

    scanf("%d",&repeat);

    } while(repeat==1);
}

break;
    default :
        printf("invalid choice");

}


}
}



//          made by Namish Aggarwal
void  displaydata()
{
     struct police* temp=p;
     struct criminal* temp2;
      int pn=0,cn=0;

     if(temp==NULL)
     {   printf(" The police stations are not added yet !!!!!! \n");
          return;
     }


     while(temp!=NULL)
     {
        pn++;
        cn=0;
           temp2=temp->cr;

           printf("\n Police Station: %d \n      Code: %s",pn,temp->police_code);Sleep(50);
           printf("\n       Incharge: %s",temp->incharge);Sleep(50);
           printf("\n       Area Under: %s",temp->area);Sleep(50);
           printf("\n       Staff count: %d",temp->staff);Sleep(50);
           printf("\n       No. of criminals: %d\n",temp->no_of_criminals);Sleep(50);


           if(temp2==NULL)
            printf("\n No criminal in this police station !!!!!!!!!!");
           else
            while(temp2!=NULL)
            {
                ++cn;
                printf("\n   Criminal no.: %d",cn);Sleep(50);
                printf("\n      Name: %s",temp2->name);Sleep(50);
                printf("\n      Code: %d",temp2->criminalno);Sleep(50);
                printf("\n      Crime: %d",temp2->crime_code);Sleep(50);
                printf("\n      Case Incharge: %s",temp2->caseincharge);Sleep(50);
                printf("\n      Admit Date: %d-%d-%d", temp2->admit.d, temp2->admit.m, temp2->admit.y);
                printf("\n      Release Date: %d-%d-%d",temp2->release.d, temp2->release.m, temp2->release.y);
                printf("\n      Tenure: %d",temp2->tenure);Sleep(50);
                temp2=temp2->next;
            }

            temp=temp->next;
     }

  return ;
}



// made by Shriyam Tripathi
int main(){

system ("color f0");

load_data();
//printall();

printf("\n\n");
printf("Welcome to our Police Station Terminal!!\n\n");
int userid;
char pass[10];

while(1){

printf("Please enter your userid and password to proceed\n\n");

scanf("%d%s", &userid, &pass);
int n=6;
while(n--){
    Sleep(200);
    printf(". ");
}
if(userid==123456 && strcmp(pass, "project")==0){
    break;
}
else{
    printf("Entered username and password are not correct!!\nPlease try again to proceed!!\n\n");
    int x;
    printf("enter '1' to try again or '2' to exit\n");

    scanf("%d", &x);

    if(x==2){
        update_data();
        exit(0);
    }
}
}

    clrscr();
    printf("Login success!!\n\n");
    Sleep(500);
    while(1){
    clrscr();
    int i;
    printf("Enter '1' to print the records\n");
    printf("Enter '2' to insert the records\n");
    printf("Enter '3' to delete the records\n");
    printf("Enter '4' to edit the records\n");
    printf("Enter '5' to search a record\n");
    printf("Enter '6' to exit the system\n");
    scanf("%d", &i);
    if(i==1){
        printf("Here are all the records that are in database::\n\n");
        displaydata();

    }
    else if(i==2){
            int j;
        printf("Enter '1' if you want to insert a criminal\n");
         printf("Enter '2' if you want to insert a police station\n");
         scanf("%d", &j);
         if(j==1){
            printf("Enter the police station code:\n");
            char pcode[10];
            scanf("%s", pcode);
            printf("Enter the criminal name:\n");
            char name[100];
            scanf("%s", name);
            printf("Enter the crime code:\n");
            int crcode;
            scanf("%d", &crcode);
            printf("Enter the criminal number:\n");
            int crnumber;
            scanf("%d", &crnumber);
            printf("Enter the incharge name:\n");
            char incharge[100];
            scanf("%s", incharge);
            int t, d1, m1, y1, d2, m2, y2;
            printf("Enter tenure, date of admittance and date of release:\n");
            scanf("%d%d%d%d%d%d%d", &t, &d1, &m1, &y1, &d2, &m2, &y2);
            newcriminal(pcode, name, crcode, crnumber, incharge, t, d1, d2, m1, m2, y1, y2);
            printf("New Criminal added\n\n");
    }
    else{
        printf("Enter the police station code:\n");
            char pcode[10];
            scanf("%s", pcode);
            printf("Enter the police station incharge:\n");
            char incharge[100];
            scanf("%s", incharge);
            printf("Enter the area name:\n");
            char area[100];
            scanf("%s", area);
            printf("Enter the number of staff:\n");
            int s;
            scanf("%d", &s);
            newpolicestation(pcode, incharge, area, s);
            printf("New police station record has been added!!\n\n");

    }
    update_data();
    }
    else if(i==3){
        int j;
        printf("Enter '1' to delete police station or '2' to delete a criminal:\n\n");
        scanf("%d", &j);
        if(j==1){
            printf("Enter the police code:\n");
            char pcode[100];
            scanf("%s", pcode);
            deletepolice(pcode);
            printf("Record deleted successfully!!");
        }
        else{
            printf("Enter the criminal number:\n");
            int k;
            scanf("%d", &k);
            deletecriminal(k);
            printf("Criminal deleted successfully!!");
        }
        update_data();
    }
    else if(i==4){
        edit();
        update_data();
    }
    else if(i==5){
        int j;
        printf("Enter '1' if you want to search a criminal\n");
         printf("Enter '2' if you want to search a police station\n");
         scanf("%d", &j);
         if(j==1){
            printf("Enter the criminal number:\n");
            int k;
            scanf("%d", &k);
            if(searchcriminal(k))
                printf("Criminal with %d crime number exists!!", k);
            else
                printf("Criminal with %d crime number does not exists!!", k);
         }
         else{
            printf("Enter the police code:\n");
            char pcode[100];
            scanf("%s", pcode);
            if(searchpolice(pcode))
                printf("Police Station with %s police code exists!!", pcode);
            else
                printf("Police Station with %s police code does not exists!!", pcode);
         }
         update_data();
    }
    else if(i==6){
        update_data();
        exit(0);
    }

    int k;
    printf("\nEnter 1 to get more information or 2 to exit");
    scanf("%d", &k);
    if(k==2){
        update_data();
        break;
    }
    update_data();
    }
update_data();
return 0;
}
