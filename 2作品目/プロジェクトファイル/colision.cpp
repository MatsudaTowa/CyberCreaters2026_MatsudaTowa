//=============================================
//
//当たり判定管理[colision.cpp]
//Auther Matsuda Towa
//
//=============================================
#include "colision.h"

//=============================================
//コンストラクタ
//=============================================
CColision::CColision()
{
}

//=============================================
//デストラクタ
//=============================================
CColision::~CColision()
{
}

//=============================================
//当たり判定_Xチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.x + Asize.x <= Bpos.x - Bsize.x
		&& Apos.x + Asize.x > Bpos.x - Bsize.x)
	{
		if (Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.x - Asize.x >= Bpos.x + Bsize.x
		&& Apos.x - Asize.x < Bpos.x + Bsize.x)
	{
		if (Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//モデルとポリゴン当たり判定_Xチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.x + AMaxpos.x <= Bpos.x - Bsize.x
		&& Apos.x + AMaxpos.x > Bpos.x - Bsize.x)
	{
		if (Aoldpos.z + AMinpos.z < Bpos.z + Bsize.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z - Bsize.z
			&& Aoldpos.y + AMinpos.y < Bpos.y + Bsize.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y - Bsize.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
	}
	else if (Aoldpos.x + AMinpos.x >= Bpos.x + Bsize.x
		&& Apos.x + AMinpos.x < Bpos.x + Bsize.x)
	{
		if (Aoldpos.z + AMinpos.z < Bpos.z + Bsize.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z - Bsize.z
			&& Aoldpos.y + AMinpos.y < Bpos.y + Bsize.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y - Bsize.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//モデル同士当たり判定_Xチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_X(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.x + AMaxpos.x <= Bpos.x + BMinpos.x
		&& Apos.x + AMaxpos.x > Bpos.x + BMinpos.x)
	{
		if (Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
	}
	else if (Aoldpos.x + AMinpos.x >= Bpos.x + BMaxpos.x
		&& Apos.x + AMinpos.x < Bpos.x + BMaxpos.x)
	{
		if (Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//当たり判定_Yチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.y + Asize.y <= Bpos.y - Bsize.y
		&& Apos.y + Asize.y > Bpos.y - Bsize.y)
	{//当たり判定(Y)下
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z)
		{
			return CColision::COLISION::COLISON_UNDER_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.y - Asize.y >= Bpos.y + Bsize.y
		&& Apos.y - Asize.y < Bpos.y + Bsize.y)
	{//当たり判定(Y)上
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.z - Asize.z < Bpos.z + Bsize.z
			&& Aoldpos.z + Asize.z > Bpos.z - Bsize.z)
		{
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//モデルとポリゴン当たり判定_Yチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.y + AMaxpos.y <= Bpos.y - Bsize.y
		&& Apos.y + AMaxpos.y > Bpos.y - Bsize.y)
	{//当たり判定(Y)下
		if (Aoldpos.x + AMinpos.x < Bpos.x + Bsize.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x - Bsize.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + Bsize.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z - Bsize.z)
		{
			CColision::COLISION::COLISON_UNDER_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.y + AMinpos.y >= Bpos.y + Bsize.y
		&& Apos.y + AMinpos.y < Bpos.y + Bsize.y)
	{//当たり判定(Y)上
		if (Aoldpos.x + AMinpos.x < Bpos.x + Bsize.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x - Bsize.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + Bsize.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z - Bsize.z)
		{
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//モデル同士当たり判定_Yチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_Y(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.y + AMaxpos.y <= Bpos.y + BMinpos.y
		&& Apos.y + AMaxpos.y > Bpos.y + BMinpos.y)
	{//当たり判定(Y)下
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z)
		{
			return CColision::COLISION::COLISON_UNDER_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.y + AMinpos.y >= Bpos.y + BMaxpos.y
		&& Apos.y + AMinpos.y < Bpos.y + BMaxpos.y)
	{//当たり判定(Y)上
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.z + AMinpos.z < Bpos.z + BMaxpos.z
			&& Aoldpos.z + AMaxpos.z > Bpos.z + BMinpos.z)
		{
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}


//=============================================
//当たり判定_Zチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 Asize, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.z + Asize.z <= Bpos.z - Bsize.z
		&& Apos.z + Asize.z > Bpos.z - Bsize.z)
	{
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y
			)
		{//当たり判定(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.z - Asize.z >= Bpos.z + Bsize.z
		&& Apos.z - Asize.z < Bpos.z + Bsize.z)
	{
		if (Aoldpos.x - Asize.x < Bpos.x + Bsize.x
			&& Aoldpos.x + Asize.x > Bpos.x - Bsize.x
			&& Aoldpos.y - Asize.y < Bpos.y + Bsize.y
			&& Aoldpos.y + Asize.y > Bpos.y - Bsize.y
			)
		{//当たり判定(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//モデルとポリゴン当たり判定_Zチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 Bsize)
{
	if (Aoldpos.z + AMaxpos.z <= Bpos.z - Bsize.z
		&& Apos.z + AMaxpos.z > Bpos.z - Bsize.z)
	{
		if (Aoldpos.x + AMinpos.x < Bpos.x + Bsize.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x - Bsize.x
			&& Aoldpos.y + AMinpos.y < Bpos.y + Bsize.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y - Bsize.y
			)
		{//当たり判定(Z)
			return CColision::COLISION::COLISON_X;

		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.z + AMinpos.z >= Bpos.z + Bsize.z
		&& Apos.z + AMinpos.z < Bpos.z + Bsize.z)
	{
		if (Aoldpos.x + AMinpos.x < Bpos.x + Bsize.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x - Bsize.x
			&& Aoldpos.y + AMinpos.y < Bpos.y + Bsize.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y - Bsize.y
			)
		{//当たり判定(Z)
			CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//モデル同士当たり判定_Zチェック関数
//=============================================
CColision::COLISION CColision::CheckColision_Z(D3DXVECTOR3 Aoldpos, D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Aoldpos.z + AMaxpos.z <= Bpos.z + BMinpos.z
		&& Apos.z + AMaxpos.z > Bpos.z + BMinpos.z)
	{
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y
			)
		{//当たり判定(Z)
			return CColision::COLISION::COLISON_Z;

		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Aoldpos.z + AMinpos.z >= Bpos.z + BMaxpos.z
		&& Apos.z + AMinpos.z < Bpos.z + BMaxpos.z)
	{
		if (Aoldpos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Aoldpos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Aoldpos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Aoldpos.y + AMaxpos.y > Bpos.y + BMinpos.y
			)
		{//当たり判定(Z)
			return CColision::COLISION::COLISON_Z;

		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//ポリゴンとモデル当たり判定チェック関数
//=============================================
CColision::COLISION CColision::CheckItemColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.x + ASize.x > Bpos.x + BMinpos.x
		&& Apos.x - ASize.x < Bpos.x + BMaxpos.x)
	{
		if (Apos.y - ASize.y < Bpos.y + BMaxpos.y
			&& Apos.y + ASize.y > Bpos.y + BMinpos.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	//if (Apos.z + ASize.z > Bpos.z + BMinpos.z
	//	&& Apos.z - ASize.z < Bpos.z + BMaxpos.z)
	//{
	//	if (Apos.x - ASize.x < Bpos.x + BMaxpos.x
	//		&& Apos.x + ASize.x > Bpos.x + BMinpos.x
	//		&& Apos.y - ASize.y < Bpos.y + BMaxpos.y
	//		&& Apos.y + ASize.y > Bpos.y + BMinpos.y
	//		)
	//	{//当たり判定(Z)
	//		return CColision::COLISION::COLISON_Z;
	//	}
	//	else
	//	{
	//		return CColision::COLISION::COLISON_NONE;
	//	}
	//}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

CColision::COLISION CColision::CheckItemFillColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.y - ASize.y < Bpos.x + BMaxpos.x)
	{
		if (Apos.z - ASize.z< Bpos.z + BMaxpos.z
			&& Apos.z + ASize.z > Bpos.z + BMinpos.z
			&& Apos.y - ASize.y < Bpos.y + BMaxpos.y
			&& Apos.y + ASize.y > Bpos.y + BMinpos.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_TOP_Y;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
}


//=============================================
//集中距離判定とモデル当たり判定チェック関数
//=============================================
CColision::COLISION CColision::CheckFlow_RangeColision(D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.x + AMaxpos.x > Bpos.x + BMinpos.x
		&& Apos.x + AMinpos.x < Bpos.x + BMaxpos.x)
	{
		if (Apos.z + AMinpos.z< Bpos.z + BMaxpos.z
			&& Apos.z + AMaxpos.z > Bpos.z + BMinpos.z
			&& Apos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Apos.y + AMaxpos.y > Bpos.y + BMinpos.y)
		{//当たり判定(X)
			return CColision::COLISION::COLISON_X;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else if (Apos.z + AMaxpos.z > Bpos.z + BMinpos.z
		&& Apos.z + AMinpos.z < Bpos.z + BMaxpos.z)
	{
		if (Apos.x + AMinpos.x < Bpos.x + BMaxpos.x
			&& Apos.x + AMaxpos.x > Bpos.x + BMinpos.x
			&& Apos.y + AMinpos.y < Bpos.y + BMaxpos.y
			&& Apos.y + AMaxpos.y > Bpos.y + BMinpos.y
			)
		{//当たり判定(Z)
			return CColision::COLISION::COLISON_Z;
		}
		else
		{
			return CColision::COLISION::COLISON_NONE;
		}
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

