#include "../header.h"

/* check_memory_clist checks if a Classes_list equals NULL
 * if it is NULL the whole program stops because its a sign of no dynamic memory */
void check_memory_clist(Classes_list a) {
    if(!a) { 
        printf("No memory\n");
        exit(0);
    } 
}

/* create_classes_list returns a new Classes_list */ 
Classes_list create_classes_list() {
    Classes_list aux;
    Class useless;

    useless.name = "";
    aux = (Classes_list)malloc(sizeof (Classes_node));
    check_memory_clist(aux);
    if(aux != NULL){
        aux->data = useless;
        aux->next = NULL;
    }
    return aux;
}

/* search_classes_list searches for a Class in the Classes_list 
 *
 * if it finds it curr will be in the position of the searched Class
 * if it doesnt find it curr will be NULL
*/
void search_classes_list(Classes_list head, Class search, Classes_list *prev, Classes_list *curr) {

    *prev = head;
    *curr = head->next;
    while((*curr) != NULL && strcmp((*curr)->data.name, search.name) != 0) {
        *prev = *curr;
        *curr = (*curr)->next;
    }

    if((*curr) != NULL && strcmp((*curr)->data.name, search.name) != 0)
        *curr = NULL;
}

/* removes_from_classes_list removes a Class from the Classes_list */
void removes_from_classes_list(Classes_list head, Class remv) {
    Classes_list prev, curr;

    search_classes_list(head, remv, &prev, &curr);
    if(curr != NULL) {
        prev->next = curr->next;
        free(curr);
    }
}

/* print_classes_list prints the Classes_list head */
void print_classes_list(Classes_list head) {
    Classes_list I = head->next;

    printf("\n\n### LISTA ACTUAL DE DISCIPLINAS ###\n\n");
    while(I){
        printf("\tDisciplina--> %s\n", I->data.name);
        printf("\tDocente--> %s\n", I->data.teacher);
        printf("---------------------------\n");
        I = I->next;
    }
}

/* request_class asks the user which Class in head they wish to use
 *
 * prints head for the user to pick which Class they wish
 * the user writes the name of the Class and its saved on class_name
 *
 * it goes through the list copy(which is a copy of the head list) until they find the same class name
 * 
 * if they dont find it, it prints "Nome de disciplina nao existente. Tente de novo."
 * and it asks the user for another Class
 *
 * when it finds the same Class name it goes to the position of that Class in
 * head list returning head in that position 
*/
void request_class(Classes_list *head) {
    char *class_name = (char *)malloc(CHAR_SIZE * sizeof(char));
    Classes_list copy;
    int n, i;

    check_memory_char(class_name);
    do {
        copy = *head;
        n = 0;
        printf("\t Que disciplina pretende?");
        print_classes_list(copy);
        printf("\t-->");
        fgets(class_name, CHAR_SIZE, stdin);

        while((strcmp(copy->data.name, class_name) != 0) && (copy->next != NULL)) {
            copy = copy->next;
            n++;
        }
        if(strcmp(copy->data.name, class_name) != 0)
            printf("\t\tNome de disciplina nao existente. Tende de novo.\n");
    } while(strcmp(copy->data.name, class_name) != 0);

    for(i = 0; i < n; i++) {
        *head = (*head)->next;
    }
    free(class_name);
}

/* append_class appends to the Classes_list head the new Class */
void append_class(Classes_list head, Class new) {
    Classes_list node;

    node = (Classes_list)malloc(sizeof (Classes_node));
    check_memory_clist(node);
    node->data = new;

    while(head->next != NULL)
        head = head->next;
    head->next = node;
    head = node;
    head->next = NULL;
}
