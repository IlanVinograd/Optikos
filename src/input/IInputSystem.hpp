#ifndef IINPUTSYSTEM_H
#define IINPUTSYSTEM_H

#include <vector>
#include <functional>
#include <string>

namespace Optikos
{

constexpr unsigned int Pressed = 1;
constexpr unsigned int Release = 2;
constexpr unsigned int Held    = 3;

struct Cursor
{
    double x;
    double y;
};

struct Binding
{
    int          key;
    int          action;
    unsigned int state = 0;
};

struct Action
{
    std::string           name;
    std::vector<Binding>  bindings;
    std::function<void()> callback = nullptr;
};

class IInputSystem
{
   public:
    virtual ~IInputSystem()    = default;
    virtual Cursor getCursor() = 0;

    virtual void bind(const std::string& action, int key, unsigned int state = Pressed) = 0;
    virtual void unbind(const std::string& action)                                      = 0;
    virtual void onAction(const std::string& action, std::function<void()> cb)          = 0;
    virtual void dispatch(int key, int action)                                          = 0;

   private:
};

}  // namespace Optikos

#endif /* IINPUTSYSTEM_H */