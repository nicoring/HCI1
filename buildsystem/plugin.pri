TEMPLATE = lib

QT *= core

DEPENDENCIES += Qt ICU MTQ

include(common.pri)

DEFINES += \
	MTQ_EXPORT_MTQ=Q_DECL_IMPORT \
	MTQ_EXPORT_TYPE=Q_DECL_IMPORT \
	MTQ_EXPORT_PLUGIN=Q_DECL_EXPORT

win32 {
	DLLDESTDIR = $${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/plugins
	QMAKE_POST_LINK += && (if not exist \"$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/apps/qml\" mkdir \"$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/apps/qml\")
	QMAKE_POST_LINK += && (if not exist \"$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/apps/qml/$${TARGET}\" mklink /j \"$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/apps/qml/$${TARGET}\" \"$${PLUGIN_DIR}/qml\")
} else {
	DESTDIR = $${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/plugins
}
