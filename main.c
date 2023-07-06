#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pila.h>

typedef struct 
{
    int registration;
    char nameSurname[40];
    int old;
    int year;
}stStudents;

void chargeFileByEnd();
void printFile();

void chargeStudentsInFile();
void chargeOneStudent();
void printFileStudents();
void printOneStudent(stStudents student);
void printStudentsInRangeYears(int min, int max);
void searchStudentsOlder();
void arrayToFile(stStudents students[], int dimension, int year);
void printArrayStudent(stStudents students[], int validateArrayStudent);
void reverseFile();
void modifyStudent(int registrationStudent);

int fileToArray(stStudents students[], int dimension);
int chargeArrayStudents(stStudents students[], int dimension);
int filterYearsCareerStudent(int yearsCareer);
int weightFile();
int countStudentsByParameter(int yearsOld);


int main (){

    int dimension = 40, validateArrayStudents, yearsOld, ageMin, ageMax, yearsCareer, idRegistration;
    stStudents students[dimension]; 
    char option;

    do
    {
        system("cls");
        printf("1 - Cargar archivo de alumnos.\n");
        printf("2 - Mostrar el archivo de alumnos.\n");
        printf("3 - Contar la cantidad de registros del archivo.\n");
        printf("4 - Contar la cantidad de alumnos mayores a una edad determinada.\n");
        printf("5 - Mostrar los alumnos en rango de edad.\n");
        printf("6 - Mostrar el alumno mas longevo.\n");
        printf("7 - Filtrar alumnos por cantidad de anos cursados.\n");
        printf("8 - Pasar desde el archivo a un arreglo.\n");
        printf("9 - Modificar los datos de un estudiante.\n");
        printf("0 - Invertir archivo.\n");
        option = getch();
        system("cls");
        switch (option)
        {
        case '1':
            system("cls");
            chargeStudents();
            system("pause");
            break;
        case '2':
            system("cls");
            printFileStudents();
            system("pause");
            break;
        case '3':
            system("cls");
            printf("La cantidad de registros que posee el archivo es: %d.\n\n", weightFile()-1);
            system("pause");
            break;
        case '4':
            system("cls");
            printf("Ingrese la edad determinada: ");
            scanf("%d",&yearsOld);
            printf("\nLa cantidad de alumnos que pasan los %d anos es: %d\n\n", yearsOld,countStudentsByParameter(yearsOld));
            system("pause");
            break;
        case '5':
            system("cls");
            printf("Ingrese la edad minima: ");
            scanf("%d",&ageMin);
            printf("Ingrese la edad maxima: ");
            scanf("%d",&ageMax);
            printf("\n\n");
            printStudentsInRangeYears(ageMin,ageMax);
            system("pause");
            break;
        case '6':
            system("cls");
            searchStudentsOlder();
            system("pause");
            break;
        case '7':
            system("cls");
            printf("Ingrese la cantidad de anos cursados para filtrar los alumnos: ");
            scanf("%d",&yearsCareer);
            printf("La cantidad de alumnos que cursan el %d ano son: %d.\n\n", yearsCareer, filterYearsCareerStudent(yearsCareer));
            system("pause");
            break;
        case '8':
            system("cls");
            validateArrayStudents = fileToArray(students, dimension);
            printArrayStudent(students,validateArrayStudents);
            system("pause");
            break;
        case '9':
            printf("Ingrese el numero de legajo del estudiante: ");
            scanf("%d",&idRegistration);
            modifyStudent(idRegistration);
            system("pause");
            break;
        case '0':
            system("cls");
            reverseFile();
            system("pause");
            break;
        default:
            break;
        }
    } while (option != 27);

    return 0;
}

/*              FUNCIONES QUE USAN LO BASICO DE ARCHIVOS TANTO CARGA COMO LECTURA!
void chargeFileByEnd(){
    FILE * file; char phrase[100]; int i=0;
    
    file = fopen ("datos.txt", "a");

    if (file != NULL){
            printf("\nIngrese la frase a ser ingresada: ");
            fflush(stdin);
            gets(phrase);
            fwrite(phrase, sizeof(char[strlen(phrase)]), 1, file);
    }

    fclose(file);
}

void printFile(){

    FILE * file; char phrase[100]; int i =0;

    file = fopen("datos.txt", "r");

    if(file != NULL){
        while (fread(&phrase[i], sizeof(char), 1, file)>0)
        {
            printf("%c", phrase[i]);
            i++;
        }
    }
    printf("\nCantidad de caracteres que contiene el archivo: %d", strlen(phrase));
    fclose(file);
}*/

