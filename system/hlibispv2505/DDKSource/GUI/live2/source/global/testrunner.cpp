#include "testrunner.hpp"
#include "objectregistry.hpp"
#include "capturegalleryitem.hpp"

#include "ispc/ModuleDSC.h"
#include "ispc/ModuleESC.h"
#include "ispc/ModuleAWS.h"

#include <iomanip>

#define COMMAND_DELAY 100000

#include <QFileInfo>

//
// Public Functions
//

VisionLive::TestRunner::TestRunner(ObjectRegistry *objReg, QThread *parent): QThread(parent)
{
	_continueRun = false;

	_connected = false;

    _paused = false;

	_pObjReg = objReg;
}

VisionLive::TestRunner::~TestRunner()
{
}

void VisionLive::TestRunner::clearCommands() 
{ 
	_commands.clear(); 
}

void VisionLive::TestRunner::addCommand(const QString &command) 
{
	_commands.push_back(command); 
}

void VisionLive::TestRunner::startTest()
{
	_continueRun = true;

	start();
}

void VisionLive::TestRunner::stopTest()
{
	_continueRun = false;
}

void VisionLive::TestRunner::setConnected(bool connected)
{
	_connectedLock.lock();
	_connected = connected;
	_connectedLock.unlock();
}

bool VisionLive::TestRunner::isConnected()
{
	bool ret;
	_connectedLock.lock();
	ret = _connected;
	_connectedLock.unlock();
	return ret;
}

//
// Protected Functions
//

void VisionLive::TestRunner::run()
{
	unsigned int index = 0;

	while((index < _commands.size()) && (_continueRun))
	{
		QString command = _commands[index];

		if(command.isEmpty()) continue;

		emit commandRun(command, index);

		QStringList words = command.split(" ", QString::SkipEmptyParts);

		TestCommandResult res;

		res = processCommand(words);
		if(!evaluateResult(command, index, res)) break;

		index++;

		usleep(COMMAND_DELAY);
	}

	emit testFinished();
}

//
// Private Functions
//

VisionLive::Type VisionLive::TestRunner::whatsThis(const QString &param)
{
	Type ret;

	QMap<QString, std::pair<QObject *, QString> >::const_iterator it = _pObjReg->find(param);

	if(it == _pObjReg->end())
	{
        if (Algorithms::isInt(param))
		{
			ret = INT;
		}
        else if (Algorithms::isDouble(param))
		{
			ret = DOUBLE;
		}
		else
		{
			ret = STRING;
		}
	}
	else
	{
		ret = Algorithms::getObjectType((*it).first);
	}

	emit logMessage(param + " is " + Algorithms::getTypeName(ret), tr("TestRunner::executeCompare"));
	return ret;
}

template<typename T> T VisionLive::TestRunner::getValue(Type paramType, QString param)
{
	QMap<QString, std::pair<QObject *, QString> >::const_iterator objectIt;

	switch(paramType)
	{
	case INT:
        return param.toInt();
	case DOUBLE:
        return param.toDouble();
	case QCHECKBOX:
		objectIt = _pObjReg->find(param);
		return ((QCheckBox *)(*objectIt).first)->isChecked()? 1 : 0;
	case QRADIOBUTTON:
		objectIt = _pObjReg->find(param);
		return ((QRadioButton *)(*objectIt).first)->isChecked()? 1 : 0;
	case QSPINBOX:
		objectIt = _pObjReg->find(param);
		return ((QSpinBox *)(*objectIt).first)->value();
	case QDOUBLESPINBOX:
		objectIt = _pObjReg->find(param);
		return ((QDoubleSpinBox *)(*objectIt).first)->value();
	case QCOMBOBOX:
		objectIt = _pObjReg->find(param);
		return ((QComboBox *)(*objectIt).first)->currentIndex();
	case QACTION:
		objectIt = _pObjReg->find(param);
		return ((QAction *)(*objectIt).first)->isChecked();
	}

	return 0;
}

