#include <stdio.h>

struct Book {
    int id;
    char title[50];
    char author[50];
    int issued;
};

void addBook() {
    struct Book b;

    printf("\nEnter Book ID: ");
    scanf("%d", &b.id);

    printf("Enter Book Title: ");
    scanf(" %49[^\n]", b.title);

    printf("Enter Author Name: ");
    scanf(" %49[^\n]", b.author);

    b.issued = 0;

    FILE *fp = fopen("books.txt", "a");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    fprintf(fp, "%d|%s|%s|%d\n",
            b.id, b.title, b.author, b.issued);

    fclose(fp);

    printf("Book added successfully!\n");
}

void displayBooks() {
    struct Book b;
    char line[200];

    FILE *fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("No books found!\n");
        return;
    }

    printf("\n===== LIBRARY BOOKS =====\n");

    while (fgets(line, sizeof(line), fp)) {

        if (sscanf(line, "%d|%49[^|]|%49[^|]|%d",
                   &b.id, b.title, b.author, &b.issued) == 4) {

            printf("\nBook ID: %d\n", b.id);
            printf("Title: %s\n", b.title);
            printf("Author: %s\n", b.author);

            if (b.issued == 1)
                printf("Status: Issued\n");
            else
                printf("Status: Available\n");
        }
    }

    fclose(fp);
}

void updateBook(int action) {
    struct Book b;
    char line[200];

    int id, found = 0;

    printf("Enter Book ID: ");
    scanf("%d", &id);

    FILE *fp = fopen("books.txt", "r");

    if (fp == NULL) {
        printf("Book file not found!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");

    if (temp == NULL) {
        fclose(fp);
        printf("File error!\n");
        return;
    }

    while (fgets(line, sizeof(line), fp)) {

        if (sscanf(line, "%d|%49[^|]|%49[^|]|%d",
                   &b.id, b.title, b.author, &b.issued) == 4) {

            if (b.id == id) {
                found = 1;

                if (action == 1) {
                    if (b.issued == 0) {
                        b.issued = 1;
                        printf("Book issued successfully!\n");
                    } else {
                        printf("Book is already issued!\n");
                    }
                }

                else {
                    if (b.issued == 1) {
                        b.issued = 0;
                        printf("Book returned successfully!\n");
                    } else {
                        printf("Book is already available!\n");
                    }
                }
            }

            fprintf(temp, "%d|%s|%s|%d\n",
                    b.id, b.title, b.author, b.issued);
        }
    }

    fclose(fp);
    fclose(temp);

    if (found) {
        remove("books.txt");
        rename("temp.txt", "books.txt");
    } else {
        remove("temp.txt");
        printf("Book not found!\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n===== LIBRARY MANAGEMENT =====\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                updateBook(1);
                break;

            case 4:
                updateBook(2);
                break;

            case 5:
                printf("Exiting Library System!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
