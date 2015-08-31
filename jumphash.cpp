//Jump Consistent Hash
//A Fast, Minimal Memory, Consistent Hash Algorithm
//Paper: http://arxiv.org/pdf/1406.2294v1.pdf

#include <stdint.h>
#include <node.h>
#include <v8.h>

namespace jumphash {

  using v8::Exception;
  using v8::FunctionCallbackInfo;
  using v8::HandleScope;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::String;
  using v8::Number;
  using v8::Value;

  int32_t JumpConsistentHash(uint64_t key, int32_t num_buckets) {
    int64_t b = -1, j = 0;
    while (j < num_buckets) {
      b = j;
      key = key * 2862933555777941757ULL + 1;
      j = (b + 1) * (double(1LL << 31) / double((key >> 33) + 1));
    }
    return b;
  }

  // Method JumpConsistentHash
  void Method(const FunctionCallbackInfo<Value>& args) {
    Isolate* isolate = args.GetIsolate();
    if (args.Length() < 2) {
      isolate->ThrowException(Exception::TypeError(
                                                   String::NewFromUtf8(isolate, "Wrong number of arguments")));
      return;
    }
    
    if (!args[0]->IsNumber() || !args[1]->IsNumber()) {
      isolate->ThrowException(Exception::TypeError(
                                                   String::NewFromUtf8(isolate, "Wrong arguments")));
      return;
    }
    uint64_t key = args[0]->IntegerValue();
    int32_t buckets = args[1]->Uint32Value();
    int32_t value = JumpConsistentHash(key,buckets);

    Local<Number> num = Number::New(isolate, value);
    args.GetReturnValue().Set(num);
  }

  void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "jumphash", Method);
  }

  NODE_MODULE(jumphash, init)
}//namespace jumphash
