#include <iostream>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "MergeSort.h"
const unsigned int datacount=3500000000U;//输入文件里的数据行数为35亿行（文件大小为21G左右）
const unsigned int num_to_sort=50000000;//在内存中一次排序的数量为5千万行（一共70个临时文件）
const char *unsort_file="unsort_data.txt";//原始未排序的输入文件名
const char *sort_file="sort_data.txt";//已排序的输出文件名
void init_data(unsigned int num);//随机生成数据文件
int main(){
    srand(time(NULL));
    init_data(datacount);
    MergeSort mersort(unsort_file,sort_file,num_to_sort);
    mersort.sort();
    system("pause");
    return 0;
}
void init_data(unsigned int num){
    FILE* f=fopen(unsort_file,"wt");//建立输入文件
    for(int i=0;i<num;++i){
        fprintf(f,"%d\n",(rand()%(1000000000-1+1))+1);//每行随机生成一个[1,1000000000]内的整数
    }
    fclose(f);
}
