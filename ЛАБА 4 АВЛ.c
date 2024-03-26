#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_PUBLISHER_LENGTH 100
#define MAX_FILENAME_LENGTH 100
#define MAX_BOOKS 2000

typedef struct {
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int year;
    char publisher[MAX_PUBLISHER_LENGTH];
    unsigned int rating;
    unsigned int price;
} Book;

typedef struct Node {
    Book book;
    struct Node* left;
    struct Node* right;
    int height;
} Node;



int height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

void printBook(Book* book) {
    printf("-------------------------------------------\nTitle: %s\nAuthor(s): %s\nYear: %d\nPublisher: %s\nRating: %d\nPrice: %d\n-------------------------------------------\n\n", 
        book->title, book->author, book->year, book->publisher, book->rating, book->price);
}

int getBalance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}
void createBookArray(Node* root, Book** bookArray, int* index) {
    if (root == NULL)
        return;

    // Рекурсивно добавляем указатель на текущую книгу в массив
    bookArray[*index] = &(root->book);
    (*index)++;

    // Рекурсивно продолжаем обход в левом и правом поддеревьях
    createBookArray(root->left, bookArray, index);
    createBookArray(root->right, bookArray, index);
}

int compareBooksByPrice_incrg(int * a, int* b) {
    Book* bookA = *( Book**)a;
    Book* bookB = *(Book**)b;

    if (bookA->price < bookB->price)
        return -1;
    else if (bookA->price > bookB->price)
        return 1;
    else
        return 0;
}
int compareBooksByPrice_decrg(int * a, int * b) {
    Book* bookA = *(Book**)a;
    Book* bookB = *(Book**)b;

    if (bookA->price < bookB->price)
        return 1;
    else if (bookA->price > bookB->price)
        return -1;
    else
        return 0;
}
int compareBooksByRating_incrg(int* a, int* b) {
    Book* bookA = *(Book**)a;
    Book* bookB = *(Book**)b;

    if (bookA->rating < bookB->rating)
        return -1;
    else if (bookA->rating > bookB->rating)
        return 1;
    else
        return 0;
}
int compareBooksByRating_decrg(int* a, int* b) {
    Book* bookA = *(Book**)a;
    Book* bookB = *(Book**)b;

    if (bookA->rating < bookB->rating)
        return 1;
    else if (bookA->rating > bookB->rating)
        return -1;
    else
        return 0;
}
int compareBooksByYear_incrg(int* a, int* b) {
    Book* bookA = *(Book**)a;
    Book* bookB = *(Book**)b;

    if (bookA->year < bookB->year)
        return -1;
    else if (bookA->year> bookB->year)
        return 1;
    else
        return 0;
}
int compareBooksByYear_decrg(int* a, int* b) {
    Book* bookA = *(Book**)a;
    Book* bookB = *(Book**)b;

    if (bookA->year < bookB->year)
        return 1;
    else if (bookA->year > bookB->year)
        return -1;
    else
        return 0;
}

int searchByKeyword(Node* root, char* keyword) {
    if (root == NULL) {
        return NULL;
    }
    int numb=atoi(keyword);
    // Проверяем, содержит ли текущая книга ключевое слово в любом из параметров
    if (strstr(root->book.title, keyword) != NULL ||
        strstr(root->book.author, keyword) != NULL ||
        strstr(root->book.publisher, keyword) != NULL || numb==root->book.year
        || numb == root->book.price
        || numb == root->book.rating) {

        printf("Book found:\n");
        printf("-------------------------------------------\nTitle: %s\nAuthor(s): %s\nYear: %d\nPublisher: %s\nRating: %d\nPrice: %d\n-------------------------------------------\n\n",
            root->book.title, root->book.author, root->book.year, root->book.publisher, root->book.rating, root->book.price);
    }

    // Рекурсивно продолжаем поиск в левом и правом поддеревьях
    searchByKeyword(root->left, keyword);
    searchByKeyword(root->right, keyword);
}

