#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE* fptr = fopen("address.csv","w");
    //fprintf(fptr,"%s,%s,%s,%s\n","Sl no","Name","Phone","email");

    for(int i=0;i < (addressBook->contactCount) ;i++)
    {
        fprintf(fptr,"%d,%s,%s,%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE* fptr = fopen("address.csv","r");
    //char tname[30];
    //char tphone[30];
    //char temail[30];
    //fseek(fptr,23,SEEK_SET);
    //printf("pos-%lu\n",ftell(fptr));
    while(!feof(fptr))
    {
        fscanf(fptr,"%*d,%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email);
        addressBook->contactCount++;
    }
    fclose(fptr);
}
