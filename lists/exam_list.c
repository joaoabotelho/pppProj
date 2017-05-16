typedef struct date {
    int day;
    int month;
    int year;
} Date;

typedef struct time {
    int hour;
    int minutes;
} Time;

typedef struct classroom {
    char letter;
    int floor;
    int room;
} Classroom;

typedef struct rnode *Classroom_list;
typedef struct rnode {
    Classroom data;
    Classroom_list next;
} Classrooms_node;

typedef struct exam {
    char type[50];
    Class *subject;
    Date date;
    Time time;
    Time duration;
    Time final;
    Student_list students_submited;
    Classroom_list classrooms;
} Exam;

typedef struct enode *Exams_list;
typedef struct enode {
    Exam data;
    Exams_list next;
} Exams_node;

Exams_list create_exams_list() {
    Exams_list aux;
    Exam null;

    aux = (Exams_list) malloc (sizeof (Exams_node));
    if(aux != NULL) {
        aux->data = null;
        aux->next = NULL;
    }
    return aux;
}

Classroom_list create_classroom_list() {
    Classroom_list aux;
    Classroom null;

    aux = (Classroom_list) malloc (sizeof (Classrooms_node));
    if(aux != NULL) {
        aux->data = null;
        aux->next = NULL;
    }
    return aux;
}
void print_classroom_list(Classroom_list head) {
    Classroom_list I = head->next;

    while(I) { 
        printf("Sala--> %c%d.%d\n", I->data.letter, I->data.floor, I->data.room);
        I=I->next;
    }

}

void print_exams_list(Exams_list head) {
    Exams_list I = head->next;

    while(I) {
        printf("\n\n%s\n", I->data.type);
        printf("Nome da Disciplina--> %s\n", I->data.subject->name);
        printf("Docente da Disciplina--> %s\n", I->data.subject->teacher);
        printf("Data do exame--> %d / %d / %d\n", I->data.date.day, I->data.date.month, I->data.date.year);
        printf("Inicio do exame--> %d : %d\n", I->data.time.hour, I->data.time.minutes);
        printf("Fim do exame--> %d : %d\n", I->data.final.hour, I->data.final.minutes);
        print_classroom_list(I->data.classrooms);
        I = I->next;
    }
}

int search_room(Exams_list head, Classroom room) {
    Classroom_list copy;
    int num = 0;

    while(head->next != NULL) {
        head = head->next;
        copy = head->data.classrooms;
        while(copy->next != NULL) {
            copy = copy->next;
            if((copy->data.letter == room.letter) && (copy->data.floor == room.floor) && (copy->data.room == room.room))
                num = 1;
        }   
    }
    return num;
}

void append_exam(Exams_list head, Exam new) {
    Exams_list node;

    node = (Exams_list) malloc (sizeof (Exams_node));
    node->data = new;

    while(head->next != NULL)
        head = head->next;
    head->next = node;
    head = node;
    head->next = NULL;
}

void append_classroom(Classroom_list head, Classroom new) {
    Classroom_list node;

    node = (Classroom_list) malloc (sizeof (Classrooms_node));
    node->data = new;

    while(head->next != NULL)
        head = head->next;
    head->next = node;
    head = node;
    head->next = NULL;
}

int comparehours(Time a,Time b) {

    if ((a.hour == b.hour) && (a.minutes == b.minutes))
        return 0; // "a" = "b"
    else if ((a.hour > b.hour) || ((a.hour == b.hour) && (a.minutes > b.minutes)))
        return -1; // "a" after "b"
    else
        return 1; // "b" after "a"
}

int compare_dates(Date a,Date b) {
    if ((a.day==b.day) && (a.month==b.month) && (a.year==b.year))
        return 0;
    if ((a.year>b.year) || ((a.year==b.year) && (a.month>b.month)) || ((a.year==b.year) && (a.month==b.month) && (a.day>b.day)))
        return -1;
    else
        return 1;
}

void type_of_exam(char str[]) {
    char temp[50];

    printf("1.Epoca Normal\n2.Epoca de Recurso\n3.Epoca Especial\n-->");
    fgets(temp,50,stdin);

    switch(temp[0]) {
        case '1':
            strcpy(str, "Epoca Normal");
            break;
        case '2':
            strcpy(str, "Epoca de Recurso");
            break;
        case '3':
            strcpy(str, "Epoca Especial");
            break;
        default:
            printf("Wrong choice. Enter again.\n");
            type_of_exam(str);
    }
}

void possible_hours(Time time_available[], int n, int hour, int minutes) {
    int i;

    for (i = 0; i < n; i++) {
        time_available[i].hour = hour;
        time_available[i].minutes = minutes;

        if (minutes == 30) {
            hour += 1;
            minutes -= 30;
        } else {
            minutes += 30;
        }
    }
}


