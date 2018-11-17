#include <Arduino.h>
#include <PCF8574.h>
#include <PLC.h>
#include <Wire.h>

#include <mqtt/async_client.h>

#include <iostream>
#include <string>
#include <vector>

using namespace BitHelpers;

static mqtt::async_client client(std::string({"tcp://192.168.88.241:1883"}),
                                 std::string({"groundfloor"}), 0);

void setup(void)
{
  Wire.begin();
  std::cout << "Connecting ... ";
  mqtt::token_ptr conntok = client.connect();
  conntok->wait();
  std::cout << "done." << std::endl;
}

void loop(void)
{
  static PCF8574 pcfIn(0x38);

  uint8_t const inputStates = pcfIn.read();

  static std::vector<size_t> const simpleInputs = {0};
  static std::vector<PLC::RTrig> triggerInputs(simpleInputs.size());

  for (auto idx = 0; idx < simpleInputs.size(); idx++)
  {
    if (triggerInputs[idx].trigger(bitget(inputStates, simpleInputs[idx])))
    {
      // overrule and light
      mqtt::message_ptr pubmsg = mqtt::make_message(std::string({"/homeautomation/bad/light/set"}), "1");
      pubmsg->set_qos(1);
      client.publish(pubmsg);
    }
  }

  delay(20);
}
