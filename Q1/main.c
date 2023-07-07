#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_PERSON 500

typedef struct{

        char name_surname[50];

        float time;

    }Person;

void addSurnameBeginning(char *name_surname);
int compareNames(const void* a, const void* b);
void printRead(char file_name[], char sort[]);


int main()
{
    char file_name[100];
    char sort_option[3];



    printf("Enter the input file name: \n");
    scanf(" %s",file_name);

    FILE* filep = fopen(file_name,"r");


    if(filep == NULL){
        printf("file not found");
        exit(1);
    }
    rewind(filep);

    Person* arrayofPerson = malloc(sizeof(Person)*MAX_PERSON);

    if(arrayofPerson == NULL){
        printf("not enough memory");
        exit(1);
    }

    int count = 0;

    char current_line[1000];
    fgets(current_line,1000,filep);

    while(fgets(current_line,1000,filep)){

            char time[100];
            char name_surname[MAX_PERSON][100];


            char* part;
            char* line;

            line = current_line;
            part = strtok(line, ",");//enter time

            part = strtok(NULL, ",");//exit time

            part = strtok(NULL, ",");//duration

            arrayofPerson[count].time =atof(part);

            part = strtok(NULL, ",");       //name and surname part


            strcpy(arrayofPerson[count].name_surname, part);

            addSurnameBeginning(arrayofPerson[count].name_surname);
            count++;
    }




        int deleted = 0;
        for (int a = 0; a < count; a++) {
            int found = 0;
        for (int b = a + 1; b < count; b++) {

            if(strcasecmp(arrayofPerson[a].name_surname, arrayofPerson[b].name_surname) == 0)
            {
                found = 1;

                if(found){
                arrayofPerson[a].time += arrayofPerson[b].time;

                for(int deleted = b; deleted < count-1; deleted++)
                {
                    //equlizes 1 right element to left element
                    arrayofPerson[deleted].time = arrayofPerson[deleted+1].time;
                    strcpy(arrayofPerson[deleted].name_surname, arrayofPerson[deleted+1].name_surname);

                }
                count--;


                b--;

            }
            }
            else{
                continue;
            }

        }
    }



    fclose(filep);




    printf("Sort the results? (yes/no): \n");
    scanf("%s",sort_option);

    if(strcasecmp(sort_option,"yes")==0){

        qsort(arrayofPerson, count, sizeof(Person), compareNames);
        for(int i = 0;i<count;i++){
        printf("%s %.2f\n",arrayofPerson[i].name_surname,arrayofPerson[i].time);
    }

    }

    else{
        for(int i = 0;i<count;i++){
        printf("%s %.2f\n",arrayofPerson[i].name_surname,arrayofPerson[i].time);
    }
    }



    return 0;
}

int compareNames(const void *a, const void *b) {
    const Person *PersonA = (const Person *)a;
    const Person *PersonB = (const Person *)b;
    return strcasecmp(PersonA->name_surname, PersonB->name_surname);
}

void addSurnameBeginning(char *name_surname) {

    char surnames[100];
    char names[100];



    int index = 0;  //index of last space
    for (index = strlen(name_surname)-1; index >= 0; index--) {
        if (name_surname[index] == ' ') {       //finds index of last space
            break;
        }
    }


    strncpy(names, &name_surname[index+1], strlen(name_surname)-index);
    //copies only surname to surnames
    //and names only name
    strncpy(surnames, name_surname, index);

    strcpy(name_surname, names);    //adds names and surnames
    strcat(name_surname, " ");
    strcat(name_surname, surnames);
}









