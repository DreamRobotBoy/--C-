#include "MC_Data_Manage.h"


/********************************************************************************************
函数功能：创建数据链表矩阵
@Param 无:
返回:指向MC_Matrix_t类型的指针
********************************************************************************************/
MC_Matrix_t *MC_MatrixCreate()
{
	MC_Matrix_t *pMatrix = (MC_Matrix_t*)malloc(sizeof(MC_Matrix_t));
	pMatrix->pNextData = NULL;
	return pMatrix;
}

/********************************************************************************************
函数功能：打印数据链表矩阵
@Param pMatrix:系数矩阵
@Param uiDimension:系数矩阵的维度
无返回值
********************************************************************************************/
void MC_MatrixPrint(MC_Matrix_t *pMatrix, uint16_t uiDimension)
{
	if (pMatrix == NULL)
	{
		return;
	}
	char string[500] = { '\0' }, strTemp[50] = { '\0' };
	MC_Matrix_t *pCur, *pNext;
	uint16_t i = 0;
	pCur = pMatrix;
	printf("\n");
	while (pCur->pNextData != NULL)
	{
		sprintf(strTemp, "%f ", pCur->fData);
		strcat(string, strTemp);
		pNext = pCur->pNextData;
		pCur = pNext;
		i++;
		if (i%uiDimension == 0)
		{
			strcat(string, "\n");
		}
	}
	strcat(string, "\n*********************************");
	printf(string);
}

/********************************************************************************************
函数功能：释放数据链表矩阵占用的堆栈内存
@Param pMatrix:系数矩阵
无返回值
********************************************************************************************/
void MC_MatrixClear(MC_Matrix_t *pMatrix)
{
	MC_Matrix_t *pCur, *pNext;
	pCur = pMatrix;
	while (pCur->pNextData != NULL)
	{
		pNext = pCur->pNextData;
		free(pCur);
		pCur = NULL;
		pCur = pNext;
	}
	free(pCur);
	pCur = NULL;
	pMatrix = NULL;
}

/********************************************************************************************
函数功能：添加数据到系数矩阵中
@Param pMatrix:系数矩阵
@Param fData:所要添加的系数
返回值 0成功 1失败
********************************************************************************************/
uint8_t MC_MatrixAddData(MC_Matrix_t *pMatrix, FP64 fData)
{
	if (pMatrix == NULL)
	{
		return 1;
	}
	MC_Matrix_t *head, *pNext, *pCur;
	//保存头指针
	head = pCur = pMatrix;
	//循环至链尾
	while (pCur->pNextData != NULL)
	{
		pNext = pCur->pNextData;
		pCur = pNext;
	}
	//链尾添加数据
	pCur->fData = fData;

	//分配新的链尾
	pNext = (MC_Matrix_t*)malloc(sizeof(MC_Matrix_t));
	pNext->pNextData = NULL;
	pCur->pNextData = pNext;

	//头指针返回
	pMatrix = head;
	return 0;

}

/********************************************************************************************
函数功能：释放系数矩阵第index个节点占用的堆栈内存
@Param pMatrix:指向系数矩阵的指针
@Param index:所需删除的节点序号，从1开始计数。
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC_MatrixDeleteIndex(MC_Matrix_t **pMatrix, uint16_t index)
{
	MC_Matrix_t *pFront = NULL, *pCur, *pNext;
	pFront = *pMatrix;
	if (pFront->pNextData == NULL)
	{
		return 1;
	}
	//删除第一个节点数据
	if (index == 1)
	{
		pCur = pFront;
		*pMatrix = pFront->pNextData;
		free(pCur);
		pCur = NULL;
		return 0;
	}
	//删除第二个节点数据
	pCur = pFront->pNextData;
	if (index == 2)
	{
		if (pCur->pNextData == NULL)
		{
			return 1;
		}
		pFront->pNextData = pCur->pNextData;
		free(pCur);
		pCur = NULL;
		return 0;
	}
	//删除大于2个节点的数据
	for (uint16_t i = 2; i < index; i++)
	{
		if (pCur->pNextData == NULL)
		{
			return 1;
		}
		pFront = pCur;
		pNext = pCur->pNextData;
		pCur = pNext;
	}

	//删除尾节点
	if (pCur->pNextData == NULL)
	{
		return 1;
	}
	pFront->pNextData = pCur->pNextData;
	free(pCur);
	pCur = NULL;
	return 0;
}

/********************************************************************************************
函数功能：查找矩阵的指定系数
@Param pMatrix:系数矩阵
@Param i:指定第i行
@Param j:指定第j列
@Param uiDimension:系数矩阵的维度
返回值 0成功，1失败
********************************************************************************************/
FP64 MC_MatrixCoeffIndex(MC_Matrix_t *pMatrix, uint16_t i, uint16_t j, uint16_t uiDimension)
{
	if (pMatrix == NULL)
	{
		return 1;
	}
	MC_Matrix_t *pCur, *pNext;
	uint16_t nCout = 1;
	pCur = pMatrix;
	while (nCout < (uiDimension*(i - 1) + j))
	{
		if (pCur->pNextData == NULL)
		{
			return 1;
		}
		pNext = pCur->pNextData;
		pCur = pNext;
		nCout++;
	}
	//定位到指定系数
	return pCur->fData;
}

