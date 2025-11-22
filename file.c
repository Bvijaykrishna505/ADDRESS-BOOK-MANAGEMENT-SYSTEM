#include <stdio.h>
#include <string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr = fopen("contacts.csv", "w");
    if (fptr == NULL) {
        printf("ERROR ❌ : Could not open contacts.csv for writing.\n");
        return;
    }

    for (int i = 0; i < addressBook->contactCount; i++) {
        fprintf(fptr, "%s,%s,%s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fptr);
    printf("INFO: Contacts saved to 📔 contacts.csv\n");
    printf("😊 Have a good day\n");
}

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv", "r");
    if (fptr == NULL) 
    {
        printf("WARNING: ❌ contacts.csv not found. Starting with an empty list.\n");
        addressBook->contactCount = 0;
        return;
    }

    int i = 0;
    while (i < MAX_CONTACTS &&
           fscanf(fptr, "%[^,],%[^,],%[^\n]\n",
                  addressBook->contacts[i].name,
                  addressBook->contacts[i].phone,
                  addressBook->contacts[i].email) == 3) 
    {
        i++;
    }

    addressBook->contactCount = i;
    fclose(fptr);
    printf("INFO: %d contacts loaded from 📒 contacts.csv\n", i);
}
