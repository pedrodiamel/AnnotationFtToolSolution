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

	int Width()const { return  m_rBox.Width(); }
	int Height()const { return m_rBox.Height(); }



};

