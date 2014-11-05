win32 {

MTQ_DIR = $${TO_BASE_DIR}/mtq
TYPES_DIR = $${TO_BASE_DIR}/types

### TYPE DEPENDENIES ###

	for(TYPE_ENTRY, TYPE_DEPENDENCIES) {
		INCLUDEPATH += $${TYPES_DIR}
		LIBS += -L$${OUT_PWD}/$${TYPES_DIR}/$${TYPE_ENTRY}/$${CURRENT_CONFIG}
		LIBS += -l$${TYPE_ENTRY}
		DEPENDPATH += $${TYPES_DIR}/$${TYPE_ENTRY}
	}

### OTHER DEPENDENCIES ###

	DEPENDENCY_DIR = $${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/dependencies

	## Alvar
	contains(DEPENDENCIES, Alvar) {
		INCLUDEPATH += $${ALVAR_DIR}/include/alvar
		LIBS += -L$${ALVAR_DIR}/bin
		LIBS += -lalvar200$${DLL_SUFFIX} -lalvarplatform200$${DLL_SUFFIX}
		QMAKE_CXXFLAGS += -wd4251 -wd4996
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${ALVAR_DIR}/bin\" \"$${DEPENDENCY_DIR}\" &&
	}

	## Boost
	contains(DEPENDENCIES, Boost) {
		INCLUDEPATH += $${BOOST_DIR}
		LIBS += -L$${BOOST_DIR}/lib
		for(lib, BOOST_LIBS): LIBS += -lboost_$${lib}$${BOOST_SUFFIX}
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${BOOST_DIR}/lib\" \"$${DEPENDENCY_DIR}\" &&
	}

	## GravitySpace
	contains(DEPENDENCIES, GravitySpace) {
		QMAKE_LFLAGS += /WX:NO
		QMAKE_CXXFLAGS_WARN_ON = # this flag is intentionally left blank

		# Alans Flags
		QMAKE_CXXFLAGS += /D_USE_MATH_DEFINES  /DNOMINMAX  /D_CRT_SECURE_NO_WARNINGS  /D_UNICODE  /DUNICODE  /DBOOST_ALL_NO_LIB  /DBOOST_ALL_DYN_LINK  /D_SCL_SECURE_NO_WARNINGS  /DWIN32_LEAN_AND_MEAN
		# Usually added by cmake
		QMAKE_CXXFLAGS += /wd4251 /D_WINDOWS /errorReport:prompt /fp:precise /GS /Gd /Gm- /wd4800 /MP /WX /wd4996 /Ob0 /TP /Zc:forScope /GR

		INCLUDEPATH += $${GRAVITY_SPACE_DIR}/include
		LIBS += -L$${GRAVITY_SPACE_DIR}/lib/$${CURRENT_CONFIG}
		LIBS += -lgravityspace-shared
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${GRAVITY_SPACE_DIR}/bin/$${CURRENT_CONFIG}\" \"$${DEPENDENCY_DIR}\" &&

		contains(GRAVITY_SPACE_USING, CUDA) {
			QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${CUDA_DIR}/bin\" \"$${DEPENDENCY_DIR}\" &&
		}

		contains(GRAVITY_SPACE_USING, SiftGPU) {
			QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${SIFT_GPU_DIR}/bin\" \"$${DEPENDENCY_DIR}\" &&
		}
	}

	## ICU
	contains(DEPENDENCIES, ICU) {
		LIBS += -L$${ICU_DIR}/bin64
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${ICU_DIR}/bin64\" \"$${DEPENDENCY_DIR}\" &&
	}

	## LaserControl
	contains(DEPENDENCIES, LaserControl) {
		INCLUDEPATH += $${LASERCONTROL_DIR}/include
		LIBS += -L$${LASERCONTROL_DIR}/lib
		LIBS += -llaserwrapper$${DLL_SUFFIX}
		QMAKE_CXXFLAGS += -wd4996
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${LASERCONTROL_DIR}/bin\" \"$${DEPENDENCY_DIR}\" &&
	}

	## MTQ
	contains(DEPENDENCIES, MTQ) {
		INCLUDEPATH += $${MTQ_DIR}/..
		LIBS += -L$${OUT_PWD}/$${MTQ_DIR}/../$${CURRENT_CONFIG}
		LIBS += -lMTQ
		DEPENDPATH += $${MTQ_DIR}
		DEFINES += MTQ_EXPORT_MTQ=Q_DECL_IMPORT
	}

	## OpenCV
	contains(DEPENDENCIES, OpenCV) {
		INCLUDEPATH += $${OPENCV_DIR}/include
		LIBS += -L$${OPENCV_DIR}/x64/vc11/lib
		for(lib, OPENCV_LIBS): LIBS += -lopencv_$${lib}$${OPENCV_VERSION_SUFFIX}$${DLL_SUFFIX}
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${OPENCV_DIR}/x64/vc11/bin\" \"$${DEPENDENCY_DIR}\" &&

		contains(OPENCV_USING, CUDA) {
			LIBS += -L$${CUDA_DIR}/lib/x64
			QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${CUDA_DIR}/bin\" \"$${DEPENDENCY_DIR}\" &&
		}
	}

	## OpenNI
	contains(DEPENDENCIES, OpenNI) {
		INCLUDEPATH += $${OPENNI_DIR}/Include
		LIBS += -L$${OPENNI_DIR}/Lib
		LIBS += -lOpenNI2
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${OPENNI_DIR}/Redist\" \"$${DEPENDENCY_DIR}\" &&
	}

	## OSG
	contains(DEPENDENCIES, OSG) {
		INCLUDEPATH += "$${OSG_DIR}/include"
		LIBS += -L"$${OSG_DIR}/lib"
				LIBS += -losgParticle$${DLL_SUFFIX} -losgVolume$${DLL_SUFFIX} -losgFX$${DLL_SUFFIX} -losgSim$${DLL_SUFFIX} -losgAnimation$${DLL_SUFFIX} -losgShadow$${DLL_SUFFIX} -lOpenThreads$${DLL_SUFFIX} -losgViewer$${DLL_SUFFIX} -losgText$${DLL_SUFFIX} -losgTerrain$${DLL_SUFFIX} -losgQtd -losgGA$${DLL_SUFFIX} -losgManipulator$${DLL_SUFFIX} -losgDB$${DLL_SUFFIX} -losg$${DLL_SUFFIX} -losgWidget$${DLL_SUFFIX} -losgPresentation$${DLL_SUFFIX} -losgUtil$${DLL_SUFFIX}
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${OSG_DIR}/bin\" \"$${DEPENDENCY_DIR}\" &&
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${OSG_DIR}/bin/osgPlugins-$${OSG_VERSION_SUFFIX}\" \"$${DEPENDENCY_DIR}\" &&
	}

	##NatNetSDK
	contains(DEPENDENCIES, NatNetSDK) {
		INCLUDEPATH += $${NATNETSDK_DIR}/include
		LIBS += -L$${NATNETSDK_DIR}/lib/x64
		LIBS += -lNatNetLib
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${NATNETSDK_DIR}/lib/x64\" \"$${DEPENDENCY_DIR}\" &&
	}

	## Qt
	contains(DEPENDENCIES, Qt) {
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${QT_DIR}/bin\" \"$${DEPENDENCY_DIR}\" &&
		QMAKE_POST_LINK += \"$${PWD}/collect_dlls.bat\" $${CURRENT_CONFIG} \"$${QT_DIR}/plugins/platforms\" \"$${OUT_PWD}/$${TO_BASE_DIR}/$${CURRENT_CONFIG}/apps/platforms\" &&
	}

	QMAKE_POST_LINK += echo All dependencies collected.
}

unix: !macx {
	## Alvar
	contains(DEPENDENCIES, Alvar ) {
		INCLUDEPATH += $${ALVAR_DIR}
		LIBS += -lalvar200
	}

	## MTQ
	contains(DEPENDENCIES, MTQ ) {
		INCLUDEPATH += $${MTQ_DIR}
		LIBS += -L$${OUT_PWD}/$${MTQ_DIR}/../$${CURRENT_CONFIG}
		LIBS += -lMultiToeQt
	}

	## OpenCV
	contains(DEPENDENCIES, OpenCV ) {
		INCLUDEPATH += $${OPENCV_DIR}
		for(lib, OPENCV_LIBS): LIBS += -lopencv_$${lib}
	}

	## OpenNI
	contains(DEPENDENCIES, OpenNI ) {
		INCLUDEPATH += $${OPENNI_DIR}
		LIBS += -lOpenNI2
	}
}

macx {
	message("MacOS is currently not supported. Sorry, Sven ;)")
}
