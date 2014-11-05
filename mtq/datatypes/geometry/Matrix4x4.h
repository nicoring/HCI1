#pragma once

#include <QMatrix4x4>

namespace mtq {

	class MTQ_EXPORT_MTQ Matrix4x4 : public QMatrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(const QMatrix &matrix);
		Matrix4x4(const QMatrix4x4 &matrix);
	};

}
