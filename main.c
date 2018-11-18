#include <stdio.h>
#include <stdlib.h>


struct Student_struct {
    char* email;
    int age;
    int gpa;
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
void printEmail();

void add(char* email) {

    struct Student_struct* new = (struct Student_struct*)malloc(sizeof(struct Student_struct));
    new->email = email;
    new->next = head;
    head = new;
}

void removeStudent(char* email){
    struct Student_struct* tempHead;
    struct Connections_struct* tempConnectNode;
    tempHead = head;
    if (head->email == email){
        head=head->next;
        return;
    }
    while(head->next!=NULL){

        if(head->next->email==email){
            printf("if\n");
            break;

        } else {
            head = head->next;
            printf("else\n");
        }
        printEmail();
    }
    if(head->next!=NULL){
        if(head->next->next->next!=NULL){
            head->next=head->next->next->next;
        }
        else{
            head->next=NULL;
        }
        printEmail();
    }
    head=tempHead;




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
    while (tempHead3 -> email != email){
        tempHead3 = tempHead3 -> next;
    }
    if (tempHead3->email == NULL){
        printf("This email is not yet registered");
        return;
    }
    printf("Enter new age");
    int age;
    scanf("%d", &age);
    tempHead3->age=age;
    printf("enter new GPA");
    int gpa;
    scanf("%d", &gpa);
    tempHead3->gpa = gpa;

}

void printEmail(){
    struct Student_struct* tempHead2;
    tempHead2 = head;
    while (head != NULL){
        printf("Email: %s", head -> email);
        printf(" age: %d\n", head -> age);
        head = head -> next;
    }
    head=tempHead2;

}

int main() {
    char decision;
    while(decision != 'q'){
        printf("Press:\na to add\nr to remove\ne to edit\nc to connect\nq to quit\n");
        scanf("%c", &decision);
        if (decision == 'a'){
            char* inputEmail = malloc(sizeof(char*));
            printf("Enter email: ");
            scanf("%s", inputEmail);
            add(inputEmail);
        }
        else if(decision =='r'){
            char* inputEmail = malloc(sizeof(char*));
            printf("Enter email: ");
            scanf("%s", inputEmail);
            removeStudent(inputEmail);
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
        else if(decision == 'p'){printEmail();}
    }
    printEmail();
    return 0;
}