#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_INPUT_LENGTH 100

struct Book
{
    char title[50];
    char author[50];
    char isbn[14];
    char borrower_name[50];
    int borrower_id;
    bool is_available;
};

bool stringValidation(char string[])
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (isdigit(string[i]))
        {
            printf("The entered string should not contain numbers !\n");
            return false;
        }
    }
    return true;
}

bool integerValidation(char string[])
{
    for (int i = 0; i < strlen(string); i++)
    {
        if (isalpha(string[i]))
        {
            printf("The entered number should not contain letters !\n");
            return false;
        }
    }
    return true;
}

bool valueRangeValidation(int start, int end, char input_name[], int value)
{
    if (!(value >= start && value <= end))
    {
        printf("%s value must be between %d and %d !\n", input_name, start, end);
        return false;
    }
    return true;
}

// max_il : max input length
// type = 1 -> string , type = 2 -> integer
bool inputValidation(char input[], int max_il, int type, char input_name[])
{
    int len = strlen(input);
    int c;
    if (len == 1)
    {
        printf("%s cannot be left blank\n", input_name);
    }
    else if (len > max_il)
    {
        printf("%s should be a maximum of %d characters in length\n", input_name, max_il - 1);
        // Input of 100 characters or more
        if (input[len - 1] != '\n')
        {
            while ((c = getchar()) != '\n')
            {
                // Buffer cleaning for the portion of the entered string from the 100th character to the last ('\n').
            }
        }
    }
    else
    {
        // Input of characters from 1 to 99
        input[len - 1] = '\0';

        if (type == 1 && stringValidation(input))
        {
            return true; // Valid string input
        }
        else if (type == 2)
        {
            if (strchr(input, ' ') != NULL)
            {
                printf("%s should not contain whitespace characters !\n", input_name);
            }
            else if (integerValidation(input))
            {
                return true; // Valid integer input
            }
        }
    }
    return false;
}

struct Book createNewBook()
{
    struct Book book;
    char input[MAX_INPUT_LENGTH];

