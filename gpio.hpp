#ifndef GPIO_HPP_
#define GPIO_HPP_


#include <stdint.h>

// NOTE one pin may only be used as a single in/out/irq at a time

enum PUPD
{
  PUPD_NONE,
  PUPD_UP,
  PUPD_DOWN,
};

enum OUT
{
  OUT_PUSHPULL,
  OUT_OPENDRAIN,
};

enum EDGE
{
  EDGE_POSITIVE,
  EDGE_NEGATIVE,
  EDGE_BOTH,
};

struct gpio_in_t
{
  const uint8_t pin;

  /// @brief initialize any clocks and connect the pin to the pad as an input
  /// @param pullup_pulldown configures the pull up/down resistor on the pad
  /// @return true: succeeded, false: failed
  bool init(PUPD pullup_pulldown);

  /// @brief stop any clocks for the pin and disconnect the pad
  /// @return true: succeeded, false: failed
  bool deinit();

  /// @return true: the pad is logic high, false: the pad is logic low
  bool read();
};

struct gpio_out_t
{
  const uint8_t pin;

  /// @brief initialize any clocks and connect the pin to the pad as an output
  /// @param pullup_pulldown set the pull up/down resistor on the pad
  /// @param out set the output type
  /// @return true: succeeded, false: failed
  bool init(PUPD pullup_pulldown, OUT out_type);

  /// @brief stop any clocks for the pin and disconnect the pad
  /// @return true: succeeded, false: failed
  bool deinit();

  /// @return true: the pad is logic high, false: the pad is logic low
  bool read();
  
  /// @param value true: set the pin to logic high, false: set the pin to logic low
  void write(bool value);
};

struct gpio_irq_t
{
  const uint8_t pin;

  /// @brief initialize any clocks and connect the pin to the pad as an input
  /// @param pullup_pulldown configures the pull up/down resistor on the pad
  /// @param edge_trigger sets the edge that the interrupt will be triggered on
  /// @return true: succeeded, false: failed
  bool init(PUPD pullup_pulldown, EDGE edge_trigger);

  /// @brief stop any clocks for the pin and disconnect the pad
  /// @return true: succeeded, false: failed
  bool deinit();

  /// @brief sets the function that will be called
  /// @param callback function that will be called when the interrupt triggers. the EDGE will specify POSITIVE/NEGATIVE
  void set_callback(void (*callback)(EDGE));

  /// @brief enables the interrupt on the pin as specified in init()
  void enable();

  /// @brief disables the interrupt on the pin if it has been enabled
  void disable();

  /// @return true: the pad is logic high, false: the pad is logic low
  bool read();
};

#endif