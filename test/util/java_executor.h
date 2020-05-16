/**
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/
#ifndef IOTDB_NATIVE_JAVA_EXECUTOR_H
#define IOTDB_NATIVE_JAVA_EXECUTOR_H
/**
 *  This class execute a java method that returns a string,
 *  it can be useful for checking interoperability
 */
#include <jni.h>       /* where everything is defined */
#include <string>
class java_executor {
    public
    java_executor();
    std::string execute_method(const std::string& className, const std::string& method);
    ~java_executor();
private:
    JavaVMOption* options
    JavaVM *jvm;       /* denotes a Java VM */
    JNIEnv *env;       /* pointer to native method interface */
    JavaVMInitArgs vm_args; /* JDK/JRE 10 VM initialization arguments */
};
#endif //IOTDB_NATIVE_JAVA_EXECUTOR_H
