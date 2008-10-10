#include <stdio.h>
#include <jni.h>
#include "p2pproxy.h"

#ifndef P2PPROXY_JMX_PORT
	#define P2PPROXY_JMX_PORT "5678"
#endif
#ifndef P2PPROXY_INSTALLDIR
	#define P2PPROXY_INSTALLDIR "/usr/local/share/java"
#endif 
#ifndef P2PPROXY_BUILDDIR
	#define P2PPROXY_BUILDDIR ".././antbuild/dist/p2pproxy_0.1"
#endif
JNIEnv* p2pproxy_application_jnienv = 0;
JavaVM* p2pproxy_application_jvm = 0;
jclass  p2pproxy_proxy_main_class = 0;

int p2pproxy_application_start(int argc, char **argv) {

	JavaVMInitArgs args;
	JavaVMOption options[7];
	jint res=-1;
	jclass lP2pProxyMainClass=0;
	jmethodID mainMethod;
	jobjectArray applicationArgsList;
	jstring applicationArg;
	int i=0;

	if (p2pproxy_application_jnienv != 0) {
		fprintf(stderr,"p2pproxy already started");
		return P2PPROXY_ERROR_APPLICATION_ALREADY_STARTED;
	}
	args.version = JNI_VERSION_1_4;
	args.nOptions = 7;
	/*options[0].optionString = "-verbose:jni";*/
	options[0].optionString = "-Djava.class.path="P2PPROXY_BUILDDIR"/p2pproxy.jar:"\
								P2PPROXY_INSTALLDIR"/p2pproxy.jar:"\
								P2PPROXY_BUILDDIR"/log4j.jar:"\
								P2PPROXY_INSTALLDIR"/log4j.jar";



	options[1].optionString = "-Dcom.sun.management.jmxremote";
	options[2].optionString = "-Dcom.sun.management.jmxremote.port="P2PPROXY_JMX_PORT;
	options[3].optionString = "-Dcom.sun.management.jmxremote.authenticate=false";
	options[4].optionString = "-Dcom.sun.management.jmxremote.ssl=false";
	options[5].optionString = "-Dorg.linphone.p2pproxy.install.dir="P2PPROXY_INSTALLDIR;
	options[6].optionString = "-Dorg.linphone.p2pproxy.build.dir="P2PPROXY_BUILDDIR;


	args.options = options;
	args.ignoreUnrecognized = JNI_FALSE;

	res = JNI_CreateJavaVM(&p2pproxy_application_jvm, (void **)&p2pproxy_application_jnienv, &args);
	if (res < 0) {
		fprintf(stderr,"cannot start p2pproxy vm [%i]",res);
		return P2PPROXY_ERROR;
	}

	p2pproxy_proxy_main_class = (*p2pproxy_application_jnienv)->FindClass(p2pproxy_application_jnienv, "org/linphone/p2pproxy/core/P2pProxyMain");

	if (lP2pProxyMainClass == 0) {
		fprintf(stderr,"cannot find class org/linphone/p2pproxy/core/P2pProxyMain");
		return P2PPROXY_ERROR;
	}
	mainMethod = (*p2pproxy_application_jnienv)->GetStaticMethodID(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, "main", "([Ljava/lang/String;)V");

	applicationArgsList = (*p2pproxy_application_jnienv)->NewObjectArray(p2pproxy_application_jnienv, argc, (*p2pproxy_application_jnienv)->FindClass(p2pproxy_application_jnienv, "java/lang/String"), NULL);
	
	for (i=0;i<argc;i++) {
		applicationArg = (*p2pproxy_application_jnienv)->NewStringUTF(p2pproxy_application_jnienv, *argv++);
		(*p2pproxy_application_jnienv)->SetObjectArrayElement(p2pproxy_application_jnienv, applicationArgsList, 0, applicationArg);

	}

	(*p2pproxy_application_jnienv)->CallStaticVoidMethod(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, mainMethod, applicationArgsList);

	return P2PPROXY_NO_ERROR;
}


const char* p2pproxy_status_string(int status_code) {
	return 0;
}


int p2pproxy_accountmgt_createAccount(const char* user_name) {
	jmethodID createAccountMethod;
	jstring applicationArg; 
	
	createAccountMethod = (*p2pproxy_application_jnienv)->GetStaticMethodID(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, "createAccount", "([java/lang/String;)I");
	applicationArg = (*p2pproxy_application_jnienv)->NewStringUTF(p2pproxy_application_jnienv, user_name);
	return (*p2pproxy_application_jnienv)->CallStaticIntMethod(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, createAccountMethod, applicationArg);
}

int p2pproxy_accountmgt_isValidAccount(const char* user_name) {
	jmethodID isValidAccountMethod;
	jstring applicationArg; 
	
	isValidAccountMethod = (*p2pproxy_application_jnienv)->GetStaticMethodID(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, "isValidAccount", "([java/lang/String;)I");
	applicationArg = (*p2pproxy_application_jnienv)->NewStringUTF(p2pproxy_application_jnienv, user_name);
	return (*p2pproxy_application_jnienv)->CallStaticIntMethod(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, isValidAccountMethod, applicationArg);
}

int p2pproxy_accountmgt_deleteAccount(const char* user_name) {
	jmethodID deleteAccountMethod;
	jstring applicationArg; 
	
	deleteAccountMethod = (*p2pproxy_application_jnienv)->GetStaticMethodID(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, "deleteAccount", "([java/lang/String;)I");
	applicationArg = (*p2pproxy_application_jnienv)->NewStringUTF(p2pproxy_application_jnienv, user_name);
	return (*p2pproxy_application_jnienv)->CallStaticIntMethod(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, deleteAccountMethod, applicationArg);
}

int p2pproxy_resourcelocation_get_sip_proxyregistrar_uri(char* aStringArray, size_t aSize) {
	jmethodID getSipProxyRegistrarUriMethod;
	jstring lJStringResult; 
	const jbyte* lString;
	jboolean  lIsCopy;
	
	getSipProxyRegistrarUriMethod = (*p2pproxy_application_jnienv)->GetStaticMethodID(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, "getSipProxyRegistrarUriMethod", "()[java/lang/String;");
	lJStringResult = (*p2pproxy_application_jnienv)->CallStaticObjectMethod(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, getSipProxyRegistrarUriMethod);
	if (lJStringResult == 0) {
		return P2PPROXY_ERROR_RESOURCELOCATOR_SERVER_NOT_FOUND;
	}
	lString =  (*p2pproxy_application_jnienv)->GetStringUTFChars(p2pproxy_application_jnienv, lJStringResult, &lIsCopy);
	memcpy(aStringArray,lString,aSize);
	(*p2pproxy_application_jnienv)->ReleaseStringUTFChars(p2pproxy_application_jnienv, lJStringResult, lString);
	return P2PPROXY_NO_ERROR;
}

int p2pproxy_application_get_state() {
	jmethodID stateMethod;
	
	stateMethod = (*p2pproxy_application_jnienv)->GetStaticMethodID(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, "getState", "()I");
	return (*p2pproxy_application_jnienv)->CallStaticIntMethod(p2pproxy_application_jnienv, p2pproxy_proxy_main_class, stateMethod);
	
}

