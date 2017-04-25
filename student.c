#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "base.c"

typedef struct student{
    int numb;
    char course[50];
    int year;
    char regime[50];
} Student;

typedef struct node *Student_list;
typedef struct node{
    Student data;
    Student_list next;
} Student_list_node;

Student new_student(){
    Student new;
    char temp[50];

    printf("### Esta a criar um novo aluno ###\n\n");
    printf("Qual e o numero de aluno?\n-->");
    fgets(temp,50,stdin);
    new.numb = fgets_to_int(temp); 

    printf("Que curso frequenta?\n-->");
    fgets(new.course,50,stdin);
        
    printf("Que ano frequenta?(1,2,3)\n-->");
    fgets(temp,50,stdin);
    new.year = fgets_to_int(temp);

    printf("Qual o seu regime?\n-->");
    fgets(new.regime,50,stdin);
    return new;
}

Student_list create_students_list(){
    Student_list aux;
    aux = (Student_list) malloc (sizeof (Student_list_node));
    if(aux != NULL){
        aux->data.numb = 0;
        aux->data.year = 0;
        aux->next = NULL;
    }
    return aux;
}

void append_student(Student_list list, Student new){
    Student_list node;
    node = (Student_list) malloc (sizeof (Student_list_node));
    node->data = new;
    while(list->next != NULL)
        list = list->next;
    list->next = node;
    list = node;
    list->next = NULL;
}
     
void print_student_list(Student_list list){
    Student_list I = list->next;
    printf("### LISTA ACTUAL DE ALUNOS ###");
    while(I){
        printf("Num de estudante--> %d\n", I->data.numb);
        printf("Curso do estudant--> %s\n", I->data.course);
        printf("Ano do estudante--> %d\n", I->data.year);
        printf("Regime do estudant--> %s\n\n", I->data.regime);
        I = I->next;
    }
}

/* WITH BUGGS
char* check_answer(){
    char *answer;
    printf("Pretende alterar(y/n)? ");
    scanf("%c", &answer);
    return answer;
} 

void change_data(Student std){
    char answer;
    printf("### Esta a querer alterar os dados de um aluno ###\n\n");
    // Numb
    printf("Este e o numero do aluno --> %d\n", std.numb);
    answer = check_answer();
    if(answer == 'y'){
        printf("O novo numero do aluno e\n-->");
        scanf("%d", &std.numb);
    }
    // Course
    printf("Este e o curso do aluno --> %s\n", std.course);
    answer = check_answer();
    if(answer == 'y'){
        printf("O novo curso do aluno e\n-->");
        scanf("%s", std.course);
    }
    // Year
    printf("O aluno esta neste ano --> %d\n", std.year);
    answer = check_answer();
    if(answer == 'y'){
        printf("O novo ano do aluno e\n-->");
        scanf("%d", &std.year);
    }
    // Regime 
    printf("Este e o regime do aluno --> %s\n", std.regime);
    answer = check_answer();
    if(answer == 'y'){
        printf("O novo regime do aluno e\n-->");
        scanf("%s", std.regime);
    }
}*/
