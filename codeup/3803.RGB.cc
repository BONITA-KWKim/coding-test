#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

int min(int *raw_prices, int size) {
    std::sort(raw_prices, raw_prices+size);
    return raw_prices[0];
}

int min_paint_price(int (*raw_prices)[3], int size) {
    int min_price = 0;
    int (*min_prices)[3] = NULL;
    min_prices = (int (*)[3])malloc(sizeof(int) * 3 * size);
    memset(min_prices, 0x00, sizeof(int) * 3 * size);

    int picked = 0;
    for(int i = 0; size > i; ++i) { 
        min_prices[i][0] = raw_prices[i][0];
        min_prices[i][1] = raw_prices[i][1];
        min_prices[i][2] = raw_prices[i][2];

        for(picked = 0; 3 > picked; ++picked) {
            int cmp[2];
            memset(cmp, 0x00, sizeof(int)*2);
            int cmp_pt = 0;
            for(int j = 0; 3 > j; ++j) {
                if (picked == j) continue;

                cmp[cmp_pt++] = min_prices[i][picked] + min_prices[i-1][j];
            }

            min_prices[i][picked] = min(cmp, 2);
        }
    }

    min_price = min(min_prices[size-1], 3);

    return min_price;
}

int main(void) {
    int min = 0;
    int house_no = 0;
    scanf("%d", &house_no);

    int (*paint_prices)[3] = NULL;
    paint_prices = (int (*)[3])malloc(sizeof(int) * 3 * house_no);

    for(int i = 0; house_no > i; ++i) {
        scanf("%d %d %d", &paint_prices[i][0], &paint_prices[i][1], &paint_prices[i][2]);
    }

    min = min_paint_price(paint_prices, house_no);

    printf("%d\n", min);
    
    return 0;
}