template<> QString VisionLive::TestRunner::getValue(Type paramType, QString param)
{
	QMap<QString, std::pair<QObject *, QString> >::const_iterator objectIt;

	switch(paramType)
	{
	case STRING:
		return param;
	case QLINEEDIT:
		objectIt = _pObjReg->find(param);
		return ((QLineEdit *)(*objectIt).first)->text();
	case QLABEL:
		objectIt = _pObjReg->find(param);
		return ((QLabel *)(*objectIt).first)->text();
	case QTEXTEDIT:
		objectIt = _pObjReg->find(param);
		return ((QTextEdit *)(*objectIt).first)->toPlainText();
	}

	return "";
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::processCommand(QStringList command)
{
	TestCommandResult res;

	if(command[0] == "LOG" && command.size() >= 2)
	{
		res = executeLog(command[1]);
	}
	else if(command[0] == "STOP")
	{
		res = executeStop();
	}
	else if(command[0] == "CLICK" && command.size() >= 2)
	{
		res = executeClick(command[1]);
	}
	else if(command[0] == "OBJEXIST" && command.size() >= 2)
	{
		res = executeObjExist(command[1]);
	}
	else if(command[0] == "FILEEXIST" && command.size() >= 2)
	{
		res = executeFileExist(command[1]);
	}
	else if(command[0] == "WAIT" && command.size() >= 2)
	{
		res = executeWait(command[1]);
	}
	else if(command[0] == "SET" && command.size() >= 3)
	{
		res = executeSet(command[1], command[2]);
	}
	else if(command[0] == "CALL" && command.size() >= 2)
	{
		if(((command.contains("ELSE"))? command.indexOf("ELSE"):command.size()) == 2) 
		{
			res = executeCall(command[1]);
		}
		else if(((command.contains("ELSE"))? command.indexOf("ELSE"):command.size()) == 3) 
		{
			res = executeCall(command[1], command[2]);
		}
		else if(((command.contains("ELSE"))? command.indexOf("ELSE"):command.size()) == 4) 
		{
			res = executeCall(command[1], command[2], command[3]);
		}
	}
	else if(command.size() >= 3 && (command[1] == "<" || command[1] == ">" || command[1] == "==" || command[1] == "!=" || command[1] == "<=" || command[1] == ">="))
	{
		res = executeCompare(command[1], command[0], command[2]);
	}
	else if(command[0] == "IF" && command.size() >= 5 && (command[3] == "THEN" || command[4] == "THEN"))
	{
		command.erase(command.begin()); // Erase IF word
		res = processCommand(command); // Process again

		// Check result
		if(res.executedProperly)
		{
			if(res.result == TEST_PASS) 
			{
				emit logMessage(tr("IF statement returned TRUE!"), tr("TestRunner::processCommand()"));
				command.erase(command.begin(), command.begin() + command.indexOf("THEN") + 1); // Erase all up to THEN inclusive
				res = processCommand(command); // Process again
			}
			else
			{
				emit logMessage(tr("IF statement returned FALSE!"), tr("TestRunner::processCommand()"));
				if(command.contains("ELSE"))
				{
					command.erase(command.begin(), command.begin() + command.indexOf("ELSE") + 1); // Erase all up to ELSE inclusive
					res = processCommand(command); // Process again
				}
				else 
				{
					emit logMessage(tr("IF statement doesn't contain ELSE!"), tr("TestRunner::processCommand()"));
					res.result = TEST_PASS; // IF statement doesn't block
				}
			}
		}
	}
	else
	{
		res.executedProperly = false;
	}

	return res;
}

bool VisionLive::TestRunner::evaluateResult(const QString &command, int index, TestCommandResult &result)
{
	if(result.stopTest)
	{
		emit commandPass(command, index);
		return false;
	}
	else if(result.executedProperly)
	{
		if(result.result != TEST_PASS) 
		{
			emit commandFail(command, index);
		}
		else
		{
			emit commandPass(command, index);
		}
	}
	else
	{
		emit commandBroken(command, index);
		return false;
	}

	return true;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeLog(const QString &text)
{
	TestCommandResult res;

	emit logMessage(text, tr("TestRunner::executeLog"));

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeStop()
{
	TestCommandResult res;

	res.stopTest = true;

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeClick(const QString &obj)
{
	TestCommandResult res;

	Type param1Type = whatsThis(obj);

	if(param1Type != QPUSHBUTTON && param1Type != QRADIOBUTTON && param1Type != QCHECKBOX && param1Type != QACTION)
	{
		emit logMessage(obj + tr(" is not a clickable type object!"), tr("TestRunner::executeClick()"));
		res.executedProperly = false;
		return res;
	}
	
	QMap<QString, std::pair<QObject *, QString> >::const_iterator it = _pObjReg->find(obj);
	if(it != _pObjReg->end())
	{
		if((*it).first) 
		{
			if(param1Type == QPUSHBUTTON || param1Type == QRADIOBUTTON || param1Type == QCHECKBOX)
			{
				emit ((QAbstractButton *)((*it).first))->click();
			}
			else if(param1Type == QACTION)
			{
				emit triggerAction((QAction *)(*it).first);
			}
		}
		else
		{
			emit logMessage(obj + tr(" doesn't exists!"), tr("TestRunner::executeClick()"));
			res.executedProperly = false;
		}
	}

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeObjExist(const QString &obj)
{
	TestCommandResult res;

	QMap<QString, std::pair<QObject *, QString> >::const_iterator it = _pObjReg->find(obj);
	if(it == _pObjReg->end())
	{
		emit logMessage(obj + tr(" is not registered!"), tr("TestRunner::executeObjExist()"));
		res.result = TEST_FAIL;
	}
	else
	{
		res.result = ((*it).first)? TEST_PASS : TEST_FAIL;
	}

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeFileExist(const QString &path)
{
	TestCommandResult res;

	Type param1Type = whatsThis(path);

	if(param1Type == STRING)
	{
		QFileInfo file(path);
		if(!file.exists())
		{
			emit logMessage(tr("Path ") + path + tr(" not found!"), tr("TestRunner::executeFileExist()"));
			res.result = TEST_FAIL;
		}
		else if(!file.isFile())
		{
			emit logMessage(path + tr(" is not a file!"), tr("TestRunner::executeFileExist()"));
			res.result = TEST_FAIL;
		}
	}
	else
	{
		emit logMessage(path + tr(" is not string!"), tr("TestRunner::executeFileExist()"));
		res.result = TEST_FAIL;
	}

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeWait(const QString &val)
{
	TestCommandResult res;

	if(!Algorithms::isInt(val))
	{
		emit logMessage(val + tr(" is not a proper value for WAIT!"), tr("TestRunner::executeWait()"));
		res.executedProperly = false;
	}
	else
	{
		usleep(val.toInt() * 1000);
	}

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeSet(const QString &obj, const QString &param)
{
	TestCommandResult res;

	Type param1Type = whatsThis(obj);
	Type param2Type = whatsThis(param);

	QMap<QString, std::pair<QObject *, QString> >::const_iterator it;
	QMap<QString, std::pair<QObject *, QString> >::const_iterator it2;

	if(param1Type == QSPINBOX || param1Type == QDOUBLESPINBOX || param1Type == QCOMBOBOX)
	{
		it = _pObjReg->find(obj);
		if(param2Type == INT)
		{
			if(param1Type == QSPINBOX) ((QSpinBox *)(*it).first)->setValue(param.toInt());
			else if(param1Type == QDOUBLESPINBOX) ((QDoubleSpinBox *)(*it).first)->setValue(param.toInt());
			else if(param1Type == QCOMBOBOX) ((QComboBox *)(*it).first)->setCurrentIndex(param.toInt());
		}
		else if(param2Type == DOUBLE)
		{
			if(param1Type == QSPINBOX) ((QSpinBox *)(*it).first)->setValue(param.toDouble());
			else if(param1Type == QDOUBLESPINBOX) ((QDoubleSpinBox *)(*it).first)->setValue(param.toDouble());
			else if(param1Type == QCOMBOBOX) ((QComboBox *)(*it).first)->setCurrentIndex(param.toDouble());
		}
		else if(param2Type == QSPINBOX)
		{
			it2 = _pObjReg->find(param);
			if(param1Type == QSPINBOX) ((QSpinBox *)(*it).first)->setValue(((QSpinBox *)(*it2).first)->value());
			else if(param1Type == QDOUBLESPINBOX) ((QDoubleSpinBox *)(*it).first)->setValue(((QSpinBox *)(*it2).first)->value());
			else if(param1Type == QCOMBOBOX) ((QComboBox *)(*it).first)->setCurrentIndex(((QSpinBox *)(*it2).first)->value());
		}
		else if(param2Type == QDOUBLESPINBOX)
		{
			it2 = _pObjReg->find(param);
			if(param1Type == QSPINBOX) ((QSpinBox *)(*it).first)->setValue(((QDoubleSpinBox *)(*it2).first)->value());
			else if(param1Type == QDOUBLESPINBOX) ((QDoubleSpinBox *)(*it).first)->setValue(((QDoubleSpinBox *)(*it2).first)->value());
			else if(param1Type == QCOMBOBOX) ((QComboBox *)(*it).first)->setCurrentIndex((int)((QDoubleSpinBox *)(*it2).first)->value());
		}
		else if(param2Type == QCOMBOBOX)
		{
			it2 = _pObjReg->find(param);

			if(param1Type == QSPINBOX) ((QSpinBox *)(*it).first)->setValue(((QComboBox *)(*it2).first)->currentIndex());
			else if(param1Type == QDOUBLESPINBOX) ((QDoubleSpinBox *)(*it).first)->setValue(((QComboBox *)(*it2).first)->currentIndex());
			else if(param1Type == QCOMBOBOX) ((QComboBox *)(*it).first)->setCurrentIndex(((QComboBox *)(*it2).first)->currentIndex());
		}
		else
		{
			emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeSet()"));
			res.executedProperly = false;
		}
	}
	else if(param1Type == QLINEEDIT)
	{
		it = _pObjReg->find(obj);
		if(param2Type == STRING)
		{
			((QLineEdit *)(*it).first)->setText(param);
		}
		else if(param2Type == QLINEEDIT)
		{
			it2 = _pObjReg->find(param);
			((QLineEdit *)(*it).first)->setText(((QLineEdit *)(*it2).first)->text());
		}
		else if(param2Type == QLABEL)
		{
			it2 = _pObjReg->find(param);
			((QLineEdit *)(*it).first)->setText(((QLabel *)(*it2).first)->text());
		}
		else
		{
			emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeSet()"));
			res.executedProperly = false;
		}
	}
	else if(param1Type == QTEXTEDIT)
	{
		it = _pObjReg->find(obj);
		if(param2Type == STRING)
		{
			((QTextEdit *)(*it).first)->setText(param);
		}
		else if(param2Type == QLINEEDIT)
		{
			it2 = _pObjReg->find(param);
			((QTextEdit *)(*it).first)->setText(((QLineEdit *)(*it2).first)->text());
		}
		else if(param2Type == QTEXTEDIT)
		{
			it2 = _pObjReg->find(param);
			((QTextEdit *)(*it).first)->setText(((QTextEdit *)(*it2).first)->toPlainText());
		}
		else if(param2Type == QLABEL)
		{
			it2 = _pObjReg->find(param);
			((QTextEdit *)(*it).first)->setText(((QLabel *)(*it2).first)->text());
		}
		else
		{
			emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeSet()"));
			res.executedProperly = false;
		}
	}
	else if(param1Type == QLABEL)
	{
		it = _pObjReg->find(obj);
		if(param2Type == STRING)
		{
			((QLabel *)(*it).first)->setText(param);
		}
		else if(param2Type == QLINEEDIT)
		{
			it2 = _pObjReg->find(param);
			((QLabel *)(*it).first)->setText(((QLineEdit *)(*it2).first)->text());
		}
		else if(param2Type == QLABEL)
		{
			it2 = _pObjReg->find(param);
			((QLabel *)(*it).first)->setText(((QLabel *)(*it2).first)->text());
		}
		else
		{
			emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeSet()"));
			res.executedProperly = false;
		}
	}
	else if(param1Type == QCHECKBOX || param1Type == QRADIOBUTTON)
	{
		it = _pObjReg->find(obj);
		if(param2Type == INT)
		{
			if(param.toInt() >= 0 && param.toInt() <= 1)
			{
				if(param1Type == QCHECKBOX) ((QCheckBox *)(*it).first)->setChecked(param.toInt());
				else if(param1Type == QRADIOBUTTON) ((QRadioButton *)(*it).first)->setChecked(param.toInt());
			}
			else
			{
				emit logMessage(tr("Parameter2 must be 0 or 1!"), tr("TestRunner::executeSet()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeSet()"));
			res.executedProperly = false;
		}
	}
	else
	{
		emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeSet()"));
		res.executedProperly = false;
	}

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeCall(const QString &fun, const QString &param, const QString &param2)
{
	TestCommandResult res;

	if(fun == "exportObjectList()")
	{
		if(!param.isEmpty())
		{
			Type param1Type = whatsThis(param);
			if(param1Type == STRING)
			{
				emit exportObjectList(param);
			}
			else
			{
				emit logMessage(tr("Wrong type parameter provided!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs a parameter!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "saveLog()")
	{
		if(!param.isEmpty())
		{
			Type param1Type = whatsThis(param);
			if(param1Type == STRING)
			{
				emit saveLog(param);
			}
			else
			{
				emit logMessage(tr("Wrong type parameter provided!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs a parameter!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "compareParameters()")
	{
        emit FB_get();

        // Wait for result
        _paused = true;
        while (_paused) usleep(COMMAND_DELAY);
	}
	else if(fun == "connect()")
	{
		if(!param.isEmpty())
		{
			Type param1Type = whatsThis(param);
			if(param1Type == INT && param.toInt() > 1024)
			{
				emit connect(param.toInt());
			}
			else
			{
				emit logMessage(tr("Wrong type parameter provided!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs a parameter!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "disconnect()")
	{
		emit disconnect();
	}
	else if(fun == "isDisconnected()")
	{
		bool connected = isConnected();
		res.result = connected? TEST_FAIL : TEST_PASS;
	}
	else if(fun == "applyConfiguration()")
	{
		emit applyConfiguration();
	}
	else if(fun == "loadConfiguration()")
	{
		if(!param.isEmpty())
		{
			Type param1Type = whatsThis(param);
			if(param1Type == STRING)
			{
				emit loadConfiguration(param);
			}
			else
			{
				emit logMessage(tr("Wrong type parameter provided!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs a parameter!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "saveConfiguration()")
	{
		if(!param.isEmpty())
		{
			Type param1Type = whatsThis(param);
			if(param1Type == STRING)
			{
				emit saveConfiguration(param);
			}
			else
			{
				emit logMessage(tr("Wrong type parameter provided!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs a parameter!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "record()")
	{
		if(!param.isEmpty())
		{
			if(!param2.isEmpty())
			{
				Type param2Type = whatsThis(param2);
				if(param2Type != INT || param2.toInt() < 0)
				{
					emit logMessage(tr("Wrong type parameter provided!"), tr("TestRunner::executeCall()"));
					res.executedProperly = false;
					return res;
				}
			}

			emit record(param, param2.toInt());
		}
		else
		{
			emit logMessage(tr("This function needs a parameter!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "saveCaptureAsFLX()")
	{
		if(!param.isEmpty() || !param2.isEmpty())
		{
			Type param1Type = whatsThis(param);
			Type param2Type = whatsThis(param2);
			QString captureName = param;

			if(param2Type == STRING)
			{
				if(param2.endsWith(".flx") || param2.endsWith(".yuv"))
				{
					if(param1Type == CAPTUREGALLERYITEM)
					{
						captureName.chop(10);
						emit saveRec_TF(captureName, param2, true);
					}
					else if(param1Type == CAPTUREPREVIEW)
					{
						captureName.chop(8);
						emit saveRec_TF(captureName, param2, true);
					}
					else
					{
						emit logMessage(tr("Parameter 1 is not a capture type!"), tr("TestRunner::executeCall()"));
						res.executedProperly = false;
					}
				}
				else
				{
					emit logMessage(tr("Wrong file format!"), tr("TestRunner::executeCall()"));
					res.executedProperly = false;
				}
			}
			else
			{
				emit logMessage(tr("Parameter 2 is not a string!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs 2 parameters!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "saveCaptureAsJPEG()")
	{
		if(!param.isEmpty() || !param2.isEmpty())
		{
			Type param1Type = whatsThis(param);
			Type param2Type = whatsThis(param2);
			QString captureName = param;
			if(param2Type == STRING)
			{
				if(param2.endsWith(".jpg"))
				{
					if(param1Type == CAPTUREGALLERYITEM)
					{
						captureName.chop(10);
						emit saveRec_TF(captureName, param2, false);
					}
					else if(param1Type == CAPTUREPREVIEW)
					{
						captureName.chop(8);
						emit saveRec_TF(captureName, param2, false);
					}
					else
					{
						emit logMessage(tr("Parameter 1 is not a capture type!"), tr("TestRunner::executeCall()"));
						res.executedProperly = false;
					}
				}
				else
				{
					emit logMessage(tr("Wrong file format!"), tr("TestRunner::executeCall()"));
					res.executedProperly = false;
				}
			}
			else
			{
				emit logMessage(tr("Parameter 2 is not a string!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs 2 parameters!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else if(fun == "triggerAction()")
	{
		if(!param.isEmpty())
		{
			Type param1Type = whatsThis(param);
			if(param1Type == QACTION)
			{
				emit triggerAction(qobject_cast<QAction *>(_pObjReg->find(param).value().first));
			}
			else
			{
				emit logMessage(tr("Wrong type parameter provided!"), tr("TestRunner::executeCall()"));
				res.executedProperly = false;
			}
		}
		else
		{
			emit logMessage(tr("This function needs a parameter!"), tr("TestRunner::executeCall()"));
			res.executedProperly = false;
		}
	}
	else
	{
		emit logMessage(fun + tr(" function is not recognized!"), tr("TestRunner::executeCall()"));
		res.executedProperly = false;
	}

	return res;
}

VisionLive::TestRunner::TestCommandResult VisionLive::TestRunner::executeCompare(const QString &op, const QString &param1, const QString &param2)
{
	TestCommandResult res;

	Type param1Type = whatsThis(param1);
	Type param2Type = whatsThis(param2);

	if((param1Type == STRING ||
		param1Type == INT ||
		param1Type == DOUBLE ||
		param1Type == QCHECKBOX ||
		param1Type == QRADIOBUTTON ||
		param1Type == QSPINBOX ||
		param1Type == QDOUBLESPINBOX ||
		param1Type == QLINEEDIT ||
		param1Type == QCOMBOBOX ||
		param1Type == QLABEL ||
		param1Type == QTEXTEDIT ||
		param1Type == QACTION) &&
		(param2Type == STRING ||
		param2Type == INT ||
		param2Type == DOUBLE ||
		param2Type == QCHECKBOX ||
		param2Type == QRADIOBUTTON ||
		param2Type == QSPINBOX ||
		param2Type == QDOUBLESPINBOX ||
		param2Type == QLINEEDIT ||
		param2Type == QCOMBOBOX ||
		param2Type == QLABEL ||
		param2Type == QTEXTEDIT ||
		param2Type == QACTION))
	{
		if((param1Type == STRING || param1Type == QLINEEDIT || param1Type == QLABEL || param1Type == QTEXTEDIT) && 
			(param2Type == STRING || param2Type == QLINEEDIT || param2Type == QLABEL || param2Type == QTEXTEDIT))
		{
			QString val1 = getValue<QString>(param1Type, param1);
			QString val2 = getValue<QString>(param2Type, param2);
			if(op == "<") res.result = (val1.compare(val2) < 0)? TEST_PASS : TEST_FAIL;
			else if(op == ">") res.result = (val1.compare(val2) > 0)? TEST_PASS : TEST_FAIL;
			else if(op == "==") res.result = (val1.compare(val2) == 0)? TEST_PASS : TEST_FAIL;
			else if(op == "!=") res.result = (val1.compare(val2) != 0)? TEST_PASS : TEST_FAIL;
			else if(op == "<=") res.result = (val1.compare(val2) <= 0)? TEST_PASS : TEST_FAIL;
			else if(op == ">=") res.result = (val1.compare(val2) >= 0)? TEST_PASS : TEST_FAIL;

			emit logMessage(val1 + " " + op + " " + val2, tr("TestRunner::executeCompare"));
		}
		else if((param1Type == INT || param1Type == DOUBLE || param1Type == QCHECKBOX || 
			param1Type == QRADIOBUTTON || param1Type == QSPINBOX || param1Type == QDOUBLESPINBOX || param1Type == QCOMBOBOX || param1Type == QACTION) &&
			(param2Type == INT || param2Type == DOUBLE || param2Type == QCHECKBOX || 
			param2Type == QRADIOBUTTON || param2Type == QSPINBOX || param2Type == QDOUBLESPINBOX || param2Type == QCOMBOBOX || param2Type == QACTION))
		{
			double val1 = getValue<double>(param1Type, param1);
			double val2 = getValue<double>(param2Type, param2);
			if(op == "<") res.result = (val1 < val2)? TEST_PASS : TEST_FAIL;
			else if(op == ">") res.result = (val1 > val2)? TEST_PASS : TEST_FAIL;
			else if(op == "==") res.result = (val1 == val2)? TEST_PASS : TEST_FAIL;
			else if(op == "!=") res.result = (val1 != val2)? TEST_PASS : TEST_FAIL;
			else if(op == "<=") res.result = (val1 <= val2)? TEST_PASS : TEST_FAIL;
			else if(op == ">=") res.result = (val1 >= val2)? TEST_PASS : TEST_FAIL;

			emit logMessage(QString::number(val1) + " " + op + " " + QString::number(val2), tr("TestRunner::executeCompare"));
		}
		else
		{
			emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeCompare()"));
			res.executedProperly = false;
		}
	}
	else
	{
		emit logMessage(tr("Wrong parameter types (") + Algorithms::getTypeName(param1Type) + ", " + Algorithms::getTypeName(param2Type) + ")!", tr("TestRunner::executeCompare()"));
		res.executedProperly = false;
	}
		
	return res;
}

//
// Public Slots
//

void VisionLive::TestRunner::FB_received(const ISPC::ParameterList &intList, const ISPC::ParameterList extList)
{
    ISPC::ParameterList local = intList;

    std::vector<std::string> excluded{
        ISPC::ModuleDSC::DSC_PITCH.name,
        ISPC::ModuleESC::ESC_PITCH.name,
        //ISPC::ModuleAWS::AWS_ENABLED.name,
        //ISPC::ModuleAWS::AWS_LOG2_B_QEFF.name,
        //ISPC::ModuleAWS::AWS_LOG2_R_QEFF.name,
        //ISPC::ModuleAWS::AWS_TILE_SIZE.name
    };

    for (auto &e : excluded) local.removeParameter(e);
        
    bool ok = true;
    for (auto &e : local)
    {
        ISPC::ParameterList::const_iterator extIt = extList.find(e.first);
        if (extIt != extList.end() && *extIt != e)
        {
            std::string intParamValues;
            for (unsigned int i = 0; i < e.second.size(); i++) 
                intParamValues = intParamValues + e.second.getString(i) + " ";
            std::string extParamValues;
            for (unsigned int i = 0; i < extIt->second.size(); i++)
                extParamValues = extParamValues + extIt->second.getString(i) + " ";

            emit logMessage(QString((e.first + "(VL/ISP) - " + intParamValues + " != " +
                extParamValues).c_str()), tr("TestRunner::executeLog"));
            ok = false;
        }
    }

    if (ok)
    {
        emit logMessage(tr("ParameterLists coparison successful!"), tr("TestRunner::executeLog"));
        _paused = false;
    }
    else
    {
        emit logMessage(tr("ParameterLists coparison failed!"), tr("TestRunner::executeLog"));
        _continueRun = false;
        _paused = false;
    }
}
