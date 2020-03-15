#pragma once

/* http://www.boost.org/doc/libs/1_54_0/libs/utility/value_init.htm#initialized_value  */
class initialized_value_t
{
  public :
    template <class T> operator T() const ;
};

initialized_value_t const initialized_value = {} ;