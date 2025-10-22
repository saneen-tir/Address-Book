#include <stdio.h>
#include <stdio_ext.h>
#include "contact.h"

int check_array[100];//used in search contact to get index of contacts with same name
int check_count = 0;

int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    //printf("i value - %d\n",addressBook.contactCount);// value is 10 after adding dummy contacts.

    do {
        
        printf("================================================\n");
        printf("                 ADDRESS BOOK                   \n");
         printf("================================================\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("================================================\n");
        //printf("------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("================================================\n");
        if(choice == 7)
        {
            printf("Exiting . . . \nThank you!!\n");
            return 1;
        }

        printf("\n");
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5: 
                int sortChoice;
                printf("Sort by:\n1.Name\n2.Phone\n3.Email:\n");
                printf("Enter your choice : ");
                scanf("%d",&sortChoice);         
                listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice);
    
       return 0;
}
