//======================================
//
//	モデルの処理[model.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ヘッダーのインクルード
#include "model.h"
#include "tree.h"
#include "fence.h"
#include "venue.h"

//============================
//モデルのクリエイト
//============================
CModel* CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, MODEL_TYPE type)
{
	//種類に応じて動的確保
	CModel* pModel = nullptr;

	//引数のオブジェクトを生成
	switch (type)
	{
	case MODEL_TYPE::MODEL_TYPE_TREE:
		pModel = new CTree;
		break;

	case MODEL_TYPE::MODEL_TYPE_FENCE:
		pModel = new CFence;
		break;

	case MODEL_TYPE::MODEL_TYPE_VENUE:
		pModel = new CVenue;
		break;

	default:
		assert(true);
		break;
	}

	//初期化
	pModel->Init();

	//パラメータの設定
	pModel->SetPos(pos);					//位置
	pModel->SetRot(rot);					//向き

	//設定した情報を返す
	return pModel;
}