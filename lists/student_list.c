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
} Student_node;

Student_list create_students_list(){
    Student_list aux;
    Student null;

    aux = (Student_list) malloc (sizeof (Student_node));
    if(aux != NULL){
        aux->data = null;
        aux->next = NULL;
    }
    return aux;
}

void search_student_list(Student_list head, int student_numb, Student_list *prev, Student_list *curr) {

    *prev = head;
    *curr = head->next;
    while((*curr) != NULL && (*curr)->data.numb < student_numb) {
        *prev = *curr;
        *curr = (*curr)->next;
    }
    if((*curr) != NULL && (*curr)->data.numb != student_numb)
        *curr = NULL;
}

void removes_from_student_list(Student_list head, int student_numb) {
    Student_list prev, curr;

    search_student_list(head, student_numb, &prev, &curr);
    if(curr != NULL) {
        prev->next = curr->next;
        free(curr);
    }
}

void append_student_wOrder(Student_list head, Student new) {
    Student_list node, prev, useless;

    node = (Student_list) malloc (sizeof (Student_node));
    if(node != NULL) {
        node->data = new;
        search_student_list(head, new.numb, &prev, &useless);
        node->next = prev->next;
        prev->next = node;
    }
}
     
void print_student_list(Student_list head){
    Student_list I = head->next;

    printf("### LISTA ACTUAL DE ALUNOS ###\n\n");
    while(I){
        printf("Num de estudante--> %d\n", I->data.numb);
        printf("Curso do estudant--> %s\n", I->data.course);
        printf("Ano do estudante--> %d\n", I->data.year);
        printf("Regime do estudante--> %s\n", I->data.regime);
        printf("----------------------\n\n");
        I = I->next;
    }
}

void regime(char str[]) {
    char temp[50];

    printf("1.Normal\n2.Trabalhador-estudante\n3.Atleta\n4.Dirigente associativo\n5.Aluno de Erasmus\n-->");
    fgets(temp,50,stdin);
    switch(temp[0]) {
        case '1':
            strcpy(str, "Normal");
            break;
        case '2':
            strcpy(str, "Trabalhador-estudante");
            break;
        case '3':
            strcpy(str, "Atleta");
            break;
        case '4':
            strcpy(str, "Dirigente associativo");
            break;
        case '5':
            strcpy(str, "Aluno de Erasmus");
            break;
        default:
            printf("Escolha errada. Tente de novo.\n");
            regime(str);
    }
}

int size_of_list(Student_list head) {
    int elements = 0;

    while(head->next != NULL) {
        head = head->next;
        elements++;
    }

    return elements;
}

int find_pivot(Student_list head) {
    int pivot, i;
    int half_size = 1 + size_of_list(head)  / 2;
    
    for(i = 0; i < half_size; i++) {
        head = head->next;
    }
    pivot = head->data.numb;

    return pivot;
}

void join_student_list(Student_list first, Student_list last) {
    
    while (first->next != NULL)
        first = first->next;
    first->next = last->next;

}

void delete_student_list(Student_list *head) {
    Student_list curr = *head;
    Student_list after;

    while (curr != NULL)
    {
        after = curr->next;
        free(curr);
        curr = after;
    }
    *head = create_students_list();
}

void quick_sort(Student_list *head) {

    int pivot = find_pivot(*head);
    Student_list smaller = create_students_list();
    Student_list bigger = create_students_list();

    while((*head)->next != NULL) {
        (*head) = (*head)->next;
        if((*head)->data.numb < pivot)
            append_student_wOrder(smaller, (*head)->data);
        else
            append_student_wOrder(bigger, (*head)->data);

    }
    
    join_student_list(smaller, bigger);
}
