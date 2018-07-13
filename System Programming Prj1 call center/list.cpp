///*
// * To change this license header, choose License Headers in Project Properties.
// * To change this template file, choose Tools | Templates
// * and open the template in the editor.
// */
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define BUFSZ 256
//#define TOKENS 4
//
///* Seperator. */
//
//const char *seperator = ",";
//
//typedef struct _Book {
//    int BookId;
//    char BookName[51];
//    char BookWriter[51];
//    int YearPublished;
//    /* Pointer to next and previous node. */
//    struct _Book *next;
//    struct _Book *previous;
//} Book;
//
//typedef struct _BookList {
//    Book *head;
//    Book *tail;
//    int BookListSz;
//} BookList;
//#pragma hdrstop
//
////---------------------------------------------------------------------------
//
///* Functions. */
//
///* Error Reporter. */
//void _perror(const char *Msg) {
//    printf("Error: %s\n", Msg);
//}
//
///* Create A Book Node. */
//Book *CreateBook(int BkId, char *BkName, char *BkWriter, int YrPub) {
//    Book *b = NULL;
//    if ((b = malloc(sizeof (Book))) == NULL) {
//        _perror("Book Creation.");
//        return NULL;
//    } else {
//        /* Init. */
//        b->BookId = BkId;
//        strcpy(b->BookName, BkName);
//        strcpy(b->BookWriter, BkWriter);
//        b->YearPublished = YrPub;
//        /* NULL. */
//        b->next = NULL;
//        b->previous = NULL;
//        /* Return. */
//        return b;
//    }
//}
//
///* Create A Book List. */
//BookList *CreateBookList(const int nrLists) {
//    /* List. */
//    BookList *bl = NULL;
//    if ((bl = calloc(nrLists, sizeof (BookList))) == NULL) {
//        _perror("List Creation.");
//        return NULL;
//    } else {
//        /* Init. */
//        bl->head = NULL;
//        bl->tail = NULL;
//        bl->BookListSz = 0;
//
//        /* Return the list. */
//        return bl;
//    }
//}
//
//int insertBookIntoBookList(BookList *List, Book *element, int BkId, char *BkName, char *BkWriter, int YrPub) {
//    /* Our Book to Add. */
//    Book *nPtrBook = NULL;
//
//    if (element == NULL && List->BookListSz != 0) {
//        _perror("Invalid Insertion.");
//        return -1;
//    }
//    /* Create the Book. */
//    nPtrBook = CreateBook(BkId, BkName, BkWriter, YrPub);
//
//    /* Case Empty List. */
//    if (!List->BookListSz) {
//        List->head = nPtrBook;
//        List->head->next = NULL;
//        List->head->previous = NULL;
//        List->tail = nPtrBook;
//    } else {
//        nPtrBook->next = element->next;
//        nPtrBook->previous = element;
//        if (element->next == NULL)
//            List->tail = nPtrBook;
//        else
//            element->next->previous = nPtrBook;
//        element->next = nPtrBook;
//    }
//    /* Advance Size. */
//    List->BookListSz++;
//    /* Return. */
//    return 0;
//}
//
///* Get a Line From Input File and seperate it. */
//int GetLineFromFile(const char *filename, int *Cnt, Book **ptrLine) {
//    if (!filename) {
//        _perror("Invalid File Name.");
//        return -1;
//    } else {
//        FILE *fileptr = NULL;
//        if ((fileptr = fopen(filename, "rt")) == NULL) {
//            _perror("Open File.");
//            return -2;
//        } else {
//            /* Basic Variables. */
//            char *tokenPtr = NULL;
//            char *TBuffer = NULL;
//            Book *Lineptr = NULL;
//            /* Case Status. */
//            int nCase = 0, jDx = 0;
//            /* Error Checking. */
//            static int nError = 0;
//            /* Get Memory. */
//            if ((TBuffer = calloc(BUFSZ, sizeof (char))) == NULL) {
//                _perror("Memory Fault.");
//                /* Close File. */
//                fclose(fileptr);
//                return -3;
//            }
//            if ((Lineptr = malloc(sizeof (Book))) == NULL) {
//                _perror("Memory Fault.");
//                /* Free memory. */
//                free(TBuffer);
//                fclose(fileptr);
//                return -4;
//            } else {
//                while (fgets(TBuffer, BUFSZ, fileptr) != NULL) {
//                    if (TBuffer[strlen(TBuffer) - 1] == '\n')
//                        TBuffer[strlen(TBuffer) - 1] = '\0';
//
//                    tokenPtr = strtok(TBuffer, seperator);
//                    if (!tokenPtr) {
//                        nError = 1;
//                        _perror("Invalid Text Line Type.");
//                        break;
//                    } else {
//                        while (tokenPtr && nCase < TOKENS) {
//                            switch (nCase) {
//                                case 0:
//                                    sscanf(tokenPtr, "%d", &Lineptr[jDx].BookId);
//                                    break;
//                                case 1:
//                                    strcpy(Lineptr[jDx].BookName, tokenPtr);
//                                    break;
//                                case 2:
//                                    strcpy(Lineptr[jDx].BookWriter, tokenPtr);
//                                    break;
//                                case 3:
//                                    sscanf(tokenPtr, "%d", &Lineptr[jDx].YearPublished);
//                                    break;
//                                default:
//                                    break;
//                            }
//                            tokenPtr = strtok(NULL, seperator);
//                            /* Advance Case Status. */
//                            nCase++;
//                        }
//                    }
//                    /* Advance jDx. */
//                    jDx++;
//                    /* Zero nCase. */
//                    nCase = 0;
//                    /* Clear TBuffer. */
//                    memset(TBuffer, 0, strlen(TBuffer));
//                    /* Realloc Line. */
//                    Lineptr = realloc(Lineptr, (jDx + 1) * sizeof (Book));
//                }
//                if (nError) {
//                    free(TBuffer);
//                    free(Lineptr);
//                    fclose(fileptr);
//                    return -4;
//                }                    /* EXIT SUCCESS. */
//                else {
//                    /* Return Values. */
//                    *ptrLine = Lineptr;
//                    *Cnt = jDx;
//                    free(TBuffer);
//                    fclose(fileptr);
//                    return 0;
//                }
//            }
//        }
//    }
//}
//
//#pragma argsused
//
//int main(int argc, char* argv[]) {
//    int i, Cnt = 0;
//    Book *nrBooks = NULL;
//    Book *ptrBook = NULL;
//    BookList *List = CreateBookList(1);
//
//    GetLineFromFile("file.txt", &Cnt, &nrBooks);
//
//    for (i = 0; i < Cnt; i++) {
//        insertBookIntoBookList(List, List->tail, nrBooks[i].BookId, nrBooks[i].BookName, nrBooks[i].BookWriter, nrBooks[i].YearPublished);
//    }
//    /* Dump Book List. */
//    printf("Book List:\n");
//    for (ptrBook = List->head; ptrBook != NULL; ptrBook = ptrBook->next)
//        printf("%d,%s,%s,%d\n", ptrBook->BookId, ptrBook->BookName, ptrBook->BookWriter, ptrBook->YearPublished);
//
//
//    printf("Hit enter to continue....");
//    getchar();
//    return 0;
//}
////---------------------------------------------------------------------------