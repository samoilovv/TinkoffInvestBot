#ifndef LOGCONFIGURATOR_H
#define LOGCONFIGURATOR_H

#include <QObject>
#include <QString>

namespace simpleqtlogger {
	class SimpleQtLogger;
}

class LogConfigurator : public QObject
{
public:
	LogConfigurator(QObject *parent = Q_NULLPTR);
    QString logFilterRules() const;
	void setLogFilterRules(const QString& rules, bool permanently = false);
	simpleqtlogger::SimpleQtLogger *logger() const;
	void setEnabledInternalLog();
	void setDisabledInternalLog();

private:
	QString _logFilterRules;
	const QString _defaultFilterRules;
	simpleqtlogger::SimpleQtLogger* _logger = nullptr;
	QString	_filterRulesFile;
private:
	void writeFilterRules(const QString&);
	void initLogger();
	bool initLogRules();
	bool writeFilterRulesToFile(const QString&);
};

#endif // LOGCONFIGURATOR_H