    do
    {
        printf("Enter book's title : ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
    } while (!inputValidation(input, 50, 1, "Book title"));
    strncpy(book.title, input, 50);

    do
    {
        printf("Enter book's author : ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
    } while (!inputValidation(input, 50, 1, "Book author"));
    strncpy(book.author, input, 50);

    do
    {
        printf("Enter book's ISBN : ");
        fgets(input, MAX_INPUT_LENGTH, stdin);
    } while (!inputValidation(input, 14, 2, "Book ISBN"));
    strncpy(book.isbn, input, 14);

    // borrower_name variable is being assigned a default value.
    strcpy(book.borrower_name, "none");
    // borrower_id variable is being assigned a default value.
    book.borrower_id = -1;
    // is_available variable is being assigned a default value.
    book.is_available = true;
    return book;
}

void copyArray(struct Book books[], struct Book copy_books[], int number_of_books)
{
    for (int i = 0; i < number_of_books; i++)
    {
        copy_books[i] = books[i];
    }
}

void displayManipulatedArray(struct Book manipulated_array[], int number_of_books)
{
    for (int i = 0; i < number_of_books; i++)
    {
        printf("Book's title : %s\n", manipulated_array[i].title);
        printf("Book's author : %s\n", manipulated_array[i].author);
        printf("Book's ISBN : %s\n", manipulated_array[i].isbn);
        printf("Book's borrower's name : %s\n", manipulated_array[i].borrower_name);
        printf("Book's borrower's ID : %d\n", manipulated_array[i].borrower_id);
        printf("Book's availability : %s\n", manipulated_array[i].is_available ? "available" : "borrowed");
        printf("--------------------------------------------------\n");
    }
}

// fp : first parameter , sp : second parameter
void swap(struct Book *fp, struct Book *sp)
{
    struct Book temp = *fp;
    *fp = *sp;
    *sp = temp;
}

void sortAndDisplayBooksAccordingToDesiredProperty(struct Book books[], int number_of_books, char property[])
{
    struct Book copy_books[100];
    copyArray(books, copy_books, number_of_books);
    int compareResult = 0;

    for (int i = 0; i < number_of_books - 1; i++)
    {
        for (int j = i + 1; j < number_of_books; j++)
        {
            if (!strcmp(property, "titles"))
            {
                compareResult = strcmp(copy_books[i].title, copy_books[j].title);
            }
            else if (!strcmp(property, "authors"))
            {
                compareResult = strcmp(copy_books[i].author, copy_books[j].author);
            }
            else if (!strcmp(property, "ISBNs"))
            {
                compareResult = strcmp(copy_books[i].isbn, copy_books[j].isbn);
            }
            else if (!strcmp(property, "borrower's name"))
            {
                compareResult = strcmp(copy_books[i].borrower_name, copy_books[j].borrower_name);
            }

            if (compareResult > 0)
            {
                swap(&copy_books[i], &copy_books[j]);
            }
        }
    }

    printf("--------------------------------------------------\n");
    printf("Books (Sorted by their %s)\n", property);
    printf("--------------------------------------------------\n");
    displayManipulatedArray(copy_books, number_of_books);
}

struct Book *findBook(struct Book books[], int number_of_books, char isbn[])
{
    for (int i = 0; i < number_of_books; i++)
    {
        if (!strcmp(books[i].isbn, isbn))
        {
            return &books[i];
        }
    }
    return NULL;
}

void displaySpecificBook(struct Book books[], int number_of_books, char isbn[])
{
    struct Book *found_book = findBook(books, number_of_books, isbn);
    if (found_book == NULL)
    {
        printf("There is no book corresponding to the entered ISBN !\n");
    }
    else
    {
        printf("Book's title : %s\n", found_book->title);
        printf("Book's author : %s\n", found_book->author);
        printf("Book's ISBN : %s\n", found_book->isbn);
        printf("Book's borrower's name : %s\n", found_book->borrower_name);
        printf("Book's borrower's ID : %d\n", found_book->borrower_id);
        printf("Book's availability : %s\n\n", found_book->is_available ? "available" : "borrowed");
    }
}

void bookBorrow(struct Book books[], int number_of_books, char isbn[])
{
    struct Book *found_book = findBook(books, number_of_books, isbn);
    char input[MAX_INPUT_LENGTH];

    if (found_book == NULL)
    {
        printf("There is no book corresponding to the entered ISBN !\n");
    }
    else
    {
        if (found_book->is_available == false)
        {
            printf("The book corresponding to the entered ISBN has already been taken !\n");
        }
        else
        {
            printf("Displaying book's information...\n");
            printf("Book's title : %s\n", found_book->title);
            printf("Book's author : %s\n", found_book->author);
            printf("Book's ISBN : %s\n\n", found_book->isbn);

            do
            {
                printf("Enter book's borrower's name : ");
                fgets(input, MAX_INPUT_LENGTH, stdin);
            } while (!inputValidation(input, 50, 1, "Borrower name"));
            strncpy(found_book->borrower_name, input, 50);

            do
            {
                printf("Enter book's borrower ID : ");
                fgets(input, MAX_INPUT_LENGTH, stdin);
            } while (!(inputValidation(input, 4, 2, "Borrower ID") && valueRangeValidation(1, 100, "Borrower ID", atoi(input))));
            found_book->borrower_id = atoi(input);

            printf("\n");
            found_book->is_available = false;
            printf("The process is successfully completed !\n");
        }
    }
}

void bookReturn(struct Book books[], int number_of_books, char isbn[])
{
    struct Book *found_book = findBook(books, number_of_books, isbn);
    if (found_book == NULL)
    {
        printf("There is no book corresponding to the entered ISBN !\n");
    }
    else
    {
        if (found_book->is_available == true)
        {
            printf("The book corresponding to the entered ISBN has not been taken !\n");
        }
        else
        {
            printf("Displaying book's information...\n");
            printf("Book's title : %s\n", found_book->title);
            printf("Book's author : %s\n", found_book->author);
            printf("Book's ISBN : %s\n", found_book->isbn);
            printf("Book's borrower's name : %s (old) --> none (new)\n", found_book->borrower_name);
            printf("Book's borrower's Id : %d (old) --> -1 (new)\n", found_book->borrower_id);
            printf("\n");
            strcpy(found_book->borrower_name, "none");
            found_book->borrower_id = -1;
            found_book->is_available = true;
            printf("The process is successfully completed !\n");
        }
    }
}

int main()
{
    struct Book books[100];
    int number_of_books = 0;
    int mm_choice = 0; // main menu choice
    int sm_choice = 0; // sub menu choice

    char input[MAX_INPUT_LENGTH];

    do
    {
        printf("Library Management System\n");
        printf("1. Add book\n");
        printf("2. Display all books\n");
        printf("3. Book borrowing\n");
        printf("4. Book returning\n");
        printf("5. Quit\n");

        do
        {
            printf("Your choice : ");
            fgets(input, MAX_INPUT_LENGTH, stdin);
        } while (!(inputValidation(input, 2, 2, "Menu choice") && valueRangeValidation(1, 5, "Menu choice", atoi(input))));
        mm_choice = atoi(input);
        printf("\n");

        if (mm_choice == 1)
        {
            if (number_of_books == 100)
            {
                printf("The library is full, you cannot add a new book !\n");
            }
            else
            {
                books[number_of_books++] = createNewBook();
            }
        }
        else if (mm_choice == 2)
        {
            if (number_of_books == 0)
            {
                printf("Library is empty, there is no book to display !\n");
            }
            else
            {
                printf("Select one of these sorting options\n");
                printf("1. Sort by their titles in ascending order\n");
                printf("2. Sort by their authors in ascending order\n");
                printf("3. Sort by their ISBN numbers in ascending order\n");
                printf("4. Sort by their borrower's name in ascending order\n");
                printf("5. Display specific book using its ISBN number\n");

                do
                {
                    printf("Your choice : ");
                    fgets(input, MAX_INPUT_LENGTH, stdin);
                } while (!(inputValidation(input, 2, 2, "Sub menu choice") && valueRangeValidation(1, 5, "Sub menu choice", atoi(input))));
                sm_choice = atoi(input);
                printf("\n");

                if (sm_choice == 1)
                {
                    sortAndDisplayBooksAccordingToDesiredProperty(books, number_of_books, "titles");
                }
                else if (sm_choice == 2)
                {
                    sortAndDisplayBooksAccordingToDesiredProperty(books, number_of_books, "authors");
                }
                else if (sm_choice == 3)
                {
                    sortAndDisplayBooksAccordingToDesiredProperty(books, number_of_books, "ISBNs");
                }
                else if (sm_choice == 4)
                {
                    sortAndDisplayBooksAccordingToDesiredProperty(books, number_of_books, "borrower's name");
                }
                else if (sm_choice == 5)
                {
                    do
                    {
                        printf("Enter book's ISBN : ");
                        fgets(input, MAX_INPUT_LENGTH, stdin);
                    } while (!inputValidation(input, 14, 2, "Book ISBN"));
                    displaySpecificBook(books, number_of_books, input);
                }
            }
        }
        else if (mm_choice == 3)
        {
            if (number_of_books == 0)
            {
                printf("Library is empty, there is no book for book borrowing process !\n");
            }
            else
            {
                do
                {
                    printf("Enter ISBN number of book for book borrowing process : ");
                    fgets(input, MAX_INPUT_LENGTH, stdin);
                } while (!inputValidation(input, 14, 2, "Book ISBN"));
                printf("\n");
                bookBorrow(books, number_of_books, input);
            }
        }
        else if (mm_choice == 4)
        {
            if (number_of_books == 0)
            {
                printf("Library is empty, there is no book for book returning process !\n");
            }
            else
            {
                do
                {
                    printf("Enter ISBN number of book for book returning process : ");
                    fgets(input, MAX_INPUT_LENGTH, stdin);
                } while (!inputValidation(input, 14, 2, "Book ISBN"));
                printf("\n");
                bookReturn(books, number_of_books, input);
            }
        }

        if (mm_choice != 5)
        {
            printf("Going back to main menu...\n\n");
        }
        else
        {
            printf("Quitting from library management system, have a nice day !\n");
        }

    } while (mm_choice != 5);

    return 0;
}
