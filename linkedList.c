#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include"linkedList.h"

// this code compiled with gcc version 10.2.0

Node *createList()
{
    Node *newList = (Node *)malloc(sizeof(Node));
    newList->product = NULL;
    newList->nextProduct = NULL;
    return newList;
}

//Creating of Product object.
Product *createProductObject(char *product_name, char *product_type, int price){
    Product *newProduct = (Product *) malloc(sizeof(Product));
    strcpy(newProduct->product_name, product_name);
    strcpy(newProduct->product_type, product_type);
    newProduct->price = price;
    return newProduct;
}

Node *deleteProduct(char *product_type, Node *productList)
{
    Node *currentNode = productList;
    Node *previousNode = NULL;
    //if list is empty
    if (productList == NULL)
    {
        return NULL;
    }
    while (strcmp(currentNode->product->product_type, product_type) != 0)
    {// until product_type not equal product_type in productLists

        if (currentNode->nextProduct == NULL){
            return NULL;
        }

        else{
            previousNode = currentNode;
            currentNode = currentNode->nextProduct;
        }
    }
    if (currentNode == productList){  // if first product will delete
        productList = productList->nextProduct;
    }

    else{
        previousNode->nextProduct = currentNode->nextProduct;
    }
    return productList;
}


Node *insertProduct(Node *productList, Product *product)
{
    if (product)
    {
        Node *currentNode = productList;
        if (currentNode->product == NULL)
        {
            currentNode->product = product;
            currentNode->nextProduct = NULL;
            productList = currentNode;
        }
        else
        {
            while (currentNode->nextProduct != NULL)
            {
                currentNode = currentNode->nextProduct;
            }
            currentNode->nextProduct = (Node *)malloc(sizeof(Node));
            currentNode->nextProduct->product = product;
            currentNode->nextProduct->nextProduct = NULL;
        }
    }
    else
    {
        printf("\n ProductList is empty. \n");
    }
    return productList;
}

Product *findProduct(Node* productList, char *product_type){
  // find the product in productLists given product_type
    Node *currentNode = productList;
    Product *prdct = (Product *)malloc(sizeof(Product));
    int flag = 0;
    if(currentNode->product == NULL)
      return NULL;
    if(currentNode == NULL){
      return NULL;
    }
    while(1){
        if(strcmp(currentNode->product->product_type, product_type) == 0){
          flag = 1;
          prdct = currentNode->product;
          return prdct;
        }
        else{
          currentNode = currentNode->nextProduct;
        }
        if(currentNode == NULL)
          break;
    }
    if(flag == 0)
      return NULL;
}

void increasedPrice(Node* productList, int num){
    Node *currentNode = productList;
    int i = 0;
    if (productList->product == NULL)
    {
        printf(" List is empty\n");
    }
    if(productList == NULL){
      printf("There is not found any product!\n");
    }
    while(i<num){
        currentNode = currentNode->nextProduct;
        i++;
    }
    int newPrice = ((currentNode->product->price * 20) / 100 ) + currentNode->product->price;
    currentNode->product->price = newPrice;
    printf("%s, %d\n", currentNode->product->product_name, currentNode->product->price);

}

int findSizeOfList(Node *productList){
  // find the size of list
    Node *currentNode = productList;
    int size = 0; // list size
    if(currentNode == NULL){
      return 0;
    }
    else if(currentNode->product == NULL)
      return 0;
    while(currentNode != NULL){
      size++;
      currentNode = currentNode->nextProduct;
    }
  return size;
}

void printByBudget(int budget, Node *productList) {
    Node *current = productList;

    if (current == NULL)
    {
        printf("\nFavorite List is empty!");
    }
    printf("You can buy products which are less than your budget: ");
    while (current!= NULL){
        if(current->product->price <= budget)
        {
          printf("%s, ", current->product->product_name);
        }
        current = current->nextProduct;
    }
    printf("\n\n");
}
int ifExistsProductType(Node *productList, char *product_type){
    Node *current = productList;
    if(current == NULL){
      return 0;
    }
    while(current != NULL){
      if(strcmp(current->product->product_type, product_type) == 0){
        return 1;
      }
      current = current->nextProduct;
    }
    return 0;

}

void printList(Node *productList)
{
    if (productList == NULL) {printf("List is empty!\n");}
    else if(productList->product == NULL)
    {
        printf(" List is empty!\n");
    }
    else if (productList != NULL)
    {
        Node *productNode = productList;
        while (productNode != NULL)
        {
            printf(" %s, %s, %d \n", productNode->product->product_name, productNode->product->product_type, productNode->product->price);
            productNode = productNode->nextProduct;
        }
    }
}
