#ifndef CIRCULARFWDLISTITERATOR_HPP
#define CIRCULARFWDLISTITERATOR_HPP

#include "CircularFwdList.hpp"

namespace zholobov {

  template < typename T >
  class CircularFwdListIterator {
  public:
    CircularFwdListIterator():
      it_(nullptr)
    {}

  private:
    typename CircularFwdList< T >::Node_t* it_;
  };

}

#endif