// Функция редактирования книги
void editBook(Node* root) {
    int buf;
        if (root != NULL) {
            int ch = 0;
            printf("What you want to edit:\n 1-Title\n 2-Author\n 3-Year\n 4-Publisher\n 5-Rating\n 6-Price\n 7-All\n");
            buf = scanf("%d", &ch);
            getchar();
            if (ch == 1)
            {
                printf("New Title: ");
                buf = fgets(root->book.title, sizeof(root->book.title), stdin);
                root->book.title[strcspn(root->book.title, "\n")] = 0;
            }
            else if (ch == 2)
            {
                printf("New Author: ");
                buf = fgets(root->book.author, sizeof(root->book.author), stdin);
                root->book.author[strcspn(root->book.author, "\n")] = 0;
            }
            else if (ch == 3)
            {
                printf("New Year: ");
                buf = scanf("%d", &root->book.year);
                buf = getchar();
            }
            else if (ch == 4)
            {
                printf("New Publisher: ");
                buf = fgets(root->book.publisher, sizeof(root->book.publisher), stdin);
                root->book.publisher[strcspn(root->book.publisher, "\n")] = 0;
            }
            else if (ch == 5)
            {
                printf("New Rating: ");
                buf = scanf("%f", &root->book.rating);
                buf = getchar();
            }
            else if (ch == 6)
            {
                printf("New Price: ");
                buf = scanf("%f", &root->book.price);
                buf = getchar();
            }
            else if (ch == 7)
            {
                printf("Enter new book information:\n");

                printf("Title: ");
                buf = fgets(root->book.title, sizeof(root->book.title), stdin);
                root->book.title[strcspn(root->book.title, "\n")] = 0;

                printf("Author: ");
                buf = fgets(root->book.author, sizeof(root->book.author), stdin);
                root->book.author[strcspn(root->book.author, "\n")] = 0;

                printf("Year: ");
                buf = scanf("%d", &root->book.year);
                buf = getchar();

                printf("Publisher: ");
                buf = fgets(root->book.publisher, sizeof(root->book.publisher), stdin);
                root->book.publisher[strcspn(root->book.publisher, "\n")] = 0;

                printf("Rating: ");
                buf = scanf("%f", &root->book.rating);
                buf = getchar();

                printf("Price: ");
                buf = scanf("%f", &root->book.price);
                buf = getchar();
            }

            printf("Book information updated.\n");
            return;
        }
}

