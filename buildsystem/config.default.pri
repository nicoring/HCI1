########################################################################
#																	   #
# This file contains default paths and configurations known to work	   #
# In case you are using a different setup copy this file to config.pri #
# and adjust the variables as needed.								   #
# QMake will then use config.pri, which is ignored by Git.			   #
#																	   #
########################################################################

COMPILER = $${basename(QMAKESPEC)}

win32 {
	COPY_TO_ATRIUM_DIR = "X:/HCI-MT/executables"
	COPY_TO_FLOOR_DIR = "Z:/HCI-MT/executables"

	COMMON_DEPENDENCY_PATH = Z:/lib_msvc11

	ALVAR_DIR = $${COMMON_DEPENDENCY_PATH}/alvar/2.0.0

	BOOST_DIR = $${COMMON_DEPENDENCY_PATH}/boost/1.55.0
	CONFIG( debug, debug|release ) { #debug
		BOOST_SUFFIX = -vc110-mt-gd-1_55
	} else { # release
		BOOST_SUFFIX = -vc110-mt-1_55
	}

	GRAVITY_SPACE_DIR = $${COMMON_DEPENDENCY_PATH}/GravitySpace
	GRAVITY_SPACE_USING += CUDA SiftGPU

	ICU_DIR = $${COMMON_DEPENDENCY_PATH}/icu

	LASERCONTROL_DIR = $${COMMON_DEPENDENCY_PATH}/LaserControl

	NATNETSDK_DIR = $${COMMON_DEPENDENCY_PATH}/NatNetSDK

	OPENCV_DIR = $${COMMON_DEPENDENCY_PATH}/opencv/2.4.8_release_with_cuda
	CUDA_DIR = $${COMMON_DEPENDENCY_PATH}/CUDA/v5.5
	CONFIG( debug, debug|release ) { #debug
	} else { # release
		OPENCV_USING += CUDA
	}

	OPENCV_VERSION_SUFFIX = 248

	QT_DIR = $${COMMON_DEPENDENCY_PATH}/Qt/5.2.0/msvc2012_64_opengl

	OSG_DIR = $${COMMON_DEPENDENCY_PATH}/OpenSceneGraph/3.2.0
	OSG_VERSION_SUFFIX = 3.2.0

	SIFT_GPU_DIR = $${COMMON_DEPENDENCY_PATH}/SiftGPU
}

unix: !macx {
	COMMON_DEPENDENCY_PATH = /usr/local/include

	ALVAR_DIR = $${COMMON_DEPENDENCY_PATH}/alvar

	OPENCV_DIR = $${COMMON_DEPENDENCY_PATH}/opencv2

	OPENNI_DIR = $${COMMON_DEPENDENCY_PATH}/openni
}
