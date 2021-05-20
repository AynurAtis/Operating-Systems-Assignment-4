#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <string.h>
#include <time.h>

#define NUMBER_OF_THREADS 4

// this code compiled with gcc version 10.2.0

Node* productList1;
Node* productList2;
Node* favoriteList;

int productList1Status = 0;
int productList2Status = 0;
int favoriteListStatus = 0;


char product_type[30];
int budget;
/* Defining mutexes for each resource */
pthread_mutex_t productList1_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t productList2_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t favoriteList_lock = PTHREAD_MUTEX_INITIALIZER;

void initializeList(){

  productList1 = createList();
  productList2 = createList();
  favoriteList = createList();

  Product *newProduct = (Product *) malloc(sizeof(Product));
  newProduct = createProductObject("iphoneX", "electronicDevice", 1000);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("shoes", "clothing", 550);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("powerbank","electronicDevice",100);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("detergent","market",20);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("coke","market",5);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("tshirt","clothing",70);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("toastMachine","electronicDevice",1000);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("sugar","market",30);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("skirt","clothing",100);
  productList1 = insertProduct(productList1, newProduct);
  newProduct = createProductObject("water","market",5);
  productList1 = insertProduct(productList1, newProduct);

  newProduct = createProductObject("jean","clothing",220);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("dress","clothing",300);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("hairDrier","electronicDevice",300);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("blender","electronicDevice",500);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("coffee","market",75);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("tea","market",30);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("heeled shoes","clothing",800);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("chocolate","market",50);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("armchair","furniture",1000);
  productList2 = insertProduct(productList2, newProduct);
  newProduct = createProductObject("bed","furniture",1000);
  productList2 = insertProduct(productList2, newProduct);

}


void cutAndinsertProduct(int id){

    int randNumber = rand() % 2 + 1;  // create a number randomly
    //(if number is 1, productList1 getting operation. if number is 2, productList2 getting operation)
    if(productList2Status == 0 && favoriteListStatus == 0 && randNumber == 2){
      // if productList2 and favoriteList are not use by any thread
      printf("\n Type 1 thread is perfoming\n");
      pthread_mutex_trylock(&productList2_lock);  // locked lists
      pthread_mutex_trylock(&favoriteList_lock);
      favoriteListStatus = 1;
      productList2Status = 1;
      int loopCounter1 = 2; // 2 products are cutting productList
      int productNumber2 = 0;
      while(productList2 != NULL && loopCounter1 > 0){
          Product *cuttingProduct = (Product *) malloc(sizeof(Product));
          cuttingProduct = findProduct(productList2, product_type); // if the product is exist
          if(cuttingProduct != NULL){
            productList2 = deleteProduct(cuttingProduct->product_type, productList2);
            favoriteList = insertProduct(favoriteList,cuttingProduct);
            productNumber2++; // how many product is cutting from productList2 and pasting to favoriteList
          }
          loopCounter1--;
      }
      pthread_mutex_unlock(&productList2_lock); //release lists
      productList2Status = 0; // change the status to use by other threads
      pthread_mutex_unlock(&favoriteList_lock);
      favoriteListStatus = 0;
      printf("\n %d products is cut from ProductList%d and pasted to favories\n", productNumber2, randNumber);
    }
    if(productList1Status == 0 && favoriteListStatus == 0 && randNumber == 1){
      // if productList1 and favoriteList are not use by any thread
      printf("\n Type 1 thread is perfoming\n");
      pthread_mutex_trylock(&productList1_lock);
      pthread_mutex_trylock(&favoriteList_lock);
      favoriteListStatus = 1;
      productList1Status = 1;
      int loopCounter2 = 2;
      int productNumber1 = 0;
      while(productList1 != NULL && loopCounter2 > 0){
          Product *cuttingProduct = (Product *) malloc(sizeof(Product));
          cuttingProduct = findProduct(productList1, product_type);
          if(cuttingProduct != NULL){
            productList1 = deleteProduct(cuttingProduct->product_type, productList1);
            favoriteList = insertProduct(favoriteList, cuttingProduct);
            productNumber1++;
          }
          loopCounter2--;
      }
      pthread_mutex_unlock(&productList1_lock);
      productList1Status = 0;
      pthread_mutex_unlock(&favoriteList_lock);
      favoriteListStatus = 0;
      printf("\n %d products is cut from ProductList%d and pasted to favories\n", productNumber1, randNumber );
    }
    sleep(0.8); // to prevent the possible starvation
    pthread_exit(NULL);
}

