#include "LogConfigurator.h"

#include "simpleQtLogger.h"
#include "HevaaStandardPaths.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QLoggingCategory>
#include <iostream>

QString getLogsDirectory()
{
    return StandardPaths::hevaaStandardLocation(StandardPaths::LogHevaaLocation);
}

bool prepareDataDirectory()
{
	if (!QDir::home().mkpath(getLogsDirectory()))
	{
		std::cerr << "Can not create logs directory!" << std::endl;
		return false;
	}

	return true;
}

void hevaaMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
     Q_UNUSED(context);

	 QByteArray localMsg = msg.toLocal8Bit();
	 switch (type) {
	 case QtDebugMsg:
		 LS_DEBUG(msg);
		 break;
	 case QtInfoMsg:
		 LS_INFO(msg);
		 break;
	 case QtWarningMsg:
		 LS_WARN(msg);
		 break;
	 case QtCriticalMsg:
		 LS_ERROR(msg);
		 break;
	 case QtFatalMsg:
		 LS_FATAL(msg);
		 abort();
	 }
 }

LogConfigurator::LogConfigurator(QObject *parent) : QObject(parent)
  , _defaultFilterRules("*.debug=true\n*.info=false")
{
	initLogger();
}

void LogConfigurator::initLogger()
{
	if(!initLogRules())
		qDebug() << "dont load rules for log";


	if (!prepareDataDirectory())
	{
		qFatal("error create dir log");
	}
    QString logFile = QString(getLogsDirectory() + "hevaa_service.log");

	// logger
	Q_ASSERT_X(SQTL_VERSION >= SQTL_VERSION_CHECK(1, 2, 0), "main", "SimpleQtLogger version");
	// enable sinks
	simpleqtlogger::ENABLE_LOG_SINK_FILE = true;
	simpleqtlogger::ENABLE_LOG_SINK_CONSOLE = true;
	simpleqtlogger::ENABLE_LOG_SINK_QDEBUG = false;
	simpleqtlogger::ENABLE_LOG_SINK_SIGNAL = false;
	// set log-features
	simpleqtlogger::ENABLE_FUNCTION_STACK_TRACE = false;
	simpleqtlogger::ENABLE_CONSOLE_COLOR = false;
	simpleqtlogger::ENABLE_CONSOLE_TRIMMED = true;
	simpleqtlogger::ENABLE_CONSOLE_LOG_FILE_STATE = true;
	// set log-levels (global; all enabled)
	simpleqtlogger::ENABLE_LOG_LEVELS.logLevel_DEBUG = true;
	// set log-levels (specific)
	simpleqtlogger::EnableLogLevels enableLogLevels_file = simpleqtlogger::ENABLE_LOG_LEVELS;
	simpleqtlogger::EnableLogLevels enableLogLevels_console = simpleqtlogger::ENABLE_LOG_LEVELS;
	simpleqtlogger::EnableLogLevels enableLogLevels_qDebug = simpleqtlogger::ENABLE_LOG_LEVELS;
	simpleqtlogger::EnableLogLevels enableLogLevels_signal = simpleqtlogger::ENABLE_LOG_LEVELS;
	enableLogLevels_file.logLevel_INFO = true;

	// initialize SimpleQtLogger (step 1/2)
	_logger = simpleqtlogger::SimpleQtLogger::createInstance(this);
	simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_file(enableLogLevels_file);
	simpleqtlogger::SimpleQtLogger::getInstance()->setLogFileName(logFile, 1024*1024*10, 10);
	simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_console(enableLogLevels_console);
	simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_qDebug(enableLogLevels_qDebug);
	simpleqtlogger::SimpleQtLogger::getInstance()->setLogLevels_signal(enableLogLevels_signal);
    qInstallMessageHandler(hevaaMessageOutput);
}

bool LogConfigurator::initLogRules()
{
    auto pathRulesConfig = StandardPaths::hevaaStandardLocation(StandardPaths::ConfigHevaaLocation);
	if (!QDir::home().mkpath(pathRulesConfig))
	{
		std::cerr << "Can not create config directory!" << std::endl;
		return false;
	}
	_filterRulesFile = pathRulesConfig +"/qtlogging.ini";
	QFile file(_filterRulesFile);
	if(!QFileInfo::exists(_filterRulesFile)) {
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream stream(&file);
            #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
            stream << _defaultFilterRules << Qt::endl;
            #else
            stream << _defaultFilterRules << endl;
            #endif
			file.close();
			setLogFilterRules(_defaultFilterRules);
			return true;
		}
	}
	if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		auto rules = file.readAll();
		setLogFilterRules(rules);
		file.close();
		return true;
	}
	return false;
}

bool LogConfigurator::writeFilterRulesToFile(const QString &rules)
{
	if(QFileInfo::exists(_filterRulesFile)) {
		QFile file(_filterRulesFile);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
			QTextStream stream(&file);
            #if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
            stream << rules << Qt::endl;
            #else
            stream << rules << endl;
            #endif
			file.close();
			return true;
		}
	}
	return false;
}

QString LogConfigurator::logFilterRules() const
{
	return _logFilterRules;
}

void LogConfigurator::setLogFilterRules(const QString &rules, bool permanently)
{
	_logFilterRules = rules;
	writeFilterRules(_logFilterRules);
	if(permanently) {
		if(writeFilterRulesToFile(rules)) qDebug() << "save setting to file";
		else qWarning() << "failed to save setting";
	}
}

simpleqtlogger::SimpleQtLogger *LogConfigurator::logger() const
{
	return _logger;
}

void LogConfigurator::setEnabledInternalLog()
{
	simpleqtlogger::ENABLE_LOG_SINK_SIGNAL = true;
}

void LogConfigurator::setDisabledInternalLog()
{
	simpleqtlogger::ENABLE_LOG_SINK_SIGNAL = false;
}

void LogConfigurator::writeFilterRules(const QString &rules)
{
	QLoggingCategory::setFilterRules(rules);
}

