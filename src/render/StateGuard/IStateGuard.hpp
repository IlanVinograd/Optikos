#ifndef ISTATEGUARD_H
#define ISTATEGUARD_H

class IStateGuard
{
   public:
        virtual void acquire() = 0;
        virtual void release() = 0;
   private:
};

#endif /* ISTATEGUARD_H */