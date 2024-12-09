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
	//if (Aoldpos.x + AMaxpos.x <= Bpos.x
	//	&& Apos.x + AMaxpos.x > Bpos.x
	//	&& Apos.z + AMinpos.z > Bpos.z - Bsize.z
	//	&& Apos.z + AMaxpos.z < Bpos.z + Bsize.z)
	//{
	//	return CColision::COLISION::COLISON_X;
	//}
	//else if (Aoldpos.x + AMaxpos.x >= Bpos.x
	//	&& Apos.x + AMaxpos.x < Bpos.x
	//	&& Apos.z + AMinpos.z > Bpos.z - Bsize.z
	//	&& Apos.z + AMaxpos.z < Bpos.z + Bsize.z)
	//{
	//	return CColision::COLISION::COLISON_X;
	//}
	//else
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
	if (Aoldpos.z + AMaxpos.z <= Bpos.z
		&& Apos.z + AMaxpos.z > Bpos.z
		&&Apos.x + AMinpos.x > Bpos.x - Bsize.x
		&& Apos.x + AMaxpos.x < Bpos.x + Bsize.x)
	{
		return CColision::COLISION::COLISON_Z;
	}
	else if (Aoldpos.z + AMaxpos.z >= Bpos.z
		&& Apos.z + AMaxpos.z < Bpos.z
		&& Apos.x + AMinpos.x > Bpos.x - Bsize.x
		&& Apos.x + AMaxpos.x < Bpos.x + Bsize.x)
	{
		return CColision::COLISION::COLISON_Z;
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
//モデル球の当たり判定チェック関数 TODO:ガバガバなので修正
//=============================================
CColision::COLISION CColision::CheckColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 AMinpos, D3DXVECTOR3 AMaxpos, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	//距離を求める
	D3DXVECTOR3 Length = Apos - Bpos;

	float CenterDistance = sqrtf((Length.x * Length.x) + (Length.y * Length.y) + (Length.z * Length.z));

	//パーツの中心を求める
	D3DXVECTOR3 originA = (AMaxpos - AMinpos) * 0.5f;

	//パーツの中心を求める
	D3DXVECTOR3 originB = (BMaxpos - BMinpos) * 0.5f;

	float Radius = (originB.x + originA.x) + (originB.y + originA.y) + (originB.z + originA.z) * 0.5f;

	if (CenterDistance <= Radius)
	{
		// 正規化（単位ベクトル化）
		D3DXVECTOR3 normalizedVec = Length / CenterDistance;

		//絶対値で度の向きに当たったか取得
		if (fabs(normalizedVec.x) > fabs(normalizedVec.y) && fabs(normalizedVec.x) > fabs(normalizedVec.z)) 
		{
			return CColision::COLISION::COLISON_X;
		}
		else if (fabs(normalizedVec.y) > fabs(normalizedVec.x) && fabs(normalizedVec.y) > fabs(normalizedVec.z))
		{
			return CColision::COLISION::COLISON_NONE;
		}
		else 
		{
			return CColision::COLISION::COLISON_Z;
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
CColision::COLISION CColision::CheckPolygonModelColisionSphere(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	//距離を求める
	D3DXVECTOR3 Length = Apos - Bpos;

	float CenterDistance = sqrtf((Length.x*Length.x) + (Length.y * Length.y) + (Length.z * Length.z));

	//パーツの中心を求める
	D3DXVECTOR3 origin = (BMaxpos - BMinpos) * 0.5f;

	float Radius = (ASize.x + origin.x) + (ASize.y + origin.y) + (ASize.z + origin.z) * 0.5f;

	if (CenterDistance <= Radius)
	{
		return COLISION_CIRCLE;
	}
	else
	{
		return CColision::COLISION::COLISON_NONE;
	}
}

//=============================================
//ポリゴンとモデル当たり判定チェックX
//=============================================
CColision::COLISION CColision::CheckPolygonModelColision_X(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.x + ASize.x > Bpos.x + BMinpos.x
		&& Apos.x - ASize.x < Bpos.x + BMaxpos.x)
	{
		if (Apos.z - ASize.z < Bpos.z + BMaxpos.z
			&& Apos.z + ASize.z > Bpos.z + BMinpos.z
			&& Apos.y - ASize.y < Bpos.y + BMaxpos.y
			&& Apos.y + ASize.y > Bpos.y + BMinpos.y
			)
		{
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
//ポリゴンとモデル当たり判定チェック関数Z
//=============================================
CColision::COLISION CColision::CheckPolygonModelColision_Z(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
{
	if (Apos.z + ASize.z > Bpos.z + BMinpos.z
		&& Apos.z - ASize.z < Bpos.z + BMaxpos.z)
	{
		if (Apos.x - ASize.x < Bpos.x + BMaxpos.x
			&& Apos.x + ASize.x > Bpos.x + BMinpos.x
			&& Apos.y - ASize.y < Bpos.y + BMaxpos.y
			&& Apos.y + ASize.y > Bpos.y + BMinpos.y
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
//ポリゴンとモデル当たり判定チェック関数Z
//=============================================
CColision::COLISION CColision::CheckPolygonFillColision(D3DXVECTOR3 Apos, D3DXVECTOR3 ASize, D3DXVECTOR3 Bpos, D3DXVECTOR3 BMinpos, D3DXVECTOR3 BMaxpos)
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
//レイとオブジェクトの当たり判定 TODO:理解しろ
//=============================================
bool CColision::CheckIntersectRay(const D3DXVECTOR3& rayStart, const D3DXVECTOR3& rayDir, const D3DXVECTOR3& boxMin, const D3DXVECTOR3& boxMax, float MaxDistance)
{
	// オブジェクトとの交差範囲を計算するための変数
	float Cross_min = (boxMin.x - rayStart.x) / rayDir.x;
	float Cross_max = (boxMax.x - rayStart.x) / rayDir.x;

	if (Cross_min > Cross_max)
	{
		std::swap(Cross_min, Cross_max); // 進行方向から見てminのほうがmaxよりデカかったら入れ替える
	}

	// y軸に沿った交差範囲を計算
	float Cross_y_min = (boxMin.y - rayStart.y) / rayDir.y;
	float Cross_y_max = (boxMax.y - rayStart.y) / rayDir.y;

	if (Cross_y_min > Cross_y_max)
	{
		std::swap(Cross_y_min, Cross_y_max);  // 進行方向から見てminのほうがmaxよりデカかったら入れ替える
	}

	// 重なる範囲を更新
	Cross_min = max (Cross_min, Cross_y_min);
	Cross_max = min (Cross_max, Cross_y_max);

	// z軸に沿った交差範囲を計算
	float Cross_z_min = (boxMin.z - rayStart.z) / rayDir.z;
	float Cross_z_max = (boxMax.z - rayStart.z) / rayDir.z;

	if (Cross_z_min > Cross_z_max) 
	{
		std::swap(Cross_z_min, Cross_z_max);  // 進行方向から見てminのほうがmaxよりデカかったら入れ替える
	}
	// x, y, z 軸全てで交差範囲が重なるかを確認
	if ((Cross_min > Cross_z_max) || (Cross_z_min > Cross_max) || Cross_min > MaxDistance)
	{
		return false;
	}

	return true;
}

