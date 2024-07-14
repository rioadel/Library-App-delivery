#include "Library.h"

void DisplayOptions(void)
{
	printf("\n---------------------------------------------------------------------\n");
	printf("Please,Choose one of the following options:                          \n");
	printf("To view all books               Enter '1'                            \n");
	printf("To add a New book               Enter '2'                            \n");
	printf("To Delete a book                Enter '3'                            \n");
	printf("To view No. of available books  Enter '4'                            \n");
	printf("To Exit the Library App         Enter '5'                            \n");
	printf("---------------------------------------------------------------------\n");
}

ErrorState_t CreateLibrary(library_t **PointerToPointer)
{
	ErrorState_t FunctionState = RET_OK;
	library_t *LibraryPointer = (library_t *)malloc(sizeof(library_t));
	if(NULL != LibraryPointer)
	{
		LibraryPointer->Size = 0;
		LibraryPointer->Head = NULL;
		LibraryPointer->Tail = NULL; 
		*PointerToPointer = LibraryPointer;
	}
	else{
		printf("Error: malloc failed to allocate the library ....:(\n");
		FunctionState = RET_NULL_PTR;
	}
	return FunctionState;
}


ErrorState_t Library_Empty(library_t *Library, LibState_t *LibraryStatus)
{
	ErrorState_t FunctionState = RET_OK;
	if((NULL != Library) && (NULL != LibraryStatus))
	{
		if(0 == Library->Size)
		{
			*LibraryStatus = LIB_EMPTY;
		}
		else{
			*LibraryStatus = LIB_NEMPTY;
		}
	}
	else{
		printf("Error: Library pointer or LibraryStatus pointer or both have NULL Address ...\n");
		FunctionState = RET_NULL_PTR;
	}
	return FunctionState;
}


ErrorState_t GetBookData(book_t *Book)
{
	ErrorState_t FunctionState = RET_OK;
	if(NULL != Book){
		
		printf("-----------------------------------------------------------------\n");
		printf("Please Enter Book Name :  ");
		gets(Book->BookName);
		fflush(stdin);
		
		printf("Please Enter Book Author :  ");
		gets(Book->BookAuthor);
		fflush(stdin);
		
		printf("please Enter The Book Price: ");
		scanf("%d",&(Book->BookPrice));
		fflush(stdin);
		
		printf("The Book has been added succefully :)\n");
		printf("-----------------------------------------------------------------\n");
	}
	else{
		printf("Error: Library pointer has a NULL address ...:(\n");
		FunctionState = RET_NULL_PTR;
	}
	return FunctionState;
};

ErrorState_t Add_Book(library_t *Library)
{
	ErrorState_t FunctionState = RET_OK;
	LibState_t L_State = LIB_NEMPTY;
	if(NULL != Library)
	{
		book_t *BookPtr = (book_t *)malloc(sizeof(book_t));
		if(NULL != BookPtr)
		{
			GetBookData(BookPtr);
			BookPtr->Next = NULL;
			Library_Empty(Library, &L_State);
			if(L_State == LIB_EMPTY)
			{
				Library->Head = BookPtr;
				Library->Tail = BookPtr;
				BookPtr->Previous = NULL;
			}
			else{
				BookPtr->Previous = Library->Tail;
				Library->Tail->Next = BookPtr;
				Library->Tail = BookPtr;
			}
			Library->Size++;
		}
		else{
			printf("Error: malloc failed to Create the Book ... :(\n");
			FunctionState = RET_NOK;
		}
		
	}
	else
	{
		printf("Error: Library pointer has a NULL address ...\n");
		FunctionState = RET_NULL_PTR;
	}
	return FunctionState;
}


ErrorState_t DisplayAllBooks(library_t *library)
{
	ErrorState_t FunctionState = RET_OK;
	LibState_t  library_state= LIB_NEMPTY;
	if(NULL !=library){
		Library_Empty(library,&library_state);
		if(library_state==LIB_EMPTY){
			printf("The library is empty. No books to view ! \n");
			FunctionState=RET_NOK;
		}else{
			
			u32 Counter = 1;
			book_t *BookPtr = library->Head;
			while(BookPtr != NULL){
				printf("---------------------------------\n");
				printf("Book No.%d  is  :  %s                   \n",Counter,BookPtr->BookName);
				printf("Book Author is  :  %s                   \n",BookPtr->BookAuthor);
				printf("Book Price  is  :  %d                   \n",BookPtr->BookPrice);
				printf("---------------------------------\n");
				Counter++;
				BookPtr = BookPtr->Next;
			}
			
			
			
			/*
			// another way to Dispaly Books
			u8 counter = 1;
			book_t *BookPtr = library->Head;
			for(counter = 1; counter <= library->Size;counter++)
			{
				printf("---------------------------------------------------------------------\n");
				printf("Book NO.%d  is: %s\n",counter,BookPtr->BookName);
				printf("Book Author is: %s\n",BookPtr->BookAuthor);
				printf("Book Price  is: %d\n",BookPtr->BookPrice);
				printf("---------------------------------------------------------------------\n");
				BookPtr = BookPtr->Next;
			}*/
			
			
		}
	}else{
		printf("Error : NULL pointer is send\n");
		FunctionState = RET_NULL_PTR;
	}
	return FunctionState;
}

ErrorState_t RemoveBook(library_t *Library)
{
	ErrorState_t FunctionState = RET_OK;
	LibState_t L_State = LIB_NEMPTY;
	book_t *Ptr = NULL;
	if(NULL != Library)
	{
		Library_Empty(Library, &L_State);
		if(L_State == LIB_EMPTY)
		{
			printf("Sorry the library is empty and there is no books to be deleted.....:(\n");
			FunctionState = RET_NOK;
		}
		else{
			u8 BookNumber;
			printf("Please,Enter the book number you want to remove between 1 to %d:  ",Library->Size);
			scanf("%d",&BookNumber);
			fflush(stdin);
			if(Library->Size == 1 && BookNumber == 1)
			{
				free(Library->Head);
				Library->Head = NULL;
				Library->Tail = NULL;
				Library->Size--;
			}
			else{
				if(BookNumber == 1 && BookNumber < Library->Size)
				{
					//Remove the First Book
					Ptr = Library->Head;
					Library->Head = Ptr->Next; 
					free(Ptr);
					Library->Head->Previous = NULL;
					Library->Size--;
				}
				else if(BookNumber > 1  && BookNumber < Library->Size)
				{
					//Remove Book from The Middle
					u8 i ;
					Ptr = Library->Head; 
					for(i = 1;i < BookNumber;i++) 
					{
						Ptr = Ptr->Next;
					}
					book_t *temp = Ptr; 
					Ptr->Next->Previous = Ptr->Previous;  
					Ptr->Previous->Next = Ptr->Next; 
					free(temp);
					Library->Size--;
				}
				else if(BookNumber == Library->Size)
				{
					// Remove the last Book
					Library->Tail = Library->Tail->Previous;
					free(Ptr);
					Library->Tail->Next = NULL;
					Library->Size--;
				}
				else
				{
					//There are No Books at that Number
					printf("This Book NO. is unavailable !!! ....:( \n");
					FunctionState = RET_NOK;
				}
				
			}
		}
	}
	else{
		printf("Error: Library pointer has NULL Address ...\n");
		FunctionState = RET_NULL_PTR;
	}
	return FunctionState;
}