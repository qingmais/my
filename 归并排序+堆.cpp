#include <iostream>
#include <ctime>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "MergeSort.h"
const unsigned int datacount=3500000000U;//�����ļ������������Ϊ35���У��ļ���СΪ21G���ң�
const unsigned int num_to_sort=50000000;//���ڴ���һ�����������Ϊ5ǧ���У�һ��70����ʱ�ļ���
const char *unsort_file="unsort_data.txt";//ԭʼδ����������ļ���
const char *sort_file="sort_data.txt";//�����������ļ���
void init_data(unsigned int num);//������������ļ�
int main(){
    srand(time(NULL));
    init_data(datacount);
    MergeSort mersort(unsort_file,sort_file,num_to_sort);
    mersort.sort();
    system("pause");
    return 0;
}
void init_data(unsigned int num){
    FILE* f=fopen(unsort_file,"wt");//���������ļ�
    for(int i=0;i<num;++i){
        fprintf(f,"%d\n",(rand()%(1000000000-1+1))+1);//ÿ���������һ��[1,1000000000]�ڵ�����
    }
    fclose(f);
}
