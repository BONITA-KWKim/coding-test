def partial_q_sort(arr, i, j):
    # raw data
    # print("raw:", arr, "i:", i, "j:", j)
    if 1 >= len(arr): return arr
    
    p = partition2(arr)
    p += 1
    
    # sorted
    # print("parition:", arr[:p], ",", arr[p:], "i:", i, "j:", j)
    
    if i > p:
        # do not sort left
        #print("sort right only")
        arr[p:] = partial_q_sort(arr[p:], i-p, j-p)
    elif j < p:
        # do not sort right
        #print("sort left only")
        arr[:p] = partial_q_sort(arr[:p], i, j)
    else:
        # sort both
        #print("sort both")
        arr[:p] = partial_q_sort(arr[:p], i, p)
        arr[p:] = partial_q_sort(arr[p:], 0, j-p)

    return arr
    
test_arr = [5, 7, 1, 8, 3, 6, 4, 2]
rst = partial_q_sort(test_arr, 2, 4)
print(test_arr, rst[1:4])