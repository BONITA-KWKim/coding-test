#include "huffman.h"

HuffmanNode *huffman_create_node(SymbolInfo new_data) {
    HuffmanNode *new_node = (HuffmanNode *)malloc(sizeof(HuffmanNode));

    new_node->left = NULL;
    new_node->right = NULL;
    new_node->data = new_data;

    return new_node;    
}

void huffman_destroy_node(HuffmanNode * node) {
    free(node);
}

void huffman_destroy_tree(HuffmanNode * node) {
    if(NULL == node) return;

    huffman_destroy_node(node->left);
    huffman_destroy_node(node->right);
    huffman_destroy_node(node);
} 

void huffman_add_bit(BitBuffer *buf, char bit) {
    UCHAR mask = 0x80;

    if(0 == (buf->size % 8)) {
        buf->buffer = realloc(buf->buffer, sizeof(UCHAR) * ((buf->size / 8) + 1));
        buf->buffer[buf->size / 8] = 0x00;
    }

    mask >>= buf->size % 8;

    if(1 == bit) {
        buf->buffer[buf->size / 8] |= mask;
    } else {
        buf->buffer[buf->size / 8] &= ~mask;
    }

    ++buf->size;
}

void huffman_encode(HuffmanNode **tree, 
                    UCHAR *source, 
                    BitBuffer *encoded, 
                    HuffmanCode code_table[]) {
    int i = 0, j = 0;
    SymbolInfo symbol_info_table[MAX_CHAR];
    UCHAR tmp[MAX_BIT];

    for(i = 0; MAX_CHAR > i; ++i) {
        symbol_info_table[i].symbol = i;
        symbol_info_table[i].frequency = 0;
    }

    i = 0;
    while('\0' != source[i]) {
        symbol_info_table[source[i++]].frequency++;
    }

    huffman_build_prefix_tree(tree, symbol_info_table);
    huffman_build_code_table(*tree, code_table, tmp, 0);

    i = 0;
    while('\0' != source[i]) {
        int bit_count = code_table[source[i]].size;

        for(j = 0; bit_count > j; ++j) {
            huffman_add_bit(encoded, code_table[source[i]].code[i]);
        }

        ++i;
    }
}

void huffman_decode(HuffmanNode **tree, BitBuffer *encoded, UCHAR *decoded) {
    int i = 0, idx = 0;
    HuffmanNode *current = tree;

    for(i = 0; encoded->size >= i; ++i) {
        UCHAR mask = 0x80;

        if(NULL == current->left && NULL == current->right) {
            decoded[idx++] = current->data.symbol;
            current = tree;
        }

        mask >>= i % 8;

        if(mask != (encoded->buffer[i/8] & mask)) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    decoded[idx] = '\0';
}

void huffman_build_prefix_tree(HuffmanNode **tree, 
                               SymbolInfo symbol_info_table[]) {
    PQNode result;
    PriorityQueue *PQ = PQ_create(0);

    for(int i = 0; MAX_CHAR > i; ++i) {
        if(0 < symbol_info_table[i].frequency) {
            HuffmanNode *bit_node = huffman_create_node(symbol_info_table[i]);
            PQNode new_node;
            new_node.priority = symbol_info_table[i].frequency;
            new_node.data = bit_node;
            PQ_enqueue(PQ, new_node);
        }
    }

    while(1 < PQ->used_size) {
        SymbolInfo new_data = {0, 0};
        HuffmanNode *bit_node = huffman_create_node(new_data);
        HuffmanNode *left, *right;

        PQNode q_left, q_right, new_node;
        
        PQ_dequeue(PQ, &q_left);
        PQ_dequeue(PQ, &q_right);

        left = (HuffmanNode *)q_left.data;
        right = (HuffmanNode *)q_right.data;

        bit_node->data.symbol = 0;
        bit_node->data.frequency = left->data.frequency + right->data.frequency;

        new_node.priority = bit_node->data.frequency;
        new_node.data = bit_node;

        PQ_enqueue(PQ, new_node);
    } // while(PQ)

    PQ_dequeue(PQ, &result);
    *tree = (HuffmanNode *)result.data;
}
void huffman_build_code_table(HuffmanNode *tree, 
                              HuffmanCode code_table[], 
                              UCHAR code[], 
                              int size) {
    if(NULL == tree) return;

    if(NULL != tree->left) {
        code[size] = 0;
        huffman_build_code_table(tree->left, code_table, code, size+1);
    }

    if(NULL == tree->left && NULL == tree->right) {
        for(int i = 0; size > i; ++i) {
            code_table[tree->data.symbol].code[i] = code[i];
        }
        code_table[tree->data.symbol].size = size;
    }
}

void huffman_print_binary(BitBuffer * buf) {
    int i =0;

    for(i = 0; buf->size > i; ++i) {
        UCHAR mask = 0x80;
        mask >>= i % 8;

        printf("%d", mask == (buf->buffer[i/8] & mask));
    }
}
