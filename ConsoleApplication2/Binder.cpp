#include "Binder.h"

////@brief:��ȡ������ĵ���ʵ������  
//ClassFactory& ClassFactory::GetInstance() 
//{
//    static ClassFactory Factory;
//    return Factory;
//}
//
////@brief:ͨ���������ַ�����ȡ���ʵ��
//void* ClassFactory::GetClassByName(string ClassName) 
//{
//    map<string, PTRCreateObject>::const_iterator Iter = ClassMap.find(ClassName);
//    if (Iter == ClassMap.end())
//        return NULL;
//    else
//        return Iter->second();
//}
//
////@brief:���������������ַ����Ͷ�Ӧ�Ĵ��������ĺ������浽map��   
//void ClassFactory::RegistClass(string Name, PTRCreateObject Method) 
//{
//    ClassMap.insert(pair<string, PTRCreateObject>(Name, Method));
//}
//
//#define REGISTER(ClassName)                                             \
//    ClassName* ObjectCreator##ClassName(){                              \
//        return new ClassName();                                           \
//    }                                                                   \
//    RegisterAction CreatorRegister##ClassName(                        \
//        #ClassName,(PTRCreateObject)ObjectCreator##ClassName)
//
//
//REGISTER(TestClassA);
