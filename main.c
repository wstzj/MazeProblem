#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

#define MaxSize 102

char Map[MaxSize][MaxSize];//地图
int Mark[MaxSize][MaxSize] = {0};//用于标记是否走过
int x_size = 0, y_size = 0;//用于记录迷宫大小
int x_start, y_start;//起点坐标
int x_end, y_end;//终点坐标
int flag = 0;

Stack *SaveStack = NULL;//记录路径
Stack *SaveStackTop = NULL;//记录路径栈顶

Stack *RecordStack = NULL;//临时栈
Stack *RecordStackTop = NULL;//临时栈顶

int direction_x[4] = {0, -1, 0, 1};
int direction_y[4] = {-1, 0, 1, 0};//四个方向，左上右下；

enum directions{
    South = 0, West = 1, North = 2, East = 3
};

/*
 * 从csv读取地图信息
 */
void ReadMap() {

    char pass[256] = "";
    char *line = NULL, *record;
    FILE *fp = fopen(".\\map.csv", "r+");

    if (fp != NULL) {
        fgets(pass, 255, fp);//跳过第一行,第一行是二进制头
        while ((line = fgets(pass, sizeof(pass), fp)) != NULL)//当没有读取到文件末尾时循环继续
        {

            record = strtok(line, ",");//以逗号将每个数分割
            x_size = 0;
            while (record != NULL)//读取每一行的数据
            {
                Map[y_size][x_size] = record[0];//将每个点存入数组
                x_size++;
                record = strtok(NULL, ",");//寻找下一个被分隔的字符串
            }
            y_size++;
        }
        x_size = x_size - 2;//减去第一列与最后一列边框
        y_size = y_size - 2;//减去第一行与最后一行边框
    }

}

/*
 * int x 横坐标
 *
 * int y 纵坐标
 */
void dfs(int x, int y) {

    if (x == x_end && y == y_end)//搜寻成功时输出结果
    {
        flag = 1;
        Node *p1 = (Node *) malloc(sizeof(Node));
        p1->x = x;
        p1->y = y;
        p1->direction = "0";
        SaveStack = push(SaveStack, p1, &SaveStackTop);//压入终点
        while (isEmpty(SaveStack)) {
            Node *p = SaveStackTop->data;
            RecordStack = push(RecordStack, p, &RecordStackTop);
            SaveStack = pop(SaveStack, &SaveStackTop);
        }
        while (isEmpty(RecordStack)) {
            Node *p = RecordStackTop->data;
            SaveStack = push(SaveStack, p, &SaveStackTop);//回溯用
            RecordStack = pop(RecordStack, &RecordStackTop);
            printf("(%d,%d,%s)", p->x, p->y, p->direction);
            if(RecordStack != NULL)//使最后一个节点不输出"->"
                printf("->");

        }
        SaveStack = pop(SaveStack, &SaveStackTop);//弹出终点
        printf("\n");
        return;
    }

    if (x < 1 || x > x_size || y < 1 || y > y_size)//越界就回溯
        return;

    for (int i = 0; i < 4; i++) {
        int next_x = x + direction_x[i];//跟据i的值+1 +0 -1
        int next_y = y + direction_y[i];//跟据i的值+1 +0 -1
        if (0 < next_x && next_x <= x_size
            && 0 < next_y && next_y <= y_size
            && Map[next_y][next_x] == '0' && Mark[next_y][next_x] == 0) //判断是否能走
        {
            Mark[next_y][next_x] = 1;//将走过的地方进行标记
            Node *p = (Node *) malloc(sizeof(Node));
            p->x = x;
            p->y = y;
            switch (i) { //下一步的方向,并存入链表
                case East:
                    p->direction = "→";
                    break;
                case North:
                    p->direction = "↓";
                    break;
                case West:
                    p->direction = "←";
                    break;
                case South:
                    p->direction = "↑";
                    break;
                default:
                    break;
            }
            SaveStack = push(SaveStack, p, &SaveStackTop);

            dfs(next_x, next_y); //深搜递归

            Mark[next_y][next_x] = 0;//回溯,标记成未走过
            SaveStack = pop(SaveStack, &SaveStackTop);//出栈
        }
    }
}


int main() {

    ReadMap(); //读取地图

    while (1) {
        printf("请输入起点，输入格式：坐标x 坐标y\n");
        scanf("%d %d", &x_start, &y_start);
        if ((x_start < 0 && x_start >= x_size) &&
            (y_start < 0 && y_start >= y_size)) //判断输入是否合理
            printf("起点越界\n");
        else if (Map[y_start][x_start] != '0')
            printf("该点不能作为一个起点\n");
        else break;
    }
    Mark[y_start][x_start] = 1;
    while (1) {
        printf("请输入终点，输入格式：坐标x 坐标y\n");
        scanf("%d %d", &x_end, &y_end);
        if ((x_end < 0 && x_end >= x_size) &&
            (y_start < 0 && y_start >= y_size))  //判断输入是否合理
            printf("终点越界\n");
        else if (Map[y_end][x_end] != '0')
            printf("该点不能作为一个终点\n");
        else break;
    }
    dfs(x_start, y_start);

    if (flag == 0){ //判断是否有解
        printf("无解");
    }
    return 0;

}
