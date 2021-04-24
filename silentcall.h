// ***************************************************************************
// General Support Classes
// ---------------------------------------------------------------------------
// silentcall.h
// call a slot without sending a signal
// ---------------------------------------------------------------------------
// Copyright (C) 2020 by t2ft - Thomas Thanner
// Waldstraße 15, 86399 Bobingen, Germany
// ---------------------------------------------------------------------------
// 2020-3-23  tt  Initial version created
// ***************************************************************************
#ifndef SILENTCALL_H
#define SILENTCALL_H

template<class T>
class SignalBlockerCallProxy
{
    T * const o;
public:
    explicit SignalBlockerCallProxy( T * oo )
      : o(oo)
    {
    }
    T* operator->()
    {
         return o;
    }
    ~SignalBlockerCallProxy()
    {
        if(o)
            o->blockSignals(false);
    }
};

template<class T>
class SignalBlocker
{
    T * const o;
public:
    explicit SignalBlocker( T * oo )
      : o(oo)
    {
    }
    SignalBlockerCallProxy<T> operator->()
    {
         if (o)
             o->blockSignals( true );
         return SignalBlockerCallProxy<T>(o);
    }
    ~SignalBlocker() {}
};

template<class T>
SignalBlocker<T> SilentCall(T* o)
{
    return SignalBlocker<T>(o);
}

#endif // SILENTCALL_H
