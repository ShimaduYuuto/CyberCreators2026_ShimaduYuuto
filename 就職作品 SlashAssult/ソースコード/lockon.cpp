//======================================
//
//	ƒƒbƒNƒIƒ“ˆ—[lockon.cpp]
//	Author : Yuuto Shimadu
//
//======================================

//ƒwƒbƒ_[‚ÌƒCƒ“ƒNƒ‹[ƒh
#include "lockon.h"
#include "camera.h"
#include "manager.h"
#include "game.h"

//============================
//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
//============================
CLockon::CLockon() : 
	m_pTarget(nullptr),
	m_pMark(nullptr),
	m_LockonList(),
	m_pRushUi(nullptr)
{
	m_LockonList.clear();
}

//============================
//ƒfƒXƒgƒ‰ƒNƒ^
//============================
CLockon::~CLockon()
{

}

//============================
//‰Šú‰»
//============================
HRESULT CLockon::Init()
{
	return S_OK;
}

//============================
//I—¹ˆ—
//============================
void CLockon::Uninit()
{
	//ƒ}[ƒN‚ð¶¬
	if (m_pMark != nullptr)
	{
		m_pMark->Uninit();
		m_pMark = nullptr;
	}

	//Á‹Žˆ—
	delete this;
}

//============================
//XV
//============================
void CLockon::Update()
{
	//ƒƒbƒNƒIƒ“‘ÎÛ‚ª‰æ–Ê“à‚É‘¶Ý‚·‚é‚©‚ðŠm”F
	if (m_pMark != nullptr)
	{
		//‚¢‚È‚©‚Á‚½‚ç”jŠü
		if (!CManager::GetInstance()->GetCamera()->GetViewObject(m_pMark->GetPos()))
		{
			//ˆó‚Æ‘ÎÛ‚Ìƒ|ƒCƒ“ƒ^‚ð”jŠü
			m_pMark->Uninit();
			m_pMark = nullptr;
			m_pTarget = nullptr;
			
		}
		else
		{
			return;
		}
	}

	//ˆó‚ª‚È‚¢‚È‚ç
	if (m_pMark == nullptr)
	{
		//ƒŠƒXƒg‚É‚¢‚È‚¢‚È‚ç”²‚¯‚é
		if (m_LockonList.size() == 0)
		{
			return;
		}

		//Å‰‚Ì“G‚ðŽæ“¾
		auto iter = m_LockonList.begin();
		m_pTarget = *iter;
		m_pMark = CLockonMark::Create(MARK_RADIUS, &m_pTarget->GetCollision()->GetPos());
	}
}

//============================
//ƒNƒŠƒGƒCƒg
//============================
CLockon* CLockon::Create()
{
	//ƒ|ƒCƒ“ƒ^—p‚Ì•Ï”
	CLockon* pLockon = nullptr;

	//¶¬
	pLockon = new CLockon;

	//‰Šú‰»
	pLockon->Init();

	return pLockon;
}

//============================
//“o˜^
//============================
void CLockon::Regist(CEnemy* enemy)
{
	//•Ï”éŒ¾
	bool bRegist = false;

	//“G‚ÌŽü‰ñ
	for (auto& iter : m_LockonList)
	{
		//‚·‚Å‚É“o˜^‚µ‚Ä‚¢‚é‚È‚ç“o˜^‚µ‚È‚¢
		if (iter == enemy)
		{
			bRegist = true;
			break;
		}
	}

	//“o˜^‚µ‚Ä‚¢‚È‚¢‚È‚ç“o˜^
	if (!bRegist)
	{
		m_LockonList.push_back(enemy);
	}
}

//============================
//íœ
//============================
void CLockon::Erase(CEnemy* enemy)
{
	//“G‚ÌŽü‰ñ
	for (auto& iter : m_LockonList)
	{
		//‚·‚Å‚É“o˜^‚µ‚Ä‚¢‚é‚È‚ç“o˜^‚µ‚È‚¢
		if (iter == enemy)
		{
			//“G‚Ìî•ñ‚ðíœ
			if (m_pTarget == enemy)
			{
				m_pTarget = nullptr;
				m_pMark->Uninit();
				m_pMark = nullptr;
			}
			m_LockonList.remove(iter);
			break;
		}
	}
}