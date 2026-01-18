#ifndef IINPUTSYSTEM_H
#define IINPUTSYSTEM_H

namespace Optikos
{
struct Cursor
{
    double x;
    double y;
};

class IInputSystem
{
   public:
    virtual ~IInputSystem()    = default;
    virtual Cursor getCursor() = 0;

   private:
};

}  // namespace Optikos

#endif /* IINPUTSYSTEM_H */