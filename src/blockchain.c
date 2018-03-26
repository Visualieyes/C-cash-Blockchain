/**
 *  BlockChain ADT : private implementation / algorithms
 *
 *  COMP220: Assignment 3
 *  Author:
 *  Date:    Feb. 1, 2018
 */

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

/***********************
 * BLOCKCHAIN private implementation details
 ***********************/
const int DEFAULT_DIFFICULTY = 2;              // Default difficulty for hashing puzzles, increase to make mining harder

/*********************
 *  PUBLIC INTERFACE
 *********************/

/*
 * Constructor - return a new, empty BlockChain
 * POST:  bcLen(chain) == 0
 */
BlockChain bcNew( ) {
    BlockChain* bc = malloc(sizeof(BlockChain));
    bc->head = NULL;
    bc->tail = NULL;
    return *bc;
}
/*
 * Destructor - remove all data and free all memory associated with the chain
 * POST: bcLen(chain) == 0
 */
void bcDelete( BlockChain *chain ){
    while (chain->head!=NULL){
        Block_t* cur = chain->head;
        chain->head = cur->next;
        blkDelete(cur);
        free(cur);
    }
}

/*
 * Print a text representation of this chain on STDOUT
 */
void bcPrint( const BlockChain chain ){
    Block_t* s = chain.head;
    while (s!=NULL){
        Block_t* cur = s;
        s = cur->next;
        blkPrevHash(*cur);
    }
}

/*
 * Return the number of Blocks in the chain
 */
int bcLen( const BlockChain chain ){
    Block_t* s = chain.head;
    int num = 0;
    while (s!=NULL){
        Block_t* cur = s;
        s = cur->next;
        num++;
    }
    return num;
}

/*
 *  Return true iff blkIsValid(block) for every block in the chain
 */
bool bcIsValid(const BlockChain chain){
    Block_t* s = chain.head;
    while (s!=NULL){
        Block_t* cur = s;
        s = cur->next;
        if (!blkIsValid(*cur)){
            return false;
        }
    }
    return true;
}

/*
 * Return a pointer to the chain's tail Block
 */
Block_t* bcTail(const BlockChain chain){
    return chain.tail;
}

/*
 * Append the given block to the chain
 *    iff blkValidates(new_block, bcTail->hash, new_block->proof_of_work)
 * POST: bcTail(*chain) == new_block && blkIsValid(*new_block)
 */
void bcAppend( BlockChain *chain, Block_t* new_block ){
    if (chain->head==NULL){
        chain->head=new_block;
        chain->tail=new_block;
    }
    if (blkValidates(*new_block, chain->tail->hash, new_block->proof_of_work)){
        printf("2nd");
        if (chain->head==chain->tail){
            chain->tail = new_block;
        }
        printf("3rd");
        chain->tail = new_block;
    }
}
