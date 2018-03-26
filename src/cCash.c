#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"
#include "sha1.h"
#define DIF 2

int main(int argc, char* argv[]){

    BlockChain chain = bcNew();

    TransactionList list1 = tlistCreate();

    tlistAppend(&list1,"Mary",1,"Rob");
    tlistAppend(&list1,"Mary",2,"Rob");
    tlistAppend(&list1,"Mary",4,"Rob");
    tlistAppend(&list1,"Rob",5,"Mary");
    tlistAppend(&list1,"Mary",4,"Rob");

    Block_t* block1 = blkCreate(list1,DIF,NULL_NONCE);

    bcAppend(&chain,block1);

    TransactionList list2 = tlistCreate();

    tlistAppend(&list2,"Kate",2,"Jay");
    tlistAppend(&list2,"Jay",5,"Kate");
    tlistAppend(&list2,"Kate",6,"Jay");

    Block_t* block2 = blkCreate(list2,DIF,NULL_NONCE);
    bcAppend(&chain,block2);

    bcPrint(chain);

    return 0;
}
