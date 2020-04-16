#ifndef ARDUINO_H
#define ARDUINO_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void setup(void);
void loop(void);
void teardown(void);

void delay(unsigned long ms);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ARDUINO_H */
