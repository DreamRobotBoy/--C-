#include "MC_Data_Manage.h"
#define DIMENSION 3               //根据矩阵维度修改这个值
void main(void)
{
	uint8_t status = 6;
	uint8_t Err;
	FP64 Value[DIMENSION] = { 0 };
	FP64 Root[DIMENSION] = { 0 };
	if (status == 6)
	{
		//创建矩阵
		MC_Matrix_t *pMatrix = MC_MatrixCreate();
		uint8_t select = 3;		
		uint16_t i = 0;
		if (select == 1)
		{
			//值数据解[1 3 2 -2]
			//打印矩阵
			//MC_MatrixPrint(pMatrix, DIMENSION);
			Value[i++] = 10;
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 4);
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, 3);
			//打印矩阵
			//MC_MatrixPrint(pMatrix, DIMENSION);
			Value[i++] = 12;
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, -4);
			//添加数据:
			Value[i++] = 7;
			MC_MatrixAddData(pMatrix, 1);
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 0);
			//打印矩阵
			//MC_MatrixPrint(pMatrix,DIMENSION);
			Value[i++] = 9;
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, 3);
			MC_MatrixAddData(pMatrix, -1);
			MC_MatrixAddData(pMatrix, 0);

		}
		else if (select == 2)
		{
			i = 0;
			//值数据[2 3 -2 1]
			Value[i++] = 19;
			//添加数据:
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 3);
			MC_MatrixAddData(pMatrix, -4);
			MC_MatrixAddData(pMatrix, 2);
			//添加数据:
			Value[i++] = 2;
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, 6);
			//添加数据:
			Value[i++] = 5;
			MC_MatrixAddData(pMatrix, 1);
			MC_MatrixAddData(pMatrix, 1);
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 0);

			//添加数据:
			Value[i++] = -9;
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, -1);
			MC_MatrixAddData(pMatrix, 5);
			MC_MatrixAddData(pMatrix, 0);


		}
		else if (select ==3)
		{
			//值数据
			i = 0;
			Value[i++] = 8;
			//添加数据:
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 1);
			MC_MatrixAddData(pMatrix, -4);
			//添加数据:
			Value[i++] = 1;
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, -3);
			MC_MatrixAddData(pMatrix, 2);
			//添加数据:
			Value[i++] = 1;
			MC_MatrixAddData(pMatrix, 4);
			MC_MatrixAddData(pMatrix, -8);
			MC_MatrixAddData(pMatrix, 12);
		}
		else if (select == 4)
		{
			i = 0;
			//值数据
			Value[i++] = 8;
			//添加数据:
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, 1);
			MC_MatrixAddData(pMatrix, -5);
			MC_MatrixAddData(pMatrix, 1);
			//打印矩阵
			//MC_MatrixPrint(pMatrix,DIMENSION);
			Value[i++] = 9;
			MC_MatrixAddData(pMatrix, 1);
			MC_MatrixAddData(pMatrix, -3);
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, -6);
			//打印矩阵
			//MC_MatrixPrint(pMatrix, DIMENSION);
			Value[i++] = -5;
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 2);
			MC_MatrixAddData(pMatrix, -1);
			MC_MatrixAddData(pMatrix, 2);
			//打印矩阵
			//MC_MatrixPrint(pMatrix, DIMENSION);
			Value[i++] = 0;
			MC_MatrixAddData(pMatrix, 0);
			MC_MatrixAddData(pMatrix, 4);
			MC_MatrixAddData(pMatrix, -7);
			MC_MatrixAddData(pMatrix, 6);
		}
		//打印矩阵
		MC_MatrixPrint(pMatrix, DIMENSION);
		////删除第i个数据
		//MC_MatrixDeleteIndex(&pMatrix, 1);
		//MC_MatrixPrint(pMatrix, DIMENSION);
		////添加数据
		//MC_MatrixAddData(pMatrix, 1.7);
		//MC_MatrixPrint(pMatrix, DIMENSION);

		////删除第i个数据
		//MC_MatrixDeleteIndex(&pMatrix, 2);
		//MC_MatrixPrint(pMatrix, DIMENSION);
		////添加数据
		//MC_MatrixAddData(pMatrix, 1.6);
		//MC_MatrixPrint(pMatrix, DIMENSION);

		////删除第i个数据
		//MC_MatrixDeleteIndex(&pMatrix, 3);
		//MC_MatrixPrint(pMatrix, DIMENSION);
		////添加数据
		//MC_MatrixAddData(pMatrix, 1.5);
		//MC_MatrixPrint(pMatrix, DIMENSION);

		////删除第i个数据
		//MC_MatrixDeleteIndex(&pMatrix, 9);
		//MC_MatrixPrint(pMatrix, DIMENSION);
		////添加数据
		//MC_MatrixAddData(pMatrix, 1.4);
		//MC_MatrixPrint(pMatrix, DIMENSION);

		////删除第i个数据
		//MC_MatrixDeleteIndex(&pMatrix, 5);
		//MC_MatrixPrint(pMatrix, DIMENSION);
		////添加数据
		//MC_MatrixAddData(pMatrix, 1.4);
		//MC_MatrixPrint(pMatrix, DIMENSION);

		//MC_MatrixDeleteIndex(&pMatrix, 9);
		////打印矩阵
		//MC_MatrixPrint(pMatrix, DIMENSION);

		////添加数据
		//MC_MatrixAddData(pMatrix, 1.7);
		//MC_MatrixAddData(pMatrix, 3.1);
		//MC_MatrixAddData(pMatrix, 5.2);
		////打印矩阵
		//MC_MatrixPrint(pMatrix, DIMENSION);

		//返回系数
		FP64 Coeff12 = MC_MatrixCoeffIndex(pMatrix, 1, 2, DIMENSION);
		FP64 Coeff31 = MC_MatrixCoeffIndex(pMatrix, 3, 1, DIMENSION);
		FP64 Coeff33 = MC_MatrixCoeffIndex(pMatrix, 3, 3, DIMENSION);
		
		//打印结果
		printf("\n");
		for (size_t i = 0; i < DIMENSION; i++)
		{
			printf("%f\n", Value[i]);
		}

		//主元排序
		//MC_MatrixSelectPivot(&pMatrix,Value, DIMENSION);
		//打印矩阵
		MC_MatrixPrint(pMatrix, DIMENSION);
		//打印结果
		printf("\n");
		for (size_t i = 0; i < DIMENSION; i++)
		{
			printf("%f\n", Value[i]);
		}


		//矩阵消去计算
		Err = MC_MatrixElimination(&pMatrix, Value, DIMENSION);
		//打印矩阵
		MC_MatrixPrint(pMatrix, DIMENSION);
		//打印结果
		printf("\n");
		for (size_t i = 0; i < DIMENSION; i++)
		{
			printf("%f\n", Value[i]);
		}
		Err = MC_MatrixInverseCal(pMatrix, Value, Root, DIMENSION);
		//清除矩阵链表
		MC_MatrixClear(pMatrix);

		if (Err == 0)
		{
			//打印结果
			printf("\n");
			for (size_t i = 0; i < DIMENSION; i++)
			{
				printf("%f\n", Root[i]);
			}
		}
		else
		{
			printf("求解无效:%d", Err);
		}
		system("pause");
	}
}