/********************************************************************************************
函数功能：将系数矩阵的第i行除以指定系数加到第j行,使得第j行的首系数为零
@Param pMatrix:指向指数矩阵的指针
@Param pValue[]:等式右值
@Param i,j:第i行，第j列
@Param uiDimension:系数矩阵的维度
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC_MatrixCalBetterElim(MC_Matrix_t **pMatrix, FP64 pValue[], uint16_t i, uint16_t j, uint16_t uiDimension)
{
	if (pMatrix == NULL || pValue == NULL)
	{
		return 1;
	}
	FP64 Coeff, Mol, Den;
	MC_Matrix_t *pRow_i = NULL, *pRow_j = NULL, *pCur, *pNext, *pCur1, *pNext1;
	uint16_t Temp_i;
	pCur = *pMatrix;

	//检索第i与j行首指针
	for (int16_t k = 1; k < uiDimension*(j - 1) + i; k++)
	{
		//检索到第i行首指针
		if (k == uiDimension*(i - 1) + i)
		{
			pRow_i = pCur;
			Den = pCur->fData;
			//确认分母为零
			if (Den == 0.0f)
			{
				//临时保存第i行序号
				Temp_i = i;
				for (int16_t m = k + 1; m <= uiDimension*(uiDimension-1)+i; m++)
				{
					pNext = pCur->pNextData;
					pCur = pNext;
					//确认第Temp_i行首系数不为零
					if (m == uiDimension*(Temp_i)+i)
					{
						if (pCur->fData != 0.0f)
						{
							//保存分母
							Den = pCur->fData;
							//将第Temp_i行加到第i行中
							pCur1 = pRow_i;
							for (int16_t num = 1; num <= uiDimension - i + 1; num++)
							{
								pCur1->fData += pCur->fData;
								pNext = pCur->pNextData;
								pNext1 = pCur1->pNextData;
								pCur = pNext;
								pCur1 = pNext1;
							}

							//值添加
							pValue[i - 1] += pValue[Temp_i];
							//回传第i行首地址
							pCur = pRow_i;
							break;
						}
						Temp_i++;
					}
					else
					{
						//矩阵无解
						if (m == uiDimension*(j-1)+i)
						{
							return 2;
						}
					}
				}
			}
		}
		pNext = pCur->pNextData;
		pCur = pNext;
	}
	//检索到第j行首指针
	pRow_j = pCur;
	Mol = pCur->fData;
	//计算系数
	Coeff = Mol / Den;
	//pRow_j-pRow_i*Coeff
	pCur = pRow_i; pCur1 = pRow_j;
	for (int16_t k = i; k <= uiDimension; k++)
	{
		//计算系数，再减到下一行
		pCur1->fData = pCur1->fData - pCur->fData*Coeff;
		//往后推进一个节点
		if (pCur->pNextData != NULL&&pCur1->pNextData != NULL)
		{
			pNext = pCur->pNextData;
			pNext1 = pCur1->pNextData;
			pCur = pNext;
			pCur1 = pNext1;
		}
	}
	pValue[j - 1] = pValue[j - 1] - pValue[i - 1] * Coeff;
	return 0;
}

/********************************************************************************************
函数功能：消元第一步，将系数矩阵转换成上三角矩阵
@Param pMatrix:指向指数矩阵的指针
@Param pValue:等式右值
@Param uiDimension:系数矩阵的维度
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC_MatrixElimination(MC_Matrix_t **pMatrix, FP64 pValue[], uint16_t uiDimension)
{
	if (pMatrix == NULL || pValue == NULL || uiDimension == 0)
	{
		return 1;
	}
	//消去
	uint16_t i = 1, j = 1;
	for (i = 1; i <= uiDimension - 1; i++)
	{//第i行运算
		for (j = i + 1; j <= uiDimension; j++)
		{
			//第j行-第i行*第j行首系数/第i行首系数
			//MC_MatrixCalElim(pMatrix, pValue, i, j, uiDimension);
			MC_MatrixCalBetterElim(pMatrix, pValue, i, j, uiDimension);
		}
	}

	return 0;
}


/********************************************************************************************
函数功能：消元第二步,上三角矩阵回代求解
@Param pMatrix:指向指数矩阵的指针
@Param pValue:等式右值
@Param pRoot:方程的根
@Param uiDimension:系数矩阵的维度
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC_MatrixInverseCal(MC_Matrix_t *pMatrix, FP64 pValue[], FP64 pRoot[], uint16_t uiDimension)
{
	if (pMatrix == NULL || pValue == NULL || pRoot == NULL || uiDimension == 0)
	{
		return 1;
	}
	//分配动态数组保存每行首地址
	MC_Matrix_t **pAddr = (MC_Matrix_t**)calloc(uiDimension, sizeof(MC_Matrix_t*));
	MC_Matrix_t *pCur, *pNext;
	pCur = pMatrix;
	int16_t j = 0;
	for (int16_t i = 1; i <= uiDimension*uiDimension; i++)
	{
		if (pCur->pNextData == NULL)
		{
			return 1;
		}
		//每行首地址
		if ((i - 1) % uiDimension == (i - 1) / uiDimension)
		{
			pAddr[j++] = pCur;
		}
		pNext = pCur->pNextData;
		pCur = pNext;
	}
	//回代求解
	FP64 fBackValue = 0;
	for (int16_t i = uiDimension - 1; i >= 0; i--)
	{
		fBackValue = 0;
		pCur = pAddr[i];
		//前一个解回代值到下一个公式值的计算
		for (int16_t k = i + 1; k < uiDimension; k++)
		{
			pNext = pCur->pNextData;
			pCur = pNext;
			fBackValue += pCur->fData*pRoot[k];
		}
		//分母为零，返回2
		if (pAddr[i]->fData == 0.0f)
		{
			return 2;
		}
		pRoot[i] = (pValue[i] - fBackValue) / pAddr[i]->fData;

	}
	//释放分配的内存
	free(pAddr);
	return 0;
}


/********************************************************************************************
/********************************************************************************************
/********************************************************************************************
/**********************  以二维数组表示矩阵,求解方程的解 ************************************
/********************************************************************************************
/********************************************************************************************
********************************************************************************************/

