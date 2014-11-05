#include "Matrix4x4.h"

using namespace mtq;

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(const QMatrix &matrix)
	: QMatrix4x4(matrix)
{
}

Matrix4x4::Matrix4x4(const QMatrix4x4 &matrix)
	: QMatrix4x4(matrix)
{
}

