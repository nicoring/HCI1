#pragma once

#include <QList>

#include "QmlLayouter/layoutObjects/QmlLayoutObject.h"
#include "QmlLayouter/transformation/RigidBodyTransformation.h"

namespace mtq {

	class FreeSpaceLayouter
	{
	public:
		FreeSpaceLayouter();
		~FreeSpaceLayouter();
		void freeSpace(QList<QSet<QmlLayoutObject *> > layoutedObjectGroups,
					   QList<QmlLayoutObject *> allObjects,
					   QQuickItem *polygonsDrawer);

	private:
		RigidBodyTransformation *m_transformation;
	};

}
