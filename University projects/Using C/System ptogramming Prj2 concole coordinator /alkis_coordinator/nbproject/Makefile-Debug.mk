#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/Chain.o \
	${OBJECTDIR}/Database.o \
	${OBJECTDIR}/Pool.o \
	${OBJECTDIR}/PoolChain.o \
	${OBJECTDIR}/PoolDatabase.o \
	${OBJECTDIR}/PoolWorld.o \
	${OBJECTDIR}/World.o \
	${OBJECTDIR}/main_coordinator.o \
	${OBJECTDIR}/main_pool.o \
	${OBJECTDIR}/pipebuffer.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alkis_coordinator

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alkis_coordinator: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/alkis_coordinator ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/Chain.o: Chain.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Chain.o Chain.cpp

${OBJECTDIR}/Database.o: Database.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Database.o Database.cpp

${OBJECTDIR}/Pool.o: Pool.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Pool.o Pool.cpp

${OBJECTDIR}/PoolChain.o: PoolChain.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PoolChain.o PoolChain.cpp

${OBJECTDIR}/PoolDatabase.o: PoolDatabase.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PoolDatabase.o PoolDatabase.cpp

${OBJECTDIR}/PoolWorld.o: PoolWorld.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/PoolWorld.o PoolWorld.cpp

${OBJECTDIR}/World.o: World.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/World.o World.cpp

${OBJECTDIR}/main_coordinator.o: main_coordinator.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_coordinator.o main_coordinator.cpp

${OBJECTDIR}/main_pool.o: main_pool.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main_pool.o main_pool.cpp

${OBJECTDIR}/pipebuffer.o: pipebuffer.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -Wall -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/pipebuffer.o pipebuffer.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
