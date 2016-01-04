#pragma once



/*!
 * \class	CGObject
 *
 * \brief	The graphic object.
 *
 * \author	Pedro
 * \date	30/12/2015
 */

class CGObject
{
	
public:
	

	gutl::CVector m_position;
	CRect m_rBox;


	CGObject();
	~CGObject();

	virtual void Prepare() = 0;
	virtual void Draw() = 0;

	virtual	int 
	Width()const { return  m_rBox.Width(); }
	virtual int 
	Height()const { return m_rBox.Height(); }

	virtual	void 
	SetPos(int x, int y){

		m_rBox.left = x; m_rBox.top = y;
		m_position = gutl::CVector(x, y, 0);
	}

	virtual	void 
	SetSize(int w, int h) { m_rBox.right = w; m_rBox.bottom = h; }

};

