#include <stdio.h>
#include "../inc/SDBApp.h"
#include "../inc/SDB.h"


/* -----------------------------------------------
 * SDB_APP
 * Super loop, keeps showing menu until user
 * enters 0 to exit.
 * ----------------------------------------------- */
void SDB_APP(void)
{
    uint8 choice;

    printf("========================================\n");
    printf("   Welcome to Simple Student Database   \n");
    printf("========================================\n");

    do
    {
        printf("\n---------- MAIN MENU ----------\n");
        printf(" 1. Add student entry\n");
        printf(" 2. Get used size\n");
        printf(" 3. Read student data\n");
        printf(" 4. Get list of all student IDs\n");
        printf(" 5. Check if ID exists\n");
        printf(" 6. Delete student data\n");
        printf(" 7. Check if database is full\n");
        printf(" 0. Exit\n");
        printf("-------------------------------\n");
        printf("Enter your choice: ");
        scanf("%hhu", &choice);

        if (choice != 0)
            SDB_action(choice);

    } while (choice != 0);

    printf("\nGoodbye! Exiting the program.\n");
}


/* -----------------------------------------------
 * SDB_action
 * Takes user choice and calls matching function.
 * ----------------------------------------------- */
void SDB_action(uint8 choice)
{
    uint32 inputID;
    uint8  count;
    uint32 idList[MAX_SIZE];
    uint8  i;

    switch (choice)
    {
        case 1:
            SDB_AddEntry();
            break;

        case 2:
            printf("\nStudents currently in database: %d / %d\n",
                   SDB_GetUsedSize(), MAX_SIZE);
            break;

        case 3:
            printf("Enter Student ID to read: ");
            scanf("%u", &inputID);
            SDB_ReadEntry(inputID);
            break;

        case 4:
            SDB_GetList(&count, idList);
            if (count == 0)
                printf("\nDatabase is empty. No IDs to show.\n");
            else
            {
                printf("\nAll Student IDs (%d total):\n", count);
                for (i = 0; i < count; i++)
                    printf("  [%d] ID: %u\n", i + 1, idList[i]);
            }
            break;

        case 5:
            printf("Enter Student ID to check: ");
            scanf("%u", &inputID);
            if (SDB_IsIdExist(inputID))
                printf("[FOUND] Student ID %u exists in the database.\n", inputID);
            else
                printf("[NOT FOUND] Student ID %u does not exist.\n", inputID);
            break;

        case 6:
            printf("Enter Student ID to delete: ");
            scanf("%u", &inputID);
            SDB_DeleteEntry(inputID);
            break;

        case 7:
            if (SDB_IsFull())
                printf("\nDatabase is FULL (%d/%d students).\n",
                       SDB_GetUsedSize(), MAX_SIZE);
            else
                printf("\nDatabase is NOT full (%d/%d students used).\n",
                       SDB_GetUsedSize(), MAX_SIZE);
            break;

        default:
            printf("[WARNING] Invalid choice. Please enter a number from 0 to 7.\n");
            break;
    }
}
