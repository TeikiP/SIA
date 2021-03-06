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


SET(CPACK_ARCHIVE_COMPONENT_INSTALL "ON")
SET(CPACK_BINARY_7Z "")
SET(CPACK_BINARY_BUNDLE "")
SET(CPACK_BINARY_CYGWIN "")
SET(CPACK_BINARY_DEB "")
SET(CPACK_BINARY_DRAGNDROP "")
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
SET(CPACK_BUILD_SOURCE_DIRS "/net/cremi/tepepin/SIA/TD6/sia_td6;/net/cremi/tepepin/SIA/TD6/sia_td6")
SET(CPACK_CMAKE_GENERATOR "Unix Makefiles")
SET(CPACK_COMMAND "/usr/bin/cpack")
SET(CPACK_COMPONENTS_ALL "runtime;tools;dev")
SET(CPACK_COMPONENTS_ALL_SET_BY_USER "TRUE")
SET(CPACK_COMPONENT_DEV_DEPENDS "runtime")
SET(CPACK_COMPONENT_DEV_DESCRIPTION "Development files for glbinding library")
SET(CPACK_COMPONENT_DEV_DISPLAY_NAME "C/C++ development files")
SET(CPACK_COMPONENT_INCLUDE_TOPLEVEL_DIRECTORY "OFF")
SET(CPACK_COMPONENT_RUNTIME_DESCRIPTION "Runtime components for glbinding library")
SET(CPACK_COMPONENT_RUNTIME_DISPLAY_NAME "Library")
SET(CPACK_COMPONENT_TOOLS_DEPENDS "runtime")
SET(CPACK_COMPONENT_TOOLS_DESCRIPTION "Tools for glbinding library")
SET(CPACK_COMPONENT_TOOLS_DISPLAY_NAME "Tools")
SET(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
SET(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "all")
SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "")
SET(CPACK_DEBIAN_PACKAGE_DESCRIPTION "A C++ binding for the OpenGL API, generated using the gl.xml specification.")
SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "opensource@cginternals.com")
SET(CPACK_DEBIAN_PACKAGE_NAME "glbinding")
SET(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
SET(CPACK_DEBIAN_PACKAGE_SECTION "devel")
SET(CPACK_DEBIAN_PACKAGE_VERSION "2.1.1")
SET(CPACK_DEB_COMPONENT_INSTALL "ON")
SET(CPACK_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_IGNORE_FILES "")
SET(CPACK_INCLUDE_TOPLEVEL_DIRECTORY "OFF")
SET(CPACK_INSTALLED_DIRECTORIES "")
SET(CPACK_INSTALL_CMAKE_PROJECTS "")
SET(CPACK_INSTALL_PREFIX "/usr/local")
SET(CPACK_MODULE_PATH "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/deploy/packages/glbinding")
SET(CPACK_NSIS_DISPLAY_NAME "glbinding")
SET(CPACK_NSIS_INSTALLER_ICON_CODE "")
SET(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
SET(CPACK_NSIS_MUI_ICON "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/deploy/images/logo.ico")
SET(CPACK_NSIS_MUI_UNIICON "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/deploy/images/logo.ico")
SET(CPACK_NSIS_PACKAGE_NAME "glbinding")
SET(CPACK_OUTPUT_CONFIG_FILE "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/CPackConfig-glbinding.cmake")
SET(CPACK_PACKAGE_DEFAULT_LOCATION "/")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/README.md")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A C++ binding for the OpenGL API, generated using the gl.xml specification.")
SET(CPACK_PACKAGE_FILE_NAME "")
SET(CPACK_PACKAGE_ICON "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/deploy/images/logo.bmp")
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "glbinding")
SET(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "glbinding")
SET(CPACK_PACKAGE_NAME "glbinding")
SET(CPACK_PACKAGE_RELOCATABLE "false")
SET(CPACK_PACKAGE_VENDOR "CG Internals GmbH")
SET(CPACK_PACKAGE_VERSION "2.1.1")
SET(CPACK_PACKAGE_VERSION_MAJOR "2")
SET(CPACK_PACKAGE_VERSION_MINOR "1")
SET(CPACK_PACKAGE_VERSION_PATCH "1")
SET(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
SET(CPACK_PATH "/usr/bin")
SET(CPACK_RESOURCE_FILE_LICENSE "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/LICENSE")
SET(CPACK_RESOURCE_FILE_README "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/README.md")
SET(CPACK_RESOURCE_FILE_WELCOME "/net/cremi/tepepin/SIA/TD6/sia_td6/ext/glbinding/README.md")
SET(CPACK_RPM_COMPONENT_INSTALL "ON")
SET(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
SET(CPACK_RPM_PACKAGE_DESCRIPTION "")
SET(CPACK_RPM_PACKAGE_GROUP "unknown")
SET(CPACK_RPM_PACKAGE_LICENSE "MIT")
SET(CPACK_RPM_PACKAGE_NAME "glbinding")
SET(CPACK_RPM_PACKAGE_PROVIDES "")
SET(CPACK_RPM_PACKAGE_RELEASE "1")
SET(CPACK_RPM_PACKAGE_RELOCATABLE "OFF")
SET(CPACK_RPM_PACKAGE_REQUIRES "")
SET(CPACK_RPM_PACKAGE_SOURCES "ON")
SET(CPACK_RPM_PACKAGE_SUMMARY "A C++ binding for the OpenGL API, generated using the gl.xml specification.")
SET(CPACK_RPM_PACKAGE_VENDOR "CG Internals GmbH")
SET(CPACK_RPM_PACKAGE_VERSION "2.1.1")
SET(CPACK_SET_DESTDIR "OFF")
SET(CPACK_SOURCE_7Z "")
SET(CPACK_SOURCE_CYGWIN "")
SET(CPACK_SOURCE_GENERATOR "TBZ2;TGZ;TXZ;TZ")
SET(CPACK_SOURCE_IGNORE_FILES "")
SET(CPACK_SOURCE_INSTALLED_DIRECTORIES "")
SET(CPACK_SOURCE_OUTPUT_CONFIG_FILE "/net/cremi/tepepin/SIA/TD6/sia_td6/CPackSourceConfig.cmake")
SET(CPACK_SOURCE_PACKAGE_FILE_NAME "")
SET(CPACK_SOURCE_RPM "OFF")
SET(CPACK_SOURCE_TBZ2 "ON")
SET(CPACK_SOURCE_TGZ "ON")
SET(CPACK_SOURCE_TOPLEVEL_TAG "")
SET(CPACK_SOURCE_TXZ "ON")
SET(CPACK_SOURCE_TZ "ON")
SET(CPACK_SOURCE_ZIP "OFF")
SET(CPACK_STRIP_FILES "")
SET(CPACK_SYSTEM_NAME "Linux")
SET(CPACK_TOPLEVEL_TAG "")
SET(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "/net/cremi/tepepin/SIA/TD6/sia_td6/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