/*Crear una función que cargue un archivo de alumnos. Abrirlo de manera tal de verificar si el
archivo ya está creado previamente. Cerrarlo dentro de la
función*/
void chargeStudents(){

    int i = 0; char option;
    while(option != 27){
        chargeOneStudent();
        printf("Desea continuar? Esc para salir");
        option = getch();
        i++;
    }

}

void chargeOneStudent(){
    FILE * file; stStudents student;

    file = fopen("students.bin", "ab"); //char[]="student"

    if(file != NULL){
        printf("\nIngrese legajo del alumno: ");
        scanf("%d", &student.registration);
        printf("Ingrese nombre y apellido del alumno: ");
        fflush(stdin);
        gets(student.nameSurname);
        printf("Ingrese la edad del alumno: ");
        scanf("%d", &student.old);
        printf("Ingrese la cantidad de anios cursados: ");
        scanf("%d", &student.year);
        fwrite(&student, sizeof(stStudents), 1, file);
    } else 
        printf("\nOcurrio un problema en el programa!");
    fclose(file);
}

/*Crear una función que muestre por pantalla los registros de un archivo de alumnos.
Modularizar.*/
void printFileStudents(){

    FILE * file; stStudents student;

    file = fopen("students.bin", "rb");
    if (file != NULL){
        while(fread(&student, sizeof(stStudents),1, file)>0){
            printOneStudent(student);
        }
    } else 
        printf("\nOcurrio un error en el programa!\n");
}

void printOneStudent(stStudents student){

    printf("Legajo: %d\n", student.registration);
    printf("Nombre y Apellido: %s\n", student.nameSurname);
    printf("Edad: %d\n", student.old);
    printf("Anios cursada: %d\n", student.year);
    printf("\n");
}


/*Dado un archivo de alumnos, hacer una función que cuente la cantidad de alumnos
mayores a edad específica que se envía por parámetro.*/
int countStudentsByParameter(int yearsOld){

    FILE * file; int count = 0; stStudents student;

    file = fopen("students.bin", "rb");

    if (file != NULL){
        while (fread(&student, sizeof(stStudents), 1, file)){
            if (student.old >= yearsOld)
                count++;
        }
    }

    fclose(file);
    return count;
}

/*Dado un archivo de alumnos, mostrar por pantalla el nombre de todos los alumnos entre un
rango de edades específico (por ejemplo, entre 17 y 25 años). Dicho rango debe recibirse
por parámetro. Modularizar*/
void printStudentsInRangeYears(int min, int max){

    FILE * file; stStudents student;

    file = fopen("students.bin", "rb");

    if(file != NULL){
        while (fread(&student, sizeof(stStudents), 1, file)){
            if(student.old >= min && student.old <= max)
                printOneStudent(student);
        }
    }

    fclose(file);
}

/*Dado un archivo de alumnos, mostrar los datos del alumno de mayor edad. Modularizar.*/
void searchStudentsOlder(){

    stStudents student, studentMaxYearsOld; FILE * file;

    studentMaxYearsOld.year = 0;

    file = fopen("students.bin", "rb");

    if (file != NULL){
        while (fread(&student, sizeof(stStudents), 1, file)){
            if (student.old > studentMaxYearsOld.old)
                studentMaxYearsOld = student;
        }
        
    }

    printOneStudent(studentMaxYearsOld);

    fclose(file);
}

int fileToArray(stStudents students[], int dimension){
    FILE * file; int i = 0;

    file = fopen("students.bin", "rb");

    if (file != NULL){
        while(fread(&students[i], sizeof(stStudents), 1, file) > 0 && i < dimension){
            i++;
        }
        fclose(file);
    }
    return i;
}

/*Crear una función que retorne la cantidad de registros que tiene el archivo. Usar fseek y
ftell. Puede pensar la función para uso genérico, que sirva para averiguar la cantidad de
registros de cualquier archivo.*/
int weightFile(){

    FILE * file = fopen("students.bin", "rb"); int weight;

    if (file != NULL){
        fseek(file, sizeof(stStudents), SEEK_END);
        weight = ftell(file) / sizeof(stStudents);
        fclose(file);
    }

    return weight;
}

int chargeArrayStudents(stStudents students[], int dimension){

    int validate, i=0;

    printf("\nIngrese la cantidad de alumnos a cargar");
    scanf("%d", &validate);
    
    while (i < validate && i < dimension){
        printf("\nIngrese legajo del alumno: ");
        scanf("%d", &students[i].registration);
        printf("\nIngrese apellido y nombre del alumno: ");
        fflush(stdin);
        gets(students[i].nameSurname);
        printf("\nIngrese edad del alumno: ");
        scanf("%d", &students[i].old);
        printf("\nIngrese el ano que esta cursando: ");
        scanf("%d", &students[i].year);   
        printOneStudent(students[i]);
        i++;
    }
    
    return validate;

}

