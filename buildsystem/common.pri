win32 {
	CONFIG(debug, debug|release) { #debug
		CURRENT_CONFIG = debug
		DLL_SUFFIX = d
	} else { #release
		CURRENT_CONFIG = release
		DLL_SUFFIX =
	}
} else {
	CURRENT_CONFIG = build
}

exists(config.pri) {
	include(config.pri)
} else {
	include(config.default.pri)
}

include(dependencies.pri)

CONFIG += CONSOLE

DEFINES += MTQ_TARGET=\\\"$${TARGET}\\\"

INCLUDEPATH += ..

unix: !macx: QMAKE_CXXFLAGS += -std=c++11
