#pragma once

#include <QVariant>

#include "mtq/utils/Singleton.h"
#include "mtq/utils/TypeId.h"

namespace mtq {

	class MTQ_EXPORT_MTQ Configuration : public QVariant
	{
	public:
		Configuration();
		Configuration(const QVariant &value);


		bool isList() const;
		bool isMap() const;

		QStringList keys() const;
		const Configuration mergeWith(const Configuration &other) const;

		const QVariant orDefault(const QVariant &defaultValue) const;
		const Configuration operator[](QString key) const;
		const Configuration operator[](int index) const;
	friend class ConfigurationService;
	};

	class MTQ_EXPORT_MTQ ConfigurationService
	{
		MTQ_SINGLETON(ConfigurationService)
	public:
		void loadFromFile(const QString fileName);
		void loadPluginConfigs();

		const Configuration getDefaultConfig(const TypeId &pluginTypeId) const;
		const Configuration global() const;
	private:
		const Configuration parseJsonFile(QString fileName) const;

		Configuration m_config;
		QMap<TypeId::Key, Configuration> m_pluginConfigs;
	};

}
