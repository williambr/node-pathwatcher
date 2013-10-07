#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include <node.h>
#include <uv.h>

using namespace v8;

#ifdef _WIN32
#include <windows.h>

// Platform-dependent definetion of handle.
typedef HANDLE WatcherHandle;

// Conversion between V8 value and WatcherHandle.
#define WatcherHandleToV8Value(h) External::New(h)
#define V8ValueToWatcherHandle(v) Handle<External>::Cast(v)->Value()
#define IsV8ValueWatcherHandle(v) v->IsExternal()
#else
// Correspoding definetions on OS X and Linux.
typedef int WatcherHandle;
#define WatcherHandleToV8Value(h) Integer::New(h)
#define V8ValueToWatcherHandle(v) v->IntegerValue()
#define IsV8ValueWatcherHandle(v) v->IsNumber()
#endif

void PlatformInit();
void PlatformThread();
WatcherHandle PlatformWatch(const char* path);
void PlatformUnwatch(WatcherHandle handle);
bool PlatformIsHandleValid(WatcherHandle handle);

enum EVENT_TYPE {
  EVENT_CHANGE,
  EVENT_RENAME,
  EVENT_DELETE
};

void WaitForMainThread();
void WakeupNewThread();
void PostEvent(EVENT_TYPE type, WatcherHandle handle, const char* path);

void CommonInit();
Handle<Value> SetCallback(const Arguments& args);
Handle<Value> Watch(const Arguments& args);
Handle<Value> Unwatch(const Arguments& args);

#endif  // SRC_COMMON_H_
