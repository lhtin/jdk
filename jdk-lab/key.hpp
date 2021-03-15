#include "../src/java.base/share/native/libjli/java.c"
int JavaMain(void* _args);

#include "../src/hotspot/share/prims/jni.cpp"
static void jni_invoke_static(JNIEnv *env, JavaValue* result, jobject receiver, JNICallType call_type, jmethodID method_id, JNI_ArgumentPusher *args, TRAPS);

#include "../src/hotspot/share/runtime/javaCalls.hpp"
void JavaCalls::call(JavaValue* result, const methodHandle& method, JavaCallArguments* args, TRAPS);
  void JavaCalls::call_helper(JavaValue* result, const methodHandle& method, JavaCallArguments* args, TRAPS);

#include "../src/hotspot/share/memory/memRegion.hpp"
class MemRegion;

#include "../src/hotspot/share/oops/symbol.hpp"
class Symbol;
  char* Symbol::as_C_string() const;

#include "../src/hotspot/share/runtime/arguments.hpp"
jint Arguments::apply_ergo(); /// 根据运行环境动态确认虚拟机启动参数


#include "../src/hotspot/share/classfile/fieldLayoutBuilder.hpp"
FieldLayoutBuilder::FieldLayoutBuilder(const Symbol* classname, const InstanceKlass* super_klass, ConstantPool* constant_pool,
                                       Array<u2>* fields, bool is_contended, FieldLayoutInfo* info);
void FieldLayoutBuilder::build_layout();
  void FieldLayoutBuilder::compute_regular_layout();
    void FieldLayoutBuilder::prologue(); /// 收集父类的fields
      void FieldLayout::initialize_instance_layout(const InstanceKlass* super_klass);
        bool FieldLayout::reconstruct_layout(const InstanceKlass* ik);
        void FieldLayout::fill_holes(const InstanceKlass* super_klass);
    void FieldLayoutBuilder::regular_field_sorting(); /// 收集类的fields并进行排序
    /// 添加到layout中
    void FieldLayout::add(GrowableArray<LayoutRawBlock*>* list, LayoutRawBlock* start);
    void FieldLayoutBuilder::epilogue(); /// 记录收集后的信息

