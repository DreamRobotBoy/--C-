#include "MC_Data_Manage.h"


/********************************************************************************************
函数功能：创建数据链表矩阵
@Param Param1:
@Param Param2:
@Param Param3:
返回值
********************************************************************************************/
MC_Matrix_t *MC_MatrixCreate()
{
	MC_Matrix_t *pMatrix = (MC_Matrix_t*)malloc(sizeof(MC_Matrix_t));
	pMatrix->pNextData = NULL;
	return pMatrix;
}

/********************************************************************************************
函数功能：打印数据链表矩阵
@Param Param1:
@Param Param2:
@Param Param3:
返回值
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
函数功能：清除数据链表矩阵
@Param Param1:
@Param Param2:
@Param Param3:
返回值
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
函数功能：向数据链表矩阵添加数据
@Param Param1:
@Param Param2:
@Param Param3:
返回值 0成功添加 1添加失败
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
函数功能：数据链表矩阵删除指定index链表
@Param Param1:
@Param Param2:
@Param Param3:
返回值 0删除成功，1删除失败
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
函数功能：数据链表矩阵插入指定index链表
@Param Param1:
@Param Param2:
@Param Param3:
返回值 0删除成功，1删除失败
********************************************************************************************/
uint8_t MC_MatrixInsertIndex(MC_Matrix_t *pMatrix, uint16_t index, FP64 fData)
{


	return 0;
}

/********************************************************************************************
函数功能：数据链表查找指定系数
@Param Param1:
@Param Param2:
@Param Param3:
返回值 0删除成功，1删除失败
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
函数功能：数据链表矩阵选主元
@Param Param1:
@Param Param2:
@Param Param3:
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC_MatrixSelectPivot(MC_Matrix_t **pMatrix,FP64 pValue[], uint16_t uiDimension)
{
	if (pMatrix == NULL || uiDimension == 0)
	{
		return 1;
	}
	//动态分配数组指针
	MC_Matrix_t **pAddr = (MC_Matrix_t**)calloc(uiDimension, sizeof(MC_Matrix_t*));
	MC_Matrix_t **pAddrTemp = (MC_Matrix_t**)calloc(uiDimension, sizeof(MC_Matrix_t*));
	MC_Matrix_t *pCur;
	pCur = *pMatrix;
	int16_t j = 0;
	//检索并保存每行首指针
	for (int16_t i = 1; i <= uiDimension*uiDimension; i++)
	{
		if (pCur->pNextData == NULL)
		{
			return 1;
		}
		if (i%uiDimension == 1)
		{
			pAddr[j] = pCur;
			pAddrTemp[j++] = pCur;
		}
		//pNext = pCur->pNextData;
		pCur = pCur->pNextData;
	}
	//把最后一个内存释放
	free(pCur);

	//主元排序
	FP64 fMaxValue = 0;	//最大值
	int16_t fMaxRowIndex = 0;//最大行序号
	FP64 ValueTemp = 0;
	for (int16_t i = 0; i < uiDimension; i++)
	{
		fMaxValue = pAddrTemp[i]->fData;
		fMaxRowIndex = i;
		//当前值等于0
		if (fMaxValue == 0.0f)
		{
			//第i行与其下面行进行大小比较，确定最大行，再换行
			for (int16_t k = i + 1; k < uiDimension; k++)
			{
				if (pAddrTemp[k]->fData != 0.0f)
				{
					fMaxValue = pAddrTemp[k]->fData;
					fMaxRowIndex = k;
					break;
				}
			}
		}

		//最大行替换至第i行
		if (fMaxValue != pAddrTemp[i]->fData)
		{
			//先换行，再链接
			pCur = pAddr[i];
			pAddr[i] = pAddr[fMaxRowIndex];
			pAddr[fMaxRowIndex] = pCur;

			//临时变量也需要换行
			pCur = pAddrTemp[i];
			pAddrTemp[i] = pAddr[fMaxRowIndex];
			pAddrTemp[fMaxRowIndex] = pCur;

			//换等于右值
			ValueTemp = pValue[i];
			pValue[i] = pValue[fMaxRowIndex];
			pValue[fMaxRowIndex] = ValueTemp;		
		}
		//临时保存
		//向前推进一个节点
		for (int16_t m = i + 1; m < uiDimension; m++)
		{
			pAddrTemp[m] = pAddrTemp[m]->pNextData;
		}
	}

	//重新链接
	pCur = pAddr[0];
	for (int16_t m = 1; m < uiDimension; m++)
	{
		for (int16_t k = 0; k < uiDimension - 1; k++)
		{
			pCur = pCur->pNextData;
		}
		pCur->pNextData = pAddr[m];
		pCur = pAddr[m];
	}
	for (int16_t k = 0; k < uiDimension-1; k++)
	{
		pCur = pCur->pNextData;
	}
	//补充最后一个内存
	pCur->pNextData = (MC_Matrix_t*)malloc(sizeof(MC_Matrix_t));
	pCur->pNextData->pNextData = NULL;
	*pMatrix = pAddr[0];
	//释放动态数组内存
	free(pAddr);
	free(pAddrTemp);
	return 0;
}


/********************************************************************************************
函数功能：数据链表矩阵//第j行-第i行*第j行首系数/第i行首系数
@Param Param1:
@Param Param2:
@Param Param3:
返回值 0成功，1失败
********************************************************************************************/
uint8_t MC_MatrixCalElim(MC_Matrix_t **pMatrix, FP64 pValue[], uint16_t i, uint16_t j, uint16_t uiDimension)
{
	if (pMatrix == NULL || pValue == NULL)
	{
		return 1;
	}
	FP64 Coeff, Mol, Den;
	MC_Matrix_t *pRow_i = NULL, *pRow_j = NULL, *pCur, *pNext, *pCur1, *pNext1;
	pCur = *pMatrix;
	//检索第i与j行首指针
	for (uint16_t k = 1; k < uiDimension*(j - 1) + i; k++)
	{
		//检索到第i行首指针
		if (k == uiDimension*(i - 1) + i)
		{
			pRow_i = pCur;
			Den = pCur->fData;
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
	for (uint16_t k = i; k <= uiDimension; k++)
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
函数功能：更好完美的数据链表矩阵//第j行-第i行*第j行首系数/第i行首系数
@Param Param1:
@Param Param2:
@Param Param3:
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
函数功能：数据链表矩阵消去运算
@Param Param1:
@Param Param2:
@Param Param3:
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
函数功能：数据链表矩阵求根运算
@Param Param1:
@Param Param2:
@Param Param3:
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
