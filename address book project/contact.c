#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <string.h>
#include<ctype.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

extern int check_array[100];
extern int check_count;

void listContacts(AddressBook *addressBook, int sortChoice) 
{
    
    // Sort contacts based on the chosen criteria
    Contact temp;
    Contact temp1;
    Contact temparr[100];

    for(int i=0 ; i<addressBook -> contactCount ; i++)
    {
        temparr[i]= addressBook -> contacts[i];
    }


    switch(sortChoice)
    {
        
        case 1:for(int i=0;i<addressBook -> contactCount -1  ;i++)
        {
            for(int j=0 ; j < addressBook -> contactCount -i - 1 ; j++  )
            {        
                if((strcasecmp(temparr[j].name , temparr[j+1].name)) > 0)
                {
                    temp = temparr[j];
                    temparr[j] = temparr[j+1];
                    temparr[j+1] = temp;
                }
            }
        } 
            break;
        case 2: 

        

        for(int i=0;i<addressBook -> contactCount -1  ;i++)
        {
            for(int j=0 ; j < addressBook -> contactCount -i - 1 ; j++  )
            {        
                if((strcasecmp(temparr[j].phone , temparr[j+1].phone)) > 0)
                {
                    temp = temparr[j];
                    temparr[j] = temparr[j+1];
                    temparr[j+1] = temp;
                }
            }
        }

                break;
        case 3: for(int i=0;i<addressBook -> contactCount -1  ;i++)
        {
            for(int j=0 ; j < addressBook -> contactCount -i - 1 ; j++  )
            {        
                if((strcasecmp(temparr[j].email , temparr[j+1].email)) > 0)
                {
                    temp = temparr[j];
                    temparr[j] = temparr[j+1];
                    temparr[j+1] = temp;
                }
            }
        }
                break;
    }

    printf("\n");
    printf("%-7s%-20s%-15s%-15s\n","Sl no","Name","Phone","Email");
    printf("------------------------------------------------------------------\n");
        for(int i=0;i < addressBook -> contactCount ; i++)
        {
            printf("%-7d%-20s%-15s%-15s\n",i+1,temparr[i].name,temparr[i].phone,temparr[i].email);
        }
    printf("------------------------------------------------------------------\n");

    
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}
int validate_name(char* tempname)
{
     for(int i=0;tempname[i];i++)
        {    
            if(tempname[i] == ' ')
            {
                continue;
            }
            if(!isalpha(tempname[i]))
            {
                printf("Invalid name ! Try again\n" );
               // printf("\n");
                return 0;
            }
                 
        }
        return 1;
}


int validate_phone(char* tempnum,AddressBook *addressBook)
{
    if(strlen(tempnum)!=10)
        {
            printf("THE NUMBER DOESN'T CONTAIN 10 DIGITS!!!\nTRY AGAIN!!\n");
            printf("\n");
            return 0;
        }
    for(int i=0;tempnum[i];i++)
        {    
            
            if(!isdigit(tempnum[i]))
            {
                printf("PHONE NUMBER SHOULD ONLY CONTAIN DIGITS!!!\n");
                printf("\n");
                return 0;
            }
                
        } 
    for(int i=0; i < addressBook->contactCount ;i++)
        {
            if(strcmp(addressBook -> contacts[i].phone,tempnum) == 0)
            {
                printf("NUMBER ALREADY EXISTS !! TRY AGAIN\n");
                printf("\n");
                return 0;
            }
        }   
        
        return 1;
    
}