FieldLayoutBuilder::build_layout() fieldLayoutBuilder.cpp:716
ClassFileParser::post_process_parsed_stream(ClassFileStream const*, ConstantPool*, Thread*) classFileParser.cpp:6281
ClassFileParser::ClassFileParser(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const*, ClassFileParser::Publicity, Thread*) classFileParser.cpp:5825
KlassFactory::create_from_stream(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const&, Thread*) klassFactory.cpp:200
SystemDictionary::resolve_from_stream(Symbol*, Handle, Handle, ClassFileStream*, Thread*) systemDictionary.cpp:1147
jvm_define_class_common(char const*, _jobject*, signed char const*, int, _jobject*, char const*, Thread*) jvm.cpp:967
::JVM_DefineClassWithSource(JNIEnv *, const char *, jobject, const jbyte *, jsize, jobject, const char *) jvm.cpp:1146
Java_java_lang_ClassLoader_defineClass1 ClassLoader.c:132
<unknown> 0x00000001107c70c9
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107b7d4a
JavaCalls::call_helper(JavaValue*, methodHandle const&, JavaCallArguments*, Thread*) javaCalls.cpp:427
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:341
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:196
JavaCalls::call_virtual(JavaValue*, Handle, Klass*, Symbol*, Symbol*, Handle, Thread*) javaCalls.cpp:209
SystemDictionary::load_instance_class(Symbol*, Handle, Thread*) systemDictionary.cpp:1606
SystemDictionary::resolve_instance_class_or_null(Symbol*, Handle, Handle, Thread*) systemDictionary.cpp:874
SystemDictionary::resolve_super_or_fail(Symbol*, Symbol*, Handle, Handle, bool, Thread*) systemDictionary.cpp:445
ClassFileParser::post_process_parsed_stream(ClassFileStream const*, ConstantPool*, Thread*) classFileParser.cpp:6225
ClassFileParser::ClassFileParser(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const*, ClassFileParser::Publicity, Thread*) classFileParser.cpp:5825
KlassFactory::create_from_stream(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const&, Thread*) klassFactory.cpp:200
SystemDictionary::resolve_from_stream(Symbol*, Handle, Handle, ClassFileStream*, Thread*) systemDictionary.cpp:1147
jvm_define_class_common(char const*, _jobject*, signed char const*, int, _jobject*, char const*, Thread*) jvm.cpp:967
::JVM_DefineClassWithSource(JNIEnv *, const char *, jobject, const jbyte *, jsize, jobject, const char *) jvm.cpp:1146
Java_java_lang_ClassLoader_defineClass1 ClassLoader.c:132
<unknown> 0x00000001107c70c9
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107b7d4a
JavaCalls::call_helper(JavaValue*, methodHandle const&, JavaCallArguments*, Thread*) javaCalls.cpp:427
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:341
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:196
JavaCalls::call_virtual(JavaValue*, Handle, Klass*, Symbol*, Symbol*, Handle, Thread*) javaCalls.cpp:209
SystemDictionary::load_instance_class(Symbol*, Handle, Thread*) systemDictionary.cpp:1606
SystemDictionary::resolve_instance_class_or_null(Symbol*, Handle, Handle, Thread*) systemDictionary.cpp:874
SystemDictionary::resolve_super_or_fail(Symbol*, Symbol*, Handle, Handle, bool, Thread*) systemDictionary.cpp:445
ClassFileParser::post_process_parsed_stream(ClassFileStream const*, ConstantPool*, Thread*) classFileParser.cpp:6225
ClassFileParser::ClassFileParser(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const*, ClassFileParser::Publicity, Thread*) classFileParser.cpp:5825
KlassFactory::create_from_stream(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const&, Thread*) klassFactory.cpp:200
SystemDictionary::resolve_from_stream(Symbol*, Handle, Handle, ClassFileStream*, Thread*) systemDictionary.cpp:1147
jvm_define_class_common(char const*, _jobject*, signed char const*, int, _jobject*, char const*, Thread*) jvm.cpp:967
::JVM_DefineClassWithSource(JNIEnv *, const char *, jobject, const jbyte *, jsize, jobject, const char *) jvm.cpp:1146
Java_java_lang_ClassLoader_defineClass1 ClassLoader.c:132
<unknown> 0x00000001107c70c9
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107b7d4a
JavaCalls::call_helper(JavaValue*, methodHandle const&, JavaCallArguments*, Thread*) javaCalls.cpp:427
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:341
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:196
JavaCalls::call_virtual(JavaValue*, Handle, Klass*, Symbol*, Symbol*, Handle, Thread*) javaCalls.cpp:209
SystemDictionary::load_instance_class(Symbol*, Handle, Thread*) systemDictionary.cpp:1606
SystemDictionary::resolve_instance_class_or_null(Symbol*, Handle, Handle, Thread*) systemDictionary.cpp:874
SystemDictionary::resolve_super_or_fail(Symbol*, Symbol*, Handle, Handle, bool, Thread*) systemDictionary.cpp:445
ClassFileParser::post_process_parsed_stream(ClassFileStream const*, ConstantPool*, Thread*) classFileParser.cpp:6225
ClassFileParser::ClassFileParser(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const*, ClassFileParser::Publicity, Thread*) classFileParser.cpp:5825
KlassFactory::create_from_stream(ClassFileStream*, Symbol*, ClassLoaderData*, ClassLoadInfo const&, Thread*) klassFactory.cpp:200
SystemDictionary::resolve_from_stream(Symbol*, Handle, Handle, ClassFileStream*, Thread*) systemDictionary.cpp:1147
jvm_define_class_common(char const*, _jobject*, signed char const*, int, _jobject*, char const*, Thread*) jvm.cpp:967
::JVM_DefineClassWithSource(JNIEnv *, const char *, jobject, const jbyte *, jsize, jobject, const char *) jvm.cpp:1146
Java_java_lang_ClassLoader_defineClass1 ClassLoader.c:132
<unknown> 0x00000001107c70c9
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107c03ea
<unknown> 0x00000001107b7d4a
JavaCalls::call_helper(JavaValue*, methodHandle const&, JavaCallArguments*, Thread*) javaCalls.cpp:427
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:341
JavaCalls::call_virtual(JavaValue*, Klass*, Symbol*, Symbol*, JavaCallArguments*, Thread*) javaCalls.cpp:196
JavaCalls::call_virtual(JavaValue*, Handle, Klass*, Symbol*, Symbol*, Handle, Thread*) javaCalls.cpp:209
SystemDictionary::load_instance_class(Symbol*, Handle, Thread*) systemDictionary.cpp:1606
SystemDictionary::resolve_instance_class_or_null(Symbol*, Handle, Handle, Thread*) systemDictionary.cpp:874
SystemDictionary::resolve_or_fail(Symbol*, Handle, Handle, bool, Thread*) systemDictionary.cpp:276
SystemDictionary::resolve_or_fail(Symbol*, Handle, Handle, bool, Thread*) systemDictionary.cpp:224
ConstantPool::klass_at_impl(constantPoolHandle const&, int, bool, Thread*) constantPool.cpp:526
InterpreterRuntime::_new(JavaThread*, ConstantPool*, int) constantPool.hpp:421
InterpreterRuntime::_new(JavaThread*, ConstantPool*, int) interpreterRuntime.cpp:218
<unknown> 0x00000001107dbb9b
<unknown> 0x00000001107b7d4a
JavaCalls::call_helper(JavaValue*, methodHandle const&, JavaCallArguments*, Thread*) javaCalls.cpp:427
jni_invoke_static(JNIEnv_*, JavaValue*, _jobject*, JNICallType, _jmethodID*, JNI_ArgumentPusher*, Thread*) jni.cpp:980
::jni_CallStaticVoidMethod(JNIEnv *, jclass, jmethodID, ...) jni.cpp:1836
JavaMain java.c:550
ThreadJavaMain java_md_macosx.m:720
_pthread_start 0x00007fff70643109
thread_start 0x00007fff7063eb8b