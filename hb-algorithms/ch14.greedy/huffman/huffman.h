#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <stdio.h>
#include <stdlib.h>
#include "priority-queue.h"

#define MAX_CHAR 26
#define MAX_BIT 6

typedef unsigned int UINT;
typedef unsigned char UCHAR;

typedef struct tagSymbolInfo {
    UCHAR symbol;
    int frequency;
} SymbolInfo;

typedef struct tagHuffmanNode {
    SymbolInfo data;
    struct tagHuffmanNode *left;
    struct tagHuffmanNode *right;
} HuffmanNode;

typedef struct tagBitBuffer {
    UCHAR *buffer;
    UINT size;
} BitBuffer;

typedef struct tagHuffmanCode {
    UCHAR code[MAX_BIT];
    int size;
} HuffmanCode;

HuffmanNode *huffman_create_node(SymbolInfo);
void huffman_destroy_node(HuffmanNode *);
void huffman_destroy_tree(HuffmanNode *);
void huffman_add_bit(BitBuffer *, char);

void huffman_encode(HuffmanNode **, UCHAR *, BitBuffer *, HuffmanCode []);
void huffman_decode(HuffmanNode **, BitBuffer *, UCHAR *);

void huffman_build_prefix_tree(HuffmanNode **, SymbolInfo []);
void huffman_build_code_table(HuffmanNode *, HuffmanCode [], UCHAR [], int);
void huffman_print_binary(BitBuffer *);

#endif //__HUFFMAN_H__