/*Crear una función que retorne la cantidad de alumnos que cursan un determinado año. El
año buscado se pasa por parámetro.*/
int filterYearsCareerStudent(int yearsCareer){

    FILE * file = fopen("students.bin", "rb"); int count=0; stStudents student;

    if (file!=NULL){
        while(fread(&student, sizeof(stStudents),1, file)){
            if (student.year == yearsCareer)
                count++;
        }
        fclose(file);
    } else 
        printf("No se pudo abrir el archivo!\n");

    return count;

}

void printArrayStudent(stStudents students[], int validateArrayStudent){

    for (int i=0; i<validateArrayStudent; i++){
        printOneStudent(students[i]);
    }

}


/*Realice una (o varias) funciones que permitan modificar un registro existente en el archivo
de alumnos. La misma debe permitir modificar uno o todos los campos de la estructura y
sobreescribir el registro existente en el archivo.*/
void modifyStudent(int registrationStudent){

    stStudents student; FILE * file = fopen("students.bin", "r+b"); char option;

    
    if (registrationStudent < weightFile() && file!=NULL){
        fseek(file, sizeof(stStudents)*(registrationStudent-1), SEEK_SET);
        fread(&student,sizeof(stStudents),1,file);
        do{
            system("cls");
            printf("1 - Modificar Nombre y apellido.\n");
            printf("2 - Modificar Edad.\n");
            printf("3 - Modificar los anos cursados.\n");
            option = getch();
            switch (option)
            {
            case '1':
                printf("Ingrese nombre y apellido: ");
                fflush(stdin);
                gets(student.nameSurname);
                break;
            case '2':
                scanf("%d", &student.old);
                break;
            case '3':
                scanf("%d", &student.year); 
                break;
            default:
                break;
            }
        } while(option!=27);

        fseek(file,(-1) * sizeof(stStudents),SEEK_CUR);
        fwrite(&student,sizeof(stStudents),1,file);
        fclose(file);
    }
}

/*Crear una función que reciba como parámetro un arreglo de tipo alumno y lo copie en el
archivo. Asimismo, realice otra función que pase los elementos del archivo a un arreglo de
alumnos, filtrando los estudiantes de un año en particular.*/
void arrayToFile(stStudents students[], int dimension, int year){
    FILE * file; int i = 0; stStudents aux;

    file = fopen("students.bin","wb");
    if (file != NULL){
        for (i; i < dimension; i++)
        {
            if (students[i].year == year)
                fwrite(&students[i], sizeof(stStudents), 1,file);
        }
        
    } else
        printf("ERROR");
    
    fclose(file);
}

/*Dado un archivo de alumnos, hacer una función que invierta los elementos del mismo. No
se puede usar otro archivo auxiliar ni un arreglo auxiliar. Debe trabajar sobre el archivo.
Puede utilizar variables de tipo alumno auxiliares.*/
void reverseFile(){

    FILE * fileBegin = fopen("students.bin", "r+b"), * fileEnd = fopen("students.bin", "r+b"); stStudents studentBegin, studentEnd; 
    int i=-1, j=0;
    if (fileBegin!=NULL && fileEnd!=NULL){
        fseek(fileBegin,(j)*sizeof(stStudents),SEEK_SET);
        fseek(fileEnd,(i)* sizeof(stStudents),SEEK_END);
        fread(&studentBegin,sizeof(stStudents),1,fileBegin);
        fread(&studentEnd,sizeof(stStudents),1,fileEnd);
        while (studentBegin.registration != studentEnd.registration){
            
            fseek(fileBegin,(j)*sizeof(stStudents),SEEK_SET);
            fseek(fileEnd,(i)* sizeof(stStudents),SEEK_END);
            fwrite(&studentBegin,sizeof(stStudents),1,fileEnd);
            fwrite(&studentEnd,sizeof(stStudents),1,fileBegin);
            j++;
            i--;
            fseek(fileBegin,(j)*sizeof(stStudents),SEEK_SET);
            fseek(fileEnd,(i)* sizeof(stStudents),SEEK_END);
            fread(&studentBegin,sizeof(stStudents),1,fileBegin);
            fread(&studentEnd,sizeof(stStudents),1,fileEnd);
        }
    fclose(fileBegin);
    fclose(fileEnd);
    }

}


