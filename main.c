#include <stdio.h>
#include <stdlib.h>


struct Student_struct {
    char* email;
    char* firstName;
    char* lastName;
    int age;
    float gpa;
    struct Student_struct* next;
}*head;

struct Connections_struct{
    char* email1;
    char* email2;
    struct Connections_struct* next;
}*headConnect;

void add(char* email);
void removeStudent(char* email);
void connect(char* email1, char* email2);
void edit (char* email);
void display();
void disconnect(char* email1, char* email2);
void saveNetwork(char* peopleFilename, char* connectionsFilename);

void add(char* email) {

    struct Student_struct* new = (struct Student_struct*)malloc(sizeof(struct Student_struct));
    new->email = email;
    new->next = head;
    head = new;
}

void removeStudent(char* email){
    struct Student_struct* tempHead,*nextTemp;
    struct Connections_struct* tempConnectNode, *nextConnect;
    tempHead = head;
    tempConnectNode = headConnect;
    if (*tempHead->email == *email){
        head=head->next;
        return;
    }
    while(tempHead->next!=NULL){

        if(*tempHead->next->email==*email){
            break;

        } else {
            tempHead = tempHead->next;
        }
    }
    nextTemp = tempHead->next;
    if(tempHead->next!=NULL){
        if(nextTemp->next!=NULL){
            tempHead->next=nextTemp->next;
        }
        else{
            tempHead->next=NULL;
        }
    }
    free(nextTemp);

    if(*tempConnectNode->email1 == *email || *tempConnectNode->email2 == *email){
        headConnect = headConnect->next;
    }
    while(tempConnectNode->next!=NULL){

        if(*tempConnectNode->next->email1 == *email || *tempConnectNode->next->email2 ==*email ){
            break;

        } else {
            tempConnectNode = tempConnectNode->next;
        }
    }

    nextConnect = tempConnectNode->next;
    if(tempConnectNode->next!=NULL){
        if(nextConnect->next!=NULL){
            tempConnectNode->next = nextConnect->next;
        }
        else{
            tempConnectNode->next=NULL;
        }
    }
    free(nextConnect);
}

void connect(char* email1, char* email2){
    struct Connections_struct* newConnect = (struct Connections_struct*)malloc(sizeof(struct Connections_struct));
    newConnect->email1 = email1;
    newConnect->email2 = email2;
    newConnect->next = headConnect;
    headConnect = newConnect;
}

void edit (char* email){
    struct Student_struct* tempHead3;
    tempHead3 = head;
    while (*tempHead3 -> email != *email){
        tempHead3 = tempHead3 -> next;
    }
    if (tempHead3->email == NULL){
        printf("This email is not yet registered");
        return;
    }
    printf("Enter first name: ");
    char* firstName;
    scanf("%s", firstName);
    tempHead3->firstName = firstName;
    printf("Enter last name: ");
    char* lastName;
    scanf("%s", lastName);
    tempHead3->lastName = lastName;
    printf("Enter new age: ");
    int age;
    scanf("%d", &age);
    tempHead3->age=age;
    printf("enter new GPA: ");
    float gpa;
    scanf("%f", &gpa);
    tempHead3->gpa = gpa;
}

void disconnect(char* email1, char* email2){
    struct Connections_struct* tempConnectNode, *nextConnect;
    tempConnectNode = headConnect;
    if(*tempConnectNode->email1 == *email1 && *tempConnectNode->email2 == *email2){
        headConnect = headConnect->next;
    }
    while(tempConnectNode->next!=NULL){

        if(*tempConnectNode->next->email1 == *email1 && *tempConnectNode->next->email2 ==*email2 ){
            break;

        } else {
            tempConnectNode = tempConnectNode->next;
        }
    }

    nextConnect = tempConnectNode->next;
    if(tempConnectNode->next!=NULL){
        if(nextConnect->next!=NULL){
            tempConnectNode->next = nextConnect->next;
        }
        else{
            tempConnectNode->next=NULL;
        }
    }
    headConnect = tempConnectNode;
}

