#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxSize 100

char Map[MaxSize][MaxSize];
int x_size = 0, y_size = 0;//用于记录迷宫大小

enum directions {
    East = 1, South, West, North
};//东南西北四个方向数据化

typedef struct Node {
    int x;//横坐标
    int y;//纵坐标
    int direction;//下一步的方向
} Node;//输出的三元组

void ReadMap() {

    char pass[102] = "";
    char *line = NULL, *record;
    FILE *fp = fopen(".\\map.csv", "r+");

    if (fp != NULL) {
        fgets(pass, 101, fp);//跳过第一行,第一行是二进制头
        fgets(pass, 101, fp);//跳过第二行,第二行是map边框
        fseek(fp, 2, SEEK_CUR);//跳过第一列，第一列是map边框
        while ((line = fgets(pass, sizeof(pass), fp)) != NULL)//当没有读取到文件末尾时循环继续
        {
            fseek(fp, 2, SEEK_CUR);//跳过第一列，第一列是map边框
            record = strtok(line, ",");//以逗号将每个数分割
            x_size = 0;
            while (record != NULL)//读取每一行的数据
            {
                Map[y_size][x_size] = record[0];
                x_size++;
                record = strtok(NULL, ",");//寻找下一个被分隔的字符串
            }
            y_size++;
        }
    }
}


int main() {

    ReadMap();
    fflush(stdout);
    return 0;

}
