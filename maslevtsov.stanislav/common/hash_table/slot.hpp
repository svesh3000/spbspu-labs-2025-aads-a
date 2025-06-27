#ifndef HASH_TABLE_SLOT_HPP
#define HASH_TABLE_SLOT_HPP

namespace maslevtsov {
  namespace detail {
    enum class SlotState
    {
      EMPTY,
      OCCUPIED,
      DELETED,
    };

    template< typename T >
    struct Slot
    {
      alignas(T) unsigned char data[sizeof(T)];
      SlotState state;

      Slot():
        state(SlotState::EMPTY)
      {}

      T* get_data_ptr()
      {
        return reinterpret_cast< T* >(&data);
      }

      const T* get_data_ptr() const
      {
        return reinterpret_cast< const T* >(&data);
      }

      template< typename... Args >
      void construct(Args&&... args)
      {
        new (&data) T(std::forward< Args >(args)...);
        state = SlotState::OCCUPIED;
      }

      void destroy()
      {
        if (state == SlotState::OCCUPIED) {
          get_data_ptr()->~T();
          state = SlotState::DELETED;
        }
      }
    };
  }
}

#endif