void display(){
    struct Student_struct* tempHead2;
    struct Connections_struct* tempConnectNode;
    tempHead2 = head;
    tempConnectNode = headConnect;
    int connected;
    while (head != NULL){
        char* email = head->email;
        printf("Name: %s %s", head -> firstName);
        printf(" age: %d", head -> age);
        printf(" gpa: %f", head -> gpa);
        printf(" Connected to:");
        if(tempConnectNode!= NULL) {
            if (*tempConnectNode->email1 == *email) {
                connected = 1;
                printf(" %s", tempConnectNode->email2);
            } else if (*tempConnectNode->email2 == *email) {
                connected = 1;
                printf(" %s", tempConnectNode->email1);
            }
            while (tempConnectNode->next != NULL) {

                if (*tempConnectNode->next->email1 == *email) {
                    connected = 1;
                    printf(" %s", tempConnectNode->email2);
                } else if (*tempConnectNode->next->email2 == *email) {
                    connected = 1;
                    printf(" %s", tempConnectNode->email1);
                }

                tempConnectNode = tempConnectNode->next;

            }
        }
        if(connected == 0){
            printf(" nobody");
        }
        head = head->next;
        printf("\n");

    }
    head=tempHead2;
    headConnect=tempConnectNode;
}

void saveNetwork(char* peopleFilename, char* connectionsFilename){
    struct Student_struct* tempHead2;
    struct Connections_struct* tempConnectNode;
    tempHead2 = head;
    tempConnectNode = headConnect;
    FILE* people = fopen( peopleFilename,"w" );
    while (head != NULL){
        fprintf(people,"Name: %s %s, ", head -> firstName, head->lastName);
        head = head -> next;
    }
    head = tempHead2;
    fclose(people);
    FILE* connections = fopen( connectionsFilename,"w" );
    while (headConnect != NULL){
        fprintf(connections,"Email 1: %s Email 2: %s, ", headConnect->email1, headConnect->email2);
        headConnect = headConnect -> next;
    }
    headConnect=tempConnectNode;
    fclose(connections);
}


int main() {
    char decision;
    while(decision != 'q'){
        printf("Press:\na to add\nr to remove\ne to edit\nc to connect\nd to disconnect\ns to save to a file\np to print\nq to quit\n");
        scanf("%c", &decision);
        if (decision == 'a'){
            char* inputEmail = malloc(sizeof(char*));
            printf("Enter email: ");
            scanf("%s", inputEmail);
            add(inputEmail);
        }
        else if(decision =='r'){
            char* inputEmail2 = malloc(sizeof(char*));
            printf("Enter email: ");
            scanf("%s", inputEmail2);
            removeStudent(inputEmail2);
        }
        else if(decision == 'e'){
            char* inputEmail = malloc(sizeof(char*));
            printf("Enter email: ");
            scanf("%s", inputEmail);
            edit(inputEmail);
        }
        else if(decision == 'c'){
            char* inputEmail = malloc(sizeof(char*));
            char* inputEmail2 = malloc(sizeof(char*));
            printf("Enter first email: ");
            scanf("%s", inputEmail);
            printf("Enter second email: ");
            scanf("%s", inputEmail2);
            connect(inputEmail,inputEmail2);
        }
        else if(decision == 'd') {
            char *inputEmail = malloc(sizeof(char *));
            char *inputEmail2 = malloc(sizeof(char *));
            printf("Enter first email: ");
            scanf("%s", inputEmail);
            printf("Enter second email: ");
            scanf("%s", inputEmail2);
            disconnect(inputEmail, inputEmail2);
        }
        else if(decision == 's') {
            char *inputEmail = malloc(sizeof(char *));
            char *inputEmail2 = malloc(sizeof(char *));
            printf("Enter file name for people: ");
            scanf("%s", inputEmail);
            printf("Enter file name for connections: ");
            scanf("%s", inputEmail2);
            saveNetwork(inputEmail, inputEmail2);
        }

       else if (decision == 'p'){
           display();
       }
    }
    return 0;
}