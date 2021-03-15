#inlcude "../build/macosx-x86_64-server-fastdebug/support/modules_include/java.base/jni.h"
#include "../src/hotspot/share/prims/jni.cpp"

#include "../src/java.base/share/native/launcher/main.c"
/// 线程1 main
int main(int argc, char **argv);
  #include "../src/java.base/share/native/libjli/java.h"
  JNIEXPORT int JNICALL
  JLI_Launch(int argc, char ** argv,              /* main argc, argv */
             int jargc, const char** jargv,          /* java args */
             int appclassc, const char** appclassv,  /* app classpath */
             const char* fullversion,                /* full version defined */
             const char* dotversion,                 /* UNUSED dot version defined */
             const char* pname,                      /* program name */
             const char* lname,                      /* launcher name */
             jboolean javaargs,                      /* JAVA_ARGS */
             jboolean cpwildcard,                    /* classpath wildcard*/
             jboolean javaw,                         /* windows-only javaw */
             jint ergo                               /* unused */
  );
    #include "../src/java.base/macosx/native/libjli/java_md_macosx.m"
    /// 因为Mac上的限制（第一个线程留给UI），所以这里会创建新的线程重新执行main程序
    /// 线程2
    void CreateExecutionEnvironment(int *pargc, char ***pargv,
                                   char jrepath[], jint so_jrepath,
                                   char jvmpath[], jint so_jvmpath,
                                   char jvmcfg[],  jint so_jvmcfg);
      void MacOSXStartup(int argc, char *argv[]); /// 重新调用main方法，注意只会执行一次，后面不再调用
    int JVMInit(InvocationFunctions* ifn, jlong threadStackSize,
            int argc, char **argv,
            int mode, char *what, int ret);
      /// 创建新线程执行JavaMain，并且join到线程2（来自java_md_macosx.m）
      int ContinueInNewThread(InvocationFunctions* ifn, jlong threadStackSize,
                              int argc, char **argv,
                              int mode, char *what, int ret);
        /// 来自java_md_macosx.md
        /// 创建线程3，JavaMain作为入口函数（直接在线程2或者新创建一个线程都行）
        void* ThreadJavaMain(void* args);
          /// Java主程序，在这里执行Java中的main静态方法
          int JavaMain(void* _args);
            /// 创建HotSpot虚拟机的各个工作线程，比如JIT线程、GC线程等
            jboolean InitializeJVM(JavaVM **pvm, JNIEnv **penv, InvocationFunctions *ifn);
              /// jni.cpp
              jint JNI_CreateJavaVM(JavaVM **vm, void **penv, void *args);
              static jint JNI_CreateJavaVM_inner(JavaVM **vm, void **penv, void *args);
                #include "../src/hotspot/share/runtime/thread.hpp"
                /// 真正地创建各种各种各样的线程。同时将JavaThread绑定到当前操作系统线程3上
                jint Threads::create_vm(JavaVMInitArgs* args, bool* canTryAgain);
                  #include "../src/hotspot/os/bsd/os_bsd.hpp"
                  bool os::create_thread(Thread* thread, ThreadType thr_type, size_t req_stack_size);
                    #include "../src/hotspot/os/bsd/os_bsd.hpp"
                    void *thread_native_entry(Thread *thread); /// 线程执行入口
                  #include "../src/hotspot/share/runtime/init.hpp"
                  jint init_globals(); /// 初始化常见的类
            /// 加载含有main方法的类
            static jclass LoadMainClass(JNIEnv *env, int mode, char *name);
            #include "../src/hotspot/share/runtime/javaCalls.hpp"
            /// 调用java中的main方法
            void JavaCalls::call(JavaValue* result, const methodHandle& method, JavaCallArguments* args, TRAPS);