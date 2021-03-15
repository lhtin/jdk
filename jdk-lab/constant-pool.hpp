class Rewriter: public StackObj {
private:
    InstanceKlass *_klass;
    constantPoolHandle _pool;
    Array<Method *> *_methods;
    
    // for Methodref, Fieldref, InterfaceMethodref
    GrowableArray<int> _cp_map; // cp_index -> cache_index
    GrowableArray<int> _cp_cache_map; // cache_index -> cp_index 
    
    // for 
    // 1. strings, methodHandle, methodType, dynamic（遍历常量池的时候）
    // 2. invokedynamic（遍历字节码的时候）
    GrowableArray<int> _reference_map; // cp_index -> resolved_reference_index
    GrowableArray<int> _resolved_references_map; // resolved_reference_index -> cp_index

    // for _invokedynamic
    GrowableArray<int> _invokedynamic_cp_cache_map; // _invokedynamic_cache_index -> cp_index
    GrowableArray<int> _invokedynamic_references_map; // resolved_reference_index -> cache_index
    
    int _resolved_reference_limit; // 从常量池中resolved的引用，不包括后面invokedynamic添加进去的
}

class ConstantPool : public Metadata {
    Array<u1>*           _tags;
    Array<Klass*>*       _resolved_klasses; // 缓存运行过程中用到的加载好的klass，供下次使用
    /** 跟class文件中的常量索引一致
     * 0
     * 1
     * 2
     * 3
     * 4
     */
};

class ConstantPoolCache: public MetaspaceObj {
    // The following fields need to be modified at runtime, so they cannot be
    // stored in the ConstantPool, which is read-only.
    // Array of resolved objects from the constant pool and map from resolved
    // object index to original constant pool index
    OopHandle            _resolved_references; // 遇到ldc等命令的时候需要填充
    Array<u2>*           _reference_map; // cache_index -> cp_index
    /** 每个item为ConstantPoolCacheEntry类型
     * 0 
     */
};

typedef intptr_t  intx;

class ConstantPoolCacheEntry {
private:
    volatile intx _indices;  // constant pool index & rewrite bytecodes
    Metadata *volatile _f1;       // entry specific metadata field
    volatile intx _f2;       // entry specific int/metadata field
    volatile intx _flags;    // flags
}



/// java.base
/// 当遇到invokedynamic时，会调用该方法
//MethodHandleNatives::linkCallSite

#include "../src/hotspot/share/classfile/systemDictionary.hpp"
/// 调用invokedynamic的启动方法
void SystemDictionary::invoke_bootstrap_method(BootstrapInfo& bootstrap_specifier, TRAPS);
