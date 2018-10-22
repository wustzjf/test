
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct array {
    int size;
    int used;
    int *arr;
};


void alloc_array(struct array *array)
{
    array->arr = (int *)malloc(array->size * sizeof(int));
}

// 由低到高有序排列
void array_insert(struct array *array, int data)
{
    int i = 0;

    if (array->used >= array->size)
        return ;

    for (i = 0; i < array->used; i++)
    {
        if (array->arr[i] > data)
        {
            memmove(&array->arr[array->used], &array->arr[i], (array->used - i) * sizeof(int)); // 注意取地址
            break;
        }
    }

    array->arr[i] = data;
    array->used++;

    return ;
}

void array_dump(struct array *array)
{
    int i = 0;

    for (i = 0; i < array->used; i++)
        printf("array[%d] : %d\n", i, array->arr[i]);

    return ;
}

int array_search(struct array *array, int data)
{
    int i = 0;

    for (i = 0; i < array->used; i++)
    {
        if (array->arr[i] == data)
            return i;

        if (array->arr[i] > data)       // 优化，可以提前结束循环，去除没必要的搜索
            return -1;
    }

    return -1;
}

int array_delete(struct array *array, int index)
{
    int i = 0;

    if (index >= array->used || index < 0)  // 小于0也需要判断
    {
        return -1;
    }

    memmove(&array->arr[index], &array->arr[index+1], (array->used - index) * sizeof(int)); // memmove 最后入参是拷贝字节数
    array->used--;  // 删除之后 used也需要变更

    return 0;
}


int main(void)
{
    int index = 0;
    struct array array = {10, 0, NULL};

    alloc_array(&array);
    array_insert(&array, 1);

    // 之前memmove 最后一个入参只填写了个数,没有sizeof操作计算整的字节数，而这里测试数据又是很小，
    // 导致没有超过1个字节，虽然没拷贝全，到数据测试仍旧没有问题
    array_insert(&array, 300);  
    array_insert(&array, 2);
    array_insert(&array, 4);
    array_dump(&array);


    index = array_search(&array, 4);
    printf("index = %d\n", index);

    index = array_search(&array, 6);
    printf("index = %d\n", index);
    
    array_delete(&array, 2);
    array_dump(&array);
    array_delete(&array, 5);
    array_dump(&array);

    return 0;

}
