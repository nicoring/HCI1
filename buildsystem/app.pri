TEMPLATE = app

QT *= core widgets

DEPENDENCIES += Qt ICU MTQ

include(common.pri)

DESTDIR = $${TO_BASE_DIR}/$${CURRENT_CONFIG}/apps

LIBS += -L$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/dependencies
LIBS += -L$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/plugins

win32 {
	QMAKE_POST_LINK += && (if not exist \"$${DESTDIR}/$${TARGET}\" mklink /j \"$${DESTDIR}/$${TARGET}\" \"$${APP_DIR}\")
	QMAKE_POST_LINK += && \"$${PWD}/create_launcher.bat\" $${CURRENT_CONFIG} $${TARGET} > \"$${OUT_PWD}/$${TO_BASE_DIR}/$${TARGET}-$${CURRENT_CONFIG}.bat\"

	## Copy to Atrium
	contains(MTQ_POST_HOOKS, Atrium) {
		COPY_DEST_DIR = \"$${COPY_TO_ATRIUM_DIR}/$$(username)/$${TARGET}-$${CURRENT_CONFIG}\"
		QMAKE_POST_LINK += && \"$${PWD}/copy_to_x.bat\" \"$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}\" $${COPY_DEST_DIR} $${TARGET} \"$${PWD}\" TRUE
	}

	## Copy to Floor
	contains(MTQ_POST_HOOKS, Floor) {
		COPY_DEST_DIR = \"$${COPY_TO_FLOOR_DIR}/$$(username)/$${TARGET}-$${CURRENT_CONFIG}\"
		QMAKE_POST_LINK += && \"$${PWD}/copy_to_x.bat\" \"$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}\" $${COPY_DEST_DIR} $${TARGET} \"$${PWD}\" TRUE
	}

} else {
	message("Apps currently not supported on unix.")
}

SOURCES += \
	$${TO_BASE_DIR}/mtq/main.cpp
