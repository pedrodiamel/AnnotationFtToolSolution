
#include "stdafx.h"
#include "AppManager.h"


CAppManagers* CAppManagers::m_instancia = 0;

CAppManagers::CAppManagers(void)
	: m_numFolder(0)
	, m_xdcIdx(0)
{
	if(m_instancia)
	throw "Esta clase solo admite una instancia";
	m_instancia = this;
}


CAppManagers::~CAppManagers(void)
{



}

CAppManagers* CAppManagers::getInstance(){

	if(!m_instancia)
		m_instancia = new CAppManagers();
	return m_instancia;
}