/********************************************************************************************
函数功能：创建系数矩阵
@Param 无:
返回:指向FP64类型的二维指针
********************************************************************************************/
FP64 **MC2_MatrixCreate(uint16_t uiDimension)
{
	//为系数矩阵分配uiDimension*(uiDimension+1)维的内存空间
	FP64 **Array = (FP64**)calloc(uiDimension,sizeof(FP64*));
	//FP64 **Array = (FP64**)malloc(uiDimension*sizeof(FP64*));
	for (int8_t i = 0; i < uiDimension; i++)
	{
		 Array[i] = (FP64*)calloc(uiDimension + 1, sizeof(FP64));
	}

	return Array;
}

/********************************************************************************************
函数功能：释放系数矩阵
@Param ppMatrix:指向系数矩阵的指针
@Param uiDimension:
无返回值:
********************************************************************************************/
void MC2_MatrixRelease(FP64 **ppMatrix, uint16_t uiDimension)
{
	//释放内存
	for (int8_t i = 0; i < uiDimension; i++)
	{
		free(ppMatrix[i]);
	}
	free(ppMatrix);

}

/********************************************************************************************
函数功能：打印系数矩阵
@Param ppMatrix:指向系数矩阵的指针
无返回值
********************************************************************************************/
void MC2_MatrixPrint(FP64 **ppMatrix, uint16_t uiDimension)
{

	for (int8_t i = 0; i <uiDimension; i++)
	{
		for (int8_t j = 0; j < uiDimension+1; j++)
		{
			printf("%f ", ppMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n******************************************************\n\n");
}

/********************************************************************************************
函数功能：添加整行系数到矩阵的第i行中
@Param ppMatrix:指向系数矩阵的指针
@Param pCoeff:指向系数矩阵的指针
@Param i:指向系数矩阵的指针
@Param uiDimension:矩阵维度
返回值 0成功  1失败
********************************************************************************************/
uint8_t MC2_MatrixAddRow(FP64 **ppMatrix, uint16_t i, FP64 pCoeff[], uint16_t length, uint16_t uiDimension)
{
	if (ppMatrix == NULL || uiDimension == 0 || pCoeff == NULL)
	{
		return 1;
	}
	//超过范围返回错误
	if (length >uiDimension+1)
	{
		return 1;
	}
	for (uint16_t j = 0; j < length; j++)
	{
		ppMatrix[i][j] = pCoeff[j];
	}
	return 0;
}


/********************************************************************************************
函数功能：添加整行系数到矩阵的第i行中
@Param ppMatrix:指向系数矩阵的指针
@Param pValue:指向系数矩阵等于右值的指针
@Param uiDimension:矩阵维度
返回值 0成功  1失败
********************************************************************************************/
uint8_t MC2_MatrixAddRvalue(FP64 **ppMatrix, FP64 pValue[], uint16_t uiDimension)
{
	if (ppMatrix == NULL || uiDimension == 0||pValue == NULL)
	{
		return 1;
	}
	for (uint16_t j = 0; j < uiDimension; j++)
	{
		ppMatrix[j][uiDimension] = pValue[j];
	}
	return 0;
}


/********************************************************************************************
函数功能：将系数矩阵的第i行除以指定系数加到第j行,使得第j行的首系数为零
@Param pMatrix:指向指数矩阵的指针
@Param i,j:第i行，第j列
@Param uiDimension:系数矩阵的维度
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC2_MatrixCalBetterElim(FP64 **ppMatrix, uint16_t i, uint16_t j, uint16_t uiDimension)
{
	if (ppMatrix == NULL || uiDimension == 0)
	{
		return 1;
	}
	FP64 Coeff;
	//确认第i行首系数为零
	if (ppMatrix[i][i] == 0.0f)
	{
		//第i行下面首系数非零的行加到第i行
		for (int16_t k = i+1; k < uiDimension; k++)
		{
			if (ppMatrix[k][i] != 0.0f)
			{
				//将第k行加到第i行中
				for (int16_t m = i; m < uiDimension+1; m++)
				{
					ppMatrix[i][m] += ppMatrix[k][m];
				}
				break;
			}
			else
			{
				if (k == uiDimension -1)
				{
					return 2;
				}
			}
		}
	}

	//计算系数
	Coeff = ppMatrix[j][i] / ppMatrix[i][i];
	for (int16_t k = i; k < uiDimension+1; k++)
	{
		//计算系数，再减到下一行
		ppMatrix[j][k] -= ppMatrix[i][k] * Coeff;
	}
	return 0;
}

/********************************************************************************************
函数功能：消元第一步，将系数矩阵转换成上三角矩阵
@Param pMatrix:指向指数矩阵的指针
@Param uiDimension:系数矩阵的维度
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC2_MatrixElimination(FP64 **ppMatrix, uint16_t uiDimension)
{
	if (ppMatrix == NULL || uiDimension == 0)
	{
		return 1;
	}
	//消去
	for (uint16_t i = 0; i < uiDimension ; i++)
	{//第i行运算
		for (uint16_t j = i + 1; j < uiDimension; j++)
		{
			//第j行-第i行*第j行首系数/第i行首系数
			//MC_MatrixCalElim(pMatrix, pValue, i, j, uiDimension);
			MC2_MatrixCalBetterElim(ppMatrix, i, j, uiDimension);
		}
	}

	return 0;
}


/********************************************************************************************
函数功能：消元第二步,上三角矩阵回代求解
@Param pMatrix:指向指数矩阵的指针
@Param pRoot:方程的根
@Param uiDimension:系数矩阵的维度
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC2_MatrixInverseCal(FP64 **ppMatrix, FP64 pRoot[], uint16_t uiDimension)
{
	if (ppMatrix == NULL || pRoot == NULL || uiDimension == 0)
	{
		return 1;
	}
	//回代求解
	FP64 fBackValue = 0;
	for (int16_t i = uiDimension - 1; i >= 0; i--)
	{
		fBackValue = 0;
		//前一个解回代值到下一个公式值的计算
		for (int16_t k = i+1; k < uiDimension; k++)
		{
			fBackValue += ppMatrix[i][k]*pRoot[k];
		}
		//分母为零，返回2
		if (ppMatrix[i][i] == 0.0f)
		{
			return 2;
		}
		pRoot[i] = (ppMatrix[i][uiDimension] - fBackValue) / ppMatrix[i][i];
	}
	return 0;
}