Node* newNode(Book book) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->book.title, book.title);
    strcpy(node->book.author, book.author);
    node->book.year = book.year;
    strcpy(node->book.publisher, book.publisher);
    node->book.rating = book.rating;
    node->book.price = book.price;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insertNode(Node* node, Book book) {
    if (node == NULL) {
        return newNode(book);
    }

    int compare = strcmp(book.title, node->book.title);
    if (compare < 0) {
        node->left = insertNode(node->left, book);
    }
    else if (compare > 0) {
        node->right = insertNode(node->right, book);
    }
    else {
        // Duplicate titles are not allowed
        printf("Book with the same title already exists.\n");
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(book.title, node->left->book.title) < 0) {
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(book.title, node->right->book.title) > 0) {
        return leftRotate(node);
    }

    if (balance > 1 && strcmp(book.title, node->left->book.title) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(book.title, node->right->book.title) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, char title[MAX_TITLE_LENGTH]) {
    if (root == NULL) {
        return root;
    }

    int compare = strcmp(title, root->book.title);
    if (compare < 0) {
        root->left = deleteNode(root->left, title);
    }
    else if (compare > 0) {
        root->right = deleteNode(root->right, title);
    }
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }

            free(temp);
        }
        else {
            Node* temp = minValueNode(root->right);

            strcpy(root->book.title, temp->book.title);
            strcpy(root->book.author, temp->book.author);
            root->book.year = temp->book.year;
            strcpy(root->book.publisher, temp->book.publisher);
            root->book.rating = temp->book.rating;
            root->book.price = temp->book.price;

            root->right = deleteNode(root->right, temp->book.title);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void inorderTraversal(Node* node) {
    if (node != NULL) {
        inorderTraversal(node->left);
        printf("-------------------------------------------\nTitle: %s\nAuthor(s): %s\nYear: %d\nPublisher: %s\nRating: %d\nPrice: %d\n-------------------------------------------\n\n",
            node->book.title, node->book.author, node->book.year, node->book.publisher, node->book.rating, node->book.price);
        inorderTraversal(node->right);
    }
}

Node* searchByTitle(Node* node, char keyword[MAX_TITLE_LENGTH]) {
    if (node == NULL) {
        return NULL;
    }

    if (strstr(node->book.title, keyword) != NULL) {
        printf("-------------------------------------------\nTitle: %s\nAuthor(s): %s\nYear: %d\nPublisher: %s\nRating: %d\nPrice: %d\n-------------------------------------------\n\n",
            node->book.title, node->book.author, node->book.year, node->book.publisher, node->book.rating, node->book.price);
        return node;
    }

    if (strcmp(keyword, node->book.title) < 0) {
        return searchByTitle(node->left, keyword);
    }
    else {
        return searchByTitle(node->right, keyword);
    }
}

void sortByRating(Node* node) {
    if (node != NULL) {
        sortByRating(node->left);
        printf("-------------------------------------------\nTitle: %s\nAuthor(s): %s\nYear: %d\nPublisher: %s\nRating: %d\nPrice: %d\n-------------------------------------------\n\n",
            node->book.title, node->book.author, node->book.year, node->book.publisher, node->book.rating, node->book.price);
        sortByRating(node->right);
    }
}

void saveDatabase(Node* node, FILE* file) {
    if (node != NULL) {
        saveDatabase(node->left, file);
        fprintf(file, "%s\n", node->book.title);
        fprintf(file, "%s\n", node->book.author);
        fprintf(file, "%d\n", node->book.year);
        fprintf(file, "%s\n", node->book.publisher);
        fprintf(file, "%d\n", node->book.rating);
        fprintf(file, "%d\n", node->book.price);
        saveDatabase(node->right, file);
    }
}

Node* loadDatabase(FILE* file, Node* root) {
    Book book;
    while (fscanf(file, "%[^\n]%*c", book.title) != EOF) {
        fscanf(file, "%[^\n]%*c", book.author);
        fscanf(file, "%d%*c", &book.year);
        fscanf(file, "%[^\n]%*c", book.publisher);
        fscanf(file, "%d%*c", &book.rating);
        fscanf(file, "%d%*c", &book.price);
        root = insertNode(root, book);
    }
    return root;
}

void displayMenu() {
    printf("Please select an option:\n1. Add a book\n2. Remove a book\n3. Edit a book\n4. Search by keyword\n5. Sort \n"
    "6. Print all books\n7. Save database to file\n8. Load database from file\n0. Exit\nEnter your choice: ");
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Node* root = NULL;
    int choice;
    printf("Welcome to the Book Database!\n");
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        getchar(); 

        if (choice==1)
        {
            Book book;
            printf("Enter the title: ");
            fgets(book.title, MAX_TITLE_LENGTH, stdin);
            book.title[strlen(book.title) - 1] = '\0'; 

            printf("Enter the author: ");
            fgets(book.author, MAX_AUTHOR_LENGTH, stdin);
            book.author[strlen(book.author) - 1] = '\0'; 

            printf("Enter the year: ");
            scanf("%d", &book.year);
            getchar(); 

            printf("Enter the publisher: ");
            fgets(book.publisher, MAX_PUBLISHER_LENGTH, stdin);
            book.publisher[strlen(book.publisher) - 1] = '\0'; 

            printf("Enter the rating: ");
            scanf("%f", &book.rating);
            getchar(); 

            printf("Enter the price: ");
            scanf("%f", &book.price);
            getchar(); 

            root = insertNode(root, book);
            printf("Book added successfully!\n");
        }
        else if (choice==2)
        {
            char title[MAX_TITLE_LENGTH];
            printf("Enter the title of the book to remove: ");
            fgets(title, MAX_TITLE_LENGTH, stdin);
            title[strlen(title) - 1] = '\0'; 

            root = deleteNode(root, title);
            printf("Book removed successfully!\n");
        }
        else if (choice==3)
        {
            char title[MAX_TITLE_LENGTH];
            printf("Enter the title of the book to edit: ");
            fgets(title, MAX_TITLE_LENGTH, stdin);
            title[strlen(title) - 1] = '\0'; 

            Node* node = searchByTitle(root, title);
            if (node!=NULL) editBook(node);
            else printf("Book not found!\n");
        }
        else if (choice==4)
        {
            char keyword[MAX_TITLE_LENGTH];
            printf("Enter the keyword to search: ");
            fgets(keyword, MAX_TITLE_LENGTH, stdin);
            keyword[strlen(keyword) - 1] = '\0'; 
            if(searchByKeyword(root, keyword)==NULL) printf("No matches\n");
        }
        else if (choice==5)
        {
            int type_of_sort = 0;
            int order_of_sort = 0;
            printf("Choose sort by...\n1 - Price\n2 - Rating\n3 - Year\n: ");
            scanf("%d", &type_of_sort);
            getchar();
            printf("In what order \n1 - increasing\n2 - decreasing\n: ");
            scanf("%d", &order_of_sort);
            getchar();
            Book* bookArray[MAX_BOOKS];
            int index = 0;
            createBookArray(root, bookArray, &index);
            if (type_of_sort==1)
            {
                if (order_of_sort==1) qsort(&bookArray, index, sizeof(Book*), compareBooksByPrice_incrg);
                else if (order_of_sort==2) qsort(&bookArray, index, sizeof(Book*), compareBooksByPrice_decrg);
            }
            else if (type_of_sort==2)
            {
                if (order_of_sort == 1) qsort(&bookArray, index, sizeof(Book*), compareBooksByRating_incrg);
                else if (order_of_sort == 2) qsort(&bookArray, index, sizeof(Book*), compareBooksByRating_decrg);
            }
            else if (type_of_sort == 3)
            {
                if (order_of_sort == 1) qsort(&bookArray, index, sizeof(Book*), compareBooksByYear_incrg);
                else if (order_of_sort == 2) qsort(&bookArray, index, sizeof(Book*), compareBooksByYear_decrg);
            }
            else if (type_of_sort==4)
            {
                printf("Incorrect inout\n");
            }

            for (int i = 0; i < index; i++) {
                printBook((bookArray[i]));
            }
        }
        else if (choice==6)
        {
            printf("All books:\n");
            inorderTraversal(root);
        }
        else if (choice==7)
{
        char filename[MAX_FILENAME_LENGTH];
        printf("Enter the filename to save: ");
        fgets(filename, MAX_FILENAME_LENGTH, stdin);
        filename[strlen(filename) - 1] = '\0'; 

        FILE* file = fopen(filename, "w");
        if (file != NULL) {
            saveDatabase(root, file);
            fclose(file);
            printf("Database saved successfully!\n");
        }
        else {
            printf("Error opening file.\n");
        }
}
        else if (choice==8)
    {
    char filename[MAX_FILENAME_LENGTH];
    printf("Enter the filename to load: ");
    fgets(filename, MAX_FILENAME_LENGTH, stdin);
    filename[strlen(filename) - 1] = '\0';
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        root = loadDatabase(file, root);
        fclose(file);
        printf("Database loaded successfully!\n");
    }
    else {
        printf("Error opening file.\n");
    }
    }
        else if (choice==0)
    {
    printf("Exiting...\n");
    exit(0);
}
        else printf("Invalid choice! Please try again.\n");
    }

    return 0;
}

