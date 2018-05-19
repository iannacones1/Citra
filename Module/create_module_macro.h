#ifndef _CREATE_MODULE_MACRO_H_
#define _CREATE_MODULE_MACRO_H_

// http://stackoverflow.com/questions/16495909/c-dynamically-load-classes
#define MODULE(CLASS_TYPE, CLASS_NAME) \
extern "C" CLASS_TYPE* create_module() { return new CLASS_NAME; } \
extern "C" void free_module(CLASS_TYPE* p) { delete p; } \

#endif /* _CREATE_MODULE_MACRO_H_ */
