//================================
//
//texture.cppに必要な宣言[texture.h]
//Author:yuuto shimadu
// 
//================================

#ifndef _TEXTURE_H_ //このマクロ定義がされていなかったら
#define _TEXTURE_H_ //２重インクルード防止のマクロ定義

//ヘッダーのインクルード
#include "main.h"

//テクスチャ管理のクラス
class CTexture
{
public:

	//メンバ関数
	CTexture();									//コンストラクタ
	~CTexture();								//デストラクタ
	void Unload();								//テクスチャの破棄
	int Regist(const char* pTextureName);		//テクスチャ登録
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);	//テクスチャ取得

private:

	//メンバ変数
	static int m_nTextureNumAll;						//テクスチャの総数
	static std::vector<LPDIRECT3DTEXTURE9> m_pTexture;	//テクスチャのポインタ
	static std::map<std::string, int> m_pTexturemap;	//テクスチャ用の連想配列
};

#endif