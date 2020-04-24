#include <string.h>
#include "huffman.h"

int main(void) {
    char *source = " http://www.seanlab.net";
    char *decoded = "";

    HuffmanNode *tree = NULL;
    BitBuffer encoded = {NULL, 0};
    HuffmanCode code_table[MAX_CHAR];

    memset(&code_table, 0x00, sizeof(HuffmanCode) * MAX_CHAR);

    huffman_encode(&tree, source, &encoded, code_table);

    printf("Original size: %d. Encoded size:%d\n", 
        (strlen(source) + 1) * sizeof(char) * 8, encoded.size);

    decoded = (char *)malloc(sizeof(char) * (strlen(source) + 1));
    huffman_decode(tree, &encoded, decoded);

    printf("Original: %s\nEncoded:", source);

    huffman_print_binary(&encoded);

    printf("\nDecoded: %s\n", decoded);

    huffman_destroy_tree(tree);
    free(decoded);

    return 0;
}