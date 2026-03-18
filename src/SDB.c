#include <stdio.h>
#include "../inc/SDB.h"


static student database[MAX_SIZE];
static uint8   usedSize = 0;


bool SDB_IsFull(void)
{
    if (usedSize >= MAX_SIZE)
        return true;
    else
        return false;
}


uint8 SDB_GetUsedSize(void)
{
    return usedSize;
}



bool SDB_IsIdExist(uint32 id)
{
    uint8 i;
    for (i = 0; i < usedSize; i++)
    {
        if (database[i].Student_ID == id)
            return true;
    }
    return false;
}


bool SDB_AddEntry(void)
{
    student newStudent;
    uint32  tempID;

    if (SDB_IsFull())
    {
        printf("\n[ERROR] Database is full! Cannot add more students.\n");
        return false;
    }

    printf("\n--- Add New Student ---\n");

    printf("Enter Student ID      : ");
    scanf("%u", &tempID);

    if (SDB_IsIdExist(tempID))
    {
        printf("[ERROR] Student ID %u already exists!\n", tempID);
        return false;
    }
    newStudent.Student_ID = tempID;

    printf("Enter Student Year    : ");
    scanf("%u", &newStudent.Student_year);

    printf("Enter Course 1 ID     : ");
    scanf("%u", &newStudent.Course1_ID);
    printf("Enter Course 1 Grade  : ");
    scanf("%u", &newStudent.Course1_grade);

    printf("Enter Course 2 ID     : ");
    scanf("%u", &newStudent.Course2_ID);
    printf("Enter Course 2 Grade  : ");
    scanf("%u", &newStudent.Course2_grade);

    printf("Enter Course 3 ID     : ");
    scanf("%u", &newStudent.Course3_ID);
    printf("Enter Course 3 Grade  : ");
    scanf("%u", &newStudent.Course3_grade);

    database[usedSize] = newStudent;
    usedSize++;

    printf("[SUCCESS] Student added successfully! (Total: %d)\n", usedSize);
    return true;
}



bool SDB_ReadEntry(uint32 id)
{
    uint8 i;
    for (i = 0; i < usedSize; i++)
    {
        if (database[i].Student_ID == id)
        {
            printf("\n===== Student Record =====\n");
            printf("Student ID     : %u\n", database[i].Student_ID);
            printf("Student Year   : %u\n", database[i].Student_year);
            printf("Course 1 ID    : %u  |  Grade: %u\n", database[i].Course1_ID, database[i].Course1_grade);
            printf("Course 2 ID    : %u  |  Grade: %u\n", database[i].Course2_ID, database[i].Course2_grade);
            printf("Course 3 ID    : %u  |  Grade: %u\n", database[i].Course3_ID, database[i].Course3_grade);
            printf("==========================\n");
            return true;
        }
    }
    printf("[ERROR] Student ID %u not found.\n", id);
    return false;
}



void SDB_DeleteEntry(uint32 id)
{
    uint8 i;
    uint8 foundIndex = MAX_SIZE;

    for (i = 0; i < usedSize; i++)
    {
        if (database[i].Student_ID == id)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == MAX_SIZE)
    {
        printf("[ERROR] Student ID %u not found.\n", id);
        return;
    }

    for (i = foundIndex; i < usedSize - 1; i++)
        database[i] = database[i + 1];

    usedSize--;
    printf("[SUCCESS] Student ID %u deleted. (Remaining: %d)\n", id, usedSize);
}



void SDB_GetList(uint8 *count, uint32 *list)
{
    uint8 i;
    *count = usedSize;
    for (i = 0; i < usedSize; i++)
        list[i] = database[i].Student_ID;
}
