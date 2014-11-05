#include "FOVCenterOptitrackDirectly.h"

#include <cmath>
#include <NatNetTypes.h>
#include <NatNetClient.h>

#include <QNetworkInterface>

#include <mtq/core/EventDispatcher.h>
#include <mtq/datatypes/Geometry.h>
#include <PositionEvents/PointingEvents.h>
#include <PositionEvents/BodyEvents.h>

using namespace mtq;

MTQ_REGISTER_PLUGIN(FOVCenterOptitrackDirectly)

QHostAddress autoselectIP(QHostAddress & peer) {
	QList<QNetworkInterface> ifaces = QNetworkInterface::allInterfaces();
	for (QNetworkInterface iface : ifaces) {
		for (QNetworkAddressEntry ifaceIP : iface.addressEntries()) {
			if (peer.isInSubnet(ifaceIP.ip(),ifaceIP.prefixLength())) {
				return ifaceIP.ip();
			}
		}
	}
	return QHostAddress(QHostAddress::LocalHost);
}

enum SkeletonIndex : int
		{
			/*	Here come the accessors to the different body parts.
				Aileen asked me to keep her list of undocumented
				indecies in the SkeletonRigidBodiesArray.
				They where prepended by OTSN_ */

			Hip = 0,
			Ab = 1,
			Chest = 2,
			Neck = 3,
			Head = 4,
			HeadEnd = 5,
			LShoulder = 6,
			LUArm = 7,
			LFArm = 8,
			LHand = 9,
			LHandEnd = 10,
			RShoulder = 11,
			RUArm = 12,
			RFArm = 13,
			RHand = 14,
			RHandEnd = 15,
			LThigh = 16,
			LShin = 17,
			LFoot = 18,
			LFootEnd = 19,
			RThigh = 20,
			RShin = 21,
			RFoot = 22,
			RFootEnd = 23,
			__SkeletonIndexCount = 24
		};


void __cdecl CallbackMessageHandler(int msgType, char * msg)
{
	MTQ_DEBUG << QString("%1").arg(msg);
}

///Callback for marker and skeleton data. updates internal state.
void __cdecl CallbackDataHandler(sFrameOfMocapData * data, void * pUserData)
{
	FOVCenterOptitrackDirectly* this_ = (FOVCenterOptitrackDirectly*) pUserData;
	//qDebug() << data->iFrame;
	if (data->nSkeletons > 0) {
		sRigidBodyData (*t)[25];
		t = (sRigidBodyData(*)[25]) (void*) data->Skeletons[0].RigidBodyData;
		sRigidBodyData head  = data->Skeletons[0].RigidBodyData[SkeletonIndex::HeadEnd];
		this_->posMutex.lock();
			this_->updateHead(&head);
		this_->posMutex.unlock();

	}
}


FOVCenterOptitrackDirectly::FOVCenterOptitrackDirectly(const QString &pluginName, const Configuration &config)
	: Plugin(pluginName, config)
{
}
/*
void FOVCenterOptitrackDirectly::updateHead(sRigidBodyData *data) {

	QVector3D pos(data->x,data->y,data->z);
	Matrix4x4 direction;
	direction.rotate(Quaternion(data->qw,data->qx, data->qy, data->qz));
	QVector3D directionVector = QVector3D(0,1,0)*direction;

	if (directionVector.z()>0) return;
	QVector3D viewPos = pos+directionVector*abs(pos.z()/directionVector.z());
	qDebug() << "emiting headpointevent";
	MTQ_EMIT(new HeadPointingEvent(viewPos.xy(), std::numeric_limits<qreal>::quiet_NaN(), mtq::User()));

}
*/

void FOVCenterOptitrackDirectly::updateHead(sRigidBodyData *data)
{
	QVector3D pos(data->x,data->y,data->z);
	Matrix4x4 direction;
	direction.rotate(Quaternion(data->qw,data->qx, data->qy, data->qz));
	QVector3D directionVector = QVector3D(0, 0, 1)*direction;
	if (directionVector.y()>0) return;
	QVector3D viewPos = pos+directionVector*abs(pos.y()/directionVector.y());
	MTQ_EMIT(new HeadPointingEvent(QVector3D(viewPos.z(), -viewPos.x(), 0), mtq::User()));
	qreal rotationOnFloor = std::atan2(-directionVector.x(), directionVector.z());
	MTQ_EMIT(new HeadEvent(QVector3D(pos.z(), -pos.x(), 0), rotationOnFloor, mtq::User()))
}

QVector3D FOVCenterOptitrackDirectly::transformToWorld(QVector3D vec)
{
	return vec;
}

void FOVCenterOptitrackDirectly::initialize()
{
}

void FOVCenterOptitrackDirectly::run()
{
	//TODO: put default in resource file
	m_serverIP = config()["serverIPAddress"].orDefault(QString("172.16.22.128")).toString();
	QHostAddress server(m_serverIP);
	run_stage2();
	if (server==QHostAddress()) {
		//TODO: no valid IP, start hostname lookup
		QHostInfo::lookupHost(m_serverIP, this, SLOT(serverLookupCallback(QHostInfo)));
	} else {

	}
}

void FOVCenterOptitrackDirectly::serverLookupCallback(QHostInfo server)
{
//TODO: check and call stage2
}


void FOVCenterOptitrackDirectly::run_stage2() {
	if (!config()["clientIPAddress"].isValid()) {
		m_clientIP = autoselectIP(QHostAddress(m_serverIP)).toString();
		MTQ_INFO << "client IP " <<m_clientIP <<" autodetected";
	} else {
		m_clientIP = config()["clientIPAddress"].toString();
	}


	QByteArray serverIPAddress = m_serverIP.toLatin1();
	QByteArray clientIPAddress = m_clientIP.toLatin1();

	char szMyIPAddress[128] = "172.16.22.127";
	char szServerIPAddress[128] = "172.16.22.128";

	m_natNetClient = new NatNetClient(ConnectionType_Unicast);
	m_natNetClient->SetMessageCallback(CallbackMessageHandler);
	m_natNetClient->SetVerbosityLevel(Verbosity_Info);
	m_natNetClient->SetDataCallback(CallbackDataHandler, this);
	MTQ_INFO << "starting Optitrack connection from " << clientIPAddress << " to " << serverIPAddress;

	int errorCode = m_natNetClient->Initialize(clientIPAddress.data(), serverIPAddress.data());
	//int errorCode = m_natNetClient->Initialize(szMyIPAddress, szServerIPAddress);
	if (errorCode != ErrorCode_OK) {
		MTQ_WARNING << "OPTITRACK INITIALIZATION FAILED:" << errorCode;
		return;
	}
	sServerDescription serverDescription;
	memset(&serverDescription, 0, sizeof(serverDescription));
	errorCode = m_natNetClient->GetServerDescription(&serverDescription);

	if (!serverDescription.HostPresent)	{
		MTQ_WARNING << "OPTITRACK HOST NOT PRESENT #########";
		return;
	}

	MTQ_INFO << "Optitrack Connected";
}
