//
// Created by jozoppi on 5/16/20.
//
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
#include "java_executor.h"
java_executor::java_executor() {
    options = new JavaVMOption[1];
    options[0].optionString = "-Djava.class.path=/usr/lib/java";
    vm_args.version = JNI_VERSION_11;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;
    JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    delete options;
}
std::string java_executor::execute_method(const std::string &className, const std::string &method) {
    jclass cls = env->FindClass(className.c_str());
    jmethodID getStringMethod = env->GetMethodID(cls, method.c_str(), "()Ljava/lang/String;");
    rv = env->CallStaticVoidMethod(cls, mid, 100);
    const char *strReturn = env->GetStringUTFChars(env, rv, 0);
    return std::string(strReturn);
}
java_executor::~java_executor() {
    jvm->DestroyJavaVM();
}