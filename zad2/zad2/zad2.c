#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Person {
    char name[30];
    char lastName[30];
    int birthYear;
    struct _Person* next;
} Person;

Person* addToBeginning(Person* head, const char* name,
    const char* lastName, int birthYear)
{
    Person* newPerson = malloc(sizeof(Person));

    if (newPerson == NULL)
        return head;

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;

    newPerson->next = head;
    return newPerson;
}

void printList(Person* head)
{
    Person* current = head;

    while (current != NULL) {
        printf("%s %s, %d\n",
            current->name,
            current->lastName,
            current->birthYear);

        current = current->next;
    }
}

Person* addToEnd(Person* head, const char* name,
    const char* lastName, int birthYear)
{
    Person* newPerson = malloc(sizeof(Person));

    if (newPerson == NULL)
        return head;

    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->birthYear = birthYear;
    newPerson->next = NULL;

    if (head == NULL)
        return newPerson;

    Person* current = head;

    while (current->next != NULL)
        current = current->next;

    current->next = newPerson;
    return head;
}

Person* findPerson(Person* head, const char* lastName)
{
    Person* current = head;

    while (current != NULL) {
        if (strcmp(current->lastName, lastName) == 0)
            return current;

        current = current->next;
    }

    return NULL;
}

Person* deletePerson(Person* head, const char* lastName)
{
    Person* current = head;
    Person* previous = NULL;

    while (current != NULL &&
        strcmp(current->lastName, lastName) != 0) {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
        return head;

    if (previous == NULL)
        head = current->next;
    else
        previous->next = current->next;

    free(current);
    return head;
}

int main()
{
    Person* head = NULL;
    Person* found = NULL;

    head = addToBeginning(head, "Ivan", "Ivic", 2000);
    head = addToBeginning(head, "Ana", "Anic", 2002);
    head = addToEnd(head, "Marko", "Markic", 1999);

    printf("Lista osoba:\n");
    printList(head);

    found = findPerson(head, "Ivic");

    if (found != NULL)
        printf("Pronadena osoba: %s %s\n",
            found->name, found->lastName);
    else
        printf("Osoba nije pronadena.\n");

    head = deletePerson(head, "Anic");

    printf("\nLista nakon brisanja:\n");
    printList(head);

    while (head != NULL) {
        Person* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
