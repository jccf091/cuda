#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include <vector>
#include <memory>

#include "common.h"
#include "driver.h"

namespace Commands {

struct Context {
  CUmodule module;
  CUstream stream;
};

class Command {
public:
  static Command *Create(Driver *driver, ETERM *batch);
  Command(Driver *driver): driver(driver) {};
  virtual void Run(Context &ctx) = 0;
protected:
  Driver *driver;
private:
  Command();
};

class Batch : public Command {
public:
  Batch(Driver *driver, ETERM *args);
  void Run(Context &ctx);
private:
  std::vector<Command *> commands;
};

class BatchList : public Command {
public:
  BatchList(Driver *driver, ETERM *args);
  void Run(Context &ctx);
private:
  std::vector<Command *> batches;
};

class RunCommand: public Command {
public:
  RunCommand(Driver *driver, ETERM *args);
  void Run(Context &ctx);
private:
  std::string kernel;
  unsigned int bx;
  unsigned int by;
  unsigned int bz;
  unsigned int gx;
  unsigned int gy;
  unsigned int gz;
  std::shared_ptr<RunArguments> arguments;
};

// class EventCommand: public Command {
// public:
//   EventCommand(Driver *driver, ETERM *args);
//   virtual void Run(Context &ctx);
// };
//
// class WaitCommand: public Command {
// public:
//   WaitCommand(Driver *driver, ETERM *args);
//   virtual void Run(Context &ctx);
// };

} // namespace Commands
#endif // __COMMANDS_H__
