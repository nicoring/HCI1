#include "Configuration.h"

#include <QFile>
#include <QDirIterator>
#include <QRegExp>
#include <QJsonDocument>

#include "mtq/core/PluginRegistry.h"
#include "mtq/utils/Logger.h"

using namespace mtq;

Configuration::Configuration()
	: QVariant()
{
}

Configuration::Configuration(const QVariant &value)
	: QVariant(value)
{
}

const Configuration Configuration::mergeWith(const Configuration &other) const
{
	if (!isValid())
		return other;

	if (!isMap() || !other.isMap())
		return *this;

	QVariantMap thisMap = toMap();
	QVariantMap otherMap = other.toMap();

	foreach(QString key, otherMap.keys()) {
		thisMap.insert(key, Configuration(thisMap[key]).mergeWith(otherMap[key]));
	}

	return Configuration(thisMap);
}

bool Configuration::isList() const
{
	return canConvert(QMetaType::QVariantList);
}

bool Configuration::isMap() const
{
	return canConvert(QMetaType::QVariantMap);
}

QStringList Configuration::keys() const
{
	return isMap() ? toMap().keys() : QStringList();
}

const QVariant Configuration::orDefault(const QVariant &defaultValue) const
{
	return isValid() ? *this : defaultValue;
}

const Configuration Configuration::operator[](int index) const {
	return Configuration(isList() ? toList()[index] : QVariant());
}

const Configuration Configuration::operator[](QString key) const {
	return Configuration(isMap() ? toMap()[key] : QVariant());
}

void ConfigurationService::loadFromFile(const QString fileName)
{
	Configuration defaultConfig(parseJsonFile(":/config/MTQ.json"));
	QString configFileName = fileName.isEmpty() ? defaultConfig["ConfigurationService"]["configFile"].toString() : fileName;
	m_config = parseJsonFile(configFileName).mergeWith(defaultConfig);
}

void ConfigurationService::loadPluginConfigs()
{
	QDirIterator it(":/config");

	while (it.hasNext()) {
		QString configFile = it.next();
		if (!configFile.endsWith(".json") || configFile.endsWith("/MTQ.json"))
			continue;

		QString pluginTypeName = QFileInfo(configFile).baseName();
		m_pluginConfigs.insert(PluginRegistry::instance().getPluginTypeId(pluginTypeName).key(), parseJsonFile(configFile));
	}
}

const Configuration ConfigurationService::getDefaultConfig(const TypeId &pluginTypeId) const
{
	Configuration config;

	TypeId currentTypeId = pluginTypeId;

	while(currentTypeId.key()) {
		if (m_pluginConfigs.contains(currentTypeId.key())) {
			config = config.mergeWith(m_pluginConfigs[currentTypeId.key()]);
		}
		currentTypeId = currentTypeId.parent();
	}

	return config;
}

const Configuration ConfigurationService::global() const
{
	return m_config;
}

const Configuration ConfigurationService::parseJsonFile(QString fileName) const
{
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly)) {
		MTQ_ERROR << "Could not read config file " << fileName << ". File not found.";
		return QVariant();
	}

	MTQ_INFO << "Reading config file " << fileName << ".";

	QJsonParseError parseError;
	QJsonDocument document = QJsonDocument::fromJson(file.readAll(), &parseError);

	if (parseError.error)
		MTQ_ERROR << "Could not parse config file " << fileName << ": " << parseError.errorString() << ".";

	return Configuration(document.toVariant());
}
