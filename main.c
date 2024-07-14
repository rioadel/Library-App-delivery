#include "main.h"

void main(void)
{
	u8 choice,counter = 0;
	library_t *LibraryAddress = NULL;
	CreateLibrary(&LibraryAddress);
	printf("---------------------------------------------------------------------\n");
	printf("\n------------------Welcome To Library App-----------------------------\n");	
	while(1)
	{
		
		DisplayOptions();
		printf("--> Enter Your Choice : ");
		scanf("%c",&choice);
		fflush(stdin);
		switch(choice)
		{
			case '1' : 
			DisplayAllBooks(LibraryAddress);
			counter = 0;
			break;
			case '2' : 
			Add_Book(LibraryAddress);
			counter = 0;
			break;
			case '3' : 
			RemoveBook(LibraryAddress);
			counter = 0;
			break;
			case '4' : 
			printf("The Availabe Books in Library is : %d \n",LibraryAddress->Size);
			counter = 0;
			break;
			case '5' : 
			printf("GOODBYE, Till We Meet Again :)");
			exit(0);
			break;
			default:
			counter++;
			if(3==counter){
				printf("SORRY!, You've exceeded the maximum number of trials.\n");  
				printf("The App is shutingdown GOODBYE...");
				exit(0);
			}
			else{
				printf("You entered a wrong input, please try again ! ");
			}
			break;
		}
	}
}


