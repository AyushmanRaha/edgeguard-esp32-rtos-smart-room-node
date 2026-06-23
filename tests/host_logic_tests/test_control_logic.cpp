#include <cassert>
#include "edgeguard_control.h"

static SensorSnapshot sensor(bool dhtOk=true, bool distanceOk=true, uint16_t cm=50, bool dark=true, float temp=25.0f){
  SensorSnapshot s; s.dhtOk=dhtOk; s.distanceOk=distanceOk; s.distanceCm=cm; s.lightIsDark=dark; s.temperatureC=temp; return s;
}
static ControlResult run(const SensorSnapshot& s, SystemSnapshot& sys, ControlContext& ctx, uint32_t now){
  ControlResult r=updateControlLogic(s, sys, ctx, defaultControlConfig(), now); sys=r.system; return r;
}
int main(){
  { SystemSnapshot sys; ControlContext ctx; auto r=run(sensor(true,true,50,true),sys,ctx,1000); assert(r.system.relay1On); }
  { SystemSnapshot sys; ControlContext ctx; auto r=run(sensor(true,true,50,false),sys,ctx,1000); assert(!r.system.relay1On); }
  { SystemSnapshot sys; ControlContext ctx; run(sensor(true,true,50,true),sys,ctx,1000); auto r=run(sensor(true,true,200,true),sys,ctx,17000); assert(!r.system.relay1On); }
  { SystemSnapshot sys; ControlContext ctx; run(sensor(true,true,50,true),sys,ctx,1000); auto r=run(sensor(true,true,200,true),sys,ctx,5000); assert(r.system.occupied && r.system.relay1On); }
  { SystemSnapshot sys; ControlContext ctx; auto r=run(sensor(true,true,50,true,36.0f),sys,ctx,1000); assert(r.system.state==State::ALERT && r.system.relay2On); }
  { SystemSnapshot sys; ControlContext ctx; run(sensor(true,true,50,true,36.0f),sys,ctx,1000); auto r=run(sensor(true,true,50,true,32.0f),sys,ctx,2000); assert(!r.system.temperatureAlert && r.system.state==State::AUTO_MONITORING); }
  { SystemSnapshot sys; ControlContext ctx; ControlResult r; for(int i=0;i<5;i++) r=run(sensor(false,true,50,true),sys,ctx,1000+i); assert(r.system.state==State::FAULT && !r.system.relay1On && !r.system.relay2On); }
  { SystemSnapshot sys; ControlContext ctx; ControlResult r; for(int i=0;i<5;i++) r=run(sensor(true,false,0,true),sys,ctx,1000+i); assert(r.system.state==State::FAULT && !r.system.relay1On && !r.system.relay2On); }
  { SystemSnapshot sys; sys.mode=Mode::MANUAL; sys.relay1On=true; sys.relay2On=false; ControlContext ctx; auto r=run(sensor(true,true,200,false),sys,ctx,1000); assert(r.system.state==State::MANUAL_OVERRIDE && r.system.relay1On && !r.system.relay2On); }
  { SystemSnapshot sys; sys.mode=Mode::AWAY; ControlContext ctx; auto r=run(sensor(true,true,50,false),sys,ctx,1000); assert(r.system.state==State::ALERT && !r.system.relay1On && r.system.relay2On); }
  { SystemSnapshot sys; sys.mode=Mode::AWAY; ControlContext ctx; auto r=run(sensor(true,true,200,true),sys,ctx,1000); assert(r.system.state==State::AUTO_MONITORING && !r.system.relay2On); }
  { SystemSnapshot sys; sys.mode=Mode::MANUAL; sys.relay1On=true; sys.relay2On=true; ControlContext ctx; ControlResult r; for(int i=0;i<5;i++) r=run(sensor(false,false,0,true,36),sys,ctx,1000+i); assert(r.system.state==State::FAULT && !r.system.relay1On && !r.system.relay2On); }
  return 0;
}
