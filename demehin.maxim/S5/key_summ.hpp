#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

namespace demehin
{
  struct KeySumm
  {
    int val_res;
    std::string str_res;

    KeySumm();
    void operator()(const std::pair< const int, std::string >&);

  };

  KeySumm::KeySumm():
    val_res(0)
}


#endif
