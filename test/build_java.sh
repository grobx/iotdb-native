#!/bin/bash
CURRENT_DIR=`pwd`
GRADLE_BIN=`which gradle`
JAVA_BIN=`which java`
echo "Building java interoperability tests"
cd ${CURRENT_DIR}/iotdb-interop
${GRADLE_BIN} build
cd ${CURRENT_DIR}/iotdb-interop/build/libs
echo "Creating java serialized data"
java -jar iotdb-interop.jar ${CURRENT_DIR}/iotdb-interop/data
cd ${CURRENT_DIR}

