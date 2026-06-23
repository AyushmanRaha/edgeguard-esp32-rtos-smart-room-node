#include <cassert>
#include <cstdio>
#include <cstring>
#include "edgeguard_event_log.h"
int main(){
  EdgeGuardEventLog log; assert(log.count()==0);
  log.push("one"); assert(log.count()==1); assert(std::strcmp(log.get(0),"one")==0);
  for(size_t i=0;i<EdgeGuardEventLog::kCapacity+2;i++){ char b[16]; snprintf(b,sizeof(b),"e%zu",i); log.push(b); }
  assert(log.count()==EdgeGuardEventLog::kCapacity); assert(std::strcmp(log.get(0),"e2")==0);
  assert(std::strcmp(log.get(EdgeGuardEventLog::kCapacity-1),"e21")==0);
  for(size_t i=0;i<log.count();++i){ char b[16]; snprintf(b,sizeof(b),"e%zu",i+2); assert(std::strcmp(log.get(i),b)==0); }
  return 0;
}
