/*
 * 1. 递归解析class file，获取layout等信息
 * 2. 创建instance klass，创建对应的java.lang.Class实例
 * 3. 方法链接，确定代码执行入口（解释器、编译器）
 */

#include "../src/hotspot/share/classfile/classLoader.hpp"
static InstanceKlass* ClassLoader::load_class(Symbol* class_name, bool search_append_only, TRAPS);

InstanceKlass; // 类的C++表示
Method; // Java中的方法

#include "../src/hotspot/share/runtime/sharedRuntime.hpp"
/// 生成i2c和c2i适配器
void SharedRuntime::gen_i2c_adapter(MacroAssembler *masm,
                                    int total_args_passed,
                                    int comp_args_on_stack,
                                    const BasicType *sig_bt,
                                    const VMRegPair *regs);
