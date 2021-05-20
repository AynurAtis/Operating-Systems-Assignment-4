#include"products.h"

// creating node struct
struct node
{
    Product *product;
    struct node* nextProduct;
};

typedef struct node Node;

// defining functions
Node *createList();
Product *createProductObject(char *product_name, char *product_type, int price);
Node *deleteProduct(char *product_type, Node *productListHeader);
Node *insertProduct(Node *productListHeader, Product *product);
Product *findProduct(Node* productList, char *product_type);
int ifExistsProductType(Node *productList, char *product_type);
void printList(Node *productListHeader);
void printByBudget(int budget, Node *playListHeader);
int findSizeOfList(Node *productList);
void increasedPrice(Node* productList, int num);
