//-----------------------------------------------------------------------------
// boost incomplete.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2002
// Eric Friedman
//
// Permission to use, copy, modify, distribute and sell this software
// and its documentation for any purpose is hereby granted without fee, 
// provided that the above copyright notice appears in all copies and 
// that both the copyright notice and this permission notice appear in 
// supporting documentation. No representations are made about the 
// suitability of this software for any purpose. It is provided "as is" 
// without express or implied warranty.

#ifndef BOOST_INCOMPLETE_HPP
#define BOOST_INCOMPLETE_HPP

#include "boost/incomplete_fwd.hpp"

#include "boost/checked_delete.hpp"
#include "boost/move.hpp"
#include "boost/mpl/if.hpp"

namespace boost {

//////////////////////////////////////////////////////////////////////////
// class template incomplete
//
// Treats an incomplete type as a value type.
//
template <typename T>
class incomplete
    : moveable< incomplete<T> >
{
public: // representation
    T* p_;

public: // structors
    ~incomplete();
    incomplete();

    incomplete(const incomplete& operand);
    incomplete(move_source<incomplete> source);

    incomplete(const T& operand);
    incomplete(move_source<T> source);

public: // modifiers
    incomplete& operator=(incomplete rhs)
    {
        swap(rhs);
        return *this;
    }

    incomplete& operator=(move_source<incomplete> source)
    {
        incomplete& rhs = source.get();
        get() = move(rhs.get());

        return *this;
    }

    incomplete& operator=(const T& rhs)
    {
        incomplete temp(rhs);
        swap(temp);

        return *this;
    }

    incomplete& operator=(move_source<T> source)
    {
        T& rhs = source.get();
        get() = move(rhs);

        return *this;
    }

    void swap(incomplete& operand)
    {
        T* temp = operand.p_;
        operand.p_ = p_;
        p_ = temp;
    }

public: // queries
    T& get() { return *get_pointer(); }
    const T& get() const { return *get_pointer(); }

    T* get_pointer() { return p_; }
    const T* get_pointer() const { return p_; }
};

template <typename T>
incomplete<T>::~incomplete()
{
    boost::checked_delete(p_);
}

template <typename T>
incomplete<T>::incomplete()
    : p_(new T)
{
}

template <typename T>
incomplete<T>::incomplete(const incomplete& operand)
    : p_(new T( operand.get() ))
{
}

template <typename T>
incomplete<T>::incomplete(move_source<incomplete> source)
    : p_(new T( move(source.get().get()) ))
{
}


template <typename T>
incomplete<T>::incomplete(const T& operand)
    : p_(new T(operand))
{
}

template <typename T>
incomplete<T>::incomplete(move_source<T> source)
    : p_(new T( move(source.get()) ))
{
}

// function template swap
//
// Swaps two incomplete<T> objects of the same type T.
//
template <typename T>
inline void swap(incomplete<T>& lhs, incomplete<T>& rhs)
{
    lhs.swap(rhs);
}

} // namespace boost

#endif // BOOST_INCOMPLETE_HPP
