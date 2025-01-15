//================================
//
//xfile.cppに必要な宣言[xfile.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _XFILE_H_ //このマクロ定義がされていなかったら
#define _XFILE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//Xファイル管理のクラス
class CXfile
{
public:

	//オブジェクトのサイズ
	typedef struct
	{
		D3DXVECTOR3 Max;	//最大値
		D3DXVECTOR3 Min;	//最小値
	}XObjectSize;

	//Xファイル情報の構造体
	typedef struct
	{
		LPD3DXMESH pMesh;							//メッシュへのポインタ
		LPD3DXBUFFER pBuffmat;						//マテリアルへのポインタ
		DWORD dwNumMat;								//マテリアルの数
		std::vector<LPDIRECT3DTEXTURE9> pTexture;	//テクスチャのポインタ
		XObjectSize aSize;							//サイズ構造体
		int nIndex;									//番号
	}XFileInfo;

	//メンバ関数
	CXfile();								//コンストラクタ
	~CXfile();								//デストラクタ
	void Unload();							//Xファイルオブジェクト破棄
	int Regist(const char* pXfileName);		//Xファイルオブジェクト登録
	XFileInfo GetAddress(int nIdx);			//Xファイルオブジェクト取得

private:

	//メンバ関数
	void LoadSize(XFileInfo& pfileinfo);	//サイズの読み込み

	//メンバ変数
	static std::map<std::string, XFileInfo> m_pXfilemap;	//Xファイル用の連想配列
};

#endif