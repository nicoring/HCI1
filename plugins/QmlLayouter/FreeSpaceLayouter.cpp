#include "FreeSpaceLayouter.h"

#include <mtq/utils/Configuration.h>
#include "QmlLayouter/PolygonUtilities.h"

using namespace mtq;

FreeSpaceLayouter::FreeSpaceLayouter()
	: m_transformation(new RigidBodyTransformation())
{
}

FreeSpaceLayouter::~FreeSpaceLayouter()
{
	delete m_transformation;
}

void FreeSpaceLayouter::freeSpace(QList<QSet<QmlLayoutObject *>> layoutedObjectGroups,
								  QList<QmlLayoutObject *> allObjects,
								  QQuickItem *polygonsDrawer)
{
	//create convexHulls
	QList<QPolygonF> hulls;
	QList<QPolygonF> innerBlobs;
	QList<QPolygonF> boundaries;
	foreach(auto objects, layoutedObjectGroups) {
		QPolygonF objPolygon;
		foreach(QmlLayoutObject * object, objects)
			objPolygon << object->center();
		QPolygonF hull = PolygonUtilities::convexHull(objPolygon);
		hulls.append(hull);
		innerBlobs.append(PolygonUtilities::scalePolygon(0.1, hull));
		boundaries.append(PolygonUtilities::scalePolygon(2, hull));
	}
	QList<QPolygonF> sourcePolygons = innerBlobs;
	QList<QPolygonF> destinationPolygons = hulls;
	sourcePolygons.append(boundaries);
	destinationPolygons.append(boundaries);
	m_transformation->setSourcePoints(sourcePolygons);
	m_transformation->setDestinationPoints(destinationPolygons);

	QSet<QmlLayoutObject*> currentlyNotLayoutedObjects = QSet<QmlLayoutObject*>::fromList(allObjects);
	foreach(auto layoutedGroup, layoutedObjectGroups)
		currentlyNotLayoutedObjects.subtract(layoutedGroup);

	if(ConfigurationService::instance().global()["useFreeSpace"].toBool())
		foreach(QmlLayoutObject *object, currentlyNotLayoutedObjects) {
			QVector2D transformedPos = m_transformation->transformPoint(QVector2D(object->position()));
			object->setCenter(transformedPos.toPointF());
		}

	if(polygonsDrawer) {
		QVariantList polygonsList;
		foreach(QPolygonF eachHull, hulls) {
			polygonsList.append(eachHull.length());
			foreach (QPointF eachPoint, eachHull) {
				polygonsList.append(eachPoint);
			}
		}
		polygonsDrawer->setProperty("freeSpacePolygons", polygonsList);
	}
}
