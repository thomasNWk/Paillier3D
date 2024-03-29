# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
SET(CPACK_BINARY_FREEBSD "")
SET(CPACK_BINARY_IFW "")
SET(CPACK_BINARY_NSIS "")
SET(CPACK_BINARY_OSXX11 "")
SET(CPACK_BINARY_PACKAGEMAKER "")
SET(CPACK_BINARY_PRODUCTBUILD "")
SET(CPACK_BINARY_RPM "")
SET(CPACK_BINARY_STGZ "")
SET(CPACK_BINARY_TBZ2 "")
SET(CPACK_BINARY_TGZ "")
SET(CPACK_BINARY_TXZ "")
SET(CPACK_BINARY_TZ "")
SET(CPACK_BINARY_WIX "")
SET(CPACK_BINARY_ZIP "")
SET(CPACK_BUILD_SOURCE_DIRS "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master;/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/build")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMPONENTS_ALL "devel;lib;examples")
SET(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
SET(CPACK_COMPONENT_DEVEL_DESCRIPTION "Header Files for C and ISPC required to develop applications with Embree.")
SET(CPACK_COMPONENT_DEVEL_DISPLAY_NAME "Development")
SET(CPACK_COMPONENT_EXAMPLES_DESCRIPTION "Tutorials demonstrating how to use Embree.")
SET(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "Examples")
SET(CPACK_COMPONENT_LIB_DESCRIPTION "The Embree library including documentation.")
SET(CPACK_COMPONENT_LIB_DISPLAY_NAME "Library")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
SET(CPACK_INSTALLED_DIRECTORIES "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master;/")
SET(CPACK_INSTALL_CMAKE_PROJECTS "")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/libigl/external/embree/common/cmake;/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/cmake;/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/libigl/cmake;/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/libigl")
SET(CPACK_NSIS_DISPLAY_NAME "Embree Ray Tracing Kernels 3.5.2")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
SET(CPACK_NSIS_PACKAGE_NAME "Embree Ray Tracing Kernels 3.5.2")
SET(CPACK_OUTPUT_CONFIG_FILE "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/build/CPackConfig.cmake")
SET(CPACK_PACKAGE_CONTACT "embree_support@intel.com")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.10/Templates/CPack.GenericDescription.txt")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Embree: High Performance Ray Tracing Kernels")
SET(CPACK_PACKAGE_FILE_NAME "Embree Ray Tracing Kernels-3.5.2-Source")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "Embree Ray Tracing Kernels 3.5.2")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "Embree Ray Tracing Kernels 3.5.2")
SET(CPACK_PACKAGE_NAME "Embree Ray Tracing Kernels")
SET(CPACK_PACKAGE_RELOCATABLE "true")
SET(CPACK_PACKAGE_VENDOR "Intel Corporation")
SET(CPACK_PACKAGE_VERSION "3.5.2")
SET(CPACK_PACKAGE_VERSION_MAJOR "3")
SET(CPACK_PACKAGE_VERSION_MINOR "5")
SET(CPACK_PACKAGE_VERSION_PATCH "2")
SET(CPACK_RESOURCE_FILE_LICENSE "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/libigl/external/embree/LICENSE.txt")
SET(CPACK_RESOURCE_FILE_README "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/libigl/external/embree/README.md")
SET(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.10/Templates/CPack.GenericWelcome.txt")
SET(CPACK_RPM_CHANGELOG_FILE "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/build/rpm_changelog.txt")
SET(CPACK_RPM_COMPONENT_INSTALL "ON")
SET(CPACK_RPM_DEFAULT_DIR_PERMISSIONS "OWNER_READ;OWNER_WRITE;OWNER_EXECUTE;GROUP_READ;GROUP_EXECUTE;WORLD_READ;WORLD_EXECUTE")
SET(CPACK_RPM_FILE_NAME "RPM-DEFAULT")
SET(CPACK_RPM_PACKAGE_GROUP "Development/Libraries")
SET(CPACK_RPM_PACKAGE_LICENSE "ASL 2.0")
SET(CPACK_RPM_PACKAGE_NAME "embree3")
SET(CPACK_RPM_PACKAGE_RELEASE "1")
SET(CPACK_RPM_PACKAGE_SOURCES "ON")
SET(CPACK_RPM_PACKAGE_URL "http://embree.github.io/")
SET(CPACK_RPM_devel_PACKAGE_ARCHITECTURE "noarch")
SET(CPACK_RPM_lib_POST_INSTALL_SCRIPT_FILE "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/libigl/external/embree/common/cmake/rpm_ldconfig.sh")
SET(CPACK_RPM_lib_POST_UNINSTALL_SCRIPT_FILE "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/libigl/external/embree/common/cmake/rpm_ldconfig.sh")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_SOURCE_IGNORE_FILES "/CVS/;/\\.svn/;/\\.bzr/;/\\.hg/;/\\.git/;\\.swp\$;\\.#;/#")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master;/")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/build/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "Embree Ray Tracing Kernels-3.5.2-Source")
SET(CPACK_SOURCE_RPM "OFF")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_SOURCE_TXZ "ON")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "Linux")
SET(CPACK_TOPLEVEL_TAG "Linux-Source")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/media/nwk/Data/Travail/MASTER_2/Codage_Compression/Encryption3D-master/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