void increasingPrice(int id){

    srand(time(NULL));
    int listNumber = rand() % 3;  // to choose the any list for increasing product price
    int size = 0;
    int indexOfElement = 0;
    printf("\n Type %d thread is performing\n", id);
    switch(listNumber){
        case 0:
          if(productList1Status == 0){  // if productList1 is not use by any threads
              pthread_mutex_trylock(&productList1_lock);
              productList1Status = 1;
              size = findSizeOfList(productList1);
              if(size > 0){
                indexOfElement = rand() % size;
                printf("\n Product price increased in productList1: ");
                increasedPrice(productList1, indexOfElement);
                printf("\n");
              }
              pthread_mutex_unlock(&productList1_lock);
              productList1Status = 0;
            }
            break;
        case 1:
          if(productList2Status == 0){  // if productList2 is not use by any threads
              pthread_mutex_trylock(&productList2_lock);
              productList2Status = 1;
              size = findSizeOfList(productList2);
              if(size > 0){
                indexOfElement = rand() % size;
                printf("\n Product price increased in productList2: ");
                increasedPrice(productList2, indexOfElement);
                printf("\n");
              }
              pthread_mutex_unlock(&productList2_lock);
              productList2Status = 0;
            }
            break;
        case 2:
          if(favoriteListStatus == 0){ // if favoriteList is not use by any threads
              pthread_mutex_trylock(&favoriteList_lock);
              favoriteListStatus = 1;
              size = findSizeOfList(favoriteList);
              if(size > 0){ // if the list is not NULL
                indexOfElement = rand() % size;
                printf("\n Product price increased in favoriteList: ");
                increasedPrice(favoriteList, indexOfElement);
                printf("\n");
              }
              pthread_mutex_unlock(&favoriteList_lock);
              favoriteListStatus = 0;
            }
            break;
        default:
            printf("Invalid operation\n");
            break;
    }
    pthread_exit(NULL);
}


void buyProducts(int id){

  if(favoriteListStatus == 0){
      Product *buyingProduct[20];
      printf("\n Type %d thread is performing...\n", id);
      pthread_mutex_trylock(&favoriteList_lock);  // locked the favoriteList
      favoriteListStatus = 1; // changed the status of favoriteList
      printByBudget(budget, favoriteList);
      printf("\n");
      pthread_mutex_unlock(&favoriteList_lock); // released favoriteList
      favoriteListStatus = 0;
    }
    pthread_exit(NULL);
}

void *allFunctionsWithThreads(void *id){

    int *idAsInt = (int *) id;
     if(*idAsInt == 0 || *idAsInt == 1) {cutAndinsertProduct(*idAsInt);}     // Type1 thread for id= 0,1
     else if(*idAsInt == 2) {increasingPrice(*idAsInt);}  // Type2 thread for id=2
     else if(*idAsInt == 3) {buyProducts(*idAsInt);}  // Type3 thread for id=3

}

int main(){

  initializeList();

  while(productList1 != NULL || productList2 != NULL){
    // repeat all operation until two product lists are empty
    printf("\n Current products list are: \n");
    printf(" ProductList1: \n");
    printList(productList1);
    printf("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n");
    printf(" ProductList2: \n");
    printList(productList2);
    printf("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n" );
    printf(" Favories: \n" );
    printList(favoriteList);
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n" );
    puts(" Please enter your favorite product_type:" );
    scanf("%s", product_type);
    while(1){ // if entered product_type not in any productList, reenter product_type
      if(ifExistsProductType(productList1, product_type) == 1 || ifExistsProductType(productList2, product_type) == 1)
          break;
      else {
        printf("\n There is no %s in productLists\n", product_type);
        puts(" Please enter your favorite product_type:" );
        scanf("%s", product_type);
      }
    }
    printf("%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n" );
    printf("Please enter your budget for shopping: \n");
    scanf("%d", &budget);
    //Initializing threads & attributes.
      pthread_t tid[4];
      pthread_attr_t attr[4];

      //Creating threads
      for(int i=0; i<NUMBER_OF_THREADS; i++){
          void *memory = malloc(sizeof(int));
          int* id = (int *) memory;
          *id = i;
          pthread_attr_init(&attr[i]);
          pthread_create(&tid[i], &attr[i], allFunctionsWithThreads, id);
      }
      //Wait for all the threads to finish its work.
      for(int i=0; i<NUMBER_OF_THREADS; i++){
          pthread_join(tid[i], NULL);
      }
    }

    printf("\n ProductList1: \n");
    printList(productList1);
    printf("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n");
    printf(" ProductList2: \n");
    printList(productList2);
    printf("\n%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n\n" );
    printf(" Favories: \n" );
    printList(favoriteList);
    printf("\nGoodbye...\n");

}
