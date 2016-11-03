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
AS=gas

# Macros
CND_PLATFORM=GNU-Solaris-Sparc
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/file_handler.o \
	${OBJECTDIR}/linked_list.o \
	${OBJECTDIR}/simulator.o \
	${OBJECTDIR}/main.o


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
LDLIBSOPTIONS=-lm /dcs/dap/NAVIGATION/libnavigation.a

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shiplane

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shiplane: /dcs/dap/NAVIGATION/libnavigation.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shiplane: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shiplane ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/file_handler.o: file_handler.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/dcs/dap/NAVIGATION -MMD -MP -MF $@.d -o ${OBJECTDIR}/file_handler.o file_handler.c

${OBJECTDIR}/linked_list.o: linked_list.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/dcs/dap/NAVIGATION -MMD -MP -MF $@.d -o ${OBJECTDIR}/linked_list.o linked_list.c

${OBJECTDIR}/simulator.o: simulator.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/dcs/dap/NAVIGATION -MMD -MP -MF $@.d -o ${OBJECTDIR}/simulator.o simulator.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.c) -g -I/dcs/dap/NAVIGATION -MMD -MP -MF $@.d -o ${OBJECTDIR}/main.o main.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/shiplane

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
