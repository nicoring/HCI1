#pragma once

#include <QHostInfo>

#include <NatNetTypes.h>
#include <NatNetClient.h>

#include <mtq/core/PluginRegistry.h>
#include <mtq/datatypes/Geometry.h>

namespace mtq {

	class MTQ_EXPORT_PLUGIN FOVCenterOptitrackDirectly : public Plugin

	{
		Q_OBJECT
	public:
		void initialize();
		void run();
		void updateHead(sRigidBodyData *data);
		QMutex posMutex;   ///mutex protecting the position and angles.

	public slots:
		void serverLookupCallback(QHostInfo server);

	private:
		void run_stage2();

		NatNetClient *m_natNetClient;
		QString m_serverIP, m_clientIP;
		QVector3D transformToWorld(QVector3D vec);

		MTQ_PLUGIN(FOVCenterOptitrackDirectly)
	};

}
