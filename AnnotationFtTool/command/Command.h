
#pragma once

#include <list>
#include <assert.h>


namespace pt{

class CCommandNotify
{
public:
	
	virtual void onComplete(const std::string &info){}
	virtual void onProgress(unsigned int i, const std::string &msg){}
	virtual void onError(const std::string &err){}

};


/*!
 * \class	CCommand
 *
 * \brief	A command pattern.
 *
 * \author	Pedro
 * \date	02/01/2016
 */

class CCommand{

public:
	
	CCommand();
	virtual ~CCommand();
	virtual void Ejecutar() = 0;
	virtual void addNotify(CCommandNotify *notify){ assert(notify); m_notify = notify;}


protected:
	
	
	CCommandNotify *m_notify;
	std::string s_msg;
	unsigned int i_progress;

	bool notify()const{return m_notify!=nullptr;} 
	void notifyComplete(const std::string &info){ 
		
		if(notify()) 
		m_notify->onComplete(info); 
		i_progress = 100;
		s_msg = info;

	}

	void notifyProgress(const unsigned i, const std::string &msg)
	{ 
		if(notify()) 
		m_notify->onProgress(i,msg); 
		i_progress = i;
		s_msg = msg;
	}

	void notifyError(const std::string &err)
	{ 
		if(notify()) 
		m_notify->onError(err); 
		s_msg = err;
	}

};




template <class Receptor>
class CommandsSimple 
	: public CCommand {

public:
	
	typedef void (Receptor::*Accion)(); //ptr func accion
	CommandsSimple(Receptor* r, Accion a):
	_receptor(r), _accion(a){}
	virtual void Ejecutar(){	
		(_receptor->*_accion)();
	}

private:

	Accion _accion;
	Receptor* _receptor;

};


class SequenceCommand 
	: public CCommand {

public:
	SequenceCommand(){}
	virtual ~SequenceCommand(){}

	virtual void Anadir(CCommand* cmd){
		_commands.push_back( cmd );
	}
	virtual void Eliminar(CCommand* cmd){
	
		_commands.remove( cmd );
	}

	virtual void Ejecutar(){
	
		std::list<CCommand*>::iterator i;
		for( i= _commands.begin(); i!=_commands.end(); i++)
			(*i)->Ejecutar();

	}

private:
	std::list<CCommand*> _commands;

};

}