int validate_mail(char* tempmail,AddressBook *addressBook)
{
        char* ptr;
        char *ptr1;
        if(!(ptr = strchr(tempmail,'@')) || !(ptr1 = strstr(tempmail,".com")))
        {
            printf("ENTER A VALID EMAIL ID!!!\n");
            printf("\n");
            return 0;
        }
        for(int i=0;tempmail[i];i++)
        {    
            
            if((tempmail[i] >64 && tempmail[i]<91 ))
            {
                printf("EMAIL SHOULD ONLY CONTAIN LOWER CASE!!!\n");
                printf("\n");
                return 0;
            }
                
        } 

        if(isalnum(*(--ptr))==0 || isalnum(*(--ptr1))==0)
        {
            printf("INVALID TYPE OF EMAIL!!!\nTRY AGAIN");
            printf("\n");
            return 0;
        }
        for(int i=0; i < addressBook->contactCount ;i++)
        {
            if(strcmp(addressBook -> contacts[i].email,tempmail) == 0)
            {
                  printf("EMAIL ALREADY EXISTS !! TRY AGAIN\n");
                  printf("\n");
                  return 0;
            }
        }    
        return 1;
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    //ENTER NAME:
    char tempname[20];
    int i;
    while(1)
    {
        
        printf("ENTER THE NAME:\n");
            __fpurge(stdin);

        scanf(" %[^\n]",tempname);
        printf("\n");
        
       if(validate_name(tempname))
       {
        strcpy(addressBook -> contacts[addressBook->contactCount].name,tempname);
        break;
       }
       printf("\n");
    }





    //ENTER PHONE NUM:
    char tempnum[20];
    while(1)
    {
        printf("ENTER THE NUMBER:\n");
        __fpurge(stdin);
        scanf(" %[^\n]",tempnum);
        printf("\n");
       if(validate_phone(tempnum,addressBook))
       {
        strcpy(addressBook -> contacts[addressBook->contactCount].phone,tempnum);
        break;
       }
       
            
    }

    
    //ENTER MAIL:
    char tempmail[20];
    while(1)
    {
        printf("ENTER THE EMAIL:\n");
        __fpurge(stdin);
        scanf(" %[^\n]",tempmail);
    
    
        if(validate_mail(tempmail,addressBook))
        {

                    strcpy(addressBook -> contacts[addressBook->contactCount++].email,tempmail);
                    printf("\nContact created successfully !! \n");
                    break;
        }
    }
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int index;  //to get the index of the searched contact (used in edit_contact()),
    int option1;
    printf("\n");
    printf("1)Search by name\n2)Search by phone\n3)Search by email\n");
    printf("Enter your choice:\n");
    __fpurge(stdin);
    scanf("%d",&option1);
    
    //printf("opt1 = %d",option1);

    switch(option1)
    {
        case 1:     char tempname[20];
                    printf("Enter the name to search:\n");
                    scanf(" %[^\n]",tempname);
                    if(validate_name(tempname)==0)
                    {
                        break;
                    }
                    printf("\n");
                    int flag=0;
                    printf("%-7s%-20s%-15s%-15s\n","Sl no","Name","Phone","Email");
                    int i;
                    check_count=0;
                    for(i=0; i < addressBook->contactCount ;i++)
                    {
                         
                        if(strcasestr(addressBook -> contacts[i].name,tempname))
                        {
                            check_array[check_count++]=i; 
                            index = i;
                            flag++;
                            printf("%-7d%-20s%-15s%-15s\n",check_count,addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
    
                        }
                    }  
                    if(check_count==0)
                    {
                        printf("%-7s%-20s%-15s%-15s\n","---","---","---","---");
                        printf("Contact not found!!\n");
                        printf("\n");
                        //printf("index-%d\n",index);
                    }
                    break;



        case 2:     char tempphone[20];
                    printf("Enter the phone to search:\n");
                    __fpurge(stdin);
                    scanf(" %[^\n]",tempphone);
                    if(validate_phone(tempphone,addressBook)==0)
                    {
                        break;
                    }
                    printf("\n");
                    printf("%-7s%-20s%-15s%-15s\n","Sl no","Name","Phone","Email");
                    flag=0;
                    for(i=0; i < addressBook->contactCount ;i++)
                    {
                         
                        if(strcmp(addressBook -> contacts[i].phone,tempphone) == 0)
                        {
                            index = i;
                            flag++;
                            printf("%-7s%-20s%-15s%-15s\n","1",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
                        }
                    }  
                    if(check_count==0)
                    {
                        printf("%-7s%-20s%-15s%-15s\n","---","---","---","---");
                        printf("Contact not found!!\n");
                        printf("\n");
                    }
                    break;
        case 3:     char tempemail[20];
                    printf("Enter the email to search:\n");
                    __fpurge(stdin);
                    scanf(" %[^\n]",tempemail);
                    if(validate_mail(tempemail,addressBook)==0)
                    {
                        break;
                    }
                    printf("\n");
                    printf("%-7s%-20s%-15s%-15s\n","Sl no","Name","Phone","Email");
                    flag=0;
                    for(i=0; i < addressBook->contactCount ;i++)
                    {
                         
                        if(strcmp(addressBook -> contacts[i].email,tempemail) == 0)
                        {
                            index = i;
                            flag++;
                            printf("%-7s%-20s%-15s%-15s\n","1",addressBook -> contacts[i].name,addressBook -> contacts[i].phone,addressBook -> contacts[i].email);
                        }
                    }  
                    if(check_count==0)
                    {
                        printf("%-7s%-20s%-15s%-15s\n","---","---","---","---");
                        printf("\n");
                        printf("Contact not found!!\n");
                        printf("\n");
                    }
                    break;
        default:    printf("Invalid input!!\n");
    }
    return index;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int index;
    printf("Search the contact to be edited:\n");
    index = searchContact(addressBook);

    if(check_count==0)
    {
        return; 
    }
    //printf("iindexx - %d",index);
    printf("\n");
    
    int sl;
    if(check_count>1)
    {
        printf("Enter the Sl no you've to edit:\n");
        __fpurge(stdin);

        scanf("%d",&sl);
        index = check_array[sl-1];
    }

    printf("\n");

    
    //printf("iindexx - %d",index);
    
    /*
    printf("checkcount - %d\n",check_count);
    for(int i=0;i<check_count;i++)
    {
        printf("%d ",check_array[i] );
    }*/
   int option;
   char temp[30];
   printf("1)Edit name\n2)Edit phone\n3)Edit mail\n");
   printf("Enter your choice:\n");
    __fpurge(stdin);
   scanf("%d",&option);

   switch(option)
   {
    case 1:
    while(1)
    {      
           printf("Enter the new name:\n");
            __fpurge(stdin);
           scanf(" %[^\n]",temp);
            if(validate_name(temp))
            {
              strcpy(addressBook->contacts[index].name,temp);
              printf("\nEdit successfull!!\n");
              break;
            }
            else{
                printf("Enter a valid detail !!\n");
                printf("\n");
            }
    }
            
           
           break;
    case 2: 
    while(1)
    {
           printf("Enter the new phone number:\n");
           scanf(" %[^\n]",temp);
           if(validate_phone(temp,addressBook))
           {
            strcpy(addressBook->contacts[index].phone,temp);
            printf("\nEdit successfull!!\n");
            break; 
           }
           else
           {
            printf("Enter a valid detail !!\n");
           }
    }
          
          break;
    case 3:
    while(1)
    {
           printf("Enter the new email:\n");
           scanf(" %[^\n]",temp);
           if(validate_mail(temp,addressBook))
           {
           strcpy(addressBook->contacts[index].email,temp);
           printf("\nEdit successfull!!\n");
           break;
           }
           else{
            printf("Enter a valid detail!!\n");
           }
    }
    
           break;
    default:printf("Invalid input!!!\n");
   }
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    //printf("%d",addressBook->contactCount);
    if(addressBook->contactCount == 1)
    {
        printf("No contacts present !!\n");
        return;
    }
    int index;
    printf("Search the contact to be deleted:\n");
    index = searchContact(addressBook);
    printf("\n");
    char ch;

    int sl;

    if(check_count == 0)
    {
        return;
    }
    if(check_count>1)
    {
        printf("Enter the Sl no you've to delete:\n");
        scanf("%d",&sl);
        index = check_array[sl-1];
    }

    


    while(1)
    {
        printf("Are you sure you want to permenantly delete the contact(y/n):\n");
        scanf(" %c",&ch);
        if(ch == 'n' || ch == 'N')
            return;
        if(ch == 'y' || ch == 'Y' )
            break;
        else
        {
            printf("Invalid input , press y/n\n");
        }        
        printf("\n");
    }
    

    
    
    

    for(int i=index ; i < (addressBook->contactCount) - 1 ; i++)
    {
        addressBook -> contacts[i] = addressBook -> contacts[i+1];
        
    }
    printf("\nContact deleted successfully!!\n");
    addressBook->contactCount-- ; 
}
