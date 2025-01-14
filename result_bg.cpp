//======================================
//
//	îwåiÇÃèàóù[result_bg.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ÉwÉbÉ_Å[ÇÃÉCÉìÉNÉãÅ[Éh
#include "result_bg.h"

//íËêî
const std::string CResult_Bg::TEXTURE_PATH = "data\\TEXTURE\\result001.png";

//============================
//îwåiÇÃÉRÉìÉXÉgÉâÉNÉ^
//============================
CResult_Bg::CResult_Bg(int nPriority) : CObject2D(nPriority)
{

}

//============================
//îwåiÇÃÉfÉXÉgÉâÉNÉ^
//============================
CResult_Bg::~CResult_Bg()
{

}

//============================
//îwåiÇÃèâä˙âª
//============================
HRESULT CResult_Bg::Init()
{
	//èâä˙âª
	CObject2D::Init();

	return S_OK;
}

//============================
//îwåiÇÃèIóπèàóù
//============================
void CResult_Bg::Uninit()
{
	CObject2D::Uninit();
}

//============================
//îwåiÇÃçXêV
//============================
void CResult_Bg::Update()
{
	CObject2D::Update();
}

//============================
//îwåiÇÃï`âÊ
//============================
void CResult_Bg::Draw()
{
	//ï`âÊèàóù
	CObject2D::Draw(TEXTURE_PATH.c_str());
}

//============================
//îwåiÇÃÉNÉäÉGÉCÉg
//============================
CResult_Bg* CResult_Bg::Create()
{
	//É|ÉCÉìÉ^ópÇÃïœêî
	CResult_Bg* pResult_Bg;

	//ÉÅÉÇÉäÇÃämï€
	pResult_Bg = new CResult_Bg;

	//èâä˙âª
	pResult_Bg->Init();
	pResult_Bg->SetPos({640.0f, 360.0f, 0.0f});	//à íu
	pResult_Bg->SetSize({ WIDTH, HEIGHT, 0.0f });	//ÉTÉCÉY

	return pResult_Bg;
}