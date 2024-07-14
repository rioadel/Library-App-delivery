#ifndef LIBRARY_H
#define LIBRARY_H


#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "ERROR_STATE.h"


typedef struct Book{
	u8 BookName[30];
	u8 BookAuthor[20];
	u32 BookPrice;
	struct Book *Next;
	struct Book *Previous;
}book_t;


typedef struct{
	u32 Size;
	book_t *Head;
	book_t *Tail;
}library_t;


typedef enum{
	LIB_EMPTY,
	LIB_NEMPTY
}LibState_t;

void DisplayOptions(void);
ErrorState_t CreateLibrary(library_t **PointerToPointer);
ErrorState_t Library_Empty(library_t *Library, LibState_t *LibraryStatus);
ErrorState_t GetBookData(book_t *Book);
ErrorState_t Add_Book(library_t *Library);
ErrorState_t RemoveBook(library_t *Library);
ErrorState_t DisplayAllBooks(library_t *library);

#endif /* the end of LIBRARY_H */