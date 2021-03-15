// Zero Interpreter
// cpp call java method
#include "../src/hotspot/share/runtime/javaCalls.hpp"
void JavaCalls::call(JavaValue* result, const methodHandle& method, JavaCallArguments* args, TRAPS);
	void JavaCalls::call_helper(JavaValue* result, const methodHandle& method, JavaCallArguments* args, TRAPS);
    #include "../src/hotspot/share/runtime/stubRoutines.hpp"
	  // 返回方法调用的入口，实际设置的为zero中的call_stub
    CallStub StubRoutines::call_stub();
      #include "../src/hotspot/cpu/zero/stubGenerator_zero.cpp"
      // 上面返回的正式这个函数，设置位置见说明1
      // 功能：1. 分配JVM Stack；2. 创建EntryFrame
      void StubGenerator::call_stub(
         JavaCallWrapper *call_wrapper,
         intptr_t*        result,
         BasicType        result_type,
         Method*          method,
         address          entry_point,
         intptr_t*        parameters,
         int              parameter_words,
         TRAPS);
        #include "../src/hotspot/share/interpreter/zero/zeroInterpreter.hpp"
        void ZeroInterpreter::invoke_method(Method* method, address entry_point, TRAPS);
          #include "../src/hotspot/cpu/zero/entry_zero.hpp"
          void ZeroEntry::invoke(Method* method, TRAPS) const;
            #include "../src/hotspot/cpu/zero/zeroInterpreter_zero.hpp"
            // normal_entry的设置时机见下面的说明2
            // 功能：创建执行方法用的frame结构
            int ZeroInterpreter::normal_entry(Method* method, intptr_t UNUSED, TRAPS);
              void ZeroInterpreter::main_loop(int recurse, TRAPS);
                #include "../src/hotspot/share/interpreter/zero/bytecodeInterpreter.hpp"
                void BytecodeInterpreter::run(interpreterState istate);
                  // 如果执行的是调用其他方法的指令，则继续执行invoke_method
                  void ZeroInterpreter::invoke_method(Method* method, address entry_point, TRAPS);

#include "../src/hotspot/cpu/zero/stubGenerator_zero.cpp"
// 说明1：设置call_stub入口为zero的call_stub
void StubGenerator::generate_initial();
#include "../src/hotspot/share/interpreter/zero/zeroInterpreterGenerator.hpp"
// 说明2：设置每种方法的入口函数
void ZeroInterpreterGenerator::generate_all();
  address ZeroInterpreterGenerator::generate_method_entry(AbstractInterpreter::MethodKind kind);
#include "../src/hotspot/share/oops/method.hpp"
// 说明3：链接java方法，也就是设置解释器入口
void Method::link_method(const methodHandle& h_method, TRAPS);

// java call cpp
#include "../src/hotspot/share/oops/method.hpp"
// 给Klass注册native方法的实际入口
bool Method::register_native(Klass* k, Symbol* name, Symbol* signature, address entry, TRAPS);
  #include "../src/hotspot/share/classfile/javaClasses.hpp"
  // 比如这里是通过直接调用
  void java_lang_Object::register_natives(TRAPS);
  #include "../src/hotspot/share/prims/jni.cpp"
  // 比如这里是先创建一个Class对应的Java原生方法RegisterNatives，这个方法的作用是注册其他的原生方法到Java中
  JNI_ENTRY(jint, jni_RegisterNatives(JNIEnv *env, jclass clazz,
                                      const JNINativeMethod *methods,
                                      jint nMethods));