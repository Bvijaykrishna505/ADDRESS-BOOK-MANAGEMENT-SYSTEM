#include <stdio.h> // Standard I/O library
#include <stdlib.h> // Standard library for memory allocation and exit
#include <string.h> // String handling functions
#include "contact.h" // Custom header for contact structures
#include "file.h"    // Custom header for file operations
//#include "populate.h" // Optional populate module (currently not used)
#include <ctype.h>   // Character type checking functions

// Function to sort contacts alphabetically by name
void sortbyname(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++) // Outer loop for passes
    {
        for(int j=0;j<addressBook->contactCount-1-i;i++) // Inner loop for comparisons
        {
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0) // Compare adjacent names
            {
                Contact temp=addressBook->contacts[j]; // Swap if out of order
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
}

// Function to sort contacts alphabetically by phone number
void sortbyphone(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++) // Outer loop for passes
    {
        for(int j=0;j<addressBook->contactCount-1-i;j++) // Inner loop for comparisons
        {
            if(strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0) // Compare adjacent phone numbers
            {
                Contact temp=addressBook->contacts[j]; // Swap if out of order
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
}

// Function to sort contacts alphabetically by email
void sortbyemail(AddressBook *addressBook)
{
    for(int i=0;i<addressBook->contactCount-1;i++) // Outer loop for passes
    {
        for(int j=0;j<addressBook->contactCount-1-i;i++) // Inner loop for comparisons
        {
            if(strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0) // Compare adjacent emails
            {
                Contact temp=addressBook->contacts[j]; // Swap if out of order
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
}

// Function to list contacts based on sorting criteria
void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    char name[50],phone[20],email[50]; // Temporary buffers for fields
    
    switch(sortCriteria) // Choose sorting option
    {
        case 1: // Sort by name
            sortbyname(addressBook); // Call sort by name
            printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
            printf("+----------------------+-----------------+-------------------------------+\n");
            for(int i=0;i<addressBook->contactCount;i++) // Display all contacts
            {
                printf("%-2d | %-20s | %-15s | %-30s |\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
        case 2: // Sort by phone
            sortbyphone(addressBook); // Call sort by phone
            printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
            printf("+----------------------+-----------------+-------------------------------+\n");
            for(int i=0;i<addressBook->contactCount;i++) // Display all contacts
            {
                printf("%-2d | %-20s | %-15s | %-30s |\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
        case 3: // Sort by email
            sortbyemail(addressBook); // Call sort by email
            printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
            printf("+----------------------+-----------------+-------------------------------+\n");
            for(int i=0;i<addressBook->contactCount;i++) // Display all contacts
            {
                printf("%-2d | %-20s | %-15s | %-30s |\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            }
            break;
    }
}

// Initialize address book and load data from file
void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0; // Set initial contact count to 0
    loadContactsFromFile(addressBook); // Load existing contacts from file
     void sortbyname(AddressBook *addressBook); // Declare sort functions
     void sortbyphone(AddressBook *addressBook);
    void sortbyemail(AddressBook *addressBook);
}

// Save contacts to file and exit program
void saveAndExit(AddressBook *addressBook) 
{
    saveContactsToFile(addressBook); // Save all contacts
    exit(EXIT_SUCCESS); // Terminate program
}

Contact addcontact; // Global contact variable

// Validate if name contains only alphabets, spaces, or '.'
int isvalidname(char *name)
{
    for(int i=0;i<strlen(name);i++)
    {
        if(!isalpha(name[i])&& name[i]!=' '&&name[i]!='.') 
        {
             return 0;
        } 
    }
    return 1;
}

// Validate if digit string is numeric
int isvaliddigit(char *digitphone)
{
    if(!isdigit)
    {
        return 0;
    }
   return 1;
}

// Validate phone number (10 digits)
int isvalidphone(char *phone)
{
    if(strlen(phone)!=10) // Length must be exactly 10
    {
       return 0;
    }
    for(int i=0;i<strlen(phone);i++)
     {
         if(!isdigit(phone[i])) // Must contain only digits
         {
             return 0;
         }
     }
     return 1;
}

// Check if phone number is unique
int isuniquephone(AddressBook *addressBook,char *phone)
{ 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0) // Compare phone numbers
        {
            return 0; // Duplicate found
        }
    }
    return 1; // Phone number is unique
}

// Validate email format
int isvalidemail(char *email)
{
    char *at = strchr(email, '@'); // Find position of '@'
    char *dot = strrchr(email, '.'); // Find last '.'
    
    for(int i=0;email[i];i++)
    {
        char c=email[i];
         if (!( (c >= 'a' && c <= 'z') || c == '@' || c == '.' )) 
        {
        return 0; // Invalid character found
        }
    }
    
    if (at && dot && at < dot && dot > at + 1 && dot[1] != '\0' && strlen(dot) <= 4 ) // Check format rules
    {
        return 1; // Valid email
    }
    return 0; // Invalid email
}

// Check if email is unique
int isuniqueemail(AddressBook *addressBook,char *email)
{
    for(int i=0;i<addressBook->contactCount;i++)
     {
        if(strcmp(addressBook->contacts[i].email,email)==0) // Compare emails
        {
            return 0; // Email already exists
        }
    }
    return 1; // Unique email
}

// Function to create and add a new contact
void createContact(AddressBook *addressBook)                                                                                                                                                                                                                                                                                                                                                                                                                                                            
{
    int count=0;
    if(addressBook->contactCount<MAX_CONTACTS) // Check if there is space
    {
        Contact addcontact; // Local contact structure
        while(1) // Loop until valid name is entered
        {
            printf("Enter the name:");
            scanf(" %[^\n]",addcontact.name);
            if(isvalidname(addcontact.name)) // Check name validity
            {
                break;
            }
            else
            {
                printf("Invalid name.Please enter valid name.\n");
            }
        }
        while(1) // Loop until valid phone is entered
        {
            printf("Enter phone number:");
            scanf(" %[^\n]",addcontact.phone);
            if(isvalidphone(addcontact.phone) && isuniquephone(addressBook,addcontact.phone))
            {
                break;
            }
            else if(!isvalidphone(addcontact.phone))
            {
                printf("Invalid phone number.Please enter valid phone number\n");
            }
            else
            {
                printf("This number is already exists.please enter unique phone number\n");
            }
        }
        while(1) // Loop until valid email is entered
        {
            printf("Enter email:");
            scanf(" %[^\n]",addcontact.email);
            if(isuniqueemail(addressBook,addcontact.email) && isvalidemail(addcontact.email))
            {
               break;
            }
            else if(!isvalidemail(addcontact.email))
            {
                printf("invalid email\n");
            }
            else if(!isuniqueemail(addressBook,addcontact.email))
            {
                printf("This email is already exists.please enter a unique email id\n");
            }
        }
        printf("Contact added successfully\n");
        addressBook->contacts[addressBook->contactCount++]=addcontact; // Add contact to list
    }
    else
    {
        printf("address book is full:\n"); // Notify if full
        return;
    }
}

// Function to search for a contact
void searchContact(AddressBook *addressBook) 
{
    Contact addcontact;
    if(addressBook->contactCount==0) // Check if address book is empty
    {
       printf("No match found");
       return;
    }
   int option;
   printf("Enter the option 1.name 2.phone 3.gmail:\n");
   scanf("%d",&option); // Read user choice
   int found=0,count=0;
   int i;
   int index[100]; // Store indices of matches
   switch(option)
   {
        case 1: // Search by name
            printf("Enter the name:");
            scanf(" %[^\n]",addcontact.name);
            if(isvalidname(addcontact.name))
            {
               printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
               printf("+----------------------+-----------------+-------------------------------+\n");
                 for(i=0;i<addressBook->contactCount;i++)
                {
                    if (strcasestr(addressBook->contacts[i].name, addcontact.name)!=NULL)
                    {
                        index[count] = i;
                        printf("%-2d | %-20s | %-15s | %-30s |\n", count + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        count++;
                        found=1;
                    }
                }
                if(!found)
                {
                     printf("contact not found");
                     return;
                }
            }
            else
            {
               printf("Invalid name.please enter valid name\n");
            }
        
            break;
        case 2: // Search by phone
            char searchphone[60];
            printf("Enter phone number: ");
            scanf(" %[^\n]",searchphone);
            if(isvaliddigit(searchphone))
            {
                for(i=0;i<addressBook->contactCount;i++)
                {
                     if(strcasestr(addressBook->contacts[i].phone,searchphone)!=NULL)
                    {
                          index[count] = i;
                          count++;
                    }
                }
            }
            else
            {
                printf("Invalid phone number.please enter valid phone number");
            }
            if(count==0)
            {
                printf("contact not found\n");
            }
            if(count==1)
            {
                printf("Contact Found\n");
              printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
              printf("+----------------------+-----------------+-------------------------------+\n");
                printf("%-2d. | %-20s | %-15s | %-30s |\n",count,addressBook->contacts[index[0]].name,addressBook->contacts[index[0]].phone,addressBook->contacts[index[0]].email);
            }
            if (count>1)
            {
                printf("Multiple names found :\n");
               printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
               printf("+----------------------+-----------------+-------------------------------+\n");

                for(int j=0;j<count;j++)
                {
                    printf("%-2d | %-20s | %-15s | %-30s |\n", j + 1,addressBook->contacts[index[j]].name,addressBook->contacts[index[j]].phone,addressBook->contacts[index[j]].email);
                }
                printf("Enter s1.no to select :  \n");
                int s;
                scanf("%d",&s);
                printf("You selected %d below is the contact :\n",s);
                if(s>=1&&s<=count)
                {
                    printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
                    printf("+----------------------+-----------------+-------------------------------+\n");

                    printf("%-20s | %-15s | %-30s |\n",addressBook->contacts[index[s-1]].name,addressBook->contacts[index[s-1]].phone,addressBook->contacts[index[s-1]].email);
                }
            }
            break;
        case 3: // Search by email
            int count=0;
            char searchemail[80];
            printf("Enter email: ");
            scanf(" %[^\n]",searchemail);
            if(1) // Always true (email validation can be added)
            {
                for(i=0;i<addressBook->contactCount;i++)
                {
                     if(strcasestr(addressBook->contacts[i].email,searchemail)!=NULL)
                    {
                          index[count] = i;
                          count++;
                    }
                }
            }
            if(count==0)
            {
                printf("contact not found\n");
            }
            if(count==1)
            {
                 printf("Contact Found\n");
              printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
              printf("+----------------------+-----------------+-------------------------------+\n");
                printf("%-2d. | %-20s | %-15s | %-30s |\n",count,addressBook->contacts[index[0]].name,addressBook->contacts[index[0]].phone,addressBook->contacts[index[0]].email);
            }
            if (count>1)
            {
                printf("Multiple names found :\n");
                printf("s.no        Name                       Phoneno             Email.id\n");
                printf("-------------------------------------------------------------------\n");
                for(int j=0;j<count;j++)
                {
                    printf("%d.\t  %s\t               %s             %s\n",j+1,addressBook->contacts[index[j]].name,addressBook->contacts[index[j]].phone,addressBook->contacts[index[j]].email);
                }
                printf("Enter s1.no to select :  \n");
                int s;
                scanf("%d",&s);
                printf("You selected %d below is the contact :\n",s);
                if(s>=1&&s<=count)
                {
                      printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address");
                    printf("+----------------------+-----------------+-------------------------------+\n");

                    printf("%-20s | %-15s | %-30s |\n",addressBook->contacts[index[s-1]].name,addressBook->contacts[index[s-1]].phone,addressBook->contacts[index[s-1]].email);
                }
            }
           break;
        default: // Invalid option
            printf("Invalid option\n");
            return;
    }
}

void editContact(AddressBook *addressBook)
{
    int option,i,j,index[100],count=0,found=0,searchindex; // declare variables
    printf("1.name 2.phone  3.email\n "); // prompt user for edit option
    printf("Enter the option:"); 
    scanf("%d",&option); // read option
    switch(option)
    {
        case 1: // edit by name
            char searchname[50];
            printf("Enter name you want to edit:");
            scanf(" %[^\n]",searchname); // read name input
            
            if(isvalidname(searchname)) // validate entered name
            {
                printf("| %-20s | %-15s | %-30s |\n", "Full Name", "Contact No", "Email Address"); // header
                printf("+----------------------+-----------------+-------------------------------+\n");
                for(i=0;i<addressBook->contactCount;i++) // loop through contacts
                {
                    if (strcasestr(addressBook->contacts[i].name, searchname) != NULL) // match name
                    {
                        index[count] = i; // store index of matched contact
                        printf("%-2d | %-20s | %-15s | %-30s |\n", count + 1,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email); // print matched contact
                        count++;
                        found=1; // mark found
                    }
                }
                if(count==0) // if no match found
                {
                    printf("No contact found by your name\n");
                    return;
                }
                if(count>=1) // if one or multiple matches found
                {
                    printf("select which s.no you want to edit:");
                    scanf("%d",&searchindex); // read which contact to edit
                   
                    printf("1.name\t 2.phone\t 3.email\n");
                    printf("enter what you want to edit\n");
                    scanf("%d",&option); // read edit field option
                    j=index[searchindex-1]; // get contact index
                    if(option==1) // edit name
                    {
                        while(1){
                            char newname[50];
                            printf("Enter new name : ");
                            scanf(" %[^\n]",newname); // read new name
                            if(isvalidname(newname)) // validate new name
                            {
                                strcpy(addressBook->contacts[j].name,newname); // update name
                                printf("name updated succesfully\n");
                                break;
                            }
                            else
                            {
                                printf("invalid name.please enter valid name");
                                continue;
                            }
                        }
                    }
                    else if(option==2) // edit phone
                    {
                        while(1)
                        {
                            char newphone[20];
                            printf("Enter new phone number : ");
                            scanf(" %[^\n]",newphone); // read new phone number
                            if(isvalidphone(newphone)&&isuniquephone(addressBook,newphone)) // validate uniqueness
                            {
                                strcpy(addressBook->contacts[j].phone,newphone); // update phone
                                printf("phone number updated successfully\n");
                                break;
                            }
                            else
                            {
                                printf("invalid phone number please enter valid phone number\n");
                                continue;
                            }
                        }
                    }
                    else if(option==3) // edit email
                    {
                        while(1){
                            char newemail[60];
                            printf("Enter new email:");
                            scanf(" %[^\n]",newemail); // read new email
                            if(isvalidemail(newemail)&&isuniqueemail(addressBook,newemail)) // validate email
                            {
                                strcpy(addressBook->contacts[j].email,newemail); // update email
                                printf("email updated successfully\n");
                                break;
                            }
                            else
                            {
                                printf("invalid email  please enter valid email\n");
                                continue;
                            }
                        }
                    }
                }
            }
            else // if invalid name
            {
                printf("enter valid name\n");
            }
            break;

        case 2: // edit by phone
            char searchphone[30];
            printf("Enter phone number you want to edit:");
            scanf(" %[^\n]",searchphone); // read phone input
           
            if(isvaliddigit(searchphone)) // validate phone
            {
                printf("| %-20s | %-15s | %-30s |\n","Full Name", "Contact No", "Email Address");
                printf("+----------------------+-----------------+-------------------------------+\n");
                for(i=0;i<addressBook->contactCount;i++) // loop contacts
                {
                    if(strstr(addressBook->contacts[i].phone,searchphone)!=NULL) // match phone
                    {
                        index[count]=i; // store index
                        printf("%-2d | %-20s | %-15s | %-30s |\n",count + 1,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email); // display contact
                        count++;
                        found=1;
                    }
                }
                if(count==0) // no match
                {
                    printf("No name found\n");
                    return;
                }
                printf("select which s.no you want to edit:");
                scanf("%d",&searchindex); // read which contact
                printf("enter what you want to edit\n");
                printf("1.Name\t 2.Phone\t 3.Email\n");
                scanf("%d",&option);
                j=index[searchindex-1]; // get contact index
           
                if(option==1) // edit name
                {
                    char newname[50];
                    printf("Enter new name");
                    scanf(" %[^\n]",newname);
                    if(isvalidname(newname))
                    {
                        strcpy(addressBook->contacts[j].name,newname);
                        printf("name updated succesfully\n");
                    }
                    else
                    {
                        printf("invalid name.please enter valid name");
                    }
                }
                else if(option==2) // edit phone
                {
                    char newphone[20];
                    printf("Enter new phone number:");
                    scanf(" %[^\n]",newphone);
                    if(isvalidphone(newphone)&&isuniquephone(addressBook,newphone))
                    {
                        strcpy(addressBook->contacts[j].phone,newphone);
                        printf("phone number updated successfully\n");
                    }
                    else
                    {
                        printf("invalid phone number please enter valid phone number\n");
                    }
                }
                else if(option==3) // edit email
                {
                    char newemail[60];
                    printf("Enter new email:");
                    scanf(" %[^\n]",newemail);
                    if(isvalidemail(newemail)&&isuniqueemail(addressBook,newemail))
                    {
                        strcpy(addressBook->contacts[j].email,newemail);
                        printf("email updated successfully\n");
                    }
                    else
                    {
                        printf("invalid email  please enter valid email\n");
                    }
                }
            }
            else
            {
                printf("invalid name");
            }
            break;

        case 3: // edit by email
            char searchemail[40];
            printf("Enter email you want to edit:");
            scanf(" %[^\n]",searchemail); // read email input
            if(1) // always pass (validation placeholder)
            {
                printf("| %-20s | %-15s | %-30s |\n","Full Name", "Contact No", "Email Address");
                printf("+----------------------+-----------------+-------------------------------+\n");
                for(i=0;i<addressBook->contactCount;i++) // loop contacts
                {
                    if (strstr(addressBook->contacts[i].email, searchemail) != NULL) // match email
                    {
                        index[count] = i; // store match index
                        printf("%d\t%s\t%s\t%s\n",count+1,
                               addressBook->contacts[i].name,
                               addressBook->contacts[i].phone,
                               addressBook->contacts[i].email);
                        count++;
                        found=1;
                    }
                }
                if(!found) // no match
                {
                     printf("Email not found");
                     return;
                }
            }
            char newname[50];
            printf("Select which s.no you want to edit:");
            scanf("%d",&searchindex); // choose index

            printf("Enter what you want to edit:");
            printf("1.name\t 2.phone\t 3.email\n");
            scanf("%d",&option);
            
            j=index[searchindex-1]; // target contact
            if(option==1)
            {
                while(1){
                    printf("Enter new name");
                    scanf(" %[^\n]",newname); // read name
                    if(isvalidname(newname))
                    {
                        strcpy(addressBook->contacts[j].name,newname); // update name
                        printf("name updated succesfully\n");
                        break;
                    }
                    else
                    {
                        printf("invalid name.please enter valid name\n");
                        continue;
                    }
                }
            }
            else if(option==2)
            {
                while(1)
                {
                    char newphone[20];
                    printf("Enter new phone number\n");
                    scanf(" %[^\n]",newphone); // read phone
                    if(isvalidphone(newphone)&&isuniquephone(addressBook,newphone))
                    {
                        strcpy(addressBook->contacts[j].phone,newphone); // update phone
                        printf("phone number updated successfully\n");
                        break;
                    }
                    else
                    {
                        printf("invalid phone number please enter valid phone number\n");
                        continue;
                    }
                }
            }
            else if(option==3)
            {
                while(1)
                {
                    char newemail[60];
                    printf("Enter new email\n");
                    scanf(" %[^\n]",newemail); // read email
                    if(isvalidemail(newemail)&&isuniqueemail(addressBook,newemail))
                    {
                        strcpy(addressBook->contacts[j].email,newemail); // update email
                        printf("email updated successfully\n");
                        break;
                    }
                    else
                    {
                        printf("invalid email -- please enter valid email\n");
                        continue;
                    }
                }
            }  
            break;

        default: // invalid option
            printf("Invalid option:");
            return;
    }
}

void deleteContact(AddressBook *addressBook)
{
    char name[50], phone[30], email[60]; // variables to store name, phone, and email inputs
    int choice, found = 0, i, j, index[100], searchindex, count = 0; // variables for tracking matches
    char del; // variable for delete confirmation (y/n)
    
    printf("Enter your option what you want to delete: 1.name 2.phone 3.email: ");
    scanf("%d", &choice); // read user choice
    
    switch (choice)
    {
        case 1: // delete by name
            printf("Enter name to delete:");
            getchar(); // consume newline character
            scanf("%[^\n]", name); // read full name input
            if (isvalidname(name)) // check if entered name is valid
            {
                printf("| %-20s | %-15s | %-30s |\n","Full Name", "Contact No", "Email Address");
                printf("+----------------------+-----------------+-------------------------------+\n");
                
                for (int i = 0; i < addressBook->contactCount; i++) // loop through contacts
                {
                    if (strcasestr(addressBook->contacts[i].name, name) != NULL) // match name (case-insensitive)
                    {
                        index[count] = i; // store index of matching contact
                        printf("%-2d | %-20s | %-15s | %-30s |\n", count + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        count++;
                        found = 1; // flag as found
                    }
                }
                
                if (count == 1) // if only one match found
                {
                    printf("Do you want to delete the contact(y/n):");
                    getchar();
                    scanf("%c", &del);
                    if (del == 'y' || del == 'Y') // confirm deletion
                    {
                        int i = index[count]; // get index of contact to delete
                        for (int j = i; j < addressBook->contactCount - 1; j++) // shift remaining contacts
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        printf("contact deleted successfully\n");
                        addressBook->contactCount--; // reduce contact count
                        return;
                    }
                }
                if (count >= 2) // if multiple matches found
                {
                    printf("select which index you want to delete:");
                    scanf(" %d", &searchindex); // read index to delete
                    printf("Do you want to delete the contact(y/n):");
                    getchar();
                    scanf("%c", &del);
                    if (del == 'y' || del == 'Y') // confirm deletion
                    {
                        int i = index[searchindex - 1];
                        for (int j = i; j < addressBook->contactCount - 1; j++) // shift contacts
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        printf("contact deleted successfully\n");
                        addressBook->contactCount--; // decrement count
                        return;
                    }
                    else
                    {
                        printf("Contact not deleted");
                    }
                }
                else
                {
                    printf("contact not found\n"); // no match found
                }
            }
            else
            {
                printf("invalid name please enter valid name\n");
                return;
            }
            break;
        
        case 2: // delete by phone
            printf("Enter the phone number to delete:");
            getchar();
            scanf("%[^\n]", phone); // read phone number
            if (isvaliddigit(phone)) // check phone validity
            {
                printf("| %-20s | %-15s | %-30s |\n","Full Name", "Contact No", "Email Address");
                printf("+----------------------+-----------------+-------------------------------+\n");
                
                for (int i = 0; i < addressBook->contactCount; i++) // iterate through contacts
                {
                    if (strstr(addressBook->contacts[i].phone, phone) != NULL) // check if phone matches
                    {
                        index[count] = i; // store matching index
                        printf("%-2d | %-20s | %-15s | %-30s |\n", count + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        count++;
                        found = 1;
                    }
                }
                if (count == 1) // single match
                {
                    printf("Do you want to delete the contact(y/n):");
                    getchar();
                    scanf("%c", &del);
                    if (del == 'y' || del == 'Y') // confirm deletion
                    {
                        int i = index[count];
                        for (int j = i; j < addressBook->contactCount - 1; j++) // shift contacts
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        printf("contact deleted successfully\n");
                        addressBook->contactCount--;
                        return;
                    }
                }
                if (count >= 2) // multiple matches
                {
                    printf("select which index you want to delete:");
                    scanf("%d", &searchindex);
                    printf("Do yo want to delete the contact(y/n):");
                    getchar();
                    scanf("%c", &del);
                    if (del == 'y' || del == 'Y') // confirm deletion
                    {
                        for (int j = i; j < addressBook->contactCount - 1; j++) // shift contacts
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--; // decrement count
                        printf("Contact deleted successfully: ");
                        break;
                    }
                    else
                    {
                        printf("contact not deleted\n");
                    }
                }
                else
                {
                    printf("contact not found\n");
                }
            }
            else
            {
                printf("Invalid phone number please enter valid phone number\n");
                return;
            }
            break;

        case 3: // delete by email
            printf("Enter the email to detete:");
            getchar();
            scanf("%[^\n]", email); // read email input
            if (1) // validation always true (should be updated to actual validation)
            {
                printf("| %-20s | %-15s | %-30s |\n","Full Name", "Contact No", "Email Address");
                printf("+----------------------+-----------------+-------------------------------+\n");
                for (int i = 0; i < addressBook->contactCount; i++) // iterate through contacts
                {
                    if (strstr(addressBook->contacts[i].email, email)) // check if email matches
                    {
                        index[count] = i; // store matching index
                        printf("%-2d | %-20s | %-15s | %-30s |\n", count + 1, addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
                        count++;
                        found = 1;
                    }
                }
                if (count == 1) // single match
                {
                    printf("Do you want to delete the contact(y/n):");
                    getchar();
                    scanf("%c", &del);
                    if (del == 'y' || del == 'Y') // confirm deletion
                    {
                        int i = index[count];
                        for (int j = i; j < addressBook->contactCount - 1; j++) // shift contacts
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        printf("contact deleted successfully\n");
                        addressBook->contactCount--;
                        return;
                    }
                }
                if (count >= 2) // multiple matches
                {
                    printf("select which s.no you want to delete:");
                    scanf(" %d", &searchindex);
                    printf("Do you want to delete the contact(y/n):");
                    getchar();
                    scanf("%c", &del);
                    if (del == 'y'|| del == 'Y') // confirm deletion
                    {
                        for (int j = 0; j < addressBook->contactCount - 1; j++) // shift contacts
                        {
                            addressBook->contacts[j] = addressBook->contacts[j + 1];
                        }
                        addressBook->contactCount--; // decrement count
                        printf("Contact deleted successfully\n");
                        break;
                    }
                    else
                    {
                        printf("contacts not deleted:");
                    }
                }
                else
                {
                    printf("email not found\n");
                }
            }
            else
            {
                printf("Invalid email please enter valid email\n");
                return;
            }
    }
}   // end of deleteContact
